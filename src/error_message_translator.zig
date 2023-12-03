const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");

pub const AK_TRANSLATOR_MAX_NAME_SIZE = c.WWISEC_AK_TRANSLATOR_MAX_NAME_SIZE;

pub const AkErrorMessageTranslator = opaque {
    pub const TagInformation = extern struct {
        tag: ?[*:0]const common.AkOSChar = null,
        start_block: ?[*:0]const common.AkOSChar = null,
        args: ?[*:0]const u8 = null,
        parsed_info: [AK_TRANSLATOR_MAX_NAME_SIZE]common.AkOSChar = undefined,
        arg_size: u32 = 0,
        len: u16 = 0,
        info_is_parsed: bool = false,

        pub inline fn fromC(value: c.WWISEC_AkErrorMessageTranslator_TagInformation) TagInformation {
            return @bitCast(value);
        }

        pub inline fn toC(self: TagInformation) c.WWISEC_AkErrorMessageTranslator_TagInformation {
            return @bitCast(self);
        }

        comptime {
            std.debug.assert(@sizeOf(TagInformation) == @sizeOf(c.WWISEC_AkErrorMessageTranslator_TagInformation));
        }
    };

    pub const FunctionTable = extern struct {
        destructor: *const fn (self: *AkErrorMessageTranslator) callconv(.C) void,
        term: *const fn (self: *AkErrorMessageTranslator) callconv(.C) void,
        translate: *const fn (self: *AkErrorMessageTranslator, in_error: [*:0]const common.AkOSChar, out_translated_error: [*:0]const common.AkOSChar, in_max_error_size: i32, in_args: [*:0]const u8, in_arg_size: u32) callconv(.C) bool,
        get_info: *const fn (self: *AkErrorMessageTranslator, in_tag_list: [*]TagInformation, in_count: u32, out_translated: *u32) callconv(.C) bool,
    };

    pub fn term(self: *AkErrorMessageTranslator) void {
        return c.WWISEC_AkErrorMessageTranslator_Term(@ptrCast(self));
    }

    pub fn setFallBackTranslator(self: *AkErrorMessageTranslator, in_fallback_translator: *AkErrorMessageTranslator) void {
        c.WWISEC_AkErrorMessageTranslator_SetFallBackTranslator(@ptrCast(self), @ptrCast(in_fallback_translator));
    }

    pub fn translate(self: *AkErrorMessageTranslator, in_allocator: std.mem.Allocator, in_error: []const u8, out_translated_error: *[]u8, max_error_size: i32, in_args: []const u8, in_arg_size: u32) !bool {
        var area_allocator = std.heap.ArenaAllocator.init(in_allocator);
        defer area_allocator.deinit();

        var allocator = area_allocator.allocator();

        const raw_error = try common.toOSChar(allocator, in_error);

        const raw_out_translated_error = try allocator.allocSentinel(common.AkOSChar, @intCast(max_error_size), 0);

        const raw_args = try common.toCString(allocator, in_args);

        const result = c.WWISEC_AkErrorMessageTranslator_Translate(@ptrCast(self), raw_error, raw_out_translated_error, max_error_size, raw_args, in_arg_size);

        out_translated_error.* = try common.fromOSChar(in_allocator, raw_out_translated_error);

        return result;
    }

    pub fn createInstance(instance: *anyopaque, function_table: *const FunctionTable) *AkErrorMessageTranslator {
        return @ptrCast(
            c.WWISEC_AkErrorMessageTranslator_CreateInstance(instance, @ptrCast(function_table)),
        );
    }

    pub fn destroyInstance(instance: *anyopaque) void {
        c.WWISEC_AkErrorMessageTranslator_DestroyInstance(@ptrCast(instance));
    }
};
