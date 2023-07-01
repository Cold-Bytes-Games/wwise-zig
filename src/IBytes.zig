const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");

pub const IReadBytes = extern struct {
    __v: *const VTable,

    pub const VTable = extern struct {
        read_bytes: *const fn (self: *IReadBytes, in_data: ?*anyopaque, in_count_bytes: i32, out_read: *i32) callconv(.C) bool,
    };

    pub fn Methods(comptime T: type) type {
        return extern struct {
            pub inline fn toSelf(iself: *const IReadBytes) *const T {
                return @ptrCast(iself);
            }

            pub inline fn toMutableSelf(iself: *IReadBytes) *T {
                return @ptrCast(iself);
            }

            pub inline fn readBytes(self: *T, in_data: ?*anyopaque, in_count_bytes: i32, out_read: *i32) bool {
                return @as(*const IReadBytes.VTable, @ptrCast(self.__v)).read_bytes(@ptrCast(self), in_data, in_count_bytes, out_read);
            }
        };
    }

    pub usingnamespace Methods(@This());
    pub usingnamespace common.CastMethods(@This());
};

pub const IWriteBytes = extern struct {
    __v: *const VTable,

    pub const VTable = extern struct {
        write_bytes: *const fn (self: *IWriteBytes, in_data: ?*const anyopaque, in_count_bytes: i32, out_written: *i32) callconv(.C) bool,
    };

    pub fn Methods(comptime T: type) type {
        return extern struct {
            pub inline fn toSelf(iself: *const IWriteBytes) *const T {
                return @ptrCast(iself);
            }

            pub inline fn toMutableSelf(iself: *IWriteBytes) *T {
                return @ptrCast(iself);
            }

            pub inline fn readBytes(self: *T, in_data: ?*const anyopaque, in_count_bytes: i32, out_written: *i32) bool {
                return @as(*const IWriteBytes.VTable, @ptrCast(self.__v)).write_bytes(@ptrCast(self), in_data, in_count_bytes, out_written);
            }
        };
    }

    pub usingnamespace Methods(@This());
    pub usingnamespace common.CastMethods(@This());
};
