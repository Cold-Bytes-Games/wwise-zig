const std = @import("std");
const builtin = @import("builtin");
const c = @import("c.zig");
const common = @import("common.zig");
const speaker_config = @import("speaker_config.zig");

pub const AkJobWorkerFunc = c.WWISEC_AkJobWorkerFunc;
pub const AkJobMgrSettings = struct {
    fn_request_job_worker: FuncRequestJobWorker,
    max_active_workers: [c.WWISEC_AK_NUM_JOB_TYPES]u32,
    num_memory_slabs: u32,
    memory_slab_size: u32,
    p_client_data: ?*anyopaque,

    pub const FuncRequestJobWorker = c.WWISEC_AkJobMgrSettings_FuncRequestJobWorker;

    pub fn fromC(job_mgr_settings: c.WWISEC_AkJobMgrSettings) AkJobMgrSettings {
        return .{
            .fn_request_job_worker = job_mgr_settings.fnRequestJobWorker,
            .max_active_workers = job_mgr_settings.uMaxActiveWorkers,
            .num_memory_slabs = job_mgr_settings.uNumMemorySlabs,
            .memory_slab_size = job_mgr_settings.uMemorySlabSize,
            .p_client_data = job_mgr_settings.pClientData,
        };
    }

    pub fn toC(self: AkJobMgrSettings) c.WWISEC_AkJobMgrSettings {
        return .{
            .fnRequestJobWorker = self.fn_request_job_worker,
            .uMaxActiveWorkers = self.max_active_workers,
            .uNumMemorySlabs = self.num_memory_slabs,
            .uMemorySlabSize = self.memory_slab_size,
            .pClientData = self.p_client_data,
        };
    }
};

pub const AkOutputSettings = struct {
    audio_device_shareset: common.AkUniqueID,
    id_device: u32,
    panning_rule: common.AkPanningRule,
    channel_config: speaker_config.AkChannelConfig,

    pub fn init(fallback_allocator: std.mem.Allocator, device_shareset: []const u8, id_device: common.AkUniqueID, channel_config: speaker_config.AkChannelConfig, panning: common.AkPanningRule) !AkOutputSettings {
        var raw_output_settings: c.WWISEC_AkOutputSettings = undefined;

        var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_char_allocator.get();

        const device_shareset_cstr = try common.toCString(allocator, device_shareset);
        defer allocator.free(device_shareset_cstr);

        c.WWISEC_AkOutputSettings_Init(&raw_output_settings, device_shareset_cstr, id_device, channel_config.toC(), @enumToInt(panning));

        return fromC(raw_output_settings);
    }

    pub fn fromC(output_settings: c.WWISEC_AkOutputSettings) AkOutputSettings {
        return .{
            .audio_device_shareset = output_settings.audioDeviceShareset,
            .id_device = output_settings.idDevice,
            .panning_rule = @intToEnum(common.AkPanningRule, output_settings.ePanningRule),
            .channel_config = speaker_config.AkChannelConfig.fromC(output_settings.channelConfig),
        };
    }

    pub fn toC(self: AkOutputSettings) c.WWISEC_AkOutputSettings {
        return c.WWISEC_AkOutputSettings{
            .audioDeviceShareset = self.audio_device_shareset,
            .idDevice = self.id_device,
            .ePanningRule = @enumToInt(self.panning_rule),
            .channelConfig = self.channel_config.toC(),
        };
    }
};

pub const AkFloorPlane = enum(i32) {
    xz = c.WWISEC_AkFloorPlane_XZ,
    xy = c.WWISEC_AkFloorPlane_XY,
    yz = c.WWISEC_AkFloorPlane_YZ,

    pub const Default = AkFloorPlane.xz;
};

pub const AkAssertHook = c.WWISEC_AkAssertHook;
pub const AkBackgroundMusicChangeCallbackFunc = c.WWISEC_AkBackgroundMusicChangeCallbackFunc;
pub const AkProfilerPushTimerFunc = c.WWISEC_AkProfilerPushTimerFunc;
pub const AkProfilerPopTimerFunc = c.WWISEC_AkProfilerPopTimerFunc;
pub const AkProfilerPostMarkerFunc = c.WWISEC_AkProfilerPostMarkerFunc;

pub const AkInitSettings = struct {
    pfn_assert_hook: AkAssertHook,
    max_num_paths: u32,
    command_queue_size: u32,
    enable_game_sync_preparation: bool,
    continuous_playback_look_ahead: u32,
    num_samples_per_frame: u32,
    monitor_queue_pool_size: u32,
    cpu_monitor_queue_max_size: u32,
    settings_main_output: AkOutputSettings,
    settings_job_manager: AkJobMgrSettings,
    max_hardware_timeout_ms: u32,
    use_sound_bank_mgr_thread: bool,
    use_lengine_thread: bool,
    bgm_callback: AkBackgroundMusicChangeCallbackFunc,
    bgm_callback_cookie: ?*anyopaque,
    plugin_dll_path: []const u8,
    floor_plane: AkFloorPlane,
    game_units_to_meters: f32,
    bank_read_buffer_size: u32,
    debug_out_of_range_limit: f32,
    debug_out_of_range_check_enabled: bool,
    fn_profiler_push_timer: AkProfilerPushTimerFunc,
    fn_profiler_pop_timer: AkProfilerPopTimerFunc,
    fn_profiler_post_marker: AkProfilerPostMarkerFunc,

    pub fn fromC(init_settings: c.WWISEC_AkInitSettings) AkInitSettings {
        return .{
            .pfn_assert_hook = init_settings.pfnAssertHook,
            .max_num_paths = init_settings.uMaxNumPaths,
            .command_queue_size = init_settings.uCommandQueueSize,
            .enable_game_sync_preparation = init_settings.bEnableGameSyncPreparation,
            .continuous_playback_look_ahead = init_settings.uContinuousPlaybackLookAhead,
            .num_samples_per_frame = init_settings.uNumSamplesPerFrame,
            .monitor_queue_pool_size = init_settings.uMonitorQueuePoolSize,
            .cpu_monitor_queue_max_size = init_settings.uCpuMonitorQueueMaxSize,
            .settings_main_output = AkOutputSettings.fromC(init_settings.settingsMainOutput),
            .settings_job_manager = AkJobMgrSettings.fromC(init_settings.settingsJobManager),
            .max_hardware_timeout_ms = init_settings.uMaxHardwareTimeoutMs,
            .use_sound_bank_mgr_thread = init_settings.bUseSoundBankMgrThread,
            .use_lengine_thread = init_settings.bUseLEngineThread,
            .bgm_callback = init_settings.BGMCallback,
            .bgm_callback_cookie = init_settings.BGMCallbackCookie,
            .plugin_dll_path = "", // NOTE: mlarouche: the plugin_dll_path is meant to be overriden by the user, the default init settings does not supply DLL path.
            .floor_plane = @intToEnum(AkFloorPlane, init_settings.eFloorPlane),
            .game_units_to_meters = init_settings.fGameUnitsToMeters,
            .bank_read_buffer_size = init_settings.uBankReadBufferSize,
            .debug_out_of_range_limit = init_settings.fDebugOutOfRangeLimit,
            .debug_out_of_range_check_enabled = init_settings.bDebugOutOfRangeCheckEnabled,
            .fn_profiler_push_timer = init_settings.fnProfilerPushTimer,
            .fn_profiler_pop_timer = init_settings.fnProfilerPopTimer,
            .fn_profiler_post_marker = init_settings.fnProfilerPostMarker,
        };
    }

    pub fn toC(self: AkInitSettings, allocator: std.mem.Allocator) !c.WWISEC_AkInitSettings {
        return .{
            .pfnAssertHook = self.pfn_assert_hook,
            .uMaxNumPaths = self.max_num_paths,
            .uCommandQueueSize = self.command_queue_size,
            .bEnableGameSyncPreparation = self.enable_game_sync_preparation,
            .uContinuousPlaybackLookAhead = self.continuous_playback_look_ahead,
            .uNumSamplesPerFrame = self.num_samples_per_frame,
            .uMonitorQueuePoolSize = self.monitor_queue_pool_size,
            .uCpuMonitorQueueMaxSize = self.cpu_monitor_queue_max_size,
            .settingsMainOutput = self.settings_main_output.toC(),
            .settingsJobManager = self.settings_job_manager.toC(),
            .uMaxHardwareTimeoutMs = self.max_hardware_timeout_ms,
            .bUseSoundBankMgrThread = self.use_sound_bank_mgr_thread,
            .bUseLEngineThread = self.use_lengine_thread,
            .BGMCallback = self.bgm_callback,
            .BGMCallbackCookie = self.bgm_callback_cookie,
            .szPluginDLLPath = try common.toOSChar(allocator, self.plugin_dll_path),
            .eFloorPlane = @enumToInt(self.floor_plane),
            .fGameUnitsToMeters = self.game_units_to_meters,
            .uBankReadBufferSize = self.bank_read_buffer_size,
            .fDebugOutOfRangeLimit = self.debug_out_of_range_limit,
            .bDebugOutOfRangeCheckEnabled = self.debug_out_of_range_check_enabled,
            .fnProfilerPushTimer = self.fn_profiler_push_timer,
            .fnProfilerPopTimer = self.fn_profiler_pop_timer,
            .fnProfilerPostMarker = self.fn_profiler_post_marker,
        };
    }
};

pub const AkThreadProperties = blk: {
    switch (builtin.os.tag) {
        .windows => {
            break :blk WIN_AkThreadProperties;
        },
        .linux, .ios, .macos => {
            break :blk POSIX_AkThreadProperties;
        },
        else => {
            @compileError("Implement AkThreadProperties for the platform");
        },
    }
};

pub const WIN_AkThreadProperties = struct {
    priority: i32,
    affinity_mask: u32,
    stack_size: u32,

    pub fn fromC(thread_properties: c.WWISEC_WIN_AkThreadProperties) WIN_AkThreadProperties {
        return .{
            .priority = thread_properties.nPriority,
            .affinity_mask = thread_properties.dwAffinityMask,
            .stack_size = thread_properties.uStackSize,
        };
    }

    pub fn toC(self: WIN_AkThreadProperties) c.WWISEC_WIN_AkThreadProperties {
        return .{
            .nPriority = self.priority,
            .dwAffinityMask = self.affinity_mask,
            .uStackSize = self.stack_size,
        };
    }
};

pub const POSIX_AkThreadProperties = struct {
    priority: i32,
    stack_size: usize,
    sched_policy: i32,
    affinity_mask: u32,

    pub fn fromC(thread_properties: c.WWISEC_POSIX_AkThreadProperties) POSIX_AkThreadProperties {
        return .{
            .priority = thread_properties.nPriority,
            .stack_size = thread_properties.uStackSize,
            .sched_policy = thread_properties.uSchedPolicy,
            .affinity_mask = thread_properties.dwAffinityMask,
        };
    }

    pub fn toC(self: POSIX_AkThreadProperties) c.WWISEC_POSIX_AkThreadProperties {
        return .{
            .nPriority = self.priority,
            .uStackSize = self.stack_size,
            .uSchedPolicy = self.sched_policy,
            .dwAffinityMask = self.affinity_mask,
        };
    }
};

pub const AkPlatformInitSettings = blk: {
    switch (builtin.os.tag) {
        .windows => {
            break :blk WIN_AkPlatformInitSettings;
        },
        .linux => {
            if (builtin.target.isAndroid()) {
                break :blk ANDROID_AkPlatformInitSettings;
            }

            break :blk LINUX_AkPlatformInitSettings;
        },
        .macos => {
            break :blk MACOSX_AkPlatformInitSettings;
        },
        .ios => {
            break :blk IOS_AkPlatformInitSettings;
        },
        else => {
            @compileError("Implement AkPlatformInitSettings for the platform");
        },
    }
};

pub const WIN_AkPlatformInitSettings = struct {
    hwnd: ?*anyopaque,
    thread_l_engine: AkThreadProperties,
    thread_output_mgr: AkThreadProperties,
    thread_bank_manager: AkThreadProperties,
    thread_monitor: AkThreadProperties,
    num_refills_in_voice: u16,
    sample_rate: u32,
    enable_avx_support: bool,
    max_system_audio_objects: u32,

    pub fn fromC(init_settings: c.WWISEC_WIN_AkPlatformInitSettings) WIN_AkPlatformInitSettings {
        return .{
            .hwnd = init_settings.hWnd,
            .thread_l_engine = AkThreadProperties.fromC(init_settings.threadLEngine),
            .thread_output_mgr = AkThreadProperties.fromC(init_settings.threadOutputMgr),
            .thread_bank_manager = AkThreadProperties.fromC(init_settings.threadBankManager),
            .thread_monitor = AkThreadProperties.fromC(init_settings.threadMonitor),
            .num_refills_in_voice = init_settings.uNumRefillsInVoice,
            .sample_rate = init_settings.uSampleRate,
            .enable_avx_support = init_settings.bEnableAvxSupport,
            .max_system_audio_objects = init_settings.uMaxSystemAudioObjects,
        };
    }

    pub fn toC(self: WIN_AkPlatformInitSettings) c.WWISEC_WIN_AkPlatformInitSettings {
        return .{
            .hWnd = self.hwnd,
            .threadLEngine = self.thread_l_engine.toC(),
            .threadOutputMgr = self.thread_output_mgr.toC(),
            .threadBankManager = self.thread_bank_manager.toC(),
            .threadMonitor = self.thread_monitor.toC(),
            .uNumRefillsInVoice = self.num_refills_in_voice,
            .uSampleRate = self.sample_rate,
            .bEnableAvxSupport = self.enable_avx_support,
            .uMaxSystemAudioObjects = self.max_system_audio_objects,
        };
    }
};

pub const AkAudioAPILinux = packed struct {
    pulse_audio: bool = false,
    alsa: bool = false,

    pub const Default = .{ .pulse_audio = true, .alsa = true };

    pub fn fromC(value: c.WWISEC_AkAudioAPILinux) AkAudioAPILinux {
        return @bitCast(AkAudioAPILinux, value);
    }

    pub fn toC(self: AkAudioAPILinux) c.WWISEC_AkAudioAPILinux {
        return @bitCast(c.WWISEC_AkAudioAPILinux, self);
    }
};

pub const LINUX_AkPlatformInitSettings = struct {
    thread_l_engine: AkThreadProperties,
    thread_output_mgr: AkThreadProperties,
    thread_bank_manager: AkThreadProperties,
    thread_monitor: AkThreadProperties,
    sample_rate: u32,
    num_refills_in_voice: u16,
    audio_api: AkAudioAPILinux = AkAudioAPILinux.Default,
    sample_type: common.AkDataTypeID,

    pub fn fromC(init_settings: c.WWISEC_LINUX_AkPlatformInitSettings) LINUX_AkPlatformInitSettings {
        return .{
            .thread_l_engine = AkThreadProperties.fromC(init_settings.threadLEngine),
            .thread_output_mgr = AkThreadProperties.fromC(init_settings.threadOutputMgr),
            .thread_bank_manager = AkThreadProperties.fromC(init_settings.threadBankManager),
            .thread_monitor = AkThreadProperties.fromC(init_settings.threadMonitor),
            .sample_rate = init_settings.uSampleRate,
            .num_refills_in_voice = init_settings.uNumRefillsInVoice,
            .audio_api = AkAudioAPILinux.fromC(init_settings.eAudioAPI),
            .sample_type = init_settings.sampleType,
        };
    }

    pub fn toC(self: LINUX_AkPlatformInitSettings) c.Ak_LINUX_PlatformInitSettings {
        return .{
            .threadLEngine = self.thread_l_engine.toC(),
            .threadOutputMgr = self.thread_output_mgr.toC(),
            .threadBankManager = self.thread_bank_manager.toC(),
            .threadMonitor = self.thread_monitor.toC(),
            .uSampleRate = self.sample_rate,
            .uNumRefillsInVoice = self.num_refills_in_voice,
            .eAudioAPI = self.audio_api.toC(),
            .sampleType = self.sample_type.toC(),
        };
    }
};

pub const MACOSX_AkPlatformInitSettings = struct {
    thread_l_engine: AkThreadProperties,
    thread_output_mgr: AkThreadProperties,
    thread_bank_manager: AkThreadProperties,
    thread_monitor: AkThreadProperties,

    sample_rate: u32,
    num_refills_in_voice: u16,

    pub fn fromC(init_settings: c.WWISEC_MACOSX_AkPlatformInitSettings) MACOSX_AkPlatformInitSettings {
        return .{
            .thread_l_engine = AkThreadProperties.fromC(init_settings.threadLEngine),
            .thread_output_mgr = AkThreadProperties.fromC(init_settings.threadOutputMgr),
            .thread_bank_manager = AkThreadProperties.fromC(init_settings.threadBankManager),
            .thread_monitor = AkThreadProperties.fromC(init_settings.threadMonitor),
            .sample_rate = init_settings.uSampleRate,
            .num_refills_in_voice = init_settings.uNumRefillsInVoice,
        };
    }

    pub fn toC(self: MACOSX_AkPlatformInitSettings) c.WWISEC_MACOSX_AkPlatformInitSettings {
        return .{
            .threadLEngine = self.thread_l_engine.toC(),
            .threadOutputMgr = self.thread_output_mgr.toC(),
            .threadBankManager = self.thread_bank_manager.toC(),
            .threadMonitor = self.thread_monitor.toC(),
            .uSampleRate = self.sample_rate,
            .uNumRefillsInVoice = self.num_refills_in_voice,
        };
    }
};

pub const IOS_AkAudioSessionCategory = enum(i32) {
    ambient = c.WWISEC_IOS_AkAudioSessionCategoryAmbient,
    solo_ambient = c.WWISEC_IOS_AkAudioSessionCategorySoloAmbient,
    play_and_record = c.WWISEC_IOS_AkAudioSessionCategoryPlayAndRecord,
    playback = c.WWISEC_IOS_AkAudioSessionCategoryPlayback,
};

pub const IOS_AkAudioSessionCategoryOptions = enum(i32) {
    mix_with_others = c.WWISEC_IOS_AkAudioSessionCategoryOptionMixWithOthers,
    duck_others = c.WWISEC_IOS_AkAudioSessionCategoryOptionDuckOthers,
    allow_bluetooth = c.WWISEC_IOS_AkAudioSessionCategoryOptionAllowBluetooth,
    default_to_speaker = c.WWISEC_IOS_AkAudioSessionCategoryOptionDefaultToSpeaker,
    allow_bluetooth_a2dp = c.WWISEC_IOS_AkAudioSessionCategoryOptionAllowBluetoothA2DP,
};

pub const IOS_AkAudioSessionMode = enum(i32) {
    default = c.WWISEC_IOS_AkAudioSessionModeDefault,
    voice_chat = c.WWISEC_IOS_AkAudioSessionModeVoiceChat,
    game_chat = c.WWISEC_IOS_AkAudioSessionModeGameChat,
    video_recording = c.WWISEC_IOS_AkAudioSessionModeVideoRecording,
    measurement = c.WWISEC_IOS_AkAudioSessionModeMeasurement,
    movie_playback = c.WWISEC_IOS_AkAudioSessionModeMoviePlayback,
    video_chat = c.WWISEC_IOS_AkAudioSessionModeVideoChat,
};

pub const IOS_AkAudioSessionSetActiveOptions = enum(i32) {
    notify_others_on_deactivation = c.WWISEC_IOS_AkAudioSessionSetActiveOptionNotifyOthersOnDeactivation,
};

pub const IOS_AkAudioSessionBehaviorOptions = enum(i32) {
    suspend_in_background = c.WWISEC_IOS_AkAudioSessionBehaviorSuspendInBackground,
};

pub const IOS_AkAudioSessionProperties = struct {
    category: IOS_AkAudioSessionCategory,
    category_options: IOS_AkAudioSessionCategoryOptions,
    mode: IOS_AkAudioSessionMode,
    set_activate_options: IOS_AkAudioSessionSetActiveOptions,
    audio_session_behavior: IOS_AkAudioSessionBehaviorOptions,

    pub fn fromC(value: c.WWISEC_IOS_AkAudioSessionProperties) IOS_AkAudioSessionProperties {
        return .{
            .category = @intToEnum(IOS_AkAudioSessionCategory, value.eCategory),
            .category_options = @intToEnum(IOS_AkAudioSessionCategoryOptions, value.eCategoryOptions),
            .mode = @intToEnum(IOS_AkAudioSessionMode, value.eMode),
            .set_activate_options = @intToEnum(IOS_AkAudioSessionSetActiveOptions, value.eSetActivateOptions),
            .audio_session_behavior = @intToEnum(IOS_AkAudioSessionBehaviorOptions, value.eAudioSessionBehavior),
        };
    }

    pub fn toC(self: IOS_AkAudioSessionProperties) c.WWISEC_IOS_AkAudioSessionProperties {
        return .{
            .eCategory = @enumToInt(self.category),
            .categoeCategoryOptionsry_options = @enumToInt(self.category_options),
            .eMode = @enumToInt(self.mode),
            .eSetActivateOptions = @enumToInt(self.set_activate_options),
            .eAudioSessionBehavior = @enumToInt(self.audio_session_behavior),
        };
    }
};

pub const IOS_AudioInputCallbackFunc = c.WWISEC_IOS_AudioInputCallbackFunc;
pub const IOS_AudioInterruptionCallbackFunc = c.WWISEC_IOS_AudioInterruptionCallbackFunc;

pub const IOS_AkAudioCallbacks = struct {
    input_callback: IOS_AudioInputCallbackFunc,
    input_callback_cookie: ?*anyopaque,
    interruption_callback: IOS_AudioInterruptionCallbackFunc,
    interruption_callback_cookie: ?*anyopaque,

    pub fn fromC(value: c.WWISEC_IOS_AkAudioCallbacks) IOS_AkAudioCallbacks {
        return .{
            .input_callback = value.inputCallback,
            .input_callback_cookie = value.inputCallbackCookie,
            .interruption_callback = value.interruptionCallback,
            .interruption_callback_cookie = value.interruptionCallbackCookie,
        };
    }

    pub fn toC(self: IOS_AkAudioCallbacks) c.WWISEC_IOS_AkAudioCallbacks {
        return .{
            .inputCallback = self.input_callback,
            .inputCallbackCookie = self.input_callback_cookie,
            .interruptionCallback = self.interruption_callback,
            .interruptionCallbackCookie = self.interruption_callback_cookie,
        };
    }
};

pub const IOS_AkPlatformInitSettings = struct {
    thread_l_engine: AkThreadProperties,
    thread_output_mgr: AkThreadProperties,
    thread_bank_manager: AkThreadProperties,
    thread_monitor: AkThreadProperties,
    sample_rate: u32,
    num_refills_in_voice: u16,
    audio_session: IOS_AkAudioSessionProperties,
    audio_callbacks: IOS_AkAudioCallbacks,
    verbose_system_output: bool,

    pub fn fromC(init_settings: c.WWISEC_IOS_AkPlatformInitSettings) IOS_AkPlatformInitSettings {
        return .{
            .thread_l_engine = AkThreadProperties.fromC(init_settings.threadLEngine),
            .thread_output_mgr = AkThreadProperties.fromC(init_settings.threadOutputMgr),
            .thread_bank_manager = AkThreadProperties.fromC(init_settings.threadBankManager),
            .thread_monitor = AkThreadProperties.fromC(init_settings.threadMonitor),
            .sample_rate = init_settings.uSampleRate,
            .num_refills_in_voice = init_settings.uNumRefillsInVoice,
            .audio_session = IOS_AkAudioSessionProperties.fromC(init_settings.audioSession),
            .audio_callbacks = IOS_AkAudioCallbacks.fromC(init_settings.audioCallbacks),
            .verbose_system_output = init_settings.bVerboseSystemOutput,
        };
    }

    pub fn toC(self: IOS_AkPlatformInitSettings) c.WWISEC_IOS_AkPlatformInitSettings {
        return .{
            .threadLEngine = self.thread_l_engine.toC(),
            .threadOutputMgr = self.thread_output_mgr.toC(),
            .threadBankManager = self.thread_bank_manager.toC(),
            .threadMonitor = self.thread_monitor.toC(),
            .uSampleRate = self.sample_rate,
            .uNumRefillsInVoice = self.num_refills_in_voice,
            .audioSession = self.audio_session.toC(),
            .audioCallbacks = self.audio_callbacks.toC(),
            .bVerboseSystemOutput = self.verbose_system_output,
        };
    }
};

pub const AkAudioAPIAndroid = packed struct {
    aaudio: bool = false,
    opensl_es: bool = false,

    pub const Default = .{ .aaudio = true, .opensl_es = true };

    pub fn fromC(value: c.WWISEC_AkAudioAPIAndroid) AkAudioAPIAndroid {
        return @bitCast(AkAudioAPIAndroid, value);
    }

    pub fn toC(self: AkAudioAPIAndroid) c.WWISEC_AkAudioAPIAndroid {
        return @bitCast(c.WWISEC_AkAudioAPIAndroid, self);
    }
};

pub const ANDROID_AkPlatformInitSettings = struct {
    thread_l_engine: AkThreadProperties,
    thread_output_mgr: AkThreadProperties,
    thread_bank_manager: AkThreadProperties,
    thread_monitor: AkThreadProperties,
    audio_api: AkAudioAPIAndroid,
    sample_rate: u32,
    num_refills_in_voice: u16,
    round_frame_size_to_hw_size: bool,
    p_sl_engine: ?*anyopaque,
    p_java_vm: ?*anyopaque,
    j_activity: ?*anyopaque,
    verbose_sink: bool,
    enable_low_latency: bool,

    pub fn fromC(init_settings: c.WWISEC_ANDROID_AkPlatformInitSettings) ANDROID_AkPlatformInitSettings {
        return .{
            .thread_l_engine = AkThreadProperties.fromC(init_settings.threadLEngine),
            .thread_output_mgr = AkThreadProperties.fromC(init_settings.threadOutputMgr),
            .thread_bank_manager = AkThreadProperties.fromC(init_settings.threadBankManager),
            .thread_monitor = AkThreadProperties.fromC(init_settings.threadMonitor),
            .audio_api = AkAudioAPIAndroid.fromC(init_settings.eAudioAPI),
            .sample_rate = init_settings.uSampleRate,
            .num_refills_in_voice = init_settings.uNumRefillsInVoice,
            .round_frame_size_to_hw_size = init_settings.bRoundFrameSizeToHWSize,
            .p_sl_engine = init_settings.pSLEngine,
            .p_java_vm = init_settings.pJavaVM,
            .j_activity = init_settings.jActivity,
            .verbose_sink = init_settings.bVerboseSink,
            .enable_low_latency = init_settings.bEnableLowLatency,
        };
    }

    pub fn toC(self: ANDROID_AkPlatformInitSettings) c.WWISEC_ANDROID_AkPlatformInitSettings {
        return .{
            .threadLEngine = self.thread_l_engine.toC(),
            .threadOutputMgr = self.thread_output_mgr.toC(),
            .threadBankManager = self.thread_bank_manager.toC(),
            .threadMonitor = self.thread_monitor.toC(),
            .eAudioAPI = self.audio_api.toC(),
            .uSampleRate = self.sample_rate,
            .uNumRefillsInVoice = self.num_refills_in_voice,
            .bRoundFrameSizeToHWSize = self.round_frame_size_to_hw_size,
            .pSLEngine = self.p_sl_engine,
            .pJavaVM = self.p_java_vm,
            .jActivity = self.j_activity,
            .bVerboseSink = self.verbose_sink,
            .bEnableLowLatency = self.enable_low_latency,
        };
    }
};
