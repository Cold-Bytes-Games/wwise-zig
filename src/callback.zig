const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const common_defs = @import("common_defs.zig");
const IAkPlugin = @import("IAkPlugin.zig");
const midi_types = @import("midi_types.zig");
const speaker_config = @import("speaker_config.zig");
const SpeakerVolumes = @import("SpeakerVolumes.zig");

pub const AkCallbackType = packed struct(common.DefaultEnumType) {
    end_of_event: bool = false,
    end_of_dynamic_sequence_item: bool = false,
    marker: bool = false,
    duration: bool = false,
    speaker_volume_matrix: bool = false,
    starvation: bool = false,
    music_playlist_select: bool = false,
    music_play_started: bool = false,
    music_sync_beat: bool = false,
    music_sync_bar: bool = false,
    music_sync_entry: bool = false,
    music_sync_exit: bool = false,
    music_sync_grid: bool = false,
    music_sync_user_ue: bool = false,
    music_sync_point: bool = false,
    pad0: bool = false,
    midi_event: bool = false,
    pad1: u4 = 0,
    enable_get_source_play_position: bool = false,
    enable_get_music_play_position: bool = false,
    enable_get_source_stream_buffering: bool = false,

    pub const MusicSyncAll = @bitCast(AkCallbackType, c.WWISEC_AK_MusicSyncAll);
    pub const CallbackBits = @bitCast(AkCallbackType, c.WWISEC_AK_CallbackBits);

    pub inline fn fromC(value: c.WWISEC_AkCallbackType) AkCallbackType {
        return @bitCast(AkCallbackType, value);
    }

    pub inline fn toC(self: AkCallbackType) c.WWISEC_AkCallbackType {
        return @bitCast(c.WWISEC_AkCallbackType, self);
    }

    comptime {
        std.debug.assert(@bitCast(common.DefaultEnumType, AkCallbackType{ .midi_event = true }) == c.WWISEC_AK_MIDIEvent);
        std.debug.assert(@bitCast(common.DefaultEnumType, AkCallbackType{ .enable_get_source_play_position = true }) == c.WWISEC_AK_EnableGetSourcePlayPosition);
        std.debug.assert(@bitCast(common.DefaultEnumType, AkCallbackType{ .enable_get_music_play_position = true }) == c.WWISEC_AK_EnableGetMusicPlayPosition);
        std.debug.assert(@bitCast(common.DefaultEnumType, AkCallbackType{ .enable_get_source_stream_buffering = true }) == c.WWISEC_AK_EnableGetSourceStreamBuffering);
    }
};

pub const AkCallbackInfo = extern struct {
    cookie: ?*anyopaque = null,
    game_obj_id: common.AkGameObjectID = 0,

    pub inline fn fromC(value: c.WWISEC_AkCallbackInfo) AkCallbackInfo {
        return @bitCast(AkCallbackInfo, value);
    }

    pub inline fn toC(self: AkCallbackInfo) c.WWISEC_AkCallbackInfo {
        return @bitCast(c.WWISEC_AkCalbackInfo, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCallbackInfo) == @sizeOf(c.WWISEC_AkCallbackInfo));
    }
};

pub const AkEventCallbackInfo = extern struct {
    base: AkCallbackInfo = .{},
    playing_id: common.AkPlayingID = 0,
    event_id: common.AkUniqueID = 0,

    pub inline fn fromC(value: c.WWISEC_AkEventCallbackInfo) AkEventCallbackInfo {
        return @bitCast(AkEventCallbackInfo, value);
    }

    pub inline fn toC(self: AkEventCallbackInfo) c.WWISEC_AkEventCallbackInfo {
        return @bitCast(c.WWISEC_AkEventCallbackInfo, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkEventCallbackInfo) == @sizeOf(c.WWISEC_AkEventCallbackInfo));
    }
};

pub const AkMIDIEventCallbackInfo = extern struct {
    base: AkEventCallbackInfo = .{},
    midi_event: midi_types.AkMIDIEvent,

    pub inline fn fromC(value: c.WWISEC_AkMIDIEventCallbackInfo) AkMIDIEventCallbackInfo {
        return @bitCast(AkMIDIEventCallbackInfo, value);
    }

    pub inline fn toC(self: AkMIDIEventCallbackInfo) c.WWISEC_AkMIDIEventCallbackInfo {
        return @bitCast(c.WWISEC_AkMIDIEventCallbackInfo, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkMIDIEventCallbackInfo) == @sizeOf(c.WWISEC_AkMIDIEventCallbackInfo));
    }
};

pub const AkMarkerCallbackInfo = extern struct {
    base: AkEventCallbackInfo = .{},
    identifier: u32 = 0,
    position: u32 = 0,
    str_label: ?[*:0]const u8 = null,

    pub inline fn fromC(value: c.WWISEC_AkMarkerCallbackInfo) AkMarkerCallbackInfo {
        return @bitCast(AkMarkerCallbackInfo, value);
    }

    pub inline fn toC(self: AkMarkerCallbackInfo) c.WWISEC_AkMarkerCallbackInfo {
        return @bitCast(c.WWISEC_AkMarkerCallbackInfo, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkMarkerCallbackInfo) == @sizeOf(c.WWISEC_AkMarkerCallbackInfo));
    }
};

pub const AkDurationCallbackInfo = extern struct {
    base: AkEventCallbackInfo,
    duration: f32,
    estimate_duration: f32,
    audio_node_id: common.AkUniqueID,
    media_id: common.AkUniqueID,
    streaming: bool,

    pub inline fn fromC(value: c.WWISEC_AkDurationCallbackInfo) AkDurationCallbackInfo {
        return @bitCast(AkDurationCallbackInfo, value);
    }

    pub inline fn toC(self: AkDurationCallbackInfo) c.WWISEC_AkDurationCallbackInfo {
        return @bitCast(c.WWISEC_AkDurationCallbackInfo, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkDurationCallbackInfo) == @sizeOf(c.WWISEC_AkDurationCallbackInfo));
    }
};

pub const AkDynamicSequenceItemCallbackInfo = extern struct {
    base: AkCallbackInfo = .{},
    playing_id: common.AkPlayingID = 0,
    audio_node_id: common.AkUniqueID = 0,
    custom_info: ?*anyopaque = null,

    pub inline fn fromC(value: c.WWISEC_AkDynamicSequenceItemCallbackInfo) AkDynamicSequenceItemCallbackInfo {
        return @bitCast(AkDynamicSequenceItemCallbackInfo, value);
    }

    pub inline fn toC(self: AkDynamicSequenceItemCallbackInfo) c.WWISEC_AkDynamicSequenceItemCallbackInfo {
        return @bitCast(c.WWISEC_AkDynamicSequenceItemCallbackInfo, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkDynamicSequenceItemCallbackInfo) == @sizeOf(c.WWISEC_AkDynamicSequenceItemCallbackInfo));
    }
};

pub const AkSpeakerVolumeMatrixCallbackInfo = extern struct {
    base: AkEventCallbackInfo = .{},
    volumes: SpeakerVolumes.MatrixPtr,
    input_config: speaker_config.AkChannelConfig = .{},
    output_config: speaker_config.AkChannelConfig = .{},
    base_volume: [*]f32,
    emitter_listener_volume: [*]f32,
    context: ?*IAkPlugin.IAkMixerInputContext = null,
    mixer_context: ?*IAkPlugin.IAkMixerPluginContext = null,

    pub inline fn fromC(value: c.WWISEC_AkSpeakerVolumeMatrixCallbackInfo) AkSpeakerVolumeMatrixCallbackInfo {
        return @bitCast(AkSpeakerVolumeMatrixCallbackInfo, value);
    }

    pub inline fn toC(self: AkSpeakerVolumeMatrixCallbackInfo) c.WWISEC_AkSpeakerVolumeMatrixCallbackInfo {
        return @bitCast(c.WWISEC_AkSpeakerVolumeMatrixCallbackInfo, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkSpeakerVolumeMatrixCallbackInfo) == @sizeOf(c.WWISEC_AkSpeakerVolumeMatrixCallbackInfo));
    }
};

pub const AkBusMeteringCallbackInfo = extern struct {
    base: AkCallbackInfo = .{},
    metering: ?*common_defs.AK_AkMetering = null,
    channel_config: speaker_config.AkChannelConfig = .{},
    metering_flags: common.AkMeteringFlags = .{},

    pub inline fn fromC(value: c.WWISEC_AkBusMeteringCallbackInfo) AkBusMeteringCallbackInfo {
        return @bitCast(AkBusMeteringCallbackInfo, value);
    }

    pub inline fn toC(self: AkBusMeteringCallbackInfo) c.WWISEC_AkBusMeteringCallbackInfo {
        return @bitCast(c.WWISEC_AkBusMeteringCallbackInfo, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkBusMeteringCallbackInfo) == @sizeOf(c.WWISEC_AkBusMeteringCallbackInfo));
    }
};

pub const AkOutputDeviceMeteringCallbackInfo = extern struct {
    base: AkCallbackInfo = .{},
    main_mix_metering: ?*common_defs.AkMetering = null,
    main_mix_config: speaker_config.AkChannelConfig = .{},
    passthrough_metering: ?*common_defs.AkMetering = null,
    passthrough_mix_config: speaker_config.AkChannelConfig = .{},
    num_system_audio_objects: u32 = 0,
    system_audio_object_meteering: [*]?*common_defs.AkMetering,
    metering_flags: common.AkMeteringFlags = .{},

    pub inline fn fromC(value: c.WWISEC_AkOutputDeviceMeteringCallbackInfo) AkOutputDeviceMeteringCallbackInfo {
        return @bitCast(AkOutputDeviceMeteringCallbackInfo, value);
    }

    pub inline fn toC(self: AkOutputDeviceMeteringCallbackInfo) c.WWISEC_AkOutputDeviceMeteringCallbackInfo {
        return @bitCast(c.WWISEC_AkOutputDeviceMeteringCallbackInfo, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkOutputDeviceMeteringCallbackInfo) == @sizeOf(c.WWISEC_AkOutputDeviceMeteringCallbackInfo));
    }
};

pub const AkMusicPlaylistCallbackInfo = extern struct {
    base: AkEventCallbackInfo = .{},
    playlist_id: common.AkUniqueID = 0,
    num_playist_items: u32 = 0,
    playlist_selection: u32 = 0,
    playlist_item_done: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_AkMusicPlaylistCallbackInfo) AkMusicPlaylistCallbackInfo {
        return @bitCast(AkMusicPlaylistCallbackInfo, value);
    }

    pub inline fn toC(self: AkMusicPlaylistCallbackInfo) c.WWISEC_AkMusicPlaylistCallbackInfo {
        return @bitCast(c.WWISEC_AkMusicPlaylistCallbackInfo, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkMusicPlaylistCallbackInfo) == @sizeOf(c.WWISEC_AkMusicPlaylistCallbackInfo));
    }
};

pub const AkSegmentInfo = extern struct {
    current_position: common.AkTimeMs = 0,
    pre_entry_duration: common.AkTimeMs = 0,
    active_duration: common.AkTimeMs = 0,
    post_exit_duration: common.AkTimeMs = 0,
    remaining_look_ahead_time: common.AkTimeMs = 0,
    beat_duration: f32 = 0.0,
    bar_duration: f32 = 0.0,
    grid_duration: f32 = 0.0,
    grid_offset: f32 = 0.0,

    pub inline fn fromC(value: c.WWISEC_AkSegmentInfo) AkSegmentInfo {
        return @bitCast(AkSegmentInfo, value);
    }

    pub inline fn toC(self: AkSegmentInfo) c.WWISEC_AkSegmentInfo {
        return @bitCast(c.WWISEC_AkSegmentInfo, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkSegmentInfo) == @sizeOf(c.WWISEC_AkSegmentInfo));
    }
};

pub const AkMusicSyncCallbackInfo = extern struct {
    base: AkCallbackInfo = .{},
    playing_id: common.AkPlayingID = 0,
    segment_info: AkSegmentInfo = .{},
    music_sync_type: AkCallbackType = .{},
    user_cue_name: ?[*:0]const u8 = null,

    pub inline fn fromC(value: c.WWISEC_AkMusicSyncCallbackInfo) AkMusicSyncCallbackInfo {
        return @bitCast(AkMusicSyncCallbackInfo, value);
    }

    pub inline fn toC(self: AkMusicSyncCallbackInfo) c.WWISEC_AkMusicSyncCallbackInfo {
        return @bitCast(c.WWISEC_AkMusicSyncCallbackInfo, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkMusicSyncCallbackInfo) == @sizeOf(c.WWISEC_AkMusicSyncCallbackInfo));
    }
};

pub const AkResourceMonitorDataSummary = extern struct {
    total_cpu: f32 = 0.0,
    plugin_cpu: f32 = 0.0,
    physical_voices: u32 = 0,
    virtual_voices: u32 = 0,
    total_voices: u32 = 0,
    nb_active_events: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_AkResourceMonitorDataSummary) AkResourceMonitorDataSummary {
        return @bitCast(AkResourceMonitorDataSummary, value);
    }

    pub inline fn toC(self: AkResourceMonitorDataSummary) c.WWISEC_AkResourceMonitorDataSummary {
        return @bitCast(c.WWISEC_AkResourceMonitorDataSummary, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkResourceMonitorDataSummary) == @sizeOf(c.WWISEC_AkResourceMonitorDataSummary));
    }
};

pub const AkCallbackFunc = ?*const fn (in_type: AkCallbackType, in_callback_info: *AkCallbackInfo) callconv(.C) void;
pub const AkBusCallbackFunc = ?*const fn (in_callback_info: *AkSpeakerVolumeMatrixCallbackInfo) callconv(.C) void;
pub const AkBusMeteringCallbackFunc = ?*const fn (in_callback_info: *AkBusMeteringCallbackInfo) callconv(.C) void;
pub const AkOutputDeviceMeteringCallbackFunc = ?*const fn (in_callback_info: *AkOutputDeviceMeteringCallbackInfo) callconv(.C) void;
pub const AkBankCallbackFunc = ?*const fn (in_bank_id: u32, in_memory_bank_ptr: ?*const anyopaque, in_load_result: common.AKRESULT, in_cookie: ?*anyopaque) callconv(.C) void;

pub const AkGlobalCallbackLocation = packed struct(common.DefaultEnumType) {
    register: bool = false,
    begin: bool = false,
    pre_process_message_queue_for_render: bool = false,
    post_messages_processed: bool = false,
    begin_render: bool = false,
    end_render: bool = false,
    end: bool = false,
    term: bool = false,
    monitor: bool = false,
    monitor_recap: bool = false,
    init: bool = false,
    @"suspend": bool = false,
    wakeup_from_suspend: bool = false,

    pub inline fn fromC(value: c.WWISEC_AkGlobalCallbackLocation) AkGlobalCallbackLocation {
        return @bitCast(AkGlobalCallbackLocation, value);
    }

    pub inline fn toC(self: AkGlobalCallbackLocation) c.WWISEC_AkGlobalCallbackLocation {
        return @bitCast(c.WWISEC_AkGlobalCallbackLocation, self);
    }
};

pub const AkGlobalCallbackFunc = *const fn (in_context: ?*IAkPlugin.IAkGlobalPluginContext, in_location: AkGlobalCallbackLocation, in_cookie: ?*anyopaque) callconv(.C) void;
pub const AkResourceMonitorCallbackFunc = *const fn (in_data_summary: ?*const AkResourceMonitorDataSummary) callconv(.C) void;

pub const AkAudioDeviceEvent = enum(common.DefaultEnumType) {
    initialization,
    removal,
    system_removal,
};

pub const AkDeviceStatusCallbackFunc = *const fn (
    in_context: ?*IAkPlugin.IAkGlobalPluginContext,
    in_id_audio_device_shareset: common.AkUniqueID,
    in_id_device_id: u32,
    in_id_event: AkAudioDeviceEvent,
    in_ak_result: common.AKRESULT,
) callconv(.C) void;

pub const AkCaptureCallbackFunc = *const fn (in_capture_buffer: ?*common_defs.AkAudioBuffer, in_id_output: common.AkOutputDeviceID, cookie: ?*anyopaque) callconv(.C) void;
