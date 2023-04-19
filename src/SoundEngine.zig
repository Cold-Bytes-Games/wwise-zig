const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const settings = @import("settings.zig");

pub fn addOutput(output_settings: settings.AkOutputSettings, out_device_id: *?common.AkOutputDeviceID, listeners: []common.AkGameObjectID) common.WwiseError!void {
    var raw_settings = output_settings.toC();

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_AddOutput(&raw_settings, @ptrCast([*]c.WWISEC_AkOutputDeviceID, out_device_id), listeners.ptr, @truncate(u32, listeners.len)),
    );
}

pub fn removeOutput(id_output: common.AkOutputDeviceID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_RemoveOutput(id_output),
    );
}

pub fn replaceOutput(output_settings: settings.AkOutputSettings, in_device_id: common.AkOutputDeviceID, out_device_id: *?common.AkOutputDeviceID) common.WwiseError!void {
    var raw_settings = output_settings.toC();

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_ReplaceOutput(&raw_settings, in_device_id, @ptrCast([*]c.WWISEC_AkOutputDeviceID, out_device_id)),
    );
}

pub fn getDefaultInitSettings(allocator: std.mem.Allocator, init_settings: *settings.AkInitSettings) !void {
    var native_settings: c.WWISEC_AkInitSettings = undefined;
    c.WWISEC_AK_SoundEngine_GetDefaultInitSettings(&native_settings);

    init_settings.* = try settings.AkInitSettings.fromC(allocator, native_settings);
}