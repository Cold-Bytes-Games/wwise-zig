# wwise-zig - Zig and C bindings to Audiokinetic Wwise

Each major version of Wwise is contained within a branch. Select the correct branch and tag when importing the library with the package manager.

The library assumes that you installed Wwise using the Wwise Launcher. We do not distribute any binary from Audiokinetic.

## Usage

Available options:
| Option | Values | Description |
| -- | -- | -- |
| `override_wwise_sdk` | []const u8 | Override the path to the Wwise SDK, by default it will use the path in environment variable WWISESDK") |
| `configuration` | debug, profile, release | Which library configuration of Wwise to use |
| `use_static_crt` | bool | On Windows, do you want to use the StaticCRT build of Wwise |
| `use_communication` | bool | Enable remote communication with Wwise Authoring. Disabled by default on Release configuration so you can leave it true at all time |

## Supported platforms

| Platform | Architecture |  Tested |
| --       | --           | --      |
| Windows  | x86          | ✅      |
| Windows  | x86-64       | ✅      |
| Linux    | x86-64       | ✅      |
| Linux    | aarch64      | ❌      |
| Android  | arm64        | ❌      |
| Android  | arm          | ❌      |
| Android  | x86          | ❌      |
| Android  | x86-64       | ❌      |
| Mac      | x86-64       | ❌      |
| iOS      |              | ❌      |
| tvOS     |              | ❌      |

- On Windows, we always use the latest supported Visual Studio (currently 2022)
- UWP is gonna be deprecated so it is not supported
- No support for consoles yet

## License

See LICENSE for more info.