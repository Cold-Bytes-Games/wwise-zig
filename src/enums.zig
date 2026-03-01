const c = @import("wwise_c");
const std = @import("std");
const zig = @import("zig.zig");

pub const AKRESULT = enum(zig.DefaultEnumType) {
    not_implemented = c.AK_NotImplemented,
    success = c.AK_Success,
    fail = c.AK_Fail,
    partial_success = c.AK_PartialSuccess,
    not_compatible = c.AK_NotCompatible,
    already_connected = c.AK_AlreadyConnected,
    invalid_file = c.AK_InvalidFile,
    audio_file_header_too_large = c.AK_AudioFileHeaderTooLarge,
    max_reached = c.AK_MaxReached,
    invalid_id = c.AK_InvalidID,
    id_not_found = c.AK_IDNotFound,
    invalid_instance_id = c.AK_InvalidInstanceID,
    no_more_data = c.AK_NoMoreData,
    invalid_state_group = c.AK_InvalidStateGroup,
    child_already_has_a_parent = c.AK_ChildAlreadyHasAParent,
    invalid_language = c.AK_InvalidLanguage,
    cannot_add_itself_as_a_child = c.AK_CannotAddItselfAsAChild,
    invalid_parameter = c.AK_InvalidParameter,
    element_already_in_list = c.AK_ElementAlreadyInList,
    path_not_found = c.AK_PathNotFound,
    path_no_vertices = c.AK_PathNoVertices,
    path_not_running = c.AK_PathNotRunning,
    path_not_paused = c.AK_PathNotPaused,
    path_node_already_in_list = c.AK_PathNodeAlreadyInList,
    path_node_not_in_list = c.AK_PathNodeNotInList,
    data_needed = c.AK_DataNeeded,
    no_data_needed = c.AK_NoDataNeeded,
    data_ready = c.AK_DataReady,
    no_data_ready = c.AK_NoDataReady,
    insufficient_memory = c.AK_InsufficientMemory,
    cancelled = c.AK_Cancelled,
    unknown_bank_id = c.AK_UnknownBankID,
    bank_read_error = c.AK_BankReadError,
    invalid_switch_type = c.AK_InvalidSwitchType,
    format_not_ready = c.AK_FormatNotReady,
    wrong_bank_version = c.AK_WrongBankVersion,
    file_not_found = c.AK_FileNotFound,
    device_not_ready = c.AK_DeviceNotReady,
    bank_already_loaded = c.AK_BankAlreadyLoaded,
    rendered_fx = c.AK_RenderedFX,
    process_needed = c.AK_ProcessNeeded,
    process_done = c.AK_ProcessDone,
    mem_manager_not_initialized = c.AK_MemManagerNotInitialized,
    stream_mgr_not_initialized = c.AK_StreamMgrNotInitialized,
    sse_instructions_not_supported = c.AK_SSEInstructionsNotSupported,
    busy = c.AK_Busy,
    unsupported_channel_config = c.AK_UnsupportedChannelConfig,
    plugin_media_not_available = c.AK_PluginMediaNotAvailable,
    must_be_virtualized = c.AK_MustBeVirtualized,
    command_too_large = c.AK_CommandTooLarge,
    rejected_by_filter = c.AK_RejectedByFilter,
    invalid_custom_platform_name = c.AK_InvalidCustomPlatformName,
    dll_cannot_load = c.AK_DLLCannotLoad,
    dll_path_not_found = c.AK_DLLPathNotFound,
    no_java_vm = c.AK_NoJavaVM,
    open_sl_error = c.AK_OpenSLError,
    plugin_not_registered = c.AK_PluginNotRegistered,
    data_alignment_error = c.AK_DataAlignmentError,
    device_not_compatible = c.AK_DeviceNotCompatible,
    duplicate_unique_id = c.AK_DuplicateUniqueID,
    init_bank_not_loaded = c.AK_InitBankNotLoaded,
    device_not_found = c.AK_DeviceNotFound,
    playing_id_not_found = c.AK_PlayingIDNotFound,
    invalid_float_value = c.AK_InvalidFloatValue,
    file_format_mismatch = c.AK_FileFormatMismatch,
    no_distinct_listener = c.AK_NoDistinctListener,
    resource_in_use = c.AK_ResourceInUse,
    invalid_bank_type = c.AK_InvalidBankType,
    already_initialized = c.AK_AlreadyInitialized,
    not_initialized = c.AK_NotInitialized,
    file_permission_error = c.AK_FilePermissionError,
    unknown_file_error = c.AK_UnknownFileError,
    too_many_concurrent_operations = c.AK_TooManyConcurrentOperations,
    invalid_file_size = c.AK_InvalidFileSize,
    deferred = c.AK_Deferred,
    file_path_too_long = c.AK_FilePathTooLong,
    invalid_state = c.AK_InvalidState,
};

pub const AkGroupType = enum(zig.DefaultEnumType) {
    @"switch" = c.AkGroupType_Switch,
    state = c.AkGroupType_State,
};

pub const AkAudioDeviceState = packed struct(zig.DefaultEnumType) {
    active: bool = false,
    disabled: bool = false,
    not_present: bool = false,
    unplugged: bool = false,
    pad: u28 = 0,

    pub const All = AkAudioDeviceState{
        .active = true,
        .disabled = true,
        .not_present = true,
        .unplugged = true,
    };

    pub inline fn fromC(value: c.AkAudioDeviceState) AkAudioDeviceState {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkAudioDeviceState) c.AkAudioDeviceState {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@as(zig.DefaultEnumType, @bitCast(AkAudioDeviceState{ .active = true })) == c.AkDeviceState_Active);
        std.debug.assert(@as(zig.DefaultEnumType, @bitCast(AkAudioDeviceState{ .disabled = true })) == c.AkDeviceState_Disabled);
        std.debug.assert(@as(zig.DefaultEnumType, @bitCast(AkAudioDeviceState{ .not_present = true })) == c.AkDeviceState_NotPresent);
        std.debug.assert(@as(zig.DefaultEnumType, @bitCast(AkAudioDeviceState{ .unplugged = true })) == c.AkDeviceState_Unplugged);
    }
};

pub const AkConnectionType = enum(zig.DefaultEnumType) {
    direct = c.ConnectionType_Direct,
    game_def_send = c.ConnectionType_GameDefSend,
    user_def_send = c.ConnectionType_UserDefSend,
    reflections_send = c.ConnectionType_ReflectionsSend,
};

pub const AkAttenuationCurveType = enum(zig.DefaultEnumType) {
    volume_dry = c.AttenuationCurveID_VolumeDry,
    volume_aux_game_def = c.AttenuationCurveID_VolumeAuxGameDef,
    volume_aux_user_def = c.AttenuationCurveID_VolumeAuxUserDef,
    low_pass_filter = c.AttenuationCurveID_LowPassFilter,
    high_pass_filter = c.AttenuationCurveID_HighPassFilter,
    high_shelf = c.AttenuationCurveID_HighShelf,
    spread = c.AttenuationCurveID_Spread,
    focus = c.AttenuationCurveID_Focus,
    obstruction_volume = c.AttenuationCurveID_ObstructionVolume,
    obstruction_lpf = c.AttenuationCurveID_ObstructionLPF,
    obstruction_hpf = c.AttenuationCurveID_ObstructionHPF,
    obstruction_hsf = c.AttenuationCurveID_ObstructionHSF,
    occlusion_volume = c.AttenuationCurveID_OcclusionVolume,
    occlusion_lpf = c.AttenuationCurveID_OcclusionLPF,
    occlusion_hpf = c.AttenuationCurveID_OcclusionHPF,
    occlusion_hsf = c.AttenuationCurveID_OcclusionHSF,
    diffraction_volume = c.AttenuationCurveID_DiffractionVolume,
    diffraction_lpf = c.AttenuationCurveID_DiffractionLPF,
    diffraction_hpf = c.AttenuationCurveID_DiffractionHPF,
    diffraction_hsf = c.AttenuationCurveID_DiffractionHSF,
    transmission_volume = c.AttenuationCurveID_TransmissionVolume,
    transmission_lpf = c.AttenuationCurveID_TransmissionLPF,
    transmission_hpf = c.AttenuationCurveID_TransmissionHPF,
    transmission_hsf = c.AttenuationCurveID_TransmissionHSF,
    project = c.AttenuationCurveID_Project,
    none = c.AttenuationCurveID_None,
};

pub fn AkCurveInterpolationTemplate(comptime BackingType: type) type {
    return enum(BackingType) {
        log3 = c.AkCurveInterpolation_Log3,
        sine = c.AkCurveInterpolation_Sine,
        log1 = c.AkCurveInterpolation_Log1,
        inv_s_curve = c.AkCurveInterpolation_InvSCurve,
        linear = c.AkCurveInterpolation_Linear,
        s_curve = c.AkCurveInterpolation_SCurve,
        exp1 = c.AkCurveInterpolation_Exp1,
        sine_recip = c.AkCurveInterpolation_SineRecip,
        exp3 = c.AkCurveInterpolation_Exp3,
        constant = c.AkCurveInterpolation_Constant,
    };
}

pub const AkCurveInterpolation = AkCurveInterpolationTemplate(zig.DefaultEnumType);
pub const AkCurveInterpolation_u8 = AkCurveInterpolationTemplate(u8);
pub const AkCurveInterpolation_u16 = AkCurveInterpolationTemplate(u16);

pub const AkBankType = enum(c.AkBankType) {
    user = c.AkBankType_User,
    event = c.AkBankType_Event,
    bus = c.AkBankType_Bus,
};

pub const AkSpeakerPanningType = enum(zig.DefaultEnumType) {
    direct_speaker_assignment = c.AK_DirectSpeakerAssignment,
    balance_fadee_height = c.AK_BalanceFadeHeight,
    steering_panner = c.AK_SteeringPanner,
};

pub const Ak3DPositionType = enum(zig.DefaultEnumType) {
    emitter = c.AK_3DPositionType_Emitter,
    emitter_with_automation = c.AK_3DPositionType_EmitterWithAutomation,
    listener_with_automation = c.AK_3DPositionType_ListenerWithAutomation,
};

pub fn AkPanningRuleTemplate(comptime BackingType: type) type {
    return enum(BackingType) {
        speakers = c.AkPanningRule_Speakers,
        headphones = c.AkPanningRule_Headphones,
    };
}

pub const AkPanningRule = AkPanningRuleTemplate(zig.DefaultEnumType);
pub const AkPanningRule_u8 = AkPanningRuleTemplate(zig.DefaultEnumType);

pub const Ak3DSpatializationMode = enum(zig.DefaultEnumType) {
    none = c.AK_SpatializationMode_None,
    position_only = c.AK_SpatializationMode_PositionOnly,
    position_and_orientation = c.AK_SpatializationMode_PositionAndOrientation,
};

pub const AkMeteringFlags = packed struct(zig.DefaultEnumType) {
    enable_bus_meter_peak: bool = false,
    enable_bus_meter_true_peak: bool = false,
    enable_bus_meter_rms: bool = false,
    reserved0: bool = false,
    enable_bus_meter_kpower: bool = false,
    enable_bus_meter_3d_meter: bool = false,
    padding: u26 = 0,

    pub inline fn fromC(value: c.AkMeteringFlags) AkMeteringFlags {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMeteringFlags) c.AkMeteringFlags {
        return @bitCast(self);
    }
};

pub const AkPluginType = enum(zig.DefaultEnumType) {
    none = c.AkPluginTypeNone,
    codec = c.AkPluginTypeCodec,
    source = c.AkPluginTypeSource,
    effect = c.AkPluginTypeEffect,
    mixer = c.AkPluginTypeMixer,
    sink = c.AkPluginTypeSink,
    global_extension = c.AkPluginTypeGlobalExtension,
    metadata = c.AkPluginTypeMetadata,
};

pub const AkNodeType = enum(u8) {
    default = c.AkNodeType_Default,
    bus = c.AkNodeType_Bus,
    audio_device = c.AkNodeType_AudioDevice,
};

pub const AkMultiPositionType = enum(zig.DefaultEnumType) {
    single_source = c.AkMultiPositionType_SingleSource,
    multi_sources = c.AkMultiPositionType_MultiSources,
    multi_directions = c.AkMultiPositionType_MultiDirections,
};

pub const AkSetPositionFlags = packed struct(zig.DefaultEnumType) {
    emitter: bool = false,
    listener: bool = false,
    pad: u30 = 0,

    pub const default = AkSetPositionFlags{ .emitter = true, .listener = true };

    pub inline fn fromC(value: c.AkSetPositionFlags) AkSetPositionFlags {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkSetPositionFlags) c.AkSetPositionFlags {
        return @as(zig.DefaultEnumType, @bitCast(self));
    }

    comptime {
        std.debug.assert(@as(zig.DefaultEnumType, @bitCast(AkSetPositionFlags{ .emitter = true })) == c.AkSetPositionFlags_Emitter);
        std.debug.assert(@as(zig.DefaultEnumType, @bitCast(AkSetPositionFlags{ .listener = true })) == c.AkSetPositionFlags_Listener);
        std.debug.assert(default.toC() == c.AkSetPositionFlags_Default);
    }
};

pub const AkListenerOp = enum(zig.DefaultEnumType) {
    set = c.AkListenerOp_Set,
    add = c.AkListenerOp_Add,
    remove = c.AkListenerOp_Remove,
};

pub fn AkActionOnEventTypeTemplate(comptime BackingType: type) type {
    return enum(BackingType) {
        stop = c.AkActionOnEventType_Stop,
        pause = c.AkActionOnEventType_Pause,
        @"resume" = c.AkActionOnEventType_Resume,
        @"break" = c.AkActionOnEventType_Break,
        release_envelope = c.AkActionOnEventType_ReleaseEnvelope,
    };
}

pub const AkActionOnEventType = AkActionOnEventTypeTemplate(zig.DefaultEnumType);
pub const AkActionOnEventType_u8 = AkActionOnEventTypeTemplate(u8);

pub fn AkDynamicSequenceTypeTemplate(comptime BackingType: type) type {
    return enum(BackingType) {
        sample_accurate = c.AkDynamicSequenceType_SampleAccurate,
        normal_transition = c.AkDynamicSequenceType_NormalTransition,
    };
}
pub const AkDynamicSequenceType = AkDynamicSequenceTypeTemplate(zig.DefaultEnumType);
pub const AkDynamicSequenceType_u8 = AkDynamicSequenceTypeTemplate(u8);

pub const AkDynamicSequenceOp = enum(u32) {
    play = c.AkDynamicSequenceOp_Play,
    pause = c.AkDynamicSequenceOp_Pause,
    @"resume" = c.AkDynamicSequenceOp_Resume,
    stop = c.AkDynamicSequenceOp_Stop,
    @"break" = c.AkDynamicSequenceOp_Break,
    close = c.AkDynamicSequenceOp_Close,
};

pub const AkChannelConfigType = enum(u4) {
    anonymous = 0,
    standard = 1,
    ambisonic = 2,
    objects = 3,

    use_device_main = 0xE,
    use_device_passthrough = 0xF,
};

pub const AkMotionDeviceType = enum(zig.DefaultEnumType) {
    controller = c.AkMotionDeviceType_Controller,
    mobile = c.AkMotionDeviceType_Mobile,
};

pub const AkMotionInputProfile = enum(zig.DefaultEnumType) {
    rumble = c.AkMotionInputProfile_GenericRumble,
    lo_res_haptics = c.AkMotionInputProfile_GenericLoResHaptics,
    hi_res_haptics = c.AkMotionInputProfile_GenericHiResHaptics,
};

pub const AkEngineRenderingMode = enum(zig.DefaultEnumType) {
    online = c.AkEngineRenderingMode_Online,
    offline = c.AkEngineRenderingMode_Offline,
    offline_threaded = c.AkEngineRenderingMode_OfflineThreaded,
};
