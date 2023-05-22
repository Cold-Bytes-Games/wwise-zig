const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const wwise_options = @import("wwise_options");
const StreamMgr = @import("StreamMgr.zig");

pub const CAkMultipleFileLocation = opaque {
    pub usingnamespace Methods(@This());

    fn Methods(comptime T: type) type {
        return struct {
            pub inline fn setBasePath(self: *T, fallback_allocator: std.mem.Allocator, base_path: []const u8) common.WwiseError!void {
                var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
                var allocator = stack_oschar_allocator.get();

                var raw_base_path = common.toOSChar(allocator, base_path) catch return common.WwiseError.Fail;
                defer allocator.free(raw_base_path);

                return common.handleAkResult(
                    c.WWISEC_AK_CAkMultipleFileLocation_SetBasePath(self, raw_base_path),
                );
            }

            pub inline fn addBasePath(self: *T, fallback_allocator: std.mem.Allocator, base_path: []const u8) common.WwiseError!void {
                var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
                var allocator = stack_oschar_allocator.get();

                var raw_base_path = common.toOSChar(allocator, base_path) catch return common.WwiseError.Fail;
                defer allocator.free(raw_base_path);

                return common.handleAkResult(
                    c.WWISEC_AK_CAkMultipleFileLocation_AddBasePath(self, raw_base_path),
                );
            }

            pub inline fn setUseSubfoldering(self: *T, use_sub_foldering: bool) void {
                c.WWISEC_CAkMultipleFileLocation_SetUseSubfoldering(self, use_sub_foldering);
            }
        };
    }
};

pub const CAkDefaultIOHookBlocking = if (wwise_options.include_default_io_hook_blocking) opaque {
    pub usingnamespace CAkMultipleFileLocation.Methods(@This());

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

    pub fn init(self: *CAkDefaultIOHookBlocking, in_device_settings: StreamMgr.AkDeviceSettings, in_async_open: bool) common.WwiseError!void {
        var raw_device_settings = in_device_settings.toC();

        return common.handleAkResult(
            c.WWISEC_AK_CAkDefaultIOHookBlocking_Init(self, &raw_device_settings, in_async_open),
        );
    }

    pub fn term(self: *CAkDefaultIOHookBlocking) void {
        c.WWISEC_AK_CAkDefaultIOHookBlocking_Term(self);
    }
} else void;

pub const CAkDefaultIOHookDeferred = if (wwise_options.include_default_io_hook_deferred) opaque {
    pub usingnamespace CAkMultipleFileLocation.Methods(@This());

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

    pub fn init(self: *CAkDefaultIOHookDeferred, in_device_settings: StreamMgr.AkDeviceSettings, in_async_open: bool) common.WwiseError!void {
        var raw_device_settings = in_device_settings.toC();

        return common.handleAkResult(
            c.WWISEC_AK_CAkDefaultIOHookDeferred_Init(self, &raw_device_settings, in_async_open),
        );
    }

    pub fn term(self: *CAkDefaultIOHookDeferred) void {
        c.WWISEC_AK_CAkDefaultIOHookDeferred_Term(self);
    }
} else void;

pub const CAkFilePackageLowLevelIOBlocking = if (wwise_options.include_file_package_io_blocking) opaque {
    pub usingnamespace CAkMultipleFileLocation.Methods(@This());

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

    pub fn init(self: *CAkFilePackageLowLevelIOBlocking, in_device_settings: StreamMgr.AkDeviceSettings, in_async_open: bool) common.WwiseError!void {
        var raw_device_settings = in_device_settings.toC();

        return common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Init(self, &raw_device_settings, in_async_open),
        );
    }

    pub fn term(self: *CAkFilePackageLowLevelIOBlocking) void {
        c.WWISEC_AK_CAkFilePackageLowLevelIOBlocking_Term(self);
    }

    pub fn loadFilePackage(self: *CAkFilePackageLowLevelIOBlocking, falllback_allocator: std.mem.Allocator, file_package_name: []const u8) common.WwiseError!u32 {
        var result: u32 = undefined;

        var stack_oschar_allocator = common.stackCharAllocator(falllback_allocator);
        var allocator = stack_oschar_allocator.get();

        var raw_file_package_name = common.toOSChar(allocator, file_package_name) catch return common.WwiseError.Fail;
        defer allocator.free(raw_file_package_name);

        try common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIOBlocking_LoadFilePackage(self, raw_file_package_name, &result),
        );

        return result;
    }

    pub fn unloadFilePackage(self: *CAkFilePackageLowLevelIOBlocking, package_id: u32) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIOBlocking_UnloadFilePackage(self, package_id),
        );
    }

    pub fn unloadAllFilePackages(self: *CAkFilePackageLowLevelIOBlocking) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIOBlocking_UnloadAllFilePackages(self),
        );
    }

    pub fn setPackageFallbackBehavior(self: *CAkFilePackageLowLevelIOBlocking, fallback: bool) void {
        c.WWISEC_AK_CAkFilePackageLowLevelIOBlocking_SetPackageFallbackBehavior(self, fallback);
    }
} else void;

pub const CAkFilePackageLowLevelIODeferred = if (wwise_options.include_file_package_io_deferred) opaque {
    pub usingnamespace CAkMultipleFileLocation.Methods(@This());

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

    pub fn init(self: *CAkFilePackageLowLevelIODeferred, in_device_settings: StreamMgr.AkDeviceSettings, in_async_open: bool) common.WwiseError!void {
        var raw_device_settings = in_device_settings.toC();

        return common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_Init(self, &raw_device_settings, in_async_open),
        );
    }

    pub fn term(self: *CAkFilePackageLowLevelIODeferred) void {
        c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_Term(self);
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

    pub fn unloadFilePackage(self: *CAkFilePackageLowLevelIODeferred, package_id: u32) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_UnloadFilePackage(self, package_id),
        );
    }

    pub fn unloadAllFilePackages(self: *CAkFilePackageLowLevelIODeferred) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_UnloadAllFilePackages(self),
        );
    }

    pub fn setPackageFallbackBehavior(self: *CAkFilePackageLowLevelIODeferred, fallback: bool) void {
        c.WWISEC_AK_CAkFilePackageLowLevelIODeferred_SetPackageFallbackBehavior(self, fallback);
    }
} else void;
