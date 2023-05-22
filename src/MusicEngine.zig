const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const callback = @import("callback.zig");

pub const AkMusicSettings = struct {
    streaming_look_ahead_ratio: f32,

    pub fn fromC(value: c.WWISEC_AkMusicSettings) AkMusicSettings {
        return .{
            .streaming_look_ahead_ratio = value.fStreamingLookAheadRatio,
        };
    }

    pub fn toC(self: AkMusicSettings) c.WWISEC_AkMusicSettings {
        return .{
            .fStreamingLookAheadRatio = self.streaming_look_ahead_ratio,
        };
    }
};

pub fn init(in_settings: *AkMusicSettings) common.WwiseError!void {
    var raw_settings = in_settings.toC();

    return common.handleAkResult(
        c.WWISEC_AK_MusicEngine_Init(&raw_settings),
    );
}

pub fn getDefaultInitSettings(out_settings: *AkMusicSettings) void {
    var raw_settings: c.WWISEC_AkMusicSettings = undefined;
    c.WWISEC_AK_MusicEngine_GetDefaultInitSettings(&raw_settings);
    out_settings.* = AkMusicSettings.fromC(raw_settings);
}

pub fn term() void {
    c.WWISEC_AK_MusicEngine_Term();
}

pub fn getPlayingSegmentInfo(in_playing_id: common.AkPlayingID, out_segment_info: *callback.AkSegmentInfo, extrapolate: bool) common.WwiseError!void {
    var raw_segment_info: c.WWISEC_AkSegmentInfo = undefined;

    try common.handleAkResult(
        c.WWISEC_AK_MusicEngine_GetPlayingSegmentInfo(in_playing_id, &raw_segment_info, extrapolate),
    );

    out_segment_info.* = callback.AkSegmentInfo.fromC(raw_segment_info);
}
