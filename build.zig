const std = @import("std");

const WwiseConfiguration = enum {
    debug,
    profile,
    release,
};

const WwiseBuildOptions = struct {
    wwise_sdk_path: []const u8,
    configuration: WwiseConfiguration,
    use_static_crt: bool,
    use_communication: bool,
    include_default_io_hook_blocking: bool,
    include_default_io_hook_deferred: bool,
    include_file_package_io_blocking: bool,
    include_file_package_io_deferred: bool,

    pub fn useDefaultIoHooks(self: WwiseBuildOptions) bool {
        return self.include_default_io_hook_blocking or self.include_default_io_hook_deferred or self.include_file_package_io_blocking or self.include_default_io_hook_deferred;
    }

    pub fn useFilePackageIO(self: WwiseBuildOptions) bool {
        return self.include_file_package_io_blocking or self.include_file_package_io_deferred;
    }
};

const CppFlags: []const []const u8 = &.{ "-std=c++17", "-Wall", "-Wpedantic" };

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    if (target.getOsTag() == .windows and target.getAbi() == .gnu) {
        return error.GnuAbiNotSupported;
    }

    const override_wwise_sdk_path_option = b.option([]const u8, "wwise_sdk", "Override the path to the Wwise SDK, by default it will use the path in environment variable WWISESDK");
    const wwise_configuration_option = b.option(WwiseConfiguration, "configuration", "Which library of Wwise to use");
    const wwise_use_static_crt_option = b.option(bool, "use_static_crt", "On Windows, use the static CRT version of the library");
    const wwise_use_communication_option = b.option(bool, "use_communication", "Enable remote communication with Wwise Authoring. Disabled by default on Release configuration so you can leave it true at all time");
    const wwise_string_stack_size_option = b.option(usize, "string_stack_size", "Stack size to use for functions that accepts AkOsChar and null-terminated strings (Default 512)");

    const wwise_include_default_io_hook_blocking_option = b.option(bool, "include_default_io_hook_blocking", "Include the Default IO Hook Blocking");
    const wwise_include_default_io_hook_deferred_option = b.option(bool, "include_default_io_hook_deferred", "Include the Default IO Hook Deferred");
    const wwise_include_file_package_io_blocking_option = b.option(bool, "include_file_package_io_blocking", "Include the File Package IO Hook Blocking");
    const wwise_include_file_package_io_deferred_option = b.option(bool, "include_file_package_io_deferred", "Include the File Package IO Hook Deferred");

    const wwise_configuration = wwise_configuration_option orelse .profile;

    const wwise_build_options = WwiseBuildOptions{
        .wwise_sdk_path = getWwiseSDKPath(b, override_wwise_sdk_path_option),
        .configuration = wwise_configuration,
        .use_static_crt = wwise_use_static_crt_option orelse true,
        .use_communication = blk: {
            if (wwise_configuration == .release) {
                break :blk false;
            }

            break :blk wwise_use_communication_option orelse false;
        },
        .include_default_io_hook_blocking = wwise_include_default_io_hook_blocking_option != null or wwise_include_file_package_io_blocking_option != null,
        .include_default_io_hook_deferred = wwise_include_default_io_hook_deferred_option != null or wwise_include_file_package_io_deferred_option != null,
        .include_file_package_io_blocking = wwise_include_file_package_io_blocking_option orelse false,
        .include_file_package_io_deferred = wwise_include_file_package_io_deferred_option orelse false,
    };

    const wwise_c = b.addStaticLibrary(.{
        .name = "wwise-c",
        .target = target,
        .optimize = optimize,
    });
    wwise_c.addCSourceFile("bindings/WwiseC.cpp", CppFlags);
    try wwiseLink(wwise_c, wwise_build_options);
    wwise_c.linkLibC();
    if (target.getOsTag() != .windows) {
        wwise_c.linkLibCpp();
    }

    if (target.getOsTag() == .windows) {
        wwise_c.defineCMacro("UNICODE", null);
    }

    if (wwise_build_options.use_communication) {
        wwise_c.defineCMacro("WWISEC_USE_COMMUNICATION", null);
    }

    if (wwise_build_options.configuration == .release) {
        wwise_c.defineCMacro("AK_OPTIMIZED", null);
    }

    try handleDefaultIOHooks(wwise_c, wwise_build_options);

    // TODO: mlarouche: Remove when https://github.com/ziglang/zig/issues/14719 is fixed
    b.installArtifact(wwise_c);

    const option_step = b.addOptions();
    option_step.addOption(usize, "string_stack_size", wwise_string_stack_size_option orelse 512);
    option_step.addOption(bool, "use_communication", wwise_build_options.use_communication);
    option_step.addOption(bool, "include_default_io_hook_blocking", wwise_build_options.include_default_io_hook_blocking);
    option_step.addOption(bool, "include_default_io_hook_deferred", wwise_build_options.include_default_io_hook_deferred);
    option_step.addOption(bool, "include_file_package_io_blocking", wwise_build_options.include_file_package_io_blocking);
    option_step.addOption(bool, "include_file_package_io_deferred", wwise_build_options.include_file_package_io_deferred);

    const wwise_compile_options = option_step.createModule();

    const wwise_zig_module = b.addModule("wwise-zig", .{
        .source_file = .{
            .path = "src/wwise-zig.zig",
        },
        .dependencies = &.{
            .{ .name = "wwise_options", .module = wwise_compile_options },
        },
    });

    const wwise_test = b.addTest(.{
        .name = "wwise_zig_test",
        .root_source_file = .{
            .path = "tests/tests.zig",
        },
        .target = target,
        .optimize = optimize,
    });
    try wwiseLink(wwise_test, wwise_build_options);
    wwise_test.linkLibrary(wwise_c);
    wwise_test.addModule("wwise-zig", wwise_zig_module);
    b.installArtifact(wwise_test);

    const run_test_cmd = b.addRunArtifact(wwise_test);
    run_test_cmd.step.dependOn(b.getInstallStep());

    const test_step = b.step("test", "Run library tests");
    test_step.dependOn(&run_test_cmd.step);

    const build_only_test_step = b.step("test_build_only", "Build the tests but does not run it");
    build_only_test_step.dependOn(&wwise_test.step);
    build_only_test_step.dependOn(b.getInstallStep());
}

fn wwiseLink(compile_step: *std.Build.CompileStep, wwise_build_options: WwiseBuildOptions) !void {
    const wwise_library_relative_path = try getWwiseLibraryPath(compile_step.step.owner, compile_step.target, wwise_build_options);

    compile_step.addSystemIncludePath(compile_step.step.owner.pathJoin(&.{ wwise_build_options.wwise_sdk_path, "include" }));
    compile_step.addIncludePath("bindings");
    compile_step.addLibraryPath(compile_step.step.owner.pathJoin(&.{ wwise_build_options.wwise_sdk_path, wwise_library_relative_path }));

    if (wwise_build_options.use_communication) {
        compile_step.linkSystemLibrary("CommunicationCentral");

        if (compile_step.target.getOsTag() == .windows) {
            compile_step.linkSystemLibrary("ws2_32");
        }
    }

    compile_step.linkSystemLibrary("AkSoundEngine");
    compile_step.linkSystemLibrary("AkStreamMgr");
    compile_step.linkSystemLibrary("AkMemoryMgr");
    compile_step.linkSystemLibrary("AkMusicEngine");

    if (compile_step.target.getOsTag() == .windows) {
        compile_step.linkSystemLibrary("user32");
    }
}

fn getWwiseSDKPath(b: *std.Build, override_wwise_sdk_path_opt: ?[]const u8) []const u8 {
    if (override_wwise_sdk_path_opt) |wwise_sdk_path| {
        return wwise_sdk_path;
    }

    if (b.env_map.get("WWISESDK")) |wwise_sdk_path| {
        return wwise_sdk_path;
    }

    return "";
}

fn getWwiseLibraryPath(b: *std.Build, target: std.zig.CrossTarget, wwise_build_options: WwiseBuildOptions) ![]const u8 {
    const config_string = switch (wwise_build_options.configuration) {
        .debug => "Debug",
        .profile => "Profile",
        .release => "Release",
    };

    switch (target.getOsTag()) {
        .windows => {
            const arch_string = switch (target.getCpuArch()) {
                .x86 => "Win32",
                .x86_64 => "x64",
                else => return error.ArchNotSupported,
            };

            const static_crt_string = if (wwise_build_options.use_static_crt) "(StaticCRT)" else "";

            return b.fmt("{s}_vc170/{s}{s}/lib", .{ arch_string, config_string, static_crt_string });
        },
        .linux => {
            if (target.getAbi() == .android) {
                const arch_string = switch (target.getCpuArch()) {
                    .aarch64 => "arm64-v8a",
                    .arm => "armeabi-v7a",
                    .x86 => "x86",
                    .x86_64 => "x86_64",
                    else => return error.ArchNotSupported,
                };

                return b.fmt("Android_{s}/{s}/lib", .{ arch_string, config_string });
            } else {
                const arch_string = switch (target.getCpuArch()) {
                    .x86_64 => "x64",
                    .aarch64 => "aarch64",
                    else => return error.ArchNotSupported,
                };

                return b.fmt("Linux_{s}/{s}/lib", .{ arch_string, config_string });
            }
        },
        .macos => {
            return b.fmt("Mac/{s}/lib", .{config_string});
        },
        .ios => {
            const abi_string = switch (target.getAbi()) {
                .simulator => "iphonesimulator",
                else => "iphoneos",
            };

            return b.fmt("iOS/{s}-{s}/lib", .{ config_string, abi_string });
        },
        .tvos => {
            const abi_string = switch (target.getAbi()) {
                .simulator => "appletvsimulator",
                else => "appletvos",
            };

            return b.fmt("tvOS/{s}-{s}/lib", .{ config_string, abi_string });
        },
        else => {
            return error.OsNotSupported;
        },
    }

    return "";
}

fn handleDefaultIOHooks(compile_step: *std.Build.CompileStep, wwise_build_options: WwiseBuildOptions) !void {
    if (!wwise_build_options.useDefaultIoHooks()) {
        return;
    }

    const platform_name = blk: {
        switch (compile_step.target.getOsTag()) {
            .windows => break :blk "Win32",
            .linux,
            .macos,
            .ios,
            .tvos,
            => {
                if (compile_step.target.getAbi() == .android) {
                    break :blk "Android";
                }
                break :blk "POSIX";
            },
            else => {
                return error.OsNotSupported;
            },
        }

        break :blk "";
    };

    compile_step.addIncludePath(compile_step.step.owner.fmt("{s}/samples/SoundEngine/Common", .{wwise_build_options.wwise_sdk_path}));
    compile_step.addIncludePath(compile_step.step.owner.fmt("{s}/samples/SoundEngine/{s}", .{ wwise_build_options.wwise_sdk_path, platform_name }));

    compile_step.addCSourceFile(compile_step.step.owner.fmt("{s}/samples/SoundEngine/Common/AkMultipleFileLocation.cpp", .{wwise_build_options.wwise_sdk_path}), CppFlags);
    compile_step.addCSourceFile(compile_step.step.owner.fmt("{s}/samples/SoundEngine/Common/AkGeneratedSoundBanksResolver.cpp", .{wwise_build_options.wwise_sdk_path}), CppFlags);

    if (wwise_build_options.include_default_io_hook_blocking) {
        compile_step.defineCMacro("WWISEC_INCLUDE_DEFAULT_IO_HOOK_BLOCKING", null);
        compile_step.addCSourceFile(compile_step.step.owner.fmt("{s}/samples/SoundEngine/{s}/AkDefaultIOHookBlocking.cpp", .{ wwise_build_options.wwise_sdk_path, platform_name }), CppFlags);
    }

    if (wwise_build_options.include_default_io_hook_deferred) {
        compile_step.defineCMacro("WWISEC_INCLUDE_DEFAULT_IO_HOOK_DEFERRED", null);
        compile_step.addCSourceFile(compile_step.step.owner.fmt("{s}/samples/SoundEngine/{s}/AkDefaultIOHookDeferred.cpp", .{ wwise_build_options.wwise_sdk_path, platform_name }), CppFlags);
    }

    if (wwise_build_options.include_file_package_io_blocking) {
        compile_step.defineCMacro("WWISEC_INCLUDE_FILE_PACKAGE_IO_BLOCKING", null);
    }

    if (wwise_build_options.include_file_package_io_deferred) {
        compile_step.defineCMacro("WWISEC_INCLUDE_FILE_PACKAGE_IO_DEFERRED", null);
    }

    if (wwise_build_options.useFilePackageIO()) {
        compile_step.addCSourceFile(compile_step.step.owner.fmt("{s}/samples/SoundEngine/Common/AkFilePackage.cpp", .{wwise_build_options.wwise_sdk_path}), CppFlags);
        compile_step.addCSourceFile(compile_step.step.owner.fmt("{s}/samples/SoundEngine/Common/AkFilePackageLUT.cpp", .{wwise_build_options.wwise_sdk_path}), CppFlags);
    }
}
