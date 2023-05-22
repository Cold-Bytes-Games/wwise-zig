const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");

pub const AkSegmentInfo = struct {
    current_position: common.AkTimeMs,
    pre_entry_duration: common.AkTimeMs,
    active_duration: common.AkTimeMs,
    post_exit_duration: common.AkTimeMs,
    remaining_look_ahead_time: common.AkTimeMs,
    beat_duration: f32,
    bar_duration: f32,
    grid_duration: f32,
    grid_offset: f32,

    pub fn fromC(value: c.WWISEC_AkSegmentInfo) AkSegmentInfo {
        return .{
            .current_position = value.iCurrentPosition,
            .pre_entry_duration = value.iPreEntryDuration,
            .active_duration = value.iActiveDuration,
            .post_exit_duration = value.iPostExitDuration,
            .remaining_look_ahead_time = value.iRemainingLookAheadTime,
            .beat_duration = value.fBeatDuration,
            .bar_duration = value.fBarDuration,
            .grid_duration = value.fGridDuration,
            .grid_offset = value.fGridOffset,
        };
    }

    pub fn toC(self: AkSegmentInfo) c.WWISEC_AkSegmentInfo {
        return .{
            .iCurrentPosition = self.current_position,
            .iPreEntryDuration = self.pre_entry_duration,
            .iActiveDuration = self.active_duration,
            .iPostExitDuration = self.post_exit_duration,
            .iRemainingLookAheadTime = self.remaining_look_ahead_time,
            .fBeatDuration = self.beat_duration,
            .fBarDuration = self.bar_duration,
            .fGridDuration = self.grid_duration,
            .fGridOffset = self.grid_offset,
        };
    }
};
