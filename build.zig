const std = @import("std");

const StaticPluginStep = @import("src/StaticPluginStep.zig");

const WwisePlatform = @import("src/wwise_platform.zig").WwisePlatform;

pub const WwiseConfiguration = enum {
    debug,
    profile,
    release,
};

pub const WwiseConfigOptions = struct {
    use_communication: bool = true,
    use_default_job_worker: bool = false,
    wwise_sdk_path: ?[]const u8 = null,
    use_static_crt: bool = true,
    configuration: WwiseConfiguration = .profile,
    include_default_io_hook_blocking: bool = false,
    include_default_io_hook_deferred: bool = false,
    include_file_package_io_blocking: bool = false,
    include_file_package_io_deferred: bool = false,
    static_plugins: []const []const u8 = &.{},
};

pub const WwiseBuildOptions = struct {
    platform: WwisePlatform,
    wwise_sdk_path: []const u8,
    configuration: WwiseConfiguration,
    use_static_crt: bool,
    use_communication: bool,
    use_default_job_worker: bool,
    include_default_io_hook_blocking: bool,
    include_default_io_hook_deferred: bool,
    include_file_package_io_blocking: bool,
    include_file_package_io_deferred: bool,
    string_stack_size: usize = 0,
    static_plugins: []const []const u8,

    pub fn useDefaultIoHooks(self: WwiseBuildOptions) bool {
        return self.include_default_io_hook_blocking or self.include_default_io_hook_deferred or self.include_file_package_io_blocking or self.include_default_io_hook_deferred;
    }

    pub fn useFilePackageIO(self: WwiseBuildOptions) bool {
        return self.include_file_package_io_blocking or self.include_file_package_io_deferred;
    }
};

pub const WwisePackage = struct {
    options: WwiseBuildOptions,
    module: *std.build.Module,
    c_library: *std.build.Step.Compile,
};

const CppFlags: []const []const u8 = &.{ "-std=c++17", "-DUNICODE", "-Wall", "-Wpedantic" };

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const wwise_package = try package(b, target, optimize, .{});

    const wwise_test = b.addTest(.{
        .name = "wwise_zig_test",
        .root_source_file = .{
            .path = thisDir() ++ "/tests/tests.zig",
        },
        .target = target,
        .optimize = optimize,
    });
    try wwiseLink(wwise_test, wwise_package.options);
    wwise_test.linkLibrary(wwise_package.c_library);
    wwise_test.addModule("wwise-zig", wwise_package.module);
    b.installArtifact(wwise_test);

    const run_test_cmd = b.addRunArtifact(wwise_test);
    run_test_cmd.step.dependOn(b.getInstallStep());

    const test_step = b.step("test", "Run library tests");
    test_step.dependOn(&run_test_cmd.step);

    const build_only_test_step = b.step("test_build_only", "Build the tests but does not run it");
    build_only_test_step.dependOn(&wwise_test.step);
    build_only_test_step.dependOn(b.getInstallStep());
}

pub fn package(b: *std.Build, target: std.zig.CrossTarget, optimize: std.builtin.Mode, config_options: WwiseConfigOptions) !WwisePackage {
    if (target.getOsTag() == .windows and target.getAbi() == .gnu) {
        return error.GnuAbiNotSupported;
    }

    const override_wwise_sdk_path_option = b.option([]const u8, "wwise_sdk", "Override the path to the Wwise SDK, by default it will use the path in environment variable WWISESDK");
    const wwise_configuration_option = b.option(WwiseConfiguration, "configuration", "Which library of Wwise to use (Default: profile)");
    const wwise_use_static_crt_option = b.option(bool, "use_static_crt", "On Windows, use the static CRT version of the library (Default: true)");
    const wwise_use_communication_option = b.option(bool, "use_communication", "Enable remote communication with Wwise Authoring. Disabled by default on Release configuration so you can leave it true at all time (Default: true)");
    const wwise_use_default_job_worker_option = b.option(bool, "use_default_job_worker", "Enable usage of the default job worker given by Audiokinetic. (Default: false)");
    const wwise_string_stack_size_option = b.option(usize, "string_stack_size", "Stack size to use for functions that accepts AkOsChar and null-terminated strings (Default: 256)");

    const wwise_include_default_io_hook_blocking_option = b.option(bool, "include_default_io_hook_blocking", "Include the Default IO Hook Blocking");
    const wwise_include_default_io_hook_deferred_option = b.option(bool, "include_default_io_hook_deferred", "Include the Default IO Hook Deferred");
    const wwise_include_file_package_io_blocking_option = b.option(bool, "include_file_package_io_blocking", "Include the File Package IO Hook Blocking");
    const wwise_include_file_package_io_deferred_option = b.option(bool, "include_file_package_io_deferred", "Include the File Package IO Hook Deferred");

    const wwisee_static_plugins_option = b.option([]const []const u8, "static_plugins", "List of builtin static plugins to build");

    const wwise_configuration = wwise_configuration_option orelse config_options.configuration;

    const wwise_build_options = WwiseBuildOptions{
        .platform = try getWwisePlatform(target),
        .wwise_sdk_path = getWwiseSDKPath(b, override_wwise_sdk_path_option),
        .configuration = wwise_configuration,
        .use_static_crt = wwise_use_static_crt_option orelse config_options.use_static_crt,
        .use_communication = blk: {
            if (wwise_configuration == .release) {
                break :blk false;
            }

            break :blk wwise_use_communication_option orelse config_options.use_communication;
        },
        .use_default_job_worker = wwise_use_default_job_worker_option orelse config_options.use_default_job_worker,
        .include_default_io_hook_blocking = wwise_include_default_io_hook_blocking_option != null or wwise_include_file_package_io_blocking_option != null or config_options.include_default_io_hook_blocking or config_options.include_file_package_io_blocking,
        .include_default_io_hook_deferred = wwise_include_default_io_hook_deferred_option != null or wwise_include_file_package_io_deferred_option != null or config_options.include_default_io_hook_deferred or config_options.include_file_package_io_deferred,
        .include_file_package_io_blocking = wwise_include_file_package_io_blocking_option orelse config_options.include_file_package_io_blocking,
        .include_file_package_io_deferred = wwise_include_file_package_io_deferred_option orelse config_options.include_file_package_io_deferred,
        .string_stack_size = wwise_string_stack_size_option orelse 256,
        .static_plugins = wwisee_static_plugins_option orelse config_options.static_plugins,
    };

    const wwise_c = b.addStaticLibrary(.{
        .name = "wwise-c",
        .target = target,
        .optimize = optimize,
    });
    wwise_c.addCSourceFile(thisDir() ++ "/bindings/WwiseC.cpp", CppFlags);
    wwise_c.addIncludePath(thisDir() ++ "/bindings");

    const static_plugin_step = StaticPluginStep.create(b, .{ .static_plugins = wwise_build_options.static_plugins });
    wwise_c.addCSourceFileSource(.{
        .args = CppFlags,
        .source = .{
            .generated = &static_plugin_step.output_file,
        },
    });

    for (wwise_build_options.static_plugins) |static_plugin| {
        wwise_c.linkSystemLibrary(static_plugin);
    }

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

    try handleDefaultWwiseSystems(wwise_c, wwise_build_options);

    const option_step = b.addOptions();
    option_step.addOption(usize, "string_stack_size", wwise_string_stack_size_option orelse 256);
    option_step.addOption(bool, "use_communication", wwise_build_options.use_communication);
    option_step.addOption(bool, "use_default_job_worker", wwise_build_options.use_default_job_worker);
    option_step.addOption(bool, "include_default_io_hook_blocking", wwise_build_options.include_default_io_hook_blocking);
    option_step.addOption(bool, "include_default_io_hook_deferred", wwise_build_options.include_default_io_hook_deferred);
    option_step.addOption(bool, "include_file_package_io_blocking", wwise_build_options.include_file_package_io_blocking);
    option_step.addOption(bool, "include_file_package_io_deferred", wwise_build_options.include_file_package_io_deferred);
    option_step.addOption(WwisePlatform, "platform", wwise_build_options.platform);

    const wwise_compile_options = option_step.createModule();

    const wwise_zig_module = b.addModule("wwise-zig", .{
        .source_file = .{
            .path = thisDir() ++ "/src/wwise-zig.zig",
        },
        .dependencies = &.{
            .{ .name = "wwise_options", .module = wwise_compile_options },
        },
    });

    return .{
        .options = wwise_build_options,
        .module = wwise_zig_module,
        .c_library = wwise_c,
    };
}

pub fn wwiseLink(compile_step: *std.Build.CompileStep, wwise_build_options: WwiseBuildOptions) !void {
    const wwise_library_relative_path = try getWwiseLibraryPath(compile_step.step.owner, compile_step.target, wwise_build_options);

    compile_step.addSystemIncludePath(compile_step.step.owner.pathJoin(&.{ wwise_build_options.wwise_sdk_path, "include" }));
    compile_step.addIncludePath(thisDir() ++ "/bindings");
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

fn getWwisePlatform(target: std.zig.CrossTarget) !WwisePlatform {
    return switch (target.getOsTag()) {
        .windows => .windows,
        .linux => if (target.getAbi() == .android) .android else .linux,
        .macos => .macos,
        .ios => .ios,
        .tvos => .tvos,
        else => error.OsNotSupported,
    };
}

fn getWwiseLibraryPath(b: *std.Build, target: std.zig.CrossTarget, wwise_build_options: WwiseBuildOptions) ![]const u8 {
    const config_string = switch (wwise_build_options.configuration) {
        .debug => "Debug",
        .profile => "Profile",
        .release => "Release",
    };

    switch (wwise_build_options.platform) {
        .windows => {
            const arch_string = switch (target.getCpuArch()) {
                .x86 => "Win32",
                .x86_64 => "x64",
                else => return error.ArchNotSupported,
            };

            const static_crt_string = if (wwise_build_options.use_static_crt) "(StaticCRT)" else "";

            return b.fmt("{s}_vc170/{s}{s}/lib", .{ arch_string, config_string, static_crt_string });
        },
        .android => {
            const arch_string = switch (target.getCpuArch()) {
                .aarch64 => "arm64-v8a",
                .arm => "armeabi-v7a",
                .x86 => "x86",
                .x86_64 => "x86_64",
                else => return error.ArchNotSupported,
            };

            return b.fmt("Android_{s}/{s}/lib", .{ arch_string, config_string });
        },
        .linux => {
            const arch_string = switch (target.getCpuArch()) {
                .x86_64 => "x64",
                .aarch64 => "aarch64",
                else => return error.ArchNotSupported,
            };

            return b.fmt("Linux_{s}/{s}/lib", .{ arch_string, config_string });
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

fn handleDefaultWwiseSystems(compile_step: *std.Build.CompileStep, wwise_build_options: WwiseBuildOptions) !void {
    if (!wwise_build_options.useDefaultIoHooks() or !wwise_build_options.use_default_job_worker) {
        return;
    }

    const platform_name = switch (wwise_build_options.platform) {
        .windows => "Win32",
        .android => "Android",
        .linux, .macos, .ios, .tvos => "POSIX",
        else => return error.OsNotSupported,
    };

    compile_step.addIncludePath(compile_step.step.owner.fmt("{s}/samples/SoundEngine/Common", .{wwise_build_options.wwise_sdk_path}));
    compile_step.addIncludePath(compile_step.step.owner.fmt("{s}/samples/SoundEngine/{s}", .{ wwise_build_options.wwise_sdk_path, platform_name }));

    if (wwise_build_options.useDefaultIoHooks()) {
        compile_step.addCSourceFile(compile_step.step.owner.fmt("{s}/samples/SoundEngine/Common/AkMultipleFileLocation.cpp", .{wwise_build_options.wwise_sdk_path}), CppFlags);
        compile_step.addCSourceFile(compile_step.step.owner.fmt("{s}/samples/SoundEngine/Common/AkGeneratedSoundBanksResolver.cpp", .{wwise_build_options.wwise_sdk_path}), CppFlags);
    }

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

    if (wwise_build_options.use_default_job_worker) {
        compile_step.defineCMacro("WWISEC_USE_DEFAULT_JOB_WORKER", null);
        compile_step.addCSourceFile(compile_step.step.owner.fmt("{s}/samples/SoundEngine/Common/AkJobWorkerMgr.cpp", .{wwise_build_options.wwise_sdk_path}), CppFlags);
    }

    if (wwise_build_options.useFilePackageIO()) {
        compile_step.addCSourceFile(compile_step.step.owner.fmt("{s}/samples/SoundEngine/Common/AkFilePackage.cpp", .{wwise_build_options.wwise_sdk_path}), CppFlags);
        compile_step.addCSourceFile(compile_step.step.owner.fmt("{s}/samples/SoundEngine/Common/AkFilePackageLUT.cpp", .{wwise_build_options.wwise_sdk_path}), CppFlags);
    }
}

inline fn thisDir() []const u8 {
    return comptime std.fs.path.dirname(@src().file) orelse ".";
}
