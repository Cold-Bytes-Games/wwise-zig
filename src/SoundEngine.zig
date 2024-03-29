const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const callbacks = @import("callbacks.zig");
const common_defs = @import("common_defs.zig");
const IAkPlugin = @import("IAkPlugin.zig");
const IBytes = @import("IBytes.zig");
const midi_types = @import("midi_types.zig");
const settings = @import("settings.zig");
const speaker_config = @import("speaker_config.zig");
const SpeakerVolumes = @import("SpeakerVolumes.zig");
const wwise_options = @import("wwise_options");

pub const DynamicDialogue = @import("DynamicDialogue.zig");
pub const DynamicSequence = @import("DynamicSequence.zig");
pub const Query = @import("Query.zig");

pub usingnamespace if (wwise_options.platform == .android) @import("android_sound_engine.zig") else struct {};
pub const iOS = if (wwise_options.platform == .ios) @import("ios_sound_engine.zig") else struct {};

pub const AkSourceSettings = extern struct {
    source_id: common.AkUniqueID = 0,
    media_memory: ?*anyopaque = null,
    media_size: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_AkSourceSettings) AkSourceSettings {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkSourceSettings) c.WWISEC_AkSourceSettings {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkSourceSettings) == @sizeOf(c.WWISEC_AkSourceSettings));
    }
};

pub const AkSourcePosition = extern struct {
    audio_node_id: common.AkUniqueID = 0,
    media_id: common.AkUniqueID = 0,
    ms_time: common.AkTimeMs = 0,
    sample_position: u32 = 0,
    update_buffer_tick: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_AkSourcePosition) AkSourcePosition {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkSourcePosition) c.WWISEC_AkSourcePosition {
        return @bitCast(self);
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

    const native_init_settings_ptr = blk: {
        if (init_settings_opt) |init_settings| {
            var native_init_settings = init_settings.toC(allocator) catch return common.WwiseError.Fail;
            break :blk &native_init_settings;
        }

        break :blk @as(?*c.WWISEC_AkInitSettings, null);
    };

    defer {
        if (native_init_settings_ptr) |native_init_settings| {
            if (native_init_settings.szPluginDLLPath != null) {
                allocator.free(native_init_settings.szPluginDLLPath[0..std.mem.len(native_init_settings.szPluginDLLPath)]);
            }
        }
    }

    const native_platform_init_settings_ptr = blk: {
        if (platform_init_settings_opt) |platform_init_settings| {
            break :blk @as(?*c.WWISEC_AkPlatformInitSettings, @ptrCast(platform_init_settings));
        }
        break :blk @as(?*c.WWISEC_AkPlatformInitSettings, null);
    };

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Init(native_init_settings_ptr, native_platform_init_settings_ptr),
    );
}

// We are passing an allocator here, but it is not used in reality
// because the plugin path returned by AK::SoundEngine::GetDefaultInitSettings is always null
// You don't need to call deinit() on AkInitSettings here.
pub fn getDefaultInitSettings(allocator: std.mem.Allocator, init_settings: *settings.AkInitSettings) !void {
    var native_settings: c.WWISEC_AkInitSettings = undefined;
    c.WWISEC_AK_SoundEngine_GetDefaultInitSettings(&native_settings);

    init_settings.* = try settings.AkInitSettings.fromC(allocator, native_settings);
}

pub fn getDefaultPlatformInitSettings(platform_init_settings: *settings.AkPlatformInitSettings) void {
    c.WWISEC_AK_SoundEngine_GetDefaultPlatformInitSettings(@ptrCast(platform_init_settings));
}

pub fn term() void {
    c.WWISEC_AK_SoundEngine_Term();
}

pub fn getAudioSettings(out_settings: *common.AkAudioSettings) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetAudioSettings(@ptrCast(out_settings)),
    );
}

pub fn getSpeakerConfiguration(in_id_output: common.AkOutputDeviceID) speaker_config.AkChannelConfig {
    return speaker_config.AkChannelConfig.fromC(
        c.WWISEC_AK_SoundEngine_GetSpeakerConfiguration(in_id_output),
    );
}

pub fn getOutputDeviceConfiguration(in_id_output: common.AkOutputDeviceID, io_channel_config: *speaker_config.AkChannelConfig, io_capabilities: *common_defs.Ak3DAudioSinkCapabilities) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetOutputDeviceConfiguration(in_id_output, @ptrCast(io_channel_config), @ptrCast(io_capabilities)),
    );
}

pub fn getPanningRule(in_id_output: common.AkOutputDeviceID) common.WwiseError!common.AkPanningRule {
    var raw_panning_rule: c.WWISEC_AkPanningRule = undefined;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetPanningRule(&raw_panning_rule, in_id_output),
    );

    return @enumFromInt(raw_panning_rule);
}

pub fn setPanningRule(in_panning_rule: common.AkPanningRule, in_id_output: common.AkOutputDeviceID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetPanningRule(@intFromEnum(in_panning_rule), in_id_output),
    );
}

pub fn getSpeakerAngles(io_speaker_angles: ?*[]f32, io_num_angles: *u32, out_height_angle: *f32, in_id_output: common.AkOutputDeviceID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetSpeakerAngles(@ptrCast(io_speaker_angles), io_num_angles, out_height_angle, in_id_output),
    );
}

pub fn setSpeakerAngles(in_speaker_angles: []const f32, in_height_angle: f32, in_id_output: common.AkOutputDeviceID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetSpeakerAngles(@ptrCast(in_speaker_angles), @truncate(in_speaker_angles.len), in_height_angle, in_id_output),
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
    return @ptrCast(c.WWISEC_AK_SoundEngine_GetGlobalPluginContext());
}

pub fn registerPlugin(in_type: common.AkPluginType, in_company_id: u32, in_plugin_id: u32, in_create_func: IAkPlugin.AkCreatePluginCallback, in_create_param_func: IAkPlugin.AkCreateParamCallback) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RegisterPlugin(
            @intFromEnum(in_type),
            in_company_id,
            in_plugin_id,
            @ptrCast(in_create_func),
            @ptrCast(in_create_param_func),
        ),
    );
}

pub fn registerPluginDLL(fallback_allocator: std.mem.Allocator, in_dll_name: []const u8, in_dll_path_opt: ?[]const u8) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    const allocator = stack_char_allocator.get();

    var area_allocator = std.heap.ArenaAllocator.init(allocator);
    defer area_allocator.deinit();

    const raw_in_dll_name = common.toOSChar(area_allocator.allocator(), in_dll_name) catch return common.WwiseError.Fail;

    const raw_in_dll_path = blk: {
        if (in_dll_path_opt) |in_dll_path| {
            break :blk @as([*c]const common.AkOSChar, common.toOSChar(area_allocator.allocator(), in_dll_path) catch return common.WwiseError.Fail);
        }

        break :blk @as([*c]const common.AkOSChar, null);
    };

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RegisterPluginDLL(raw_in_dll_name, raw_in_dll_path),
    );
}

pub const RegisterGlobalCallbackOptionalArgs = struct {
    location: callbacks.AkGlobalCallbackLocation = .{ .begin_render = true },
    cookie: ?*anyopaque = null,
    plugin_type: common.AkPluginType = .none,
    company_id: u32 = 0,
    plugin_id: u32 = 0,
};

pub fn registerGlobalCallback(in_callback: callbacks.AkGlobalCallbackFunc, optional_args: RegisterGlobalCallbackOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RegisterGlobalCallback(
            @ptrCast(in_callback),
            @intCast(optional_args.location.toC()),
            optional_args.cookie,
            @intFromEnum(optional_args.plugin_type),
            optional_args.company_id,
            optional_args.plugin_id,
        ),
    );
}

pub const UnregisterGlobalCallbackOptionalArgs = struct {
    location: callbacks.AkGlobalCallbackLocation = .{ .begin_render = true },
};

pub fn unregisterGlobalCallback(in_callback: callbacks.AkGlobalCallbackFunc, optional_args: UnregisterGlobalCallbackOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnregisterGlobalCallback(
            @ptrCast(in_callback),
            @intCast(optional_args.location.toC()),
        ),
    );
}

pub fn registerResourceMonitorCallback(in_callback: callbacks.AkResourceMonitorCallbackFunc) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RegisterResourceMonitorCallback(@ptrCast(in_callback)),
    );
}

pub fn unregisterResourceMonitorCallback(in_callback: callbacks.AkResourceMonitorCallbackFunc) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnregisterResourceMonitorCallback(@ptrCast(in_callback)),
    );
}

pub fn registerAudioDeviceStatusCallback(in_callback: callbacks.AkDeviceStatusCallbackFunc) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RegisterAudioDeviceStatusCallback(@ptrCast(in_callback)),
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

    const raw_string = try common.toCString(allocator, string);
    defer allocator.free(raw_string);

    return c.WWISEC_AK_SoundEngine_GetIDFromString(raw_string);
}

pub const PostEventOptionalArgs = struct {
    flags: callbacks.AkCallbackType = .{},
    callback: callbacks.AkCallbackFunc = null,
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
        if (optional_args.external_sources != null) {
            std.debug.assert(optional_args.allocator != null);
        }

        if (optional_args.allocator) |allocator| {
            area_allocator_opt = std.heap.ArenaAllocator.init(allocator);
            if (optional_args.external_sources) |external_sources| {
                num_external_sources = @truncate(external_sources.len);

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
            break :blk @as(?[*]c.WWISEC_AkExternalSourceInfo, @ptrCast(@constCast(external_sources)));
        }

        break :blk @as(?[*]c.WWISEC_AkExternalSourceInfo, null);
    };

    return c.WWISEC_AK_SoundEngine_PostEvent_ID(
        in_eventID,
        game_object_id,
        @intCast(optional_args.flags.toC()),
        @ptrCast(optional_args.callback),
        optional_args.cookie,
        num_external_sources,
        external_sources_ptr,
        optional_args.playing_id,
    );
}

pub fn postEventString(fallback_allocator: std.mem.Allocator, in_event_name: []const u8, game_object_id: common.AkGameObjectID, optional_args: PostEventOptionalArgs) !common.AkPlayingID {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var char_allocator = stack_char_allocator.get();

    const raw_event_name = try common.toCString(char_allocator, in_event_name);
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
                num_external_sources = @truncate(external_sources.len);

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
            break :blk @as(?[*]c.WWISEC_AkExternalSourceInfo, @ptrCast(@constCast(external_sources)));
        }

        break :blk @as(?[*]c.WWISEC_AkExternalSourceInfo, null);
    };

    return c.WWISEC_AK_SoundEngine_PostEvent_String(
        raw_event_name,
        game_object_id,
        @intCast(optional_args.flags.toC()),
        @ptrCast(optional_args.callback),
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
            @intFromEnum(in_action_type),
            optional_args.game_object_id,
            optional_args.transition_duration,
            @intFromEnum(optional_args.fade_curve),
            optional_args.playing_id,
        ),
    );
}

pub fn executeActionOnEventString(fallback_allocator: std.mem.Allocator, in_event_name: []const u8, in_action_type: AkActionOnEventType, optional_args: ExecuteActionOnEventOptionalArgs) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_event_name = common.toCString(allocator, in_event_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_event_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_ExecuteActionOnEvent_String(
            raw_event_name,
            @intFromEnum(in_action_type),
            optional_args.game_object_id,
            optional_args.transition_duration,
            @intFromEnum(optional_args.fade_curve),
            optional_args.playing_id,
        ),
    );
}

pub const PostMIDIOnEventOptionalArgs = struct {
    absolute_offsets: bool = false,
    flags: callbacks.AkCallbackType = .{},
    callback: callbacks.AkCallbackFunc = null,
    cookie: ?*anyopaque = null,
    playing_id: common.AkPlayingID = common.AK_INVALID_PLAYING_ID,
};

// NOTE: mlarouche: Workaround for translate-c that does not put the proper alignment on AkMIDIPost
extern fn WWISEC_AK_SoundEngine_PostMIDIOnEvent(in_eventID: c.WWISEC_AkUniqueID, in_gameObjectID: c.WWISEC_AkGameObjectID, in_pPosts: [*]midi_types.AkMIDIPost, in_uNumPosts: u16, in_bAbsoluteOffsets: bool, in_uFlags: u32, in_pfnCallback: c.WWISEC_AkCallbackFunc, in_pCookie: ?*anyopaque, in_playingID: c.WWISEC_AkPlayingID) c.WWISEC_AkPlayingID;

pub fn postMIDIOnEvent(
    in_event_id: common.AkUniqueID,
    in_game_object_id: common.AkGameObjectID,
    in_midi_posts: []const midi_types.AkMIDIPost,
    optional_args: PostMIDIOnEventOptionalArgs,
) common.AkPlayingID {
    return WWISEC_AK_SoundEngine_PostMIDIOnEvent(
        in_event_id,
        in_game_object_id,
        @ptrCast(@constCast(in_midi_posts)),
        @truncate(in_midi_posts.len),
        optional_args.absolute_offsets,
        @intCast(optional_args.flags.toC()),
        @ptrCast(optional_args.callback),
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

    const raw_event_name = common.toCString(allocator, in_event_name) catch return common.WwiseError.Fail;
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

    const raw_event_name = common.toCString(allocator, in_event_name) catch return common.WwiseError.Fail;
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

    const raw_event_name = common.toCString(allocator, in_event_name) catch return common.WwiseError.Fail;
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

    const raw_event_name = common.toCString(allocator, in_event_name) catch return common.WwiseError.Fail;
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

    const raw_event_name = common.toCString(allocator, in_event_name) catch return common.WwiseError.Fail;
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

pub fn getSourcePlayPosition(in_playing_id: common.AkPlayingID, extrapolate: bool) common.WwiseError!common.AkTimeMs {
    var out_position: common.AkTimeMs = undefined;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetSourcePlayPosition(
            in_playing_id,
            &out_position,
            extrapolate,
        ),
    );

    return out_position;
}

pub fn getSourcePlayPositions(in_playing_id: common.AkPlayingID, out_positions: ?[*]AkSourcePosition, io_positions_count: *u32, in_extrapolate: bool) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetSourcePlayPositions(
            in_playing_id,
            @ptrCast(out_positions),
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
    c.WWISEC_AK_SoundEngine_StopAll(optional_args.game_object_id);
}

pub const StopPlayingIDOptionalArgs = struct {
    transition_duration: common.AkTimeMs = 0,
    fade_curve: common.AkCurveInterpolation = .linear,
};

pub fn stopPlayingID(in_playing_id: common.AkPlayingID, optional_args: StopPlayingIDOptionalArgs) void {
    return c.WWISEC_AK_SoundEngine_StopPlayingID(
        in_playing_id,
        optional_args.transition_duration,
        @intFromEnum(optional_args.fade_curve),
    );
}

pub const ExecuteActionOnPlayingIDOptionalArgs = struct {
    transition_duration: common.AkTimeMs = 0,
    fade_curve: common.AkCurveInterpolation = .linear,
};

pub fn executeActionOnPlayingID(in_action_type: AkActionOnEventType, in_playing_id: common.AkPlayingID, optional_args: ExecuteActionOnPlayingIDOptionalArgs) void {
    c.WWISEC_AK_SoundEngine_ExecuteActionOnPlayingID(
        @intFromEnum(in_action_type),
        in_playing_id,
        optional_args.transition_duration,
        @intFromEnum(optional_args.fade_curve),
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
            @intFromEnum(in_type),
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

    const raw_name = common.toCString(allocator, in_name) catch return common.WwiseError.Fail;
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
            @ptrCast(&in_position),
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
            @ptrCast(positions),
            @truncate(positions.len),
            @intFromEnum(optional_args.multi_position_type),
            optional_args.flags.toC(),
        ),
    );
}

pub fn setMultiplePositionChannelEmitter(in_game_object: common.AkGameObjectID, positions: []const common.AkChannelEmitter, optional_args: SetMultiplePositionOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetMultiplePositions_ChannelEmitter(
            in_game_object,
            @ptrCast(positions),
            @truncate(positions.len),
            @intFromEnum(optional_args.multi_position_type),
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

    const raw_bank_name = common.toCString(allocator, in_bank_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_bank_name);

    var out_bank_id: common.AkBankID = common.AK_INVALID_BANK_ID;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_LoadBank_String(raw_bank_name, &out_bank_id, @intFromEnum(optional_args.bank_type)),
    );

    return out_bank_id;
}

pub fn loadBankID(in_bank_id: common.AkBankID, optional_args: LoadBankOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_LoadBank_ID(in_bank_id, @intFromEnum(optional_args.bank_type)),
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

    out_bank_type.* = @enumFromInt(raw_bank_type);
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

    out_bank_type.* = @enumFromInt(raw_bank_type);
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

pub fn loadBankAsyncString(fallback_allocator: std.mem.Allocator, in_bank_name: []const u8, in_bank_callback: callbacks.AkBankCallbackFunc, in_cookie: ?*anyopaque, optional_args: LoadBankOptionalArgs) common.WwiseError!common.AkBankID {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_bank_name = common.toCString(allocator, in_bank_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_bank_name);

    var out_bank_id: common.AkBankID = common.AK_INVALID_BANK_ID;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_LoadBank_Async_String(
            raw_bank_name,
            @ptrCast(in_bank_callback),
            in_cookie,
            &out_bank_id,
            @intFromEnum(optional_args.bank_type),
        ),
    );
    return out_bank_id;
}

pub fn loadBankAsyncID(in_bank_id: common.AkBankID, in_bank_callback: callbacks.AkBankCallbackFunc, in_cookie: ?*anyopaque, optional_args: LoadBankOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_LoadBank_Async_ID(
            in_bank_id,
            @ptrCast(in_bank_callback),
            in_cookie,
            @intFromEnum(optional_args.bank_type),
        ),
    );
}

pub fn loadBankMemoryViewAsync(in_memory_bank: ?*const anyopaque, in_memory_bank_size: u32, in_bank_callback: callbacks.AkBankCallbackFunc, in_cookie: ?*anyopaque) common.WwiseError!common.AkBankID {
    var out_bank_id: common.AkBankID = common.AK_INVALID_BANK_ID;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_LoadBankMemoryView_Async(
            in_memory_bank,
            in_memory_bank_size,
            @ptrCast(in_bank_callback),
            in_cookie,
            &out_bank_id,
        ),
    );

    return out_bank_id;
}

pub fn loadBankMemoryViewAsyncOutBankType(in_memory_bank: ?*const anyopaque, in_memory_bank_size: u32, in_bank_callback: callbacks.AkBankCallbackFunc, in_cookie: ?*anyopaque, out_bank_id: *common.AkBankID, out_bank_type: *common.AkBankType) common.WwiseError!void {
    var raw_bank_type: u32 = 0;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_LoadBankMemoryView_Async_OutBankType(
            in_memory_bank,
            in_memory_bank_size,
            @ptrCast(in_bank_callback),
            in_cookie,
            out_bank_id,
            &raw_bank_type,
        ),
    );
    out_bank_type.* = @enumFromInt(raw_bank_type);
}

pub fn loadBankMemoryCopyAsync(in_memory_bank: ?*const anyopaque, in_memory_bank_size: u32, in_bank_callback: callbacks.AkBankCallbackFunc, in_cookie: ?*anyopaque, out_bank_id: *common.AkBankID, out_bank_type: *common.AkBankType) common.WwiseError!void {
    var raw_bank_type: u32 = 0;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_LoadBankMemoryCopy_Async(
            in_memory_bank,
            in_memory_bank_size,
            @ptrCast(in_bank_callback),
            in_cookie,
            out_bank_id,
            &raw_bank_type,
        ),
    );
    out_bank_type.* = @enumFromInt(raw_bank_type);
}

pub const UnloadBankOptionalArgs = struct {
    bank_type: common.AkBankType = .user,
};

pub fn unloadBankString(fallback_allocator: std.mem.Allocator, in_bank_name: []const u8, in_memory_bank: ?*const anyopaque, optional_args: UnloadBankOptionalArgs) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_bank_name = common.toCString(allocator, in_bank_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_bank_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnloadBank_String(raw_bank_name, in_memory_bank, @intFromEnum(optional_args.bank_type)),
    );
}

pub fn unloadBankID(in_bank_id: common.AkBankID, in_memory_bank: ?*const anyopaque, optional_args: UnloadBankOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnloadBank_ID(in_bank_id, in_memory_bank, @intFromEnum(optional_args.bank_type)),
    );
}

pub fn unloadBankAsyncString(fallback_allocator: std.mem.Allocator, in_bank_name: []const u8, in_memory_bank: ?*const anyopaque, in_bank_callback: callbacks.AkBankCallbackFunc, in_cookie: ?*anyopaque, optional_args: UnloadBankOptionalArgs) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_bank_name = common.toCString(allocator, in_bank_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_bank_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnloadBank_Async_String(
            raw_bank_name,
            in_memory_bank,
            @ptrCast(in_bank_callback),
            in_cookie,
            @intFromEnum(optional_args.bank_type),
        ),
    );
}

pub fn unloadBankAsyncID(in_bank_id: common.AkBankID, in_memory_bank: ?*const anyopaque, in_bank_callback: callbacks.AkBankCallbackFunc, in_cookie: ?*anyopaque, optional_args: UnloadBankOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnloadBank_Async_ID(
            in_bank_id,
            in_memory_bank,
            @ptrCast(in_bank_callback),
            in_cookie,
            @intFromEnum(optional_args.bank_type),
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

    const raw_bank_name = common.toCString(allocator, in_bank_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_bank_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareBank_String(
            @intFromEnum(in_preparation_type),
            raw_bank_name,
            @intFromEnum(optional_args.flags),
            @intFromEnum(optional_args.bank_type),
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
            @intFromEnum(in_preparation_type),
            in_bank_id,
            @intFromEnum(optional_args.flags),
            @intFromEnum(optional_args.bank_type),
        ),
    );
}

pub fn prepareBankAsyncString(
    fallback_allocator: std.mem.Allocator,
    in_preparation_type: PreparationType,
    in_bank_name: []const u8,
    in_bank_callback: callbacks.AkBankCallbackFunc,
    in_cookie: ?*anyopaque,
    optional_args: PrepareBankOptionalArgs,
) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_bank_name = common.toCString(allocator, in_bank_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_bank_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareBank_Async_String(
            @intFromEnum(in_preparation_type),
            raw_bank_name,
            @ptrCast(in_bank_callback),
            in_cookie,
            @intFromEnum(optional_args.flags),
            @intFromEnum(optional_args.bank_type),
        ),
    );
}

pub fn prepareBankAsyncID(
    in_preparation_type: PreparationType,
    in_bank_id: common.AkBankID,
    in_bank_callback: callbacks.AkBankCallbackFunc,
    in_cookie: ?*anyopaque,
    optional_args: PrepareBankOptionalArgs,
) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareBank_Async_ID(
            @intFromEnum(in_preparation_type),
            in_bank_id,
            @ptrCast(in_bank_callback),
            in_cookie,
            @intFromEnum(optional_args.flags),
            @intFromEnum(optional_args.bank_type),
        ),
    );
}

pub fn clearPreparedEvents() common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_ClearPreparedEvents(),
    );
}

pub fn prepareEventString(fallback_allocator: std.mem.Allocator, in_preparation_type: PreparationType, in_event_names: []const []const u8) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    const char_allocator = stack_char_allocator.get();

    var area_allocator = std.heap.ArenaAllocator.init(char_allocator);
    defer area_allocator.deinit();

    const allocator = area_allocator.allocator();

    var raw_event_names_list = std.ArrayList([*:0]const u8).init(allocator);
    defer raw_event_names_list.deinit();

    for (in_event_names) |event_name| {
        const raw_event_name = common.toCString(allocator, event_name) catch return common.WwiseError.Fail;
        raw_event_names_list.append(raw_event_name) catch return common.WwiseError.Fail;
    }

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareEvent_String(
            @intFromEnum(in_preparation_type),
            @ptrCast(raw_event_names_list.items),
            @truncate(raw_event_names_list.items.len),
        ),
    );
}

pub fn prepareEventID(in_preparation_type: PreparationType, in_event_ids: []const common.AkUniqueID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareEvent_ID(
            @intFromEnum(in_preparation_type),
            @ptrCast(@constCast(in_event_ids)),
            @truncate(in_event_ids.len),
        ),
    );
}

pub fn prepareEventAsyncString(
    fallback_allocator: std.mem.Allocator,
    in_preparation_type: PreparationType,
    in_event_names: [][]const u8,
    in_bank_callback: callbacks.AkBankCallbackFunc,
    in_cookie: ?*anyopaque,
) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    const char_allocator = stack_char_allocator.get();

    var area_allocator = std.heap.ArenaAllocator.init(char_allocator);
    defer area_allocator.deinit();

    const allocator = area_allocator.allocator();

    var raw_event_names_list = std.ArrayList([*:0]const u8).init(allocator);
    defer raw_event_names_list.deinit();

    for (in_event_names) |event_name| {
        const raw_event_name = common.toCString(allocator, event_name) catch return common.WwiseError.Fail;
        raw_event_names_list.append(raw_event_name) catch return common.WwiseError.Fail;
    }

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareEvent_Async_String(
            @intFromEnum(in_preparation_type),
            @ptrCast(raw_event_names_list.items),
            @truncate(raw_event_names_list.items.len),
            @ptrCast(in_bank_callback),
            in_cookie,
        ),
    );
}

pub fn prepareEventAsyncID(
    in_preparation_type: PreparationType,
    in_event_ids: []const common.AkUniqueID,
    in_bank_callback: callbacks.AkBankCallbackFunc,
    in_cookie: ?*anyopaque,
) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareEvent_Async_ID(
            @intFromEnum(in_preparation_type),
            @ptrCast(@constCast(in_event_ids)),
            @truncate(in_event_ids.len),
            @ptrCast(in_bank_callback),
            in_cookie,
        ),
    );
}

pub fn setMedia(in_source_settings: []const AkSourceSettings) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetMedia(
            @ptrCast(@constCast(in_source_settings)),
            @truncate(in_source_settings.len),
        ),
    );
}

pub fn unsetMedia(in_source_settings: []const AkSourceSettings) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnsetMedia(
            @ptrCast(@constCast(in_source_settings)),
            @truncate(in_source_settings.len),
        ),
    );
}

pub fn tryUnsetMedia(in_source_settings: []const AkSourceSettings, unset_results: ?[*]common.AKRESULT) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_TryUnsetMedia(
            @ptrCast(@constCast(in_source_settings)),
            @truncate(in_source_settings.len),
            @ptrCast(unset_results),
        ),
    );
}

pub fn prepareGameSyncsString(
    fallback_allocator: std.mem.Allocator,
    in_game_sync_type: common.AkGroupType,
    in_preparation_type: PreparationType,
    in_group_name: []const u8,
    in_game_sync_names: [][]const u8,
) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    const char_allocator = stack_char_allocator.get();

    var area_allocator = std.heap.ArenaAllocator.init(char_allocator);
    defer area_allocator.deinit();

    const allocator = area_allocator.allocator();

    const raw_group_name = common.toCString(allocator, in_group_name) catch return common.WwiseError.Fail;

    var raw_game_sync_names_list = std.ArrayList([*:0]const u8).init(allocator);
    defer raw_game_sync_names_list.deinit();

    for (in_game_sync_names) |game_sync_name| {
        const raw_game_sync_name = common.toCString(allocator, game_sync_name) catch return common.WwiseError.Fail;
        raw_game_sync_names_list.append(raw_game_sync_name) catch return common.WwiseError.Fail;
    }

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareGameSyncs_String(
            @intFromEnum(in_preparation_type),
            @intFromEnum(in_game_sync_type),
            raw_group_name,
            @ptrCast(raw_game_sync_names_list.items),
            @truncate(raw_game_sync_names_list.items.len),
        ),
    );
}

pub fn prepareGameSyncsID(
    in_preparation_type: PreparationType,
    in_game_sync_type: common.AkGroupType,
    in_group_id: u32,
    in_game_sync_ids: []const u32,
) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareGameSyncs_ID(
            @intFromEnum(in_preparation_type),
            @intFromEnum(in_game_sync_type),
            in_group_id,
            @ptrCast(@constCast(in_game_sync_ids)),
            @truncate(in_game_sync_ids.len),
        ),
    );
}

pub fn prepareGameSyncsAsyncString(
    fallback_allocator: std.mem.Allocator,
    in_preparation_type: PreparationType,
    in_game_sync_type: common.AkGroupType,
    in_group_name: []const u8,
    in_game_sync_names: [][]const u8,
    in_bank_callback: callbacks.AkBankCallbackFunc,
    in_cookie: ?*anyopaque,
) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    const char_allocator = stack_char_allocator.get();

    var area_allocator = std.heap.ArenaAllocator.init(char_allocator);
    defer area_allocator.deinit();

    const allocator = area_allocator.allocator();

    const raw_group_name = common.toCString(allocator, in_group_name) catch return common.WwiseError.Fail;

    var raw_game_sync_names_list = std.ArrayList([*:0]const u8).init(allocator);
    defer raw_game_sync_names_list.deinit();

    for (in_game_sync_names) |game_sync_name| {
        const raw_game_sync_name = common.toCString(allocator, game_sync_name) catch return common.WwiseError.Fail;
        raw_game_sync_names_list.append(raw_game_sync_name) catch return common.WwiseError.Fail;
    }

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareGameSyncs_Async_String(
            @intFromEnum(in_preparation_type),
            @intFromEnum(in_game_sync_type),
            raw_group_name,
            @ptrCast(raw_game_sync_names_list.items),
            @truncate(raw_game_sync_names_list.items.len),
            @ptrCast(in_bank_callback),
            in_cookie,
        ),
    );
}

pub fn prepareGameSyncsAsyncID(
    in_preparation_type: PreparationType,
    in_game_sync_type: common.AkGroupType,
    in_group_id: u32,
    in_game_sync_ids: []const u32,
    in_bank_callback: callbacks.AkBankCallbackFunc,
    in_cookie: ?*anyopaque,
) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PrepareGameSyncs_Async_ID(
            @intFromEnum(in_preparation_type),
            @intFromEnum(in_game_sync_type),
            in_group_id,
            @ptrCast(@constCast(in_game_sync_ids)),
            @truncate(in_game_sync_ids.len),
            @ptrCast(in_bank_callback),
            in_cookie,
        ),
    );
}

pub fn setListeners(in_emitter_game_obj: common.AkGameObjectID, in_listener_game_objs: []const common.AkGameObjectID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetListeners(
            in_emitter_game_obj,
            @ptrCast(in_listener_game_objs),
            @truncate(in_listener_game_objs.len),
        ),
    );
}

pub fn addListener(in_emitter_game_obj: common.AkGameObjectID, in_listener_game_obj: common.AkGameObjectID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_AddListener(in_emitter_game_obj, in_listener_game_obj),
    );
}

pub fn removeListener(in_emitter_game_obj: common.AkGameObjectID, in_listener_game_obj: common.AkGameObjectID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RemoveListener(in_emitter_game_obj, in_listener_game_obj),
    );
}

pub fn setDefaultListeners(in_listener_game_objs: []const common.AkGameObjectID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetDefaultListeners(
            @ptrCast(in_listener_game_objs),
            @truncate(in_listener_game_objs.len),
        ),
    );
}

pub fn addDefaultListener(in_listener_game_obj: common.AkGameObjectID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_AddDefaultListener(in_listener_game_obj),
    );
}

pub fn removeDefaultListener(in_listener_game_obj: common.AkGameObjectID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RemoveDefaultListener(in_listener_game_obj),
    );
}

pub fn resetListenersToDefault(in_emitter_game_obj: common.AkGameObjectID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_ResetListenersToDefault(in_emitter_game_obj),
    );
}

pub fn setListenerSpatialization(
    in_listener_id: common.AkGameObjectID,
    in_spatialized: bool,
    in_channel_config: speaker_config.AkChannelConfig,
    in_volume_offsets: SpeakerVolumes.VectorPtr,
) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetListenerSpatialization(
            in_listener_id,
            in_spatialized,
            in_channel_config.toC(),
            in_volume_offsets,
        ),
    );
}

pub const SetRTPCValueOptionalArgs = struct {
    game_object_id: common.AkGameObjectID = common.AK_INVALID_GAME_OBJECT,
    value_change_duration: common.AkTimeMs = 0,
    fade_curve: common.AkCurveInterpolation = .linear,
    bypass_internal_value_interpolation: bool = false,
};

pub fn setRTPCValueID(in_rtpc_id: common.AkRtpcID, in_value: common.AkRtpcValue, optional_args: SetRTPCValueOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetRTPCValue_ID(
            in_rtpc_id,
            in_value,
            optional_args.game_object_id,
            optional_args.value_change_duration,
            @intFromEnum(optional_args.fade_curve),
            optional_args.bypass_internal_value_interpolation,
        ),
    );
}

pub fn setRTPCValueString(fallback_allocator: std.mem.Allocator, in_rtpc_name: []const u8, in_value: common.AkRtpcValue, optional_args: SetRTPCValueOptionalArgs) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_rtpc_name = common.toCString(allocator, in_rtpc_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_rtpc_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetRTPCValue_String(
            raw_rtpc_name,
            in_value,
            optional_args.game_object_id,
            optional_args.value_change_duration,
            @intFromEnum(optional_args.fade_curve),
            optional_args.bypass_internal_value_interpolation,
        ),
    );
}

pub const SetRTPCValueByPlayingIDOptionalArgs = struct {
    value_change_duration: common.AkTimeMs = 0,
    fade_curve: common.AkCurveInterpolation = .linear,
    bypass_internal_value_interpolation: bool = false,
};

pub fn setRTPCValueByPlayingID(
    in_rtpc_id: common.AkRtpcID,
    in_value: common.AkRtpcValue,
    in_playing_id: common.AkPlayingID,
    optional_args: SetRTPCValueByPlayingIDOptionalArgs,
) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetRTPCValueByPlayingID_ID(
            in_rtpc_id,
            in_value,
            in_playing_id,
            optional_args.value_change_duration,
            @intFromEnum(optional_args.fade_curve),
            optional_args.bypass_internal_value_interpolation,
        ),
    );
}

pub fn setRTPCValueByPlayingIDString(
    fallback_allocator: std.mem.Allocator,
    in_rtpc_name: []const u8,
    in_value: common.AkRtpcValue,
    in_playing_id: common.AkPlayingID,
    optional_args: SetRTPCValueByPlayingIDOptionalArgs,
) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_rtpc_name = common.toCString(allocator, in_rtpc_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_rtpc_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetRTPCValueByPlayingID_String(
            raw_rtpc_name,
            in_value,
            in_playing_id,
            optional_args.value_change_duration,
            @intFromEnum(optional_args.fade_curve),
            optional_args.bypass_internal_value_interpolation,
        ),
    );
}

pub const ResetRTPCValueOptionalArgs = struct {
    game_object_id: common.AkGameObjectID = common.AK_INVALID_GAME_OBJECT,
    value_change_duration: common.AkTimeMs = 0,
    fade_curve: common.AkCurveInterpolation = .linear,
    bypass_internal_value_interpolation: bool = false,
};

pub fn resetRTPCValueID(in_rtpc_id: common.AkRtpcID, optional_args: ResetRTPCValueOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_ResetRTPCValue_ID(
            in_rtpc_id,
            optional_args.game_object_id,
            optional_args.value_change_duration,
            @intFromEnum(optional_args.fade_curve),
            optional_args.bypass_internal_value_interpolation,
        ),
    );
}

pub fn resetRTPCValueString(fallback_allocator: std.mem.Allocator, in_rtpc_name: []const u8, optional_args: ResetRTPCValueOptionalArgs) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_rtpc_name = common.toCString(allocator, in_rtpc_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_rtpc_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_ResetRTPCValue_String(
            raw_rtpc_name,
            optional_args.game_object_id,
            optional_args.value_change_duration,
            @intFromEnum(optional_args.fade_curve),
            optional_args.bypass_internal_value_interpolation,
        ),
    );
}

pub fn setSwitchID(in_switch_group: common.AkSwitchGroupID, in_switch_state: common.AkSwitchStateID, in_game_object_id: common.AkGameObjectID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetSwitch_ID(in_switch_group, in_switch_state, in_game_object_id),
    );
}

pub fn setSwitchString(fallback_allocator: std.mem.Allocator, in_switch_group: []const u8, in_switch_state: []const u8, in_game_object_id: common.AkGameObjectID) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_switch_group = common.toCString(allocator, in_switch_group) catch return common.WwiseError.Fail;
    defer allocator.free(raw_switch_group);

    const raw_switch_state = common.toCString(allocator, in_switch_state) catch return common.WwiseError.Fail;
    defer allocator.free(raw_switch_state);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetSwitch_String(raw_switch_group, raw_switch_state, in_game_object_id),
    );
}

pub fn postTriggerID(in_trigger_id: common.AkTriggerID, in_game_object_id: common.AkGameObjectID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PostTrigger_ID(in_trigger_id, in_game_object_id),
    );
}

pub fn postTriggerString(fallback_allocator: std.mem.Allocator, in_trigger_name: []const u8, in_game_object_id: common.AkGameObjectID) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_trigger_name = common.toCString(allocator, in_trigger_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_trigger_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_PostTrigger_String(raw_trigger_name, in_game_object_id),
    );
}

pub fn setStateID(in_state_group: common.AkStateGroupID, in_state: common.AkStateID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetState_ID(in_state_group, in_state),
    );
}

pub fn setStateString(fallback_allocator: std.mem.Allocator, in_state_group: []const u8, in_state: []const u8) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_state_group = common.toCString(allocator, in_state_group) catch return common.WwiseError.Fail;
    defer allocator.free(raw_state_group);

    const raw_state = common.toCString(allocator, in_state) catch return common.WwiseError.Fail;
    defer allocator.free(raw_state);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetState_String(raw_state_group, raw_state),
    );
}

pub fn setGameObjectAuxSendValues(allocator: std.mem.Allocator, in_game_object_id: common.AkGameObjectID, in_aux_send_values: []const common.AkAuxSendValue) common.WwiseError!void {
    const raw_aux_send_values = allocator.alloc(c.WWISEC_AkAuxSendValue, in_aux_send_values.len) catch return common.WwiseError.Fail;
    defer allocator.free(raw_aux_send_values);

    for (0..in_aux_send_values.len) |index| {
        raw_aux_send_values[index] = in_aux_send_values[index].toC();
    }

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetGameObjectAuxSendValues(
            in_game_object_id,
            @ptrCast(raw_aux_send_values),
            @truncate(in_aux_send_values.len),
        ),
    );
}

pub fn registerBusVolumeCallback(in_bus_id: common.AkUniqueID, in_callback: callbacks.AkBusCallbackFunc, in_cookie: ?*anyopaque) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RegisterBusVolumeCallback(
            in_bus_id,
            @ptrCast(in_callback),
            in_cookie,
        ),
    );
}

pub fn registerBusMeteringCallback(in_bus_id: common.AkUniqueID, in_callback: callbacks.AkBusMeteringCallbackFunc, in_metering_flags: common.AkMeteringFlags, in_cookie: ?*anyopaque) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RegisterBusMeteringCallback(
            in_bus_id,
            @ptrCast(in_callback),
            in_metering_flags.toC(),
            in_cookie,
        ),
    );
}

pub fn registerOutputDeviceMeteringCallback(in_id_output: common.AkOutputDeviceID, in_callback: callbacks.AkOutputDeviceMeteringCallbackFunc, in_metering_flags: common.AkMeteringFlags, in_cookie: ?*anyopaque) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RegisterOutputDeviceMeteringCallback(
            in_id_output,
            @ptrCast(in_callback),
            in_metering_flags.toC(),
            in_cookie,
        ),
    );
}

pub fn setGameObjectOutputBusVolume(in_emitter_obj_id: common.AkGameObjectID, in_listener_obj_id: common.AkGameObjectID, in_control_value: f32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetGameObjectOutputBusVolume(in_emitter_obj_id, in_listener_obj_id, in_control_value),
    );
}

pub fn setActorMixerEffect(in_audio_node_id: common.AkUniqueID, in_fx_index: u32, in_share_set_id: common.AkUniqueID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetActorMixerEffect(in_audio_node_id, in_fx_index, in_share_set_id),
    );
}

pub fn setBusEffectID(in_audio_node_id: common.AkUniqueID, in_fx_index: u32, in_share_set_id: common.AkUniqueID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetBusEffect_ID(in_audio_node_id, in_fx_index, in_share_set_id),
    );
}

pub fn setBusEffectString(fallback_allocatr: std.mem.Allocator, in_bus_name: []const u8, in_fx_index: u32, in_share_set_id: common.AkUniqueID) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocatr);
    var allocator = stack_char_allocator.get();

    const raw_bus_name = common.toCString(allocator, in_bus_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_bus_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetBusEffect_String(raw_bus_name, in_fx_index, in_share_set_id),
    );
}

pub fn setOutputDeviceEffect(in_output_device_id: common.AkOutputDeviceID, in_fx_index: u32, in_fx_share_set_id: common.AkUniqueID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetOutputDeviceEffect(in_output_device_id, in_fx_index, in_fx_share_set_id),
    );
}

pub fn setMixerID(in_audio_node_id: common.AkUniqueID, in_share_set_id: common.AkUniqueID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetMixer_ID(in_audio_node_id, in_share_set_id),
    );
}

pub fn setMixerString(fallback_allocator: std.mem.Allocator, in_bus_name: []const u8, in_share_set_id: common.AkUniqueID) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_bus_name = common.toCString(allocator, in_bus_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_bus_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetMixer_String(raw_bus_name, in_share_set_id),
    );
}

pub fn setBusConfigID(in_audio_node_id: common.AkUniqueID, in_channel_config: speaker_config.AkChannelConfig) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetBusConfig_ID(in_audio_node_id, in_channel_config.toC()),
    );
}

pub fn setBusConfigString(fallback_allocator: std.mem.Allocator, in_bus_name: []const u8, in_channe_config: speaker_config.AkChannelConfig) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_bus_name = common.toCString(allocator, in_bus_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_bus_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetBusConfig_String(raw_bus_name, in_channe_config.toC()),
    );
}

pub fn setObjectObstructionAndOcclusion(in_emitter_id: common.AkGameObjectID, in_listener_id: common.AkGameObjectID, in_obstruction_level: f32, in_occlusion_level: f32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetObjectObstructionAndOcclusion(in_emitter_id, in_listener_id, in_obstruction_level, in_occlusion_level),
    );
}

pub fn setMultipleObstructionAndOcclusion(in_emitter_id: common.AkGameObjectID, in_listener_id: common.AkGameObjectID, in_obstruction_occlusion_values: []const common.AkObstructionOcclusionValues) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetMultipleObstructionAndOcclusion(
            in_emitter_id,
            in_listener_id,
            @ptrCast(@constCast(in_obstruction_occlusion_values)),
            @truncate(in_obstruction_occlusion_values.len),
        ),
    );
}

pub fn getContainerHistory(in_bytes: ?*IBytes.IWriteBytes) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetContainerHistory(@ptrCast(in_bytes)),
    );
}

pub fn setContainerHistory(in_bytes: ?*IBytes.IReadBytes) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetContainerHistory(@ptrCast(in_bytes)),
    );
}

pub fn startOutputCapture(fallback_allocator: std.mem.Allocator, in_capture_file_name: []const u8) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_capture_file_name = common.toOSChar(allocator, in_capture_file_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_capture_file_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_StartOutputCapture(raw_capture_file_name),
    );
}

pub fn stopOutputCapture() common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_StopOutputCapture(),
    );
}

pub fn addOutputCaptureMarker(fallback_allocator: std.mem.Allocator, in_marker_text: []const u8) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    const allocator = stack_char_allocator.get();

    const raw_marker_text = common.toCString(allocator, in_marker_text) catch return common.WwiseError.Fail;

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_AddOutputCaptureMarker(raw_marker_text),
    );
}

pub fn getSampleRate() u32 {
    return c.WWISEC_AK_SoundEngine_GetSampleRate();
}

pub const RegistereCaptureCallbackOptionalArgs = struct {
    id_output: common.AkOutputDeviceID = common.AK_INVALID_OUTPUT_DEVICE_ID,
    cookie: ?*anyopaque = null,
};

pub fn regiserCaptureCallback(in_callback: callbacks.AkCaptureCallbackFunc, optional_args: RegistereCaptureCallbackOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RegisterCaptureCallback(
            @ptrCast(in_callback),
            optional_args.id_output,
            optional_args.cookie,
        ),
    );
}

pub const UnregistereCaptureCallbackOptionalArgs = struct {
    id_output: common.AkOutputDeviceID = common.AK_INVALID_OUTPUT_DEVICE_ID,
    cookie: ?*anyopaque = null,
};

pub fn unregisterCaptureCallback(in_callback: callbacks.AkCaptureCallbackFunc, optional_args: UnregistereCaptureCallbackOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_UnregisterCaptureCallback(
            @ptrCast(in_callback),
            optional_args.id_output,
            optional_args.cookie,
        ),
    );
}

pub fn startProfilerCapture(fallback_allocator: std.mem.Allocator, in_capture_file_name: []const u8) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_capture_file_name = common.toOSChar(allocator, in_capture_file_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_capture_file_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_StartProfilerCapture(raw_capture_file_name),
    );
}

pub fn stopProfilerCapture() common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_StopProfilerCapture(),
    );
}

pub fn setOfflineRenderingFrameTime(in_frame_time_in_secconds: f32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetOfflineRenderingFrameTime(in_frame_time_in_secconds),
    );
}

pub fn setOfflineRendering(in_enable_offline_rendering: bool) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetOfflineRendering(in_enable_offline_rendering),
    );
}

pub fn addOutput(output_settings: *const settings.AkOutputSettings, listeners: []common.AkGameObjectID) common.WwiseError!common.AkOutputDeviceID {
    var out_device_id: common.AkOutputDeviceID = common.AK_INVALID_OUTPUT_DEVICE_ID;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_AddOutput(
            @ptrCast(output_settings),
            @ptrCast(&out_device_id),
            listeners.ptr,
            @truncate(listeners.len),
        ),
    );

    return out_device_id;
}

pub fn removeOutput(id_output: common.AkOutputDeviceID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RemoveOutput(id_output),
    );
}

pub fn replaceOutput(output_settings: *const settings.AkOutputSettings, in_device_id: common.AkOutputDeviceID, out_device_id: ?*common.AkOutputDeviceID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_ReplaceOutput(@ptrCast(output_settings), in_device_id, @ptrCast(out_device_id)),
    );
}

pub fn getOutputID(in_id_shareset: common.AkUniqueID, in_id_device: u32) common.AkOutputDeviceID {
    return c.WWISEC_AK_SoundEngine_GetOutputID_ID(in_id_shareset, in_id_device);
}

pub fn getOuputIDString(fallback_allocator: std.mem.Allocator, in_share_set: []const u8, in_id_device: u32) !common.AkOutputDeviceID {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_share_set = try common.toCString(allocator, in_share_set);
    defer allocator.free(raw_share_set);

    return c.WWISEC_AK_SoundEngine_GetOutputID_String(raw_share_set, in_id_device);
}

pub fn setBusDeviceID(in_id_bus: common.AkUniqueID, in_id_new_device: common.AkUniqueID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetBusDevice_ID(in_id_bus, in_id_new_device),
    );
}

pub fn setBusDeviceString(fallback_allocator: std.mem.Allocator, in_bus_name: []const u8, in_device_name: []const u8) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_bus_name = common.toCString(allocator, in_bus_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_bus_name);

    const raw_device_name = common.toCString(allocator, in_device_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_device_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetBusDevice_String(raw_bus_name, raw_device_name),
    );
}

pub fn getDeviceListPlugin(allocator: std.mem.Allocator, in_company_id: u32, in_plugin_id: u32, io_max_num_devices: *u32, out_device_descriptions_opt: ?[*]common.AkDeviceDescription) common.WwiseError!void {
    var area_allocator_instance = std.heap.ArenaAllocator.init(allocator);
    defer area_allocator_instance.deinit();

    var area_allocator = area_allocator_instance.allocator();

    const raw_device_descriptions_ptr: ?[*]c.WWISEC_AkDeviceDescription = blk: {
        if (out_device_descriptions_opt) |_| {
            const raw_device_descriptions = area_allocator.alloc(c.WWISEC_AkDeviceDescription, io_max_num_devices.*) catch return common.WwiseError.Fail;
            break :blk @as(?[*]c.WWISEC_AkDeviceDescription, @ptrCast(raw_device_descriptions));
        }

        break :blk @as(?[*]c.WWISEC_AkDeviceDescription, null);
    };

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetDeviceList_Plugin(
            in_company_id,
            in_plugin_id,
            io_max_num_devices,
            raw_device_descriptions_ptr,
        ),
    );

    if (out_device_descriptions_opt) |out_device_descriptions| {
        if (raw_device_descriptions_ptr) |raw_device_descritions| {
            for (0..io_max_num_devices.*) |index| {
                out_device_descriptions[index] = common.AkDeviceDescription.fromC(allocator, raw_device_descritions[index]) catch return common.WwiseError.Fail;
            }
        }
    }
}

pub fn getDeviceListShareSet(allocator: std.mem.Allocator, in_audio_device_share_set_id: common.AkUniqueID, io_max_num_devices: *u32, out_device_descriptions_opt: ?[*]common.AkDeviceDescription) common.WwiseError!void {
    var area_allocator_instance = std.heap.ArenaAllocator.init(allocator);
    defer area_allocator_instance.deinit();

    var area_allocator = area_allocator_instance.allocator();

    const raw_device_descriptions_ptr: ?[*]c.WWISEC_AkDeviceDescription = blk: {
        if (out_device_descriptions_opt) |_| {
            const raw_device_descriptions = area_allocator.alloc(c.WWISEC_AkDeviceDescription, io_max_num_devices.*) catch return common.WwiseError.Fail;
            break :blk @as(?[*]c.WWISEC_AkDeviceDescription, @ptrCast(raw_device_descriptions));
        }

        break :blk @as(?[*]c.WWISEC_AkDeviceDescription, null);
    };

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetDeviceList_ShareSet(
            in_audio_device_share_set_id,
            io_max_num_devices,
            raw_device_descriptions_ptr,
        ),
    );

    if (out_device_descriptions_opt) |out_device_descriptions| {
        if (raw_device_descriptions_ptr) |raw_device_descritions| {
            for (0..io_max_num_devices.*) |index| {
                out_device_descriptions[index] = common.AkDeviceDescription.fromC(allocator, raw_device_descritions[index]) catch return common.WwiseError.Fail;
            }
        }
    }
}

pub fn setOutputVolume(in_id_output: common.AkOutputDeviceID, in_volume: f32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_SetOutputVolume(in_id_output, in_volume),
    );
}

pub fn getDeviceSpatialAudioSupport(in_id_device: u32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetDeviceSpatialAudioSupport(in_id_device),
    );
}

pub const SuspendOptionalArgs = struct {
    render_anyway: bool = false,
    fadeout: bool = true,
};

pub fn @"suspend"(optional_args: SuspendOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Suspend(optional_args.render_anyway, optional_args.fadeout),
    );
}

pub const WakeupFromSuspendOptionalArgs = struct {
    delay_ms: u32 = 0,
};

pub fn wakeupFromSuspend(optional_args: WakeupFromSuspendOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_WakeupFromSuspend(optional_args.delay_ms),
    );
}

pub fn getBufferTick() u32 {
    return c.WWISEC_AK_SoundEngine_GetBufferTick();
}

pub fn getSampleTick() u64 {
    return c.WWISEC_AK_SoundEngine_GetSampleTick();
}
