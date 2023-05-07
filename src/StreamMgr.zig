const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const settings = @import("settings.zig");
const stream_interfaces = @import("IAkStreamMgr.zig");

pub const AkStreamMgrSettings = extern struct {
    dummy: u8 = 0,

    pub fn fromC(_: c.WWISEC_AkStreamMgrSettings) AkStreamMgrSettings {
        return .{};
    }

    pub fn toC(_: AkStreamMgrSettings) c.WWISEC_AkStreamMgrSettings {
        return std.mem.zeroes(c.WWISEC_AkStreamMgrSettings);
    }
};

pub const AkDeviceSettings = struct {
    io_memory: ?*anyopaque,
    io_memory_size: u32,
    io_memory_alignment: u32,
    pool_attributes: u32,
    granularity: u32,
    scheduler_type_flags: u32,
    thread_properties: settings.AkThreadProperties,
    target_auto_stm_buffer_length: f32,
    max_concurrent_io: u32,
    use_stream_cache: bool,
    max_cache_pinned_bytes: u32,

    pub fn fromC(device_settings: c.WWISEC_AkDeviceSettings) AkDeviceSettings {
        return .{
            .io_memory = device_settings.pIOMemory,
            .io_memory_size = device_settings.uIOMemorySize,
            .io_memory_alignment = device_settings.uIOMemoryAlignment,
            .pool_attributes = device_settings.ePoolAttributes,
            .granularity = device_settings.uGranularity,
            .scheduler_type_flags = device_settings.uSchedulerTypeFlags,
            .thread_properties = settings.AkThreadProperties.fromC(device_settings.threadProperties),
            .target_auto_stm_buffer_length = device_settings.fTargetAutoStmBufferLength,
            .max_concurrent_io = device_settings.uMaxConcurrentIO,
            .use_stream_cache = device_settings.bUseStreamCache,
            .max_cache_pinned_bytes = device_settings.uMaxCachePinnedBytes,
        };
    }

    pub fn toC(self: AkDeviceSettings) c.WWISEC_AkDeviceSettings {
        return .{
            .pIOMemory = self.io_memory,
            .uIOMemorySize = self.io_memory_size,
            .uIOMemoryAlignment = self.io_memory_alignment,
            .ePoolAttributes = self.pool_attributes,
            .uGranularity = self.granularity,
            .uSchedulerTypeFlags = self.scheduler_type_flags,
            .threadProperties = self.thread_properties.toC(),
            .fTargetAutoStmBufferLength = self.target_auto_stm_buffer_length,
            .uMaxConcurrentIO = self.max_concurrent_io,
            .bUseStreamCache = self.use_stream_cache,
            .uMaxCachePinnedBytes = self.max_cache_pinned_bytes,
        };
    }
};

pub fn create(in_settings: *AkStreamMgrSettings) ?*stream_interfaces.IAkStreamMgr {
    return @ptrCast(?*stream_interfaces.IAkStreamMgr, @alignCast(
        @alignOf(?*stream_interfaces.IAkStreamMgr),
        c.WWISEC_AK_StreamMgr_Create(@ptrCast([*c]c.WWISEC_AkStreamMgrSettings, in_settings)),
    ));
}

pub fn getDefaultSettings(out_settings: *AkStreamMgrSettings) void {
    var temp_raw_settings: c.WWISEC_AkStreamMgrSettings = undefined;
    c.WWISEC_AK_StreamMgr_GetDefaultSettings(&temp_raw_settings);

    out_settings.* = AkStreamMgrSettings.fromC(temp_raw_settings);
}

pub fn getDefaultDeviceSettings(out_settings: *AkDeviceSettings) void {
    var temp_raw_settings: c.WWISEC_AkDeviceSettings = undefined;
    c.WWISEC_AK_StreamMgr_GetDefaultDeviceSettings(&temp_raw_settings);

    out_settings.* = AkDeviceSettings.fromC(temp_raw_settings);
}
