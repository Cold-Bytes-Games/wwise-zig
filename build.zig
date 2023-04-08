const std = @import("std");

pub const WwiseConfiguration = enum {
    debug,
    profile,
    release,
};

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const override_wwise_sdk_path_option = b.option([]const u8, "override_wwise_sdk", "Override the path to the Wwise SDK, by default it will use the path in environment variable WWISESDK");
    const wwise_configuration_option = b.option(WwiseConfiguration, "configuration", "Which library of Wwise to use");
    const wwise_use_static_crt_option = b.option(bool, "use_static_crt", "On Windows, use the static CRT version of the library");
    const wwise_use_communication_option = b.option(bool, "use_communication", "Enable remote communication with Wwise Authoring. Disabled by default on Release configuration so you can leave it true at all time");

    const wwise_configuration = wwise_configuration_option orelse .profile;
    const wwise_use_static_crt = wwise_use_static_crt_option orelse true;
    const wwise_sdk_path = getWwiseSDKPath(b, override_wwise_sdk_path_option);
    const wwise_library_relative_path = try getWwiseLibraryPath(b, target, wwise_configuration, wwise_use_static_crt);
    const wwise_use_communication = blk: {
        if (wwise_configuration == .release) {
            break :blk false;
        }

        break :blk wwise_use_communication_option orelse false;
    };

    const wwise_c = b.addStaticLibrary(.{
        .name = "wwise-c",
        .target = target,
        .optimize = optimize,
    });
    wwise_c.addCSourceFile("bindings/WwiseC.cpp", &.{"-std=c++17"});
    wwise_c.addSystemIncludePath(b.pathJoin(&.{ wwise_sdk_path, "include" }));
    wwise_c.addLibraryPath(b.pathJoin(&.{ wwise_sdk_path, wwise_library_relative_path }));
    wwise_c.linkLibC();

    if (target.getOsTag() == .windows) {
        wwise_c.defineCMacro("UNICODE", null);
    }

    if (wwise_use_communication) {
        wwise_c.defineCMacro("WWISEC_USE_COMMUNICATION", null);
        wwise_c.linkSystemLibrary("CommunicationCentral");

        if (target.getOsTag() == .windows) {
            wwise_c.linkSystemLibrary("ws2_32");
        }
    }

    _ = b.addModule("wwise-zig", .{
        .source_file = .{
            .path = "src/wwise_zig.zig",
        },
    });
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

fn getWwiseLibraryPath(b: *std.Build, target: std.zig.CrossTarget, configuration: WwiseConfiguration, use_static_crt: bool) ![]const u8 {
    const config_string = switch (configuration) {
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

            const static_crt_string = if (use_static_crt) "(StaticCRT)" else "";

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
