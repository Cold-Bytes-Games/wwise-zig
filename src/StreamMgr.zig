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
        destructor: *const fn (iself: *IAkLowLevelIOHook) callconv(.C) void,
        close: *const fn (iself: *IAkLowLevelIOHook, in_file_desc: *AkFileDesc) callconv(.C) common.AKRESULT,
        get_block_size: *const fn (iself: *IAkLowLevelIOHook, in_file_desc: *AkFileDesc) callconv(.C) u32,
        get_device_desc: *const fn (iself: *IAkLowLevelIOHook, out_device_desc: *stream_interfaces.NativeAkDeviceDesc) callconv(.C) void,
        get_device_data: *const fn (iself: *IAkLowLevelIOHook) callconv(.C) u32,
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
        destructor: *const fn (iself: *IAkIOHookBlocking) callconv(.C) void,
        close: *const fn (iself: *IAkIOHookBlocking, in_file_desc: *AkFileDesc) callconv(.C) common.AKRESULT,
        get_block_size: *const fn (iself: *IAkIOHookBlocking, in_file_desc: *AkFileDesc) callconv(.C) u32,
        get_device_desc: *const fn (iself: *IAkIOHookBlocking, out_device_desc: *stream_interfaces.NativeAkDeviceDesc) callconv(.C) void,
        get_device_data: *const fn (iself: *IAkIOHookBlocking) callconv(.C) u32,
        read: *const fn (
            iself: *IAkIOHookBlocking,
            in_file_desc: *AkFileDesc,
            in_heuristics: *AkIoHeuristics,
            out_buffer: ?*anyopaque,
            in_transfer_info: *AkIOTransferInfo,
        ) callconv(.C) common.AKRESULT,
        write: *const fn (
            iself: *IAkIOHookBlocking,
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
        destructor: *const fn (iself: *IAkIOHookBlocking) callconv(.C) void,
        close: *const fn (iself: *IAkIOHookBlocking, in_file_desc: *AkFileDesc) callconv(.C) common.AKRESULT,
        get_block_size: *const fn (iself: *IAkIOHookBlocking, in_file_desc: *AkFileDesc) callconv(.C) u32,
        get_device_desc: *const fn (iself: *IAkIOHookBlocking, out_device_desc: *stream_interfaces.NativeAkDeviceDesc) callconv(.C) void,
        get_device_data: *const fn (iself: *IAkIOHookBlocking) callconv(.C) u32,
        batch_read: *const fn (
            iself: *IAkIOHookDeferredBatch,
            in_num_transfers: u32,
            in_transfer_items: [*]BatchIoTransferItem,
            in_batch_io_callback: AkBatchIOCallback,
            io_dispatch_results: [*]common.AKRESULT,
        ) callconv(.C) common.AKRESULT,
        batch_write: *const fn (
            iself: *IAkIOHookDeferredBatch,
            in_num_transfers: u32,
            in_transfer_items: [*]BatchIoTransferItem,
            in_batch_io_callback: AkBatchIOCallback,
            io_dispatch_results: [*]common.AKRESULT,
        ) callconv(.C) common.AKRESULT,
        batch_cancel: *const fn (
            iself: *IAkIOHookDeferredBatch,
            in_num_transfers: u32,
            in_transfer_items: [*]BatchIoTransferItem,
            io_cancel_all_transfers_for_this_file: [*]*bool,
        ) callconv(.C) void,
    };

    pub const BatchIoTransferItem = extern struct {
        file_desc: ?*AkFileDesc = null,
        io_heuristics: AkIoHeuristics = .{},
        transfer_info: ?[*]AkAsyncIOTransferInfo = null,
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
pub const IAkIOHookDeferred = extern struct {
    __v: *const VTable,

    pub const VTable = extern struct {
        virtual_destructor: common.VirtualDestructor(IAkIOHookDeferred) = .{},
        close: *const fn (iself: *IAkIOHookDeferred, in_file_desc: *c.WWISEC_AkFileDesc) callconv(.C) c.WWISEC_AKRESULT,
        get_block_size: *const fn (iself: *IAkIOHookDeferred, in_file_desc: *c.WWISEC_AkFileDesc) callconv(.C) u32,
        get_device_desc: *const fn (iself: *IAkIOHookDeferred, out_device_desc: *c.WWISEC_AkDeviceDesc) callconv(.C) void,
        get_device_data: *const fn (iself: *IAkIOHookDeferred) callconv(.C) u32,
        batch_read: *const fn (
            iself: *IAkIOHookDeferred,
            in_num_transfers: u32,
            in_transfer_items: [*]c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem,
            in_batch_io_callback: AkBatchIOCallback,
            io_dispatch_results: [*]c.WWISEC_AKRESULT,
        ) callconv(.C) c.WWISEC_AKRESULT,
        batch_write: *const fn (
            iself: *IAkIOHookDeferred,
            in_num_transfers: u32,
            in_transfer_items: [*]c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem,
            in_batch_io_callback: AkBatchIOCallback,
            io_dispatch_results: [*]c.WWISEC_AKRESULT,
        ) callconv(.C) c.WWISEC_AKRESULT,
        batch_cancel: *const fn (
            iself: *IAkIOHookDeferred,
            in_num_transfers: u32,
            in_transfer_items: [*]c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem,
            io_cancel_all_transfers_for_this_file: [*]*bool,
        ) callconv(.C) void,
        read: *const fn (
            iself: *IAkIOHookDeferred,
            in_file_desc: *c.WWISEC_AkFileDesc,
            in_heuristics: *c.WWISEC_AkIoHeuristics,
            io_transferInfo: *c.WWISEC_AkAsyncIOTransferInfo,
        ) callconv(.C) c.WWISEC_AKRESULT,
        write: *const fn (
            iself: *IAkIOHookDeferred,
            in_file_desc: *c.WWISEC_AkFileDesc,
            in_heuristics: *c.WWISEC_AkIoHeuristics,
            io_transferInfo: *c.WWISEC_AkAsyncIOTransferInfo,
        ) callconv(.C) c.WWISEC_AKRESULT,
        cancel: *const fn (
            iself: *IAkIOHookDeferred,
            in_file_desc: *c.WWISEC_AkFileDesc,
            io_transferInfo: *c.WWISEC_AkAsyncIOTransferInfo,
            io_bCancelAllTransfersForThisFile: *bool,
        ) callconv(.C) void,
    };

    pub fn Methods(comptime T: type) type {
        return extern struct {
            pub inline fn toSelf(iself: *const IAkIOHookDeferred) *const T {
                return @ptrCast(iself);
            }

            pub inline fn toMutableSelf(iself: *IAkIOHookDeferred) *T {
                return @ptrCast(iself);
            }

            pub inline fn deinit(self: *T) void {
                @as(*const IAkIOHookDeferred.VTable, @ptrCast(self.__v)).virtual_destructor.call(@ptrCast(self));
            }

            pub inline fn close(self: *T, in_file_desc: AkFileDesc) common.WwiseError!void {
                var raw_file_desc = in_file_desc.toC();
                return common.handleAkResult(
                    @as(*const IAkIOHookDeferred.VTable, @ptrCast(self.__v)).close(@ptrCast(self), &raw_file_desc),
                );
            }

            pub inline fn getBlockSize(self: *T, in_file_desc: AkFileDesc) u32 {
                var raw_file_desc = in_file_desc.toC();
                return @as(*const IAkIOHookDeferred.VTable, @ptrCast(self.__v)).get_block_size(@ptrCast(self), &raw_file_desc);
            }

            pub inline fn getDeviceDesc(self: *T, allocator: std.mem.Allocator, out_device_desc: *stream_interfaces.AkDeviceDesc) !void {
                var raw_device_desc: c.WWISEC_AkDeviceDesc = undefined;
                @as(*const IAkIOHookDeferred.VTable, @ptrCast(self.__v)).get_device_desc(@ptrCast(self), &raw_device_desc);
                out_device_desc.* = try stream_interfaces.AkDeviceDesc.fromC(raw_device_desc, allocator);
            }

            pub inline fn getDeviceData(self: *T) u32 {
                return @as(*const IAkIOHookDeferred.VTable, @ptrCast(self.__v)).get_device_data(@ptrCast(self));
            }

            pub inline fn batchRead(
                self: *T,
                in_num_transfers: u32,
                in_transfer_items: [*]BatchIoTransferItem,
                in_batch_io_callback: AkBatchIOCallback,
                io_dispatch_results: [*]c.WWISEC_AKRESULT,
            ) common.WwiseError!void {
                return common.handleAkResult(
                    @as(*const IAkIOHookDeferred.VTable, @ptrCast(self.__v)).batch_read(
                        @as(*IAkIOHookDeferred, @ptrCast(self)),
                        in_num_transfers,
                        @as([*]c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem, @ptrCast(in_transfer_items)),
                        in_batch_io_callback,
                        io_dispatch_results,
                    ),
                );
            }

            pub inline fn batchWrite(
                self: *T,
                in_num_transfers: u32,
                in_transfer_items: [*]BatchIoTransferItem,
                in_batch_io_callback: AkBatchIOCallback,
                io_dispatch_results: [*]c.WWISEC_AKRESULT,
            ) common.WwiseError!void {
                return common.handleAkResult(
                    @as(*const IAkIOHookDeferredBatch.VTable, @ptrCast(self.__v)).batch_write(
                        @ptrCast(self),
                        in_num_transfers,
                        @ptrCast(in_transfer_items),
                        in_batch_io_callback,
                        io_dispatch_results,
                    ),
                );
            }

            pub inline fn batchCancel(
                self: *T,
                in_num_transfers: u32,
                in_transfer_items: [*]BatchIoTransferItem,
                io_cancel_all_transfers_for_this_file: [*]*bool,
            ) void {
                @as(*const IAkIOHookDeferred.VTable, @ptrCast(self.__v)).batch_cancel(
                    @ptrCast(self),
                    in_num_transfers,
                    @ptrCast(in_transfer_items),
                    io_cancel_all_transfers_for_this_file,
                );
            }

            pub inline fn read(
                self: *T,
                io_file_desc: *AkFileDesc,
                in_heuristics: AkIoHeuristics,
                io_transfer_info: *AkAsyncIOTransferInfo,
            ) common.WwiseError!void {
                var raw_file_desc = io_file_desc.toC();
                var raw_heuristics = in_heuristics.toC();
                var raw_transfer_info = io_transfer_info.toC();

                try common.handleAkResult(@as(*const IAkIOHookDeferred.VTable, @ptrCast(self.__v)).read(
                    @ptrCast(self),
                    &raw_file_desc,
                    &raw_heuristics,
                    &raw_transfer_info,
                ));

                io_file_desc.* = AkFileDesc.fromC(raw_file_desc);
                io_transfer_info.* = AkAsyncIOTransferInfo.fromC(raw_transfer_info);
            }

            pub inline fn write(
                self: *T,
                io_file_desc: *AkFileDesc,
                in_heuristics: AkIoHeuristics,
                io_transfer_info: *AkAsyncIOTransferInfo,
            ) common.WwiseError!void {
                var raw_file_desc = io_file_desc.toC();
                var raw_heuristics = in_heuristics.toC();
                var raw_transfer_info = io_transfer_info.toC();

                try common.handleAkResult(@as(*const IAkIOHookDeferred.VTable, @ptrCast(self.__v)).write(
                    @ptrCast(self),
                    &raw_file_desc,
                    &raw_heuristics,
                    &raw_transfer_info,
                ));

                io_file_desc.* = AkFileDesc.fromC(raw_file_desc);
                io_transfer_info.* = AkAsyncIOTransferInfo.fromC(raw_transfer_info);
            }

            pub inline fn cancel(
                self: *T,
                io_file_desc: *AkFileDesc,
                io_transfer_info: *AkAsyncIOTransferInfo,
                io_cancel_all_transfers_for_this_file: *bool,
            ) void {
                var raw_file_desc = io_file_desc.toC();
                var raw_transfer_info = io_transfer_info.toC();

                @as(*const IAkIOHookDeferred.VTable, @ptrCast(self.__v)).write(
                    @ptrCast(self),
                    &raw_file_desc,
                    &raw_transfer_info,
                    io_cancel_all_transfers_for_this_file,
                );

                io_file_desc.* = AkFileDesc.fromC(raw_file_desc);
                io_transfer_info.* = AkAsyncIOTransferInfo.fromC(raw_transfer_info);
            }
        };
    }

    pub const BatchIoTransferItem = extern struct {
        file_desc: ?*AkFileDesc,
        io_heuristics: AkIoHeuristics,
        transfer_info: ?*AkAsyncIOTransferInfo,

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

    pub usingnamespace Methods(@This());
    pub usingnamespace common.CastMethods(@This());
};

pub const IAkFileLocationResolver = extern struct {
    __v: *const VTable,

    pub const VTable = extern struct {
        virtual_destructor: common.VirtualDestructor(IAkFileLocationResolver) = .{},
        open_string: *const fn (
            iself: *IAkFileLocationResolver,
            in_file_name: [*]const c.AkOSChar,
            in_openMode: c.WWISEC_AkOpenMode,
            in_flags: ?*c.WWISEC_AkFileSystemFlags,
            io_syncOpen: *bool,
            io_fileDesc: *c.WWISEC_AkFileDesc,
        ) callconv(.C) c.WWISEC_AKRESULT,
        open_id: *const fn (
            iself: *IAkFileLocationResolver,
            in_fileID: c.WWISEC_AkFileID,
            in_openMode: c.WWISEC_AkOpenMode,
            in_flags: ?*c.WWISEC_AkFileSystemFlags,
            io_syncOpen: *bool,
            io_fileDesc: *c.WWISEC_AkFileDesc,
        ) callconv(.C) c.WWISEC_AKRESULT,
        output_searched_paths_string: *const fn (
            iself: *IAkFileLocationResolver,
            in_result: *c.WWISEC_AKRESULT,
            in_file_name: [*]const c.AkOSChar,
            in_flags: ?*c.WWISEC_AkFileSystemFlags,
            in_open_mode: c.WWISEC_AkOpenMode,
            out_searched_path: *[*]const c.AkOSChar,
            in_path_size: i32,
        ) callconv(.C) c.WWISEC_AKRESULT,
        output_searched_paths_id: *const fn (
            iself: *IAkFileLocationResolver,
            in_result: *c.WWISEC_AKRESULT,
            in_file_id: c.WWISEC_AkFileID,
            in_flags: ?*c.WWISEC_AkFileSystemFlags,
            in_open_mode: c.WWISEC_AkOpenMode,
            out_searched_path: *[*]const c.AkOSChar,
            in_path_size: i32,
        ) callconv(.C) c.WWISEC_AKRESULT,
    };

    pub fn Methods(comptime T: type) type {
        return extern struct {
            pub inline fn toSelf(iself: *const IAkFileLocationResolver) *const T {
                return @ptrCast(iself);
            }

            pub inline fn toMutableSelf(iself: *IAkFileLocationResolver) *T {
                return @ptrCast(iself);
            }

            pub inline fn deinit(self: *T) void {
                @as(*const IAkFileLocationResolver.VTable, @ptrCast(self.__v)).virtual_destructor.call(@ptrCast(self));
            }

            pub inline fn openString(
                self: *T,
                fallback_allocator: std.mem.Allocator,
                in_file_name: []const u8,
                in_open_mode: stream_interfaces.AkOpenMode,
                in_flags: ?stream_interfaces.AkFileSystemFlags,
                io_sync_open: *bool,
                io_file_desc: *AkFileDesc,
            ) common.WwiseError!void {
                var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
                var allocator = stack_oschar_allocator.get();

                var raw_file_name = common.toOSChar(allocator, in_file_name) catch return common.WwiseError.Fail;
                defer allocator.free(raw_file_name);

                var raw_flags = blk: {
                    if (in_flags) |flags| {
                        var raw_c_flags = flags.toC();
                        break :blk &raw_c_flags;
                    }

                    break :blk @as(?*c.WWISEC_AkFileSystemFlags, null);
                };

                var raw_file_desc = io_file_desc.toC();

                try common.handleAkResult(
                    @as(*const IAkFileLocationResolver.VTable, @ptrCast(self.__v)).open_string(
                        @ptrCast(self),
                        raw_file_name,
                        in_open_mode,
                        raw_flags,
                        io_sync_open,
                        &raw_file_desc,
                    ),
                );

                io_file_desc.* = AkFileDesc.fromC(raw_file_desc);
            }

            pub inline fn openId(
                self: *T,
                in_file_id: common.AkFileID,
                in_open_mode: stream_interfaces.AkOpenMode,
                in_flags: ?stream_interfaces.AkFileSystemFlags,
                io_sync_open: *bool,
                io_file_desc: *AkFileDesc,
            ) common.WwiseError!void {
                var raw_flags = blk: {
                    if (in_flags) |flags| {
                        var raw_c_flags = flags.toC();
                        break :blk &raw_c_flags;
                    }

                    break :blk @as(?*c.WWISEC_AkFileSystemFlags, null);
                };

                var raw_file_desc = io_file_desc.toC();

                try common.handleAkResult(
                    @as(*const IAkFileLocationResolver.VTable, @ptrCast(self.__v)).open_id(
                        @ptrCast(self),
                        in_file_id,
                        in_open_mode,
                        raw_flags,
                        io_sync_open,
                        &raw_file_desc,
                    ),
                );

                io_file_desc.* = AkFileDesc.fromC(raw_file_desc);
            }

            // TODO: Implement OutputSearchedPaths wrappers (not used by the default IO hooks)
        };
    }

    pub usingnamespace Methods(@This());
    pub usingnamespace common.CastMethods(@This());
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
