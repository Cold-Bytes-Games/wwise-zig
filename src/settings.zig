const std = @import("std");
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

pub const AkFloorPlane = enum(u32) {
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

    pub fn deinit(self: AkInitSettings, allocator: std.mem.Allocator) void {
        allocator.free(self.plugin_dll_path);
    }

    pub fn fromC(allocator: std.mem.Allocator, init_settings: c.WWISEC_AkInitSettings) !AkInitSettings {
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
            .plugin_dll_path = try common.fromOSChar(allocator, init_settings.szPluginDLLPath),
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
