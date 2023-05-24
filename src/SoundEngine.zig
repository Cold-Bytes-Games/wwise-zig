const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const common_defs = @import("common_defs.zig");
const callback = @import("callback.zig");
const settings = @import("settings.zig");
const speaker_config = @import("speaker_config.zig");
const IAkPlugin = @import("IAkPlugin.zig");

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

    var raw_in_dll_name = common.toOSChar(allocator, in_dll_name) catch return common.WwiseError.Fail;

    var raw_in_dll_path = blk: {
        if (in_dll_path_opt) |in_dll_path| {
            break :blk common.toOSChar(allocator, in_dll_path) catch return common.WwiseError.Fail;
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
