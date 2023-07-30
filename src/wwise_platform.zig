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

    pub fn getAuthoringPlatformName(self: WwisePlatform) [] const u8 {
         return switch (self) {
            .android => "Android",
            .ios => "iOS",
            .tvos => "iOS",
            .macos => "Mac",
            .linux => "Linux",
            .windows => "Windows",
            .xboxone => "XboxOne",
            .xboxseries => "XboxSeriesX",
            .nintendo_switch => "Switch",
            .ps4 => "PS4",
            .ps5 => "PS5",
        };
    }
};

pub const platform = wwise_options.platform;
