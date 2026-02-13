const BookmarkAlloc = @import("BookmarkAlloc.zig");
const c = @import("wwise_c");
const MemoryArena = @import("MemoryArena.zig");
const std = @import("std");
const TempAlloc = @import("TempAlloc.zig");
const zig = @import("zig.zig");

pub const AkMemPoolId = c.WWISEC_AkMemPoolId;

pub const AkMemID = enum(zig.DefaultEnumType) {
    object = c.WWISEC_AkMemID_Object,
    event = c.WWISEC_AkMemID_Event,
    structure = c.WWISEC_AkMemID_Structure,
    media = c.WWISEC_AkMemID_Media,
    game_object = c.WWISEC_AkMemID_GameObject,
    processing = c.WWISEC_AkMemID_Processing,
    processing_plugin = c.WWISEC_AkMemID_ProcessingPlugin,
    streaming = c.WWISEC_AkMemID_Streaming,
    streaming_io = c.WWISEC_AkMemID_StreamingIO,
    spatial_audio = c.WWISEC_AkMemID_SpatialAudio,
    spatial_audio_geometry = c.WWISEC_AkMemID_SpatialAudioGeometry,
    spatial_audio_paths = c.WWISEC_AkMemID_SpatialAudioPaths,
    game_sim = c.WWISEC_AkMemID_GameSim,
    monitor_queue = c.WWISEC_AkMemID_MonitorQueue,
    profiler = c.WWISEC_AkMemID_Profiler,
    file_package = c.WWISEC_AkMemID_FilePackage,
    sound_engine = c.WWISEC_AkMemID_SoundEngine,
    integration = c.WWISEC_AkMemID_Integration,
    job_mgr = c.WWISEC_AkMemID_JobMgr,
    temp_audio_render = c.WWISEC_AkMemID_TempAudioRender,
    bookmark_alloc = c.WWISEC_AkMemID_BookmarkAlloc,
};

pub const AkMemType_Media = c.WWISEC_AkMemType_Media;
pub const AkMemType_Device = c.WWISEC_AkMemType_Device;
pub const AkMemType_NoTrack = c.WWISEC_AkMemType_NoTrack;

pub const CategoryStats = extern struct {
    used: u64 = 0,
    peak_used: u64 = 0,
    allocs: u32 = 0,
    frees: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_AK_MemoryMgr_CategoryStats) CategoryStats {
        return @bitCast(value);
    }

    pub inline fn toC(self: CategoryStats) c.WWISEC_AK_MemoryMgr_CategoryStats {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(CategoryStats) == @sizeOf(c.WWISEC_AK_MemoryMgr_CategoryStats));
    }
};

pub const GlobalStats = extern struct {
    used: u64 = 0,
    reserved: u64 = 0,

    pub inline fn fromC(value: c.WWISEC_AK_MemoryMgr_GlobalStats) GlobalStats {
        return @bitCast(value);
    }

    pub inline fn toC(self: GlobalStats) c.WWISEC_AK_MemoryMgr_GlobalStats {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(GlobalStats) == @sizeOf(c.WWISEC_AK_MemoryMgr_GlobalStats));
    }
};

// BEGIN MemoryMgrModule
pub const AkMemInitForThread = ?*const fn () callconv(.c) void;
pub const AkMemTermForThread = ?*const fn () callconv(.c) void;
pub const AkMemTrimForThread = ?*const fn () callconv(.c) void;
pub const AkMemMalloc = ?*const fn (pool_id: AkMemPoolId, size: usize) callconv(.c) ?*anyopaque;
pub const AkMemMalign = ?*const fn (pool_id: AkMemPoolId, size: usize, alignment: u32) callconv(.c) ?*anyopaque;
pub const AkMemRealloc = ?*const fn (pool_id: AkMemPoolId, address: ?*anyopaque, size: usize) callconv(.c) ?*anyopaque;
pub const AkMemReallocAligned = ?*const fn (pool_id: AkMemPoolId, address: ?*anyopaque, size: usize, alignment: u32) callconv(.c) ?*anyopaque;
pub const AkMemFree = ?*const fn (pool_id: AkMemPoolId, address: ?*anyopaque) callconv(.c) void;
pub const AkMemTotalReservedMemorySize = ?*const fn () callconv(.c) usize;
pub const AkMemSizeOfMemory = ?*const fn (pool_id: AkMemPoolId, address: ?*anyopaque) callconv(.c) usize;
pub const AkMemDebugMalloc = ?*const fn (pool_id: AkMemPoolId, size: usize, address: ?*anyopaque, file: ?[*:0]const u8, line: u32) callconv(.c) void;
pub const AkMemDebugMalign = ?*const fn (pool_id: AkMemPoolId, size: usize, alignment: u32, address: ?*anyopaque, file: ?[*:0]const u8, line: u32) callconv(.c) void;
pub const AkMemDebugRealloc = ?*const fn (pool_id: AkMemPoolId, old_address: ?*anyopaque, size: usize, new_addresss: ?*anyopaque, file: ?[*:0]const u8, line: u32) callconv(.c) void;
pub const AkMemDebugReallocAligned = ?*const fn (pool_id: AkMemPoolId, old_address: ?*anyopaque, size: usize, alignment: u32, new_address: ?*anyopaque, file: ?[*:0]const u8, line: u32) callconv(.c) void;
pub const AkMemDebugFree = ?*const fn (pool_id: AkMemPoolId, address: ?*anyopaque) callconv(.c) void;

pub const AkMemoryMgrArena = enum(zig.DefaultEnumType) {
    primary = 0,
    media,
    profiler,
    device,
};

pub const AkMemSettings = extern struct {
    init_for_thread: AkMemInitForThread = null,
    term_for_thread: AkMemTermForThread = null,
    trim_for_thread: AkMemTrimForThread = null,
    malloc: AkMemMalloc = null,
    malign: AkMemMalign = null,
    realloc: AkMemRealloc = null,
    realloc_aligned: AkMemReallocAligned = null,
    free: AkMemFree = null,
    total_reserved_memory_size: AkMemTotalReservedMemorySize = null,
    size_of_memory: AkMemSizeOfMemory = null,

    memory_arena_settiongs: [std.meta.fields(AkMemoryMgrArena).len]MemoryArena.AkMemoryArenaSettings = @splat(.{}),
    temp_alloc_settings: [std.meta.fields(TempAlloc.Type).len]TempAlloc.InitSettings = @splat(.{}),
    bookmark_alloc_settings: BookmarkAlloc.InitSettings = .{},

    debug_malloc: AkMemDebugMalloc = null,
    debug_malign: AkMemDebugMalign = null,
    debug_realloc: AkMemDebugRealloc = null,
    debug_realloc_aligned: AkMemDebugReallocAligned = null,
    debug_free: AkMemDebugFree = null,
    memory_debug_level: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_AkMemSettings) AkMemSettings {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMemSettings) c.WWISEC_AkMemSettings {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkMemSettings) == @sizeOf(c.WWISEC_AkMemSettings));
    }
};

pub fn init(in_pSettings: *AkMemSettings) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_MemoryMgr_Init(@ptrCast(in_pSettings)),
    );
}

pub fn term() void {
    c.WWISEC_AK_MemoryMgr_Term();
}

pub fn getDefaultSettings(out_pMemSettings: *AkMemSettings) void {
    c.WWISEC_AK_MemoryMgr_GetDefaultSettings(@ptrCast(out_pMemSettings));
}
// END MemoryMgrModule

pub fn isInitialized() bool {
    return c.WWISEC_AK_MemoryMgr_IsInitialized();
}

pub fn initForThread() void {
    c.WWISEC_AK_MemoryMgr_InitForThread();
}

pub fn termForThread() void {
    c.WWISEC_AK_MemoryMgr_TermForThread();
}

pub fn malloc(in_poolId: AkMemPoolId, in_uSize: usize) ?*anyopaque {
    return c.WWISEC_AK_MemoryMgr_Malloc(in_poolId, in_uSize);
}

pub fn reallocAligned(in_poolId: AkMemPoolId, in_pAlloc: ?*anyopaque, in_uSize: usize, in_uAlignment: u32) ?*anyopaque {
    return c.WWISEC_AK_MemoryMgr_ReallocAligned(in_poolId, in_pAlloc, in_uSize, in_uAlignment);
}

pub fn free(in_poolId: AkMemPoolId, in_pMemAddress: ?*anyopaque) void {
    c.WWISEC_AK_MemoryMgr_Free(in_poolId, in_pMemAddress);
}

pub fn malign(in_poolId: AkMemPoolId, in_USize: usize, in_uAlignment: u32) ?*anyopaque {
    return c.WWISEC_AK_MemoryMgr_Malign(in_poolId, in_USize, in_uAlignment);
}

pub fn getCategoryStats(in_poolId: AkMemPoolId) CategoryStats {
    var result: CategoryStats = undefined;
    c.WWISEC_AK_MemoryMgr_GetCategoryStats(in_poolId, @ptrCast(&result));
    return result;
}

pub fn getGlobalStats() GlobalStats {
    var result: GlobalStats = undefined;
    c.WWISEC_AK_MemoryMgr_GetGlobalStats(@ptrCast(&result));
    return result;
}

pub fn startProfileThreadUsage() void {
    c.WWISEC_AK_MemoryMgr_StartProfileThreadUsage();
}

pub fn stopProfileThreadUsage() u64 {
    return c.WWISEC_AK_MemoryMgr_StopProfileThreadUsage();
}

pub fn dumpToFile(fallback_allocator: std.mem.Allocator, filename: []const u8) !void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const filename_oschar = try common.toOSChar(allocator, filename);
    defer allocator.free(filename_oschar);

    c.WWISEC_AK_MemoryMgr_DumpToFile(filename_oschar);
}
