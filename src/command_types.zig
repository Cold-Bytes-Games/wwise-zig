const ak_3d_objects = @import("ak_3d_objects.zig");
const c = @import("wwise_c");
const callback_types = @import("callback_types.zig");
const enums = @import("enums.zig");
const sound_engine_types = @import("sound_engine_types.zig");
const SpatialAudio = if (wwise_options.use_spatial_audio) @import("SpatialAudio.zig") else void;
const speaker_config = @import("speaker_config.zig");
const std = @import("std");
const typedefs = @import("typedefs.zig");
const wwise_options = @import("wwise_options");
const zig = @import("zig.zig");

pub const AkCommand = enum(zig.DefaultEnumType) {
    end_of_buffer = c.AkCommand_EndOfBuffer,
    post_event = c.AkCommand_PostEvent,
    register_game_object = c.AkCommand_RegisterGameObject,
    unregister_game_object = c.AkCommand_UnregisterGameObject,
    callback = c.AkCommand_Callback,
    set_rtpc = c.AkCommand_SetRTPC,
    reset_rtpc = c.AkCommand_ResetRTPC,
    set_position = c.AkCommand_SetPosition,
    set_listeners = c.AkCommand_SetListeners,
    set_default_listeners = c.AkCommand_SetDefaultListeners,
    reset_listeners = c.AkCommand_ResetListeners,
    set_listener_spatialization = c.AkCommand_SetListenerSpatialization,
    set_game_object_aux_send_values = c.AkCommand_SetGameObjectAuxSendValues,
    set_game_object_output_bus_volume = c.AkCommand_SetGameObjectOutputBusVolume,
    set_object_obstruction_and_occlusion = c.AkCommand_SetObjectObstructionAndOcclusion,
    set_multiple_obstruction_and_occlusion = c.AkCommand_SetMultipleObstructionAndOcclusion,
    set_scaling_factor = c.AkCommand_SetScalingFactor,
    set_multiple_positions = c.AkCommand_SetMultiplePositions,
    set_distance_probe = c.AkCommand_SetDistanceProbe,
    stop_all = c.AkCommand_StopAll,
    execute_action_on_event = c.AkCommand_ExecuteActionOnEvent,
    execute_action_on_playing_id = c.AkCommand_ExecuteActionOnPlayingID,
    seek_on_event = c.AkCommand_SeekOnEvent,
    set_state = c.AkCommand_SetState,
    set_switch = c.AkCommand_SetSwitch,
    post_trigger = c.AkCommand_PostTrigger,
    post_midi_on_event = c.AkCommand_PostMIDIOnEvent,
    stop_midi_on_event = c.AkCommand_StopMIDIOnEvent,

    dynamic_sequence_open = c.AkCommand_DynamicSequence_Open,
    dynamic_sequence_op = c.AkCommand_DynamicSequence_Op,
    dynamic_sequence_seek = c.AkCommand_DynamicSequence_Seek,

    add_output = c.AkCommand_AddOutput,
    remove_output = c.AkCommand_RemoveOutput,
    replace_output = c.AkCommand_ReplaceOutput,
    set_bus_audio_device = c.AkCommand_SetBusAudioDevice,
    set_bus_config = c.AkCommand_SetBusConfig,
    reset_bus_config = c.AkCommand_ResetBusConfig,
    set_effect = c.AkCommand_SetEffect,
    set_output_volume = c.AkCommand_SetOutputVolume,
    set_panning_rule = c.AkCommand_SetPanningRule,
    set_speaker_angles = c.AkCommand_SetSpeakerAngles,
    control_output_capture = c.AkCommand_ControlOutputCapture,
    add_output_capture_marker = c.AkCommand_AddOutputCaptureMarker,
    control_offline_rendering = c.AkCommand_ControlOfflineRendering,
    set_random_seed = c.AkCommand_SetRandomSeed,
    control_event_stream_cache = c.AkCommand_ControlEventStreamCache,
    control_suspended_state = c.AkCommand_ControlSuspendedState,
    mute_background_music = c.AkCommand_MuteBackgroundMusic,
    send_plugin_custom_game_data = c.AkCommand_SendPluginCustomGameData,
    set_sidechain_mix_config = c.AkCommand_SetSidechainMixConfig,
    reset_global_values = c.AkCommand_ResetGlobalValues,

    sa_register_listener = c.AkCommand_SA_RegisterListener,
    sa_unregister_listener = c.AkCommand_SA_UnregisterListener,
    sa_set_image_source = c.AkCommand_SA_SetImageSource,
    sa_remove_image_source = c.AkCommand_SA_RemoveImageSource,
    sa_clear_image_sources = c.AkCommand_SA_ClearImageSources,
    sa_set_geometry = c.AkCommand_SA_SetGeometry,
    sa_remove_geometry = c.AkCommand_SA_RemoveGeometry,
    sa_set_geometry_instance = c.AkCommand_SA_SetGeometryInstance,
    sa_remove_geometry_instance = c.AkCommand_SA_RemoveGeometryInstance,
    sa_set_room = c.AkCommand_SA_SetRoom,
    sa_remove_room = c.AkCommand_SA_RemoveRoom,
    sa_set_portal = c.AkCommand_SA_SetPortal,
    sa_remove_portal = c.AkCommand_SA_RemovePortal,
    sa_set_portal_obstruction_and_occlusion = c.AkCommand_SA_SetPortalObstructionAndOcclusion,
    sa_set_game_object_to_portal_obstruction = c.AkCommand_SA_SetGameObjectToPortalObstruction,
    sa_set_portal_to_portal_obstruction = c.AkCommand_SA_SetPortalToPortalObstruction,
    sa_set_reverb_zone = c.AkCommand_SA_SetReverbZone,
    sa_remove_reverb_zone = c.AkCommand_SA_RemoveReverbZone,
    sa_set_game_object_in_room = c.AkCommand_SA_SetGameObjectInRoom,
    sa_unset_game_object_in_room = c.AkCommand_SA_UnsetGameObjectInRoom,
    sa_set_game_object_radius = c.AkCommand_SA_SetGameObjectRadius,
    sa_set_adjacent_room_bleed = c.AkCommand_SA_SetAdjacentRoomBleed,
    sa_set_early_reflections_aux_send = c.AkCommand_SA_SetEarlyReflectionsAuxSend,
    sa_set_early_reflections_volume = c.AkCommand_SA_SetEarlyReflectionsVolume,
    sa_set_reflections_order = c.AkCommand_SA_SetReflectionsOrder,
    sa_set_diffraction_order = c.AkCommand_SA_SetDiffractionOrder,
    sa_set_max_global_reflection_paths = c.AkCommand_SA_SetMaxGlobalReflectionPaths,
    sa_set_max_emitter_room_aux_sends = c.AkCommand_SA_SetMaxEmitterRoomAuxSends,
    sa_set_max_diffraction_paths = c.AkCommand_SA_SetMaxDiffractionPaths,
    sa_set_smoothing_constant = c.AkCommand_SA_SetSmoothingConstant,
    sa_set_transmission_operation = c.AkCommand_SA_SetTransmissionOperation,
    sa_set_number_of_primary_rays = c.AkCommand_SA_SetNumberOfPrimaryRays,
    sa_set_load_balancing_spread = c.AkCommand_SA_SetLoadBalancingSpread,
    sa_reset_stochastic_engine = c.AkCommand_SA_ResetStochasticEngine,
};

pub const AkCommandCallbackFunc = ?*const fn (in_cookie: ?*anyopaque) callconv(.c) void;

pub const AkCmd_PostEvent = extern struct {
    playing_id: typedefs.AkPlayingID align(1) = 0,
    event_id: typedefs.AkUniqueID align(1) = 0,
    game_object_id: typedefs.AkGameObjectID align(1) = 0,
    action_target_playing_id: typedefs.AkPlayingID align(1) = 0,
    flags: callback_types.AkCallbackType align(1) = .{},
    callback: callback_types.AkEventCallbackFunc align(1) = null,
    callback_cookie: ?*anyopaque align(1) = null,
    num_external_sources: u32 align(1) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_PostEvent
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_PostEvent) AkCmd_PostEvent {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_PostEvent) c.AkCmd_PostEvent {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_PostEvent) == @sizeOf(c.AkCmd_PostEvent));
    // }

    pub const COMMAND_TYPE: AkCommand = .post_event;
};

pub const AkCmd_RegisterGameObject = extern struct {
    game_object_id: typedefs.AkGameObjectID = 0,

    pub inline fn fromC(value: c.AkCmd_RegisterGameObject) AkCmd_RegisterGameObject {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_RegisterGameObject) c.AkCmd_RegisterGameObject {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_RegisterGameObject) == @sizeOf(c.AkCmd_RegisterGameObject));
    }

    pub const COMMAND_TYPE: AkCommand = .register_game_object;
};

pub const AkCmd_UnregisterGameObject = extern struct {
    game_object_id: typedefs.AkGameObjectID = 0,

    pub inline fn fromC(value: c.AkCmd_UnregisterGameObject) AkCmd_UnregisterGameObject {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_UnregisterGameObject) c.AkCmd_UnregisterGameObject {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_UnregisterGameObject) == @sizeOf(c.AkCmd_UnregisterGameObject));
    }

    pub const COMMAND_TYPE: AkCommand = .unregister_game_object;
};

pub const AkCmd_Callback = extern struct {
    callback: AkCommandCallbackFunc = null,
    callback_cookie: ?*anyopaque = null,

    pub inline fn fromC(value: c.AkCmd_Callback) AkCmd_Callback {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_Callback) c.AkCmd_Callback {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_Callback) == @sizeOf(c.AkCmd_Callback));
    }

    pub const COMMAND_TYPE: AkCommand = .callback;
};

pub const AkCmd_SetRTPC = extern struct {
    rtpc_id: typedefs.AkRtpcID align(1) = 0,
    rtpc_value: typedefs.AkRtpcValue align(1) = 0,
    game_object_id: typedefs.AkGameObjectID align(1) = 0,
    playing_id: typedefs.AkPlayingID align(1) = 0,
    transition_time: typedefs.AkTimeMs align(1) = 0,
    fade_curve: enums.AkCurveInterpolation_u16 align(1) = .constant,
    bypass_internal_value_interpolation: u16 align(1) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SetRTPC
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SetRTPC) AkCmd_SetRTPC {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SetRTPC) c.AkCmd_SetRTPC {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SetRTPC) == @sizeOf(c.AkCmd_SetRTPC));
    // }

    pub const COMMAND_TYPE: AkCommand = .set_rtpc;
};

pub const AkCmd_ResetRTPC = extern struct {
    rtpc_id: typedefs.AkRtpcID align(1) = 0,
    game_object_id: typedefs.AkGameObjectID align(1) = 0,
    playing_id: typedefs.AkPlayingID align(1) = 0,
    transition_time: typedefs.AkTimeMs align(1) = 0,
    fade_curve: enums.AkCurveInterpolation_u16 align(1) = .constant,
    bypass_internal_value_interpolation: u16 align(1) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_ResetRTPC
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_ResetRTPC) AkCmd_ResetRTPC {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_ResetRTPC) c.AkCmd_ResetRTPC {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_ResetRTPC) == @sizeOf(c.AkCmd_ResetRTPC));
    // }

    pub const COMMAND_TYPE: AkCommand = .reset_rtpc;
};

pub const AkCmd_SetPosition = extern struct {
    game_object_id: typedefs.AkGameObjectID align(1) = 0,
    position: ak_3d_objects.AkWorldTransform align(1) = .{},
    flags: u32 align(1) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SetPosition
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SetPosition) AkCmd_SetPosition {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SetPosition) c.AkCmd_SetPosition {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SetPosition) == @sizeOf(c.AkCmd_SetPosition));
    // }

    pub const COMMAND_TYPE: AkCommand = .set_position;
};

pub const AkCmd_SetMultiplePositions = extern struct {
    game_object_id: typedefs.AkGameObjectID align(1) = 0,
    flags: u32 align(1) = 0,
    multi_position_type: u32 align(1) = 0,
    num_positions: u32 align(1) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SetMultiplePositions
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SetMultiplePositions) AkCmd_SetMultiplePositions {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SetMultiplePositions) c.AkCmd_SetMultiplePositions {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SetMultiplePositions) == @sizeOf(c.AkCmd_SetMultiplePositions));
    // }

    pub const COMMAND_TYPE: AkCommand = .set_multiple_positions;
};

pub const AkCmd_SetListeners = extern struct {
    game_object_id: typedefs.AkGameObjectID align(1) = 0,
    operation: u32 align(1) = 0,
    num_listener_ids: u32 align(1) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SetListeners
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SetListeners) AkCmd_SetListeners {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SetListeners) c.AkCmd_SetListeners {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SetListeners) == @sizeOf(c.AkCmd_SetListeners));
    // }

    pub const COMMAND_TYPE: AkCommand = .set_listeners;
};

pub const AkCmd_SetDefaultListeners = extern struct {
    operation: u32 = 0,
    num_listener_i_ds: u32 = 0,

    pub inline fn fromC(value: c.AkCmd_SetDefaultListeners) AkCmd_SetDefaultListeners {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SetDefaultListeners) c.AkCmd_SetDefaultListeners {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SetDefaultListeners) == @sizeOf(c.AkCmd_SetDefaultListeners));
    }

    pub const COMMAND_TYPE: AkCommand = .set_default_listeners;
};

pub const AkCmd_ResetListeners = extern struct {
    game_object_id: typedefs.AkGameObjectID = 0,

    pub inline fn fromC(value: c.AkCmd_ResetListeners) AkCmd_ResetListeners {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_ResetListeners) c.AkCmd_ResetListeners {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_ResetListeners) == @sizeOf(c.AkCmd_ResetListeners));
    }

    pub const COMMAND_TYPE: AkCommand = .reset_listeners;
};

pub const AkCmd_SetListenerSpatialization = extern struct {
    listener_id: typedefs.AkGameObjectID = 0,
    channel_config: speaker_config.AkChannelConfig = .{},
    is_spatialized: u32 = 0,

    pub inline fn fromC(value: c.AkCmd_ResetListeners) AkCmd_ResetListeners {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_ResetListeners) c.AkCmd_ResetListeners {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_ResetListeners) == @sizeOf(c.AkCmd_ResetListeners));
    }

    pub const COMMAND_TYPE: AkCommand = .set_listener_spatialization;
};

pub const AkCmd_SetGameObjectAuxSendValues = extern struct {
    game_object_id: typedefs.AkGameObjectID align(1) = 0,
    num_values: u32 align(1) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SetGameObjectAuxSendValues
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SetGameObjectAuxSendValues) AkCmd_SetGameObjectAuxSendValues {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SetGameObjectAuxSendValues) c.AkCmd_SetGameObjectAuxSendValues {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SetGameObjectAuxSendValues) == @sizeOf(c.AkCmd_SetGameObjectAuxSendValues));
    // }

    pub const COMMAND_TYPE: AkCommand = .set_game_object_aux_send_values;
};

pub const AkCmd_SetGameObjectOutputBusVolume = extern struct {
    emitter_id: typedefs.AkGameObjectID align(1) = 0,
    listener_id: typedefs.AkGameObjectID align(1) = 0,
    control_value: f32 align(1) = 0.0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SetGameObjectOutputBusVolume
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SetGameObjectOutputBusVolume) AkCmd_SetGameObjectOutputBusVolume {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SetGameObjectOutputBusVolume) c.AkCmd_SetGameObjectOutputBusVolume {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SetGameObjectOutputBusVolume) == @sizeOf(c.AkCmd_SetGameObjectOutputBusVolume));
    // }

    pub const COMMAND_TYPE: AkCommand = .set_game_object_output_bus_volume;
};

pub const AkCmd_SetScalingFactor = extern struct {
    game_object_id: typedefs.AkGameObjectID align(1) = 0,
    scaling_factor: f32 align(1) = 0.0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SetScalingFactor
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SetScalingFactor) AkCmd_SetScalingFactor {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SetScalingFactor) c.AkCmd_SetScalingFactor {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SetScalingFactor) == @sizeOf(c.AkCmd_SetScalingFactor));
    // }

    pub const COMMAND_TYPE: AkCommand = .set_scaling_factor;
};

pub const AkCmd_SetObjectObstructionAndOcclusion = extern struct {
    emitter_id: typedefs.AkGameObjectID = 0,
    listener_id: typedefs.AkGameObjectID = 0,
    value: sound_engine_types.AkObstructionOcclusionValues = .{},

    pub inline fn fromC(value: c.AkCmd_SetObjectObstructionAndOcclusion) AkCmd_SetObjectObstructionAndOcclusion {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SetObjectObstructionAndOcclusion) c.AkCmd_SetObjectObstructionAndOcclusion {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SetObjectObstructionAndOcclusion) == @sizeOf(c.AkCmd_SetObjectObstructionAndOcclusion));
    }

    pub const COMMAND_TYPE: AkCommand = .set_object_obstruction_and_occlusion;
};

pub const AkCmd_SetMultipleObstructionAndOcclusion = extern struct {
    emitter_id: typedefs.AkGameObjectID align(1) = 0,
    listener_id: typedefs.AkGameObjectID align(1) = 0,
    num_values: u32 align(1) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SetMultipleObstructionAndOcclusion
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SetMultipleObstructionAndOcclusion) AkCmd_SetMultipleObstructionAndOcclusion {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SetMultipleObstructionAndOcclusion) c.AkCmd_SetMultipleObstructionAndOcclusion {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SetMultipleObstructionAndOcclusion) == @sizeOf(c.AkCmd_SetMultipleObstructionAndOcclusion));
    // }

    pub const COMMAND_TYPE: AkCommand = .set_multiple_obstruction_and_occlusion;
};

pub const AkCmd_SetDistanceProbe = extern struct {
    game_object_id: typedefs.AkGameObjectID = 0,
    distance_probe_id: typedefs.AkGameObjectID = 0,

    pub inline fn fromC(value: c.AkCmd_SetDistanceProbe) AkCmd_SetDistanceProbe {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SetDistanceProbe) c.AkCmd_SetDistanceProbe {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SetDistanceProbe) == @sizeOf(c.AkCmd_SetDistanceProbe));
    }

    pub const COMMAND_TYPE: AkCommand = .set_distance_probe;
};

pub const AkCmd_StopAll = extern struct {
    game_object_id: typedefs.AkGameObjectID = 0,

    pub inline fn fromC(value: c.AkCmd_StopAll) AkCmd_StopAll {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_StopAll) c.AkCmd_StopAll {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_StopAll) == @sizeOf(c.AkCmd_StopAll));
    }

    pub const COMMAND_TYPE: AkCommand = .stop_all;
};

pub const AkCmd_ExecuteActionOnEvent = extern struct {
    event_id: typedefs.AkUniqueID align(1) = 0,
    game_object_id: typedefs.AkGameObjectID align(1) = 0,
    transition_time: typedefs.AkTimeMs align(1) = 0,
    playing_id: typedefs.AkPlayingID align(1) = 0,
    fade_curve: enums.AkCurveInterpolation_u8 align(1) = .constant,
    action_type: enums.AkActionOnEventType_u8 align(1) = .stop,
    _zig_padding: u16 align(1) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_ExecuteActionOnEvent
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_ExecuteActionOnEvent) AkCmd_ExecuteActionOnEvent {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_ExecuteActionOnEvent) c.AkCmd_ExecuteActionOnEvent {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_ExecuteActionOnEvent) == @sizeOf(c.AkCmd_ExecuteActionOnEvent));
    // }

    pub const COMMAND_TYPE: AkCommand = .execute_action_on_event;
};

pub const AkCmd_ExecuteActionOnPlayingID = extern struct {
    action_type: enums.AkActionOnEventType align(4) = .stop,
    playing_id: typedefs.AkPlayingID align(4) = 0,
    transition_time: typedefs.AkTimeMs align(4) = 0,
    fade_curve: enums.AkCurveInterpolation_u8 align(4) = .constant,

    // mlarouche: We can't convert directly from the translate-c AkCmd_ExecuteActionOnPlayingID
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_ExecuteActionOnPlayingID) AkCmd_ExecuteActionOnPlayingID {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_ExecuteActionOnPlayingID) c.AkCmd_ExecuteActionOnPlayingID {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_ExecuteActionOnPlayingID) == @sizeOf(c.AkCmd_ExecuteActionOnPlayingID));
    // }

    pub const COMMAND_TYPE: AkCommand = .execute_action_on_playing_id;
};

pub const AkCmd_SeekOnEvent = extern struct {
    event_id: typedefs.AkUniqueID = 0,
    position: extern union {
        absolute: typedefs.AkTimeMs,
        relative: f32,
    } = .{
        .relative = 0.0,
    },
    game_object_id: typedefs.AkGameObjectID = 0,
    playing_id: typedefs.AkPlayingID = 0,
    is_position_relative: u8 = 0,
    seek_to_nearest_marker: u8 = 0,

    pub inline fn fromC(value: c.AkCmd_SeekOnEvent) AkCmd_SeekOnEvent {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SeekOnEvent) c.AkCmd_SeekOnEvent {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SeekOnEvent) == @sizeOf(c.AkCmd_SeekOnEvent));
    }

    pub const COMMAND_TYPE: AkCommand = .seek_on_event;
};

pub const AkCmd_SetState = extern struct {
    state_group_id: typedefs.AkStateGroupID = 0,
    state_id: typedefs.AkStateID = 0,

    pub inline fn fromC(value: c.AkCmd_SetState) AkCmd_SetState {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SetState) c.AkCmd_SetState {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SetState) == @sizeOf(c.AkCmd_SetState));
    }

    pub const COMMAND_TYPE: AkCommand = .set_state;
};

pub const AkCmd_SetSwitch = extern struct {
    switch_group_id: typedefs.AkSwitchGroupID = 0,
    switch_id: typedefs.AkSwitchStateID = 0,
    game_object_id: typedefs.AkGameObjectID = 0,

    pub inline fn fromC(value: c.AkCmd_SetSwitch) AkCmd_SetSwitch {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SetSwitch) c.AkCmd_SetSwitch {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SetSwitch) == @sizeOf(c.AkCmd_SetSwitch));
    }

    pub const COMMAND_TYPE: AkCommand = .set_switch;
};

pub const AkCmd_PostTrigger = extern struct {
    trigger_id: typedefs.AkTriggerID align(4) = 0,
    game_object_id: typedefs.AkGameObjectID align(4) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_PostTrigger
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_PostTrigger) AkCmd_PostTrigger {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_PostTrigger) c.AkCmd_PostTrigger {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_PostTrigger) == @sizeOf(c.AkCmd_PostTrigger));
    // }

    pub const COMMAND_TYPE: AkCommand = .post_trigger;
};

pub const AkCmd_PostMIDIOnEvent = extern struct {
    playing_id: typedefs.AkPlayingID align(1) = 0,
    event_id: typedefs.AkUniqueID align(1) = 0,
    game_object_id: typedefs.AkGameObjectID align(1) = 0,
    flags: callback_types.AkCallbackType align(1) = .{},
    callback: callback_types.AkEventCallbackFunc align(1) = null,
    callback_cookie: ?*anyopaque align(1) = null,
    is_offset_absolute: u8 align(1) = 0,
    is_new_sequence: u8 align(1) = 0,
    num_midi_posts: u32 align(4) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_PostMIDIOnEvent
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_PostMIDIOnEvent) AkCmd_PostMIDIOnEvent {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_PostMIDIOnEvent) c.AkCmd_PostMIDIOnEvent {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_PostMIDIOnEvent) == @sizeOf(c.AkCmd_PostMIDIOnEvent));
    // }

    pub const COMMAND_TYPE: AkCommand = .post_midi_on_event;
};

pub const AkCmd_StopMIDIOnEvent = extern struct {
    playing_id: typedefs.AkPlayingID = 0,
    event_id: typedefs.AkUniqueID = 0,
    game_object_id: typedefs.AkGameObjectID = 0,

    pub inline fn fromC(value: c.AkCmd_StopMIDIOnEvent) AkCmd_StopMIDIOnEvent {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_StopMIDIOnEvent) c.AkCmd_StopMIDIOnEvent {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_StopMIDIOnEvent) == @sizeOf(c.AkCmd_StopMIDIOnEvent));
    }

    pub const COMMAND_TYPE: AkCommand = .stop_midi_on_event;
};

pub const AkCmd_DynamicSequence_Open = extern struct {
    playing_id: typedefs.AkPlayingID align(4) = 0,
    game_object_id: typedefs.AkGameObjectID align(4) = 0,
    type: enums.AkDynamicSequenceType_u8 align(4) = .sample_accurate,
    flags: callback_types.AkCallbackType align(4) = .{},
    callback: callback_types.AkEventCallbackFunc align(4) = null,
    callback_cookie: ?*anyopaque align(4) = null,

    // mlarouche: We can't convert directly from the translate-c AkCmd_DynamicSequence_Open
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_DynamicSequence_Open) AkCmd_DynamicSequence_Open {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_DynamicSequence_Open) c.AkCmd_DynamicSequence_Open {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_DynamicSequence_Open) == @sizeOf(c.AkCmd_DynamicSequence_Open));
    // }

    pub const COMMAND_TYPE: AkCommand = .dynamic_sequence_open;
};

pub const AkCmd_DynamicSequence_Op = extern struct {
    playing_id: typedefs.AkPlayingID = 0,
    operation: enums.AkDynamicSequenceOp = .play,
    transition_time: typedefs.AkTimeMs = 0,
    fade_curve: enums.AkCurveInterpolation_u8 = .constant,

    pub inline fn fromC(value: c.AkCmd_DynamicSequence_Op) AkCmd_DynamicSequence_Op {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_DynamicSequence_Op) c.AkCmd_DynamicSequence_Op {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_DynamicSequence_Op) == @sizeOf(c.AkCmd_DynamicSequence_Op));
    }

    pub const COMMAND_TYPE: AkCommand = .dynamic_sequence_op;
};

pub const AkCmd_DynamicSequence_Seek = extern struct {
    playing_id: typedefs.AkPlayingID = 0,
    position: extern union {
        absolute: typedefs.AkTimeMs,
        relative: f32,
    } = .{ .relative = 0.0 },
    is_position_relative: u8 = 0,
    seek_to_nearest_marker: u8 = 0,

    pub inline fn fromC(value: c.AkCmd_DynamicSequence_Seek) AkCmd_DynamicSequence_Seek {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_DynamicSequence_Seek) c.AkCmd_DynamicSequence_Seek {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_DynamicSequence_Seek) == @sizeOf(c.AkCmd_DynamicSequence_Seek));
    }

    pub const COMMAND_TYPE: AkCommand = .dynamic_sequence_seek;
};

pub const AkCmd_AddOutput = extern struct {
    settings: sound_engine_types.AkOutputSettings = .{},
    num_listener_ids: u32 = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_AddOutput
    // because it use bitfields on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_AddOutput) AkCmd_AddOutput {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_AddOutput) c.AkCmd_AddOutput {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_AddOutput) == @sizeOf(c.AkCmd_AddOutput));
    // }

    pub const COMMAND_TYPE: AkCommand = .add_output;
};

pub const AkCmd_RemoveOutput = extern struct {
    output_device_id: typedefs.AkOutputDeviceID = 0,

    pub inline fn fromC(value: c.AkCmd_RemoveOutput) AkCmd_RemoveOutput {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_RemoveOutput) c.AkCmd_RemoveOutput {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_RemoveOutput) == @sizeOf(c.AkCmd_RemoveOutput));
    }

    pub const COMMAND_TYPE: AkCommand = .remove_output;
};

pub const AkCmd_ReplaceOutput = extern struct {
    output_device_id: typedefs.AkOutputDeviceID = 0,
    settings: sound_engine_types.AkOutputSettings = .{},

    // mlarouche: We can't convert directly from the translate-c AkCmd_ReplaceOutput
    // because it use bitfields on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_ReplaceOutput) AkCmd_ReplaceOutput {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_ReplaceOutput) c.AkCmd_ReplaceOutput {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_ReplaceOutput) == @sizeOf(c.AkCmd_ReplaceOutput));
    // }

    pub const COMMAND_TYPE: AkCommand = .replace_output;
};

pub const AkCmd_SetBusAudioDevice = extern struct {
    bus_id: typedefs.AkUniqueID = 0,
    audio_device_shareset_id: typedefs.AkUniqueID = 0,

    pub inline fn fromC(value: c.AkCmd_SetBusAudioDevice) AkCmd_SetBusAudioDevice {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SetBusAudioDevice) c.AkCmd_SetBusAudioDevice {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SetBusAudioDevice) == @sizeOf(c.AkCmd_SetBusAudioDevice));
    }

    pub const COMMAND_TYPE: AkCommand = .set_bus_audio_device;
};

pub const AkCmd_SetBusConfig = extern struct {
    bus_id: typedefs.AkUniqueID = 0,
    channel_config: speaker_config.AkChannelConfig = .{},

    // mlarouche: We can't convert directly from the translate-c AkCmd_SetBusConfig
    // because it use bitfields on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SetBusConfig) AkCmd_SetBusConfig {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SetBusConfig) c.AkCmd_SetBusConfig {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SetBusConfig) == @sizeOf(c.AkCmd_SetBusConfig));
    // }

    pub const COMMAND_TYPE: AkCommand = .set_bus_config;
};

pub const AkCmd_ResetBusConfig = extern struct {
    bus_id: typedefs.AkUniqueID = 0,

    pub inline fn fromC(value: c.AkCmd_ResetBusConfig) AkCmd_ResetBusConfig {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_ResetBusConfig) c.AkCmd_ResetBusConfig {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_ResetBusConfig) == @sizeOf(c.AkCmd_ResetBusConfig));
    }

    pub const COMMAND_TYPE: AkCommand = .reset_bus_config;
};

pub const AkCmd_ResetGlobalValues = extern struct {
    unused: u32 = 0,

    pub inline fn fromC(value: c.AkCmd_ResetGlobalValues) AkCmd_ResetGlobalValues {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_ResetGlobalValues) c.AkCmd_ResetGlobalValues {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_ResetGlobalValues) == @sizeOf(c.AkCmd_ResetGlobalValues));
    }

    pub const COMMAND_TYPE: AkCommand = .reset_global_values;
};

pub const AkCmd_SetSidechainMixConfig = extern struct {
    sidechain_mix_id: typedefs.AkUniqueID = 0,
    channel_config: speaker_config.AkChannelConfig = .{},

    // mlarouche: We can't convert directly from the translate-c AkCmd_SetSidechainMixConfig
    // because it use bitfields on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SetSidechainMixConfig) AkCmd_SetSidechainMixConfig {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SetSidechainMixConfig) c.AkCmd_SetSidechainMixConfig {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SetSidechainMixConfig) == @sizeOf(c.AkCmd_SetSidechainMixConfig));
    // }

    pub const COMMAND_TYPE: AkCommand = .set_sidechain_mix_config;
};

pub const AkCmd_SetEffect = extern struct {
    node_id: u64 = 0,
    node_type: enums.AkNodeType = .default,
    fx_index: u8 = 0,
    fx_shareset_id: typedefs.AkUniqueID = 0,

    pub inline fn fromC(value: c.AkCmd_SetEffect) AkCmd_SetEffect {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SetEffect) c.AkCmd_SetEffect {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SetEffect) == @sizeOf(c.AkCmd_SetEffect));
    }

    pub const COMMAND_TYPE: AkCommand = .set_effect;
};

pub const AkCmd_SetOutputVolume = extern struct {
    output_id: typedefs.AkOutputDeviceID align(4) = 0,
    volume: f32 align(4) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SetOutputVolume
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SetOutputVolume) AkCmd_SetOutputVolume {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SetOutputVolume) c.AkCmd_SetOutputVolume {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SetOutputVolume) == @sizeOf(c.AkCmd_SetOutputVolume));
    // }

    pub const COMMAND_TYPE: AkCommand = .set_output_volume;
};

pub const AkCmd_SetPanningRule = extern struct {
    panning_rule: enums.AkPanningRule_u8 align(4) = .speakers,
    output_id: typedefs.AkOutputDeviceID align(4) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SetPanningRule
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SetPanningRule) AkCmd_SetPanningRule {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SetPanningRule) c.AkCmd_SetPanningRule {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SetPanningRule) == @sizeOf(c.AkCmd_SetPanningRule));
    // }

    pub const COMMAND_TYPE: AkCommand = .set_panning_rule;
};

pub const AkCmd_SetSpeakerAngles = extern struct {
    num_angles: u32 = 0,
    height_angle: f32 = 0.0,
    output_id: typedefs.AkOutputDeviceID = 0,

    pub inline fn fromC(value: c.AkCmd_SetSpeakerAngles) AkCmd_SetSpeakerAngles {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SetSpeakerAngles) c.AkCmd_SetSpeakerAngles {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SetSpeakerAngles) == @sizeOf(c.AkCmd_SetSpeakerAngles));
    }

    pub const COMMAND_TYPE: AkCommand = .set_speaker_angles;
};

pub const AkCmd_ControlOutputCapture = extern struct {
    is_enabled: u32 = 0,

    pub inline fn fromC(value: c.AkCmd_ControlOutputCapture) AkCmd_ControlOutputCapture {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_ControlOutputCapture) c.AkCmd_ControlOutputCapture {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_ControlOutputCapture) == @sizeOf(c.AkCmd_ControlOutputCapture));
    }

    pub const COMMAND_TYPE: AkCommand = .control_output_capture;
};

pub const AkCmd_AddOutputCaptureMarker = extern struct {
    marker_data_size: u32 = 0,
    sample_pos: u32 = 0,

    pub inline fn fromC(value: c.AkCmd_AddOutputCaptureMarker) AkCmd_AddOutputCaptureMarker {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_AddOutputCaptureMarker) c.AkCmd_AddOutputCaptureMarker {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_AddOutputCaptureMarker) == @sizeOf(c.AkCmd_AddOutputCaptureMarker));
    }

    pub const COMMAND_TYPE: AkCommand = .add_output_capture_marker;
};

pub const AkCmd_ControlOfflineRendering = extern struct {
    is_enabled: u32 = 0,
    frame_time_in_seconds: f32 = 0,

    pub inline fn fromC(value: c.AkCmd_ControlOfflineRendering) AkCmd_ControlOfflineRendering {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_ControlOfflineRendering) c.AkCmd_ControlOfflineRendering {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_ControlOfflineRendering) == @sizeOf(c.AkCmd_ControlOfflineRendering));
    }

    pub const COMMAND_TYPE: AkCommand = .control_offline_rendering;
};

pub const AkCmd_SetRandomSeed = extern struct {
    seed_value: u32 = 0,

    pub inline fn fromC(value: c.AkCmd_SetRandomSeed) AkCmd_SetRandomSeed {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SetRandomSeed) c.AkCmd_SetRandomSeed {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SetRandomSeed) == @sizeOf(c.AkCmd_SetRandomSeed));
    }

    pub const COMMAND_TYPE: AkCommand = .set_random_seed;
};

pub const AkCmd_ControlEventStreamCache = extern struct {
    event_id: typedefs.AkUniqueID = 0,
    is_cached: u8 = 0,
    active_priority: typedefs.AkPriority = 0,
    inactive_priority: typedefs.AkPriority = 0,

    pub inline fn fromC(value: c.AkCmd_ControlEventStreamCache) AkCmd_ControlEventStreamCache {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_ControlEventStreamCache) c.AkCmd_ControlEventStreamCache {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_ControlEventStreamCache) == @sizeOf(c.AkCmd_ControlEventStreamCache));
    }

    pub const COMMAND_TYPE: AkCommand = .control_event_stream_cache;
};

pub const AkCmd_ControlSuspendedState = extern struct {
    is_suspended: u8 = 0,
    render_while_suspended: u8 = 0,
    transition_time: typedefs.AkTimeMs = 0,

    pub inline fn fromC(value: c.AkCmd_ControlSuspendedState) AkCmd_ControlSuspendedState {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_ControlSuspendedState) c.AkCmd_ControlSuspendedState {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_ControlSuspendedState) == @sizeOf(c.AkCmd_ControlSuspendedState));
    }

    pub const COMMAND_TYPE: AkCommand = .control_suspended_state;
};

pub const AkCmd_MuteBackgroundMusic = extern struct {
    is_muted: u32 = 0,

    pub inline fn fromC(value: c.AkCmd_MuteBackgroundMusic) AkCmd_MuteBackgroundMusic {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_MuteBackgroundMusic) c.AkCmd_MuteBackgroundMusic {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_MuteBackgroundMusic) == @sizeOf(c.AkCmd_MuteBackgroundMusic));
    }

    pub const COMMAND_TYPE: AkCommand = .mute_background_music;
};

pub const AkCmd_SendPluginCustomGameData = extern struct {
    bus_id: typedefs.AkUniqueID align(4) = 0,
    game_object_id: typedefs.AkGameObjectID align(4) = 0,
    plugin_type: enums.AkPluginType align(4) = .none,
    company_id: u32 align(4) = 0,
    plugin_id: u32 align(4) = 0,
    data_size: u32 align(4) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SetPanningRule
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SendPluginCustomGameData) AkCmd_SendPluginCustomGameData {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SendPluginCustomGameData) c.AkCmd_SendPluginCustomGameData {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SendPluginCustomGameData) == @sizeOf(c.AkCmd_SendPluginCustomGameData));
    // }

    pub const COMMAND_TYPE: AkCommand = .send_plugin_custom_game_data;
};

pub const AkCmd_SA_RegisterListener = if (wwise_options.use_spatial_audio) extern struct {
    game_object_id: typedefs.AkGameObjectID align(4) = 0,
    primary_listener: bool align(4) = false,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SA_RegisterListener
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SA_RegisterListener) AkCmd_SA_RegisterListener {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SA_RegisterListener) c.AkCmd_SA_RegisterListener {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SA_RegisterListener) == @sizeOf(c.AkCmd_SA_RegisterListener));
    // }

    pub const COMMAND_TYPE: AkCommand = .sa_register_listener;
} else extern struct {};

pub const AkCmd_SA_UnregisterListener = if (wwise_options.use_spatial_audio) extern struct {
    game_object_id: typedefs.AkGameObjectID = 0,

    pub inline fn fromC(value: c.AkCmd_SA_UnregisterListener) AkCmd_SA_UnregisterListener {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_UnregisterListener) c.AkCmd_SA_UnregisterListener {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_UnregisterListener) == @sizeOf(c.AkCmd_SA_UnregisterListener));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_unregister_listener;
} else extern struct {};

pub const AkCmd_SA_SetImageSource = if (wwise_options.use_spatial_audio) extern struct {
    image_source_id: typedefs.AkImageSourceID align(1) = 0,
    info: SpatialAudio.AkImageSourceSettings align(1) = .{},
    aux_bus_id: typedefs.AkUniqueID align(1) = 0,
    game_object_id: typedefs.AkGameObjectID align(1) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SA_SetImageSource
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SA_SetImageSource) AkCmd_SA_SetImageSource {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SA_SetImageSource) c.AkCmd_SA_SetImageSource {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SA_SetImageSource) == @sizeOf(c.AkCmd_SA_SetImageSource));
    // }

    pub const COMMAND_TYPE: AkCommand = .sa_set_image_source;
} else extern struct {};

pub const AkCmd_SA_RemoveImageSource = if (wwise_options.use_spatial_audio) extern struct {
    image_source_id: typedefs.AkUniqueID = 0,
    aux_bus_id: typedefs.AkUniqueID = 0,
    game_object_id: typedefs.AkGameObjectID = 0,

    pub inline fn fromC(value: c.AkCmd_SA_RemoveImageSource) AkCmd_SA_RemoveImageSource {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_RemoveImageSource) c.AkCmd_SA_RemoveImageSource {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_RemoveImageSource) == @sizeOf(c.AkCmd_SA_RemoveImageSource));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_remove_image_source;
} else extern struct {};

pub const AkCmd_SA_ClearImageSources = if (wwise_options.use_spatial_audio) extern struct {
    aux_bus_id: typedefs.AkUniqueID align(4) = 0,
    game_object_id: typedefs.AkGameObjectID align(4) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SA_ClearImageSources
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SA_ClearImageSources) AkCmd_SA_ClearImageSources {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SA_ClearImageSources) c.AkCmd_SA_ClearImageSources {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SA_ClearImageSources) == @sizeOf(c.AkCmd_SA_ClearImageSources));
    // }

    pub const COMMAND_TYPE: AkCommand = .sa_clear_image_sources;
} else extern struct {};

pub const AkCmd_SA_SetGeometry = if (wwise_options.use_spatial_audio) extern struct {
    geometry_set_id: SpatialAudio.AkGeometrySetID = .{},

    pub inline fn fromC(value: c.AkCmd_SA_SetGeometry) AkCmd_SA_SetGeometry {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_SetGeometry) c.AkCmd_SA_SetGeometry {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_SetGeometry) == @sizeOf(c.AkCmd_SA_SetGeometry));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_set_geometry;
} else extern struct {};

pub const AkCmd_SA_RemoveGeometry = if (wwise_options.use_spatial_audio) extern struct {
    geometry_set_id: SpatialAudio.AkGeometrySetID = .{},

    pub inline fn fromC(value: c.AkCmd_SA_RemoveGeometry) AkCmd_SA_RemoveGeometry {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_RemoveGeometry) c.AkCmd_SA_RemoveGeometry {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_RemoveGeometry) == @sizeOf(c.AkCmd_SA_RemoveGeometry));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_remove_geometry;
} else extern struct {};

pub const AkCmd_SA_SetGeometryInstance = if (wwise_options.use_spatial_audio) extern struct {
    geometry_instance_id: SpatialAudio.AkGeometryInstanceID = .{},
    params: SpatialAudio.AkGeometryInstanceParams = .{},

    // mlarouche: We can't convert directly from the translate-c AkCmd_SA_SetGeometryInstance
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SA_SetGeometryInstance) AkCmd_SA_SetGeometryInstance {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SA_SetGeometryInstance) c.AkCmd_SA_SetGeometryInstance {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SA_SetGeometryInstance) == @sizeOf(c.AkCmd_SA_SetGeometryInstance));
    // }

    pub const COMMAND_TYPE: AkCommand = .sa_set_geometry_instance;
} else extern struct {};

pub const AkCmd_SA_RemoveGeometryInstance = if (wwise_options.use_spatial_audio) extern struct {
    geometry_instance_id: SpatialAudio.AkGeometryInstanceID = .{},

    pub inline fn fromC(value: c.AkCmd_SA_RemoveGeometryInstance) AkCmd_SA_RemoveGeometryInstance {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_RemoveGeometryInstance) c.AkCmd_SA_RemoveGeometryInstance {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_RemoveGeometryInstance) == @sizeOf(c.AkCmd_SA_RemoveGeometryInstance));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_remove_geometry_instance;
} else extern struct {};

pub const AkCmd_SA_SetRoom = if (wwise_options.use_spatial_audio) extern struct {
    room_id: SpatialAudio.AkRoomID align(4) = .{},
    params: SpatialAudio.AkRoomParams align(4) = .{},

    // mlarouche: We can't convert directly from the translate-c AkCmd_SA_SetRoom
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SA_SetRoom) AkCmd_SA_SetRoom {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SA_SetRoom) c.AkCmd_SA_SetRoom {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SA_SetRoom) == @sizeOf(c.AkCmd_SA_SetRoom));
    // }

    pub const COMMAND_TYPE: AkCommand = .sa_set_room;
} else extern struct {};

pub const AkCmd_SA_RemoveRoom = if (wwise_options.use_spatial_audio) extern struct {
    room_id: SpatialAudio.AkRoomID = .{},

    pub inline fn fromC(value: c.AkCmd_SA_RemoveRoom) AkCmd_SA_RemoveRoom {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_RemoveRoom) c.AkCmd_SA_RemoveRoom {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_RemoveRoom) == @sizeOf(c.AkCmd_SA_RemoveRoom));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_remove_room;
} else extern struct {};

pub const AkCmd_SA_SetPortal = if (wwise_options.use_spatial_audio) extern struct {
    portal_id: SpatialAudio.AkPortalID align(4) = .{},
    params: SpatialAudio.AkPortalParams align(4) = .{},

    // mlarouche: We can't convert directly from the translate-c AkCmd_SA_SetPortal
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SA_SetPortal) AkCmd_SA_SetPortal {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SA_SetPortal) c.AkCmd_SA_SetPortal {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SA_SetPortal) == @sizeOf(c.AkCmd_SA_SetPortal));
    // }

    pub const COMMAND_TYPE: AkCommand = .sa_set_portal;
} else extern struct {};

pub const AkCmd_SA_SetPortalObstructionAndOcclusion = if (wwise_options.use_spatial_audio) extern struct {
    portal_id: SpatialAudio.AkPortalID align(4) = .{},
    obstruction: f32 align(4) = 0,
    occlusion: f32 align(4) = 0,
    transition: bool align(4) = false,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SA_SetPortalObstructionAndOcclusion
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SA_SetPortalObstructionAndOcclusion) AkCmd_SA_SetPortalObstructionAndOcclusion {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SA_SetPortalObstructionAndOcclusion) c.AkCmd_SA_SetPortalObstructionAndOcclusion {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SA_SetPortalObstructionAndOcclusion) == @sizeOf(c.AkCmd_SA_SetPortalObstructionAndOcclusion));
    // }

    pub const COMMAND_TYPE: AkCommand = .sa_set_portal_obstruction_and_occlusion;
} else extern struct {};

pub const AkCmd_SA_SetGameObjectToPortalObstruction = if (wwise_options.use_spatial_audio) extern struct {
    game_object_id: typedefs.AkGameObjectID align(4) = 0,
    portal_id: SpatialAudio.AkPortalID align(4) = .{},
    obstruction: f32 align(4) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SA_SetGameObjectToPortalObstruction
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SA_SetGameObjectToPortalObstruction) AkCmd_SA_SetGameObjectToPortalObstruction {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SA_SetGameObjectToPortalObstruction) c.AkCmd_SA_SetGameObjectToPortalObstruction {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SA_SetGameObjectToPortalObstruction) == @sizeOf(c.AkCmd_SA_SetGameObjectToPortalObstruction));
    // }

    pub const COMMAND_TYPE: AkCommand = .sa_set_game_object_to_portal_obstruction;
} else extern struct {};

pub const AkCmd_SA_SetPortalToPortalObstruction = if (wwise_options.use_spatial_audio) extern struct {
    portal_id0: SpatialAudio.AkPortalID align(4) = .{},
    portal_id1: SpatialAudio.AkPortalID align(4) = .{},
    obstruction: f32 align(4) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SA_SetPortalToPortalObstruction
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SA_SetPortalToPortalObstruction) AkCmd_SA_SetPortalToPortalObstruction {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SA_SetPortalToPortalObstruction) c.AkCmd_SA_SetPortalToPortalObstruction {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SA_SetPortalToPortalObstruction) == @sizeOf(c.AkCmd_SA_SetPortalToPortalObstruction));
    // }

    pub const COMMAND_TYPE: AkCommand = .sa_set_portal_to_portal_obstruction;
} else extern struct {};

pub const AkCmd_SA_RemovePortal = if (wwise_options.use_spatial_audio) extern struct {
    portal_id: SpatialAudio.AkPortalID = .{},

    pub inline fn fromC(value: c.AkCmd_SA_RemovePortal) AkCmd_SA_RemovePortal {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_RemovePortal) c.AkCmd_SA_RemovePortal {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_RemovePortal) == @sizeOf(c.AkCmd_SA_RemovePortal));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_remove_portal;
} else extern struct {};

pub const AkCmd_SA_SetReverbZone = if (wwise_options.use_spatial_audio) extern struct {
    reverb_zone_room_id: SpatialAudio.AkRoomID align(4) = .{},
    parent_room_id: SpatialAudio.AkRoomID align(4) = .{},
    transition_region_width: f32 align(4) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SA_SetReverbZone
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SA_SetReverbZone) AkCmd_SA_SetReverbZone {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SA_SetReverbZone) c.AkCmd_SA_SetReverbZone {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SA_SetReverbZone) == @sizeOf(c.AkCmd_SA_SetReverbZone));
    // }

    pub const COMMAND_TYPE: AkCommand = .sa_set_reverb_zone;
} else extern struct {};

pub const AkCmd_SA_RemoveReverbZone = if (wwise_options.use_spatial_audio) extern struct {
    reverb_zone_room_id: SpatialAudio.AkRoomID = .{},

    pub inline fn fromC(value: c.AkCmd_SA_RemoveReverbZone) AkCmd_SA_RemoveReverbZone {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_RemoveReverbZone) c.AkCmd_SA_RemoveReverbZone {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_RemoveReverbZone) == @sizeOf(c.AkCmd_SA_RemoveReverbZone));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_remove_reverb_zone;
} else extern struct {};

pub const AkCmd_SA_SetGameObjectInRoom = if (wwise_options.use_spatial_audio) extern struct {
    game_object_id: typedefs.AkGameObjectID = 0,
    room_id: SpatialAudio.AkRoomID = .{},

    pub inline fn fromC(value: c.AkCmd_SA_SetGameObjectInRoom) AkCmd_SA_SetGameObjectInRoom {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_SetGameObjectInRoom) c.AkCmd_SA_SetGameObjectInRoom {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_SetGameObjectInRoom) == @sizeOf(c.AkCmd_SA_SetGameObjectInRoom));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_set_game_object_in_room;
} else extern struct {};

pub const AkCmd_SA_UnsetGameObjectInRoom = if (wwise_options.use_spatial_audio) extern struct {
    game_object_id: typedefs.AkGameObjectID = 0,

    pub inline fn fromC(value: c.AkCmd_SA_UnsetGameObjectInRoom) AkCmd_SA_UnsetGameObjectInRoom {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_UnsetGameObjectInRoom) c.AkCmd_SA_UnsetGameObjectInRoom {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_UnsetGameObjectInRoom) == @sizeOf(c.AkCmd_SA_UnsetGameObjectInRoom));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_unset_game_object_in_room;
} else extern struct {};

pub const AkCmd_SA_SetGameObjectRadius = if (wwise_options.use_spatial_audio) extern struct {
    game_object_id: typedefs.AkGameObjectID = 0,
    outer_radius: f32 = 0,
    inner_radius: f32 = 0,

    pub inline fn fromC(value: c.AkCmd_SA_SetGameObjectRadius) AkCmd_SA_SetGameObjectRadius {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_SetGameObjectRadius) c.AkCmd_SA_SetGameObjectRadius {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_SetGameObjectRadius) == @sizeOf(c.AkCmd_SA_SetGameObjectRadius));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_set_game_object_radius;
} else extern struct {};

pub const AkCmd_SA_SetEarlyReflectionsAuxSend = if (wwise_options.use_spatial_audio) extern struct {
    game_object_id: typedefs.AkGameObjectID align(4) = 0,
    aux_bus_id: typedefs.AkAuxBusID align(4) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SA_SetEarlyReflectionsAuxSend
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SA_SetEarlyReflectionsAuxSend) AkCmd_SA_SetEarlyReflectionsAuxSend {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SA_SetEarlyReflectionsAuxSend) c.AkCmd_SA_SetEarlyReflectionsAuxSend {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SA_SetEarlyReflectionsAuxSend) == @sizeOf(c.AkCmd_SA_SetEarlyReflectionsAuxSend));
    // }

    pub const COMMAND_TYPE: AkCommand = .sa_set_early_reflections_aux_send;
} else extern struct {};

pub const AkCmd_SA_SetEarlyReflectionsVolume = if (wwise_options.use_spatial_audio) extern struct {
    game_object_id: typedefs.AkGameObjectID align(4) = 0,
    volume: f32 align(4) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SA_SetEarlyReflectionsVolume
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SA_SetEarlyReflectionsVolume) AkCmd_SA_SetEarlyReflectionsVolume {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SA_SetEarlyReflectionsVolume) c.AkCmd_SA_SetEarlyReflectionsVolume {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SA_SetEarlyReflectionsVolume) == @sizeOf(c.AkCmd_SA_SetEarlyReflectionsVolume));
    // }

    pub const COMMAND_TYPE: AkCommand = .sa_set_early_reflections_volume;
} else extern struct {};

pub const AkCmd_SA_SetAdjacentRoomBleed = if (wwise_options.use_spatial_audio) extern struct {
    adjacentRoomBleed: f32 = 0,

    pub inline fn fromC(value: c.AkCmd_SA_SetAdjacentRoomBleed) AkCmd_SA_SetAdjacentRoomBleed {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_SetAdjacentRoomBleed) c.AkCmd_SA_SetAdjacentRoomBleed {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_SetAdjacentRoomBleed) == @sizeOf(c.AkCmd_SA_SetAdjacentRoomBleed));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_set_adjacent_room_bleed;
} else extern struct {};

pub const AkCmd_SA_SetReflectionsOrder = if (wwise_options.use_spatial_audio) extern struct {
    reflections_order: u32 = 0,
    update_paths: bool = false,

    pub inline fn fromC(value: c.AkCmd_SA_SetReflectionsOrder) AkCmd_SA_SetReflectionsOrder {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_SetReflectionsOrder) c.AkCmd_SA_SetReflectionsOrder {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_SetReflectionsOrder) == @sizeOf(c.AkCmd_SA_SetReflectionsOrder));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_set_reflections_order;
} else extern struct {};

pub const AkCmd_SA_SetDiffractionOrder = if (wwise_options.use_spatial_audio) extern struct {
    diffraction_order: u32 = 0,
    update_paths: bool = false,

    pub inline fn fromC(value: c.AkCmd_SA_SetDiffractionOrder) AkCmd_SA_SetDiffractionOrder {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_SetDiffractionOrder) c.AkCmd_SA_SetDiffractionOrder {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_SetDiffractionOrder) == @sizeOf(c.AkCmd_SA_SetDiffractionOrder));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_set_reflections_order;
} else extern struct {};

pub const AkCmd_SA_SetMaxGlobalReflectionPaths = if (wwise_options.use_spatial_audio) extern struct {
    max_reflection_paths: u32 = 0,

    pub inline fn fromC(value: c.AkCmd_SA_SetMaxGlobalReflectionPaths) AkCmd_SA_SetMaxGlobalReflectionPaths {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_SetMaxGlobalReflectionPaths) c.AkCmd_SA_SetMaxGlobalReflectionPaths {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_SetMaxGlobalReflectionPaths) == @sizeOf(c.AkCmd_SA_SetMaxGlobalReflectionPaths));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_set_max_global_reflection_paths;
} else extern struct {};

pub const AkCmd_SA_SetMaxEmitterRoomAuxSends = if (wwise_options.use_spatial_audio) extern struct {
    max_emitter_room_aux_sends: u32 = 0,

    pub inline fn fromC(value: c.AkCmd_SA_SetMaxEmitterRoomAuxSends) AkCmd_SA_SetMaxEmitterRoomAuxSends {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_SetMaxEmitterRoomAuxSends) c.AkCmd_SA_SetMaxEmitterRoomAuxSends {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_SetMaxEmitterRoomAuxSends) == @sizeOf(c.AkCmd_SA_SetMaxEmitterRoomAuxSends));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_set_max_emitter_room_aux_sends;
} else extern struct {};

pub const AkCmd_SA_SetMaxDiffractionPaths = if (wwise_options.use_spatial_audio) extern struct {
    max_diffraction_paths: u32 align(4) = 0,
    game_object_id: typedefs.AkGameObjectID align(4) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SA_SetMaxDiffractionPaths
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SA_SetMaxDiffractionPaths) AkCmd_SA_SetMaxDiffractionPaths {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SA_SetMaxDiffractionPaths) c.AkCmd_SA_SetMaxDiffractionPaths {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SA_SetMaxDiffractionPaths) == @sizeOf(c.AkCmd_SA_SetMaxDiffractionPaths));
    // }

    pub const COMMAND_TYPE: AkCommand = .sa_set_max_diffraction_paths;
} else extern struct {};

pub const AkCmd_SA_SetSmoothingConstant = if (wwise_options.use_spatial_audio) extern struct {
    smoothing_constant_ms: f32 align(4) = 0,
    game_object_id: typedefs.AkGameObjectID align(4) = 0,

    // mlarouche: We can't convert directly from the translate-c AkCmd_SA_SetSmoothingConstant
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkCmd_SA_SetSmoothingConstant) AkCmd_SA_SetSmoothingConstant {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkCmd_SA_SetSmoothingConstant) c.AkCmd_SA_SetSmoothingConstant {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkCmd_SA_SetSmoothingConstant) == @sizeOf(c.AkCmd_SA_SetSmoothingConstant));
    // }

    pub const COMMAND_TYPE: AkCommand = .sa_set_smoothing_constant;
} else extern struct {};

pub const AkCmd_SA_SetTransmissionOperation = if (wwise_options.use_spatial_audio) extern struct {
    operation: u32 = 0,

    pub inline fn fromC(value: c.AkCmd_SA_SetTransmissionOperation) AkCmd_SA_SetTransmissionOperation {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_SetTransmissionOperation) c.AkCmd_SA_SetTransmissionOperation {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_SetTransmissionOperation) == @sizeOf(c.AkCmd_SA_SetTransmissionOperation));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_set_transmission_operation;
} else extern struct {};

pub const AkCmd_SA_SetNumberOfPrimaryRays = if (wwise_options.use_spatial_audio) extern struct {
    nb_primary_rays: u32 = 0,

    pub inline fn fromC(value: c.AkCmd_SA_SetNumberOfPrimaryRays) AkCmd_SA_SetNumberOfPrimaryRays {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_SetNumberOfPrimaryRays) c.AkCmd_SA_SetNumberOfPrimaryRays {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_SetNumberOfPrimaryRays) == @sizeOf(c.AkCmd_SA_SetNumberOfPrimaryRays));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_set_number_of_primary_rays;
} else extern struct {};

pub const AkCmd_SA_SetLoadBalancingSpread = if (wwise_options.use_spatial_audio) extern struct {
    nb_frames: u32 = 0,

    pub inline fn fromC(value: c.AkCmd_SA_SetLoadBalancingSpread) AkCmd_SA_SetLoadBalancingSpread {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_SetLoadBalancingSpread) c.AkCmd_SA_SetLoadBalancingSpread {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_SetLoadBalancingSpread) == @sizeOf(c.AkCmd_SA_SetLoadBalancingSpread));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_set_load_balancing_spread;
} else extern struct {};

pub const AkCmd_SA_ResetStochasticEngine = if (wwise_options.use_spatial_audio) extern struct {
    unused: u32 = 0,

    pub inline fn fromC(value: c.AkCmd_SA_ResetStochasticEngine) AkCmd_SA_ResetStochasticEngine {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCmd_SA_ResetStochasticEngine) c.AkCmd_SA_ResetStochasticEngine {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCmd_SA_ResetStochasticEngine) == @sizeOf(c.AkCmd_SA_ResetStochasticEngine));
    }

    pub const COMMAND_TYPE: AkCommand = .sa_reset_stochastic_engine;
} else extern struct {};

pub const AkCommandBufferHeader = extern struct {
    buffer_size: u32 = 0,
    last_command_offset: u32 = 0,
    completion_callback: AkCommandCallbackFunc = null,
    completion_callback_cookie: ?*anyopaque = null,

    pub inline fn fromC(value: c.AkCommandBufferHeader) AkCommandBufferHeader {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCommandBufferHeader) c.AkCommandBufferHeader {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCommandBufferHeader) == @sizeOf(c.AkCommandBufferHeader));
    }
};

pub const AkCommandHeader = extern struct {
    code: u16 = 0,
    size: u16 = 0,
    flags: u16 = 0,
    result: u16 = 0,

    pub inline fn fromC(value: c.AkCommandHeader) AkCommandHeader {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCommandHeader) c.AkCommandHeader {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCommandHeader) == @sizeOf(c.AkCommandHeader));
    }
};

pub const AkCommandBufferIterator = extern struct {
    header: ?*AkCommandHeader = null,
    payload: ?*anyopaque = null,
    buffer: ?*anyopaque = null,

    pub inline fn fromC(value: c.AkCommandBufferIterator) AkCommandBufferIterator {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkCommandBufferIterator) c.AkCommandBufferIterator {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCommandBufferIterator) == @sizeOf(c.AkCommandBufferIterator));
    }
};
