const c = @import("wwise_c");
const std = @import("std");

pub const IReadBytes = opaque {
    pub const FunctionTable = extern struct {
        read_bytes: *const fn (self: *IReadBytes, in_data: ?*anyopaque, in_count_bytes: i32, out_read: *i32) callconv(.c) bool,
    };

    pub fn readBytes(self: *IReadBytes, in_data: ?*anyopaque, in_count_bytes: i32, out_read: *i32) bool {
        return c.WWISEC_AK_IReadBytes_ReadBytes(@ptrCast(self), in_data, in_count_bytes, out_read);
    }

    pub fn createInstance(instance: *anyopaque, function_table: *const FunctionTable) *IReadBytes {
        return @ptrCast(
            c.WWISEC_AK_IReadBytes_CreateInstance(instance, @ptrCast(function_table)),
        );
    }

    pub fn destroyInstance(instance: *anyopaque) void {
        c.WWISEC_AK_IReadBytes_DestroyInstance(@ptrCast(instance));
    }
};

pub const IWriteBytes = opaque {
    pub const FunctionTable = extern struct {
        write_bytes: *const fn (self: *IWriteBytes, in_data: ?*const anyopaque, in_count_bytes: i32, out_written: *i32) callconv(.c) bool,
    };

    pub fn writeBytes(self: *IWriteBytes, in_data: ?*const anyopaque, in_count_bytes: i32, out_written: *i32) bool {
        return c.WWISE_AK_IWriteBytes_WriteBytes(@ptrCast(self), in_data, in_count_bytes, out_written);
    }

    pub fn createInstance(instance: *anyopaque, function_table: *const FunctionTable) *IWriteBytes {
        return @ptrCast(
            c.WWISEC_AK_IWriteBytes_CreateInstance(instance, @ptrCast(function_table)),
        );
    }

    pub fn destroyInstance(instance: *anyopaque) void {
        c.WWISEC_AK_IWriteBytes_DestroyInstance(@ptrCast(instance));
    }
};
