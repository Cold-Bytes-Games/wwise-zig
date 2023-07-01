const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const callbacks = @import("callbacks.zig");

pub const AkMusicSettings = extern struct {
    streaming_look_ahead_ratio: f32 = 0.0,

    pub inline fn fromC(value: c.WWISEC_AkMusicSettings) AkMusicSettings {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMusicSettings) c.WWISEC_AkMusicSettings {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkMusicSettings) == @sizeOf(c.WWISEC_AkMusicSettings));
    }
};

pub fn init(in_settings: ?*AkMusicSettings) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_MusicEngine_Init(@ptrCast(in_settings)),
    );
}

pub fn getDefaultInitSettings(out_settings: *AkMusicSettings) void {
    c.WWISEC_AK_MusicEngine_GetDefaultInitSettings(@ptrCast(out_settings));
}

pub fn term() void {
    c.WWISEC_AK_MusicEngine_Term();
}

pub fn getPlayingSegmentInfo(in_playing_id: common.AkPlayingID, out_segment_info: *callbacks.AkSegmentInfo, extrapolate: bool) common.WwiseError!void {
    try common.handleAkResult(
        c.WWISEC_AK_MusicEngine_GetPlayingSegmentInfo(in_playing_id, @ptrCast(out_segment_info), extrapolate),
    );
}
