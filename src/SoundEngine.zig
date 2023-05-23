const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const settings = @import("settings.zig");

pub fn addOutput(output_settings: *const settings.AkOutputSettings, out_device_id: *?common.AkOutputDeviceID, listeners: []common.AkGameObjectID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_AddOutput(@ptrCast(*const c.WWISEC_AkOutputSettings, output_settings), @ptrCast([*]c.WWISEC_AkOutputDeviceID, out_device_id), listeners.ptr, @truncate(u32, listeners.len)),
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

pub fn init(fallback_allocator: std.mem.Allocator, init_settings: settings.AkInitSettings, platform_init_settings: settings.AkPlatformInitSettings) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var native_init_settings = init_settings.toC(allocator) catch return common.WwiseError.Fail;
    defer allocator.free(native_init_settings.szPluginDLLPath[0..init_settings.plugin_dll_path.len]);

    var native_platform_init_settings = platform_init_settings.toC();

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Init(&native_init_settings, &native_platform_init_settings),
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

pub fn term() void {
    c.WWISEC_AK_SoundEngine_Term();
}
