const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const settings = @import("settings.zig");
const stream_interfaces = @import("IAkStreamMgr.zig");

pub const AK_SCHEDULER_BLOCKING = c.WWISEC_AK_SCHEDULER_BLOCKING;
pub const AK_SCHEDULER_DEFERRED_LINED_UP = c.WWISEC_AK_SCHEDULER_DEFERRED_LINED_UP;

pub const AkStreamMgrSettings = extern struct {
    dummy: u8 = 0,

    pub fn fromC(_: c.WWISEC_AkStreamMgrSettings) AkStreamMgrSettings {
        return .{};
    }

    pub fn toC(_: AkStreamMgrSettings) c.WWISEC_AkStreamMgrSettings {
        return std.mem.zeroes(c.WWISEC_AkStreamMgrSettings);
    }
};

pub const AkDeviceSettings = struct {
    io_memory: ?*anyopaque,
    io_memory_size: u32,
    io_memory_alignment: u32,
    pool_attributes: u32,
    granularity: u32,
    scheduler_type_flags: u32,
    thread_properties: settings.AkThreadProperties,
    target_auto_stm_buffer_length: f32,
    max_concurrent_io: u32,
    use_stream_cache: bool,
    max_cache_pinned_bytes: u32,

    pub fn fromC(device_settings: c.WWISEC_AkDeviceSettings) AkDeviceSettings {
        return .{
            .io_memory = device_settings.pIOMemory,
            .io_memory_size = device_settings.uIOMemorySize,
            .io_memory_alignment = device_settings.uIOMemoryAlignment,
            .pool_attributes = device_settings.ePoolAttributes,
            .granularity = device_settings.uGranularity,
            .scheduler_type_flags = device_settings.uSchedulerTypeFlags,
            .thread_properties = settings.AkThreadProperties.fromC(device_settings.threadProperties),
            .target_auto_stm_buffer_length = device_settings.fTargetAutoStmBufferLength,
            .max_concurrent_io = device_settings.uMaxConcurrentIO,
            .use_stream_cache = device_settings.bUseStreamCache,
            .max_cache_pinned_bytes = device_settings.uMaxCachePinnedBytes,
        };
    }

    pub fn toC(self: AkDeviceSettings) c.WWISEC_AkDeviceSettings {
        return .{
            .pIOMemory = self.io_memory,
            .uIOMemorySize = self.io_memory_size,
            .uIOMemoryAlignment = self.io_memory_alignment,
            .ePoolAttributes = self.pool_attributes,
            .uGranularity = self.granularity,
            .uSchedulerTypeFlags = self.scheduler_type_flags,
            .threadProperties = self.thread_properties.toC(),
            .fTargetAutoStmBufferLength = self.target_auto_stm_buffer_length,
            .uMaxConcurrentIO = self.max_concurrent_io,
            .bUseStreamCache = self.use_stream_cache,
            .uMaxCachePinnedBytes = self.max_cache_pinned_bytes,
        };
    }
};

pub const AkFileDesc = struct {
    file_size: i64,
    sector: u64,
    custom_param_size: u32,
    custom_param: ?*anyopaque,
    file_handle: common.AkFileHandle,
    device_id: common.AkDeviceID,
    package: ?*anyopaque,

    pub fn fromC(value: c.WWISEC_AkFileDesc) AkFileDesc {
        return .{
            .file_size = value.iFileSize,
            .sector = value.uSector,
            .custom_param_size = value.uCustomParamSize,
            .custom_param = value.pCustomParam,
            .file_handle = value.hFile,
            .device_id = value.deviceID,
            .package = value.pPackage,
        };
    }

    pub fn toC(self: AkFileDesc) c.WWISEC_AkFileDesc {
        return .{
            .iFileSize = self.file_size,
            .uSector = self.sector,
            .uCustomParamSize = self.custom_param_size,
            .pCustomParam = self.custom_param,
            .hFile = self.file_handle,
            .deviceID = self.device_id,
            .pPackage = self.package,
        };
    }
};

pub const AkIOTransferInfo = struct {
    file_position: u64,
    buffer_size: u32,
    requested_size: u32,

    pub fn fromC(value: c.WWISEC_AkIOTransferInfo) AkIOTransferInfo {
        return .{
            .file_position = value.uFilePosition,
            .buffer_size = value.uBufferSize,
            .requested_size = value.uRequestedSize,
        };
    }

    pub fn toC(self: AkIOTransferInfo) c.WWISEC_AkIOTransferInfo {
        return .{
            .uFilePosition = self.file_position,
            .uBufferSize = self.buffer_size,
            .uRequestedSize = self.requested_size,
        };
    }
};

pub const AkIOCallback = c.WWISEC_AkIOCallback;
pub const AkBatchIOCallback = c.WWISEC_AkBatchIOCallback;

pub const AkAsyncIOTransferInfo = struct {
    base: AkIOTransferInfo,
    buffer: ?*anyopaque,
    callback: AkIOCallback,
    cookie: ?*anyopaque,
    user_data: ?*anyopaque,

    pub fn fromC(value: c.WWISEC_AkAsyncIOTransferInfo) AkAsyncIOTransferInfo {
        return .{
            .base = AkIOTransferInfo.fromC(value.base),
            .buffer = value.pBuffer,
            .callback = value.pCallback,
            .cookie = value.pCookie,
            .user_data = value.pUserData,
        };
    }

    pub fn toC(self: AkAsyncIOTransferInfo) c.WWISEC_AkAsyncIOTransferInfo {
        return .{
            .base = self.base.toC(),
            .pBuffer = self.buffer,
            .pCallback = self.callback,
            .pCookie = self.cookie,
            .pUserData = self.user_data,
        };
    }
};

pub const AkIoHeuristics = struct {
    deadline: f32,
    priority: common.AkPriority,

    pub fn fromC(value: c.WWISEC_AkIoHeuristics) AkIoHeuristics {
        return .{
            .deadline = value.fDeadline,
            .priority = value.priority,
        };
    }

    pub fn toC(self: AkIoHeuristics) c.WWISEC_AkIoHeuristics {
        return .{
            .fDeadline = self.deadline,
            .priority = self.priority,
        };
    }
};

pub const IAkLowLevelIOHook = extern struct {
    __v: *const VTable,

    pub const VTable = extern struct {
        virtual_destructor: common.VirtualDestructor(IAkLowLevelIOHook) = .{},
        close: *const fn (iself: *IAkLowLevelIOHook, in_fileDesc: *c.WWISEC_AkFileDesc) callconv(.C) c.WWISEC_AKRESULT,
        get_block_size: *const fn (iself: *IAkLowLevelIOHook, in_fileDesc: *c.WWISEC_AkFileDesc) callconv(.C) u32,
        get_device_desc: *const fn (iself: *IAkLowLevelIOHook, out_deviceDesc: *c.WWISEC_AkDeviceDesc) callconv(.C) void,
        get_device_data: *const fn (iself: *IAkLowLevelIOHook) callconv(.C) u32,
    };

    pub fn Methods(comptime T: type) type {
        return extern struct {
            pub inline fn toSelf(iself: *const IAkLowLevelIOHook) *const T {
                return @ptrCast(*const T, iself);
            }

            pub inline fn toMutableSelf(iself: *IAkLowLevelIOHook) *T {
                return @ptrCast(*T, iself);
            }

            pub inline fn deinit(self: *T) void {
                @ptrCast(*const IAkLowLevelIOHook.VTable, self.__v).virtual_destructor.call(@ptrCast(*IAkLowLevelIOHook, self));
            }

            pub inline fn close(self: *T, in_file_desc: AkFileDesc) common.WwiseError!void {
                var raw_file_desc = in_file_desc.toC();
                return common.handleAkResult(
                    @ptrCast(*const IAkLowLevelIOHook.VTable, self.__v).close(@ptrCast(*IAkLowLevelIOHook, self), &raw_file_desc),
                );
            }

            pub inline fn getBlockSize(self: *T, in_file_desc: AkFileDesc) u32 {
                var raw_file_desc = in_file_desc.toC();
                return @ptrCast(*const IAkLowLevelIOHook.VTable, self.__v).get_block_size(@ptrCast(*IAkLowLevelIOHook, self), &raw_file_desc);
            }

            pub inline fn getDeviceDesc(self: *T, allocator: std.mem.Allocator, out_device_desc: *stream_interfaces.AkDeviceDesc) !void {
                var raw_device_desc: c.WWISEC_AkDeviceDesc = undefined;
                @ptrCast(*const IAkLowLevelIOHook.VTable, self.__v).get_device_desc(@ptrCast(*IAkLowLevelIOHook, self), &raw_device_desc);
                out_device_desc.* = try stream_interfaces.AkDeviceDesc.fromC(raw_device_desc, allocator);
            }

            pub inline fn getDeviceData(self: *T) u32 {
                return @ptrCast(*const IAkLowLevelIOHook.VTable, self.__v).get_device_data(@ptrCast(*IAkLowLevelIOHook, self));
            }
        };
    }

    pub usingnamespace Methods(@This());
    pub usingnamespace common.CastMethods(@This());
};

// Inherits from IAkLowLevelIOHook
pub const IAkIOHookBlocking = extern struct {
    __v: *const VTable,

    pub const VTable = extern struct {
        virtual_destructor: common.VirtualDestructor(IAkIOHookBlocking) = .{},
        close: *const fn (iself: *IAkIOHookBlocking, in_fileDesc: *c.WWISEC_AkFileDesc) callconv(.C) c.WWISEC_AKRESULT,
        get_block_size: *const fn (iself: *IAkIOHookBlocking, in_fileDesc: *c.WWISEC_AkFileDesc) callconv(.C) u32,
        get_device_desc: *const fn (iself: *IAkIOHookBlocking, out_deviceDesc: *c.WWISEC_AkDeviceDesc) callconv(.C) void,
        get_device_data: *const fn (iself: *IAkIOHookBlocking) callconv(.C) u32,
        read: *const fn (
            iself: *IAkIOHookBlocking,
            in_fileDesc: *c.WWISEC_AkFileDesc,
            in_heuristics: *c.WWISEC_AkIoHeuristics,
            out_pBuffer: ?*anyopaque,
            in_transferInfo: *c.WWISEC_AkIOTransferInfo,
        ) callconv(.C) c.WWWISEC_AKRESULT,
        write: *const fn (
            iself: *IAkIOHookBlocking,
            in_fileDesc: *c.WWISEC_AkFileDesc,
            in_pData: ?*anyopaque,
            in_transferInfo: *c.WWISEC_AkIOTransferInfo,
        ) callconv(.C) c.WWISEC_AKRESULT,
    };

    pub fn Methods(comptime T: type) type {
        return extern struct {
            pub inline fn toSelf(iself: *const IAkIOHookBlocking) *const T {
                return @ptrCast(*const T, iself);
            }

            pub inline fn toMutableSelf(iself: *IAkIOHookBlocking) *T {
                return @ptrCast(*T, iself);
            }

            pub inline fn deinit(self: *T) void {
                @ptrCast(*const IAkIOHookBlocking.VTable, self.__v).virtual_destructor.call(@ptrCast(*IAkIOHookBlocking, self));
            }

            pub inline fn close(self: *T, in_file_desc: AkFileDesc) common.WwiseError!void {
                var raw_file_desc = in_file_desc.toC();
                return common.handleAkResult(
                    @ptrCast(*const IAkIOHookBlocking.VTable, self.__v).close(@ptrCast(*IAkIOHookBlocking, self), &raw_file_desc),
                );
            }

            pub inline fn getBlockSize(self: *T, in_file_desc: AkFileDesc) u32 {
                var raw_file_desc = in_file_desc.toC();
                return @ptrCast(*const IAkIOHookBlocking.VTable, self.__v).get_block_size(@ptrCast(*IAkIOHookBlocking, self), &raw_file_desc);
            }

            pub inline fn getDeviceDesc(self: *T, allocator: std.mem.Allocator, out_device_desc: *stream_interfaces.AkDeviceDesc) !void {
                var raw_device_desc: c.WWISEC_AkDeviceDesc = undefined;
                @ptrCast(*const IAkIOHookBlocking.VTable, self.__v).get_device_desc(@ptrCast(*IAkIOHookBlocking, self), &raw_device_desc);
                out_device_desc.* = try stream_interfaces.AkDeviceDesc.fromC(raw_device_desc, allocator);
            }

            pub inline fn getDeviceData(self: *T) u32 {
                return @ptrCast(*const IAkIOHookBlocking.VTable, self.__v).get_device_data(@ptrCast(*IAkIOHookBlocking, self));
            }

            pub inline fn read(
                self: *T,
                in_file_desc: AkFileDesc,
                in_heuristics: AkIoHeuristics,
                out_buffer: ?*anyopaque,
                io_transfer_info: *AkIOTransferInfo,
            ) common.WwiseError!void {
                var raw_file_desc = in_file_desc.toC();
                var raw_heuristics = in_heuristics.toC();
                var raw_transfer_info = io_transfer_info.toC();

                try common.handleAkResult(
                    @ptrCast(*const IAkIOHookBlocking.VTable, self.__v).read(
                        @ptrCast(*IAkIOHookBlocking, self),
                        &raw_file_desc,
                        &raw_heuristics,
                        out_buffer,
                        &raw_transfer_info,
                    ),
                );
                io_transfer_info.* = AkIOTransferInfo.fromC(raw_transfer_info);
            }

            pub inline fn write(
                self: *T,
                in_file_desc: AkFileDesc,
                in_heuristics: AkIoHeuristics,
                in_data: ?*anyopaque,
                io_transfer_info: *AkIOTransferInfo,
            ) common.WwiseError!void {
                var raw_file_desc = in_file_desc.toC();
                var raw_heuristics = in_heuristics.toC();
                var raw_transfer_info = io_transfer_info.toC();
                try common.handleAkResult(
                    @ptrCast(*const IAkIOHookBlocking.VTable, self.__v).write(
                        @ptrCast(*IAkIOHookBlocking, self),
                        &raw_file_desc,
                        &raw_heuristics,
                        in_data,
                        &raw_transfer_info,
                    ),
                );
                io_transfer_info.* = AkIOTransferInfo.fromC(raw_transfer_info);
            }
        };
    }

    pub usingnamespace Methods(@This());
    pub usingnamespace common.CastMethods(@This());
};

// Inherits from IAkLowLevelIOHook
pub const IAkIOHookDeferredBatch = extern struct {
    __v: *const VTable,

    pub const VTable = extern struct {
        virtual_destructor: common.VirtualDestructor(IAkIOHookDeferredBatch) = .{},
        close: *const fn (iself: *IAkIOHookDeferredBatch, in_fileDesc: *c.WWISEC_AkFileDesc) callconv(.C) c.WWISEC_AKRESULT,
        get_block_size: *const fn (iself: *IAkIOHookDeferredBatch, in_fileDesc: *c.WWISEC_AkFileDesc) callconv(.C) u32,
        get_device_desc: *const fn (iself: *IAkIOHookDeferredBatch, out_deviceDesc: *c.WWISEC_AkDeviceDesc) callconv(.C) void,
        get_device_data: *const fn (iself: *IAkIOHookDeferredBatch) callconv(.C) u32,
        batch_read: *const fn (
            iself: *IAkIOHookDeferredBatch,
            in_num_transfers: u32,
            in_transfer_items: [*]c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem,
            in_batch_io_callback: AkBatchIOCallback,
            io_dispatch_results: [*]c.WWISEC_AKRESULT,
        ) callconv(.C) c.WWISEC_AKRESULT,
        batch_write: *const fn (
            iself: *IAkIOHookDeferredBatch,
            in_num_transfers: u32,
            in_transfer_items: [*]c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem,
            in_batch_io_callback: AkBatchIOCallback,
            io_dispatch_results: [*]c.WWISEC_AKRESULT,
        ) callconv(.C) c.WWISEC_AKRESULT,
        batch_cancel: *const fn (
            iself: *IAkIOHookDeferredBatch,
            in_num_transfers: u32,
            in_transfer_items: [*]c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem,
            io_cancel_all_transfers_for_this_file: [*]*bool,
        ) callconv(.C) void,
    };

    pub fn Methods(comptime T: type) type {
        return extern struct {
            pub inline fn toSelf(iself: *const IAkIOHookDeferredBatch) *const T {
                return @ptrCast(*const T, iself);
            }

            pub inline fn toMutableSelf(iself: *IAkIOHookDeferredBatch) *T {
                return @ptrCast(*T, iself);
            }

            pub inline fn deinit(self: *T) void {
                @ptrCast(*const IAkIOHookDeferredBatch.VTable, self.__v).virtual_destructor.call(@ptrCast(*IAkIOHookDeferredBatch, self));
            }

            pub inline fn close(self: *T, in_file_desc: AkFileDesc) common.WwiseError!void {
                var raw_file_desc = in_file_desc.toC();
                return common.handleAkResult(
                    @ptrCast(*const IAkIOHookDeferredBatch.VTable, self.__v).close(@ptrCast(*IAkIOHookDeferredBatch, self), &raw_file_desc),
                );
            }

            pub inline fn getBlockSize(self: *T, in_file_desc: AkFileDesc) u32 {
                var raw_file_desc = in_file_desc.toC();
                return @ptrCast(*const IAkIOHookDeferredBatch.VTable, self.__v).get_block_size(@ptrCast(*IAkIOHookDeferredBatch, self), &raw_file_desc);
            }

            pub inline fn getDeviceDesc(self: *T, allocator: std.mem.Allocator, out_device_desc: *stream_interfaces.AkDeviceDesc) !void {
                var raw_device_desc: c.WWISEC_AkDeviceDesc = undefined;
                @ptrCast(*const IAkIOHookDeferredBatch.VTable, self.__v).get_device_desc(@ptrCast(*IAkIOHookDeferredBatch, self), &raw_device_desc);
                out_device_desc.* = try stream_interfaces.AkDeviceDesc.fromC(raw_device_desc, allocator);
            }

            pub inline fn getDeviceData(self: *T) u32 {
                return @ptrCast(*const IAkIOHookDeferredBatch.VTable, self.__v).get_device_data(@ptrCast(*IAkIOHookDeferredBatch, self));
            }

            pub inline fn batchRead(
                self: *T,
                in_num_transfers: u32,
                in_transfer_items: [*]c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem,
                in_batch_io_callback: AkBatchIOCallback,
                io_dispatch_results: [*]c.WWISEC_AKRESULT,
            ) common.WwiseError!void {
                return common.handleAkResult(
                    @ptrCast(*const IAkIOHookDeferredBatch.VTable, self.__v).batch_read(
                        @ptrCast(*IAkIOHookDeferredBatch, self),
                        in_num_transfers,
                        in_transfer_items,
                        in_batch_io_callback,
                        io_dispatch_results,
                    ),
                );
            }

            pub inline fn batchWrite(
                self: *T,
                in_num_transfers: u32,
                in_transfer_items: [*]c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem,
                in_batch_io_callback: AkBatchIOCallback,
                io_dispatch_results: [*]c.WWISEC_AKRESULT,
            ) common.WwiseError!void {
                return common.handleAkResult(
                    @ptrCast(*const IAkIOHookDeferredBatch.VTable, self.__v).batch_write(
                        @ptrCast(*IAkIOHookDeferredBatch, self),
                        in_num_transfers,
                        in_transfer_items,
                        in_batch_io_callback,
                        io_dispatch_results,
                    ),
                );
            }

            pub inline fn batchCancel(
                self: *T,
                in_num_transfers: u32,
                in_transfer_items: [*]c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem,
                io_cancel_all_transfers_for_this_file: [*]*bool,
            ) void {
                @ptrCast(*const IAkIOHookDeferredBatch.VTable, self.__v).batch_cancel(
                    @ptrCast(*IAkIOHookDeferredBatch, self),
                    in_num_transfers,
                    in_transfer_items,
                    io_cancel_all_transfers_for_this_file,
                );
            }
        };
    }

    pub const BatchIoTransferItem = c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem;

    pub usingnamespace Methods(@This());
    pub usingnamespace common.CastMethods(@This());
};

// Inherits from IAkIOHookDeferredBatch
pub const IAkIOHookDeferred = extern struct {
    __v: *const VTable,

    pub const VTable = extern struct {
        virtual_destructor: common.VirtualDestructor(IAkIOHookDeferred) = .{},
        close: *const fn (iself: *IAkIOHookDeferred, in_fileDesc: *c.WWISEC_AkFileDesc) callconv(.C) c.WWISEC_AKRESULT,
        get_block_size: *const fn (iself: *IAkIOHookDeferred, in_fileDesc: *c.WWISEC_AkFileDesc) callconv(.C) u32,
        get_device_desc: *const fn (iself: *IAkIOHookDeferred, out_deviceDesc: *c.WWISEC_AkDeviceDesc) callconv(.C) void,
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
            in_fileDesc: *c.WWISEC_AkFileDesc,
            in_heuristics: *c.WWISEC_AkIoHeuristics,
            io_transferInfo: *c.WWISEC_AkAsyncIOTransferInfo,
        ) callconv(.C) c.WWWISEC_AKRESULT,
        write: *const fn (
            iself: *IAkIOHookDeferred,
            in_fileDesc: *c.WWISEC_AkFileDesc,
            in_heuristics: *c.WWISEC_AkIoHeuristics,
            io_transferInfo: *c.WWISEC_AkAsyncIOTransferInfo,
        ) callconv(.C) c.WWISEC_AKRESULT,
        cancel: *const fn (
            iself: *IAkIOHookDeferred,
            in_fileDesc: *c.WWISEC_AkFileDesc,
            io_transferInfo: *c.WWISEC_AkAsyncIOTransferInfo,
            io_bCancelAllTransfersForThisFile: *bool,
        ) callconv(.C) void,
    };

    pub fn Methods(comptime T: type) type {
        return extern struct {
            pub inline fn toSelf(iself: *const IAkIOHookDeferred) *const T {
                return @ptrCast(*const T, iself);
            }

            pub inline fn toMutableSelf(iself: *IAkIOHookDeferred) *T {
                return @ptrCast(*T, iself);
            }

            pub inline fn deinit(self: *T) void {
                @ptrCast(*const IAkIOHookDeferred.VTable, self.__v).virtual_destructor.call(@ptrCast(*IAkIOHookDeferred, self));
            }

            pub inline fn close(self: *T, in_file_desc: AkFileDesc) common.WwiseError!void {
                var raw_file_desc = in_file_desc.toC();
                return common.handleAkResult(
                    @ptrCast(*const IAkIOHookDeferred.VTable, self.__v).close(@ptrCast(*IAkIOHookDeferred, self), &raw_file_desc),
                );
            }

            pub inline fn getBlockSize(self: *T, in_file_desc: AkFileDesc) u32 {
                var raw_file_desc = in_file_desc.toC();
                return @ptrCast(*const IAkIOHookDeferred.VTable, self.__v).get_block_size(@ptrCast(*IAkIOHookDeferred, self), &raw_file_desc);
            }

            pub inline fn getDeviceDesc(self: *T, allocator: std.mem.Allocator, out_device_desc: *stream_interfaces.AkDeviceDesc) !void {
                var raw_device_desc: c.WWISEC_AkDeviceDesc = undefined;
                @ptrCast(*const IAkIOHookDeferred.VTable, self.__v).get_device_desc(@ptrCast(*IAkIOHookDeferred, self), &raw_device_desc);
                out_device_desc.* = try stream_interfaces.AkDeviceDesc.fromC(raw_device_desc, allocator);
            }

            pub inline fn getDeviceData(self: *T) u32 {
                return @ptrCast(*const IAkIOHookDeferred.VTable, self.__v).get_device_data(@ptrCast(*IAkIOHookDeferred, self));
            }

            pub inline fn batchRead(
                self: *T,
                in_num_transfers: u32,
                in_transfer_items: [*]c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem,
                in_batch_io_callback: AkBatchIOCallback,
                io_dispatch_results: [*]c.WWISEC_AKRESULT,
            ) common.WwiseError!void {
                return common.handleAkResult(
                    @ptrCast(*const IAkIOHookDeferred.VTable, self.__v).batch_read(
                        @ptrCast(*IAkIOHookDeferred, self),
                        in_num_transfers,
                        in_transfer_items,
                        in_batch_io_callback,
                        io_dispatch_results,
                    ),
                );
            }

            pub inline fn batchWrite(
                self: *T,
                in_num_transfers: u32,
                in_transfer_items: [*]c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem,
                in_batch_io_callback: AkBatchIOCallback,
                io_dispatch_results: [*]c.WWISEC_AKRESULT,
            ) common.WwiseError!void {
                return common.handleAkResult(
                    @ptrCast(*const IAkIOHookDeferredBatch.VTable, self.__v).batch_write(
                        @ptrCast(*IAkIOHookDeferredBatch, self),
                        in_num_transfers,
                        in_transfer_items,
                        in_batch_io_callback,
                        io_dispatch_results,
                    ),
                );
            }

            pub inline fn batchCancel(
                self: *T,
                in_num_transfers: u32,
                in_transfer_items: [*]c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem,
                io_cancel_all_transfers_for_this_file: [*]*bool,
            ) void {
                @ptrCast(*const IAkIOHookDeferred.VTable, self.__v).batch_cancel(
                    @ptrCast(*IAkIOHookDeferred, self),
                    in_num_transfers,
                    in_transfer_items,
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

                try common.handleAkResult(@ptrCast(*const IAkIOHookDeferred.VTable, self.__v).read(
                    @ptrCast(*IAkIOHookDeferred, self),
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

                try common.handleAkResult(@ptrCast(*const IAkIOHookDeferred.VTable, self.__v).write(
                    @ptrCast(*IAkIOHookDeferred, self),
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

                @ptrCast(*const IAkIOHookDeferred.VTable, self.__v).write(
                    @ptrCast(*IAkIOHookDeferred, self),
                    &raw_file_desc,
                    &raw_transfer_info,
                    io_cancel_all_transfers_for_this_file,
                );

                io_file_desc.* = AkFileDesc.fromC(raw_file_desc);
                io_transfer_info.* = AkAsyncIOTransferInfo.fromC(raw_transfer_info);
            }
        };
    }

    pub const BatchIoTransferItem = c.WWISEC_AK_StreamMgr_IAkIOHookDeferredBatch_BatchIoTransferItem;

    pub usingnamespace Methods(@This());
    pub usingnamespace common.CastMethods(@This());
};

pub const IAkFileLocationResolver = extern struct {
    __v: *const VTable,

    pub const VTable = extern struct {
        virtual_destructor: common.VirtualDestructor(IAkFileLocationResolver) = .{},
        open_string: *const fn (
            iself: *IAkFileLocationResolver,
            in_file_name: [*]const c.AkOsChar,
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
            in_file_name: [*]const c.AkOsChar,
            in_flags: ?*c.WWISEC_AkFileSystemFlags,
            in_open_mode: c.WWISEC_AkOpenMode,
            out_searched_path: *[*]const c.AkOsChar,
            in_path_size: i32,
        ) callconv(.C) c.WWISEC_AKRESULT,
        output_searched_paths_id: *const fn (
            iself: *IAkFileLocationResolver,
            in_result: *c.WWISEC_AKRESULT,
            in_file_id: c.WWISEC_AkFileID,
            in_flags: ?*c.WWISEC_AkFileSystemFlags,
            in_open_mode: c.WWISEC_AkOpenMode,
            out_searched_path: *[*]const c.AkOsChar,
            in_path_size: i32,
        ) callconv(.C) c.WWISEC_AKRESULT,
    };

    pub fn Methods(comptime T: type) type {
        return extern struct {
            pub inline fn toSelf(iself: *const IAkFileLocationResolver) *const T {
                return @ptrCast(*const T, iself);
            }

            pub inline fn toMutableSelf(iself: *IAkFileLocationResolver) *T {
                return @ptrCast(*T, iself);
            }

            pub inline fn deinit(self: *T) void {
                @ptrCast(*const IAkFileLocationResolver.VTable, self.__v).virtual_destructor.call(@ptrCast(*IAkFileLocationResolver, self));
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
                    @ptrCast(*const IAkFileLocationResolver.VTable, self.__v).open_string(
                        @ptrCast(*IAkFileLocationResolver, self),
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
                    @ptrCast(*const IAkFileLocationResolver.VTable, self.__v).open_id(
                        @ptrCast(*IAkFileLocationResolver, self),
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
    return @ptrCast(?*stream_interfaces.IAkStreamMgr, @alignCast(
        @alignOf(?*stream_interfaces.IAkStreamMgr),
        c.WWISEC_AK_StreamMgr_Create(@ptrCast([*c]c.WWISEC_AkStreamMgrSettings, in_settings)),
    ));
}

pub fn getDefaultSettings(out_settings: *AkStreamMgrSettings) void {
    var temp_raw_settings: c.WWISEC_AkStreamMgrSettings = undefined;
    c.WWISEC_AK_StreamMgr_GetDefaultSettings(&temp_raw_settings);

    out_settings.* = AkStreamMgrSettings.fromC(temp_raw_settings);
}

pub fn getFileLocationResolver() ?*IAkFileLocationResolver {
    return @ptrCast(?*IAkFileLocationResolver, c.WWISEC_AK_StreamMgr_GetFileLocationResolver());
}

pub fn setFileLocationResolver(in_file_location_resolver: ?*IAkFileLocationResolver) void {
    c.WWISEC_AK_StreamMgr_SetFileLocationResolver(in_file_location_resolver);
}

pub fn createDevice(in_settings: AkDeviceSettings, in_low_level_hook: ?*IAkLowLevelIOHook) common.AkDeviceID {
    var raw_settings = in_settings.toC();
    return c.WWISEC_AK_StreamMgr_CreateDevice(&raw_settings, in_low_level_hook);
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
    var temp_raw_settings: c.WWISEC_AkDeviceSettings = undefined;
    c.WWISEC_AK_StreamMgr_GetDefaultDeviceSettings(&temp_raw_settings);

    out_settings.* = AkDeviceSettings.fromC(temp_raw_settings);
}

pub fn setCurrentLanguage(fallback_allocator: std.mem.Allocator, language_name: []const u8) common.WwiseError!void {
    var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_oschar_allocator.get();

    var raw_language_name = common.toOSChar(allocator, language_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_language_name);

    return common.handleAkResult(
        c.WWISEC_AK_StreamMgr_SetCurrentLanguage(raw_language_name),
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
