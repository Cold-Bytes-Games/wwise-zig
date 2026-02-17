const c = @import("wwise_c");
const common_defs = @import("common_defs.zig");
const enums = @import("enums.zig");
const IAkPlugin = @import("IAkPlugin.zig");
const midi_types = @import("midi_types.zig");
const speaker_config = @import("speaker_config.zig");
const SpeakerVolumes = @import("SpeakerVolumes.zig");
const std = @import("std");
const typedefs = @import("typedefs.zig");
const zig = @import("zig.zig");

pub const AkCallbackType = packed struct(zig.DefaultEnumType) {
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
    midi_event: bool = false,
    dynamic_sequence_select: bool = false, // 16
    pad1: u5 = 0,
    enable_get_music_play_position: bool = false, // 21
    enable_get_source_stream_buffering: bool = false, // 22
    pad2: u10 = 0,

    pub const music_sync_all: AkCallbackType = @bitCast(c.AK_MusicSyncAll);
    pub const callback_bits: AkCallbackType = @bitCast(c.AK_CallbackBits);

    pub inline fn fromC(value: u32) AkCallbackType {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCallbackType) u32 {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@as(zig.DefaultEnumType, @bitCast(AkCallbackType{ .midi_event = true })) == c.AK_MIDIEvent);
        std.debug.assert(@as(zig.DefaultEnumType, @bitCast(AkCallbackType{ .enable_get_source_play_position = true })) == c.AK_EnableGetSourcePlayPosition);
        std.debug.assert(@as(zig.DefaultEnumType, @bitCast(AkCallbackType{ .enable_get_music_play_position = true })) == c.AK_EnableGetMusicPlayPosition);
        std.debug.assert(@as(zig.DefaultEnumType, @bitCast(AkCallbackType{ .enable_get_source_stream_buffering = true })) == c.AK_EnableGetSourceStreamBuffering);
        std.debug.assert(@as(zig.DefaultEnumType, @bitCast(AkCallbackType{ .dynamic_sequence_select = true })) == c.AK_DynamicSequenceSelect);
    }
};

pub const AkAudioDeviceEvent = enum(zig.DefaultEnumType) {
    initialization,
    removal,
    system_removal,
};

pub const AkGlobalCallbackLocation = packed struct(zig.DefaultEnumType) {
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
    profiler_connect: bool = false,
    profiler_disconnect: bool = false,
    pad: u17 = 0,

    pub inline fn fromC(value: u32) AkGlobalCallbackLocation {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkGlobalCallbackLocation) u32 {
        return @bitCast(self);
    }
};

pub const AkSegmentInfo = extern struct {
    current_position: typedefs.AkTimeMs = 0,
    pre_entry_duration: typedefs.AkTimeMs = 0,
    active_duration: typedefs.AkTimeMs = 0,
    post_exit_duration: typedefs.AkTimeMs = 0,
    remaining_look_ahead_time: typedefs.AkTimeMs = 0,
    beat_duration: f32 = 0.0,
    bar_duration: f32 = 0.0,
    grid_duration: f32 = 0.0,
    grid_offset: f32 = 0.0,

    pub inline fn fromC(value: c.AkSegmentInfo) AkSegmentInfo {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkSegmentInfo) c.AkSegmentInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkSegmentInfo) == @sizeOf(c.AkSegmentInfo));
    }
};

pub const AkEventCallbackInfo = extern struct {
    game_obj_id: typedefs.AkGameObjectID = 0,
    playing_id: typedefs.AkPlayingID = 0,
    event_id: typedefs.AkUniqueID = 0,

    pub inline fn fromC(value: c.AkEventCallbackInfo) AkEventCallbackInfo {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkEventCallbackInfo) c.AkEventCallbackInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkEventCallbackInfo) == @sizeOf(c.AkEventCallbackInfo));
    }
};

pub const AkMIDIEventCallbackInfo = extern struct {
    midi_event: midi_types.AkMIDIEvent,

    pub inline fn fromC(value: c.AkMIDIEventCallbackInfo) AkMIDIEventCallbackInfo {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMIDIEventCallbackInfo) c.AkMIDIEventCallbackInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkMIDIEventCallbackInfo) == @sizeOf(c.AkMIDIEventCallbackInfo));
    }
};

pub const AkMarkerCallbackInfo = extern struct {
    identifier: u32 = 0,
    position: u32 = 0,
    str_label: ?[*:0]const u8 = null,
    label_size: u32 = 0,

    pub inline fn fromC(value: c.AkMarkerCallbackInfo) AkMarkerCallbackInfo {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMarkerCallbackInfo) c.AkMarkerCallbackInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkMarkerCallbackInfo) == @sizeOf(c.AkMarkerCallbackInfo));
    }
};

pub const AkDurationCallbackInfo = extern struct {
    duration: f32,
    estimate_duration: f32,
    audio_node_id: typedefs.AkUniqueID,
    media_id: typedefs.AkUniqueID,
    streaming: bool,

    pub inline fn fromC(value: c.AkDurationCallbackInfo) AkDurationCallbackInfo {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkDurationCallbackInfo) c.AkDurationCallbackInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkDurationCallbackInfo) == @sizeOf(c.AkDurationCallbackInfo));
    }
};

pub const AkDynamicSequenceItemCallbackInfo = extern struct {
    audio_node_id: typedefs.AkUniqueID = 0,
    custom_info: ?*anyopaque = null,

    pub inline fn fromC(value: c.AkDynamicSequenceItemCallbackInfo) AkDynamicSequenceItemCallbackInfo {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkDynamicSequenceItemCallbackInfo) c.AkDynamicSequenceItemCallbackInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkDynamicSequenceItemCallbackInfo) == @sizeOf(c.AkDynamicSequenceItemCallbackInfo));
    }
};

pub const AkSpeakerVolumeMatrixCallbackInfo = extern struct {
    volumes: SpeakerVolumes.MatrixPtr,
    input_config: speaker_config.AkChannelConfig = .{},
    output_config: speaker_config.AkChannelConfig = .{},
    base_volume: [*]f32,
    emitter_listener_volume: [*]f32,
    context: ?*IAkPlugin.IAkMixerInputContext = null,
    mixer_context: ?*IAkPlugin.IAkMixerPluginContext = null,

    pub inline fn fromC(value: c.AkSpeakerVolumeMatrixCallbackInfo) AkSpeakerVolumeMatrixCallbackInfo {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkSpeakerVolumeMatrixCallbackInfo) c.AkSpeakerVolumeMatrixCallbackInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkSpeakerVolumeMatrixCallbackInfo) == @sizeOf(c.AkSpeakerVolumeMatrixCallbackInfo));
    }
};

pub const AkMusicPlaylistCallbackInfo = extern struct {
    playlist_id: typedefs.AkUniqueID = 0,
    num_playlist_items: u32 = 0,
    playlist_selection: u32 = 0,
    playlist_item_done: u32 = 0,

    pub inline fn fromC(value: c.AkMusicPlaylistCallbackInfo) AkMusicPlaylistCallbackInfo {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMusicPlaylistCallbackInfo) c.AkMusicPlaylistCallbackInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkMusicPlaylistCallbackInfo) == @sizeOf(c.AkMusicPlaylistCallbackInfo));
    }
};

pub const AkMusicSyncCallbackInfo = extern struct {
    segment_info: AkSegmentInfo = .{},
    music_sync_type: AkCallbackType = .{},
    user_cue_name: ?[*:0]const u8 = null,

    pub inline fn fromC(value: c.AkMusicSyncCallbackInfo) AkMusicSyncCallbackInfo {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMusicSyncCallbackInfo) c.AkMusicSyncCallbackInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkMusicSyncCallbackInfo) == @sizeOf(c.AkMusicSyncCallbackInfo));
    }
};

pub const AkCallbackInfo = extern struct {
    cookie: ?*anyopaque = null,
    game_obj_id: typedefs.AkGameObjectID = 0,

    pub inline fn fromC(value: c.WWISEC_AkCallbackInfo) AkCallbackInfo {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCallbackInfo) c.WWISEC_AkCallbackInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCallbackInfo) == @sizeOf(c.WWISEC_AkCallbackInfo));
    }
};

pub const AkBusMeteringCallbackInfo = extern struct {
    base: AkCallbackInfo = .{},
    metering: ?*common_defs.AkMetering = null,
    channel_config: speaker_config.AkChannelConfig = .{},
    metering_flags: enums.AkMeteringFlags = .{},

    pub inline fn fromC(value: c.WWISEC_AkBusMeteringCallbackInfo) AkBusMeteringCallbackInfo {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkBusMeteringCallbackInfo) c.WWISEC_AkBusMeteringCallbackInfo {
        return @bitCast(self);
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
    system_audio_object_metering: [*]?*common_defs.AkMetering,
    metering_flags: enums.AkMeteringFlags = .{},

    pub inline fn fromC(value: c.WWISEC_AkOutputDeviceMeteringCallbackInfo) AkOutputDeviceMeteringCallbackInfo {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkOutputDeviceMeteringCallbackInfo) c.WWISEC_AkOutputDeviceMeteringCallbackInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkOutputDeviceMeteringCallbackInfo) == @sizeOf(c.WWISEC_AkOutputDeviceMeteringCallbackInfo));
    }
};

pub const AkResourceMonitorDataSummary = extern struct {
    total_cpu: f32 = 0.0,
    plugin_cpu: f32 = 0.0,
    physical_voices: u32 = 0,
    virtual_voices: u32 = 0,
    total_voices: u32 = 0,
    nb_active_events: u32 = 0,

    pub inline fn fromC(value: c.AkResourceMonitorDataSummary) AkResourceMonitorDataSummary {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkResourceMonitorDataSummary) c.AkResourceMonitorDataSummary {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkResourceMonitorDataSummary) == @sizeOf(c.AkResourceMonitorDataSummary));
    }
};

pub const AkDynamicSequenceSelectCallbackInfo = struct {
    audio_node_id: typedefs.AkUniqueID = 0,
    ms_delay: typedefs.AkTimeMs = 0,
    custom_info: ?*anyopaque = null,
    ar_external_sources: typedefs.AkExternalSourceArray = null,

    pub inline fn fromC(value: c.WWISEC_AkDynamicSequenceSelectCallbackInfo) AkDynamicSequenceSelectCallbackInfo {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkDynamicSequenceSelectCallbackInfo) c.WWISEC_AkDynamicSequenceSelectCallbackInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkDynamicSequenceSelectCallbackInfo) == @sizeOf(c.WWISEC_AkDynamicSequenceSelectCallbackInfo));
    }
};

pub const AkEventCallbackFunc = ?*const fn (in_type: AkCallbackType, in_event_info: *AkEventCallbackInfo, in_callback_info: ?*anyopaque, in_cookie: ?*anyopaque) callconv(.c) void;
pub const AkCallbackFunc = AkEventCallbackFunc;
pub const AkBusCallbackFunc = ?*const fn (in_callback_info: *AkSpeakerVolumeMatrixCallbackInfo, in_cookie: ?*anyopaque) callconv(.c) void;
pub const AkBankCallbackFunc = ?*const fn (in_bank_id: u32, in_memory_bank_ptr: ?*const anyopaque, in_load_result: enums.AKRESULT, in_cookie: ?*anyopaque) callconv(.c) void;
pub const AkGlobalCallbackFunc = *const fn (in_context: ?*IAkPlugin.IAkGlobalPluginContext, in_location: AkGlobalCallbackLocation, in_cookie: ?*anyopaque) callconv(.c) void;
pub const AkResourceMonitorCallbackFunc = *const fn (in_data_summary: ?*const AkResourceMonitorDataSummary) callconv(.c) void;
pub const AkDeviceStatusCallbackFunc = *const fn (
    in_context: ?*IAkPlugin.IAkGlobalPluginContext,
    in_id_audio_device_shareset: typedefs.AkUniqueID,
    in_id_device_id: u32,
    in_id_event: AkAudioDeviceEvent,
    in_ak_result: enums.AKRESULT,
) callconv(.c) void;

pub const AkBusMeteringCallbackFunc = ?*const fn (in_callback_info: *AkBusMeteringCallbackInfo) callconv(.c) void;
pub const AkOutputDeviceMeteringCallbackFunc = ?*const fn (in_callback_info: *AkOutputDeviceMeteringCallbackInfo) callconv(.c) void;
pub const AkCaptureCallbackFunc = *const fn (in_capture_buffer: ?*common_defs.AkAudioBuffer, in_id_output: typedefs.AkOutputDeviceID, cookie: ?*anyopaque) callconv(.c) void;
