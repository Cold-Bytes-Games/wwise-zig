const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");

pub const AkMemPoolId = c.WWISEC_AkMemPoolId;

pub const AkMemID = enum(common.DefaultEnumType) {
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
};

pub const AkMemType_Media = c.WWISEC_AkMemType_Media;
pub const AkMemType_Device = c.WWISEC_AkMemType_Device;
pub const AkMemType_NoTrack = c.WWISEC_AkMemType_NoTrack;

pub const AkMemInitForThread = ?*const fn () callconv(.C) void;
pub const AkMemTermForThread = ?*const fn () callconv(.C) void;
pub const AkMemTrimForThread = ?*const fn () callconv(.C) void;
pub const AkMemMalloc = ?*const fn (pool_id: AkMemPoolId, size: usize) callconv(.C) ?*anyopaque;
pub const AkMemMalign = ?*const fn (pool_id: AkMemPoolId, size: usize, alignment: u32) callconv(.C) ?*anyopaque;
pub const AkMemRealloc = ?*const fn (pool_id: AkMemPoolId, address: ?*anyopaque, size: usize) callconv(.C) ?*anyopaque;
pub const AkMemReallocAligned = ?*const fn (pool_id: AkMemPoolId, address: ?*anyopaque, size: usize, alignment: u32) callconv(.C) ?*anyopaque;
pub const AkMemFree = ?*const fn (pool_id: AkMemPoolId, address: ?*anyopaque) callconv(.C) void;
pub const AkMemTotalReservedMemorySize = ?*const fn () callconv(.C) usize;
pub const AkMemSizeOfMemory = ?*const fn (pool_id: AkMemPoolId, address: ?*anyopaque) callconv(.C) usize;
pub const AkMemDebugMalloc = ?*const fn (pool_id: AkMemPoolId, size: usize, address: ?*anyopaque, file: ?[*:0]const u8, line: u32) callconv(.C) void;
pub const AkMemDebugMalign = ?*const fn (pool_id: AkMemPoolId, size: usize, alignment: u32, address: ?*anyopaque, file: ?[*:0]const u8, line: u32) callconv(.C) void;
pub const AkMemDebugRealloc = ?*const fn (pool_id: AkMemPoolId, old_address: ?*anyopaque, size: usize, new_addresss: ?*anyopaque, file: ?[*:0]const u8, line: u32) callconv(.C) void;
pub const AkMemDebugReallocAligned = ?*const fn (pool_id: AkMemPoolId, old_address: ?*anyopaque, size: usize, alignment: u32, new_address: ?*anyopaque, file: ?[*:0]const u8, line: u32) callconv(.C) void;
pub const AkMemDebugFree = ?*const fn (pool_id: AkMemPoolId, address: ?*anyopaque) callconv(.C) void;
pub const AkMemAllocVM = ?*const fn (size: usize, extra: ?*usize) callconv(.C) ?*anyopaque;
pub const AkMemFreeVM = ?*const fn (address: ?*anyopaque, size: usize, extra: usize, release: usize) callconv(.C) void;

pub const AkMemSettings = extern struct {
    init_for_thread: AkMemInitForThread = null,
    term_for_thread: AkMemTermForThread = null,
    malloc: AkMemMalloc = null,
    malign: AkMemMalign = null,
    realloc: AkMemRealloc = null,
    realloc_aligned: AkMemReallocAligned = null,
    free: AkMemFree = null,
    total_reserved_memory_size: AkMemTotalReservedMemorySize = null,
    size_of_memory: AkMemSizeOfMemory = null,
    mem_allocation_size_limit: u64 = 0,
    use_device_mem_always: bool = false,
    alloc_vm: AkMemAllocVM = null,
    free_vm: AkMemFreeVM = null,
    alloc_device: AkMemAllocVM = null,
    free_device: AkMemFreeVM = null,
    vm_page_size: u32 = 0,
    device_page_size: u32 = 0,
    debug_malloc: AkMemDebugMalloc = null,
    debug_malign: AkMemDebugMalign = null,
    debug_realloc: AkMemDebugRealloc = null,
    debug_realloc_aligned: AkMemDebugReallocAligned = null,
    debug_free: AkMemDebugFree = null,
    memory_debug_level: u32 = 0,
    trim_for_thread: AkMemTrimForThread = null,

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
    device_used: u64 = 0,
    reserved: u64 = 0,
    max: u64 = 0,

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

pub fn init(in_pSettings: *AkMemSettings) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_MemoryMgr_Init(@ptrCast(in_pSettings)),
    );
}

pub fn term() void {
    c.WWISEC_AK_MemoryMgr_Term();
}

pub fn getDefaultSettings(out_pMemSettings: *AkMemSettings) void {
    c.WWISEC_AK_MemoryMgr_GetDefaultSettings(@ptrCast(out_pMemSettings));
}

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
