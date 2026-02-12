const ak_3d_objects = @import("ak_3d_objects.zig");
const c = @import("wwise_c");
const callback_types = @import("callback_types.zig");
const common = @import("common.zig");
const constants = @import("constants.zig");
const enums = @import("enums.zig");
const IAkPluginMemAlloc = @import("IAkPluginMemAlloc.zig").IAkPluginMemAlloc;
const IAkStreamMgr = @import("IAkStreamMgr.zig");
const midi_types = @import("midi_types.zig");
const Monitor = @import("Monitor.zig");
const platform_context = @import("platform_context.zig");
const settings = @import("settings.zig");
const speaker_config = @import("speaker_config.zig");
const SpeakerVolumes = @import("SpeakerVolumes.zig");
const std = @import("std");
const typedefs = @import("typedefs.zig");
const virtual_acoustics = @import("virtual_acoustics.zig");
const zig = @import("zig.zig");

pub const AkCreatePluginCallback = ?*const fn (in_allocator: ?*IAkPluginMemAlloc) callconv(.c) ?*IAkPlugin;
pub const AkCreateParamCallback = ?*const fn (in_allocator: ?*IAkPluginMemAlloc) callconv(.c) ?*IAkPluginParam;
pub const AkGetDeviceListCallback = ?*const fn (io_max_num_devices: *u32, out_device_description: ?[*]c.WWISEC_AkDeviceDescription) callconv(.c) enums.AKRESULT;

pub const AkPluginServiceType = enum(zig.DefaultEnumType) {
    mixer = c.WWISEC_AK_PluginServiceType_Mixer,
    rng = c.WWISEC_AK_PluginServiceType_RNG,
    audio_object_attenuation = c.WWISEC_AK_PluginServiceType_AudioObjectAttenuation,
    audio_object_priority = c.WWISEC_AK_PluginServiceType_AudioObjectPriority,
    hash_table = c.WWISEC_AK_PluginServiceType_HashTable,
    markers = c.WWISEC_AK_PluginServiceType_Markers,
    temp_alloc = c.WWISEC_AK_PluginServiceType_TempAlloc,
};

pub const IAkPluginService = opaque {};

pub const IAkMixerInputContext = opaque {};
pub const IAkMixerPluginContext = opaque {};

pub const IAkGlobalPluginContext = opaque {
    pub fn getStreamMgr(self: *const IAkGlobalPluginContext) *IAkStreamMgr.IAkStreamMgr {
        return @ptrCast(
            @alignCast(
                c.WWISEC_AK_IAkGlobalPluginContext_GetStreamMgr(
                    @ptrCast(self),
                ),
            ),
        );
    }

    pub fn getMaxBufferLength(self: *const IAkGlobalPluginContext) u16 {
        return c.WWISEC_AK_IAkGlobalPluginContext_GetMaxBufferLength(@ptrCast(self));
    }

    pub fn isRenderingOffline(self: *const IAkGlobalPluginContext) bool {
        return c.WWISEC_AK_IAkGlobalPluginContext_IsRenderingOffline(@ptrCast(self));
    }

    pub fn getSampleRate(self: *const IAkGlobalPluginContext) u32 {
        return c.WWISEC_AK_IAkGlobalPluginContext_GetSampleRate(@ptrCast(self));
    }

    pub fn postMonitorMessage(self: *IAkGlobalPluginContext, fallback_allocator: std.mem.Allocator, in_error: []const u8, in_error_level: Monitor.ErrorLevel) zig.WwiseError!void {
        var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_char_allocator.get();

        const raw_error = common.toCString(allocator, in_error) catch return zig.WwiseError.Fail;
        defer allocator.free(raw_error);

        return zig.handleAkResult(
            c.WWISEC_AK_IAkGlobalPluginContext_PostMonitorMessage(
                @ptrCast(self),
                raw_error,
                in_error_level.toC(),
            ),
        );
    }

    pub fn registerPlugin(self: *IAkGlobalPluginContext, in_type: enums.AkPluginType, in_company_id: u32, in_plugin_id: u32, in_create_func: AkCreatePluginCallback, in_create_param_func: AkCreateParamCallback) zig.WwiseError!void {
        return zig.handleAkResult(
            c.WWISEC_AK_IAkGlobalPluginContext_RegisterPlugin(
                @ptrCast(self),
                @intFromEnum(in_type),
                in_company_id,
                in_plugin_id,
                @ptrCast(in_create_func),
                @ptrCast(in_create_param_func),
            ),
        );
    }

    pub fn registerCodec(self: *IAkGlobalPluginContext, in_company_id: u32, in_plugin_id: u32, in_file_create_func: common.AkCreateFileSourceCallback, in_bank_create_func: common.AkCreateBankSourceCallback) zig.WwiseError!void {
        return zig.handleAkResult(
            c.WWISEC_AK_IAkGlobalPluginContext_RegisterCodec(
                @ptrCast(self),
                in_company_id,
                in_plugin_id,
                @ptrCast(in_file_create_func),
                @ptrCast(in_bank_create_func),
            ),
        );
    }

    pub const RegisterGlobalCallbackOptionalArgs = struct {
        location: callback_types.AkGlobalCallbackLocation = .{ .begin_render = true },
        cookie: ?*anyopaque = null,
    };

    pub fn registerGlobalCallback(self: *IAkGlobalPluginContext, in_type: enums.AkPluginType, in_company_id: u32, in_plugin_id: u32, in_callback: callback_types.AkGlobalCallbackFunc, optional_args: RegisterGlobalCallbackOptionalArgs) zig.WwiseError!void {
        return zig.handleAkResult(
            c.WWISEC_AK_IAkGlobalPluginContext_RegisterGlobalCallback(
                @ptrCast(self),
                @intFromEnum(in_type),
                in_company_id,
                in_plugin_id,
                @ptrCast(in_callback),
                optional_args.location.toC(),
                optional_args.cookie,
            ),
        );
    }

    pub const UnregisterGlobalCallbackOptionArgs = struct {
        location: callback_types.AkGlobalCallbackLocation = .{ .begin_render = true },
    };

    pub fn unregisterGlobalCallback(
        self: *IAkGlobalPluginContext,
        in_callback: callback_types.AkGlobalCallbackFunc,
        optional_args: UnregisterGlobalCallbackOptionArgs,
    ) zig.WwiseError!void {
        return zig.handleAkResult(
            c.WWISEC_AK_IAkGlobalPluginContext_UnregisterGlobalCallback(
                @ptrCast(self),
                @ptrCast(in_callback),
                optional_args.location.toC(),
            ),
        );
    }

    pub fn getAllocator(self: *IAkGlobalPluginContext) ?*IAkPluginMemAlloc {
        return @ptrCast(c.WWISEC_AK_IAkGlobalPluginContext_GetAllocator(@ptrCast(self)));
    }

    pub const SetRtpcValueOptionalArgs = struct {
        game_object_id: typedefs.AkGameObjectID = constants.AK_INVALID_GAME_OBJECT,
        value_change_duration: typedefs.AkTimeMs = 0,
        fade_curve: enums.AkCurveInterpolation = .linear,
        bypass_internal_value_interpolation: bool = false,
    };

    pub fn setRTPCValue(
        self: *IAkGlobalPluginContext,
        in_rtpcID: typedefs.AkRtpcID,
        in_value: typedefs.AkRtpcValue,
        optional_args: SetRtpcValueOptionalArgs,
    ) zig.WwiseError!void {
        return zig.handleAkResult(
            c.WWISEC_AK_IAkGlobalPluginContext_SetRTPCValue(
                @ptrCast(self),
                in_rtpcID,
                in_value,
                optional_args.game_object_id,
                optional_args.value_change_duration,
                @intFromEnum(optional_args.fade_curve),
                optional_args.bypass_internal_value_interpolation,
            ),
        );
    }

    pub fn sendPluginCustomGameData(
        self: *IAkGlobalPluginContext,
        in_bus_id: typedefs.AkUniqueID,
        in_bus_object_id: typedefs.AkGameObjectID,
        in_type: enums.AkPluginType,
        in_company_id: u32,
        in_plugin_id: u32,
        in_data: ?*const anyopaque,
        in_size_in_bytes: u32,
    ) zig.WwiseError!void {
        return zig.handleAkResult(
            c.WWISEC_AK_IAkGlobalPluginContext_SendPluginCustomGameData(
                @ptrCast(self),
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

    pub fn computeAmbisonicsEncoding(
        self: *IAkGlobalPluginContext,
        in_azimuth: f32,
        in_elevation: f32,
        in_cfg_ambisonics: speaker_config.AkChannelConfig,
        out_volumes: SpeakerVolumes.VectorPtr,
    ) void {
        return c.WWISEC_AK_IAkGlobalPluginContext_ComputeAmbisonicsEncoding(
            @ptrCast(self),
            in_azimuth,
            in_elevation,
            in_cfg_ambisonics.toC(),
            out_volumes,
        );
    }

    pub fn computeWeightedAmbisonicsDecodingFromSampledSphere(
        self: *IAkGlobalPluginContext,
        in_samples: []const ak_3d_objects.AkVector,
        in_cfg_ambisonics: speaker_config.AkChannelConfig,
        out_mx_volume: SpeakerVolumes.MatrixPtr,
    ) zig.WwiseError!void {
        return zig.handleAkResult(
            c.WWISEC_AK_IAkGlobalPluginContext_ComputeWeightedAmbisonicsDecodingFromSampledSphere(
                @ptrCast(self),
                @ptrCast(in_samples),
                @truncate(in_samples.len),
                in_cfg_ambisonics.toC(),
                out_mx_volume,
            ),
        );
    }

    pub fn getAcousticTexture(self: *IAkGlobalPluginContext, in_acoustic_texture_id: typedefs.AkAcousticTextureID) ?*const virtual_acoustics.AkAcousticTexture {
        return @ptrCast(
            c.WWISEC_AK_IAkGlobalPluginContext_GetAcousticTexture(@ptrCast(self), in_acoustic_texture_id),
        );
    }

    pub fn computeSphericalCoordinates(
        self: *const IAkGlobalPluginContext,
        in_pair: *const ak_3d_objects.AkEmitterListenerPair,
        out_azimuth: *f32,
        out_elevation: *f32,
    ) zig.WwiseError!void {
        return zig.handleAkResult(
            c.WWISEC_AK_IAkGlobalPluginContext_ComputeSphericalCoordinates(
                @ptrCast(self),
                @ptrCast(in_pair),
                out_azimuth,
                out_elevation,
            ),
        );
    }

    pub fn getPlatformInitSettings(self: *const IAkGlobalPluginContext) ?*const settings.AkPlatformInitSettings {
        return @ptrCast(c.WWISEC_AK_IAkGlobalPluginContext_GetPlatformInitSettings(@ptrCast(self)));
    }

    // It is recommended that you call deinit() on the returned AkInitSettings here
    pub fn getInitSettings(self: *const IAkGlobalPluginContext, allocator: std.mem.Allocator) !?settings.AkInitSettings {
        var raw_init_settings_opt: ?*const c.WWISEC_AkInitSettings = null;
        raw_init_settings_opt = @ptrCast(c.WWISEC_AK_IAkGlobalPluginContext_GetInitSettings(@ptrCast(self)));

        if (raw_init_settings_opt) |raw_init_settings| {
            return try settings.AkInitSettings.fromC(allocator, raw_init_settings.*);
        } else {
            return null;
        }
    }

    pub fn getAudioSettings(self: *const IAkGlobalPluginContext) zig.WwiseError!common.AkAudioSettings {
        var result: common.AkAudioSettings = .{};
        try zig.handleAkResult(c.WWISEC_AK_IAkGlobalPluginContext_GetAudioSettings(@ptrCast(self), @ptrCast(&result)));
        return result;
    }

    pub fn getIDFromString(self: *const IAkGlobalPluginContext, fallback_allocator: std.mem.Allocator, in_string: []const u8) !u32 {
        var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_char_allocator.get();

        const raw_string = try common.toCString(allocator, in_string);
        defer allocator.free(raw_string);

        return c.WWISEC_AK_IAkGlobalPluginContext_GetIDFromString(@ptrCast(self), raw_string);
    }

    pub const PostEventSyncOptionalArgs = struct {
        flags: callback_types.AkCallbackType = .{},
        callback: callback_types.AkCallbackFunc = null,
        cookie: ?*anyopaque = null,
        allocator: ?std.mem.Allocator = null,
        external_sources: ?[]const common.AkExternalSourceInfo = null,
        playing_id: typedefs.AkPlayingID = connstants.AK_INVALID_PLAYING_ID,
    };

    pub fn postEventSync(
        self: *IAkGlobalPluginContext,
        in_event_id: typedefs.AkUniqueID,
        in_game_object_id: typedefs.AkGameObjectID,
        optional_args: PostEventSyncOptionalArgs,
    ) !typedefs.AkPlayingID {
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

        return c.WWISEC_AK_IAkGlobalPluginContext_PostEventSync(
            @ptrCast(self),
            in_event_id,
            in_game_object_id,
            optional_args.flags.toC(),
            @ptrCast(optional_args.callback),
            optional_args.cookie,
            num_external_sources,
            external_sources_ptr,
            optional_args.playing_id,
        );
    }

    pub const PostMIDIOnEventSyncOptionalArgs = struct {
        absolute_offsets: bool = false,
        flags: callback_types.AkCallbackType = .{},
        callback: callback_types.AkCallbackFunc = null,
        cookie: ?*anyopaque = null,
        playing_id: typedefs.AkPlayingID = constants.AK_INVALID_PLAYING_ID,
    };

    // NOTE: mlarouche: Workaround for translate-c that does not put the proper alignment on AkMIDIPost
    extern fn WWISEC_AK_IAkGlobalPluginContext_PostMIDIOnEventSync(self: ?*c.WWISEC_AK_IAkGlobalPluginContext, in_eventID: c.WWISEC_AkUniqueID, in_gameObjectID: c.WWISEC_AkGameObjectID, in_pPosts: [*]midi_types.AkMIDIPost, in_uNumPosts: u16, in_bAbsoluteOffsets: bool, in_uFlags: u32, in_pfnCallback: c.WWISEC_AkCallbackFunc, in_pCookie: ?*anyopaque, in_playingID: c.WWISEC_AkPlayingID) c.WWISEC_AkPlayingID;

    pub fn postMIDIOnEventSync(
        self: *IAkGlobalPluginContext,
        in_event_id: typedefs.AkUniqueID,
        in_game_object_id: typedefs.AkGameObjectID,
        in_midi_posts: []const midi_types.AkMIDIPost,
        optional_args: PostMIDIOnEventSyncOptionalArgs,
    ) typedefs.AkPlayingID {
        return WWISEC_AK_IAkGlobalPluginContext_PostMIDIOnEventSync(
            @ptrCast(self),
            in_event_id,
            in_game_object_id,
            @ptrCast(@constCast(in_midi_posts)),
            @truncate(in_midi_posts.len),
            optional_args.absolute_offsets,
            optional_args.flags.toC(),
            @ptrCast(optional_args.callback),
            optional_args.cookie,
            optional_args.playing_id,
        );
    }

    pub const StopMIDIOnEventSync = struct {
        event_id: typedefs.AkUniqueID = constants.AK_INVALID_UNIQUE_ID,
        game_object_id: typedefs.AkGameObjectID = constants.AK_INVALID_GAME_OBJECT,
        playing_id: typedefs.AkPlayingID = constants.AK_INVALID_PLAYING_ID,
    };

    pub fn stopMIDIOnEventSync(self: *IAkGlobalPluginContext, optional_args: StopMIDIOnEventSync) zig.WwiseError!void {
        return zig.handleAkResult(
            c.WWISEC_AK_IAkGlobalPluginContext_StopMIDIOnEventSync(
                @ptrCast(self),
                optional_args.event_id,
                optional_args.game_object_id,
                optional_args.playing_id,
            ),
        );
    }

    pub fn getPlatformContext(self: *const IAkGlobalPluginContext) ?*platform_context.IAkPlatformContext {
        return @ptrCast(c.WWISEC_AK_IAkGlobalPluginContext_GetPlatformContext(@ptrCast(self)));
    }

    pub fn getPluginService(self: *const IAkGlobalPluginContext, in_plugin_service: AkPluginServiceType) ?*IAkPluginService {
        return @ptrCast(
            c.WWISEC_AK_IAkGlobalPluginContext_GetPluginService(@ptrCast(self), @intFromEnum(in_plugin_service)),
        );
    }

    pub fn getBufferTick(self: *const IAkGlobalPluginContext) u32 {
        return c.WWISEC_AK_IAkGlobalPluginContext_GetBufferTick(@ptrCast(self));
    }
};

pub const IAkPlugin = opaque {};
pub const IAkPluginParam = opaque {};
