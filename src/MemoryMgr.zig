const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");

pub const AkMemSettings = c.WWISEC_AkMemSettings;
pub const AkMemPoolId = c.WWISEC_AkMemPoolId;
pub const CategoryStats = c.WWISEC_AK_MemoryMgr_CategoryStats;
pub const GlobalStats = c.WWISEC_AK_MemoryMgr_GlobalStats;

pub fn init(in_pSettings: *AkMemSettings) common.WwiseError!void {
    return common.handleAkResult(c.WWISEC_AK_MemoryMgr_Init(@ptrCast([*c]AkMemSettings, in_pSettings)));
}

pub fn term() void {
    c.WWISEC_AK_MemoryMgr_Term();
}

pub fn getDefaultSettings(out_pMemSettings: *AkMemSettings) void {
    c.WWISEC_AK_MemoryMgr_GetDefaultSettings(out_pMemSettings);
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

pub fn malloc(in_poolId: AkMemPoolId, in_uSize: usize) *anyopaque {
    return c.WWISEC_AK_MemoryMgr_Malloc(in_poolId, in_uSize);
}

pub fn reallocAligned(in_poolId: AkMemPoolId, in_pAlloc: *anyopaque, in_uSize: usize, in_uAlignment: u32) *anyopaque {
    return c.WWISEC_AK_MemoryMgr_ReallocAligned(in_poolId, in_pAlloc, in_uSize, in_uAlignment);
}

pub fn free(in_poolId: AkMemPoolId, in_pMemAddress: *anyopaque) void {
    c.WWISEC_AK_MemoryMgr_Free(in_poolId, in_pMemAddress);
}

pub fn malign(in_poolId: AkMemPoolId, in_USize: usize, in_uAlignment: u32) *anyopaque {
    return c.WWISEC_AK_MemoryMgr_Malign(in_poolId, in_USize, in_uAlignment);
}

pub fn getCategoryStats(in_poolId: AkMemPoolId) CategoryStats {
    var result: CategoryStats = undefined;
    c.WWISEC_AK_MemoryMgr_GetCategoryStats(in_poolId, &result);
    return result;
}

pub fn getGlobalStats() GlobalStats {
    var result: GlobalStats = undefined;
    c.WWISEC_AK_MemoryMgr_GetGlobalStats(&result);
    return result;
}

pub fn startProfileThreadUsage() void {
    c.WWISEC_AK_MemoryMgr_StartProfileThreadUsage();
}

pub fn stopProfileThreadUsage() u64 {
    return c.WWISEC_AK_MemoryMgr_StopProfileThreadUsage();
}

pub fn dumpToFile(allocator: std.mem.Allocator, filename: []const u8) !void {
    var os_string_allocator_instance = common.osCharAllocator(allocator);
    var os_string_allocator = os_string_allocator_instance.get();

    const filename_oschar = try common.toOSChar(os_string_allocator, filename);
    defer os_string_allocator.free(filename_oschar);

    c.WWISEC_AK_MemoryMgr_DumpToFile(filename_oschar);
}
