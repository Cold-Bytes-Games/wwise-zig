const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const wwise_options = @import("wwise_options");
const StreamMgr = @import("StreamMgr.zig");

pub const CAkDefaultIOHookBlocking = if (wwise_options.include_default_io_hook_blocking) opaque {
    const Alignment = @alignOf(*CAkDefaultIOHookBlocking);

    pub fn create(allocator: std.mem.Allocator) !*CAkDefaultIOHookBlocking {
        const instance_size_of = c.WWISEC_AK_CAkDefaultIOHookBlocking_Sizeof();
        const buffer = try allocator.alignedAlloc(u8, Alignment, instance_size_of);
        return @ptrCast(*CAkDefaultIOHookBlocking, c.WWISEC_AK_CAkDefaultIOHookBlocking_Create(@ptrCast([*]u8, buffer[0..instance_size_of])));
    }

    pub fn destroy(self: *CAkDefaultIOHookBlocking, allocator: std.mem.Allocator) void {
        c.WWISEC_AK_CAkDefaultIOHookBlocking_Destroy(self);

        const instance_size_of = c.WWISEC_AK_CAkDefaultIOHookBlocking_Sizeof();
        const buffer = @ptrCast([*]align(Alignment) u8, @alignCast(Alignment, self));
        allocator.free(buffer[0..instance_size_of]);
    }

    pub inline fn init(self: *CAkDefaultIOHookBlocking, in_device_settings: *const StreamMgr.AkDeviceSettings, in_async_open: bool) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_CAkDefaultIOHookBlocking_Init(self, @ptrCast(*const c.WWISEC_AkDeviceSettings, in_device_settings), in_async_open),
        );
    }

    pub inline fn term(self: *CAkDefaultIOHookBlocking) void {
        c.WWISEC_AK_CAkDefaultIOHookBlocking_Term(self);
    }

    pub fn setBasePath(self: *CAkDefaultIOHookBlocking, fallback_allocator: std.mem.Allocator, base_path: []const u8) common.WwiseError!void {
        var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_oschar_allocator.get();

        var raw_base_path = common.toOSChar(allocator, base_path) catch return common.WwiseError.Fail;
        defer allocator.free(raw_base_path);

        return common.handleAkResult(
            c.WWISEC_AK_CAkDefaultIOHookBlocking_SetBasePath(self, raw_base_path),
        );
    }

    pub fn addBasePath(self: *CAkDefaultIOHookBlocking, fallback_allocator: std.mem.Allocator, base_path: []const u8) common.WwiseError!void {
        var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_oschar_allocator.get();

        var raw_base_path = common.toOSChar(allocator, base_path) catch return common.WwiseError.Fail;
        defer allocator.free(raw_base_path);

        return common.handleAkResult(
            c.WWISEC_AK_CAkDefaultIOHookBlocking_AddBasePath(self, raw_base_path),
        );
    }

    pub inline fn setUseSubfoldering(self: *CAkDefaultIOHookBlocking, use_sub_foldering: bool) void {
        c.WWISEC_CAkDefaultIOHookBlocking_SetUseSubfoldering(self, use_sub_foldering);
    }
} else void;

pub const CAkDefaultIOHookDeferred = if (wwise_options.include_default_io_hook_deferred) opaque {
    const Alignment = @alignOf(*CAkDefaultIOHookDeferred);

    pub fn create(allocator: std.mem.Allocator) !*CAkDefaultIOHookDeferred {
        const instance_size_of = c.WWISEC_AK_CAkDefaultIOHookDeferred_Sizeof();
        const buffer = try allocator.alignedAlloc(u8, Alignment, instance_size_of);
        return @ptrCast(*CAkDefaultIOHookDeferred, c.WWISEC_AK_CAkDefaultIOHookDeferred_Create(@ptrCast([*]u8, buffer[0..instance_size_of])));
    }

    pub fn destroy(self: *CAkDefaultIOHookDeferred, allocator: std.mem.Allocator) void {
        c.WWISEC_AK_CAkDefaultIOHookDeferred_Destroy(self);

        const instance_size_of = c.WWISEC_AK_CAkDefaultIOHookDeferred_Sizeof();
        const buffer = @ptrCast([*]align(Alignment) u8, @alignCast(Alignment, self));
        allocator.free(buffer[0..instance_size_of]);
    }

    pub inline fn init(self: *CAkDefaultIOHookDeferred, in_device_settings: *const StreamMgr.AkDeviceSettings, in_async_open: bool) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_CAkDefaultIOHookDeferred_Init(self, @ptrCast(*const c.WWISEC_AkDeviceSettings, in_device_settings), in_async_open),
        );
    }

    pub inline fn term(self: *CAkDefaultIOHookDeferred) void {
        c.WWISEC_AK_CAkDefaultIOHookDeferred_Term(self);
    }

    pub fn setBasePath(self: *CAkDefaultIOHookDeferred, fallback_allocator: std.mem.Allocator, base_path: []const u8) common.WwiseError!void {
        var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_oschar_allocator.get();

        var raw_base_path = common.toOSChar(allocator, base_path) catch return common.WwiseError.Fail;
        defer allocator.free(raw_base_path);

        return common.handleAkResult(
            c.WWISEC_AK_CAkDefaultIOHookDeferred_SetBasePath(self, raw_base_path),
        );
    }

    pub fn addBasePath(self: *CAkDefaultIOHookDeferred, fallback_allocator: std.mem.Allocator, base_path: []const u8) common.WwiseError!void {
        var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_oschar_allocator.get();

        var raw_base_path = common.toOSChar(allocator, base_path) catch return common.WwiseError.Fail;
        defer allocator.free(raw_base_path);

        return common.handleAkResult(
            c.WWISEC_AK_CAkDefaultIOHookDeferred_AddBasePath(self, raw_base_path),
        );
    }

    pub inline fn setUseSubfoldering(self: *CAkDefaultIOHookDeferred, use_sub_foldering: bool) void {
        c.WWISEC_CAkDefaultIOHookDeferred_SetUseSubfoldering(self, use_sub_foldering);
    }
} else void;

pub const CAkFilePackageLowLevelIOBlocking = if (wwise_options.include_file_package_io_blocking) opaque {
    const Alignment = @alignOf(*CAkFilePackageLowLevelIOBlocking);

    pub fn create(allocator: std.mem.Allocator) !*CAkFilePackageLowLevelIOBlocking {
        const instance_size_of = c.WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Sizeof();
        const buffer = try allocator.alignedAlloc(u8, Alignment, instance_size_of);
        return @ptrCast(*CAkFilePackageLowLevelIOBlocking, c.WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Create(@ptrCast([*]u8, buffer[0..instance_size_of])));
    }

    pub fn destroy(self: *CAkFilePackageLowLevelIOBlocking, allocator: std.mem.Allocator) void {
        c.WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Destroy(self);

        const instance_size_of = c.WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Sizeof();
        const buffer = @ptrCast([*]align(Alignment) u8, @alignCast(Alignment, self));
        allocator.free(buffer[0..instance_size_of]);
    }

    pub inline fn init(self: *CAkFilePackageLowLevelIOBlocking, in_device_settings: *const StreamMgr.AkDeviceSettings, in_async_open: bool) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Init(self, @ptrCast(*const c.WWISEC_AkDeviceSettings, in_device_settings), in_async_open),
        );
    }

    pub inline fn term(self: *CAkFilePackageLowLevelIOBlocking) void {
        c.WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Term(self);
    }

    pub fn setBasePath(self: *CAkFilePackageLowLevelIOBlocking, fallback_allocator: std.mem.Allocator, base_path: []const u8) common.WwiseError!void {
        var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_oschar_allocator.get();

        var raw_base_path = common.toOSChar(allocator, base_path) catch return common.WwiseError.Fail;
        defer allocator.free(raw_base_path);

        return common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIOBlocking_SetBasePath(self, @ptrCast([*]const c.AkOSChar, raw_base_path)),
        );
    }

    pub fn addBasePath(self: *CAkFilePackageLowLevelIOBlocking, fallback_allocator: std.mem.Allocator, base_path: []const u8) common.WwiseError!void {
        var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_oschar_allocator.get();

        var raw_base_path = common.toOSChar(allocator, base_path) catch return common.WwiseError.Fail;
        defer allocator.free(raw_base_path);

        return common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIOBlocking_AddBasePath(self, raw_base_path),
        );
    }

    pub inline fn setUseSubfoldering(self: *CAkFilePackageLowLevelIOBlocking, use_sub_foldering: bool) void {
        c.WWISEC_CAkFilePackageLowLevelIOBlocking_SetUseSubfoldering(self, use_sub_foldering);
    }

    pub fn loadFilePackage(self: *CAkFilePackageLowLevelIOBlocking, falllback_allocator: std.mem.Allocator, file_package_name: []const u8) common.WwiseError!u32 {
        var result: u32 = undefined;

        var stack_oschar_allocator = common.stackCharAllocator(falllback_allocator);
        var allocator = stack_oschar_allocator.get();

        var raw_file_package_name = common.toOSChar(allocator, file_package_name) catch return common.WwiseError.Fail;
        defer allocator.free(raw_file_package_name);

        try common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIOBlocking_LoadFilePackage(self, @ptrCast([*]const c.AkOSChar, raw_file_package_name), &result),
        );

        return result;
    }

    pub inline fn unloadFilePackage(self: *CAkFilePackageLowLevelIOBlocking, package_id: u32) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIOBlocking_UnloadFilePackage(self, package_id),
        );
    }

    pub inline fn unloadAllFilePackages(self: *CAkFilePackageLowLevelIOBlocking) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIOBlocking_UnloadAllFilePackages(self),
        );
    }

    pub inline fn setPackageFallbackBehavior(self: *CAkFilePackageLowLevelIOBlocking, fallback: bool) void {
        c.WWISEC_AK_CAkFilePackageLowLevelIOBlocking_SetPackageFallbackBehavior(self, fallback);
    }
} else void;

pub const CAkFilePackageLowLevelIODeferred = if (wwise_options.include_file_package_io_deferred) opaque {
    const Alignment = @alignOf(*CAkFilePackageLowLevelIODeferred);

    pub fn create(allocator: std.mem.Allocator) !*CAkFilePackageLowLevelIODeferred {
        const instance_size_of = c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_Sizeof();
        const buffer = try allocator.alignedAlloc(u8, Alignment, instance_size_of);
        return @ptrCast(*CAkFilePackageLowLevelIODeferred, c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_Create(@ptrCast([*]u8, buffer[0..instance_size_of])));
    }

    pub fn destroy(self: *CAkFilePackageLowLevelIODeferred, allocator: std.mem.Allocator) void {
        c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_Destroy(self);

        const instance_size_of = c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_Sizeof();
        const buffer = @ptrCast([*]align(Alignment) u8, @alignCast(Alignment, self));
        allocator.free(buffer[0..instance_size_of]);
    }

    pub inline fn init(self: *CAkFilePackageLowLevelIODeferred, in_device_settings: *const StreamMgr.AkDeviceSettings, in_async_open: bool) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_Init(self, @ptrCast(*const c.WWISEC_AkDeviceSettings, in_device_settings), in_async_open),
        );
    }

    pub inline fn term(self: *CAkFilePackageLowLevelIODeferred) void {
        c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_Term(self);
    }

    pub fn setBasePath(self: *CAkFilePackageLowLevelIODeferred, fallback_allocator: std.mem.Allocator, base_path: []const u8) common.WwiseError!void {
        var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_oschar_allocator.get();

        var raw_base_path = common.toOSChar(allocator, base_path) catch return common.WwiseError.Fail;
        defer allocator.free(raw_base_path);

        return common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_SetBasePath(self, raw_base_path),
        );
    }

    pub fn addBasePath(self: *CAkFilePackageLowLevelIODeferred, fallback_allocator: std.mem.Allocator, base_path: []const u8) common.WwiseError!void {
        var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_oschar_allocator.get();

        var raw_base_path = common.toOSChar(allocator, base_path) catch return common.WwiseError.Fail;
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

        var raw_file_package_name = common.toOSChar(allocator, file_package_name) catch return common.WwiseError.Fail;
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
