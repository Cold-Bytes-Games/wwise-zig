const c = @import("wwise_c");
const callback_types = @import("callback_types.zig");
const common = @import("common.zig");
const std = @import("std");
const typedefs = @import("typedefs.zig");
const zig = @import("zig.zig");

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

pub fn init(in_settings: ?*AkMusicSettings) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_MusicEngine_Init(@ptrCast(in_settings)),
    );
}

pub fn getDefaultInitSettings(out_settings: *AkMusicSettings) void {
    c.WWISEC_AK_MusicEngine_GetDefaultInitSettings(@ptrCast(out_settings));
}

pub fn term() void {
    c.WWISEC_AK_MusicEngine_Term();
}

pub fn getPlayingSegmentInfo(in_playing_id: typedefs.AkPlayingID, out_segment_info: *callback_types.AkSegmentInfo, extrapolate: bool) zig.WwiseError!void {
    try zig.handleAkResult(
        c.WWISEC_AK_MusicEngine_GetPlayingSegmentInfo(in_playing_id, @ptrCast(out_segment_info), extrapolate),
    );
}
