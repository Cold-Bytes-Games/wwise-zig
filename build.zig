const std = @import("std");
const builtin = @import("builtin");

const StaticPluginStep = @import("build/StaticPluginStep.zig");
const GenerateWwiseIDStep = @import("build/GenerateWwiseIDStep.zig");

const WwisePlatform = @import("src/wwise_platform.zig").WwisePlatform;

pub const WwiseConfiguration = enum {
    debug,
    profile,
    release,
};

pub const WwiseBuildOptions = struct {
    platform: WwisePlatform,
    wwise_sdk_path: []const u8,
    configuration: WwiseConfiguration,
    use_static_crt: bool,
    use_communication: bool,
    use_default_job_worker: bool,
    use_spatial_audio: bool,
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

const CppFlags: []const []const u8 = &.{ "-std=c++17", "-DUNICODE", "-Wall", "-Wpedantic", "-fno-sanitize=alignment" };

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    if (target.result.os.tag == .windows and target.result.abi == .gnu) {
        return error.GnuAbiNotSupported;
    }

    const override_wwise_sdk_path_option = b.option([]const u8, "wwise_sdk", "Override the path to the Wwise SDK, by default it will use the path in environment variable WWISESDK");
    const wwise_configuration_option = b.option(WwiseConfiguration, "configuration", "Which library of Wwise to use (Default: profile)");
    const wwise_use_static_crt_option = b.option(bool, "use_static_crt", "On Windows, use the static CRT version of the library (Default: true)");
    const wwise_use_communication_option = b.option(bool, "use_communication", "Enable remote communication with Wwise Authoring. Disabled by default on Release configuration so you can leave it true at all time (Default: true)");
    const wwise_use_default_job_worker_option = b.option(bool, "use_default_job_worker", "Enable usage of the default job worker given by Audiokinetic. (Default: false)");
    const wwise_use_spatial_audio_option = b.option(bool, "use_spatial_audio", "Enable usagee of the Spatial Audio module (Default: false)");
    const wwise_string_stack_size_option = b.option(usize, "string_stack_size", "Stack size to use for functions that accepts AkOsChar and null-terminated strings (Default: 256)");

    const wwise_include_default_io_hook_blocking_option = b.option(bool, "include_default_io_hook_blocking", "Include the Default IO Hook Blocking");
    const wwise_include_default_io_hook_deferred_option = b.option(bool, "include_default_io_hook_deferred", "Include the Default IO Hook Deferred");
    const wwise_include_file_package_io_blocking_option = b.option(bool, "include_file_package_io_blocking", "Include the File Package IO Hook Blocking");
    const wwise_include_file_package_io_deferred_option = b.option(bool, "include_file_package_io_deferred", "Include the File Package IO Hook Deferred");

    const wwise_static_plugins_option = b.option([]const []const u8, "static_plugins", "List of builtin static plugins to build");

    const wwise_configuration = wwise_configuration_option orelse .profile;

    const wwise_build_options = WwiseBuildOptions{
        .platform = try getWwisePlatform(target),
        .wwise_sdk_path = getWwiseSDKPath(b, override_wwise_sdk_path_option),
        .configuration = wwise_configuration,
        .use_static_crt = wwise_use_static_crt_option orelse true,
        .use_communication = blk: {
            if (wwise_configuration == .release) {
                break :blk false;
            }

            break :blk wwise_use_communication_option orelse true;
        },
        .use_default_job_worker = wwise_use_default_job_worker_option orelse false,
        .use_spatial_audio = wwise_use_spatial_audio_option orelse false,
        .include_default_io_hook_blocking = wwise_include_default_io_hook_blocking_option != null or wwise_include_file_package_io_blocking_option != null,
        .include_default_io_hook_deferred = wwise_include_default_io_hook_deferred_option != null or wwise_include_file_package_io_deferred_option != null,
        .include_file_package_io_blocking = wwise_include_file_package_io_blocking_option orelse false,
        .include_file_package_io_deferred = wwise_include_file_package_io_deferred_option orelse false,
        .string_stack_size = wwise_string_stack_size_option orelse 256,
        .static_plugins = wwise_static_plugins_option orelse &.{},
    };

    const wwise_c = b.addStaticLibrary(.{
        .name = "wwise-c",
        .target = target,
        .optimize = optimize,
    });
    wwise_c.addCSourceFile(.{
        .file = .{
            .path = thisDir() ++ "/bindings/WwiseC.cpp",
        },
        .flags = CppFlags,
    });
    wwise_c.addIncludePath(.{
        .path = thisDir() ++ "/bindings",
    });

    const static_plugin_step = StaticPluginStep.create(b, .{ .static_plugins = wwise_build_options.static_plugins });
    wwise_c.addCSourceFile(.{
        .file = .{
            .generated = &static_plugin_step.output_file,
        },
        .flags = CppFlags,
    });

    for (wwise_build_options.static_plugins) |static_plugin| {
        wwise_c.linkSystemLibrary(static_plugin);
    }

    try wwiseLinkModule(&wwise_c.root_module, wwise_build_options);
    wwise_c.linkLibC();
    if (target.result.os.tag != .windows) {
        wwise_c.linkLibCpp();
    }

    if (target.result.os.tag == .windows) {
        wwise_c.defineCMacro("UNICODE", null);
    }

    if (wwise_build_options.use_communication) {
        wwise_c.defineCMacro("WWISEC_USE_COMMUNICATION", null);
    }

    if (wwise_build_options.use_spatial_audio) {
        wwise_c.defineCMacro("WWISEC_USE_SPATIAL_AUDIO", null);
    }

    if (wwise_build_options.configuration == .release) {
        wwise_c.defineCMacro("AK_OPTIMIZED", null);
    }

    try handleDefaultWwiseSystems(wwise_c, wwise_build_options);

    const option_step = b.addOptions();
    option_step.addOption(usize, "string_stack_size", wwise_string_stack_size_option orelse 256);
    option_step.addOption(bool, "use_communication", wwise_build_options.use_communication);
    option_step.addOption(bool, "use_default_job_worker", wwise_build_options.use_default_job_worker);
    option_step.addOption(bool, "use_spatial_audio", wwise_build_options.use_spatial_audio);
    option_step.addOption(bool, "include_default_io_hook_blocking", wwise_build_options.include_default_io_hook_blocking);
    option_step.addOption(bool, "include_default_io_hook_deferred", wwise_build_options.include_default_io_hook_deferred);
    option_step.addOption(bool, "include_file_package_io_blocking", wwise_build_options.include_file_package_io_blocking);
    option_step.addOption(bool, "include_file_package_io_deferred", wwise_build_options.include_file_package_io_deferred);
    option_step.addOption(WwisePlatform, "platform", wwise_build_options.platform);

    const wwise_compile_options = option_step.createModule();

    const wwise_zig_module = b.addModule("wwise-zig", .{
        .root_source_file = .{
            .path = thisDir() ++ "/src/wwise-zig.zig",
        },
        .imports = &.{
            .{ .name = "wwise_options", .module = wwise_compile_options },
        },
        .target = target,
        .optimize = optimize,
    });

    wwise_zig_module.linkLibrary(wwise_c);
    try wwiseLinkModule(wwise_zig_module, wwise_build_options);

    const wwise_test = b.addTest(.{
        .name = "wwise_zig_test",
        .root_source_file = .{
            .path = thisDir() ++ "/tests/tests.zig",
        },
        .target = target,
        .optimize = optimize,
    });
    wwise_test.root_module.addImport("wwise-zig", wwise_zig_module);
    b.installArtifact(wwise_test);

    const run_test_cmd = b.addRunArtifact(wwise_test);
    run_test_cmd.step.dependOn(b.getInstallStep());

    const test_step = b.step("test", "Run library tests");
    test_step.dependOn(&run_test_cmd.step);

    const build_only_test_step = b.step("test_build_only", "Build the tests but does not run it");
    build_only_test_step.dependOn(&wwise_test.step);
    build_only_test_step.dependOn(b.getInstallStep());
}

fn wwiseLinkModule(module: *std.Build.Module, wwise_build_options: WwiseBuildOptions) !void {
    const wwise_library_relative_path = try getWwiseLibraryPath(module.owner, module.resolved_target.?, wwise_build_options);

    module.addSystemIncludePath(.{
        .path = module.owner.pathJoin(&.{ wwise_build_options.wwise_sdk_path, "include" }),
    });
    module.addIncludePath(.{
        .path = thisDir() ++ "/bindings",
    });
    module.addLibraryPath(.{
        .path = module.owner.pathJoin(&.{ wwise_build_options.wwise_sdk_path, wwise_library_relative_path }),
    });

    if (wwise_build_options.use_communication) {
        module.linkSystemLibrary("CommunicationCentral", .{ .needed = true });

        if (module.resolved_target) |target| {
            if (target.result.os.tag == .windows) {
                module.linkSystemLibrary("ws2_32", .{ .needed = true });
            }
        }
    }

    if (wwise_build_options.use_spatial_audio) {
        module.linkSystemLibrary("AkSpatialAudio", .{ .needed = true });
    }

    module.linkSystemLibrary("AkSoundEngine", .{ .needed = true });
    module.linkSystemLibrary("AkStreamMgr", .{ .needed = true });
    module.linkSystemLibrary("AkMemoryMgr", .{ .needed = true });
    module.linkSystemLibrary("AkMusicEngine", .{ .needed = true });

    if (module.resolved_target) |target| {
        if (target.result.os.tag == .windows) {
            module.linkSystemLibrary("user32", .{ .needed = true });
        }
    }
}

pub const GenerateSoundBanksArgs = struct {
    /// Override the path of the Wwise SDK, if not it will use the WWISESDK environment variable
    override_wwise_sdk_path: ?[]const u8 = null,
    /// Explicit list the platforms you want to generate the sound banks, if nothing specified, all the platforms will be generated
    platforms: []const WwisePlatform = &.{},
    /// Explicit list of the languages to generate, if not specified it will build all the languages
    languages: []const []const u8 = &.{},
    /// Instead of passing the platforms, you can use the target from Zig
    target: ?std.Build.ResolvedTarget = null,
    /// Output folder of the sound banks, will use the default in the project if omitted
    output_folder: ?[]const u8 = null,
    /// List of sound banks to generate, if not specified it will build all the sound banks
    sound_banks: []const []const u8 = &.{},
    /// Overrides the root output path specified in the soundbank settings.
    root_output_path: ?[]const u8 = null,
};

pub fn addGenerateSoundBanksStep(b: *std.Build, wwise_project_path: []const u8, args: GenerateSoundBanksArgs) !*std.Build.Step.Run {
    var arg_list = std.ArrayList([]const u8).init(b.allocator);
    defer arg_list.deinit();

    const absolute_wwise_project_path = b.pathFromRoot(wwise_project_path);

    const wwise_sdk_path = getWwiseSDKPath(b, args.override_wwise_sdk_path);

    const application_name = switch (builtin.os.tag) {
        .windows => "WwiseConsole.exe",
        else => "WwiseConsole",
    };

    const wwise_console_path = try std.fs.path.resolve(b.allocator, &.{ wwise_sdk_path, "..", "Authoring", "x64", "Release", "bin", application_name });

    try arg_list.append(wwise_console_path);
    try arg_list.append("generate-soundbank");
    try arg_list.append(absolute_wwise_project_path);

    if (args.target) |target| {
        const wwise_platform = try getWwisePlatform(target);

        try arg_list.append("--platform");
        try arg_list.append(b.fmt("{s}", .{wwise_platform.getAuthoringPlatformName()}));
    }

    for (args.platforms) |platform| {
        try arg_list.append("--platform");
        try arg_list.append(b.fmt("{s}", .{platform.getAuthoringPlatformName()}));
    }

    for (args.languages) |language| {
        try arg_list.append("--language");
        try arg_list.append(b.fmt("{s}", .{language}));
    }

    if (args.output_folder) |output_folder| {
        try arg_list.append("--output");
        try arg_list.append(b.fmt("{s}", .{output_folder}));
    }

    for (args.sound_banks) |sound_bank| {
        try arg_list.append("--bank");
        try arg_list.append(b.fmt("{s}", .{sound_bank}));
    }

    if (args.root_output_path) |root_output_path| {
        try arg_list.append("--root-output-path");
        try arg_list.append(b.fmt("{s}", .{root_output_path}));
    }

    const run_step = b.addSystemCommand(arg_list.items);
    run_step.step.name = "Generate Wwise Sound Banks";
    run_step.extra_file_dependencies = &.{absolute_wwise_project_path};
    return run_step;
}

pub const GenerateWwiseIDModuleOptions = struct {
    /// Add a dependency to any step, such as generate sound banks
    previous_step: ?*std.Build.Step = null,
};

pub fn generateWwiseIDModule(b: *std.Build, wwise_id_file_path: []const u8, wwise_zig_module: *std.Build.Module, options: GenerateWwiseIDModuleOptions) *std.Build.Module {
    const generate_id_module_step = GenerateWwiseIDStep.create(b, .{
        .id_file_path = wwise_id_file_path,
    });

    if (options.previous_step) |previous_step| {
        generate_id_module_step.step.dependOn(previous_step);
    }

    const id_module = b.createModule(.{
        .root_source_file = .{
            .generated = &generate_id_module_step.output_file,
        },
        .imports = &.{
            .{ .name = "wwise-zig", .module = wwise_zig_module },
        },
    });

    return id_module;
}

fn getWwiseSDKPath(b: *std.Build, override_wwise_sdk_path_opt: ?[]const u8) []const u8 {
    if (override_wwise_sdk_path_opt) |wwise_sdk_path| {
        if (wwise_sdk_path.len > 0) {
            return wwise_sdk_path;
        }
    }

    if (b.graph.env_map.get("WWISESDK")) |wwise_sdk_path| {
        return wwise_sdk_path;
    }

    return "";
}

fn getWwisePlatform(target: std.Build.ResolvedTarget) !WwisePlatform {
    return switch (target.result.os.tag) {
        .windows => .windows,
        .linux => if (target.result.abi == .android) .android else .linux,
        .macos => .macos,
        .ios => .ios,
        .tvos => .tvos,
        else => error.OsNotSupported,
    };
}

fn getWwiseLibraryPath(b: *std.Build, target: std.Build.ResolvedTarget, wwise_build_options: WwiseBuildOptions) ![]const u8 {
    const config_string = switch (wwise_build_options.configuration) {
        .debug => "Debug",
        .profile => "Profile",
        .release => "Release",
    };

    switch (wwise_build_options.platform) {
        .windows => {
            const arch_string = switch (target.result.cpu.arch) {
                .x86 => "Win32",
                .x86_64 => "x64",
                else => return error.ArchNotSupported,
            };

            const static_crt_string = if (wwise_build_options.use_static_crt) "(StaticCRT)" else "";

            return b.fmt("{s}_vc170/{s}{s}/lib", .{ arch_string, config_string, static_crt_string });
        },
        .android => {
            const arch_string = switch (target.result.cpu.arch) {
                .aarch64 => "arm64-v8a",
                .arm => "armeabi-v7a",
                .x86 => "x86",
                .x86_64 => "x86_64",
                else => return error.ArchNotSupported,
            };

            return b.fmt("Android_{s}/{s}/lib", .{ arch_string, config_string });
        },
        .linux => {
            const arch_string = switch (target.result.cpu.arch) {
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
            const abi_string = switch (target.result.abi) {
                .simulator => "iphonesimulator",
                else => "iphoneos",
            };

            return b.fmt("iOS/{s}-{s}/lib", .{ config_string, abi_string });
        },
        .tvos => {
            const abi_string = switch (target.result.abi) {
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

fn handleDefaultWwiseSystems(compile_step: *std.Build.Step.Compile, wwise_build_options: WwiseBuildOptions) !void {
    if (!wwise_build_options.useDefaultIoHooks() and !wwise_build_options.use_default_job_worker) {
        return;
    }

    const platform_name = switch (wwise_build_options.platform) {
        .windows => "Win32",
        .android => "Android",
        .linux, .macos, .ios, .tvos => "POSIX",
        else => return error.OsNotSupported,
    };

    compile_step.addIncludePath(.{
        .path = compile_step.step.owner.fmt("{s}/samples/SoundEngine/Common", .{wwise_build_options.wwise_sdk_path}),
    });
    compile_step.addIncludePath(.{
        .path = compile_step.step.owner.fmt("{s}/samples/SoundEngine/{s}", .{ wwise_build_options.wwise_sdk_path, platform_name }),
    });

    if (wwise_build_options.useDefaultIoHooks()) {
        compile_step.addCSourceFile(.{
            .file = .{
                .path = compile_step.step.owner.fmt("{s}/samples/SoundEngine/Common/AkMultipleFileLocation.cpp", .{wwise_build_options.wwise_sdk_path}),
            },
            .flags = CppFlags,
        });
        compile_step.addCSourceFile(.{
            .file = .{
                .path = compile_step.step.owner.fmt("{s}/samples/SoundEngine/Common/AkGeneratedSoundBanksResolver.cpp", .{wwise_build_options.wwise_sdk_path}),
            },
            .flags = CppFlags,
        });
    }

    if (wwise_build_options.include_default_io_hook_blocking) {
        compile_step.defineCMacro("WWISEC_INCLUDE_DEFAULT_IO_HOOK_BLOCKING", null);
        compile_step.addCSourceFile(.{
            .file = .{
                .path = compile_step.step.owner.fmt("{s}/samples/SoundEngine/{s}/AkDefaultIOHookBlocking.cpp", .{ wwise_build_options.wwise_sdk_path, platform_name }),
            },
            .flags = CppFlags,
        });
    }

    if (wwise_build_options.include_default_io_hook_deferred) {
        compile_step.defineCMacro("WWISEC_INCLUDE_DEFAULT_IO_HOOK_DEFERRED", null);
        compile_step.addCSourceFile(.{
            .file = .{ .path = compile_step.step.owner.fmt("{s}/samples/SoundEngine/{s}/AkDefaultIOHookDeferred.cpp", .{ wwise_build_options.wwise_sdk_path, platform_name }) },
            .flags = CppFlags,
        });
    }

    if (wwise_build_options.include_file_package_io_blocking) {
        compile_step.defineCMacro("WWISEC_INCLUDE_FILE_PACKAGE_IO_BLOCKING", null);
    }

    if (wwise_build_options.include_file_package_io_deferred) {
        compile_step.defineCMacro("WWISEC_INCLUDE_FILE_PACKAGE_IO_DEFERRED", null);
    }

    if (wwise_build_options.use_default_job_worker) {
        compile_step.defineCMacro("WWISEC_USE_DEFAULT_JOB_WORKER", null);
        compile_step.addCSourceFile(.{
            .file = .{
                .path = compile_step.step.owner.fmt("{s}/samples/SoundEngine/Common/AkJobWorkerMgr.cpp", .{wwise_build_options.wwise_sdk_path}),
            },
            .flags = CppFlags,
        });
    }

    if (wwise_build_options.useFilePackageIO()) {
        compile_step.addCSourceFile(.{
            .file = .{
                .path = compile_step.step.owner.fmt("{s}/samples/SoundEngine/Common/AkFilePackage.cpp", .{wwise_build_options.wwise_sdk_path}),
            },
            .flags = CppFlags,
        });
        compile_step.addCSourceFile(.{
            .file = .{
                .path = compile_step.step.owner.fmt("{s}/samples/SoundEngine/Common/AkFilePackageLUT.cpp", .{wwise_build_options.wwise_sdk_path}),
            },
            .flags = CppFlags,
        });
    }
}

inline fn thisDir() []const u8 {
    return comptime std.fs.path.dirname(@src().file) orelse ".";
}
