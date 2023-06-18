const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const settings = @import("settings.zig");

pub const AkStmStatus = enum(common.DefaultEnumType) {
    idle = c.WWISEC_AK_StmStatusIdle,
    completed = c.WWISEC_AK_StmStatusCompleted,
    pending = c.WWISEC_AK_StmStatusPending,
    cancelled = c.WWISEC_AK_StmStatusCancelled,
    @"error" = c.WWISEC_AK_StmStatusError,
};

pub const AkMoveMethod = enum(common.DefaultEnumType) {
    begin = c.WWISEC_AK_MoveBegin,
    current = c.WWISEC_AK_MoveCurrent,
    end = c.WWISEC_AK_MoveEnd,
};

pub const AkOpenMode = enum(common.DefaultEnumType) {
    read = c.WWISEC_AK_OpenModeRead,
    write = c.WWISEC_AK_OpenModeWrite,
    write_ovrwr = c.WWISEC_AK_OpenModeWriteOvrwr,
    read_write = c.WWISEC_AK_OpenModeReadWrite,
};

pub const AkFileSystemFlags = extern struct {
    company_id: u32 = 0,
    codec_id: u32 = 0,
    custom_param_size: u32 = 0,
    custom_param: ?*anyopaque = null,
    is_language_specific: bool = false,
    is_automatic_stream: bool = false,
    cache_id: common.AkFileID = common.AK_INVALID_FILE_ID,
    num_bytes_prefetch: u32 = 0,
    directory_hash: u32 = common.AK_INVALID_UNIQUE_ID,

    pub fn fromC(value: c.WWISEC_AkFileSystemFlags) AkFileSystemFlags {
        return @bitCast(AkFileSystemFlags, value);
    }

    pub fn toC(self: AkFileSystemFlags) c.WWISEC_AkFileSystemFlags {
        return @bitCast(c.WWISEC_AkFileSystemFlags, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkFileSystemFlags) == @sizeOf(c.WWISEC_AkFileSystemFlags));
    }
};

pub const AkStreamInfo = struct {
    device_id: common.AkDeviceID = 0,
    name: []const u8,
    size: u64 = 0,
    is_open: bool = false,

    pub fn deinit(self: AkStreamInfo, allocator: std.mem.Allocator) void {
        allocator.free(self.name);
    }

    pub fn fromC(value: c.WWISEC_AkStreamInfo, allocator: std.mem.Allocator) !AkStreamInfo {
        return .{
            .device_id = value.deviceID,
            .name = try common.fromOSChar(allocator, value.pszName),
            .size = value.uSize,
            .is_open = value.bIsOpen,
        };
    }

    pub fn toC(self: AkStreamInfo, allocator: std.mem.Allocator) !c.WWISEC_AkStreamInfo {
        return .{
            .deviceID = self.device_id,
            .pszName = try common.toOSChar(allocator, self.name),
            .uSize = self.size,
            .bIsOpen = self.is_open,
        };
    }
};

pub const AkAutoStmHeuristics = extern struct {
    throughput: f32 = 0.0,
    loop_start: u32 = 0,
    loop_end: u32 = 0,
    min_num_buffers: u8 = 0,
    priority: common.AkPriority = 0,

    pub fn fromC(value: c.WWISEC_AkAutoStmHeuristics) AkAutoStmHeuristics {
        return @bitCast(AkAutoStmHeuristics, value);
    }

    pub fn toC(self: AkAutoStmHeuristics) c.WWISEC_AkAutoStmHeuristics {
        return @bitCast(c.WWISEC_AkAutoStmHeuristics, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkAutoStmHeuristics) == @sizeOf(c.WWISEC_AkAutoStmHeuristics));
    }
};

pub const AkAutoStmBufSettings = extern struct {
    buffer_size: u32 = 0,
    min_buffer_size: u32 = 0,
    block_size: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_AkAutoStmBufSettings) AkAutoStmBufSettings {
        return @bitCast(AkAutoStmBufSettings, value);
    }

    pub inline fn toC(self: AkAutoStmBufSettings) c.WWISEC_AkAutoStmBufSettings {
        return @bitCast(c.WWISEC_AkAutoStmBufSettings, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkAutoStmBufSettings) == @sizeOf(c.WWISEC_AkAutoStmBufSettings));
    }
};

pub const AkDeviceDesc = struct {
    device_id: common.AkDeviceID = 0,
    can_write: bool = false,
    can_read: bool = false,
    device_name: []const u8,

    pub fn fromC(value: c.WWISEC_AkDeviceDesc, allocator: std.mem.Allocator) !AkDeviceDesc {
        return .{
            .device_id = value.deviceID,
            .can_write = value.bCanWrite,
            .can_read = value.bCanRead,
            .device_name = try std.unicode.utf16leToUtf8Alloc(allocator, value.szDeviceName[0..value.uStringSize]),
        };
    }

    pub fn toC(self: AkDeviceDesc) !c.WWISEC_AkDeviceDesc {
        var result: c.WWISEC_AkDeviceDesc = undefined;

        result.deviceID = self.device_id;
        result.bCanWrite = self.can_write;
        result.bCanRead = self.can_read;

        @memset(&result.szDeviceName, 0);
        result.uStringSize = @truncate(u32, try std.unicode.utf8ToUtf16Le(&result.szDeviceName, self.device_name));

        return result;
    }
};

pub const AkDeviceData = extern struct {
    device_id: common.AkDeviceID = 0,
    mem_size: u32 = 0,
    mem_used: u32 = 0,
    allocs: u32 = 0,
    frees: u32 = 0,
    peak_refd_mem_used: u32 = 0,
    unreferenced_cached_bytes: u32 = 0,
    granularity: u32 = 0,
    num_active_streams: u32 = 0,
    total_bytes_transferred: u32 = 0,
    low_level_bytes_transferred: u32 = 0,
    avg_cache_efficiency: f32 = 0.0,
    num_low_level_requests_completed: u32 = 0,
    num_low_level_requests_cancelled: u32 = 0,
    num_low_level_requests_pending: u32 = 0,
    custom_param: u32 = 0,
    cache_pinned_bytes: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_AkDeviceData) AkDeviceData {
        return @bitCast(AkDeviceData, value);
    }

    pub inline fn toC(self: AkDeviceData) c.WWISEC_AkDeviceData {
        return @bitCast(c.WWISEC_AkDeviceData, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkDeviceData) == @sizeOf(c.WWISEC_AkDeviceData));
    }
};

pub const AkStreamRecord = struct {
    stream_id: u32 = 0,
    device_id: common.AkDeviceID = 0,
    stream_name: []const u8,
    file_size: u64 = 0,
    custom_param_size: u32 = 0,
    custom_param: u32 = 0,
    is_auto_stream: bool = false,
    is_caching_stream: bool = false,

    pub fn fromC(value: c.WWISEC_AkStreamRecord, allocator: std.mem.Allocator) !AkStreamRecord {
        return .{
            .stream_id = value.uStreamID,
            .device_id = value.deviceID,
            .stream_name = try std.unicode.utf16leToUtf8Alloc(allocator, value.szStreamName[0..]),
            .file_size = value.uFileSize,
            .custom_param_size = value.uCustomParamSize,
            .custom_param = value.uCustomParam,
            .is_auto_stream = value.bIsAutoStream,
            .is_caching_stream = value.bIsCachingStream,
        };
    }

    pub fn toC(self: AkStreamRecord) !c.WWISEC_AkStreamRecord {
        var result: c.WWISEC_AkStreamRecord = undefined;

        @memset(&result.szStreamName, 0);
        result.uStringSize = @truncate(u32, try std.unicode.utf8ToUtf16Le(&result.szStreamName, self.stream_name));

        result.uStreamID = self.stream_id;
        result.deviceID = self.device_id;
        result.uFileSize = self.file_size;
        result.uCustomParamSize = self.custom_param_size;
        result.uCustomParam = self.custom_param;
        result.bIsAutoStream = self.is_auto_stream;
        result.bIsCachingStream = self.is_caching_stream;

        return result;
    }
};

pub const AkStreamData = extern struct {
    stream_id: u32 = 0,
    priority: u32 = 0,
    file_position: u64 = 0,
    target_buffering_size: u32 = 0,
    virtual_buffering_size: u32 = 0,
    buffered_size: u32 = 0,
    num_bytes_transfered: u32 = 0,
    num_bytes_transfered_low_level: u32 = 0,
    memory_referenced: u32 = 0,
    estimated_throughput: f32 = 0.0,
    active: bool = false,

    pub inline fn fromC(value: c.WWISEC_AkStreamData) AkStreamData {
        return @bitCast(AkStreamData, value);
    }

    pub inline fn toC(self: AkStreamData) c.WWISEC_AkStreamData {
        return @bitCast(c.WWISEC_AkStreamData, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkStreamData) == @sizeOf(c.WWISEC_AkStreamData));
    }
};

pub const IAkStreamProfile = extern struct {
    __v: *const VTable,

    pub const VTable = extern struct {
        virtual_destructor: common.VirtualDestructor(IAkStreamProfile) = .{},
        get_stream_record: *const fn (self: *IAkStreamProfile, out_streamRecord: *c.WWISEC_AkStreamRecord) callconv(.C) void,
        get_stream_data: *const fn (self: *IAkStreamProfile, ouut_streamData: *c.WWISEC_AkStreamData) callconv(.C) void,
        is_new: *const fn (self: *IAkStreamProfile) callconv(.C) bool,
        clear_new: *const fn (self: *IAkStreamProfile) callconv(.C) void,
    };

    pub fn Methods(comptime T: type) type {
        return extern struct {
            pub inline fn toSelf(iself: *const IAkStreamProfile) *const T {
                return @ptrCast(*const T, iself);
            }

            pub inline fn toMutableSelf(iself: *IAkStreamProfile) *T {
                return @ptrCast(*T, iself);
            }

            pub inline fn deinit(self: *T) void {
                @ptrCast(*const IAkStreamProfile.VTable, self.__v).virtual_destructor.call(@ptrCast(*IAkStreamProfile, self));
            }

            pub inline fn getStreamRecord(self: *T, allocator: std.mem.Allocator, out_stream_record: *AkStreamRecord) !void {
                var raw_stream_record: c.WWISEC_AkStreamRecord = undefined;
                @ptrCast(*const IAkStreamProfile.VTable, self.__v).get_stream_record(@ptrCast(*IAkStreamProfile, self), &raw_stream_record);
                out_stream_record.* = try AkStreamRecord.fromC(raw_stream_record, allocator);
            }

            pub inline fn getStreamData(self: *T, out_stream_data: *AkStreamData) void {
                var raw_stream_data: c.WWISEC_AkStreamData = undefined;
                @ptrCast(*const IAkStreamProfile.VTable, self.__v).get_stream_data(@ptrCast(*IAkStreamProfile, self), &raw_stream_data);
                out_stream_data.* = AkStreamData.fromC(raw_stream_data);
            }

            pub inline fn isNew(self: *T) bool {
                return @ptrCast(*const IAkStreamProfile.VTable, self.__v).is_new(@ptrCast(*IAkStreamProfile, self));
            }

            pub inline fn clearNew(self: *T) void {
                @ptrCast(*const IAkStreamProfile.VTable, self.__v).clear_new(@ptrCast(*IAkStreamProfile, self));
            }
        };
    }

    pub usingnamespace Methods(@This());
    pub usingnamespace common.CastMethods(@This());
};

pub const IAkDeviceProfile = extern struct {
    __v: *const VTable,

    pub const VTable = extern struct {
        virtual_destructor: common.VirtualDestructor(IAkDeviceProfile) = .{},
        on_profile_start: *const fn (iself: *IAkDeviceProfile) callconv(.C) void,
        on_profile_end: *const fn (iself: *IAkDeviceProfile) callconv(.C) void,
        get_desc: *const fn (iself: *IAkDeviceProfile, out_device_desc: *c.WWISEC_AkDeviceDesc) callconv(.C) void,
        get_data: *const fn (iself: *IAkDeviceProfile, out_device_data: *c.WWISEC_AkDeviceData) callconv(.C) void,
        is_new: *const fn (iself: *IAkDeviceProfile) callconv(.C) bool,
        clear_new: *const fn (iself: *IAkDeviceProfile) callconv(.C) void,
        get_num_streams: *const fn (iself: *IAkDeviceProfile) callconv(.C) u32,
        get_stream_profile: *const fn (iself: *IAkDeviceProfile, in_stream_index: u32) callconv(.C) ?*IAkStreamProfile,
    };

    pub fn Methods(comptime T: type) type {
        return extern struct {
            pub inline fn toSelf(iself: *const IAkDeviceProfile) *const T {
                return @ptrCast(*const T, iself);
            }

            pub inline fn toMutableSelf(iself: *IAkDeviceProfile) *T {
                return @ptrCast(*T, iself);
            }

            pub inline fn deinit(self: *T) void {
                @ptrCast(*const IAkDeviceProfile.VTable, self.__v).virtual_destructor.call(@ptrCast(*IAkDeviceProfile, self));
            }

            pub inline fn onProfileStart(self: *T) void {
                @ptrCast(*const IAkDeviceProfile.VTable, self.__v).on_profile_start(@ptrCast(*IAkDeviceProfile, self));
            }

            pub inline fn onProfileEnd(self: *T) void {
                @ptrCast(*const IAkDeviceProfile.VTable, self.__v).on_profile_end(@ptrCast(*IAkDeviceProfile, self));
            }

            pub inline fn getDesc(self: *T, allocator: std.mem.Allocator, out_device_desc: *AkDeviceDesc) !void {
                var raw_device_desc: c.WWISEC_AkDeviceDesc = undefined;
                @ptrCast(*const IAkDeviceProfile.VTable, self.__v).get_desc(@ptrCast(*IAkDeviceProfile, self), &raw_device_desc);
                out_device_desc.* = try AkDeviceDesc.fromC(raw_device_desc, allocator);
            }

            pub inline fn getData(self: *T, out_device_data: *AkDeviceData) void {
                var raw_device_data: c.WWISEC_AkDeviceData = undefined;
                @ptrCast(*const IAkDeviceProfile.VTable, self.__v).get_data(@ptrCast(*IAkDeviceProfile, self), &raw_device_data);
                out_device_data.* = AkDeviceData.fromC(raw_device_data);
            }

            pub inline fn isNew(self: *T) bool {
                return @ptrCast(*const IAkDeviceProfile.VTable, self.__v).is_new(@ptrCast(*IAkDeviceProfile, self));
            }

            pub inline fn clearNew(self: *T) void {
                @ptrCast(*const IAkDeviceProfile.VTable, self.__v).clear_new(@ptrCast(*IAkDeviceProfile, self));
            }

            pub inline fn getNumStreams(self: *T) u32 {
                return @ptrCast(*const IAkDeviceProfile.VTable, self.__v).get_num_streams(@ptrCast(*IAkDeviceProfile, self));
            }

            pub inline fn getStreamProfile(self: *T, in_stream_index: u32) ?*IAkStreamProfile {
                return @ptrCast(*const IAkDeviceProfile.VTable, self.__v).get_stream_profile(@ptrCast(*IAkDeviceProfile, self), in_stream_index);
            }
        };
    }

    pub usingnamespace Methods(@This());
    pub usingnamespace common.CastMethods(@This());
};

pub const IAkStreamMgrProfile = extern struct {
    __v: *const VTable,

    pub const VTable = extern struct {
        virtual_destructor: common.VirtualDestructor(IAkStreamMgrProfile) = .{},
        start_monitoring: *const fn (iself: *IAkStreamMgrProfile) callconv(.C) c.WWISEC_AKRESULT,
        stop_monitoring: *const fn (iself: *IAkStreamMgrProfile) callconv(.C) void,
        get_num_devices: *const fn (iself: *IAkStreamMgrProfile) callconv(.C) u32,
        get_device_profile: *const fn (iself: *IAkStreamMgrProfile) callconv(.C) ?*IAkDeviceProfile,
    };

    pub fn Methods(comptime T: type) type {
        return extern struct {
            pub inline fn toSelf(iself: *const IAkStreamMgrProfile) *const T {
                return @ptrCast(*const T, iself);
            }

            pub inline fn toMutableSelf(iself: *IAkStreamMgrProfile) *T {
                return @ptrCast(*T, iself);
            }

            pub inline fn deinit(self: *T) void {
                @ptrCast(*const IAkStreamMgrProfile.VTable, self.__v).virtual_destructor.call(@ptrCast(*IAkStreamMgrProfile, self));
            }

            pub inline fn startMonitoring(self: *T) common.WwiseError!void {
                return common.handleAkResult(
                    @ptrCast(*const IAkStreamMgrProfile.VTable, self.__v).start_monitoring(@ptrCast(*IAkStreamMgrProfile, self)),
                );
            }

            pub inline fn stopMonitoring(self: *T) void {
                @ptrCast(*const IAkStreamMgrProfile.VTable, self.__v).stop_monitoring(@ptrCast(*IAkStreamMgrProfile, self));
            }

            pub inline fn getNumDevices(self: *T) u32 {
                return @ptrCast(*const IAkStreamMgrProfile.VTable, self.__v).get_num_devices(@ptrCast(*IAkStreamMgrProfile, self));
            }

            pub inline fn getDeviceProfile(self: *T) ?*IAkDeviceProfile {
                return @ptrCast(*const IAkStreamMgrProfile.VTable, self.__v).get_device_profile(@ptrCast(*IAkStreamMgrProfile, self));
            }
        };
    }

    pub usingnamespace Methods(@This());
    pub usingnamespace common.CastMethods(@This());
};

pub const IAkStdStream = extern struct {
    __v: *const VTable,

    pub const VTable = extern struct {
        virtual_destructor: common.VirtualDestructor(IAkStdStream) = .{},
        destroy: *const fn (iself: *IAkStdStream) callconv(.C) void,
        get_info: *const fn (iself: *IAkStdStream, out_info: *c.WWISEC_AkStreamInfo) callconv(.C) void,
        get_file_descriptor: *const fn (iself: *IAkStdStream) callconv(.C) ?*anyopaque,
        set_stream_name: *const fn (iself: *IAkStdStream, in_stream_name: [*:0]const c.AkOSChar) callconv(.C) c.WWISEC_AKRESULT,
        get_block_size: *const fn (iself: *IAkStdStream) callconv(.C) u32,
        read: *const fn (iself: *IAkStdStream, in_buffer: ?*anyopaque, in_req_size: u32, in_wait: bool, in_priority: c.WWISEC_AkPriority, in_deadline: f32, out_size: *u32) callconv(.C) c.WWISEC_AKRESULT,
        write: *const fn (iself: *IAkStdStream, in_buffer: ?*anyopaque, in_req_size: u32, in_wait: bool, in_priority: c.WWISEC_AkPriority, in_deadline: f32, out_size: *u32) callconv(.C) c.WWISEC_AKRESULT,
        get_position: *const fn (iself: *IAkStdStream, out_end_of_stream: *bool) callconv(.C) u64,
        set_position: *const fn (iself: *IAkStdStream, in_move_offset: i64, in_move_method: c.WWISEC_AkMoveMethod, out_real_offset: *i64) callconv(.C) c.WWISEC_AKRESULT,
        cancel: *const fn (iself: *IAkStdStream) callconv(.C) void,
        get_data: *const fn (iself: *IAkStdStream, out_size: *u32) callconv(.C) ?*anyopaque,
        get_status: *const fn (iself: *IAkStdStream) callconv(.C) c.WWISEC_AkStmStatus,
        wait_for_pending_operation: *const fn (iself: *IAkStdStream) callconv(.C) c.WWISEC_AkStmStatus,
    };

    pub fn Methods(comptime T: type) type {
        return extern struct {
            pub inline fn toSelf(iself: *const IAkStdStream) *const T {
                return @ptrCast(*const T, iself);
            }

            pub inline fn toMutableSelf(iself: *IAkStdStream) *T {
                return @ptrCast(*T, iself);
            }

            pub inline fn deinit(self: *T) void {
                @ptrCast(*const IAkStdStream.VTable, self.__v).virtual_destructor.call(@ptrCast(*IAkStdStream, self));
            }

            pub inline fn destroy(self: *T) void {
                @ptrCast(*const IAkStdStream.VTable, self.__v).destroy(@ptrCast(*IAkStdStream, self));
            }

            pub inline fn getInfo(self: *T, allocator: std.mem.Allocator) !AkStreamInfo {
                var raw_stream_info: c.WWISEC_AkStreamInfo = undefined;
                @ptrCast(*const IAkStdStream.VTable, self.__v).get_info(@ptrCast(*IAkStdStream, self), &raw_stream_info);
                return try AkStreamInfo.fromC(raw_stream_info, allocator);
            }

            pub inline fn getFileDescriptor(self: *T) ?*anyopaque {
                return @ptrCast(*const IAkStdStream.VTable, self.__v).get_file_descriptor(@ptrCast(*IAkStdStream, self));
            }

            pub inline fn setStreamName(self: *T, fallback_allocator: std.mem.Allocator, stream_name: []const u8) common.WwiseError!void {
                var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
                var allocator = stack_oschar_allocator.get();

                var raw_stream_name = common.toOSChar(allocator, stream_name) catch return common.WwiseError.Fail;
                defer allocator.free(raw_stream_name);

                return common.handleAkResult(
                    @ptrCast(*const IAkStdStream.VTable, self.__v).set_stream_name(@ptrCast(*IAkStdStream, self), raw_stream_name),
                );
            }

            pub inline fn getBlockSize(self: *T) u32 {
                return @ptrCast(*const IAkStdStream.VTable, self.__v).get_block_size(@ptrCast(*IAkStdStream, self));
            }

            pub inline fn read(self: *T, in_buffer: ?*anyopaque, in_req_size: u32, in_wait: bool, in_priority: common.AkPriority, in_deadline: f32, out_size: *u32) common.WwiseError!void {
                return common.handleAkResult(
                    @ptrCast(*const IAkStdStream.VTable, self.__v).read(
                        @ptrCast(*IAkStdStream, self),
                        in_buffer,
                        in_req_size,
                        in_wait,
                        in_priority,
                        in_deadline,
                        out_size,
                    ),
                );
            }

            pub inline fn write(self: *T, in_buffer: ?*anyopaque, in_req_size: u32, in_wait: bool, in_priority: common.AkPriority, in_deadline: f32, out_size: *u32) common.WwiseError!void {
                return common.handleAkResult(
                    @ptrCast(*const IAkStdStream.VTable, self.__v).write(
                        @ptrCast(*IAkStdStream, self),
                        in_buffer,
                        in_req_size,
                        in_wait,
                        in_priority,
                        in_deadline,
                        out_size,
                    ),
                );
            }

            pub inline fn getPosition(self: *T, out_end_of_stream: *bool) u64 {
                return @ptrCast(*const IAkStdStream.VTable, self.__v).get_position(@ptrCast(*IAkStdStream, self), out_end_of_stream);
            }

            pub inline fn setPosition(self: *T, in_move_offset: i64, in_move_method: AkMoveMethod, out_real_offset: *i64) common.WwiseError!void {
                return common.handleAkResult(
                    @ptrCast(*const IAkStdStream.VTable, self.__v).set_position(@ptrCast(*IAkStdStream, self), in_move_offset, @enumToInt(in_move_method), out_real_offset),
                );
            }

            pub inline fn cancel(self: *T) void {
                @ptrCast(*const IAkStdStream.VTable, self.__v).cancel(@ptrCast(*IAkStdStream, self));
            }

            pub inline fn getData(self: *T, out_size: *u32) ?*anyopaque {
                return @ptrCast(*const IAkStdStream.VTable, self.__v).get_data(@ptrCast(*IAkStdStream, self), out_size);
            }

            pub inline fn getStatus(self: *T) AkStmStatus {
                return @intToEnum(AkStmStatus, @ptrCast(*const IAkStdStream.VTable, self.__v).get_status(@ptrCast(*IAkStdStream, self)));
            }

            pub inline fn waitForPendingOperation(self: *T) AkStmStatus {
                return @intToEnum(AkStmStatus, @ptrCast(*const IAkStdStream.VTable, self.__v).wait_for_pending_operation(@ptrCast(*IAkStdStream, self)));
            }
        };
    }

    pub usingnamespace Methods(@This());
    pub usingnamespace common.CastMethods(@This());
};

pub const IAkAutoStream = extern struct {
    __v: *const VTable,

    pub const VTable = extern struct {
        virtual_destructor: common.VirtualDestructor(IAkAutoStream) = .{},
        destroy: *const fn (iself: *IAkAutoStream) callconv(.C) void,
        get_info: *const fn (iself: *IAkAutoStream, out_info: *c.WWISEC_AkStreamInfo) callconv(.C) void,
        get_file_descriptor: *const fn (iself: *IAkAutoStream) callconv(.C) ?*anyopaque,
        get_heuristics: *const fn (iself: *IAkAutoStream, out_heuristics: *c.WWISEC_AkAutoStmHeuristics) callconv(.C) void,
        set_heuristics: *const fn (iself: *IAkAutoStream, in_heuristics: *c.WWISEC_AkAutoStmHeuristics) callconv(.C) void,
        set_minimal_buffer_size: *const fn (iself: *IAkAutoStream, in_min_buffer_size: u32) callconv(.C) void,
        set_min_target_buffer_size: *const fn (iself: *IAkAutoStream, in_min_target_buffer_size: u32) callconv(.C) void,
        set_stream_name: *const fn (iself: *IAkAutoStream, in_stream_name: [*:0]const c.AkOSChar) callconv(.C) c.WWISEC_AKRESULT,
        get_block_size: *const fn (iself: *IAkAutoStream) callconv(.C) u32,
        query_buffering_status: *const fn (iself: *IAkAutoStream, out_num_bytes_available: *u32) callconv(.C) c.WWISEC_AKRESULT,
        get_nominal_buffering: *const fn (iself: *IAkAutoStream) callconv(.C) u32,
        start: *const fn (iself: *IAkAutoStream) callconv(.C) c.WWISEC_AKRESULT,
        stop: *const fn (iself: *IAkAutoStream) callconv(.C) c.WWISEC_AKRESULT,
        get_position: *const fn (iself: *IAkAutoStream, out_end_of_stream: *bool) callconv(.C) u64,
        set_position: *const fn (iself: *IAkAutoStream, in_move_offset: i64, in_move_method: c.WWISEC_AkMoveMethod, out_real_offset: *i64) callconv(.C) c.WWISEC_AKRESULT,
        get_buffer: *const fn (iself: *IAkAutoStream, out_buffer: *?*anyopaque, out_size: *u32, in_wait: bool) callconv(.C) c.WWISEC_AKRESULT,
        release_buffer: *const fn (iself: *IAkAutoStream) callconv(.C) c.WWISEC_AKRESULT,
    };

    pub fn Methods(comptime T: type) type {
        return extern struct {
            pub inline fn toSelf(iself: *const IAkAutoStream) *const T {
                return @ptrCast(*const T, iself);
            }

            pub inline fn toMutableSelf(iself: *IAkAutoStream) *T {
                return @ptrCast(*T, iself);
            }

            pub inline fn deinit(self: *T) void {
                @ptrCast(*const IAkAutoStream.VTable, self.__v).virtual_destructor.call(@ptrCast(*IAkAutoStream, self));
            }

            pub inline fn destroy(self: *T) void {
                @ptrCast(*const IAkAutoStream.VTable, self.__v).destroy(@ptrCast(*IAkAutoStream, self));
            }

            pub inline fn getInfo(self: *T, allocator: std.mem.Allocator, out_info: *AkStreamInfo) !void {
                var raw_stream_info: c.WWISEC_AkStreamInfo = undefined;
                @ptrCast(*const IAkAutoStream.VTable, self.__v).get_info(@ptrCast(*IAkAutoStream, self), &raw_stream_info);
                out_info.* = try AkStreamInfo.fromC(raw_stream_info, allocator);
            }

            pub inline fn getFileDescriptor(self: *T) ?*anyopaque {
                return @ptrCast(*const IAkAutoStream.VTable, self.__v).get_file_descriptor(@ptrCast(*IAkAutoStream, self));
            }

            pub inline fn getHeuristics(self: *T, out_heuristics: *AkAutoStmHeuristics) void {
                @ptrCast(*const IAkAutoStream.VTable, self.__v).get_heuristics(@ptrCast(*IAkAutoStream, self), @ptrCast(*c.WWISEC_AkAutoStmHeuristics, out_heuristics));
            }

            pub inline fn setHeuristics(self: *T, in_heuristics: *AkAutoStmHeuristics) void {
                @ptrCast(*const IAkAutoStream.VTable, self.__v).set_heuristics(@ptrCast(*IAkAutoStream, self), @ptrCast(*c.WWISEC_AkAutoStmHeuristics, in_heuristics));
            }

            pub inline fn setMinimalBufferSize(self: *T, in_min_buffer_size: u32) void {
                @ptrCast(*const IAkAutoStream.VTable, self.__v).set_minimal_buffer_size(@ptrCast(*IAkAutoStream, self), in_min_buffer_size);
            }

            pub inline fn setMinTargetBufferSize(self: *T, in_min_target_buffer_size: u32) void {
                @ptrCast(*const IAkAutoStream.VTable, self.__v).set_min_target_buffer_size(@ptrCast(*IAkAutoStream, self), in_min_target_buffer_size);
            }

            pub inline fn setStreamName(self: *T, fallback_allocator: std.mem.Allocator, stream_name: []const u8) common.WwiseError!void {
                var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
                var allocator = stack_oschar_allocator.get();

                var raw_stream_name = common.toOSChar(allocator, stream_name) catch return common.WwiseError.Fail;
                defer allocator.free(raw_stream_name);

                return common.handleAkResult(
                    @ptrCast(*const IAkAutoStream.VTable, self.__v).set_stream_name(@ptrCast(*IAkAutoStream, self), raw_stream_name),
                );
            }

            pub inline fn getBlockSize(self: *T) u32 {
                return @ptrCast(*const IAkAutoStream.VTable, self.__v).get_block_size(@ptrCast(*IAkAutoStream, self));
            }

            pub inline fn queryBufferingStatus(self: *T, out_num_bytes_available: *u32) common.WwiseError!void {
                return common.handleAkResult(
                    @ptrCast(*const IAkAutoStream.VTable, self.__v).query_buffering_status(@ptrCast(*IAkAutoStream, self), out_num_bytes_available),
                );
            }

            pub inline fn getNominalBuffering(self: *T) u32 {
                return @ptrCast(*const IAkAutoStream.VTable, self.__v).get_nominal_buffering(@ptrCast(*IAkAutoStream, self));
            }

            pub inline fn start(self: *T) common.WwiseError!void {
                return common.handleAkResult(
                    @ptrCast(*const IAkAutoStream.VTable, self.__v).start(@ptrCast(*IAkAutoStream, self)),
                );
            }

            pub inline fn stop(self: *T) common.WwiseError!void {
                return common.handleAkResult(
                    @ptrCast(*const IAkAutoStream.VTable, self.__v).stop(@ptrCast(*IAkAutoStream, self)),
                );
            }

            pub inline fn getPosition(self: *T, out_end_of_stream: *bool) u64 {
                return @ptrCast(*const IAkAutoStream.VTable, self.__v).get_position(@ptrCast(*IAkAutoStream, self), out_end_of_stream);
            }

            pub inline fn setPosition(self: *T, in_move_offset: i64, in_move_method: AkMoveMethod, out_real_offset: *i64) common.WwiseError!void {
                return common.handleAkResult(
                    @ptrCast(*const IAkAutoStream.VTable, self.__v).set_position(@ptrCast(*IAkAutoStream, self), in_move_offset, @enumToInt(in_move_method), out_real_offset),
                );
            }

            pub inline fn getBuffer(self: *T, out_buffer: *?*anyopaque, out_size: *u32, in_wait: bool) common.WwiseError!void {
                return common.handleAkResult(
                    @ptrCast(*const IAkAutoStream.VTable, self.__v).set_position(@ptrCast(*IAkAutoStream, self), out_buffer, out_size, in_wait),
                );
            }

            pub inline fn releaseBuffer(self: *T) common.WwiseError!void {
                return common.handleAkResult(
                    @ptrCast(*const IAkAutoStream.VTable, self.__v).release_buffer(@ptrCast(*IAkAutoStream, self)),
                );
            }
        };
    }

    pub usingnamespace Methods(@This());
    pub usingnamespace common.CastMethods(@This());
};

pub const IAkStreamMgr = extern struct {
    __v: *const VTable,

    pub const VTable = extern struct {
        virtual_destructor: common.VirtualDestructor(IAkStreamMgr) = .{},
        destroy: *const fn (
            self: *IAkStreamMgr,
        ) callconv(.C) void,
        get_stream_mgr_profile: *const fn (
            self: *IAkStreamMgr,
        ) callconv(.C) ?*IAkStreamMgrProfile,
        create_str_id: *const fn (
            self: *IAkStreamMgr,
            in_fileID: c.WWISEC_AkFileID,
            in_pFSFlags: ?*c.WWISEC_AkFileSystemFlags,
            in_eOpenMode: AkOpenMode,
            out_pStream: *?*IAkStdStream,
            in_bSyncOpen: bool,
        ) callconv(.C) c.WWISEC_AKRESULT,
        create_std_string: *const fn (
            self: *IAkStreamMgr,
            in_pszFileName: [*c]const c.AkOSChar,
            in_pFSFlags: ?*c.WWISEC_AkFileSystemFlags,
            in_eOpenMode: AkOpenMode,
            out_pStream: *?*IAkStdStream,
            in_bSyncOpen: bool,
        ) callconv(.C) c.WWISEC_AKRESULT,
        create_auto_string: *const fn (
            self: *IAkStreamMgr,
            in_pszFileName: [*c]const c.AkOSChar,
            in_pFSFlags: ?*c.WWISEC_AkFileSystemFlags,
            in_heuristics: *const c.WWISEC_AkAutoStmHeuristics,
            in_pBufferSettings: ?*c.WWISEC_AkAutoStmBufSettings,
            out_pStream: *?*IAkAutoStream,
            in_bSyncOpen: bool,
        ) callconv(.C) c.WWISEC_AKRESULT,
        create_auto_id: *const fn (
            self: *IAkStreamMgr,
            in_fileID: c.WWISEC_AkFileID,
            in_pFSFlags: ?*c.WWISEC_AkFileSystemFlags,
            in_heuristics: *const c.WWISEC_AkAutoStmHeuristics,
            in_pBufferSettings: ?*c.WWISEC_AkAutoStmBufSettings,
            out_pStream: *?*IAkAutoStream,
            in_bSyncOpen: bool,
        ) callconv(.C) c.WWISEC_AKRESULT,
        create_auto_memory: *const fn (
            self: *IAkStreamMgr,
            in_pBuffer: ?*anyopaque,
            in_uSize: c.AkUInt64,
            in_heuristics: *const c.WWISEC_AkAutoStmHeuristics,
            out_pStream: *?*IAkAutoStream,
        ) callconv(.C) c.WWISEC_AKRESULT,
        pin_file_in_cache: *const fn (
            self: *IAkStreamMgr,
            in_fileID: c.WWISEC_AkFileID,
            in_pFSFlags: ?*c.WWISEC_AkFileSystemFlags,
            in_uPriority: c.WWISEC_AkPriority,
        ) callconv(.C) c.WWISEC_AKRESULT,
        unpin_file_in_cache: *const fn (
            self: *IAkStreamMgr,
            in_fileID: c.WWISEC_AkFileID,
            in_uPriority: c.WWISEC_AkPriority,
        ) callconv(.C) c.WWISEC_AKRESULT,
        update_caching_priority: *const fn (
            self: *IAkStreamMgr,
            in_fileID: c.WWISEC_AkFileID,
            in_uPriority: c.WWISEC_AkPriority,
            in_uOldPriority: c.WWISEC_AkPriority,
        ) callconv(.C) c.WWISEC_AKRESULT,
        get_buffer_status_for_pinned_file: *const fn (
            self: *IAkStreamMgr,
            in_fileID: c.WWISEC_AkFileID,
            out_fPercentBuffered: *c.AkReal32,
            out_bCacheFull: *bool,
        ) callconv(.C) c.WWISEC_AKRESULT,
        relocate_memory_stream: *const fn (
            self: *IAkStreamMgr,
            in_pStream: *IAkAutoStream,
            in_pNewStart: ?*anyopaque,
        ) callconv(.C) c.WWISEC_AKRESULT,
    };

    pub fn Methods(comptime T: type) type {
        return extern struct {
            pub inline fn toSelf(iself: *const IAkStreamMgr) *const T {
                return @ptrCast(*const T, iself);
            }

            pub inline fn toMutableSelf(iself: *IAkStreamMgr) *T {
                return @ptrCast(*T, iself);
            }

            pub inline fn deinit(self: *T) void {
                @ptrCast(*const IAkStreamMgr.VTable, self.__v).virtual_destructor.call(@ptrCast(*IAkStreamMgr, self));
            }

            pub inline fn destroy(self: *T) void {
                @ptrCast(*const IAkStreamMgr.VTable, self.__v).destroy(@ptrCast(*IAkStreamMgr, self));
            }

            pub inline fn getStreamMgrProfile(self: *T) ?*IAkStreamMgrProfile {
                return @ptrCast(*const IAkStreamMgr.VTable, self.__v).get_stream_mgr_profile(@ptrCast(*IAkStreamMgr, self));
            }

            pub fn createStdString(
                self: *T,
                fallback_allocator: std.mem.Allocator,
                in_pszFileName: []const u8,
                in_pFSFlags: ?AkFileSystemFlags,
                in_eOpenMode: AkOpenMode,
                out_pStream: *?*IAkStdStream,
                in_bSyncOpen: bool,
            ) common.WwiseError!void {
                var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
                var allocator = stack_char_allocator.get();

                const filename_oschar = common.toOSChar(allocator, in_pszFileName) catch return common.WwiseError.Fail;
                defer allocator.free(filename_oschar);

                var raw_fsflags_ptr: ?*c.WWISEC_AkFileSystemFlags = blk: {
                    if (in_pFSFlags) |fs_flags| {
                        var raw_fsflags = fs_flags.toC();
                        break :blk &raw_fsflags;
                    }
                    break :blk null;
                };

                return common.handleAkResult(@ptrCast(*const IAkStreamMgr.VTable, self.__v).create_std_string(
                    @ptrCast(*IAkStreamMgr, self),
                    @ptrCast([*]const c.AkOSChar, filename_oschar),
                    raw_fsflags_ptr,
                    in_eOpenMode,
                    out_pStream,
                    in_bSyncOpen,
                ));
            }

            pub inline fn createStdId(
                self: *T,
                in_fileID: c.WWISEC_AkFileID,
                in_pFSFlags: ?*c.WWISEC_AkFileSystemFlags,
                in_eOpenMode: AkOpenMode,
                out_pStream: *?*IAkStdStream,
                in_bSyncOpen: bool,
            ) common.WwiseError!void {
                return common.handleAkResult(@ptrCast(*const IAkStreamMgr.VTable, self.__v).create_str_id(
                    @ptrCast(*IAkStreamMgr, self),
                    in_fileID,
                    in_pFSFlags,
                    in_eOpenMode,
                    out_pStream,
                    in_bSyncOpen,
                ));
            }

            pub fn createAutoString(
                self: *T,
                fallback_allocator: std.mem.Allocator,
                in_pszFileName: []const u8,
                in_pFSFlags: ?AkFileSystemFlags,
                in_heuristics: AkAutoStmHeuristics,
                in_pBufferSettings: ?AkAutoStmBufSettings,
                out_pStream: *?*IAkAutoStream,
                in_bSyncOpen: bool,
            ) common.WwiseError!void {
                var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
                var allocator = stack_char_allocator.get();

                const filename_oschar = try common.toOSChar(allocator, in_pszFileName);
                defer allocator.free(filename_oschar);

                const raw_heuristics = in_heuristics.toC();

                var raw_fsflags_ptr: ?*c.WWISEC_AkFileSystemFlags = blk: {
                    if (in_pFSFlags) |fs_flags| {
                        var raw_fsflags = fs_flags.toC();
                        break :blk &raw_fsflags;
                    }
                    break :blk null;
                };

                var raw_buffer_settings: ?*c.WWISEC_AkAutoStmBufSettings = blk: {
                    if (in_pBufferSettings) |buffer_settings| {
                        var raw_settings = buffer_settings.toC();
                        break :blk &raw_settings;
                    }
                    break :blk null;
                };

                return common.handleAkResult(@ptrCast(*const IAkStreamMgr.VTable, self.__v).create_auto_string(
                    @ptrCast(*IAkStreamMgr, self),
                    filename_oschar,
                    raw_fsflags_ptr,
                    &raw_heuristics,
                    raw_buffer_settings,
                    out_pStream,
                    in_bSyncOpen,
                ));
            }

            pub fn createAutoId(
                self: *T,
                in_fileID: c.WWISEC_AkFileID,
                in_pFSFlags: ?AkFileSystemFlags,
                in_heuristics: AkAutoStmHeuristics,
                in_pBufferSettings: ?*c.WWISEC_AkAutoStmBufSettings,
                out_pStream: *?*IAkAutoStream,
                in_bSyncOpen: bool,
            ) common.WwiseError!void {
                var raw_fsflags_ptr: ?*c.WWISEC_AkFileSystemFlags = blk: {
                    if (in_pFSFlags) |fs_flags| {
                        var raw_fsflags = fs_flags.toC();
                        break :blk &raw_fsflags;
                    }
                    break :blk null;
                };

                var raw_buffer_settings: ?*c.WWISEC_AkAutoStmBufSettings = blk: {
                    if (in_pBufferSettings) |buffer_settings| {
                        var raw_settings = buffer_settings.toC();
                        break :blk &raw_settings;
                    }
                    break :blk null;
                };

                const raw_heuristics = in_heuristics.toC();

                return common.handleAkResult(@ptrCast(*const IAkStreamMgr.VTable, self.__v).create_auto_id(
                    @ptrCast(*IAkStreamMgr, self),
                    in_fileID,
                    raw_fsflags_ptr,
                    &raw_heuristics,
                    raw_buffer_settings,
                    out_pStream,
                    in_bSyncOpen,
                ));
            }

            pub inline fn createAutoMemory(
                self: *T,
                in_pBuffer: ?*anyopaque,
                in_uSize: c.AkUInt64,
                in_heuristics: AkAutoStmHeuristics,
                out_pStream: *?*IAkAutoStream,
            ) common.WwiseError!void {
                const raw_heuristics = in_heuristics.toC();

                return common.handleAkResult(@ptrCast(*const IAkStreamMgr.VTable, self.__v).create_auto_memory(
                    @ptrCast(*IAkStreamMgr, self),
                    in_pBuffer,
                    in_uSize,
                    &raw_heuristics,
                    out_pStream,
                ));
            }

            pub inline fn pinFileInCache(
                self: *T,
                in_fileID: c.WWISEC_AkFileID,
                in_pFSFlags: ?AkFileSystemFlags,
                in_uPriority: c.WWISEC_AkPriority,
            ) common.WwiseError!void {
                var raw_fsflags_ptr: ?*c.WWISEC_AkFileSystemFlags = blk: {
                    if (in_pFSFlags) |fs_flags| {
                        var raw_fsflags = fs_flags.toC();
                        break :blk &raw_fsflags;
                    }
                    break :blk null;
                };

                return common.handleAkResult(@ptrCast(*const IAkStreamMgr.VTable, self.__v).pin_file_in_cache(
                    @ptrCast(*IAkStreamMgr, self),
                    in_fileID,
                    raw_fsflags_ptr,
                    in_uPriority,
                ));
            }

            pub inline fn unpinFileInCache(
                self: *T,
                in_fileID: c.WWISEC_AkFileID,
                in_uPriority: c.WWISEC_AkPriority,
            ) common.WwiseError!void {
                return common.handleAkResult(@ptrCast(*const IAkStreamMgr.VTable, self.__v).unpin_file_in_cache(
                    @ptrCast(*IAkStreamMgr, self),
                    in_fileID,
                    in_uPriority,
                ));
            }

            pub inline fn updateCachingPriority(
                self: *T,
                in_fileID: c.WWISEC_AkFileID,
                in_uPriority: c.WWISEC_AkPriority,
                in_uOldPriority: c.WWISEC_AkPriority,
            ) common.WwiseError!void {
                return common.handleAkResult(@ptrCast(*const IAkStreamMgr.VTable, self.__v).update_caching_priority(
                    @ptrCast(*IAkStreamMgr, self),
                    in_fileID,
                    in_uPriority,
                    in_uOldPriority,
                ));
            }

            pub inline fn getBufferStatusForPinnedFile(
                self: *T,
                in_fileID: c.WWISEC_AkFileID,
                out_fPercentBuffered: *c.AkReal32,
                out_bCacheFull: *bool,
            ) common.WwiseError!void {
                return common.handleAkResult(@ptrCast(*const IAkStreamMgr.VTable, self.__v).get_buffer_status_for_pinned_file(
                    @ptrCast(*IAkStreamMgr, self),
                    in_fileID,
                    out_fPercentBuffered,
                    out_bCacheFull,
                ));
            }

            pub inline fn relocateMemoryStream(
                self: *T,
                in_pStream: *IAkAutoStream,
                in_pNewStart: ?*anyopaque,
            ) common.WwiseError!void {
                return common.handleAkResult(@ptrCast(*const IAkStreamMgr.VTable, self.__v).relocate_memory_stream(
                    @ptrCast(*IAkStreamMgr, self),
                    in_pStream,
                    in_pNewStart,
                ));
            }
        };
    }

    pub usingnamespace Methods(@This());
    pub usingnamespace common.CastMethods(@This());

    pub fn get() ?*IAkStreamMgr {
        return @ptrCast(?*IAkStreamMgr, @alignCast(@alignOf(?*IAkStreamMgr), c.WWISEC_AK_IAkStreamMgr_Get()));
    }
};
