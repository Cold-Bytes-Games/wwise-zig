# wwise-zig - Zig bindings to Audiokinetic Wwise (2022.1.10)

This package implement a native [Zig](https://ziglang.org/) binding for [Audiokinetic Wwise](https://www.audiokinetic.com/en/products/wwise). The included C binding is designed only to be used by the Zig binding. If you want to expand the C binding to be fully functional please submit any pull requests.

Each function name, structs and enums has been renamed to fit the Zig coding style. It should be easy to map to the [Wwise SDK documentation](https://www.audiokinetic.com/en/library/edge/?source=SDK&id=index.html).

Each major version of Wwise is contained within a branch. Select the correct branch and tag when importing the library with the Zig package manager.

The library assumes that you installed Wwise using the Wwise Launcher. We do not distribute any binary from Audiokinetic.

This is a 3rd party binding and it is not affiliated with Audiokinetic.

[![Join our Discord!](https://discordapp.com/api/guilds/1161009516771549374/widget.png?style=banner2)](https://discord.gg/jMxttNCBys)

## Zig version

This library uses zig nominated [2024.3.0-mach](https://machengine.org/about/nominated-zig/). To install using [`zigup`](https://github.com/marler8997/zigup):

```sh
zigup 0.12.0-dev.3180+83e578a18
```

## Versioning info

This binding mimic the versioning of Wwise but add the Zig binding version at the end.

Example:

2022.1.9-zig0

* 2022 = year
* 1 = major Wwise version
* 9 = minor Wwise version
* -zig0 = Zig binding version

## Supported platforms

| Platform | Architecture                   |  Tested |
| --       | --                             | --      |
| Windows  | x86 (msvc ABI only)            | ❌      |
| Windows  | x86-64 (msvc ABI only)         | ✅      |
| Linux    | x86-64                         | ✅      |
| Linux    | aarch64                        | ❌      |
| Android  | arm64                          | ❌      |
| Android  | arm                            | ❌      |
| Android  | x86                            | ❌      |
| Android  | x86-64                         | ❌      |
| Mac      | Universal (x86-64 and aarch64) | ❌      |
| iOS      |                                | ❌      |
| tvOS     |                                | ❌      |

- On Windows, the default GNU ABI is not supported, always use the MSVC ABI
- On Windows, we always use the latest supported Visual Studio (currently 2022)
- On Linux, the default I/O hooks are currently not supported (see #1)
- UWP is gonna be deprecated so it is not supported
- No support for consoles yet

## Import it in your project

1. Add this repo in your `build.zig.zon` file, you'll need to add the hash and update the commit hash to the latest commit in the branch
```zig
.@"wwise-zig" = .{
    .url = "https://github.com/Cold-Bytes-Games/wwise-zig/archive/90cdc6877369b55af3ee2dfcf091dc547ed59f03.tar.gz",
    .hash = "122053d2ec67ebe8a47b45ac32ddf41283b27c3519196b6730d9b826a463d1294299",
},
```
2. Import the dependency in your `build.zig`. See the Usage section for the list of available options.

```zig
const std = @import("std");
const wwise_zig = @import("wwise-zig");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const wwise_dependency = b.dependency("wwise-zig", .{
        .target = target,
        .optimize = optimize,
        .use_communication = true,
        .use_default_job_worker = true,
        .use_spatial_audio = true,
        .use_static_crt = true,
        .include_file_package_io_blocking = true,
        .configuration = .profile,
        .static_plugins = @as([]const []const u8, &.{
            "AkToneSource",
            "AkParametricEQFX",
            "AkDelayFX",
            "AkPeakLimiterFX",
            "AkRoomVerbFX",
            "AkStereoDelayFX",
            "AkSynthOneSource",
            "AkAudioInputSource",
            "AkVorbisDecoder",
        }),
    });

    const exe = b.addExecutable(.{
        .name = "wwise-zig-demo",
        .root_source_file = .{ .path = "src/main.zig" },
        .target = target,
        .optimize = optimize,
    });

    exe.root_module.addImport("wwise-zig", wwise_dependency.module("wwise-zig"));
}
```

## Usage

Available options:
| Option | Values | Description |
| -- | -- | -- |
| `wwise_sdk` | `[]const u8` | Override the path to the Wwise SDK, by default it will use the path in environment variable WWISESDK |
| `configuration` | debug, profile, release | Which library configuration of Wwise to use (Default: profile) |
| `use_static_crt` | `bool` | On Windows, do you want to use the StaticCRT build of Wwise (Default: true) |
| `use_communication` | `bool` | Enable remote communication with Wwise Authoring. Disabled by default on Release configuration so you can leave it true at all time (Default: true) |
| `use_default_job_worker` | `bool` | Enable usage of the default job worker given by Audiokinetic. (Default: false) |
| `use_spatial_audio` | `bool` | Enable usagee of the Spatial Audio module (Default: false) |
| `string_stack_size` | `usize` | Stack size to use for functions that accepts AkOsChar and null-terminated strings (Default: 256) |
| `include_default_io_hook_blocking` | `bool` | Include the Default IO Hook Blocking (Default: false) |
| `include_default_io_hook_deferred` | `bool` | Include the Default IO Hook Deferred (Default: false) |
| `include_file_package_io_blocking` | `bool` | Include the File Package IO Hook Blocking (Default: false) |
| `include_file_package_io_deferred` | `bool` | Include the File Package IO Hook Deferred (Default: false) |
| `static_plugins` | []const []const u8 | List of static plugins to link to (Default: empty) |

We recommend using `AK` as your import name to match closely with the C++ API.

```zig
const AK = @import("wwise-zig");

pub fn main() !void {
    var memory_settings: AK.AkMemSettings = undefined;
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();
}
```

You can also look at the Integration Demo ported to Zig here for how the API is used in a sample application: https://github.com/Cold-Bytes-Games/wwise-zig-demo

### Handling AkOsChar and C null-terminated strings

`wwise-zig` is trying to save allocations when calling functions that accepts strings by using stack-allocated space to convert to `const AkOsChar*`/`const char*` or use a fallback allocator if the string is bigger than the stack size.

You can customize the size allocated by modifying the `string_stack_size` when importing the dependency.

Each function that handle strings looks similar to this: 
```zig
pub fn dumpToFile(fallback_allocator: std.mem.Allocator, filename: []const u8) !void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const filename_oschar = try common.toOSChar(allocator, filename);
    defer allocator.free(filename_oschar);

    c.WWISEC_AK_MemoryMgr_DumpToFile(filename_oschar);
}
```

### Handling C++ inheritance

You can create derivated Zig struct from Wwise C++ clases that have virtual methods. Each binded class has a `FunctionTable` object like `IAkIOHookDeferredBatch` here:

```zig
pub const IAkIOHookDeferredBatch = opaque {
    pub const FunctionTable = extern struct {
        destructor: *const fn (self: *IAkIOHookBlocking) callconv(.C) void,
        close: *const fn (self: *IAkIOHookBlocking, in_file_desc: *AkFileDesc) callconv(.C) common.AKRESULT,
        get_block_size: *const fn (self: *IAkIOHookBlocking, in_file_desc: *AkFileDesc) callconv(.C) u32,
        get_device_desc: *const fn (self: *IAkIOHookBlocking, out_device_desc: *stream_interfaces.NativeAkDeviceDesc) callconv(.C) void,
        get_device_data: *const fn (self: *IAkIOHookBlocking) callconv(.C) u32,
        batch_read: *const fn (
            self: *IAkIOHookDeferredBatch,
            in_num_transfers: u32,
            in_transfer_items: [*]BatchIoTransferItem,
            in_batch_io_callback: AkBatchIOCallback,
            io_dispatch_results: [*]common.AKRESULT,
        ) callconv(.C) common.AKRESULT,
        batch_write: *const fn (
            self: *IAkIOHookDeferredBatch,
            in_num_transfers: u32,
            in_transfer_items: [*]BatchIoTransferItem,
            in_batch_io_callback: AkBatchIOCallback,
            io_dispatch_results: [*]common.AKRESULT,
        ) callconv(.C) common.AKRESULT,
        batch_cancel: *const fn (
            self: *IAkIOHookDeferredBatch,
            in_num_transfers: u32,
            in_transfer_items: [*]BatchIoTransferItem,
            io_cancel_all_transfers_for_this_file: [*]*bool,
        ) callconv(.C) void,
    };
}
```
On the glue side, we inherit from the interface and call those functions with the instance of your Zig struct.

Each class has a method `createInstance()` and `destroyInstance` that are used to create an instance of your own derivated struct. It uses AK memory manager function to allocate the instance with the `AkMemID_Integration` memory tag.

```zig
var zig_io_blocking = ZigTestIAkOHookBlocking{};
var native_io_blocking = AK.StreamMgr.IAkIOHookBlocking.createInstance(
            &zig_io_blocking,
            &AK.StreamMgr.IAkIOHookBlocking.FunctionTable{
                .destructor = @ptrCast(&ZigTestIAkOHookBlocking.destructor),
                .close = @ptrCast(&ZigTestIAkOHookBlocking.close),
                .get_block_size = @ptrCast(&ZigTestIAkOHookBlocking.getBlockSize),
                .get_device_desc = @ptrCast(&ZigTestIAkOHookBlocking.getDeviceDesc),
                .get_device_data = @ptrCast(&ZigTestIAkOHookBlocking.getDeviceData),
                .read = @ptrCast(&read),
                .write = @ptrCast(&write),
            },
        );
defer AK.StreamMgr.IAkIOHookBlocking.destroyInstance(native_io_blocking);
```

However we recommend creating a helper function in your struct to create the correct instance with the function table properly filled.

Here's a quick sample of a derivated `IAkOHookBlocking` struct from our test suite:
```zig
const ZigTestIAkOHookBlocking = struct {
    destructor_called: bool = false,
    close_called: bool = false,
    get_block_size_called: bool = false,
    get_device_desc_called: bool = false,
    get_device_data_called: bool = false,
    read_called: bool = false,
    write_called: bool = false,
    close_size: i64 = 0,

    pub fn destructor(self: *ZigTestIAkOHookBlocking) callconv(.C) void {
        self.destructor_called = true;
    }

    pub fn close(self: *ZigTestIAkOHookBlocking, in_file_desc: *AK.StreamMgr.AkFileDesc) callconv(.C) AK.AKRESULT {
        self.close_size = in_file_desc.file_size;
        self.close_called = true;

        return .success;
    }

    pub fn getBlockSize(self: *ZigTestIAkOHookBlocking, in_file_desc: *AK.StreamMgr.AkFileDesc) callconv(.C) u32 {
        _ = in_file_desc;
        self.get_block_size_called = true;
        return 512;
    }

    pub fn getDeviceDesc(self: *ZigTestIAkOHookBlocking, out_device_desc: *AK.NativeAkDeviceDesc) callconv(.C) void {
        self.get_device_desc_called = true;

        var zig_device_desc = AK.AkDeviceDesc{};
        zig_device_desc.can_write = false;
        zig_device_desc.can_read = true;
        zig_device_desc.device_name = "wwise-zig IO";

        out_device_desc.* = zig_device_desc.toC() catch unreachable;
    }

    pub fn getDeviceData(self: *ZigTestIAkOHookBlocking) callconv(.C) u32 {
        self.get_device_data_called = true;
        return 4269;
    }

    pub fn read(self: *ZigTestIAkOHookBlocking, in_file_desc: *AK.StreamMgr.AkFileDesc, in_heuristics: *AK.StreamMgr.AkIoHeuristics, out_buffer: ?*anyopaque, in_transfer_info: *AK.StreamMgr.AkIOTransferInfo) callconv(.C) AK.AKRESULT {
        _ = in_file_desc;
        _ = in_heuristics;

        self.read_called = true;

        if (out_buffer) |checked_buffer| {
            var read_buffer = @as([*]u8, @ptrCast(checked_buffer));
            @memset(read_buffer[in_transfer_info.file_position..in_transfer_info.requested_size], 0xC1);
        }

        return .success;
    }

    pub fn write(self: *ZigTestIAkOHookBlocking, in_file_desc: *AK.StreamMgr.AkFileDesc, in_heuristics: *AK.StreamMgr.AkIoHeuristics, in_data: ?*anyopaque, in_transfer_info: *AK.StreamMgr.AkIOTransferInfo) callconv(.C) AK.AKRESULT {
        _ = in_heuristics;
        _ = in_transfer_info;
        _ = in_data;
        _ = in_file_desc;

        self.write_called = true;

        return .success;
    }

    pub fn createIAkIOHookBlocking(self: *ZigTestIAkOHookBlocking) *AK.StreamMgr.IAkIOHookBlocking {
        return AK.StreamMgr.IAkIOHookBlocking.createInstance(
            self,
            &AK.StreamMgr.IAkIOHookBlocking.FunctionTable{
                .destructor = @ptrCast(&destructor),
                .close = @ptrCast(&close),
                .get_block_size = @ptrCast(&getBlockSize),
                .get_device_desc = @ptrCast(&getDeviceDesc),
                .get_device_data = @ptrCast(&getDeviceData),
                .read = @ptrCast(&read),
                .write = @ptrCast(&write),
            },
        );
    }
};
```

### Use the default I/O hook(s) from the SDK

First you need to include at least one I/O hook in the build options.

All the default I/O are included in the IOHooks namespace from the `wwise-zig` package.

Use the `create` and `destroy` function with a Zig allocator to create a instance of the I/O hook.

After that, you need to call `init` and `setBasePath` like in C++

```zig
const std = @import("std");
const AK = @import("wwise-zig");

pub fn main() !void {
    var io_hook = try AK.IOHooks.CAkFilePackageLowLevelIODeferred.create(std.testing.allocator);
    defer io_hook.destroy(std.testing.allocator);

    try io_hook.init(device_settings, false);
    defer io_hook.term();

    try io_hook.setBasePath(std.testing.allocator, ".");

    const loaded_package_id = try io_hook.loadFilePackage(std.testing.allocator, "MyWwiseData.pck");
}
```

### Generate the Sound Banks with the Zig build system

We are bundling a build step to generate the sound banks. To use it:
1. Include the wwise-zig dependency in youtr `build.zig.zon` file.
1. Import the wwise-zig module in your `build.zig`.
1. Call `addGenerateSooundBanksStep()` and pass the `std.Build` instance and some optioons.
1. After that, it is recommended that you add the generate sound banks steps as a dependency of your compile step.

Options available:
| Option | Values | Description |
| -- | -- | -- |
| `override_wwise_sdk_path` | `[]const u8` | Override the path of the Wwise SDK, if not it will use the WWISESDK environment variable |
| `platforms` | ` []const WwisePlatform` | Explicit list the platforms you want to generate the sound banks, if nothing specified, all the platforms will be generated |
| `languages` | `[]const []const u8` | Explicit list of the languages to generate, if not specified it will build all the languages |
| `target` | `std.zig.CrossTarget` | Instead of passing the platforms, you can use the target from Zig |
| `output_folder` | `[]const u8` | Output folder of the sound banks, will use the default in the project if omitted |
| `sound_banks` | `[]const []const u8` | List of sound banks to generate, if not specified it will build all the sound banks |
| `root_output_path` | `[]const u8` | Overrides the root output path specified in the soundbank settings|

Example:
```zig
const std = @import("std");
const wwise_zig = @import("wwise-zig");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const build_soundbanks_step = try wwise_zig.addGenerateSoundBanksStep(b, "WwiseProject/IntegrationDemo.wproj", .{
        .target = target,
    });

     const exe = b.addExecutable(.{
        .name = "wwise-zig-demo",
        .root_source_file = .{ .path = "src/main.zig" },
        .target = target,
        .optimize = optimize,
    });
    exe.step.dependOn(&build_soundbanks_step.step);

    // [...]
}
```

### Generate a zig module with Wwise ID

If specified in the Wwise project settings, you can generate a C header file that contains all the unique ID of your events, soundbanks, states, switch, game parameters. We include a way to parse that header file and generate a Zig module on the fly.

You need to pass the main `wwise-zig` module to the function because we use `AkUniqueID` from the main module.

It is recommended that you add a dependency to the generated sound banks step if you use it in your `build.zig` file.

```zig
const std = @import("std");
const wwise_zig = @import("wwise-zig");

pub fn build(b: *std.Build) !void {
    // [...]
     const wwise_id_module = wwise_zig.generateWwiseIDModule(b, "WwiseProject/GeneratedSoundBanks/Wwise_IDs.h", wwise_package.module, .{
        .previous_step = &build_soundbanks_step.step,
    });

    exe.addModule("wwise-ids", wwise_id_module);
```

## License

See LICENSE for more info.