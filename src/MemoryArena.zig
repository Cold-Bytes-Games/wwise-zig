const std = @import("std");
const c = @import("wwise_c");
const common = @import("common.zig");

pub const AkAllocSpan = ?*const fn (in_size: usize, out_userData: *usize) ?*anyopaque;
pub const AkFreeSpan = ?*const fn (in_address: ?*anyopaque, in_size: usize, in_user_data: usize) void;

pub const AkMemoryArenaSettings = extern struct {
    enable_sba: bool = false,
    sba_init_size: u32 = 0,
    sba_span_size: u32 = 0,
    sba_maximum_unused_spans: u32 = 0,

    tlsf_init_size: u32 = 0,
    tlsf_span_size: u32 = 0,
    tlsf_large_span_size: u32 = 0,
    tlsf_span_overhead: u32 = 0,
    tlsf_maximum_unused_medium_spans: u32 = 0,
    tlsf_maximum_unused_large_spans: u32 = 0,

    alloc_size_large: u32 = 0,
    alloc_size_huge: u32 = 0,

    mem_reserved_limit: u32 = 0,

    mem_alloc_span: AkAllocSpan = null,
    mem_free_span: AkFreeSpan = null,

    pub inline fn fromC(value: c.WWISEC_AK_MemoryArea_AkMemoryArenaSettings) AkMemoryArenaSettings {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMemoryArenaSettings) c.WWISEC_AK_MemoryArea_AkMemoryArenaSettings {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkMemoryArenaSettings) == @sizeOf(c.WWISEC_AK_MemoryArea_AkMemoryArenaSettings));
    }
};
