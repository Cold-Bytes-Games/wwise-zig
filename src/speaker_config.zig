const std = @import("std");

// NOTE: Please sync this with the defines in AkSpeakerConfig.h
pub const AkSpeakerSetup = packed struct(u20) {
    front_left: bool = false,
    front_right: bool = false,
    front_center: bool = false,
    low_frequency: bool = false,
    back_left: bool = false,
    back_right: bool = false,
    padded1: u2 = 0,
    back_center: bool = false,
    side_left: bool = false,
    side_right: bool = false,
    height_top: bool = false,
    height_front_left: bool = false,
    height_front_center: bool = false,
    height_front_right: bool = false,
    height_back_left: bool = false,
    height_back_center: bool = false,
    height_back_right: bool = false,
    padded2: u2 = 0,

    pub const @"0.1" = AkSpeakerSetup{
        .low_frequency = true,
    };

    pub const @"1.0" = AkSpeakerSetup{
        .front_center = true,
    };

    pub const @"1.1" = AkSpeakerSetup{
        .front_center = true,
        .low_frequency = true,
    };

    pub const @"2.0" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
    };

    pub const @"2.1" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .low_frequency = true,
    };

    pub const @"3.0" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .front_center = true,
    };

    pub const @"3.1" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .front_center = true,
        .low_frequency = true,
    };

    pub const @"4.0" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
    };

    pub const @"4.1" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .low_frequency = true,
    };

    pub const @"5.0" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .front_center = true,
    };

    pub const @"5.1" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .front_center = true,
        .low_frequency = true,
    };

    pub const @"6.0" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .back_left = true,
        .back_right = true,
    };

    pub const @"6.1" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .back_left = true,
        .back_right = true,
        .low_frequency = true,
    };

    pub const @"7.0" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .back_left = true,
        .back_right = true,
        .front_center = true,
    };

    pub const @"7.1" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .back_left = true,
        .back_right = true,
        .front_center = true,
        .low_frequency = true,
    };

    pub const Surround = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .back_center = true,
    };

    pub const Height_2 = AkSpeakerSetup{
        .height_front_left = true,
        .height_front_right = true,
    };

    pub const Height_4 = AkSpeakerSetup{
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
    };

    pub const Height_5 = AkSpeakerSetup{
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
        .height_front_center = true,
    };

    pub const Height_All = AkSpeakerSetup{
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
        .height_front_center = true,
        .height_back_center = true,
    };

    pub const Height_4_Top = AkSpeakerSetup{
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
        .height_top = true,
    };

    pub const Height_5_Top = AkSpeakerSetup{
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
        .height_front_center = true,
        .height_top = true,
    };

    pub const @"Auro 222" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .height_front_left = true,
        .height_front_right = true,
    };

    pub const @"Auro 8" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
    };

    pub const @"Auro 9.0" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
        .front_center = true,
    };

    pub const @"Auro 9.1" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
        .front_center = true,
        .low_frequency = true,
    };

    pub const @"Auro 10.0" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
        .front_center = true,
        .height_top = true,
    };

    pub const @"Auro 10.1" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
        .front_center = true,
        .height_top = true,
        .low_frequency = true,
    };

    pub const @"Auro 11.0" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
        .front_center = true,
        .height_top = true,
        .height_front_center = true,
    };

    pub const @"Auro 11.1" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
        .front_center = true,
        .height_top = true,
        .height_front_center = true,
        .low_frequency = true,
    };

    pub const @"Auro 11.0 (7+4)" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .back_left = true,
        .back_right = true,
        .front_center = true,
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
    };

    pub const @"Auro 11.1 (7+4)" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .back_left = true,
        .back_right = true,
        .front_center = true,
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
        .low_frequency = true,
    };

    pub const @"Auro 13.0" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .back_left = true,
        .back_right = true,
        .front_center = true,
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
        .height_front_center = true,
        .height_top = true,
    };

    pub const @"Auro 13.1" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .back_left = true,
        .back_right = true,
        .front_center = true,
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
        .height_front_center = true,
        .height_top = true,
        .low_frequency = true,
    };

    pub const @"Dolby 5.0.2" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .front_center = true,
        .height_front_left = true,
        .height_front_right = true,
    };

    pub const @"Dolby 5.1.2" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .front_center = true,
        .height_front_left = true,
        .height_front_right = true,
        .low_frequency = true,
    };

    pub const @"Dolby 6.0.2" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .back_left = true,
        .back_right = true,
        .height_front_left = true,
        .height_front_right = true,
    };

    pub const @"Dolby 6.1.2" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .back_left = true,
        .back_right = true,
        .height_front_left = true,
        .height_front_right = true,
        .low_frequency = true,
    };

    pub const @"Dolby 6.0.4" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .back_left = true,
        .back_right = true,
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
    };

    pub const @"Dolby 6.1.4" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .back_left = true,
        .back_right = true,
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
        .low_frequency = true,
    };

    pub const @"Dolby 7.0.2" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .back_left = true,
        .back_right = true,
        .front_center = true,
        .height_front_left = true,
        .height_front_right = true,
    };

    pub const @"Dolby 7.1.2" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .back_left = true,
        .back_right = true,
        .front_center = true,
        .height_front_left = true,
        .height_front_right = true,
        .low_frequency = true,
    };

    pub const @"Dolby 7.0.4" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .back_left = true,
        .back_right = true,
        .front_center = true,
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
    };

    pub const @"Dolby 7.1.4" = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .side_left = true,
        .side_right = true,
        .back_left = true,
        .back_right = true,
        .front_center = true,
        .height_front_left = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_right = true,
        .low_frequency = true,
    };

    pub const All_Speakers = AkSpeakerSetup{
        .front_left = true,
        .front_right = true,
        .front_center = true,
        .low_frequency = true,
        .back_left = true,
        .back_right = true,
        .back_center = true,
        .side_left = true,
        .side_right = true,
        .height_top = true,
        .height_front_left = true,
        .height_front_center = true,
        .height_front_right = true,
        .height_back_left = true,
        .height_back_center = true,
        .height_back_right = true,
    };

    pub const Mono = @"1.0";
    pub const Stereo = @"2.0";
    pub const Front = @"3.0";

    pub inline fn fixLeftToCenter(self: *AkSpeakerSetup) void {
        if (!self.front_center and !self.front_right and self.front_left) {
            self.front_left = false;
            self.front_center = true;
        }
    }

    pub inline fn fixRearToSide(self: *AkSpeakerSetup) void {
        if (self.back_left and !self.side_left) {
            self.back_left = false;
            self.back_right = false;
            self.side_left = true;
            self.side_right = true;
        }
    }

    pub inline fn convertToSupported(self: *AkSpeakerSetup) void {
        fixLeftToCenter(self);
        fixRearToSide(self);
    }

    pub inline fn numChannels(self: AkSpeakerSetup) u8 {
        return @popCount(@as(u20, @bitCast(self)));
    }

    pub inline fn fromNumChannels(channels: u8) AkSpeakerSetup {
        return switch (channels) {
            1 => @"1.0",
            2 => @"2.0",
            3 => @"2.1",
            4 => @"4.0",
            5 => @"5.0",
            6 => @"5.1",
            7 => @"7.0",
            8 => @"7.1",
            else => .{},
        };
    }

    pub inline fn hasLFE(self: AkSpeakerSetup) bool {
        return self.low_frequency;
    }

    pub inline fn hasCenter(self: AkSpeakerSetup) bool {
        return self.front_center;
    }

    pub inline fn hasSurroundChannels(self: AkSpeakerSetup) bool {
        return self.back_left or self.side_left;
    }

    pub inline fn hasStricklyOnePairOfSurroundChannels(self: AkSpeakerSetup) bool {
        return (!self.back_left and self.side_left) or (self.back_left and !self.side_left);
    }

    pub inline fn hasSideAndRearChannels(self: AkSpeakerSetup) bool {
        return self.back_left and self.side_left;
    }

    pub inline fn hasHeightChannels(self: AkSpeakerSetup) bool {
        return self.height_back_center or self.height_back_left or self.height_back_right or self.height_front_center or self.height_front_left or self.height_front_right or self.height_top;
    }

    pub inline fn backToSideChannels(self: *AkSpeakerSetup) bool {
        if (hasStricklyOnePairOfSurroundChannels(self)) {
            self.back_left = false;
            self.back_right = false;
            self.side_left = true;
            self.side_right = true;
        }
    }
};

comptime {
    std.debug.assert(@as(u20, @bitCast(AkSpeakerSetup{ .back_center = true })) == 0x100);
    std.debug.assert(@as(u20, @bitCast(AkSpeakerSetup{ .side_left = true })) == 0x200);
    std.debug.assert(@as(u20, @bitCast(AkSpeakerSetup{ .side_right = true })) == 0x400);
}

pub const AK_STANDARD_MAX_NUM_CHANNELS = 8;
pub const AK_MAX_AMBISONICS_ORDER = 5;

pub const AkChannelConfigType = enum(u4) {
    anonymous = 0,
    standard = 1,
    ambisonic = 2,
    objects = 3,

    use_device_main = 0xE,
    use_device_passthrough = 0xF,
};

pub const AkChannelConfig = packed struct(u32) {
    num_channels: u8 = 0,
    config_type: AkChannelConfigType = .anonymous,
    channel_mask: AkSpeakerSetup = .{},

    pub inline fn standard(channel_mask: AkSpeakerSetup) AkChannelConfig {
        return create(channel_mask.numChannels(), channel_mask);
    }

    pub inline fn anonymous(num_channels: u8) AkChannelConfig {
        return create(num_channels, .{});
    }

    pub inline fn ambisonic(num_channels: u8) AkChannelConfig {
        var result: AkChannelConfig = .{};
        result.setAmbisonic(num_channels);
        return result;
    }

    pub inline fn object() AkChannelConfig {
        var result: AkChannelConfig = .{};
        result.setObject();
        return result;
    }

    pub inline fn create(num_channels: u8, channel_mask: AkSpeakerSetup) AkChannelConfig {
        var result: AkChannelConfig = .{};
        result.setStandardOrAnonymous(num_channels, channel_mask);
        return result;
    }

    pub inline fn clear(self: *AkChannelConfig) void {
        self.num_channels = 0;
        self.config_type = .anonymous;
        self.channel_mask = .{};
    }

    pub inline fn setStandard(self: *AkChannelConfig, channel_mask: AkSpeakerSetup) void {
        self.num_channels = channel_mask.numChannels();
        self.config_type = .standard;
        self.channel_mask = channel_mask;
    }

    pub inline fn setStandardOrAnonymous(self: *AkChannelConfig, num_channels: u8, channel_mask: AkSpeakerSetup) void {
        self.num_channels = num_channels;
        self.config_type = if (channel_mask.numChannels() > 0) .standard else .anonymous;
        self.channel_mask = channel_mask;
    }

    pub inline fn setAnonymous(self: *AkChannelConfig, num_channels: u8) void {
        self.num_channels = num_channels;
        self.config_type = .anonymous;
        self.channel_mask = .{};
    }

    pub inline fn setAmbisonic(self: *AkChannelConfig, num_channels: u8) void {
        self.num_channels = num_channels;
        self.config_type = .ambisonic;
        self.channel_mask = .{};
    }

    pub inline fn setObject(self: *AkChannelConfig) void {
        self.num_channels = 0;
        self.config_type = .objects;
        self.channel_mask = .{};
    }

    pub inline fn setSameAsMainMax(self: *AkChannelConfig) void {
        self.num_channels = 0;
        self.config_type = .use_device_main;
        self.channel_mask = .{};
    }

    pub inline fn setSameAsPassthrough(self: *AkChannelConfig) void {
        self.num_channels = 0;
        self.config_type = .use_device_passthrough;
        self.channel_mask = .{};
    }

    pub inline fn isValid(self: AkChannelConfig) bool {
        return @intFromEnum(self.config_type) <= @intFromEnum(AkChannelConfigType.objects) and (self.num_channels != 0 or self.config_type == .objects);
    }

    pub inline fn removeLFE(self: AkChannelConfig) AkChannelConfig {
        var new_config = self;

        new_config.channel_mask.low_frequency = false;
        new_config.num_channels = new_config.channel_mask.numChannels();

        return new_config;
    }

    pub inline fn removeCenter(self: AkChannelConfig) AkChannelConfig {
        var new_config = self;

        new_config.channel_mask.front_center = false;
        new_config.num_channels = new_config.channel_mask.numChannels();

        return new_config;
    }

    pub inline fn hasLFE(self: AkChannelConfig) bool {
        return self.channel_mask.hasLFE();
    }

    pub inline fn hasCenter(self: AkChannelConfig) bool {
        return self.channel_mask.hasCenter();
    }

    pub inline fn fromC(channel_config: u32) AkChannelConfig {
        return @bitCast(channel_config);
    }

    pub inline fn toC(self: AkChannelConfig) u32 {
        return @bitCast(self);
    }
};
