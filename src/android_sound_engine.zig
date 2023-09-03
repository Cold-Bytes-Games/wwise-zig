const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const settings = @import("settings.zig");

pub const SLObjectItf = ?*anyopaque;

pub fn getWwiseOpenSLInterface() SLObjectItf {
    return c.WWISEC_AK_SoundEngine_GetWwiseOpenSLInterface();
}

pub fn getFastPathSettings(allocator: std.mem.Allocator, in_settings: *settings.AkInitSettings, in_platform_settings: *settings.AkPlatformInitSettings) common.WwiseError!void {
    var area_allocator = std.heap.ArenaAllocator.init(allocator);
    defer area_allocator.deinit();

    var raw_init_settings = in_settings.toC(area_allocator.allocator()) catch return common.WwiseError.Fail;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_GetFastPathSettings(
            &raw_init_settings,
            @ptrCast(in_platform_settings),
        ),
    );

    in_settings.* = settings.AkInitSettings.fromC(allocator, raw_init_settings);
}
