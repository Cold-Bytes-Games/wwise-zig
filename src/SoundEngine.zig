const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const callback = @import("callback.zig");
const common_defs = @import("common_defs.zig");
const IAkPlugin = @import("IAkPlugin.zig");
const midi_types = @import("midi_types.zig");
const settings = @import("settings.zig");
const speaker_config = @import("speaker_config.zig");

pub const AkSourcePosition = extern struct {
    audio_node_id: common.AkUniqueID = 0,
    media_id: common.AkUniqueID = 0,
    ms_time: common.AkTimeMs = 0,
    sample_position: u32 = 0,
    update_buffer_tick: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_AkSourcePosition) AkSourcePosition {
        return @bitCast(AkSourcePosition, value);
    }

    pub inline fn toC(self: AkSourcePosition) c.WWISEC_AkSourcePosition {
        return @bitCast(c.WWISEC_AkSourcePosition, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkSourcePosition) == @sizeOf(c.WWISEC_AkSourcePosition));
    }
};

pub const MultiPositionType = enum(common.DefaultEnumType) {
    single_source = c.WWISEC_AK_SoundEngine_MultiPositionType_SingleSource,
    multi_sources = c.WWISEC_AK_SoundEngine_MultiPositionType_MultiSources,
    multi_directions = c.WWISEC_AK_SoundEngine_MultiPositionType_MultiDirections,
};

pub const PreparationType = enum(common.DefaultEnumType) {
    load = c.WWISEC_AK_SoundEngine_Preparation_Load,
    unload = c.WWISEC_AK_SoundEngine_Preparation_Unload,
    load_and_decode = c.WWISEC_AK_SoundEngine_Preparation_LoadAndDecode,
};

pub const AkBankContent = enum(common.DefaultEnumType) {
    structure_only = c.WWISEC_AK_SoundEngine_AkBankContent_StructureOnly,
    all = c.WWISEC_AK_SoundEngine_AkBankContent_All,
};

pub fn isInitialized() bool {
    return c.WWISEC_AK_SoundEngine_IsInitialized();
}

pub fn init(fallback_allocator: std.mem.Allocator, init_settings_opt: ?*settings.AkInitSettings, platform_init_settings_opt: ?*settings.AkPlatformInitSettings) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var native_init_settings_ptr = blk: {
        if (init_settings_opt) |init_settings| {
            var native_init_settings = init_settings.toC(allocator) catch return common.WwiseError.Fail;
            break :blk &native_init_settings;
        }

        break :blk @as(?*c.WWISEC_AkInitSettings, null);
    };

    defer {
        if (native_init_settings_ptr) |native_init_settings| {
            allocator.free(native_init_settings.szPluginDLLPath[0..std.mem.len(native_init_settings.szPluginDLLPath)]);
        }
    }

    var native_platform_init_settings_ptr = blk: {
        if (platform_init_settings_opt) |platform_init_settings| {
            break :blk @ptrCast(?*c.WWISEC_AkPlatformInitSettings, platform_init_settings);
        }
        break :blk @as(?*c.WWISEC_AkPlatformInitSettings, null);
    };

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Init(native_init_settings_ptr, native_platform_init_settings_ptr),
    );
}

pub fn getDefaultInitSettings(init_settings: *settings.AkInitSettings) void {
    var native_settings: c.WWISEC_AkInitSettings = undefined;
    c.WWISEC_AK_SoundEngine_GetDefaultInitSettings(&native_settings);

    init_settings.* = settings.AkInitSettings.fromC(native_settings);
}

pub fn getDefaultPlatformInitSettings(platform_init_settings: *settings.AkPlatformInitSettings) void {
    c.WWISEC_AK_SoundEngine_GetDefaultPlatformInitSettings(@ptrCast(*c.WWISEC_AkPlatformInitSettings, platform_init_settings));
}

pub fn term() void {
    c.WWISEC_AK_SoundEngine_Term();
}

pub fn getAudioSettings(out_settings: *common.AkAudioSettings) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetAudioSettings(@ptrCast(*c.WWISEC_AkAudioSettings, out_settings)),
    );
}

pub fn getSpeakerConfiguration(in_id_output: common.AkOutputDeviceID) speaker_config.AkChannelConfig {
    return speaker_config.AkChannelConfig.fromC(
        c.WWISEC_AK_SoundEngine_GetSpeakerConfiguration(in_id_output),
    );
}

pub fn getOutputDeviceConfiguration(in_id_output: common.AkOutputDeviceID, io_channel_config: *speaker_config.AkChannelConfig, io_capabilities: *common_defs.Ak3DAudioSinkCapabilities) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetOutputDeviceConfiguration(in_id_output, @ptrCast(*c.WWISEC_AkChannelConfig, io_channel_config), @ptrCast(*c.WWISEC_Ak3DAudioSinkCapabilities, io_capabilities)),
    );
}

pub fn getPanningRule(in_id_output: common.AkOutputDeviceID) common.WwiseError!common.AkPanningRule {
    var raw_panning_rule: c.WWISEC_AkPanningRule = undefined;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetPanningRule(&raw_panning_rule, in_id_output),
    );

    return @intToEnum(common.AkPanningRule, raw_panning_rule);
}

pub fn setPanningRule(in_panning_rule: common.AkPanningRule, in_id_output: common.AkOutputDeviceID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetPanningRule(@enumToInt(in_panning_rule), in_id_output),
    );
}

pub fn getSpeakerAngles(io_speaker_angles: ?*[]f32, io_num_angles: *u32, out_height_angle: *f32, in_id_output: common.AkOutputDeviceID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetSpeakerAngles(@ptrCast(?[*]f32, io_speaker_angles), io_num_angles, out_height_angle, in_id_output),
    );
}

pub fn setSpeakerAngles(in_speaker_angles: []const f32, in_height_angle: f32, in_id_output: common.AkOutputDeviceID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetSpeakerAngles(@ptrCast([*]const f32, in_speaker_angles), @truncate(u32, in_speaker_angles.len), in_height_angle, in_id_output),
    );
}

pub fn setVolumeThreshold(in_volume_threshold_db: f32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetVolumeThreshold(in_volume_threshold_db),
    );
}

pub fn setMaxNumVoicesLimit(in_max_number_voices: u16) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetMaxNumVoicesLimit(in_max_number_voices),
    );
}

pub fn setJobMgrMaxActiveWorkers(in_job_type: common.AkJobType, in_new_max_active_workers: u32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetJobMgrMaxActiveWorkers(in_job_type, in_new_max_active_workers),
    );
}

pub fn renderAudio(in_allow_sync_render: bool) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RenderAudio(in_allow_sync_render),
    );
}

pub fn getGlobalPluginContext() ?*IAkPlugin.IAkGlobalPluginContext {
    return @ptrCast(?*IAkPlugin.IAkGlobalPluginContext, c.WWISEC_AK_SoundEngine_GetGlobalPluginContext());
}

pub fn registerPlugin(in_type: common.AkPluginType, in_company_id: u32, in_plugin_id: u32, in_create_func: IAkPlugin.AkCreatePluginCallback, in_create_param_func: IAkPlugin.AkCreateParamCallback) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RegisterPlugin(
            @enumToInt(in_type),
            in_company_id,
            in_plugin_id,
            @ptrCast(c.WWISEC_AkCreatePluginCallback, in_create_func),
            @ptrCast(c.WWISEC_AkCreateParamCallback, in_create_param_func),
        ),
    );
}

pub fn registerPluginDLL(fallback_allocator: std.mem.Allocator, in_dll_name: []const u8, in_dll_path_opt: ?[]const u8) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var area_allocator = std.heap.ArenaAllocator.init(allocator);
    defer area_allocator.deinit();

    var raw_in_dll_name = common.toOSChar(area_allocator.allocator(), in_dll_name) catch return common.WwiseError.Fail;

    var raw_in_dll_path = blk: {
        if (in_dll_path_opt) |in_dll_path| {
            break :blk common.toOSChar(area_allocator.allocator(), in_dll_path) catch return common.WwiseError.Fail;
        }

        break :blk @as([*c]const c.AkOSChar, null);
    };

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RegisterPluginDLL(raw_in_dll_name, raw_in_dll_path),
    );
}

pub fn registerGlobalCallback(
    in_callback: callback.AkGlobalCallbackFunc,
    in_location: callback.AkGlobalCallbackLocation,
    in_cookie: ?*anyopaque,
    in_type: common.AkPluginType,
    in_company_id: u32,
    in_plugin_id: u32,
) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RegisterGlobalCallback(
            @ptrCast(c.WWISEC_AkGlobalCallbackFunc, in_callback),
            @intCast(u32, in_location.toC()),
            in_cookie,
            @enumToInt(in_type),
            in_company_id,
            in_plugin_id,
        ),
    );
}

pub fn unregisterGlobalCallback(in_callback: callback.AkGlobalCallbackFunc, in_location: callback.AkGlobalCallbackLocation) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnregisterGlobalCallback(
            @ptrCast(c.WWISEC_AkGlobalCallbackFunc, in_callback),
            @intCast(u32, in_location.toC()),
        ),
    );
}

pub fn registerResourceMonitorCallback(in_callback: callback.AkResourceMonitorCallbackFunc) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RegisterResourceMonitorCallback(@ptrCast(c.WWISEC_AkResourceMonitorCallbackFunc, in_callback)),
    );
}

pub fn unregisterResourceMonitorCallback(in_callback: callback.AkResourceMonitorCallbackFunc) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnregisterResourceMonitorCallback(@ptrCast(c.WWISEC_AkResourceMonitorCallbackFunc, in_callback)),
    );
}

pub fn registerAudioDeviceStatusCallback(in_callback: callback.AkDeviceStatusCallbackFunc) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RegisterAudioDeviceStatusCallback(@ptrCast(c.WWISEC_AK_AkDeviceStatusCallbackFunc, in_callback)),
    );
}

pub fn unregisterAudioDeviceStatusCallback() common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnregisterAudioDeviceStatusCallback(),
    );
}

pub fn getIDFromString(fallback_allocator: std.mem.Allocator, string: []const u8) !u32 {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_string = try common.toCString(allocator, string);
    defer allocator.free(raw_string);

    return c.WWISEC_AK_SoundEngine_GetIDFromString(raw_string);
}

pub const PostEventOptionalArgs = struct {
    flags: callback.AkCallbackType = .{},
    callback_func: callback.AkCallbackFunc = null,
    cookie: ?*anyopaque = null,
    allocator: ?std.mem.Allocator = null,
    external_sources: ?[]const common.AkExternalSourceInfo = null,
    playing_id: common.AkPlayingID = 0,
};

pub fn postEventID(in_eventID: common.AkUniqueID, game_object_id: common.AkGameObjectID, optional_args: PostEventOptionalArgs) !common.AkPlayingID {
    var num_external_sources: u32 = 0;

    var area_allocator_opt: ?std.heap.ArenaAllocator = null;
    defer {
        if (area_allocator_opt) |area_allocator| {
            area_allocator.deinit();
        }
    }

    const external_sources = blk: {
        if (optional_args.allocator) |allocator| {
            area_allocator_opt = std.heap.ArenaAllocator.init(allocator);
            if (optional_args.external_sources) |external_sources| {
                num_external_sources = @truncate(u32, external_sources.len);

                const raw_external_sources = try area_allocator_opt.?.allocator().alloc(c.WWISEC_AkExternalSourceInfo, num_external_sources);

                for (external_sources, 0..) |external_source, index| {
                    raw_external_sources[index] = try external_source.toC(area_allocator_opt.?.allocator());
                }

                break :blk raw_external_sources;
            }
        }

        break :blk &[0]c.WWISEC_AkExternalSourceInfo{};
    };

    const external_sources_ptr = blk: {
        if (external_sources.len > 0) {
            break :blk @ptrCast(?[*]c.WWISEC_AkExternalSourceInfo, @constCast(external_sources));
        }

        break :blk @as(?[*]c.WWISEC_AkExternalSourceInfo, null);
    };

    return c.WWISEC_AK_SoundEngine_PostEvent_ID(
        in_eventID,
        game_object_id,
        @intCast(u32, optional_args.flags.toC()),
        @ptrCast(c.WWISEC_AkCallbackFunc, optional_args.callback_func),
        optional_args.cookie,
        num_external_sources,
        external_sources_ptr,
        optional_args.playing_id,
    );
}

pub fn postEventString(fallback_allocator: std.mem.Allocator, in_event_name: []const u8, game_object_id: common.AkGameObjectID, optional_args: PostEventOptionalArgs) !common.AkPlayingID {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var char_allocator = stack_char_allocator.get();

    var raw_event_name = try common.toCString(char_allocator, in_event_name);
    defer char_allocator.free(raw_event_name);

    var num_external_sources: u32 = 0;

    var area_allocator_opt: ?std.heap.ArenaAllocator = null;
    defer {
        if (area_allocator_opt) |area_allocator| {
            area_allocator.deinit();
        }
    }

    const external_sources = blk: {
        if (optional_args.allocator) |allocator| {
            area_allocator_opt = std.heap.ArenaAllocator.init(allocator);
            if (optional_args.external_sources) |external_sources| {
                num_external_sources = @truncate(u32, external_sources.len);

                const raw_external_sources = try area_allocator_opt.?.allocator().alloc(c.WWISEC_AkExternalSourceInfo, num_external_sources);

                for (external_sources, 0..) |external_source, index| {
                    raw_external_sources[index] = try external_source.toC(area_allocator_opt.?.allocator());
                }

                break :blk raw_external_sources;
            }
        }

        break :blk &[0]c.WWISEC_AkExternalSourceInfo{};
    };

    const external_sources_ptr = blk: {
        if (external_sources.len > 0) {
            break :blk @ptrCast(?[*]c.WWISEC_AkExternalSourceInfo, @constCast(external_sources));
        }

        break :blk @as(?[*]c.WWISEC_AkExternalSourceInfo, null);
    };

    return c.WWISEC_AK_SoundEngine_PostEvent_String(
        raw_event_name,
        game_object_id,
        @intCast(u32, optional_args.flags.toC()),
        @ptrCast(c.WWISEC_AkCallbackFunc, optional_args.callback_func),
        optional_args.cookie,
        num_external_sources,
        external_sources_ptr,
        optional_args.playing_id,
    );
}

pub const AkActionOnEventType = enum(common.DefaultEnumType) {
    stop = c.WWISEC_AkActionOnEventType_Stop,
    pause = c.WWISEC_AkActionOnEventType_Pause,
    @"resume" = c.WWISEC_AkActionOnEventType_Resume,
    @"break" = c.WWISEC_AkActionOnEventType_Break,
    release_envelope = c.WWISEC_AkActionOnEventType_ReleaseEnvelope,
};

pub const ExecuteActionOnEventOptionalArgs = struct {
    game_object_id: common.AkGameObjectID = common.AK_INVALID_GAME_OBJECT,
    transition_duration: common.AkTimeMs = 0,
    fade_curve: common.AkCurveInterpolation = .linear,
    playing_id: common.AkPlayingID = common.AK_INVALID_PLAYING_ID,
};

pub fn executeActionOnEventID(in_event_id: common.AkUniqueID, in_action_type: AkActionOnEventType, optional_args: ExecuteActionOnEventOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_ExecuteActionOnEvent_ID(
            in_event_id,
            @enumToInt(in_action_type),
            optional_args.game_object_id,
            optional_args.transition_duration,
            @enumToInt(optional_args.fade_curve),
            optional_args.playing_id,
        ),
    );
}

pub fn executeActionOnEventString(fallback_allocator: std.mem.Allocator, in_event_name: []const u8, in_action_type: AkActionOnEventType, optional_args: ExecuteActionOnEventOptionalArgs) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_event_name = common.toCString(allocator, in_event_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_event_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_ExecuteActionOnEvent_String(
            raw_event_name,
            @enumToInt(in_action_type),
            optional_args.game_object_id,
            optional_args.transition_duration,
            @enumToInt(optional_args.fade_curve),
            optional_args.playing_id,
        ),
    );
}

pub const PostMIDIOnEventOptionalArgs = struct {
    absolute_offsets: bool = false,
    flags: callback.AkCallbackType = .{},
    callback: callback.AkCallbackFunc = null,
    cookie: ?*anyopaque = null,
    playing_id: common.AkPlayingID = common.AK_INVALID_PLAYING_ID,
};

pub fn postMIDIOnEvent(in_event_id: common.AkUniqueID, in_game_object_id: common.AkGameObjectID, in_midi_posts: []const midi_types.AkMIDIPost, optional_args: PostMIDIOnEventOptionalArgs) common.AkPlayingID {
    return c.WWISEC_AK_SoundEngine_PostMIDIOnEvent(
        in_event_id,
        in_game_object_id,
        @ptrCast([*]c.WWISEC_AkMIDIPost, @constCast(in_midi_posts)),
        @truncate(u16, in_midi_posts.len),
        optional_args.absolute_offsets,
        @intCast(u32, optional_args.flags.toC()),
        @ptrCast(c.WWISEC_AkCallbackFunc, optional_args.callback),
        optional_args.cookie,
        optional_args.playing_id,
    );
}

pub const StopMIDIOnEventOptionalArgs = struct {
    event_id: common.AkUniqueID = common.AK_INVALID_UNIQUE_ID,
    game_object_id: common.AkGameObjectID = common.AK_INVALID_GAME_OBJECT,
    playing_id: common.AkPlayingID = common.AK_INVALID_PLAYING_ID,
};

pub fn stopMIDIOnEvent(optional_args: StopMIDIOnEventOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_StopMIDIOnEvent(
            optional_args.event_id,
            optional_args.game_object_id,
            optional_args.playing_id,
        ),
    );
}

pub fn pinEventInStreamCacheID(in_event_id: common.AkUniqueID, in_active_priority: common.AkPriority, in_inactive_priority: common.AkPriority) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PinEventInStreamCache_ID(
            in_event_id,
            in_active_priority,
            in_inactive_priority,
        ),
    );
}

pub fn pinEventInStreamCacheString(fallback_allocator: std.mem.Allocator, in_event_name: []const u8, in_active_priority: common.AkPriority, in_inactive_priority: common.AkPriority) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_event_name = common.toCString(allocator, in_event_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_event_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PinEventInStreamCache_String(
            raw_event_name,
            in_active_priority,
            in_inactive_priority,
        ),
    );
}

pub fn unpinEventInStreamCacheID(in_event_id: common.AkUniqueID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnpinEventInStreamCache_ID(in_event_id),
    );
}

pub fn unpinEventInStreamCacheString(fallback_allocator: std.mem.Allocator, in_event_name: []const u8) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_event_name = common.toCString(allocator, in_event_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_event_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnpinEventInStreamCache_String(raw_event_name),
    );
}

pub fn getBufferStatusForPinnedEventID(in_event_id: common.AkUniqueID, out_percent_buffered: *f32, out_cache_pinned_memory_full: *bool) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetBufferStatusForPinnedEvent_ID(
            in_event_id,
            out_percent_buffered,
            out_cache_pinned_memory_full,
        ),
    );
}

pub fn getBufferStatusForPinnedEventString(fallback_allocator: std.mem.Allocator, in_event_name: []const u8, out_percent_buffered: *f32, out_cache_pinned_memory_full: *bool) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_event_name = common.toCString(allocator, in_event_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_event_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetBufferStatusForPinnedEvent_String(
            raw_event_name,
            out_percent_buffered,
            out_cache_pinned_memory_full,
        ),
    );
}

pub const SeekOnEventOptionalArgs = struct {
    seek_to_nearest_marker: bool = false,
    playing_id: common.AkPlayingID = common.AK_INVALID_PLAYING_ID,
};

pub fn seekOnEventTimeID(in_event_id: common.AkUniqueID, in_game_object: common.AkGameObjectID, in_position: common.AkTimeMs, optional_args: SeekOnEventOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SeekOnEvent_Time_ID(
            in_event_id,
            in_game_object,
            in_position,
            optional_args.seek_to_nearest_marker,
            optional_args.playing_id,
        ),
    );
}

pub fn seekOnEventTimeString(fallback_allocator: std.mem.Allocator, in_event_name: []const u8, in_game_object: common.AkGameObjectID, in_position: common.AkTimeMs, optional_args: SeekOnEventOptionalArgs) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_event_name = common.toCString(allocator, in_event_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_event_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SeekOnEvent_Time_String(
            raw_event_name,
            in_game_object,
            in_position,
            optional_args.seek_to_nearest_marker,
            optional_args.playing_id,
        ),
    );
}

pub fn seekOnEventPercentID(in_event_id: common.AkUniqueID, in_game_object: common.AkGameObjectID, in_percent: f32, optional_args: SeekOnEventOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SeekOnEvent_Percent_ID(
            in_event_id,
            in_game_object,
            in_percent,
            optional_args.seek_to_nearest_marker,
            optional_args.playing_id,
        ),
    );
}

pub fn seekOnEventPercentString(fallback_allocator: std.mem.Allocator, in_event_name: []const u8, in_game_object: common.AkGameObjectID, in_percent: f32, optional_args: SeekOnEventOptionalArgs) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_event_name = common.toCString(allocator, in_event_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_event_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SeekOnEvent_Percent_String(
            raw_event_name,
            in_game_object,
            in_percent,
            optional_args.seek_to_nearest_marker,
            optional_args.playing_id,
        ),
    );
}

pub fn cancelEventCallbackCookie(in_cookie: ?*anyopaque) void {
    c.WWISEC_AK_SoundEngine_CancelEventCallbackCookie(in_cookie);
}

pub fn cancelEventCallbackGameObject(in_game_object_id: common.AkGameObjectID) void {
    c.WWISEC_AK_SoundEngine_CancelEventCallbackGameObject(in_game_object_id);
}

pub fn cancelEventCallback(in_playing_id: common.AkPlayingID) void {
    c.WWISEC_AK_SoundEngine_CancelEventCallback(in_playing_id);
}

pub fn getSourcePlayPosition(in_playing_id: common.AkPlayingID, out_position: *common.AkTimeMs, extrapolate: bool) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetSourcePlayPosition(
            in_playing_id,
            out_position,
            extrapolate,
        ),
    );
}

pub fn getSourcePlayPositions(in_playing_id: common.AkPlayingID, out_positions: ?[*]AkSourcePosition, io_positions_count: *u32, in_extrapolate: bool) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetSourcePlayPositions(
            in_playing_id,
            @ptrCast([*c]c.WWISEC_AkSourcePosition, out_positions),
            io_positions_count,
            in_extrapolate,
        ),
    );
}

pub fn getSourceStreamBuffering(in_playing_id: common.AkPlayingID, out_buffering: *common.AkTimeMs, out_is_buffering: *bool) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetSourceStreamBuffering(
            in_playing_id,
            out_buffering,
            out_is_buffering,
        ),
    );
}

pub const StopAllOptionalArgs = struct {
    game_object_id: common.AkGameObjectID = common.AK_INVALID_GAME_OBJECT,
};

pub fn stopAll(optional_args: StopAllOptionalArgs) void {
    return c.WWISEC_AK_SoundEngine_StopAll(optional_args.game_object_id);
}

pub const StopPlayingIDOptionalArgs = struct {
    transition_duration: common.AkTimeMs = 0,
    fade_curve: common.AkCurveInterpolation = .linear,
};

pub fn stopPlayingID(in_playing_id: common.AkPlayingID, optional_args: StopPlayingIDOptionalArgs) void {
    return c.WWISEC_AK_SoundEngine_StopPlayingID(
        in_playing_id,
        optional_args.transition_duration,
        @enumToInt(optional_args.fade_curve),
    );
}

pub const ExecuteActionOnPlayingIDOptionalArgs = struct {
    transition_duration: common.AkTimeMs = 0,
    fade_curve: common.AkCurveInterpolation = .linear,
};

pub fn executeActionOnPlayingID(in_action_type: AkActionOnEventType, in_playing_id: common.AkPlayingID, optional_args: ExecuteActionOnPlayingIDOptionalArgs) void {
    c.WWISEC_AK_SoundEngine_ExecuteActionOnPlayingID(
        @enumToInt(in_action_type),
        in_playing_id,
        optional_args.transition_duration,
        @enumToInt(optional_args.fade_curve),
    );
}

pub fn setRandomSeed(in_seed: u32) void {
    c.WWISEC_AK_SoundEngine_SetRandomSeed(in_seed);
}

pub fn muteBackgroundMusic(in_mute: bool) void {
    c.WWISEC_AK_SoundEngine_MuteBackgroundMusic(in_mute);
}

pub fn getBackgroundMusicMute() bool {
    return c.WWISEC_AK_SoundEngine_GetBackgroundMusicMute();
}

pub fn sendPluginCustomGameData(
    in_bus_id: common.AkUniqueID,
    in_bus_object_id: common.AkUniqueID,
    in_type: common.AkPluginType,
    in_company_id: u32,
    in_plugin_id: u32,
    in_data: ?*anyopaque,
    in_size_in_bytes: u32,
) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SendPluginCustomGameData(
            in_bus_id,
            in_bus_object_id,
            @enumToInt(in_type),
            in_company_id,
            in_plugin_id,
            in_data,
            in_size_in_bytes,
        ),
    );
}

pub fn registerGameObj(in_game_object_id: common.AkGameObjectID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RegisterGameObj(in_game_object_id),
    );
}

pub fn registerGameObjWithName(fallback_allocator: std.mem.Allocator, in_game_object_id: common.AkGameObjectID, in_name: []const u8) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_name = common.toCString(allocator, in_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RegisterGameObjWithName(in_game_object_id, raw_name),
    );
}

pub fn unregisterGameObj(in_game_object_id: common.AkGameObjectID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnregisterGameObj(in_game_object_id),
    );
}

pub fn unregisterAllGameObj() common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnregisterAllGameObj(),
    );
}

pub const SetPositionOptionalArgs = struct {
    flags: common.AkSetPositionFlags = common.AkSetPositionFlags.Default,
};

pub fn setPosition(in_game_object_id: common.AkGameObjectID, in_position: common.AkSoundPosition, optional_args: SetPositionOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetPosition(
            in_game_object_id,
            @ptrCast(?*const c.WWISEC_AkSoundPosition, &in_position),
            optional_args.flags.toC(),
        ),
    );
}

pub const SetMultiplePositionOptionalArgs = struct {
    multi_position_type: MultiPositionType = .multi_directions,
    flags: common.AkSetPositionFlags = common.AkSetPositionFlags.Default,
};

pub fn setMultiplePositionsSoundPosition(in_game_object: common.AkGameObjectID, positions: []const common.AkSoundPosition, optional_args: SetMultiplePositionOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetMultiplePositions_SoundPosition(
            in_game_object,
            @ptrCast([*]const c.WWISEC_AkSoundPosition, positions),
            @truncate(u16, positions.len),
            @enumToInt(optional_args.multi_position_type),
            optional_args.flags.toC(),
        ),
    );
}

pub fn setMultiplePositionChannelEmitter(in_game_object: common.AkGameObjectID, positions: []const common.AkChannelEmitter, optional_args: SetMultiplePositionOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetMultiplePositions_ChannelEmitter(
            in_game_object,
            @ptrCast([*]const c.WWISEC_AkChannelEmitter, positions),
            @truncate(u16, positions.len),
            @enumToInt(optional_args.multi_position_type),
            optional_args.flags.toC(),
        ),
    );
}

pub fn setScalingFactor(in_game_object_id: common.AkGameObjectID, in_attenuation_scaling_factor: f32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetScalingFactor(in_game_object_id, in_attenuation_scaling_factor),
    );
}

pub fn setDistanceProbe(in_listener_game_object_id: common.AkGameObjectID, in_distance_probe_game_object_id: common.AkGameObjectID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetDistanceProbe(in_listener_game_object_id, in_distance_probe_game_object_id),
    );
}

pub fn clearBanks() common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_ClearBanks(),
    );
}

pub fn setBankLoadIOSettings(in_throughput: f32, in_priority: common.AkPriority) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetBankLoadIOSettings(in_throughput, in_priority),
    );
}

pub const LoadBankOptionalArgs = struct {
    bank_type: common.AkBankType = .user,
};

pub fn loadBankString(fallback_allocator: std.mem.Allocator, in_bank_name: []const u8, optional_args: LoadBankOptionalArgs) common.WwiseError!common.AkBankID {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_bank_name = common.toCString(allocator, in_bank_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_bank_name);

    var out_bank_id: common.AkBankID = common.AK_INVALID_BANK_ID;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_LoadBank_String(raw_bank_name, &out_bank_id, @enumToInt(optional_args.bank_type)),
    );

    return out_bank_id;
}

pub fn loadBankID(in_bank_id: common.AkBankID, optional_args: LoadBankOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_LoadBank_ID(in_bank_id, @enumToInt(optional_args.bank_type)),
    );
}

pub fn loadBankMemoryView(in_memory_bank: ?*const anyopaque, in_memory_bank_size: u32) common.WwiseError!common.AkBankID {
    var out_bank_id: common.AkBankID = common.AK_INVALID_BANK_ID;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_LoadBankMemoryView(in_memory_bank, in_memory_bank_size, &out_bank_id),
    );

    return out_bank_id;
}

pub fn loadBankMemoryViewOutBankType(in_memory_bank: ?*const anyopaque, in_memory_bank_size: u32, out_bank_id: *common.AkBankID, out_bank_type: *common.AkBankType) common.WwiseError!void {
    var raw_bank_type: u32 = 0;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_LoadBankMemoryView_OutBankType(in_memory_bank, in_memory_bank_size, out_bank_id, &raw_bank_type),
    );

    out_bank_type.* = @intToEnum(common.AkBankType, raw_bank_type);
}

pub fn loadBankMemoryCopy(in_memory_bank: ?*const anyopaque, in_memory_bank_size: u32) common.WwiseError!common.AkBankID {
    var out_bank_id: common.AkBankID = common.AK_INVALID_BANK_ID;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_LoadBankMemoryCopy(in_memory_bank, in_memory_bank_size, &out_bank_id),
    );

    return out_bank_id;
}

pub fn loadBankMemoryCopyOutBankType(in_memory_bank: ?*anyopaque, in_memory_bank_size: u32, out_bank_id: *common.AkBankID, out_bank_type: *common.AkBankType) common.WwiseError!void {
    var raw_bank_type: u32 = 0;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_LoadBankMemoryCopy_OutBankType(in_memory_bank, in_memory_bank_size, out_bank_id, &raw_bank_type),
    );

    out_bank_type.* = @intToEnum(common.AkBankType, raw_bank_type);
}

pub fn decodeBank(in_memory_bank: ?*const anyopaque, in_memory_bank_size: u32, in_pool_for_decoded_bank: common.AkMemPoolId, out_decoded_bank_ptr: *?*anyopaque, out_decoded_bank_size: u32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_DecodeBank(
            in_memory_bank,
            in_memory_bank_size,
            in_pool_for_decoded_bank,
            out_decoded_bank_ptr,
            out_decoded_bank_size,
        ),
    );
}

pub fn loadBankAsyncString(fallback_allocator: std.mem.Allocator, in_bank_name: []const u8, in_bank_callback: callback.AkBankCallbackFunc, in_cookie: ?*anyopaque, optional_args: LoadBankOptionalArgs) common.WwiseError!common.AkBankID {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_bank_name = common.toCString(allocator, in_bank_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_bank_name);

    var out_bank_id: common.AkBankID = common.AK_INVALID_BANK_ID;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_LoadBank_Async_String(
            raw_bank_name,
            @ptrCast(c.WWISEC_AkBankCallbackFunc, in_bank_callback),
            in_cookie,
            &out_bank_id,
            @enumToInt(optional_args.bank_type),
        ),
    );
    return out_bank_id;
}

pub fn loadBankAsyncID(in_bank_id: common.AkBankID, in_bank_callback: callback.AkBankCallbackFunc, in_cookie: ?*anyopaque, optional_args: LoadBankOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_LoadBank_Async_ID(
            in_bank_id,
            @ptrCast(c.WWISEC_AkBankCallbackFunc, in_bank_callback),
            in_cookie,
            @enumToInt(optional_args.bank_type),
        ),
    );
}

pub fn loadBankMemoryViewAsync(in_memory_bank: ?*const anyopaque, in_memory_bank_size: u32, in_bank_callback: callback.AkBankCallbackFunc, in_cookie: ?*anyopaque) common.WwiseError!common.AkBankID {
    var out_bank_id: common.AkBankID = common.AK_INVALID_BANK_ID;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_LoadBankMemoryView_Async(
            in_memory_bank,
            in_memory_bank_size,
            @ptrCast(c.WWISEC_AkBankCallbackFunc, in_bank_callback),
            in_cookie,
            &out_bank_id,
        ),
    );

    return out_bank_id;
}

pub fn loadBankMemoryViewAsyncOutBankType(in_memory_bank: ?*const anyopaque, in_memory_bank_size: u32, in_bank_callback: callback.AkBankCallbackFunc, in_cookie: ?*anyopaque, out_bank_id: *common.AkBankID, out_bank_type: *common.AkBankType) common.WwiseError!void {
    var raw_bank_type: u32 = 0;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_LoadBankMemoryView_Async_OutBankType(
            in_memory_bank,
            in_memory_bank_size,
            @ptrCast(c.WWISEC_AkBankCallbackFunc, in_bank_callback),
            in_cookie,
            out_bank_id,
            &raw_bank_type,
        ),
    );
    out_bank_type.* = @intToEnum(common.AkBankType, raw_bank_type);
}

pub fn loadBankMemoryCopyAsync(in_memory_bank: ?*const anyopaque, in_memory_bank_size: u32, in_bank_callback: callback.AkBankCallbackFunc, in_cookie: ?*anyopaque, out_bank_id: *common.AkBankID, out_bank_type: *common.AkBankType) common.WwiseError!void {
    var raw_bank_type: u32 = 0;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_LoadBankMemoryCopy_Async(
            in_memory_bank,
            in_memory_bank_size,
            @ptrCast(c.WWISEC_AkBankCallbackFunc, in_bank_callback),
            in_cookie,
            out_bank_id,
            &raw_bank_type,
        ),
    );
    out_bank_type.* = @intToEnum(common.AkBankType, raw_bank_type);
}

pub const UnloadBankOptionalArgs = struct {
    bank_type: common.AkBankType = .user,
};

pub fn unloadBankString(fallback_allocator: std.mem.Allocator, in_bank_name: []const u8, in_memory_bank: ?*const anyopaque, optional_args: UnloadBankOptionalArgs) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_bank_name = common.toCString(allocator, in_bank_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_bank_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnloadBank_String(raw_bank_name, in_memory_bank, @enumToInt(optional_args.bank_type)),
    );
}

pub fn unloadBankID(in_bank_id: common.AkBankID, in_memory_bank: ?*const anyopaque, optional_args: UnloadBankOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnloadBank_ID(in_bank_id, in_memory_bank, @enumToInt(optional_args.bank_type)),
    );
}

pub fn unloadBankAsyncString(fallback_allocator: std.mem.Allocator, in_bank_name: []const u8, in_memory_bank: ?*const anyopaque, in_bank_callback: callback.AkBankCallbackFunc, in_cookie: ?*anyopaque, optional_args: UnloadBankOptionalArgs) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_bank_name = common.toCString(allocator, in_bank_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_bank_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnloadBank_Async_String(
            raw_bank_name,
            in_memory_bank,
            @ptrCast(c.WWISEC_AkBankCallbackFunc, in_bank_callback),
            in_cookie,
            @enumToInt(optional_args.bank_type),
        ),
    );
}

pub fn unloadBankAsyncID(in_bank_id: common.AkBankID, in_memory_bank: ?*const anyopaque, in_bank_callback: callback.AkBankCallbackFunc, in_cookie: ?*anyopaque, optional_args: UnloadBankOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnloadBank_Async_ID(
            in_bank_id,
            in_memory_bank,
            @ptrCast(c.WWISEC_AkBankCallbackFunc, in_bank_callback),
            in_cookie,
            @enumToInt(optional_args.bank_type),
        ),
    );
}

pub fn cancelBankCallbackCookie(in_cookie: ?*anyopaque) void {
    c.WWISEC_AK_SoundEngine_CancelBankCallbackCookie(in_cookie);
}

pub const PrepareBankOptionalArgs = struct {
    flags: AkBankContent = .all,
    bank_type: common.AkBankType = .user,
};

pub fn prepareBankString(
    fallback_allocator: std.mem.Allocator,
    in_preparation_type: PreparationType,
    in_bank_name: []const u8,
    optional_args: PrepareBankOptionalArgs,
) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_bank_name = common.toCString(allocator, in_bank_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_bank_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareBank_String(
            @enumToInt(in_preparation_type),
            raw_bank_name,
            @enumToInt(optional_args.flags),
            @enumToInt(optional_args.bank_type),
        ),
    );
}

pub fn prepareBankID(
    in_preparation_type: PreparationType,
    in_bank_id: common.AkBankID,
    optional_args: PrepareBankOptionalArgs,
) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareBank_ID(
            @enumToInt(in_preparation_type),
            in_bank_id,
            @enumToInt(optional_args.flags),
            @enumToInt(optional_args.bank_type),
        ),
    );
}

pub fn prepareBankAsyncString(
    fallback_allocator: std.mem.Allocator,
    in_preparation_type: PreparationType,
    in_bank_name: []const u8,
    in_bank_callback: callback.AkBankCallbackFunc,
    in_cookie: ?*anyopaque,
    optional_args: PrepareBankOptionalArgs,
) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_bank_name = common.toCString(allocator, in_bank_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_bank_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareBank_Async_String(
            @enumToInt(in_preparation_type),
            raw_bank_name,
            @ptrCast(c.WWISEC_AkBankCallbackFunc, in_bank_callback),
            in_cookie,
            @enumToInt(optional_args.flags),
            @enumToInt(optional_args.bank_type),
        ),
    );
}

pub fn prepareBankAsyncID(
    in_preparation_type: PreparationType,
    in_bank_id: common.AkBankID,
    in_bank_callback: callback.AkBankCallbackFunc,
    in_cookie: ?*anyopaque,
    optional_args: PrepareBankOptionalArgs,
) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareBank_Async_ID(
            @enumToInt(in_preparation_type),
            in_bank_id,
            @ptrCast(c.WWISEC_AkBankCallbackFunc, in_bank_callback),
            in_cookie,
            @enumToInt(optional_args.flags),
            @enumToInt(optional_args.bank_type),
        ),
    );
}

pub fn clearPreparedEvents() common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_ClearPreparedEvents(),
    );
}

pub fn prepareEventString(fallback_allocator: std.mem.Allocator, in_preparation_type: PreparationType, in_event_names: [][]const u8) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var char_allocator = stack_char_allocator.get();

    var area_allocator = std.heap.ArenaAllocator.init(char_allocator);
    defer area_allocator.deinit();

    var allocator = area_allocator.allocator();

    var raw_event_names_list = std.ArrayList([*:0]const u8).init(allocator);
    defer raw_event_names_list.deinit();

    for (in_event_names) |event_name| {
        var raw_event_name = common.toCString(allocator, event_name) catch return common.WwiseError.Fail;
        raw_event_names_list.append(raw_event_name) catch return common.WwiseError.Fail;
    }

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareEvent_String(
            @enumToInt(in_preparation_type),
            @ptrCast([*c][*c]const u8, raw_event_names_list.items),
            @truncate(u32, raw_event_names_list.items.len),
        ),
    );
}

pub fn prepareEventID(in_preparation_type: PreparationType, in_event_ids: []const common.AkUniqueID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareEvent_ID(
            @enumToInt(in_preparation_type),
            @ptrCast([*]c.WWISEC_AkUniqueID, @constCast(in_event_ids)),
            @truncate(u32, in_event_ids.len),
        ),
    );
}

pub fn prepareEventAsyncString(
    fallback_allocator: std.mem.Allocator,
    in_preparation_type: PreparationType,
    in_event_names: [][]const u8,
    in_bank_callback: callback.AkBankCallbackFunc,
    in_cookie: ?*anyopaque,
) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var char_allocator = stack_char_allocator.get();

    var area_allocator = std.heap.ArenaAllocator.init(char_allocator);
    defer area_allocator.deinit();

    var allocator = area_allocator.allocator();

    var raw_event_names_list = std.ArrayList([*:0]const u8).init(allocator);
    defer raw_event_names_list.deinit();

    for (in_event_names) |event_name| {
        var raw_event_name = common.toCString(allocator, event_name) catch return common.WwiseError.Fail;
        raw_event_names_list.append(raw_event_name) catch return common.WwiseError.Fail;
    }

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareEvent_Async_String(
            @enumToInt(in_preparation_type),
            @ptrCast([*c][*c]const u8, raw_event_names_list.items),
            @truncate(u32, raw_event_names_list.items.len),
            @ptrCast(c.WWISEC_AkBankCallbackFunc, in_bank_callback),
            in_cookie,
        ),
    );
}

pub fn prepareEventAsyncID(
    in_preparation_type: PreparationType,
    in_event_ids: []const common.AkUniqueID,
    in_bank_callback: callback.AkBankCallbackFunc,
    in_cookie: ?*anyopaque,
) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareEvent_Async_ID(
            @enumToInt(in_preparation_type),
            @ptrCast([*]c.WWISEC_AkUniqueID, @constCast(in_event_ids)),
            @truncate(u32, in_event_ids.len),
            @ptrCast(c.WWISEC_AkBankCallbackFunc, in_bank_callback),
            in_cookie,
        ),
    );
}

pub fn addOutput(output_settings: *const settings.AkOutputSettings, out_device_id: *?common.AkOutputDeviceID, listeners: []common.AkGameObjectID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_AddOutput(@ptrCast(*const c.WWISEC_AkOutputSettings, output_settings), @ptrCast([*]c.WWISEC_AkOutputDeviceID, out_device_id), listeners.ptr, @truncate(u32, listeners.len)),
    );
}

pub fn removeOutput(id_output: common.AkOutputDeviceID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RemoveOutput(id_output),
    );
}

pub fn replaceOutput(output_settings: *const settings.AkOutputSettings, in_device_id: common.AkOutputDeviceID, out_device_id: *?common.AkOutputDeviceID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_ReplaceOutput(@ptrCast(*const c.WWISEC_AkOutputSettings, output_settings), in_device_id, @ptrCast([*]c.WWISEC_AkOutputDeviceID, out_device_id)),
    );
}
