const std = @import("std");
const c = @import("c.zig");
const callbacks = @import("callbacks.zig");
const common = @import("common.zig");
const IAkPluginMemAlloc = @import("IAkPluginMemAlloc.zig").IAkPluginMemAlloc;
const IAkStreamMgr = @import("IAkStreamMgr.zig");
const Monitor = @import("Monitor.zig");
const SpeakerVolumes = @import("SpeakerVolumes.zig");
const settings = @import("settings.zig");
const speaker_config = @import("speaker_config.zig");
const virtual_acoustics = @import("virtual_acoustics.zig");

pub const AkCreatePluginCallback = ?*const fn (in_allocator: ?*IAkPluginMemAlloc) callconv(.C) ?*IAkPlugin;
pub const AkCreateParamCallback = ?*const fn (in_allocator: ?*IAkPluginMemAlloc) callconv(.C) ?*IAkPluginParam;
pub const AkGetDeviceListCallback = ?*const fn (io_max_num_devices: *u32, out_device_description: ?[*]c.WWISEC_AkDeviceDescription) callconv(.C) common.AKRESULT;

pub const IAkPluginService = opaque {};

pub const IAkMixerInputContext = opaque {};
pub const IAkMixerPluginContext = opaque {};

pub const IAkGlobalPluginContext = opaque {
    pub fn getStreamMgr(self: *const IAkGlobalPluginContext) *IAkStreamMgr.IAkStreamMgr {
        return @ptrCast(
            c.WWISEC_AK_IAkGlobalPluginContext_GetStreamMgr(self),
        );
    }

    pub fn getMaxBufferLength(self: *const IAkGlobalPluginContext) u16 {
        return c.WWISEC_AK_IAkGlobalPluginContext_GetMaxBufferLength(self);
    }

    pub fn isRenderingOffline(self: *const IAkGlobalPluginContext) bool {
        return c.WWISEC_AK_IAkGlobalPluginContext_IsRenderingOffline(self);
    }

    pub fn getSampleRate(self: *const IAkGlobalPluginContext) u32 {
        return c.WWISEC_AK_IAkGlobalPluginContext_GetSampleRate(self);
    }

    pub fn postMonitorMessage(self: *IAkGlobalPluginContext, fallback_allocator: std.mem.Allocator, in_error: []const u8, in_error_level: Monitor.ErrorLevel) common.WwiseError!void {
        var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_char_allocator.get();

        const raw_error = common.toCString(allocator, in_error);
        defer allocator.free(raw_error);

        return common.handleAkResult(
            c.WWISEC_AK_IAkGlobalPluginContext_PostMonitorMessage(
                self,
                raw_error,
                in_error_level.toC(),
            ),
        );
    }

    pub fn registerPlugin(self: *IAkGlobalPluginContext, in_type: common.AkPluginType, in_company_id: u32, in_plugin_id: u32, in_create_func: AkCreatePluginCallback, in_create_param_func: AkCreateParamCallback) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkGlobalPluginContext_RegisterPlugin(
                self,
                @intFromEnum(in_type),
                in_company_id,
                in_plugin_id,
                @ptrCast(in_create_func),
                @ptrCast(in_create_param_func),
            ),
        );
    }

    pub fn registerCodec(self: *IAkGlobalPluginContext, in_company_id: u32, in_plugin_id: u32, in_file_create_func: common.AkCreateFileSourceCallback, in_bank_create_func: common.AkCreateBankSourceCallback) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkGlobalPluginContext_RegisterCodec(
                self,
                in_company_id,
                in_plugin_id,
                @ptrCast(in_file_create_func),
                @ptrCast(in_bank_create_func),
            ),
        );
    }

    pub const RegisterGlobalCallbackOptionalArgs = struct {
        location: callbacks.AkGlobalCallbackLocation = .{ .begin_render = true },
        cookie: ?*anyopaque = null,
    };

    pub fn registerGlobalCallback(self: *IAkGlobalPluginContext, in_type: common.AkPluginType, in_company_id: u32, in_plugin_id: u32, in_callback: callbacks.AkGlobalCallbackFunc, optional_args: RegisterGlobalCallbackOptionalArgs) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkGlobalPluginContext_RegisterGlobalCallback(
                self,
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
        location: callbacks.AkGlobalCallbackLocation = .{ .begin_render = true },
    };

    pub fn unregisterGlobalCallback(
        self: *IAkGlobalPluginContext,
        in_callback: callbacks.AkGlobalCallbackFunc,
        optional_args: UnregisterGlobalCallbackOptionArgs,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkGlobalPluginContext_UnregisterGlobalCallback(
                self,
                in_callback,
                optional_args.locaition.toC(),
            ),
        );
    }

    pub fn getAllocator(self: *IAkGlobalPluginContext) ?*IAkPluginMemAlloc {
        return c.WWISEC_AK_IAkGlobalPluginContext_GetAllocator(self);
    }

    pub const SetRtpcValueOptionalArgs = struct {
        game_object_id: common.AkGameObjectID = common.AK_INVALID_GAME_OBJECT,
        value_change_duration: common.AkTimeMs = 0,
        fade_curve: common.AkCurveInterpolation = .linear,
        bypass_internal_value_interpolation: bool = false,
    };

    pub fn setRTPCValue(
        self: *IAkGlobalPluginContext,
        in_rtpcID: common.AkRtpcID,
        in_value: common.AkRtpcValue,
        optional_args: SetRtpcValueOptionalArgs,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkGlobalPluginContext_SetRTPCValue(
                self,
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
        in_bus_id: common.AkUniqueID,
        in_bus_object_id: common.AkGameObjectID,
        in_type: common.AkPluginType,
        in_company_id: u32,
        in_plugin_id: u32,
        in_data: ?*const anyopaque,
        in_size_in_bytes: u32,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkGlobalPluginContext_SendPluginCustomGameData(
                self,
                in_bus_id,
                in_bus_object_id,
                in_type,
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
            self,
            in_azimuth,
            in_elevation,
            in_cfg_ambisonics,
            out_volumes,
        );
    }

    pub fn computeWeightedAmbisonicsDecodingFromSampledSphere(
        self: *IAkGlobalPluginContext,
        in_samples: []const common.AkVector,
        in_cfg_ambisonics: speaker_config.AkChannelConfig,
        out_mx_volume: SpeakerVolumes.MatrixPtr,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkGlobalPluginContext_ComputeWeightedAmbisonicsDecodingFromSampledSphere(
                self,
                @ptrCast(in_samples),
                @truncate(in_samples.len),
                in_cfg_ambisonics.toC(),
                out_mx_volume,
            ),
        );
    }

    pub fn getAcousticTexture(self: *IAkGlobalPluginContext, in_acoustic_texture_id: common.AkAcousticTextureID) ?*const virtual_acoustics.AkAcousticTexture {
        return virtual_acoustics.AkAcousticTexture.fromC(
            c.WWISEC_AK_IAkGlobalPluginContext_GetAcousticTexture(self, in_acoustic_texture_id),
        );
    }

    pub fn computeSphericalCoordinates(
        self: *const IAkGlobalPluginContext,
        in_pair: *const common.AkEmitterListenerPair,
         out_azimuth: *f32,
        out_elevation: *f32,
    ) common.WwiseError!void {
        return common.handleAkResult(
          c. WWISEC_AK_IAkGlobalPluginContext_ComputeSphericalCoordinates(
            self,
            @ptrCast(in_pair),
            out_azimuth,
            out_elevation,
          ),
        );
    }
};

pub const IAkPlugin = opaque {};
pub const IAkPluginParam = opaque {};
