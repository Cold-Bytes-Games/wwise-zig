const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");

pub const ErrorLevel = packed struct(common.DefaultEnumType) {
    message: bool = false,
    @"error": bool = false,
    pad: u30 = 0,

    pub const All = ErrorLevel{ .message = true, .@"error" = true };

    pub fn fromC(value: c.WWISEC_AK_Monitor_ErrorLevel) ErrorLevel {
        return @bitCast(value);
    }

    pub fn toC(self: ErrorLevel) c.WWISEC_AK_Monitor_ErrorLevel {
        return @bitCast(self);
    }
};
