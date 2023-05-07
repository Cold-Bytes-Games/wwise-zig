const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const settings = @import("settings.zig");

pub const TestVTable = extern struct {
    __v: *const VTable,

    pub const VTable = extern struct {
        virtual_destructor: common.VirtualDestructor(TestVTable) = .{},
        print: *const fn (self: *TestVTable, value: i32) callconv(.C) void,
    };

    pub fn Methods(comptime T: type) type {
        return extern struct {
            pub inline fn deinit(self: *T) void {
                @ptrCast(*const TestVTable.VTable, self.__v).virtual_destructor.call(@ptrCast(*TestVTable, self));
            }

            pub inline fn toSelf(iself: *const TestVTable) *const T {
                return @ptrCast(*const T, iself);
            }

            pub inline fn toMutableSelf(iself: *TestVTable) *T {
                return @ptrCast(*T, iself);
            }

            pub inline fn print(self: *T, value: i32) void {
                return @ptrCast(*const TestVTable.VTable, self.__v)
                    .print(@ptrCast(*TestVTable, self), value);
            }
        };
    }

    pub usingnamespace Methods(@This());
    pub usingnamespace common.CastMethods(@This());

    comptime {
        std.debug.assert(@sizeOf(VTable) == @sizeOf(c.WWISEC_TestVTable));
        std.debug.assert(@offsetOf(VTable, "print") == @offsetOf(c.WWISEC_TestVTable, "Print"));
    }
};

pub fn setTestInstance(instance: *TestVTable) void {
    c.WWISEC_SetTestVTable(instance);
}

pub fn testCall() void {
    c.WWISEC_CallTest();
}
