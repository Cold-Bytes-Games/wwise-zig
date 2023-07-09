const wwise_options = @import("wwise_options");

pub const WwisePlatform = enum {
    android,
    ios,
    tvos,
    macos,
    linux,
    windows,
    xboxone,
    xboxseries,
    nintendo_switch,
    ps4,
    ps5,
};

pub const platform = wwise_options.platform;
