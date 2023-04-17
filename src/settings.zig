const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const speaker_config = @import("speaker_config.zig");

pub const AkOutputSettings = struct {
    audio_device_shareset: common.AkUniqueID,
    id_device: u32,
    panning_rule: common.AkPanningRule,
    channel_config: speaker_config.AkChannelConfig,

    pub fn init(fallback_allocator: std.mem.Allocator, device_shareset: []const u8, id_device: common.AkUniqueID, channel_config: speaker_config.AkChannelConfig, panning: common.AkPanningRule) !AkOutputSettings {
        var raw_output_settings: c.WWISEC_AkOutputSettings = undefined;

        var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_char_allocator.get();

        const device_shareset_cstr = try common.toCString(allocator, device_shareset);
        defer allocator.free(device_shareset_cstr);

        c.WWISEC_AkOutputSettings_Init(&raw_output_settings, device_shareset_cstr, id_device, channel_config.toC(), @enumToInt(panning));

        return fromC(raw_output_settings);
    }

    pub fn fromC(output_settings: c.WWISEC_AkOutputSettings) AkOutputSettings {
        return .{
            .audio_device_shareset = output_settings.audioDeviceShareset,
            .id_device = output_settings.idDevice,
            .panning_rule = @intToEnum(common.AkPanningRule, output_settings.ePanningRule),
            .channel_config = speaker_config.AkChannelConfig.fromC(output_settings.channelConfig),
        };
    }

    pub fn toC(self: AkOutputSettings) c.WWISEC_AkOutputSettings {
        return c.WWISEC_AkOutputSettings{
            .audioDeviceShareset = self.audio_device_shareset,
            .idDevice = self.id_device,
            .ePanningRule = @enumToInt(self.panning_rule),
            .channelConfig = self.channel_config.toC(),
        };
    }
};
