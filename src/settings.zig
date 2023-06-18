const std = @import("std");
const builtin = @import("builtin");
const c = @import("c.zig");
const common = @import("common.zig");
const speaker_config = @import("speaker_config.zig");

pub const AkJobWorkerFunc = ?*const fn (in_job_type: common.AkJobType, in_execution_time_usec: u32) callconv(.C) void;

pub const AkJobMgrSettings = extern struct {
    fn_request_job_worker: FuncRequestJobWorker = null,
    max_active_workers: [common.AK_NUM_JOB_TYPES]u32 = [_]u32{0} ** common.AK_NUM_JOB_TYPES,
    num_memory_slabs: u32 = 0,
    memory_slab_size: u32 = 0,
    p_client_data: ?*anyopaque = null,

    pub const FuncRequestJobWorker = c.WWISEC_AkJobMgrSettings_FuncRequestJobWorker;

    pub inline fn fromC(value: c.WWISEC_AkJobMgrSettings) AkJobMgrSettings {
        return @bitCast(AkJobMgrSettings, value);
    }

    pub inline fn toC(self: AkJobMgrSettings) c.WWISEC_AkJobMgrSettings {
        return @bitCast(c.WWISEC_AkJobMgrSettings, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkJobMgrSettings) == @sizeOf(c.WWISEC_AkJobMgrSettings));
    }
};

pub const AkOutputSettings = extern struct {
    audio_device_shareset: common.AkUniqueID = 0,
    id_device: u32 = 0,
    panning_rule: common.AkPanningRule = .speakers,
    channel_config: speaker_config.AkChannelConfig = .{},

    pub fn init(fallback_allocator: std.mem.Allocator, device_shareset: []const u8, id_device: common.AkUniqueID, channel_config: speaker_config.AkChannelConfig, panning: common.AkPanningRule) !AkOutputSettings {
        var raw_output_settings: c.WWISEC_AkOutputSettings = undefined;

        var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_char_allocator.get();

        const device_shareset_cstr = try common.toCString(allocator, device_shareset);
        defer allocator.free(device_shareset_cstr);

        c.WWISEC_AkOutputSettings_Init(&raw_output_settings, device_shareset_cstr, id_device, channel_config.toC(), @enumToInt(panning));

        return fromC(raw_output_settings);
    }

    pub inline fn fromC(value: c.WWISEC_AkOutputSettings) AkOutputSettings {
        return @bitCast(AkOutputSettings, value);
    }

    pub inline fn toC(self: AkOutputSettings) c.WWISEC_AkOutputSettings {
        return @bitCast(c.WWISEC_AkOutputSettings, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkOutputSettings) == @sizeOf(c.WWISEC_AkOutputSettings));
    }
};

pub const AkFloorPlane = enum(common.DefaultEnumType) {
    xz = c.WWISEC_AkFloorPlane_XZ,
    xy = c.WWISEC_AkFloorPlane_XY,
    yz = c.WWISEC_AkFloorPlane_YZ,

    pub const Default = AkFloorPlane.xz;
};

pub const AkAssertHook = ?*const fn (in_expression: ?[*:0]const u8, in_filename: ?[*:0]const u8, in_line_number: i32) callconv(.C) void;
pub const AkBackgroundMusicChangeCallbackFunc = ?*const fn (in_background_music_muted: bool, in_cookie: ?*anyopaque) callconv(.C) common.AKRESULT;
pub const AkProfilerPushTimerFunc = ?*const fn (in_plugin_id: common.AkPluginID, in_zone_name: ?[*:0]const u8) callconv(.C) void;
pub const AkProfilerPopTimerFunc = ?*const fn () callconv(.C) void;
pub const AkProfilerPostMarkerFunc = ?*const fn (in_plugin_id: common.AkPluginID, in_marker_name: ?[*:0]const u8) callconv(.C) void;

pub const AkInitSettings = struct {
    pfn_assert_hook: AkAssertHook = null,
    max_num_paths: u32 = 0,
    command_queue_size: u32 = 0,
    enable_game_sync_preparation: bool = false,
    continuous_playback_look_ahead: u32 = 0,
    num_samples_per_frame: u32 = 0,
    monitor_queue_pool_size: u32 = 0,
    cpu_monitor_queue_max_size: u32 = 0,
    settings_main_output: AkOutputSettings = .{},
    settings_job_manager: AkJobMgrSettings = .{},
    max_hardware_timeout_ms: u32 = 0,
    use_sound_bank_mgr_thread: bool = false,
    use_lengine_thread: bool = false,
    bgm_callback: AkBackgroundMusicChangeCallbackFunc = null,
    bgm_callback_cookie: ?*anyopaque = null,
    plugin_dll_path: []const u8 = "",
    floor_plane: AkFloorPlane = .xz,
    game_units_to_meters: f32 = 0.0,
    bank_read_buffer_size: u32 = 0,
    debug_out_of_range_limit: f32 = 0.0,
    debug_out_of_range_check_enabled: bool = false,
    fn_profiler_push_timer: AkProfilerPushTimerFunc = null,
    fn_profiler_pop_timer: AkProfilerPopTimerFunc = null,
    fn_profiler_post_marker: AkProfilerPostMarkerFunc = null,

    pub fn fromC(value: c.WWISEC_AkInitSettings) AkInitSettings {
        return .{
            .pfn_assert_hook = value.pfnAssertHook,
            .max_num_paths = value.uMaxNumPaths,
            .command_queue_size = value.uCommandQueueSize,
            .enable_game_sync_preparation = value.bEnableGameSyncPreparation,
            .continuous_playback_look_ahead = value.uContinuousPlaybackLookAhead,
            .num_samples_per_frame = value.uNumSamplesPerFrame,
            .monitor_queue_pool_size = value.uMonitorQueuePoolSize,
            .cpu_monitor_queue_max_size = value.uCpuMonitorQueueMaxSize,
            .settings_main_output = AkOutputSettings.fromC(value.settingsMainOutput),
            .settings_job_manager = AkJobMgrSettings.fromC(value.settingsJobManager),
            .max_hardware_timeout_ms = value.uMaxHardwareTimeoutMs,
            .use_sound_bank_mgr_thread = value.bUseSoundBankMgrThread,
            .use_lengine_thread = value.bUseLEngineThread,
            .bgm_callback = @ptrCast(AkBackgroundMusicChangeCallbackFunc, value.BGMCallback),
            .bgm_callback_cookie = value.BGMCallbackCookie,
            .plugin_dll_path = "", // NOTE: mlarouche: the plugin_dll_path is meant to be overriden by the user, the default init settings does not supply DLL path.
            .floor_plane = @intToEnum(AkFloorPlane, value.eFloorPlane),
            .game_units_to_meters = value.fGameUnitsToMeters,
            .bank_read_buffer_size = value.uBankReadBufferSize,
            .debug_out_of_range_limit = value.fDebugOutOfRangeLimit,
            .debug_out_of_range_check_enabled = value.bDebugOutOfRangeCheckEnabled,
            .fn_profiler_push_timer = value.fnProfilerPushTimer,
            .fn_profiler_pop_timer = @ptrCast(AkProfilerPopTimerFunc, value.fnProfilerPopTimer),
            .fn_profiler_post_marker = value.fnProfilerPostMarker,
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
            .BGMCallback = @ptrCast(c.WWISEC_AkBackgroundMusicChangeCallbackFunc, self.bgm_callback),
            .BGMCallbackCookie = self.bgm_callback_cookie,
            .szPluginDLLPath = @ptrCast([*]c.AkOSChar, try common.toOSChar(allocator, self.plugin_dll_path)),
            .eFloorPlane = @enumToInt(self.floor_plane),
            .fGameUnitsToMeters = self.game_units_to_meters,
            .uBankReadBufferSize = self.bank_read_buffer_size,
            .fDebugOutOfRangeLimit = self.debug_out_of_range_limit,
            .bDebugOutOfRangeCheckEnabled = self.debug_out_of_range_check_enabled,
            .fnProfilerPushTimer = self.fn_profiler_push_timer,
            .fnProfilerPopTimer = @ptrCast(c.WWISEC_AkProfilerPopTimerFunc, self.fn_profiler_pop_timer),
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

pub const WIN_AkThreadProperties = extern struct {
    priority: i32 = 0,
    affinity_mask: u32 = 0,
    stack_size: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_WIN_AkThreadProperties) WIN_AkThreadProperties {
        return @bitCast(WIN_AkThreadProperties, value);
    }

    pub inline fn toC(self: WIN_AkThreadProperties) c.WWISEC_WIN_AkThreadProperties {
        return @bitCast(c.WWISEC_WIN_AkThreadProperties, self);
    }

    comptime {
        std.debug.assert(@sizeOf(WIN_AkThreadProperties) == @sizeOf(c.WWISEC_WIN_AkThreadProperties));
    }
};

pub const POSIX_AkThreadProperties = extern struct {
    priority: i32 = 0,
    stack_size: usize = 0,
    sched_policy: i32 = 0,
    affinity_mask: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_POSIX_AkThreadProperties) POSIX_AkThreadProperties {
        return @bitCast(POSIX_AkThreadProperties, value);
    }

    pub inline fn toC(self: POSIX_AkThreadProperties) c.WWISEC_POSIX_AkThreadProperties {
        return @bitCast(c.WWISEC_POSIX_AkThreadProperties, self);
    }

    comptime {
        std.debug.assert(@sizeOf(POSIX_AkThreadProperties) == @sizeOf(c.WWISEC_POSIX_AkThreadProperties));
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

pub const WIN_AkPlatformInitSettings = extern struct {
    hwnd: ?*anyopaque = null,
    thread_l_engine: WIN_AkThreadProperties = .{},
    thread_output_mgr: WIN_AkThreadProperties = .{},
    thread_bank_manager: WIN_AkThreadProperties = .{},
    thread_monitor: WIN_AkThreadProperties = .{},
    num_refills_in_voice: u16 = 0,
    sample_rate: u32 = 0,
    enable_avx_support: bool = false,
    max_system_audio_objects: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_WIN_AkPlatformInitSettings) WIN_AkPlatformInitSettings {
        return @bitCast(WIN_AkPlatformInitSettings, value);
    }

    pub inline fn toC(self: WIN_AkPlatformInitSettings) c.WWISEC_WIN_AkPlatformInitSettings {
        return @bitCast(c.WWISEC_WIN_AkPlatformInitSettings, self);
    }

    comptime {
        std.debug.assert(@sizeOf(WIN_AkPlatformInitSettings) == @sizeOf(c.WWISEC_WIN_AkPlatformInitSettings));
    }
};

pub const AkAudioAPILinux = packed struct(common.DefaultEnumType) {
    pulse_audio: bool = false,
    alsa: bool = false,
    padding: u30 = 0,

    pub const Default = .{ .pulse_audio = true, .alsa = true };

    pub fn fromC(value: c.WWISEC_AkAudioAPILinux) AkAudioAPILinux {
        return @bitCast(AkAudioAPILinux, value);
    }

    pub fn toC(self: AkAudioAPILinux) c.WWISEC_AkAudioAPILinux {
        return @bitCast(c.WWISEC_AkAudioAPILinux, self);
    }
};

pub const LINUX_AkPlatformInitSettings = extern struct {
    thread_l_engine: POSIX_AkThreadProperties = .{},
    thread_output_mgr: POSIX_AkThreadProperties = .{},
    thread_bank_manager: POSIX_AkThreadProperties = .{},
    thread_monitor: POSIX_AkThreadProperties = .{},
    sample_rate: u32 = 0,
    num_refills_in_voice: u16 = 0,
    audio_api: AkAudioAPILinux = AkAudioAPILinux.Default,
    sample_type: common.AkDataTypeID = 0,

    pub inline fn fromC(value: c.WWISEC_LINUX_AkPlatformInitSettings) LINUX_AkPlatformInitSettings {
        return @bitCast(LINUX_AkPlatformInitSettings, value);
    }

    pub inline fn toC(self: LINUX_AkPlatformInitSettings) c.WWISEC_LINUX_AkPlatformInitSettings {
        return @bitCast(c.WWISEC_LINUX_AkPlatformInitSettings, self);
    }

    comptime {
        std.debug.assert(@sizeOf(LINUX_AkPlatformInitSettings) == @sizeOf(c.WWISEC_LINUX_AkPlatformInitSettings));
    }
};

pub const MACOSX_AkPlatformInitSettings = extern struct {
    thread_l_engine: POSIX_AkThreadProperties = .{},
    thread_output_mgr: POSIX_AkThreadProperties = .{},
    thread_bank_manager: POSIX_AkThreadProperties = .{},
    thread_monitor: POSIX_AkThreadProperties = .{},

    sample_rate: u32 = 0,
    num_refills_in_voice: u16 = 0,

    pub inline fn fromC(value: c.WWISEC_MACOSX_AkPlatformInitSettings) MACOSX_AkPlatformInitSettings {
        return @bitCast(MACOSX_AkPlatformInitSettings, value);
    }

    pub inline fn toC(self: MACOSX_AkPlatformInitSettings) c.WWISEC_MACOSX_AkPlatformInitSettings {
        return @bitCast(c.WWISEC_MACOSX_AkPlatformInitSettings, self);
    }

    comptime {
        std.debug.assert(@sizeOf(MACOSX_AkPlatformInitSettings) == @sizeOf(c.WWISEC_MACOSX_AkPlatformInitSettings));
    }
};

pub const IOS_AkAudioSessionCategory = enum(common.DefaultEnumType) {
    ambient = c.WWISEC_IOS_AkAudioSessionCategoryAmbient,
    solo_ambient = c.WWISEC_IOS_AkAudioSessionCategorySoloAmbient,
    play_and_record = c.WWISEC_IOS_AkAudioSessionCategoryPlayAndRecord,
    playback = c.WWISEC_IOS_AkAudioSessionCategoryPlayback,
};

pub const IOS_AkAudioSessionCategoryOptions = enum(common.DefaultEnumType) {
    mix_with_others = c.WWISEC_IOS_AkAudioSessionCategoryOptionMixWithOthers,
    duck_others = c.WWISEC_IOS_AkAudioSessionCategoryOptionDuckOthers,
    allow_bluetooth = c.WWISEC_IOS_AkAudioSessionCategoryOptionAllowBluetooth,
    default_to_speaker = c.WWISEC_IOS_AkAudioSessionCategoryOptionDefaultToSpeaker,
    allow_bluetooth_a2dp = c.WWISEC_IOS_AkAudioSessionCategoryOptionAllowBluetoothA2DP,
};

pub const IOS_AkAudioSessionMode = enum(common.DefaultEnumType) {
    default = c.WWISEC_IOS_AkAudioSessionModeDefault,
    voice_chat = c.WWISEC_IOS_AkAudioSessionModeVoiceChat,
    game_chat = c.WWISEC_IOS_AkAudioSessionModeGameChat,
    video_recording = c.WWISEC_IOS_AkAudioSessionModeVideoRecording,
    measurement = c.WWISEC_IOS_AkAudioSessionModeMeasurement,
    movie_playback = c.WWISEC_IOS_AkAudioSessionModeMoviePlayback,
    video_chat = c.WWISEC_IOS_AkAudioSessionModeVideoChat,
};

pub const IOS_AkAudioSessionSetActiveOptions = enum(common.DefaultEnumType) {
    notify_others_on_deactivation = c.WWISEC_IOS_AkAudioSessionSetActiveOptionNotifyOthersOnDeactivation,
};

pub const IOS_AkAudioSessionBehaviorOptions = enum(common.DefaultEnumType) {
    suspend_in_background = c.WWISEC_IOS_AkAudioSessionBehaviorSuspendInBackground,
};

pub const IOS_AkAudioSessionProperties = extern struct {
    category: IOS_AkAudioSessionCategory = .ambient,
    category_options: IOS_AkAudioSessionCategoryOptions = .mix_with_others,
    mode: IOS_AkAudioSessionMode = .default,
    set_activate_options: IOS_AkAudioSessionSetActiveOptions = .notify_others_on_deactivation,
    audio_session_behavior: IOS_AkAudioSessionBehaviorOptions = .suspend_in_background,

    pub inline fn fromC(value: c.WWISEC_IOS_AkAudioSessionProperties) IOS_AkAudioSessionProperties {
        return @bitCast(IOS_AkAudioSessionProperties, value);
    }

    pub inline fn toC(self: IOS_AkAudioSessionProperties) c.WWISEC_IOS_AkAudioSessionProperties {
        return @bitCast(c.WWISEC_IOS_AkAudioSessionProperties, self);
    }

    comptime {
        std.debug.assert(@sizeOf(IOS_AkAudioSessionProperties) == @sizeOf(c.WWISEC_IOS_AkAudioSessionProperties));
    }
};

pub const IOS_AudioInputCallbackFunc = c.WWISEC_IOS_AudioInputCallbackFunc;
pub const IOS_AudioInterruptionCallbackFunc = c.WWISEC_IOS_AudioInterruptionCallbackFunc;

pub const IOS_AkAudioCallbacks = extern struct {
    input_callback: IOS_AudioInputCallbackFunc = null,
    input_callback_cookie: ?*anyopaque = null,
    interruption_callback: IOS_AudioInterruptionCallbackFunc = null,
    interruption_callback_cookie: ?*anyopaque = null,

    pub inline fn fromC(value: c.WWISEC_IOS_AkAudioCallbacks) IOS_AkAudioCallbacks {
        return @bitCast(IOS_AkAudioCallbacks, value);
    }

    pub inline fn toC(self: IOS_AkAudioCallbacks) c.WWISEC_IOS_AkAudioCallbacks {
        return @bitCast(c.WWISEC_IOS_AkAudioCallbacks, self);
    }

    comptime {
        std.debug.assert(@sizeOf(IOS_AkAudioCallbacks) == @sizeOf(c.WWISEC_IOS_AkAudioCallbacks));
    }
};

pub const IOS_AkPlatformInitSettings = extern struct {
    thread_l_engine: POSIX_AkThreadProperties = .{},
    thread_output_mgr: POSIX_AkThreadProperties = .{},
    thread_bank_manager: POSIX_AkThreadProperties = .{},
    thread_monitor: POSIX_AkThreadProperties = .{},
    sample_rate: u32 = 0,
    num_refills_in_voice: u16 = 0,
    audio_session: IOS_AkAudioSessionProperties = .{},
    audio_callbacks: IOS_AkAudioCallbacks = .{},
    verbose_system_output: bool = false,

    pub inline fn fromC(value: c.WWISEC_IOS_AkPlatformInitSettings) IOS_AkPlatformInitSettings {
        return @bitCast(IOS_AkPlatformInitSettings, value);
    }

    pub inline fn toC(self: IOS_AkPlatformInitSettings) c.WWISEC_IOS_AkPlatformInitSettings {
        return @bitCast(c.WWISEC_IOS_AkPlatformInitSettings, self);
    }

    comptime {
        std.debug.assert(@sizeOf(IOS_AkPlatformInitSettings) == @sizeOf(c.WWISEC_IOS_AkPlatformInitSettings));
    }
};

pub const AkAudioAPIAndroid = packed struct(common.DefaultEnumType) {
    aaudio: bool = false,
    opensl_es: bool = false,
    pad: u30 = 0,

    pub const Default = .{ .aaudio = true, .opensl_es = true };

    pub inline fn fromC(value: c.WWISEC_AkAudioAPIAndroid) AkAudioAPIAndroid {
        return @bitCast(AkAudioAPIAndroid, value);
    }

    pub inline fn toC(self: AkAudioAPIAndroid) c.WWISEC_AkAudioAPIAndroid {
        return @bitCast(c.WWISEC_AkAudioAPIAndroid, self);
    }
};

pub const ANDROID_AkPlatformInitSettings = extern struct {
    thread_l_engine: POSIX_AkThreadProperties = .{},
    thread_output_mgr: POSIX_AkThreadProperties = .{},
    thread_bank_manager: POSIX_AkThreadProperties = .{},
    thread_monitor: POSIX_AkThreadProperties = .{},
    audio_api: AkAudioAPIAndroid = AkAudioAPIAndroid.Default,
    sample_rate: u32 = 0,
    num_refills_in_voice: u16 = 0,
    round_frame_size_to_hw_size: bool = false,
    p_sl_engine: ?*anyopaque = null,
    p_java_vm: ?*anyopaque = null,
    j_activity: ?*anyopaque = null,
    verbose_sink: bool = false,
    enable_low_latency: bool = false,

    pub inline fn fromC(value: c.WWISEC_ANDROID_AkPlatformInitSettings) ANDROID_AkPlatformInitSettings {
        return @bitCast(ANDROID_AkPlatformInitSettings, value);
    }

    pub inline fn toC(self: ANDROID_AkPlatformInitSettings) c.WWISEC_ANDROID_AkPlatformInitSettings {
        return @bitCast(c.WWISEC_ANDROID_AkPlatformInitSettings, self);
    }

    comptime {
        std.debug.assert(@sizeOf(ANDROID_AkPlatformInitSettings) == @sizeOf(c.WWISEC_ANDROID_AkPlatformInitSettings));
    }
};
