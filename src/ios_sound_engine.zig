const c = @import("wwise_c");
const settings = @import("settings.zig");
const std = @import("std");

pub fn changeAudioSessionProperties(in_properties: *const settings.IOS_AkAudioSessionProperties) void {
    c.WWISEC_AK_SoundEngine_iOS_ChangeAudioSessionProperties(@ptrCast(in_properties));
}
