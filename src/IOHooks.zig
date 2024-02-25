const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const wwise_options = @import("wwise_options");
const StreamMgr = @import("StreamMgr.zig");

pub const CAkDefaultIOHookDeferred = if (wwise_options.include_default_io_hook_deferred) opaque {
    const Alignment = @alignOf(*CAkDefaultIOHookDeferred);

    pub fn create(allocator: std.mem.Allocator) !*CAkDefaultIOHookDeferred {
        const instance_size_of = c.WWISEC_AK_CAkDefaultIOHookDeferred_Sizeof();
        const buffer = try allocator.alignedAlloc(u8, Alignment, instance_size_of);
        return @ptrCast(c.WWISEC_AK_CAkDefaultIOHookDeferred_Create(@ptrCast(buffer[0..instance_size_of])));
    }

    pub fn destroy(self: *CAkDefaultIOHookDeferred, allocator: std.mem.Allocator) void {
        c.WWISEC_AK_CAkDefaultIOHookDeferred_Destroy(self);

        const instance_size_of = c.WWISEC_AK_CAkDefaultIOHookDeferred_Sizeof();
        const buffer: [*]align(Alignment) u8 = @ptrCast(@alignCast(self));
        allocator.free(buffer[0..instance_size_of]);
    }

    pub inline fn init(self: *CAkDefaultIOHookDeferred, in_device_settings: *const StreamMgr.AkDeviceSettings) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_CAkDefaultIOHookDeferred_Init(self, @ptrCast(in_device_settings)),
        );
    }

    pub inline fn term(self: *CAkDefaultIOHookDeferred) void {
        c.WWISEC_AK_CAkDefaultIOHookDeferred_Term(self);
    }

    pub fn setBasePath(self: *CAkDefaultIOHookDeferred, fallback_allocator: std.mem.Allocator, base_path: []const u8) common.WwiseError!void {
        var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_oschar_allocator.get();

        const raw_base_path = common.toOSChar(allocator, base_path) catch return common.WwiseError.Fail;
        defer allocator.free(raw_base_path);

        return common.handleAkResult(
            c.WWISEC_AK_CAkDefaultIOHookDeferred_SetBasePath(self, raw_base_path),
        );
    }

    pub fn addBasePath(self: *CAkDefaultIOHookDeferred, fallback_allocator: std.mem.Allocator, base_path: []const u8) common.WwiseError!void {
        var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_oschar_allocator.get();

        const raw_base_path = common.toOSChar(allocator, base_path) catch return common.WwiseError.Fail;
        defer allocator.free(raw_base_path);

        return common.handleAkResult(
            c.WWISEC_AK_CAkDefaultIOHookDeferred_AddBasePath(self, raw_base_path),
        );
    }

    pub inline fn setUseSubfoldering(self: *CAkDefaultIOHookDeferred, use_sub_foldering: bool) void {
        c.WWISEC_CAkDefaultIOHookDeferred_SetUseSubfoldering(self, use_sub_foldering);
    }
} else void;

pub const CAkFilePackageLowLevelIODeferred = if (wwise_options.include_file_package_io_deferred) opaque {
    const Alignment = @alignOf(*CAkFilePackageLowLevelIODeferred);

    pub fn create(allocator: std.mem.Allocator) !*CAkFilePackageLowLevelIODeferred {
        const instance_size_of = c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_Sizeof();
        const buffer = try allocator.alignedAlloc(u8, Alignment, instance_size_of);
        return @ptrCast(c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_Create(@ptrCast(buffer[0..instance_size_of])));
    }

    pub fn destroy(self: *CAkFilePackageLowLevelIODeferred, allocator: std.mem.Allocator) void {
        c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_Destroy(self);

        const instance_size_of = c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_Sizeof();
        const buffer: [*]align(Alignment) u8 = @ptrCast(@alignCast(self));
        allocator.free(buffer[0..instance_size_of]);
    }

    pub inline fn init(self: *CAkFilePackageLowLevelIODeferred, in_device_settings: *const StreamMgr.AkDeviceSettings) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_Init(self, @ptrCast(in_device_settings)),
        );
    }

    pub inline fn term(self: *CAkFilePackageLowLevelIODeferred) void {
        c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_Term(self);
    }

    pub fn setBasePath(self: *CAkFilePackageLowLevelIODeferred, fallback_allocator: std.mem.Allocator, base_path: []const u8) common.WwiseError!void {
        var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_oschar_allocator.get();

        const raw_base_path = common.toOSChar(allocator, base_path) catch return common.WwiseError.Fail;
        defer allocator.free(raw_base_path);

        return common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_SetBasePath(self, raw_base_path),
        );
    }

    pub fn addBasePath(self: *CAkFilePackageLowLevelIODeferred, fallback_allocator: std.mem.Allocator, base_path: []const u8) common.WwiseError!void {
        var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_oschar_allocator.get();

        const raw_base_path = common.toOSChar(allocator, base_path) catch return common.WwiseError.Fail;
        defer allocator.free(raw_base_path);

        return common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_AddBasePath(self, raw_base_path),
        );
    }

    pub inline fn setUseSubfoldering(self: *CAkFilePackageLowLevelIODeferred, use_sub_foldering: bool) void {
        c.WWISEC_CAkFilePackageLowLevelIODeferred_SetUseSubfoldering(self, use_sub_foldering);
    }

    pub fn loadFilePackage(self: *CAkFilePackageLowLevelIODeferred, falllback_allocator: std.mem.Allocator, file_package_name: []const u8) common.WwiseError!u32 {
        var result: u32 = undefined;

        var stack_oschar_allocator = common.stackCharAllocator(falllback_allocator);
        var allocator = stack_oschar_allocator.get();

        const raw_file_package_name = common.toOSChar(allocator, file_package_name) catch return common.WwiseError.Fail;
        defer allocator.free(raw_file_package_name);

        try common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_LoadFilePackage(self, raw_file_package_name, &result),
        );

        return result;
    }

    pub inline fn unloadFilePackage(self: *CAkFilePackageLowLevelIODeferred, package_id: u32) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_UnloadFilePackage(self, package_id),
        );
    }

    pub inline fn unloadAllFilePackages(self: *CAkFilePackageLowLevelIODeferred) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_UnloadAllFilePackages(self),
        );
    }

    pub inline fn setPackageFallbackBehavior(self: *CAkFilePackageLowLevelIODeferred, fallback: bool) void {
        c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_SetPackageFallbackBehavior(self, fallback);
    }
} else void;
