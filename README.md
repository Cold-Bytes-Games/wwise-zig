# wwise-zig - Zig bindings to Audiokinetic Wwise

This package implement a native [Zig](https://ziglang.org/) binding for [Audiokinetic Wwise](https://www.audiokinetic.com/en/products/wwise). The included C binding is designed only to be used by the Zig binding. If you want to expand the C binding to be fully functional please submit any pull requests.

Each function name, structs and enums has been renamed to fit the Zig coding style. It should be easy to map to the [Wwise SDK documentation](https://www.audiokinetic.com/en/library/edge/?source=SDK&id=index.html).

Each major version of Wwise is contained within a branch. Select the correct branch and tag when importing the library with the Zig package manager.

The library assumes that you installed Wwise using the Wwise Launcher. We do not distribute any binary from Audiokinetic.

This is a 3rd party binding and it is not affiliated with Audiokinetic.

## Usage

Available options:
| Option | Values | Description |
| -- | -- | -- |
| `wwise_sdk` | `[]const u8` | Override the path to the Wwise SDK, by default it will use the path in environment variable WWISESDK |
| `configuration` | debug, profile, release | Which library configuration of Wwise to use |
| `use_static_crt` | `bool` | On Windows, do you want to use the StaticCRT build of Wwise |
| `use_communication` | `bool` | Enable remote communication with Wwise Authoring. Disabled by default on Release configuration so you can leave it true at all time |
| `string_stack_size` | `usize` | Stack size to use for functions that accepts AkOsChar and null-terminated strings (Default 512) |
| `include_default_io_hook_blocking` | `bool` | Include the Default IO Hook Blocking |
| `include_default_io_hook_deferred` | `bool` | Include the Default IO Hook Deferred |
| `include_file_package_io_blocking` | `bool` | Include the File Package IO Hook Blocking |
| `include_file_package_io_deferred` | `bool` | Include the File Package IO Hook Deferred |

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

### Handling AkOsChar and C null-terminated strings

`wwise-zig` is trying to save allocations when calling functions that accepts strings by using stack-allocated space to convert to `const AkOsChar*`/`const char*` or use a fallback allocator if the string is bigger than the stack size.

You can customize the size allocated by modifying the `string_stack_size` when importing the dependency.

Each function that handle strings looks similar to this: 
```zig
pub fn dumpToFile(fallback_allocator: std.mem.Allocator, filename: []const u8) !void {
    var os_string_allocator = common.osCharAllocator(fallback_allocator);
    var allocator = os_string_allocator.get();

    const filename_oschar = try common.toOSChar(allocator, filename);
    defer allocator.free(filename_oschar);

    c.WWISEC_AK_MemoryMgr_DumpToFile(filename_oschar);
}
```

### Handling C++ interfaces and inheritance

TODO

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

## Supported platforms

| Platform | Architecture           |  Tested |
| --       | --                     | --      |
| Windows  | x86 (msvc ABI only)    | ✅      |
| Windows  | x86-64 (msvc ABI only) | ✅      |
| Linux    | x86-64                 | ✅      |
| Linux    | aarch64                | ❌      |
| Android  | arm64                  | ❌      |
| Android  | arm                    | ❌      |
| Android  | x86                    | ❌      |
| Android  | x86-64                 | ❌      |
| Mac      | x86-64                 | ❌      |
| iOS      |                        | ❌      |
| tvOS     |                        | ❌      |

- On Windows, the default GNU ABI is not supported, always use MSVC ABI
- On Windows, we always use the latest supported Visual Studio (currently 2022)
- On Linux, the default I/O hooks are currently not supported (see #1)
- UWP is gonna be deprecated so it is not supported
- No support for consoles yet

## Versioning info

This binding mimic the versioning of Wwise but add the Zig binding version at the end.

Example:

2022.1.4-zig0

* 2022 = year
* 1 = major Wwise version
* 4 = minor Wwise version
* -zig0 = Zig binding version

## License

See LICENSE for more info.