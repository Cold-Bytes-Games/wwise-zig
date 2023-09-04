const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const settings = @import("settings.zig");
const stream_interfaces = @import("IAkStreamMgr.zig");

pub const AK_SCHEDULER_BLOCKING = c.WWISEC_AK_SCHEDULER_BLOCKING;
pub const AK_SCHEDULER_DEFERRED_LINED_UP = c.WWISEC_AK_SCHEDULER_DEFERRED_LINED_UP;

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
    scheduler_type_flags: u32 = 0,
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
    custom_param_size: u32 = 0,
    custom_param: ?*anyopaque = null,
    file_handle: common.AkFileHandle = null,
    device_id: common.AkDeviceID = 0,
    package: ?*anyopaque = null,

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
pub const AkBatchIOCallback = ?*const fn (in_num_transfers: u32, in_transfer_info: [*]*AkAsyncIOTransferInfo, in_result: common.AKRESULT) callconv(.C) void;

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

    pub fn createInstance(instance: *anyopaque, function_table: *const FunctionTable) *IAkLowLevelIOHook {
        return @ptrCast(
            c.WWISEC_AK_StreamMgr_IAkLowLevelIOHook_CreateInstance(instance, @ptrCast(function_table)),
        );
    }

    pub fn destroyInstance(instance: *anyopaque) void {
        c.WWISEC_AK_StreamMgr_IAkLowLevelIOHook_DestroyInstance(@ptrCast(instance));
    }
};

// Inherits from IAkLowLevelIOHook
pub const IAkIOHookBlocking = opaque {
    pub const FunctionTable = extern struct {
        destructor: *const fn (self: *IAkIOHookBlocking) callconv(.C) void,
        close: *const fn (self: *IAkIOHookBlocking, in_file_desc: *AkFileDesc) callconv(.C) common.AKRESULT,
        get_block_size: *const fn (self: *IAkIOHookBlocking, in_file_desc: *AkFileDesc) callconv(.C) u32,
        get_device_desc: *const fn (self: *IAkIOHookBlocking, out_device_desc: *stream_interfaces.NativeAkDeviceDesc) callconv(.C) void,
        get_device_data: *const fn (self: *IAkIOHookBlocking) callconv(.C) u32,
        read: *const fn (
            self: *IAkIOHookBlocking,
            in_file_desc: *AkFileDesc,
            in_heuristics: *AkIoHeuristics,
            out_buffer: ?*anyopaque,
            in_transfer_info: *AkIOTransferInfo,
        ) callconv(.C) common.AKRESULT,
        write: *const fn (
            self: *IAkIOHookBlocking,
            in_file_desc: *AkFileDesc,
            in_heuristics: *AkIoHeuristics,
            in_data: ?*anyopaque,
            in_transfer_info: *AkIOTransferInfo,
        ) callconv(.C) common.AKRESULT,
    };

    pub fn close(self: *IAkIOHookBlocking, in_file_desc: *const AkFileDesc) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkIOHookBlocking_Close(
                @ptrCast(self),
                @constCast(@ptrCast(in_file_desc)),
            ),
        );
    }

    pub fn getBlockSize(self: *IAkIOHookBlocking, in_file_desc: *const AkFileDesc) u32 {
        return c.WWISEC_AK_StreamMgr_IAkIOHookBlocking_GetBlockSize(
            @ptrCast(self),
            @constCast(@ptrCast(in_file_desc)),
        );
    }

    pub fn getDeviceDesc(self: *IAkIOHookBlocking, allocator: std.mem.Allocator, out_device_desc: *stream_interfaces.AkDeviceDesc) !void {
        var raw_device_desc: stream_interfaces.NativeAkDeviceDesc = undefined;
        c.WWISEC_AK_StreamMgr_IAkIOHookBlocking_GetDeviceDesc(@ptrCast(self), @ptrCast(&raw_device_desc));
        out_device_desc.* = try stream_interfaces.AkDeviceDesc.fromC(&raw_device_desc, allocator);
    }

    pub fn getDeviceData(self: *IAkIOHookBlocking) u32 {
        return c.WWISEC_AK_StreamMgr_IAkIOHookBlocking_GetDeviceData(@ptrCast(self));
    }

    pub fn read(self: *IAkIOHookBlocking, in_file_desc: *const AkFileDesc, in_heuristics: *const AkIoHeuristics, out_buffer: ?*anyopaque, in_transfer_info: *const AkIOTransferInfo) common.WwiseError!void {
        try common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkIOHookBlocking_Read(
                @ptrCast(self),
                @constCast(@ptrCast(in_file_desc)),
                @ptrCast(in_heuristics),
                out_buffer,
                @constCast(@ptrCast(in_transfer_info)),
            ),
        );
    }

    pub fn write(self: *IAkIOHookBlocking, in_file_desc: *const AkFileDesc, in_heuristics: *const AkIoHeuristics, in_data: ?*anyopaque, io_transfer_info: *AkIOTransferInfo) common.WwiseError!void {
        try common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkIOHookBlocking_Write(
                @ptrCast(self),
                @constCast(@ptrCast(in_file_desc)),
                @ptrCast(in_heuristics),
                in_data,
                @ptrCast(io_transfer_info),
            ),
        );
    }

    pub fn createInstance(instance: *anyopaque, function_table: *const FunctionTable) *IAkIOHookBlocking {
        return @ptrCast(
            c.WWISEC_AK_StreamMgr_IAkIOHookBlocking_CreateInstance(instance, @ptrCast(function_table)),
        );
    }

    pub fn destroyInstance(instance: *anyopaque) void {
        c.WWISEC_AK_StreamMgr_IAkIOHookBlocking_DestroyInstance(@ptrCast(instance));
    }
};

// Inherits from IAkLowLevelIOHook
pub const IAkIOHookDeferredBatch = opaque {
    pub const FunctionTable = extern struct {
        destructor: *const fn (self: *IAkIOHookBlocking) callconv(.C) void,
        close: *const fn (self: *IAkIOHookBlocking, in_file_desc: *AkFileDesc) callconv(.C) common.AKRESULT,
        get_block_size: *const fn (self: *IAkIOHookBlocking, in_file_desc: *AkFileDesc) callconv(.C) u32,
        get_device_desc: *const fn (self: *IAkIOHookBlocking, out_device_desc: *stream_interfaces.NativeAkDeviceDesc) callconv(.C) void,
        get_device_data: *const fn (self: *IAkIOHookBlocking) callconv(.C) u32,
        batch_read: *const fn (
            self: *IAkIOHookDeferredBatch,
            in_num_transfers: u32,
            in_transfer_items: [*]BatchIoTransferItem,
            in_batch_io_callback: AkBatchIOCallback,
            io_dispatch_results: [*]common.AKRESULT,
        ) callconv(.C) common.AKRESULT,
        batch_write: *const fn (
            self: *IAkIOHookDeferredBatch,
            in_num_transfers: u32,
            in_transfer_items: [*]BatchIoTransferItem,
            in_batch_io_callback: AkBatchIOCallback,
            io_dispatch_results: [*]common.AKRESULT,
        ) callconv(.C) common.AKRESULT,
        batch_cancel: *const fn (
            self: *IAkIOHookDeferredBatch,
            in_num_transfers: u32,
            in_transfer_items: [*]BatchIoTransferItem,
            io_cancel_all_transfers_for_this_file: [*]*bool,
        ) callconv(.C) void,
    };

    pub const BatchIoTransferItem = extern struct {
        file_desc: ?*AkFileDesc = null,
        io_heuristics: AkIoHeuristics = .{},
        transfer_info: ?*AkAsyncIOTransferInfo = null,

        pub inline fn fromC(value: c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem) BatchIoTransferItem {
            return @bitCast(value);
        }

        pub inline fn toC(self: BatchIoTransferItem) c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem {
            return @bitCast(self);
        }

        comptime {
            std.debug.assert(@sizeOf(BatchIoTransferItem) == @sizeOf(c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem));
        }
    };

    pub fn close(self: *IAkIOHookDeferredBatch, in_file_desc: *const AkFileDesc) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_Close(
                @ptrCast(self),
                @constCast(@ptrCast(in_file_desc)),
            ),
        );
    }

    pub fn getBlockSize(self: *IAkIOHookDeferredBatch, in_file_desc: *const AkFileDesc) u32 {
        return c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_GetBlockSize(
            @ptrCast(self),
            @constCast(@ptrCast(in_file_desc)),
        );
    }

    pub fn getDeviceDesc(self: *IAkIOHookDeferredBatch, allocator: std.mem.Allocator, out_device_desc: *stream_interfaces.AkDeviceDesc) !void {
        var raw_device_desc: stream_interfaces.NativeAkDeviceDesc = undefined;
        c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_GetDeviceDesc(@ptrCast(self), @ptrCast(&raw_device_desc));
        out_device_desc.* = try stream_interfaces.AkDeviceDesc.fromC(&raw_device_desc, allocator);
    }

    pub fn getDeviceData(self: *IAkIOHookDeferredBatch) u32 {
        return c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_GetDeviceData(@ptrCast(self));
    }

    pub fn batchRead(
        self: *IAkIOHookDeferredBatch,
        in_num_transfers: u32,
        in_transfer_items: [*]BatchIoTransferItem,
        in_batch_io_callback: AkBatchIOCallback,
        io_dispatch_results: [*]common.AKRESULT,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchRead(
                @ptrCast(self),
                in_num_transfers,
                @ptrCast(in_transfer_items),
                @ptrCast(in_batch_io_callback),
                @ptrCast(io_dispatch_results),
            ),
        );
    }

    pub fn batchWrite(
        self: *IAkIOHookDeferredBatch,
        in_num_transfers: u32,
        in_transfer_items: [*]BatchIoTransferItem,
        in_batch_io_callback: AkBatchIOCallback,
        io_dispatch_results: [*]common.AKRESULT,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchWrite(
                @ptrCast(self),
                in_num_transfers,
                @ptrCast(in_transfer_items),
                @ptrCast(in_batch_io_callback),
                @ptrCast(io_dispatch_results),
            ),
        );
    }

    pub fn batchCancel(
        self: *IAkIOHookDeferredBatch,
        in_num_transfers: u32,
        in_transfer_items: [*]BatchIoTransferItem,
        io_cancel_all_transfers_for_this_file: [*]*bool,
    ) void {
        c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchCancel(
            @ptrCast(self),
            in_num_transfers,
            @ptrCast(in_transfer_items),
            @ptrCast(io_cancel_all_transfers_for_this_file),
        );
    }

    pub fn createInstance(instance: *anyopaque, function_table: *const FunctionTable) *IAkIOHookDeferredBatch {
        return @ptrCast(
            c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_CreateInstance(instance, @ptrCast(function_table)),
        );
    }

    pub fn destroyInstance(instance: *anyopaque) void {
        c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_DestroyInstance(@ptrCast(instance));
    }
};

// Inherits from IAkIOHookDeferredBatch
pub const IAkIOHookDeferred = opaque {
    pub const FunctionTable = extern struct {
        destructor: *const fn (self: *IAkIOHookBlocking) callconv(.C) void,
        close: *const fn (self: *IAkIOHookBlocking, in_file_desc: *AkFileDesc) callconv(.C) common.AKRESULT,
        get_block_size: *const fn (self: *IAkIOHookBlocking, in_file_desc: *AkFileDesc) callconv(.C) u32,
        get_device_desc: *const fn (self: *IAkIOHookBlocking, out_device_desc: *stream_interfaces.NativeAkDeviceDesc) callconv(.C) void,
        get_device_data: *const fn (self: *IAkIOHookBlocking) callconv(.C) u32,
        batch_read: ?*const fn (
            self: *IAkIOHookDeferredBatch,
            in_num_transfers: u32,
            in_transfer_items: [*]BatchIoTransferItem,
            in_batch_io_callback: AkBatchIOCallback,
            io_dispatch_results: [*]common.AKRESULT,
        ) callconv(.C) common.AKRESULT = null,
        batch_write: ?*const fn (
            self: *IAkIOHookDeferredBatch,
            in_num_transfers: u32,
            in_transfer_items: [*]BatchIoTransferItem,
            in_batch_io_callback: AkBatchIOCallback,
            io_dispatch_results: [*]common.AKRESULT,
        ) callconv(.C) common.AKRESULT = null,
        batch_cancel: ?*const fn (
            self: *IAkIOHookDeferredBatch,
            in_num_transfers: u32,
            in_transfer_items: [*]BatchIoTransferItem,
            io_cancel_all_transfers_for_this_file: [*]*bool,
        ) callconv(.C) void = null,
        read: *const fn (
            self: *IAkIOHookDeferred,
            in_file_desc: *AkFileDesc,
            in_heuristics: *AkIoHeuristics,
            io_transferInfo: *AkAsyncIOTransferInfo,
        ) callconv(.C) common.AKRESULT,
        write: *const fn (
            self: *IAkIOHookDeferred,
            in_file_desc: *AkFileDesc,
            in_heuristics: *AkIoHeuristics,
            io_transferInfo: *AkAsyncIOTransferInfo,
        ) callconv(.C) common.AKRESULT,
        cancel: *const fn (
            self: *IAkIOHookDeferred,
            in_file_desc: *AkFileDesc,
            io_transferInfo: *AkAsyncIOTransferInfo,
            io_bCancelAllTransfersForThisFile: *bool,
        ) callconv(.C) void,
    };

    pub const BatchIoTransferItem = IAkIOHookDeferredBatch.BatchIoTransferItem;

    pub fn close(self: *IAkIOHookDeferred, in_file_desc: *AkFileDesc) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkIOHookDeferred_Close(
                @ptrCast(self),
                @ptrCast(in_file_desc),
            ),
        );
    }

    pub fn getBlockSize(self: *IAkIOHookDeferred, in_file_desc: *AkFileDesc) u32 {
        return c.WWISEC_AK_StreamMgr_IAkIOHookDeferred_GetBlockSize(@ptrCast(self), @ptrCast(in_file_desc));
    }

    pub fn getDeviceDesc(self: *IAkIOHookDeferred, allocator: std.mem.Allocator, out_device_desc: *stream_interfaces.AkDeviceDesc) !void {
        var raw_device_desc: stream_interfaces.NativeAkDeviceDesc = undefined;
        c.WWISEC_AK_StreamMgr_IAkIOHookDeferred_GetDeviceDesc(@ptrCast(self), @ptrCast(&raw_device_desc));
        out_device_desc.* = try stream_interfaces.AkDeviceDesc.fromC(&raw_device_desc, allocator);
    }

    pub fn getDeviceData(self: *IAkIOHookDeferred) u32 {
        return c.WWISEC_AK_StreamMgr_IAkIOHookDeferred_GetDeviceData(@ptrCast(self));
    }

    pub fn batchRead(
        self: *IAkIOHookDeferred,
        in_num_transfers: u32,
        in_transfer_items: [*]BatchIoTransferItem,
        in_batch_io_callback: AkBatchIOCallback,
        io_dispatch_results: [*]common.AKRESULT,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkIOHookDeferred_BatchRead(
                @ptrCast(self),
                in_num_transfers,
                @ptrCast(in_transfer_items),
                @ptrCast(in_batch_io_callback),
                @ptrCast(io_dispatch_results),
            ),
        );
    }

    pub fn batchWrite(
        self: *IAkIOHookDeferred,
        in_num_transfers: u32,
        in_transfer_items: [*]BatchIoTransferItem,
        in_batch_io_callback: AkBatchIOCallback,
        io_dispatch_results: [*]common.AKRESULT,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkIOHookDeferred_BatchWrite(
                @ptrCast(self),
                in_num_transfers,
                @ptrCast(in_transfer_items),
                @ptrCast(in_batch_io_callback),
                @ptrCast(io_dispatch_results),
            ),
        );
    }

    pub fn batchCancel(
        self: *IAkIOHookDeferred,
        in_num_transfers: u32,
        in_transfer_items: [*]BatchIoTransferItem,
        io_cancel_all_transfers_for_this_file: [*]*bool,
    ) void {
        c.WWISEC_AK_StreamMgr_IAkIOHookDeferred_BatchCancel(
            @ptrCast(self),
            in_num_transfers,
            @ptrCast(in_transfer_items),
            @ptrCast(io_cancel_all_transfers_for_this_file),
        );
    }

    pub fn read(
        self: *IAkIOHookDeferred,
        in_file_desc: *AkFileDesc,
        in_heuristics: *AkIoHeuristics,
        io_transfer_info: *AkAsyncIOTransferInfo,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkIOHookDeferred_Read(
                @ptrCast(self),
                @ptrCast(in_file_desc),
                @ptrCast(in_heuristics),
                @ptrCast(io_transfer_info),
            ),
        );
    }

    pub fn write(
        self: *IAkIOHookDeferred,
        in_file_desc: *AkFileDesc,
        in_heuristics: *AkIoHeuristics,
        io_transfer_info: *AkAsyncIOTransferInfo,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkIOHookDeferred_Write(
                @ptrCast(self),
                @ptrCast(in_file_desc),
                @ptrCast(in_heuristics),
                @ptrCast(io_transfer_info),
            ),
        );
    }

    pub fn cancel(
        self: *IAkIOHookDeferred,
        in_file_desc: *AkFileDesc,
        io_transfer_info: *AkAsyncIOTransferInfo,
        io_cancel_all_transfers_for_this_file: *bool,
    ) void {
        c.WWISEC_AK_StreamMgr_IAkIOHookDeferred_Cancel(
            @ptrCast(self),
            @ptrCast(in_file_desc),
            @ptrCast(io_transfer_info),
            io_cancel_all_transfers_for_this_file,
        );
    }

    pub fn createInstance(instance: *anyopaque, function_table: *const FunctionTable) *IAkIOHookDeferred {
        return @ptrCast(
            c.WWISEC_AK_StreamMgr_IAkIOHookDeferred_CreateInstance(instance, @ptrCast(function_table)),
        );
    }

    pub fn destroyInstance(instance: *anyopaque) void {
        c.WWISEC_AK_StreamMgr_IAkIOHookDeferred_DestroyInstance(@ptrCast(instance));
    }
};

pub const IAkFileLocationResolver = opaque {
    pub const FunctionTable = extern struct {
        destructor: *const fn (self: *IAkFileLocationResolver) callconv(.C) void,
        open_string: *const fn (
            self: *IAkFileLocationResolver,
            in_file_name: [*]const common.AkOSChar,
            in_open_mode: stream_interfaces.AkOpenMode,
            in_flags: ?*stream_interfaces.AkFileSystemFlags,
            io_sync_open: *bool,
            io_file_desc: *AkFileDesc,
        ) callconv(.C) common.AKRESULT,
        open_id: *const fn (
            self: *IAkFileLocationResolver,
            in_fileID: common.AkFileID,
            in_open_mode: stream_interfaces.AkOpenMode,
            in_flags: ?*stream_interfaces.AkFileSystemFlags,
            io_sync_open: *bool,
            io_file_desc: *AkFileDesc,
        ) callconv(.C) common.AKRESULT,
        output_searched_paths_string: ?*const fn (
            self: *IAkFileLocationResolver,
            in_result: *const common.AKRESULT,
            in_file_name: [*]const common.AkOSChar,
            in_flags: ?*stream_interfaces.AkFileSystemFlags,
            in_open_mode: stream_interfaces.AkOpenMode,
            out_searched_path: *[*]const common.AkOSChar,
            in_path_size: i32,
        ) callconv(.C) common.AKRESULT = null,
        output_searched_paths_id: ?*const fn (
            self: *IAkFileLocationResolver,
            in_result: *const common.AKRESULT,
            in_file_id: common.AkFileID,
            in_flags: ?*stream_interfaces.AkFileSystemFlags,
            in_open_mode: stream_interfaces.AkOpenMode,
            out_searched_path: *[*]const common.AkOSChar,
            in_path_size: i32,
        ) callconv(.C) common.AKRESULT = null,
    };

    pub fn openString(
        self: *IAkFileLocationResolver,
        fallback_allocator: std.mem.Allocator,
        in_file_name: []const u8,
        in_open_mode: stream_interfaces.AkOpenMode,
        in_flags: ?*stream_interfaces.AkFileSystemFlags,
        io_sync_open: *bool,
        io_file_desc: *AkFileDesc,
    ) common.WwiseError!void {
        var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_oschar_allocator.get();

        var raw_file_name = common.toOSChar(allocator, in_file_name) catch return common.WwiseError.Fail;
        defer allocator.free(raw_file_name);

        try common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkFileLocationResolver_Open_String(
                @ptrCast(self),
                raw_file_name,
                @intFromEnum(in_open_mode),
                @ptrCast(in_flags),
                io_sync_open,
                @ptrCast(io_file_desc),
            ),
        );
    }

    pub fn openId(
        self: *IAkFileLocationResolver,
        in_file_id: common.AkFileID,
        in_open_mode: stream_interfaces.AkOpenMode,
        in_flags: ?*stream_interfaces.AkFileSystemFlags,
        io_sync_open: *bool,
        io_file_desc: *AkFileDesc,
    ) common.WwiseError!void {
        try common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkFileLocationResolver_Open_ID(
                @ptrCast(self),
                in_file_id,
                @intFromEnum(in_open_mode),
                @ptrCast(in_flags),
                io_sync_open,
                @ptrCast(io_file_desc),
            ),
        );
    }

    pub fn outputSearchedPathsString(
        self: *IAkFileLocationResolver,
        allocator: std.mem.Allocator,
        in_result: common.AKRESULT,
        in_filename: []const u8,
        in_flags: ?*stream_interfaces.AkFileSystemFlags,
        in_open_mode: stream_interfaces.AkOpenMode,
        out_searched_path: *[]u8,
    ) common.WwiseError!void {
        var stack_oschar_allocator = common.stackCharAllocator(allocator);
        var oschar_allocator = stack_oschar_allocator.get();

        var raw_filename = common.toOSChar(oschar_allocator, in_filename) catch return common.WwiseError.Fail;
        defer oschar_allocator.free(raw_filename);

        var raw_out_searched_path = allocator.allocSentinel(common.AkOSChar, out_searched_path.len, 0) catch return common.WwiseError.Fail;
        defer allocator.free(raw_out_searched_path);

        try common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkFileLocationResolver_OutputSearchedPaths_String(
                @ptrCast(self),
                @ptrCast(&in_result),
                raw_filename,
                @ptrCast(in_flags),
                @intFromEnum(in_open_mode),
                raw_out_searched_path,
                @intCast(raw_out_searched_path.len),
            ),
        );

        out_searched_path.* = common.fromOSChar(allocator, raw_out_searched_path) catch return common.WwiseError.Fail;
    }

    pub fn outputSearchedPathsID(
        self: *IAkFileLocationResolver,
        allocator: std.mem.Allocator,
        in_result: common.AKRESULT,
        in_file_id: common.AkFileID,
        in_flags: ?*stream_interfaces.AkFileSystemFlags,
        in_open_mode: stream_interfaces.AkOpenMode,
        out_searched_path: *[]u8,
    ) common.WwiseError!void {
        var raw_out_searched_path = allocator.allocSentinel(common.AkOSChar, out_searched_path.len, 0) catch return common.WwiseError.Fail;
        defer allocator.free(raw_out_searched_path);

        try common.handleAkResult(
            c.WWISEC_AK_StreamMgr_IAkFileLocationResolver_OutputSearchedPaths_ID(
                @ptrCast(self),
                @ptrCast(&in_result),
                in_file_id,
                @ptrCast(in_flags),
                @intFromEnum(in_open_mode),
                raw_out_searched_path,
                @intCast(raw_out_searched_path.len),
            ),
        );

        out_searched_path.* = common.fromOSChar(allocator, raw_out_searched_path) catch return common.WwiseError.Fail;
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

pub fn createDevice(in_settings: *const AkDeviceSettings, in_low_level_hook: ?*IAkLowLevelIOHook) common.AkDeviceID {
    return c.WWISEC_AK_StreamMgr_CreateDevice(@ptrCast(in_settings), in_low_level_hook);
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

    var raw_language_name = common.toOSChar(allocator, language_name) catch return common.WwiseError.Fail;
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
