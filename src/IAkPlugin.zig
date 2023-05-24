const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");

pub const IAkMixerInputContext = extern struct {};
pub const IAkMixerPluginContext = extern struct {};
pub const IAkGlobalPluginContext = extern struct {};
pub const IAkPlugin = extern struct {};
pub const IAkPluginParam = extern struct {};
pub const IAkPluginMemAlloc = extern struct {};

pub const AkCreatePluginCallback = ?*const fn (in_allocator: ?*IAkPluginMemAlloc) callconv(.C) ?*IAkPlugin;
pub const AkCreateParamCallback = ?*const fn (in_allocator: ?*IAkPluginMemAlloc) callconv(.C) ?*IAkPluginParam;
pub const AkGetDeviceListCallback = ?*const fn (io_max_num_devices: *u32, out_device_description: ?[*]c.WWISEC_AkDeviceDescription) callconv(.C) common.AKRESULT;
