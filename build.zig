const std = @import("std");

const WwiseConfiguration = enum {
    debug,
    profile,
    release,
};

const WwiseOptions = struct {
    wwise_sdk_path: []const u8,
    configuration: WwiseConfiguration,
    use_static_crt: bool,
    use_communication: bool,
};

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    if (target.getOsTag() == .windows and target.getAbi() == .gnu) {
        return error.GnuAbiNotSupported;
    }

    const override_wwise_sdk_path_option = b.option([]const u8, "override_wwise_sdk", "Override the path to the Wwise SDK, by default it will use the path in environment variable WWISESDK");
    const wwise_configuration_option = b.option(WwiseConfiguration, "configuration", "Which library of Wwise to use");
    const wwise_use_static_crt_option = b.option(bool, "use_static_crt", "On Windows, use the static CRT version of the library");
    const wwise_use_communication_option = b.option(bool, "use_communication", "Enable remote communication with Wwise Authoring. Disabled by default on Release configuration so you can leave it true at all time");

    const wwise_configuration = wwise_configuration_option orelse .profile;

    const wwise_options = WwiseOptions{
        .wwise_sdk_path = getWwiseSDKPath(b, override_wwise_sdk_path_option),
        .configuration = wwise_configuration,
        .use_static_crt = wwise_use_static_crt_option orelse true,
        .use_communication = blk: {
            if (wwise_configuration == .release) {
                break :blk false;
            }

            break :blk wwise_use_communication_option orelse false;
        },
    };

    const wwise_c = b.addStaticLibrary(.{
        .name = "wwise-c",
        .target = target,
        .optimize = optimize,
    });
    wwise_c.addCSourceFile("bindings/WwiseC.cpp", &.{"-std=c++17"});
    try wwiseLink(wwise_c, wwise_options);
    wwise_c.linkLibC();

    if (target.getOsTag() == .windows) {
        wwise_c.defineCMacro("UNICODE", null);
    }

    if (wwise_options.use_communication) {
        wwise_c.defineCMacro("WWISEC_USE_COMMUNICATION", null);
    }

    const wwise_zig_module = b.addModule("wwise-zig", .{
        .source_file = .{
            .path = "src/wwise-zig.zig",
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
    try wwiseLink(wwise_test, wwise_options);
    wwise_test.linkLibrary(wwise_c);
    wwise_test.addModule("wwise-zig", wwise_zig_module);
    wwise_test.install();

    const run_test_cmd = wwise_test.run();
    run_test_cmd.step.dependOn(b.getInstallStep());

    const test_step = b.step("test", "Run library tests");
    test_step.dependOn(&run_test_cmd.step);

    const build_only_test_step = b.step("test_build_only", "Build the tests but does not run it");
    build_only_test_step.dependOn(&wwise_test.step);
    build_only_test_step.dependOn(b.getInstallStep());
}

fn wwiseLink(compile_step: *std.Build.CompileStep, wwise_options: WwiseOptions) !void {
    const wwise_library_relative_path = try getWwiseLibraryPath(compile_step.step.owner, compile_step.target, wwise_options);

    compile_step.addSystemIncludePath(compile_step.step.owner.pathJoin(&.{ wwise_options.wwise_sdk_path, "include" }));
    compile_step.addIncludePath("bindings");
    compile_step.addLibraryPath(compile_step.step.owner.pathJoin(&.{ wwise_options.wwise_sdk_path, wwise_library_relative_path }));

    if (wwise_options.use_communication) {
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

fn getWwiseLibraryPath(b: *std.Build, target: std.zig.CrossTarget, wwise_options: WwiseOptions) ![]const u8 {
    const config_string = switch (wwise_options.configuration) {
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

            const static_crt_string = if (wwise_options.use_static_crt) "(StaticCRT)" else "";

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
