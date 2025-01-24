const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");

pub const Stats = struct {
    recent_peak_mem_used: u32 = 0,
    recent_blocks_fetched: u32 = 0,
    mem_allocated: u32 = 0,
    blocks_allocated: u32 = 0,

    peak_mem_used: u32 = 0,
    peak_mem_allocated: u32 = 0,
    peak_blocks_fetched: u32 = 0,
    peak_blocks_allocated: u32 = 0,
    peak_block_size: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_AK_BookmarkAlloc_Stats) Stats {
        return @bitCast(value);
    }

    pub inline fn toC(self: Stats) c.WWISEC_AK_BookmarkAlloc_Stats {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(Stats) == @sizeOf(c.WWISEC_AK_BookmarkAlloc_Stats));
    }
};

pub const InitSettings = extern struct {
    minimum_block_count: u32 = 0,
    minimum_block_size: u32 = 0,
    maximum_unused_blocks: u32 = 0,

    debug_detailed_stats: bool = false,
    debug_clear_memory: bool = false,
    debug_enable_sentinels: bool = false,
    debug_standalone_allocs: bool = false,

    pub inline fn fromC(value: c.WWISEC_AK_BookmarkAlloc_InitSettings) InitSettings {
        return @bitCast(value);
    }

    pub inline fn toC(self: InitSettings) c.WWISEC_AK_BookmarkAlloc_InitSettings {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(InitSettings) == @sizeOf(c.WWISEC_AK_BookmarkAlloc_InitSettings));
    }
};

pub fn GetStats(out_stats: *Stats) void {
    return c.WWISEC_AK_BookmarkAlloc_GetStats(@ptrCast(out_stats));
}
