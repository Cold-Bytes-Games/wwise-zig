const c = @import("wwise_c");
const std = @import("std");
const zig = @import("zig.zig");

pub const Stats = extern struct {
    mem_used: u32 = 0,
    mem_allocated: u32 = 0,
    blocks_used: u32 = 0,

    peak_mem_used: u32 = 0,
    peak_mem_allocated: u32 = 0,
    peak_blocks_used: u32 = 0,
    peak_block_used: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_AK_TempAlloc_Stats) Stats {
        return @bitCast(value);
    }

    pub inline fn toC(self: Stats) c.WWISEC_AK_TempAlloc_Stats {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(Stats) == @sizeOf(c.WWISEC_AK_TempAlloc_Stats));
    }
};

pub const Type = enum(zig.DefaultEnumType) {
    audio_render = c.WWISEC_AK_TempAlloc_Type_AudioRender,
};

pub const InitSettings = extern struct {
    minimum_block_count: u32 = 0,
    minimum_block_size: u32 = 0,
    maximum_unused_blocks: u32 = 0,
    debug_detailed_stats: bool = false,
    debug_clear_memory: bool = false,
    debug_enable_sentinels: bool = false,
    debug_flush_blocks: bool = false,
    debug_standalone_allocs: bool = false,

    pub inline fn fromC(value: c.WWISEC_AK_TempAlloc_InitSettings) InitSettings {
        return @bitCast(value);
    }

    pub inline fn toC(self: InitSettings) c.WWISEC_AK_TempAlloc_InitSettings {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(InitSettings) == @sizeOf(c.WWISEC_AK_TempAlloc_InitSettings));
    }
};

pub fn getStats(in_type: Type) Stats {
    var result: Stats = .{};
    c.WWISEC_AK_TempAlloc_GetStats(@intFromEnum(in_type), @ptrCast(&result));
    return result;
}

pub fn dumpTempAllocsToFile(fallback_allocator: std.mem.Allocator, in_type: Type, filename: []const u8) !void {
    var stack_oschar_allocator = zig.stackCharAllocator(fallback_allocator);
    const allocator = stack_oschar_allocator.get();

    const raw_filename = try zig.toOSChar(allocator, filename);
    defer allocator.free(raw_filename);

    c.WWISEC_AK_TempAlloc_DumpTempAllocsToFile(@intFromEnum(in_type), raw_filename);
}
