const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const callbacks = @import("callback.zig");

pub const AkExternalSourceArray = ?*anyopaque;

pub const PlaylistItem = extern struct {
    audio_node_id: common.AkUniqueID = 0,
    ms_delay: common.AkTimeMs = 0,
    custom_info: ?*anyopaque = null,
    external_srcs: AkExternalSourceArray = null,

    pub inline fn fromC(value: c.WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem) PlaylistItem {
        return @bitCast(PlaylistItem, value);
    }

    pub inline fn toC(self: PlaylistItem) c.WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem {
        return @bitCast(c.WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem, self);
    }

    pub fn setExternalSources(self: *PlaylistItem, external_srcs: []const common.AkExternalSourceInfo) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem_SetExternalSources(
                @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem, self),
                @truncate(u32, external_srcs.len),
                @ptrCast([*]c.WWISEC_AkExternalSourceInfo, @constCast(external_srcs)),
            ),
        );
    }

    comptime {
        std.debug.assert(@sizeOf(PlaylistItem) == @sizeOf(c.WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem));
    }
};

pub const Playlist = opaque {
    pub const EnqueueOptionalArgs = struct {
        ms_delay: common.AkTimeMs = 0,
        custom_info: ?*anyopaque = null,
        external_sources: []const common.AkExternalSourceInfo = &.{},
    };

    pub fn enqueue(self: *Playlist, in_audio_node_id: common.AkUniqueID, optional_args: EnqueueOptionalArgs) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Enqueue(
                @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
                in_audio_node_id,
                optional_args.ms_delay,
                optional_args.custom_info,
                @truncate(u32, optional_args.external_sources.len),
                @ptrCast([*]c.WWISEC_AkExternalSourceInfo, @constCast(optional_args.external_sources)),
            ),
        );
    }

    pub fn erase(self: *Playlist, in_index: u32) void {
        c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Erase(
            @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
            in_index,
        );
    }

    pub fn eraseSwap(self: *Playlist, in_index: u32) void {
        c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_EraseSwap(
            @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
            in_index,
        );
    }

    pub fn isGrowingAllowed(self: *Playlist) bool {
        return c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_IsGrowingAllowed(
            @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
        );
    }

    pub fn reserve(self: *Playlist, in_reserve: u32) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Reserve(
                @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
                in_reserve,
            ),
        );
    }

    pub fn reserveExtra(self: *Playlist, in_reserve: u32) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_ReserveExtra(
                @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
                in_reserve,
            ),
        );
    }

    pub fn reserved(self: *Playlist) u32 {
        return c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Reserved(
            @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
        );
    }

    pub fn term(self: *Playlist) void {
        c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Term(
            @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
        );
    }

    pub fn length(self: *Playlist) u32 {
        return c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Length(
            @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
        );
    }

    pub fn data(self: *Playlist) [*]PlaylistItem {
        return @ptrCast(
            [*]PlaylistItem,
            c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Data(
                @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
            ),
        );
    }

    pub fn isEmpty(self: *Playlist) bool {
        return c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_IsEmpty(
            @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
        );
    }

    pub fn exists(self: *Playlist, in_item: *const PlaylistItem) ?*PlaylistItem {
        return @ptrCast(
            ?*PlaylistItem,
            c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Exists(
                @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
                @ptrCast(?*const c.WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem, in_item),
            ),
        );
    }

    pub fn addLast(self: *Playlist) ?*PlaylistItem {
        return @ptrCast(
            ?*PlaylistItem,
            c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_AddLast(
                @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
            ),
        );
    }

    pub fn addLastItem(self: *Playlist, in_item: *const PlaylistItem) ?*PlaylistItem {
        return @ptrCast(
            ?*PlaylistItem,
            c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_AddLastItem(
                @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
                @ptrCast(?*const c.WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem, in_item),
            ),
        );
    }

    pub fn last(self: *Playlist) *PlaylistItem {
        return @ptrCast(
            *PlaylistItem,
            c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Last(
                @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
            ),
        );
    }

    pub fn removeLast(self: *Playlist) void {
        c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_RemoveLast(
            @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
        );
    }

    pub fn remove(self: *Playlist, in_item: *const PlaylistItem) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Remove(
                @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
                @ptrCast(?*const c.WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem, in_item),
            ),
        );
    }

    pub fn removeSwap(self: *Playlist, in_item: *const PlaylistItem) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_RemoveSwap(
                @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
                @ptrCast(?*const c.WWISEC_AK_SoundEngine_DynamicSequence_PlaylistItem, in_item),
            ),
        );
    }

    pub fn removeAll(self: *Playlist) void {
        c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_RemoveAll(
            @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
        );
    }

    pub fn at(self: *Playlist, in_index: u32) *PlaylistItem {
        return @ptrCast(
            *PlaylistItem,
            c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_At(
                @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
                in_index,
            ),
        );
    }

    pub fn insert(self: *Playlist, in_index: u32) ?*PlaylistItem {
        return @ptrCast(
            ?*PlaylistItem,
            c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Insert(
                @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
                in_index,
            ),
        );
    }

    pub fn growArray(self: *Playlist) bool {
        return c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_GrowArray(
            @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
        );
    }

    pub fn growArraySize(self: *Playlist, in_grow_by: u32) bool {
        return c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_GrowArraySize(
            @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
            in_grow_by,
        );
    }

    pub fn resize(self: *Playlist, in_size: u32) bool {
        return c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Resize(
            @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
            in_size,
        );
    }

    pub fn transfer(self: *Playlist, source: *Playlist) void {
        c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Transfer(
            @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
            @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, source),
        );
    }

    pub fn copy(self: *Playlist, source: *const Playlist) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist_Copy(
                @ptrCast(?*c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, self),
                @ptrCast(?*const c.WWISEC_AK_SoundEngine_DynamicSequence_Playlist, source),
            ),
        );
    }
};

pub const DynamicSequenceType = enum(common.DefaultEnumType) {
    sample_accurate = c.WWISEC_AK_SoundEngine_DynamicSequence_DynamicSequenceType_SampleAccurate,
    normal_transition = c.WWISEC_AK_SoundEngine_DynamicSequence_DynamicSequenceType_NormalTransition,
};

pub const OpenOptionalArgs = struct {
    flags: callbacks.AkCallbackType = .{},
    callback: callbacks.AkCallbackFunc = null,
    cookie: ?*anyopaque = null,
    dynamic_sequence_type: DynamicSequenceType = .sample_accurate,
};

pub fn open(in_game_object_id: common.AkGameObjectID, optional_args: OpenOptionalArgs) common.AkPlayingID {
    return c.WWISEC_AK_SoundEngine_DynamicSequence_Open(
        in_game_object_id,
        @intCast(u32, optional_args.flags.toC()),
        @ptrCast(c.WWISEC_AkCallbackFunc, optional_args.callback),
        optional_args.cookie,
        @enumToInt(optional_args.dynamic_sequence_type),
    );
}

pub fn close(in_playing_id: common.AkPlayingID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_DynamicSequence_Close(in_playing_id),
    );
}

pub const PlayOptionalArgs = struct {
    transition_duration: common.AkTimeMs = 0,
    fade_curve: common.AkCurveInterpolation = .linear,
};

pub fn play(in_playing_id: common.AkPlayingID, optional_args: PlayOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_DynamicSequence_Play(
            in_playing_id,
            optional_args.transition_duration,
            @enumToInt(optional_args.fade_curve),
        ),
    );
}

pub const PauseOptionalArgs = struct {
    transition_duration: common.AkTimeMs = 0,
    fade_curve: common.AkCurveInterpolation = .linear,
};

pub fn pause(in_playing_id: common.AkPlayingID, optional_args: PauseOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_DynamicSequence_Pause(
            in_playing_id,
            optional_args.transition_duration,
            @enumToInt(optional_args.fade_curve),
        ),
    );
}

pub const ResumeOptionalArgs = struct {
    transition_duration: common.AkTimeMs = 0,
    fade_curve: common.AkCurveInterpolation = .linear,
};

pub fn @"resume"(in_playing_id: common.AkPlayingID, optional_args: ResumeOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_DynamicSequence_Resume(
            in_playing_id,
            optional_args.transition_duration,
            @enumToInt(optional_args.fade_curve),
        ),
    );
}

pub const StopOptionalArgs = struct {
    transition_duration: common.AkTimeMs = 0,
    fade_curve: common.AkCurveInterpolation = .linear,
};

pub fn stop(in_playing_id: common.AkPlayingID, optional_args: StopOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_DynamicSequence_Stop(
            in_playing_id,
            optional_args.transition_duration,
            @enumToInt(optional_args.fade_curve),
        ),
    );
}

pub fn @"break"(in_playing_id: common.AkPlayingID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_DynamicSequence_Break(in_playing_id),
    );
}

pub fn seekTime(in_playing_id: common.AkPlayingID, in_position: common.AkTimeMs, in_seek_to_nearest_marker: bool) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_DynamicSequence_Seek_Time(in_playing_id, in_position, in_seek_to_nearest_marker),
    );
}

pub fn seekPercent(in_playing_id: common.AkPlayingID, in_percent: f32, in_seek_to_nearest_marker: bool) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_DynamicSequence_Seek_Percent(in_playing_id, in_percent, in_seek_to_nearest_marker),
    );
}

pub fn getPauseTimes(in_playing_id: common.AkPlayingID, out_time: *u32, out_duration: *u32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_DynamicSequence_GetPauseTimes(in_playing_id, out_time, out_duration),
    );
}

pub fn getPlayingItem(in_playing_id: common.AkPlayingID, out_audio_node_id: *common.AkUniqueID, out_custom_info: *?*anyopaque) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_DynamicSequence_GetPlayingItem(in_playing_id, out_audio_node_id, out_custom_info),
    );
}

pub fn lockPlaylist(in_playing_id: common.AkPlayingID) ?*Playlist {
    return @ptrCast(
        ?*Playlist,
        c.WWISEC_AK_SoundEngine_DynamicSequence_LockPlaylist(in_playing_id),
    );
}

pub fn unlockPlaylist(in_playing_id: common.AkPlayingID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_DynamicSequence_UnlockPlaylist(in_playing_id),
    );
}
