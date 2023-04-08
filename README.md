# wwise-zig - Zig and C bindings to Audiokinetic Wwise

This package implement a native [Zig](https://ziglang.org/) binding for [Audiokinetic Wwise](https://www.audiokinetic.com/en/products/wwise). It also include a pure C binding.

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