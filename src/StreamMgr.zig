const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const settings = @import("settings.zig");
const stream_interfaces = @import("IAkStreamMgr.zig");

pub const AkStreamMgrSettings = extern struct {
    dummy: u8 = 0,

    pub inline fn fromC(value: c.WWISEC_AkStreamMgrSettings) AkStreamMgrSettings {
        return @bitCast(value);
    }

    pub fn toC(self: AkStreamMgrSettings) c.WWISEC_AkStreamMgrSettings {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkStreamMgrSettings) == @sizeOf(c.WWISEC_AkStreamMgrSettings));
    }
};

pub const AkDeviceSettings = extern struct {
    io_memory: ?*anyopaque = null,
    io_memory_size: u32 = 0,
    io_memory_alignment: u32 = 0,
    pool_attributes: u32 = 0,
    granularity: u32 = 0,
    thread_properties: settings.AkThreadProperties = .{},
    target_auto_stm_buffer_length: f32 = 0.0,
    max_concurrent_io: u32 = 0,
    use_stream_cache: bool = false,
    max_cache_pinned_bytes: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_AkDeviceSettings) AkDeviceSettings {
        return @bitCast(value);
    }

    pub fn toC(self: AkDeviceSettings) c.WWISEC_AkDeviceSettings {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkDeviceSettings) == @sizeOf(c.WWISEC_AkDeviceSettings));
    }
};

pub const AkFileDesc = extern struct {
    file_size: i64 = 0,
    sector: u64 = 0,
    file_handle: common.AkFileHandle = null,
    device_id: common.AkDeviceID = 0,

    pub inline fn fromC(value: c.WWISEC_AkFileDesc) AkFileDesc {
        return @bitCast(value);
    }

    pub fn toC(self: AkFileDesc) c.WWISEC_AkFileDesc {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkFileDesc) == @sizeOf(c.WWISEC_AkFileDesc));
    }
};

pub const AkIOTransferInfo = extern struct {
    file_position: u64 = 0,
    buffer_size: u32 = 0,
    requested_size: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_AkIOTransferInfo) AkIOTransferInfo {
        return @bitCast(value);
    }

    pub fn toC(self: AkIOTransferInfo) c.WWISEC_AkIOTransferInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkIOTransferInfo) == @sizeOf(c.WWISEC_AkIOTransferInfo));
    }
};

pub const AkIOCallback = ?*const fn (in_transfer_info: ?*anyopaque, in_result: common.AKRESULT) callconv(.C) void;

pub const AkAsyncIOTransferInfo = extern struct {
    base: AkIOTransferInfo = .{},
    buffer: ?*anyopaque = null,
    callback: AkIOCallback = null,
    cookie: ?*anyopaque = null,
    user_data: ?*anyopaque = null,

    pub inline fn fromC(value: c.WWISEC_AkAsyncIOTransferInfo) AkAsyncIOTransferInfo {
        return @bitCast(value);
    }

    pub fn toC(self: AkAsyncIOTransferInfo) c.WWISEC_AkAsyncIOTransferInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkAsyncIOTransferInfo) == @sizeOf(c.WWISEC_AkAsyncIOTransferInfo));
    }
};

pub const AkFileOpenCallback = ?*const fn (in_open_info: ?*NativeAkSyncFileOpenData, in_result: common.AKRESULT) callconv(.C) void;

pub const NativeAkSyncFileOpenData = extern struct {
    base: stream_interfaces.NativeAkFileOpenData,
    callback: ?*AkFileOpenCallback,
    cookie: ?*anyopaque,
    file_desc: AkFileDesc,
    custom_data: ?*anyopaque,
    stream_name: [*]const common.AkOSChar,

    pub inline fn fromC(value: c.WWISEC_AkAsyncFileOpenData) NativeAkSyncFileOpenData {
        return @bitCast(value);
    }

    pub fn toC(self: NativeAkSyncFileOpenData) c.WWISEC_AkAsyncFileOpenData {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(NativeAkSyncFileOpenData) == @sizeOf(c.WWISEC_AkAsyncFileOpenData));
    }
};

pub const AkIoHeuristics = extern struct {
    deadline: f32 = 0.0,
    priority: common.AkPriority = 0,

    pub inline fn fromC(value: c.WWISEC_AkIoHeuristics) AkIoHeuristics {
        return @bitCast(value);
    }

    pub fn toC(self: AkIoHeuristics) c.WWISEC_AkIoHeuristics {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkIoHeuristics) == @sizeOf(c.WWISEC_AkIoHeuristics));
    }
};

pub const IAkLowLevelIOHook = opaque {
    pub const FunctionTable = extern struct {
        destructor: *const fn (self: *IAkLowLevelIOHook) callconv(.C) void,
        close: *const fn (self: *IAkLowLevelIOHook, in_file_desc: *AkFileDesc) callconv(.C) common.AKRESULT,
        get_block_size: *const fn (self: *IAkLowLevelIOHook, in_file_desc: *AkFileDesc) callconv(.C) u32,
        get_device_desc: *const fn (self: *IAkLowLevelIOHook, out_device_desc: *stream_interfaces.NativeAkDeviceDesc) callconv(.C) void,
        get_device_data: *const fn (self: *IAkLowLevelIOHook) callconv(.C) u32,
        batch_open: *const fn (
            self: IAkLowLevelIOHook,
            in_num_files: u32,
            in_items: [*]*NativeAkSyncFileOpenData,
        ) callconv(.C) void,
        batch_read: *const fn (
            self: *IAkLowLevelIOHook,
            in_num_transfers: u32,
            in_transfer_items: [*]BatchIoTransferItem,
        ) callconv(.C) common.AKRESULT,
        batch_write: *const fn (
            self: *IAkLowLevelIOHook,
            in_num_transfers: u32,
            in_transfer_items: [*]BatchIoTransferItem,
        ) callconv(.C) common.AKRESULT,
        batch_cancel: *const fn (
            self: *IAkLowLevelIOHook,
            in_num_transfers: u32,
            in_transfer_items: [*]BatchIoTransferItem,
            io_cancel_all_transfers_for_this_file: [*]*bool,
        ) callconv(.C) void,
        output_searched_paths: *const fn (
            self: *IAkLowLevelIOHook,
            in_result: common.AKRESULT,
            in_file_open: *const stream_interfaces.NativeAkFileOpenData,
            out_searched_path: [*]common.AkOSChar,
            in_path_size: i32,
        ) callconv(.C) common.AKRESULT,
    };

    pub const BatchIoTransferItem = extern struct {
        file_desc: ?*AkFileDesc = null,
        io_heuristics: AkIoHeuristics = .{},
        transfer_info: ?*AkAsyncIOTransferInfo = null,

        pub inline fn fromC(value: c.WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchIoTransferItem) BatchIoTransferItem {
            return @bitCast(value);
        }

        pub inline fn toC(self: BatchIoTransferItem) c.WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchIoTransferItem {
            return @bitCast(self);
        }

        comptime {
            std.debug.assert(@sizeOf(BatchIoTransferItem) == @sizeOf(c.WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchIoTransferItem));
        }
    };

    pub fn close(self: *IAkLowLevelIOHook, in_file_desc: *const AkFileDesc) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkLowLevelIOHook_Close(
                @ptrCast(self),
                @constCast(@ptrCast(in_file_desc)),
            ),
        );
    }

    pub fn getBlockSize(self: *IAkLowLevelIOHook, in_file_desc: *const AkFileDesc) u32 {
        return c.WWISEC_AK_StreamMgr_IAkLowLevelIOHook_GetBlockSize(
            @ptrCast(self),
            @constCast(@ptrCast(in_file_desc)),
        );
    }

    pub fn getDeviceDesc(self: *IAkLowLevelIOHook, allocator: std.mem.Allocator, out_device_desc: *stream_interfaces.AkDeviceDesc) !void {
        var raw_device_desc: stream_interfaces.NativeAkDeviceDesc = undefined;
        c.WWISEC_AK_StreamMgr_IAkLowLevelIOHook_GetDeviceDesc(@ptrCast(self), @ptrCast(&raw_device_desc));
        out_device_desc.* = try stream_interfaces.AkDeviceDesc.fromC(&raw_device_desc, allocator);
    }

    pub fn getDeviceData(self: *IAkLowLevelIOHook) u32 {
        return c.WWISEC_AK_StreamMgr_IAkLowLevelIOHook_GetDeviceData(@ptrCast(self));
    }

    pub fn batchOpen(
        self: *IAkLowLevelIOHook,
        in_num_files: u32,
        in_items: [*]*NativeAkSyncFileOpenData,
    ) void {
        c.WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchOpen(
            @ptrCast(self),
            in_num_files,
            @ptrCast(in_items),
        );
    }

    pub fn batchRead(
        self: *IAkLowLevelIOHook,
        in_num_transfers: u32,
        in_transfer_items: [*]BatchIoTransferItem,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchRead(
                @ptrCast(self),
                in_num_transfers,
                @ptrCast(in_transfer_items),
            ),
        );
    }

    pub fn batchWrite(
        self: *IAkLowLevelIOHook,
        in_num_transfers: u32,
        in_transfer_items: [*]BatchIoTransferItem,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchWrite(
                @ptrCast(self),
                in_num_transfers,
                @ptrCast(in_transfer_items),
            ),
        );
    }

    pub fn batchCancel(
        self: *IAkLowLevelIOHook,
        in_num_transfers: u32,
        in_transfer_items: [*]BatchIoTransferItem,
        io_cancel_all_transfers_for_this_file: [*]*bool,
    ) void {
        c.WWISEC_AK_StreamMgr_IAkLowLevelIOHook_BatchCancel(
            @ptrCast(self),
            in_num_transfers,
            @ptrCast(in_transfer_items),
            @ptrCast(io_cancel_all_transfers_for_this_file),
        );
    }

    pub fn outputSearchedPaths(
        self: *IAkLowLevelIOHook,
        fallback_allocator: std.mem.Allocator,
        in_result: common.AKRESULT,
        in_file_open: stream_interfaces.AkFileOpenData,
        out_searched_path: [*]common.AkOSChar,
        in_path_size: i32,
    ) common.WwiseError!void {
        var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_char_allocator.get();

        const native_file_open = in_file_open.toC(allocator) catch return common.WwiseError.Fail;
        defer allocator.free(native_file_open.file);

        return common.handleAkResult(c.WWISEC_AK_StreamMgr_IAkLowLevelIOHook_OutputSearchedPaths(
            @ptrCast(self),
            in_result,
            @ptrCast(&native_file_open),
            out_searched_path,
            in_path_size,
        ));
    }

    pub fn createInstance(instance: *anyopaque, function_table: *const FunctionTable) *IAkLowLevelIOHook {
        return @ptrCast(
            c.WWISEC_AK_StreamMgr_IAkLowLevelIOHook_CreateInstance(instance, @ptrCast(function_table)),
        );
    }

    pub fn destroyInstance(instance: *anyopaque) void {
        c.WWISEC_AK_StreamMgr_IAkLowLevelIOHook_DestroyInstance(@ptrCast(instance));
    }
};

pub const IAkFileLocationResolver = opaque {
    pub const FunctionTable = extern struct {
        destructor: *const fn (self: *IAkFileLocationResolver) callconv(.C) void,
        get_next_preferred_device: *const fn (self: *IAkFileLocationResolver, in_file_open: *NativeAkSyncFileOpenData, io_id_device: *common.AkDeviceID) callconv(.C) common.AKRESULT,
    };

    pub fn getNextPreferredDevice(self: *IAkFileLocationResolver, in_file_open: *NativeAkSyncFileOpenData, io_id_device: *common.AkDeviceID) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkFileLocationResolver_GetNextPreferredDevice(
                @ptrCast(self),
                @ptrCast(in_file_open),
                @ptrCast(io_id_device),
            ),
        );
    }

    pub fn createInstance(instance: *anyopaque, function_table: *const FunctionTable) *IAkFileLocationResolver {
        return @ptrCast(
            c.WWISEC_AK_StreamMgr_IAkFileLocationResolver_CreateInstance(instance, @ptrCast(function_table)),
        );
    }

    pub fn destroyInstance(instance: *anyopaque) void {
        c.WWISEC_AK_StreamMgr_IAkFileLocationResolver_DestroyInstance(@ptrCast(instance));
    }
};

pub fn create(in_settings: *AkStreamMgrSettings) ?*stream_interfaces.IAkStreamMgr {
    return @ptrCast(@alignCast(c.WWISEC_AK_StreamMgr_Create(@ptrCast(in_settings))));
}

pub fn getDefaultSettings(out_settings: *AkStreamMgrSettings) void {
    c.WWISEC_AK_StreamMgr_GetDefaultSettings(@ptrCast(out_settings));
}

pub fn getFileLocationResolver() ?*IAkFileLocationResolver {
    return @ptrCast(@alignCast(c.WWISEC_AK_StreamMgr_GetFileLocationResolver()));
}

pub fn setFileLocationResolver(in_file_location_resolver: ?*IAkFileLocationResolver) void {
    c.WWISEC_AK_StreamMgr_SetFileLocationResolver(in_file_location_resolver);
}

pub fn createDevice(in_settings: *const AkDeviceSettings, in_low_level_hook: ?*IAkLowLevelIOHook) common.WwiseError!common.AkDeviceID {
    var result: common.AkDeviceID = undefined;

    try common.handleAkResult(
        c.WWISEC_AK_StreamMgr_CreateDevice(@ptrCast(in_settings), in_low_level_hook, @ptrCast(&result)),
    );

    return result;
}

pub fn destroyDevice(in_deviceID: common.AkDeviceID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_StreamMgr_DestroyDevice(in_deviceID),
    );
}

pub fn performIO() common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_StreamMgr_PerformIO(),
    );
}

pub fn getDefaultDeviceSettings(out_settings: *AkDeviceSettings) void {
    c.WWISEC_AK_StreamMgr_GetDefaultDeviceSettings(@ptrCast(out_settings));
}

pub fn setCurrentLanguage(fallback_allocator: std.mem.Allocator, language_name: []const u8) common.WwiseError!void {
    var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_oschar_allocator.get();

    const raw_language_name = common.toOSChar(allocator, language_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_language_name);

    return common.handleAkResult(
        c.WWISEC_AK_StreamMgr_SetCurrentLanguage(@ptrCast(raw_language_name)),
    );
}

pub fn getCurrentLanguage(allocator: std.mem.Allocator) ![]const u8 {
    return try common.fromOSChar(allocator, c.WWISEC_AK_StreamMgr_GetCurrentLanguage());
}

pub const AkLanguageCChangeHandler = c.WWISEC_AK_StreamMgr_AkLanguageChangeHandler;

pub fn addLanguageChangeObserver(in_handler: AkLanguageCChangeHandler, in_cookie: ?*anyopaque) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_StreamMgr_AddLanguageChangeObserver(in_handler, in_cookie),
    );
}

pub fn removeLanguageChangeObserver(in_cookie: ?*anyopaque) void {
    c.WWISEC_AK_StreamMgr_RemoveLanguageChangeObserver(in_cookie);
}

pub fn flushAllCaches() void {
    c.WWISEC_AK_StreamMgr_FlushAllCaches();
}
