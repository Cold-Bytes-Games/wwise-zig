const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const settings = @import("settings.zig");

pub fn changeAudioSessionProperties(in_properties: *const settings.IOS_AkAudioSessionProperties) void {
    c.WWISEC_AK_SoundEngine_iOS_ChangeAudioSessionProperties(@ptrCast(in_properties));
}
