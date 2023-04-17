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
