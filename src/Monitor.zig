const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const error_message_translator = @import("error_message_translator.zig");
const StreamMgr = @import("StreamMgr.zig");
const builtin = @import("builtin");

pub const MsgContext = extern struct {
    in_playing_id: common.AkPlayingID = common.AK_INVALID_PLAYING_ID,
    in_game_obj_id: common.AkGameObjectID = common.AK_INVALID_GAME_OBJECT,
    in_sound_id: common.AkUniqueID = common.AK_INVALID_UNIQUE_ID,
    in_is_bus: bool = false,

    pub inline fn fromC(value: c.WWISEC_AK_Monitor_MsgContext) MsgContext {
        return @bitCast(value);
    }

    pub inline fn toC(self: MsgContext) c.WWISEC_AK_Monitor_MsgContext {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(MsgContext) == @sizeOf(c.WWISEC_AK_Monitor_MsgContext));
    }
};

pub const ErrorLevel = packed struct(common.DefaultEnumType) {
    message: bool = false,
    @"error": bool = false,
    pad: u30 = 0,

    pub const All = ErrorLevel{ .message = true, .@"error" = true };

    pub fn fromC(value: c.WWISEC_AK_Monitor_ErrorLevel) ErrorLevel {
        return @bitCast(value);
    }

    pub fn toC(self: ErrorLevel) c.WWISEC_AK_Monitor_ErrorLevel {
        return @bitCast(self);
    }
};

pub const ErrorCode = enum(common.DefaultEnumType) {
    no_error = c.WWISEC_AK_Monitor_ErrorCode_NoError,
    file_not_found = c.WWISEC_AK_Monitor_ErrorCode_FileNotFound,
    cannot_open_file = c.WWISEC_AK_Monitor_ErrorCode_CannotOpenFile,
    cannot_start_stream_no_memory = c.WWISEC_AK_Monitor_ErrorCode_CannotStartStreamNoMemory,
    io_device = c.WWISEC_AK_Monitor_ErrorCode_IODevice,
    incompatible_io_settings = c.WWISEC_AK_Monitor_ErrorCode_IncompatibleIOSettings,
    plugin_unsupported_channel_configuration = c.WWISEC_AK_Monitor_ErrorCode_PluginUnsupportedChannelConfiguration,
    plugin_media_unavailable = c.WWISEC_AK_Monitor_ErrorCode_PluginMediaUnavailable,
    plugin_initialisation_failed = c.WWISEC_AK_Monitor_ErrorCode_PluginInitialisationFailed,
    plugin_processing_failed = c.WWISEC_AK_Monitor_ErrorCode_PluginProcessingFailed,
    plugin_execution_invalid = c.WWISEC_AK_Monitor_ErrorCode_PluginExecutionInvalid,
    plugin_allocation_failed = c.WWISEC_AK_Monitor_ErrorCode_PluginAllocationFailed,
    vorbis_seek_table_recommended = c.WWISEC_AK_Monitor_ErrorCode_VorbisSeekTableRecommended,
    vorbis_decode_error = c.WWISEC_AK_Monitor_ErrorCode_VorbisDecodeError,
    atrac9_decode_failed = c.WWISEC_AK_Monitor_ErrorCode_ATRAC9DecodeFailed,
    atrac9_loop_section_too_small = c.WWISEC_AK_Monitor_ErrorCode_ATRAC9LoopSectionTooSmall,
    invalid_audio_file_header = c.WWISEC_AK_Monitor_ErrorCode_InvalidAudioFileHeader,
    audio_file_header_too_large = c.WWISEC_AK_Monitor_ErrorCode_AudioFileHeaderTooLarge,
    loop_too_small = c.WWISEC_AK_Monitor_ErrorCode_LoopTooSmall,
    transition_not_accurate_channel = c.WWISEC_AK_Monitor_ErrorCode_TransitionNotAccurateChannel,
    transition_not_accurate_plugin_mismatch = c.WWISEC_AK_Monitor_ErrorCode_TransitionNotAccuratePluginMismatch,
    transition_not_accurate_rejected_by_plugin = c.WWISEC_AK_Monitor_ErrorCode_TransitionNotAccurateRejectedByPlugin,
    transition_not_accurate_starvation = c.WWISEC_AK_Monitor_ErrorCode_TransitionNotAccurateStarvation,
    transition_not_accurate_codec_error = c.WWISEC_AK_Monitor_ErrorCode_TransitionNotAccurateCodecError,
    nothing_to_play = c.WWISEC_AK_Monitor_ErrorCode_NothingToPlay,
    play_failed = c.WWISEC_AK_Monitor_ErrorCode_PlayFailed,
    stinger_could_not_be_scheduled = c.WWISEC_AK_Monitor_ErrorCode_StingerCouldNotBeScheduled,
    too_long_segment_look_ahead = c.WWISEC_AK_Monitor_ErrorCode_TooLongSegmentLookAhead,
    cannot_schedule_music_switch = c.WWISEC_AK_Monitor_ErrorCode_CannotScheduleMusicSwitch,
    too_many_simultaneous_music_segments = c.WWISEC_AK_Monitor_ErrorCode_TooManySimultaneousMusicSegments,
    playlist_stopped_for_editing = c.WWISEC_AK_Monitor_ErrorCode_PlaylistStoppedForEditing,
    music_clips_rescheduled_after_track_edit = c.WWISEC_AK_Monitor_ErrorCode_MusicClipsRescheduledAfterTrackEdit,
    cannot_play_source_create = c.WWISEC_AK_Monitor_ErrorCode_CannotPlaySource_Create,
    cannot_play_source_virtual_off = c.WWISEC_AK_Monitor_ErrorCode_CannotPlaySource_VirtualOff,
    cannot_play_source_time_skip = c.WWISEC_AK_Monitor_ErrorCode_CannotPlaySource_TimeSkip,
    cannot_play_source_inconsistent_state = c.WWISEC_AK_Monitor_ErrorCode_CannotPlaySource_InconsistentState,
    media_not_loaded = c.WWISEC_AK_Monitor_ErrorCode_MediaNotLoaded,
    voice_starving = c.WWISEC_AK_Monitor_ErrorCode_VoiceStarving,
    streaming_source_starving = c.WWISEC_AK_Monitor_ErrorCode_StreamingSourceStarving,
    xma_decoder_source_starving = c.WWISEC_AK_Monitor_ErrorCode_XMADecoderSourceStarving,
    xma_decoding_error = c.WWISEC_AK_Monitor_ErrorCode_XMADecodingError,
    invalid_xma_data = c.WWISEC_AK_Monitor_ErrorCode_InvalidXMAData,
    plugin_not_registered = c.WWISEC_AK_Monitor_ErrorCode_PluginNotRegistered,
    codec_not_registered = c.WWISEC_AK_Monitor_ErrorCode_CodecNotRegistered,
    plugin_version_mismatch = c.WWISEC_AK_Monitor_ErrorCode_PluginVersionMismatch,
    event_id_not_found = c.WWISEC_AK_Monitor_ErrorCode_EventIDNotFound,
    invalid_group_id = c.WWISEC_AK_Monitor_ErrorCode_InvalidGroupID,
    selected_node_not_available = c.WWISEC_AK_Monitor_ErrorCode_SelectedNodeNotAvailable,
    selected_media_not_available = c.WWISEC_AK_Monitor_ErrorCode_SelectedMediaNotAvailable,
    no_valid_switch = c.WWISEC_AK_Monitor_ErrorCode_NoValidSwitch,
    bank_load_failed = c.WWISEC_AK_Monitor_ErrorCode_BankLoadFailed,
    error_while_loading_bank = c.WWISEC_AK_Monitor_ErrorCode_ErrorWhileLoadingBank,
    insufficient_space_to_load_bank = c.WWISEC_AK_Monitor_ErrorCode_InsufficientSpaceToLoadBank,
    lower_engine_command_list_full = c.WWISEC_AK_Monitor_ErrorCode_LowerEngineCommandListFull,
    seek_no_marker = c.WWISEC_AK_Monitor_ErrorCode_SeekNoMarker,
    cannot_seek_continuous = c.WWISEC_AK_Monitor_ErrorCode_CannotSeekContinuous,
    seek_after_eof = c.WWISEC_AK_Monitor_ErrorCode_SeekAfterEof,
    unknown_game_object = c.WWISEC_AK_Monitor_ErrorCode_UnknownGameObject,
    game_object_never_registered = c.WWISEC_AK_Monitor_ErrorCode_GameObjectNeverRegistered,
    dead_game_object = c.WWISEC_AK_Monitor_ErrorCode_DeadGameObject,
    game_object_is_not_emitter = c.WWISEC_AK_Monitor_ErrorCode_GameObjectIsNotEmitter,
    external_source_not_resolved = c.WWISEC_AK_Monitor_ErrorCode_ExternalSourceNotResolved,
    file_format_mismatch = c.WWISEC_AK_Monitor_ErrorCode_FileFormatMismatch,
    command_queue_full = c.WWISEC_AK_Monitor_ErrorCode_CommandQueueFull,
    command_too_large = c.WWISEC_AK_Monitor_ErrorCode_CommandTooLarge,
    xma_create_decoder_limit_reached = c.WWISEC_AK_Monitor_ErrorCode_XMACreateDecoderLimitReached,
    xma_stream_buffer_too_small = c.WWISEC_AK_Monitor_ErrorCode_XMAStreamBufferTooSmall,
    modulator_scope_error_inst = c.WWISEC_AK_Monitor_ErrorCode_ModulatorScopeError_Inst,
    modulator_scope_error_obj = c.WWISEC_AK_Monitor_ErrorCode_ModulatorScopeError_Obj,
    seek_after_end_of_playlist = c.WWISEC_AK_Monitor_ErrorCode_SeekAfterEndOfPlaylist,
    opus_require_seek_table = c.WWISEC_AK_Monitor_ErrorCode_OpusRequireSeekTable,
    opus_decode_error = c.WWISEC_AK_Monitor_ErrorCode_OpusDecodeError,
    source_plugin_not_found = c.WWISEC_AK_Monitor_ErrorCode_SourcePluginNotFound,
    virtual_voice_limit = c.WWISEC_AK_Monitor_ErrorCode_VirtualVoiceLimit,
    not_enough_memory_to_start = c.WWISEC_AK_Monitor_ErrorCode_NotEnoughMemoryToStart,
    unknown_opus_error = c.WWISEC_AK_Monitor_ErrorCode_UnknownOpusError,
    audio_device_init_failure = c.WWISEC_AK_Monitor_ErrorCode_AudioDeviceInitFailure,
    audio_device_remove_failure = c.WWISEC_AK_Monitor_ErrorCode_AudioDeviceRemoveFailure,
    audio_device_not_found = c.WWISEC_AK_Monitor_ErrorCode_AudioDeviceNotFound,
    audio_device_not_valid = c.WWISEC_AK_Monitor_ErrorCode_AudioDeviceNotValid,
    spatial_audio_listener_automation_not_supported = c.WWISEC_AK_Monitor_ErrorCode_SpatialAudio_ListenerAutomationNotSupported,
    media_duplication_length = c.WWISEC_AK_Monitor_ErrorCode_MediaDuplicationLength,
    hw_voices_system_init_failed = c.WWISEC_AK_Monitor_ErrorCode_HwVoicesSystemInitFailed,
    hw_voices_decode_batch_failed = c.WWISEC_AK_Monitor_ErrorCode_HwVoicesDecodeBatchFailed,
    hw_voice_limit_reached = c.WWISEC_AK_Monitor_ErrorCode_HwVoiceLimitReached,
    hw_voice_init_failed = c.WWISEC_AK_Monitor_ErrorCode_HwVoiceInitFailed,
    opus_hw_command_failed = c.WWISEC_AK_Monitor_ErrorCode_OpusHWCommandFailed,
    add_output_listener_id_with_zero_listeners = c.WWISEC_AK_Monitor_ErrorCode_AddOutputListenerIdWithZeroListeners,
    @"3d_object_limit_exceeded" = c.WWISEC_AK_Monitor_ErrorCode_3DObjectLimitExceeded,
    opus_hw_fatal_error = c.WWISEC_AK_Monitor_ErrorCode_OpusHWFatalError,
    opus_hw_decode_unavailable = c.WWISEC_AK_Monitor_ErrorCode_OpusHWDecodeUnavailable,
    opus_hw_timeout = c.WWISEC_AK_Monitor_ErrorCode_OpusHWTimeout,
    system_audio_objects_unavailable = c.WWISEC_AK_Monitor_ErrorCode_SystemAudioObjectsUnavailable,
    add_output_no_distinct_listener = c.WWISEC_AK_Monitor_ErrorCode_AddOutputNoDistinctListener,
    plugin_cannot_run_on_object_config = c.WWISEC_AK_Monitor_ErrorCode_PluginCannotRunOnObjectConfig,
    spatial_audio_reflection_bus_error = c.WWISEC_AK_Monitor_ErrorCode_SpatialAudio_ReflectionBusError,
    vorbis_hw_decode_unavailable = c.WWISEC_AK_Monitor_ErrorCode_VorbisHWDecodeUnavailable,
    external_source_no_memory_size = c.WWISEC_AK_Monitor_ErrorCode_ExternalSourceNoMemorySize,
    monitor_queue_full = c.WWISEC_AK_Monitor_ErrorCode_MonitorQueueFull,
    monitor_msg_too_large = c.WWISEC_AK_Monitor_ErrorCode_MonitorMsgTooLarge,
    non_compliant_device_memory = c.WWISEC_AK_Monitor_ErrorCode_NonCompliantDeviceMemory,
    job_worker_func_call_mismatch = c.WWISEC_AK_Monitor_ErrorCode_JobWorkerFuncCallMismatch,
    job_mgr_out_of_memory = c.WWISEC_AK_Monitor_ErrorCode_JobMgrOutOfMemory,
    invalid_file_size = c.WWISEC_AK_Monitor_ErrorCode_InvalidFileSize,
    plugin_msg = c.WWISEC_AK_Monitor_ErrorCode_PluginMsg,
    sink_open_sl = c.WWISEC_AK_Monitor_ErrorCode_SinkOpenSL,
    audio_out_of_range = c.WWISEC_AK_Monitor_ErrorCode_AudioOutOfRange,
    audio_out_of_range_on_bus = c.WWISEC_AK_Monitor_ErrorCode_AudioOutOfRangeOnBus,
    audio_out_of_range_on_bus_fx = c.WWISEC_AK_Monitor_ErrorCode_AudioOutOfRangeOnBusFx,
    audio_out_of_range_ray = c.WWISEC_AK_Monitor_ErrorCode_AudioOutOfRangeRay,
    unknown_dialogue_event = c.WWISEC_AK_Monitor_ErrorCode_UnknownDialogueEvent,
    failed_posting_event = c.WWISEC_AK_Monitor_ErrorCode_FailedPostingEvent,
    output_device_initialization_failed = c.WWISEC_AK_Monitor_ErrorCode_OutputDeviceInitializationFailed,
    unload_bank_failed = c.WWISEC_AK_Monitor_ErrorCode_UnloadBankFailed,
    plugin_file_not_found = c.WWISEC_AK_Monitor_ErrorCode_PluginFileNotFound,
    plugin_file_incompatible = c.WWISEC_AK_Monitor_ErrorCode_PluginFileIncompatible,
    plugin_file_not_enough_memory_to_start = c.WWISEC_AK_Monitor_ErrorCode_PluginFileNotEnoughMemoryToStart,
    plugin_file_invalid = c.WWISEC_AK_Monitor_ErrorCode_PluginFileInvalid,
    plugin_file_register_failed = c.WWISEC_AK_Monitor_ErrorCode_PluginFileRegisterFailed,
    unknown_argument = c.WWISEC_AK_Monitor_ErrorCode_UnknownArgument,
    dynamic_sequence_already_closed = c.WWISEC_AK_Monitor_ErrorCode_DynamicSequenceAlreadyClosed,
    pending_action_destroyed = c.WWISEC_AK_Monitor_ErrorCode_PendingActionDestroyed,
    cross_fade_transition_ignored = c.WWISEC_AK_Monitor_ErrorCode_CrossFadeTransitionIgnored,
    music_renderer_seeking_failed = c.WWISEC_AK_Monitor_ErrorCode_MusicRendererSeekingFailed,
    dynamic_sequence_id_not_found = c.WWISEC_AK_Monitor_ErrorCode_DynamicSequenceIdNotFound,
    bus_not_found_by_name = c.WWISEC_AK_Monitor_ErrorCode_BusNotFoundByName,
    audio_device_share_set_not_found = c.WWISEC_AK_Monitor_ErrorCode_AudioDeviceShareSetNotFound,
    audio_device_share_set_not_found_by_name = c.WWISEC_AK_Monitor_ErrorCode_AudioDeviceShareSetNotFoundByName,
    sound_engine_too_many_game_objects = c.WWISEC_AK_Monitor_ErrorCode_SoundEngineTooManyGameObjects,
    sound_engine_too_many_positions = c.WWISEC_AK_Monitor_ErrorCode_SoundEngineTooManyPositions,
    sound_engine_cant_call_on_child_bus = c.WWISEC_AK_Monitor_ErrorCode_SoundEngineCantCallOnChildBus,
    sound_engine_playing_id_not_found = c.WWISEC_AK_Monitor_ErrorCode_SoundEnginePlayingIdNotFound,
    sound_engine_invalid_transform = c.WWISEC_AK_Monitor_ErrorCode_SoundEngineInvalidTransform,
    sound_engine_too_many_event_posts = c.WWISEC_AK_Monitor_ErrorCode_SoundEngineTooManyEventPosts,
    audio_subsystem_stopped_responding = c.WWISEC_AK_Monitor_ErrorCode_AudioSubsystemStoppedResponding,
    not_enough_mem_in_function = c.WWISEC_AK_Monitor_ErrorCode_NotEnoughMemInFunction,
    fx_not_found = c.WWISEC_AK_Monitor_ErrorCode_FXNotFound,
    set_mixer_not_a_bus = c.WWISEC_AK_Monitor_ErrorCode_SetMixerNotABus,
    audio_node_not_found = c.WWISEC_AK_Monitor_ErrorCode_AudioNodeNotFound,
    set_mixer_failed = c.WWISEC_AK_Monitor_ErrorCode_SetMixerFailed,
    set_bus_config_unsupported = c.WWISEC_AK_Monitor_ErrorCode_SetBusConfigUnsupported,
    bus_not_found = c.WWISEC_AK_Monitor_ErrorCode_BusNotFound,
    mismatching_media_size = c.WWISEC_AK_Monitor_ErrorCode_MismatchingMediaSize,
    incompatible_bank_version = c.WWISEC_AK_Monitor_ErrorCode_IncompatibleBankVersion,
    unexpected_prepare_game_syncs_call = c.WWISEC_AK_Monitor_ErrorCode_UnexpectedPrepareGameSyncsCall,
    music_engine_not_initialized = c.WWISEC_AK_Monitor_ErrorCode_MusicEngineNotInitialized,
    loading_bank_mismatch = c.WWISEC_AK_Monitor_ErrorCode_LoadingBankMismatch,
    master_bus_structure_not_loaded = c.WWISEC_AK_Monitor_ErrorCode_MasterBusStructureNotLoaded,
    too_many_children = c.WWISEC_AK_Monitor_ErrorCode_TooManyChildren,
    bank_contain_uneditable_effect = c.WWISEC_AK_Monitor_ErrorCode_BankContainUneditableEffect,
    memory_allocation_failed = c.WWISEC_AK_Monitor_ErrorCode_MemoryAllocationFailed,
    invalid_float_priority = c.WWISEC_AK_Monitor_ErrorCode_InvalidFloatPriority,
    sound_load_failed_insufficient_memory = c.WWISEC_AK_Monitor_ErrorCode_SoundLoadFailedInsufficientMemory,
    nx_device_registration_failed = c.WWISEC_AK_Monitor_ErrorCode_NXDeviceRegistrationFailed,
    mix_plugin_on_object_bus = c.WWISEC_AK_Monitor_ErrorCode_MixPluginOnObjectBus,
    xbox_xma_voice_reset_failed = c.WWISEC_AK_Monitor_ErrorCode_XboxXMAVoiceResetFailed,
    xbox_acp_message = c.WWISEC_AK_Monitor_ErrorCode_XboxACPMessage,
    xbox_frame_dropped = c.WWISEC_AK_Monitor_ErrorCode_XboxFrameDropped,
    xbox_acp_error = c.WWISEC_AK_Monitor_ErrorCode_XboxACPError,
    xbox_xma_fatal_error = c.WWISEC_AK_Monitor_ErrorCode_XboxXMAFatalError,
    missing_music_node_parent = c.WWISEC_AK_Monitor_ErrorCode_MissingMusicNodeParent,
    hardware_opus_decoder_error = c.WWISEC_AK_Monitor_ErrorCode_HardwareOpusDecoderError,
    set_geometry_too_many_triangle_connected = c.WWISEC_AK_Monitor_ErrorCode_SetGeometryTooManyTriangleConnected,
    set_geometry_triangle_too_large = c.WWISEC_AK_Monitor_ErrorCode_SetGeometryTriangleTooLarge,
    set_geometry_failed = c.WWISEC_AK_Monitor_ErrorCode_SetGeometryFailed,
    removing_geometry_set_failed = c.WWISEC_AK_Monitor_ErrorCode_RemovingGeometrySetFailed,
    set_geometry_instance_failed = c.WWISEC_AK_Monitor_ErrorCode_SetGeometryInstanceFailed,
    removing_geometry_instance_failed = c.WWISEC_AK_Monitor_ErrorCode_RemovingGeometryInstanceFailed,
    reverting_to_default_audio_device = c.WWISEC_AK_Monitor_ErrorCode_RevertingToDefaultAudioDevice,
    reverting_to_dummy_audio_device = c.WWISEC_AK_Monitor_ErrorCode_RevertingToDummyAudioDevice,
    audio_thread_suspended = c.WWISEC_AK_Monitor_ErrorCode_AudioThreadSuspended,
    audio_thread_resumed = c.WWISEC_AK_Monitor_ErrorCode_AudioThreadResumed,
    reset_playlist_action_ignored_global_scope = c.WWISEC_AK_Monitor_ErrorCode_ResetPlaylistActionIgnoredGlobalScope,
    reset_playlist_action_ignored_continuous = c.WWISEC_AK_Monitor_ErrorCode_ResetPlaylistActionIgnoredContinuous,
    playing_trigger_rate_not_supported = c.WWISEC_AK_Monitor_ErrorCode_PlayingTriggerRateNotSupported,
    set_geometry_triangle_is_skipped = c.WWISEC_AK_Monitor_ErrorCode_SetGeometryTriangleIsSkipped,
    set_geometry_instance_invalid_transform = c.WWISEC_AK_Monitor_ErrorCode_SetGeometryInstanceInvalidTransform,
    set_game_object_radius_size_error = c.WWISEC_AK_Monitor_ErrorCode_SetGameObjectRadiusSizeError,
    set_portal_non_distinct_room = c.WWISEC_AK_Monitor_ErrorCode_SetPortalNonDistinctRoom,
    set_portal_invalid_extent = c.WWISEC_AK_Monitor_ErrorCode_SetPortalInvalidExtent,
    spatial_audio_portal_not_found = c.WWISEC_AK_Monitor_ErrorCode_SpatialAudio_PortalNotFound,
    invalid_float_in_function = c.WWISEC_AK_Monitor_ErrorCode_InvalidFloatInFunction,
    fltmax_not_supported = c.WWISEC_AK_Monitor_ErrorCode_FLTMAXNotSupported,
    cannot_initialize_ambisonic_channel_configuration = c.WWISEC_AK_Monitor_ErrorCode_CannotInitializeAmbisonicChannelConfiguration,
    cannot_initialize_passthrough = c.WWISEC_AK_Monitor_ErrorCode_CannotInitializePassthrough,
    @"3d_audio_unsupported_size" = c.WWISEC_AK_Monitor_ErrorCode_3DAudioUnsupportedSize,
    ambisonic_not_available = c.WWISEC_AK_Monitor_ErrorCode_AmbisonicNotAvailable,
    no_audio_device = c.WWISEC_AK_Monitor_ErrorCode_NoAudioDevice,
    support = c.WWISEC_AK_Monitor_ErrorCode_Support,
    replay_message = c.WWISEC_AK_Monitor_ErrorCode_ReplayMessage,
    game_message = c.WWISEC_AK_Monitor_ErrorCode_GameMessage,
    test_message = c.WWISEC_AK_Monitor_ErrorCode_TestMessage,
    translator_standard_tag_test = c.WWISEC_AK_Monitor_ErrorCode_TranslatorStandardTagTest,
    translator_wwise_tag_test = c.WWISEC_AK_Monitor_ErrorCode_TranslatorWwiseTagTest,
    translator_string_size_test = c.WWISEC_AK_Monitor_ErrorCode_TranslatorStringSizeTest,
    invalid_parameter = c.WWISEC_AK_Monitor_ErrorCode_InvalidParameter,
    max_audio_obj_exceeded = c.WWISEC_AK_Monitor_ErrorCode_MaxAudioObjExceeded,
    mms_not_enabled = c.WWISEC_AK_Monitor_ErrorCode_MMSNotEnabled,
    not_enough_system_obj = c.WWISEC_AK_Monitor_ErrorCode_NotEnoughSystemObj,
    not_enough_system_obj_win = c.WWISEC_AK_Monitor_ErrorCode_NotEnoughSystemObjWin,
    transition_not_accurate_source_too_short = c.WWISEC_AK_Monitor_ErrorCode_TransitionNotAccurateSourceTooShort,
    already_initialized = c.WWISEC_AK_Monitor_ErrorCode_AlreadyInitialized,
    wrong_number_of_arguments = c.WWISEC_AK_Monitor_ErrorCode_WrongNumberOfArguments,
    data_alignement = c.WWISEC_AK_Monitor_ErrorCode_DataAlignement,
    plugin_msg_with_share_set = c.WWISEC_AK_Monitor_ErrorCode_PluginMsgWithShareSet,
    sound_engine_not_init = c.WWISEC_AK_Monitor_ErrorCode_SoundEngineNotInit,
    no_default_switch = c.WWISEC_AK_Monitor_ErrorCode_NoDefaultSwitch,
    cant_set_bound_switch = c.WWISEC_AK_Monitor_ErrorCode_CantSetBoundSwitch,
    io_device_init_failed = c.WWISEC_AK_Monitor_ErrorCode_IODeviceInitFailed,
    switch_list_empty = c.WWISEC_AK_Monitor_ErrorCode_SwitchListEmpty,
    no_switch_selected = c.WWISEC_AK_Monitor_ErrorCode_NoSwitchSelected,
};

pub const LocalOutputFunc = ?*const fn (in_error_code: ErrorCode, in_error: [*:0]const common.AkOSChar, in_error_level: ErrorLevel, in_playing_id: common.AkPlayingID, in_game_object_id: common.AkGameObjectID) callconv(.C) void;

pub const PostCodeOptionalArgs = struct {
    playing_id: common.AkPlayingID = common.AK_INVALID_PLAYING_ID,
    game_obj_id: common.AkGameObjectID = common.AK_INVALID_GAME_OBJECT,
    audio_node_id: common.AkUniqueID = common.AK_INVALID_UNIQUE_ID,
    is_bus: bool = false,
};

pub fn postCode(in_error: ErrorCode, in_error_level: ErrorLevel, optional_args: PostCodeOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_Monitor_PostCode(
            @intFromEnum(in_error),
            in_error_level.toC(),
            optional_args.playing_id,
            optional_args.game_obj_id,
            optional_args.audio_node_id,
            optional_args.is_bus,
        ),
    );
}

pub const PostStringOptionalArgs = struct {
    playing_id: common.AkPlayingID = common.AK_INVALID_PLAYING_ID,
    game_obj_id: common.AkGameObjectID = common.AK_INVALID_GAME_OBJECT,
    audio_node_id: common.AkUniqueID = common.AK_INVALID_UNIQUE_ID,
    is_bus: bool = false,
};

pub fn postString(fallback_allocator: std.mem.Allocator, in_error: []const u8, in_error_level: ErrorLevel, optional_args: PostStringOptionalArgs) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_error = common.toCString(allocator, in_error) catch return common.WwiseError.Fail;
    defer allocator.free(raw_error);

    return common.handleAkResult(
        c.WWISEC_AK_Monitor_PostString(
            raw_error,
            in_error_level.toC(),
            optional_args.playing_id,
            optional_args.game_obj_id,
            optional_args.audio_node_id,
            optional_args.is_bus,
        ),
    );
}

pub const SetLocalOutputOptionalArgs = struct {
    error_level: ErrorLevel = ErrorLevel.All,
    monitor_func: LocalOutputFunc = null,
};

pub fn setLocalOutput(optional_args: SetLocalOutputOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_Monitor_SetLocalOutput(
            @intCast(optional_args.error_level.toC()),
            @ptrCast(optional_args.monitor_func),
        ),
    );
}

pub const AddTranslatorOptionalArgs = struct {
    override_previous_translators: bool = false,
};

pub fn addTranslator(translator: *error_message_translator.AkErrorMessageTranslator, optional_args: AddTranslatorOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_Monitor_AddTranslator(
            @ptrCast(translator),
            optional_args.override_previous_translators,
        ),
    );
}

pub fn resetTranslator() common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_Monitor_ResetTranslator(),
    );
}

pub fn getTimeStamp() common.AkTimeMs {
    return c.WWISEC_AK_Monitor_GetTimeStamp();
}

pub fn monitorStreamMgrInit(in_stream_mgr_settings: *const StreamMgr.AkStreamMgrSettings) void {
    c.WWISEC_AK_Monitor_MonitorStreamMgrInit(@ptrCast(in_stream_mgr_settings));
}

pub fn monitorStreamingDeviceInit(in_device_id: common.AkDeviceID, in_device_settings: *const StreamMgr.AkDeviceSettings) void {
    c.WWISEC_AK_Monitor_MonitorStreamingDeviceInit(in_device_id, @ptrCast(in_device_settings));
}

pub fn monitorStreamingDeviceDestroyed(in_device_id: common.AkDeviceID) void {
    c.WWISEC_AK_Monitor_MonitorStreamingDeviceDestroyed(in_device_id);
}

pub fn monitorStreamMgrTerm() void {
    c.WWISEC_AK_Monitor_MonitorStreamMgrTerm();
}

pub inline fn akMonitorError(in_error_code: ErrorCode) common.WwiseError!void {
    if (builtin.mode == .debug) {
        return postCode(in_error_code, ErrorLevel{ .@"error" = true }, .{});
    }
}

pub inline fn akMonitorStreamMgrInit(in_stream_mgr_settings: *const StreamMgr.AkStreamMgrSettings) void {
    if (builtin.mode == .debug) {
        monitorStreamMgrInit(in_stream_mgr_settings);
    }
}

pub inline fn akMonitorStreamingDeviceInit(in_device_id: common.AkDeviceID, in_device_settings: *const StreamMgr.AkDeviceSettings) void {
    if (builtin.mode == .debug) {
        monitorStreamingDeviceInit(in_device_id, in_device_settings);
    }
}

pub inline fn akMonitorStreamingDeviceDestroyed(in_device_id: common.AkDeviceID) void {
    if (builtin.mode == .debug) {
        monitorStreamingDeviceDestroyed(in_device_id);
    }
}

pub inline fn akMonitorStreamMgrTerm() void {
    if (builtin.mode == .debug) {
        monitorStreamMgrTerm();
    }
}
