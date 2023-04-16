# wwise-zig - Zig bindings to Audiokinetic Wwise

This package implement a native [Zig](https://ziglang.org/) binding for [Audiokinetic Wwise](https://www.audiokinetic.com/en/products/wwise). The included C binding is designed only to be used by the Zig binding. If you want to expand the C binding to be fully functional please submit any pull requests.

Each function name has been renamed to fit the Zig coding style. It should be easy to map to the [Wwise SDK documentation](https://www.audiokinetic.com/en/library/edge/?source=SDK&id=index.html).

Each major version of Wwise is contained within a branch. Select the correct branch and tag when importing the library with the Zig package manager.

The library assumes that you installed Wwise using the Wwise Launcher. We do not distribute any binary from Audiokinetic.

This is a 3rd party binding and it is not affiliated with Audiokinetic.

## Usage

Available options:
| Option | Values | Description |
| -- | -- | -- |
| `override_wwise_sdk` | []const u8 | Override the path to the Wwise SDK, by default it will use the path in environment variable WWISESDK") |
| `configuration` | debug, profile, release | Which library configuration of Wwise to use |
| `use_static_crt` | bool | On Windows, do you want to use the StaticCRT build of Wwise |
| `use_communication` | bool | Enable remote communication with Wwise Authoring. Disabled by default on Release configuration so you can leave it true at all time |
| `string_stack_size` | usize | Stack size to use for functions that accepts AkOsChar and null-terminated strings (Default 512) |

We recommend using `AK` as your import name to match closely with the C++ API.

```zig
const AK = @import("wwise-zig);

pub fn main() !void {
    var memory_settings: AK.AkMemSettings = undefined;
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();
}
```

### Handling AkOsChar and null-terminated strings

`wwise-zig` is trying to save allocations by using stack-allocated space to convert to AkOsChar or null-terminated strings and use a fallback allocator if the string is bigger than the stack size.

You can customize the size allocated by modifying the `string_stack_size` when importing the dependency.

Each function that handle string looks similar to this: 
```zig
pub fn dumpToFile(fallback_allocator: std.mem.Allocator, filename: []const u8) !void {
    var os_string_allocator = common.osCharAllocator(fallback_allocator);
    var allocator = os_string_allocator.get();

    const filename_oschar = try common.toOSChar(allocator, filename);
    defer allocator.free(filename_oschar);

    c.WWISEC_AK_MemoryMgr_DumpToFile(filename_oschar);
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
- UWP is gonna be deprecated so it is not supported
- No support for consoles yet

## License

See LICENSE for more info.