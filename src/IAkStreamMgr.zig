const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const settings = @import("settings.zig");

pub const AK_MONITOR_STREAMNAME_MAXLENGTH = c.WWISEC_AK_MONITOR_STREAMNAME_MAXLENGTH;
pub const AK_MONITOR_DEVICENAME_MAXLENGTH = c.WWISEC_AK_MONITOR_DEVICENAME_MAXLENGTH;

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
        return @bitCast(value);
    }

    pub fn toC(self: AkFileSystemFlags) c.WWISEC_AkFileSystemFlags {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkFileSystemFlags) == @sizeOf(c.WWISEC_AkFileSystemFlags));
    }
};

pub const NativeAkStreamInfo = extern struct {
    device_id: common.AkDeviceID = 0,
    name: ?[*:0]const common.AkOSChar,
    size: u64 = 0,
    is_open: bool = false,

    pub fn fromC(value: c.WWISEC_AkStreamInfo) NativeAkStreamInfo {
        return @bitCast(value);
    }

    pub fn toC(self: NativeAkStreamInfo) c.WWISEC_AkStreamInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(NativeAkStreamInfo) == @sizeOf(c.WWISEC_AkStreamInfo));
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

    pub fn fromC(value: NativeAkStreamInfo, allocator: std.mem.Allocator) !AkStreamInfo {
        return .{
            .device_id = value.device_id,
            .name = try common.fromOSChar(allocator, value.name),
            .size = value.size,
            .is_open = value.is_open,
        };
    }

    pub fn toC(self: AkStreamInfo, allocator: std.mem.Allocator) !NativeAkStreamInfo {
        return .{
            .device_id = self.device_id,
            .name = try common.toOSChar(allocator, self.name),
            .size = self.size,
            .is_open = self.is_open,
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
        return @bitCast(value);
    }

    pub fn toC(self: AkAutoStmHeuristics) c.WWISEC_AkAutoStmHeuristics {
        return @bitCast(self);
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
        return @bitCast(value);
    }

    pub inline fn toC(self: AkAutoStmBufSettings) c.WWISEC_AkAutoStmBufSettings {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkAutoStmBufSettings) == @sizeOf(c.WWISEC_AkAutoStmBufSettings));
    }
};

pub const NativeAkDeviceDesc = extern struct {
    device_id: common.AkDeviceID = 0,
    can_write: bool = false,
    can_read: bool = false,
    device_name: [AK_MONITOR_DEVICENAME_MAXLENGTH]common.AkUtf16 = undefined,
    string_size: u32 = 0,

    comptime {
        std.debug.assert(@sizeOf(NativeAkDeviceDesc) == @sizeOf(c.WWISEC_AkDeviceDesc));
    }
};

pub const AkDeviceDesc = struct {
    device_id: common.AkDeviceID = 0,
    can_write: bool = false,
    can_read: bool = false,
    device_name: []const u8 = "",

    pub fn fromC(value: *const NativeAkDeviceDesc, allocator: std.mem.Allocator) !AkDeviceDesc {
        return .{
            .device_id = value.device_id,
            .can_write = value.can_write,
            .can_read = value.can_read,
            .device_name = try std.unicode.utf16leToUtf8Alloc(allocator, value.device_name[0..value.string_size]),
        };
    }

    pub fn toC(self: AkDeviceDesc) !NativeAkDeviceDesc {
        var result: NativeAkDeviceDesc = undefined;

        result.device_id = self.device_id;
        result.can_write = self.can_write;
        result.can_read = self.can_read;

        @memset(&result.device_name, 0);
        result.string_size = @truncate(try std.unicode.utf8ToUtf16Le(&result.device_name, self.device_name));

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
        return @bitCast(value);
    }

    pub inline fn toC(self: AkDeviceData) c.WWISEC_AkDeviceData {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkDeviceData) == @sizeOf(c.WWISEC_AkDeviceData));
    }
};

pub const NativeAkStreamRecord = extern struct {
    stream_id: u32 = 0,
    device_id: common.AkDeviceID = 0,
    stream_name: [AK_MONITOR_STREAMNAME_MAXLENGTH]common.AkUtf16,
    string_size: u32 = 0,
    file_size: u64 = 0,
    custom_param_size: u32 = 0,
    custom_param: u32 = 0,
    is_auto_stream: bool = false,
    is_caching_stream: bool = false,

    pub inline fn fromC(value: c.WWISEC_AkStreamRecord) AkDeviceData {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkDeviceData) c.WWISEC_AkStreamRecord {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(NativeAkStreamRecord) == @sizeOf(c.WWISEC_AkStreamRecord));
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

    pub fn deinit(self: AkStreamRecord, allocator: std.mem.Allocator) void {
        allocator.free(self.stream_name);
    }

    pub fn fromC(value: *NativeAkStreamRecord, allocator: std.mem.Allocator) !AkStreamRecord {
        return .{
            .stream_id = value.stream_id,
            .device_id = value.device_id,
            .stream_name = try std.unicode.utf16leToUtf8Alloc(allocator, value.stream_name[0..]),
            .file_size = value.file_size,
            .custom_param_size = value.custom_param_size,
            .custom_param = value.custom_param,
            .is_auto_stream = value.is_auto_stream,
            .is_caching_stream = value.is_caching_stream,
        };
    }

    pub fn toC(self: AkStreamRecord) !NativeAkStreamRecord {
        var result: NativeAkStreamRecord = undefined;

        @memset(&result.stream_name, 0);
        result.string_size = @truncate(try std.unicode.utf8ToUtf16Le(&result.stream_name, self.stream_name));

        result.stream_id = self.stream_id;
        result.device_id = self.device_id;
        result.file_size = self.file_size;
        result.custom_param_size = self.custom_param_size;
        result.custom_param = self.custom_param;
        result.is_auto_stream = self.is_auto_stream;
        result.is_caching_stream = self.is_caching_stream;

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
        return @bitCast(value);
    }

    pub inline fn toC(self: AkStreamData) c.WWISEC_AkStreamData {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkStreamData) == @sizeOf(c.WWISEC_AkStreamData));
    }
};

pub const IAkStreamProfile = opaque {
    pub const FunctionTable = extern struct {
        destructor: *const fn (self: *IAkStreamProfile) callconv(.C) void,
        get_stream_record: *const fn (self: *IAkStreamProfile, out_stream_record: *AkStreamRecord) callconv(.C) void,
        get_stream_data: *const fn (self: *IAkStreamProfile, ouut_stream_data: *AkStreamData) callconv(.C) void,
        is_new: *const fn (self: *IAkStreamProfile) callconv(.C) bool,
        clear_new: *const fn (self: *IAkStreamProfile) callconv(.C) void,
    };

    pub fn getStreamRecord(self: *IAkStreamProfile, allocator: std.mem.Allocator, out_stream_record: *AkStreamRecord) !void {
        var native_stream_record: NativeAkStreamRecord = undefined;
        c.WWISEC_AK_IAkStreamProfile_GetStreamRecord(@ptrCast(self), @ptrCast(&native_stream_record));
        out_stream_record.* = try AkStreamRecord.fromC(&native_stream_record, allocator);
    }

    pub fn getStreamData(self: *IAkStreamProfile, out_stream_data: *AkStreamData) void {
        c.WWISEC_AK_IAkStreamProfile_GetStreamData(@ptrCast(self), @ptrCast(out_stream_data));
    }

    pub fn isNew(self: *IAkStreamProfile) bool {
        return c.WWISEC_AK_IAkStreamProfile_IsNew(@ptrCast(self));
    }

    pub fn clearNew(self: *IAkStreamProfile) void {
        c.WWISEC_AK_IAkStreamProfile_ClearNew(@ptrCast(self));
    }

    pub fn createInstance(instance: *anyopaque, function_table: *const FunctionTable) *IAkStreamProfile {
        return @ptrCast(
            c.WWISEC_AK_IAkStreamProfile_CreateInstance(instance, @ptrCast(function_table)),
        );
    }

    pub fn destroyInstance(instance: *anyopaque) void {
        c.WWISEC_AK_IAkStreamProfile_DestroyInstance(@ptrCast(instance));
    }
};

pub const IAkDeviceProfile = opaque {
    pub const FunctionTable = extern struct {
        destructor: *const fn (self: *IAkDeviceProfile) callconv(.C) void,
        on_profile_start: *const fn (self: *IAkDeviceProfile) callconv(.C) void,
        on_profile_end: *const fn (self: *IAkDeviceProfile) callconv(.C) void,
        get_desc: *const fn (self: *IAkDeviceProfile, out_device_desc: *NativeAkDeviceDesc) callconv(.C) void,
        get_data: *const fn (self: *IAkDeviceProfile, out_device_data: *AkDeviceData) callconv(.C) void,
        is_new: *const fn (self: *IAkDeviceProfile) callconv(.C) bool,
        clear_new: *const fn (self: *IAkDeviceProfile) callconv(.C) void,
        get_num_streams: *const fn (self: *IAkDeviceProfile) callconv(.C) u32,
        get_stream_profile: *const fn (self: *IAkDeviceProfile, in_stream_index: u32) callconv(.C) ?*IAkStreamProfile,
    };

    pub fn onProfileStart(self: *IAkDeviceProfile) void {
        c.WWISEC_AK_IAkDeviceProfile_OnProfileStart(@ptrCast(self));
    }

    pub fn onProfileEnd(self: *IAkDeviceProfile) void {
        c.WWISEC_AK_IAkDeviceProfile_OnProfileEnd(@ptrCast(self));
    }

    pub fn getDesc(self: *IAkDeviceProfile, allocator: std.mem.Allocator, out_device_desc: *AkDeviceDesc) !void {
        var raw_device_desc: NativeAkDeviceDesc = undefined;
        c.WWISEC_AK_IAkDeviceProfile_GetDesc(@ptrCast(self), @ptrCast(&raw_device_desc));
        out_device_desc.* = try AkDeviceDesc.fromC(&raw_device_desc, allocator);
    }

    pub fn getData(self: *IAkDeviceProfile, out_device_data: *AkDeviceData) void {
        c.WWISEC_AK_IAkDeviceProfile_GetData(@ptrCast(self), @ptrCast(out_device_data));
    }

    pub fn isNew(self: *IAkDeviceProfile) bool {
        return c.WWISEC_AK_IAkDeviceProfile_IsNew(@ptrCast(self));
    }

    pub fn clearNew(self: *IAkDeviceProfile) void {
        c.WWISEC_AK_IAkDeviceProfile_ClearNew(@ptrCast(self));
    }

    pub fn getNumStreams(self: *IAkDeviceProfile) u32 {
        return c.WWISEC_AK_IAkDeviceProfile_GetNumStreams(@ptrCast(self));
    }

    pub fn getStreamProfile(self: *IAkDeviceProfile, in_stream_index: u32) ?*IAkStreamProfile {
        return @ptrCast(
            c.WWISEC_AK_IAkDeviceProfile_GetStreamProfile(@ptrCast(self), in_stream_index),
        );
    }

    pub fn createInstance(instance: *anyopaque, function_table: *const FunctionTable) *IAkDeviceProfile {
        return @ptrCast(
            c.WWISEC_AK_IAkDeviceProfile_CreateInstance(instance, @ptrCast(function_table)),
        );
    }

    pub fn destroyInstance(instance: *anyopaque) void {
        c.WWISEC_AK_IAkDeviceProfile_DestroyInstance(@ptrCast(instance));
    }
};

pub const IAkStreamMgrProfile = opaque {
    pub const FunctionTable = extern struct {
        destructor: *const fn (self: *IAkStreamMgrProfile) callconv(.C) void,
        start_monitoring: *const fn (self: *IAkStreamMgrProfile) callconv(.C) common.AKRESULT,
        stop_monitoring: *const fn (self: *IAkStreamMgrProfile) callconv(.C) void,
        get_num_devices: *const fn (self: *IAkStreamMgrProfile) callconv(.C) u32,
        get_device_profile: *const fn (self: *IAkStreamMgrProfile, in_device_index: u32) callconv(.C) ?*IAkDeviceProfile,
    };

    pub fn startMonitoring(self: *IAkStreamMgrProfile) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkStreamMgrProfile_StartMonitoring(@ptrCast(self)),
        );
    }

    pub fn stopMonitoring(self: *IAkStreamMgrProfile) void {
        c.WWISEC_AK_IAkStreamMgrProfile_StopMonitoring(@ptrCast(self));
    }

    pub fn getNumDevices(self: *IAkStreamMgrProfile) u32 {
        return c.WWISEC_AK_IAkStreamMgrProfile_GetNumDevices(@ptrCast(self));
    }

    pub fn getDeviceProfile(self: *IAkStreamMgrProfile, in_device_index: u32) ?*IAkDeviceProfile {
        return @ptrCast(
            c.WWISEC_AK_IAkStreamMgrProfile_GetDeviceProfile(@ptrCast(self), in_device_index),
        );
    }

    pub fn createInstance(instance: *anyopaque, function_table: *const FunctionTable) *IAkStreamMgrProfile {
        return @ptrCast(
            c.WWISEC_AK_IAkStreamMgrProfile_CreateInstance(instance, @ptrCast(function_table)),
        );
    }

    pub fn destroyInstance(instance: *anyopaque) void {
        c.WWISEC_AK_IAkStreamMgrProfile_DestroyInstance(@ptrCast(instance));
    }
};

pub const IAkStdStream = opaque {
    pub const FunctionTable = extern struct {
        destructor: *const fn (self: *IAkStdStream) callconv(.C) void,
        destroy: *const fn (self: *IAkStdStream) callconv(.C) void,
        get_info: *const fn (self: *IAkStdStream, out_info: *NativeAkStreamInfo) callconv(.C) void,
        get_file_descriptor: *const fn (self: *IAkStdStream) callconv(.C) ?*anyopaque,
        set_stream_name: *const fn (self: *IAkStdStream, in_stream_name: [*:0]const common.AkOSChar) callconv(.C) common.AKRESULT,
        get_block_size: *const fn (self: *IAkStdStream) callconv(.C) u32,
        read: *const fn (self: *IAkStdStream, in_buffer: ?*anyopaque, in_req_size: u32, in_wait: bool, in_priority: common.AkPriority, in_deadline: f32, out_size: *u32) callconv(.C) common.AKRESULT,
        write: *const fn (self: *IAkStdStream, in_buffer: ?*anyopaque, in_req_size: u32, in_wait: bool, in_priority: common.AkPriority, in_deadline: f32, out_size: *u32) callconv(.C) common.AKRESULT,
        get_position: *const fn (self: *IAkStdStream, out_end_of_stream: *bool) callconv(.C) u64,
        set_position: *const fn (self: *IAkStdStream, in_move_offset: i64, in_move_method: AkMoveMethod, out_real_offset: *i64) callconv(.C) common.AKRESULT,
        cancel: *const fn (self: *IAkStdStream) callconv(.C) void,
        get_data: *const fn (self: *IAkStdStream, out_size: *u32) callconv(.C) ?*anyopaque,
        get_status: *const fn (self: *IAkStdStream) callconv(.C) AkStmStatus,
        wait_for_pending_operation: *const fn (self: *IAkStdStream) callconv(.C) AkStmStatus,
    };

    pub fn destroy(self: *IAkStdStream) void {
        c.WWISEC_AK_IAkStdStream_Destroy(@ptrCast(self));
    }

    pub fn getInfo(self: *IAkStdStream, allocator: std.mem.Allocator) !AkStreamInfo {
        var raw_stream_info: NativeAkStreamInfo = undefined;
        c.WWISEC_AK_IAkStdStream_GetInfo(@ptrCast(self), @ptrCast(&raw_stream_info));
        return try AkStreamInfo.fromC(raw_stream_info, allocator);
    }

    pub fn getFileDescriptor(self: *IAkStdStream) ?*anyopaque {
        return c.WWISEC_AK_IAkStdStream_GetFileDescriptor(@ptrCast(self));
    }

    pub fn setStreamName(self: *IAkStdStream, fallback_allocator: std.mem.Allocator, stream_name: []const u8) common.WwiseError!void {
        var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_oschar_allocator.get();

        var raw_stream_name = common.toOSChar(allocator, stream_name) catch return common.WwiseError.Fail;
        defer allocator.free(raw_stream_name);

        return common.handleAkResult(
            c.WWISEC_AK_IAkStdStream_SetStreamName(@ptrCast(self), raw_stream_name),
        );
    }

    pub fn getBlockSize(self: *IAkStdStream) u32 {
        return c.WWISEC_AK_IAkStdStream_GetBlockSize(@ptrCast(self));
    }

    pub fn read(self: *IAkStdStream, in_buffer: ?*anyopaque, in_req_size: u32, in_wait: bool, in_priority: common.AkPriority, in_deadline: f32, out_size: *u32) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkStdStream_Read(
                @ptrCast(self),
                in_buffer,
                in_req_size,
                in_wait,
                in_priority,
                in_deadline,
                out_size,
            ),
        );
    }

    pub fn write(self: *IAkStdStream, in_buffer: ?*anyopaque, in_req_size: u32, in_wait: bool, in_priority: common.AkPriority, in_deadline: f32, out_size: *u32) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkStdStream_Write(
                @ptrCast(self),
                in_buffer,
                in_req_size,
                in_wait,
                in_priority,
                in_deadline,
                out_size,
            ),
        );
    }

    pub fn getPosition(self: *IAkStdStream, out_end_of_stream: *bool) u64 {
        return c.WWISEC_AK_IAkStdStream_GetPosition(@ptrCast(self), out_end_of_stream);
    }

    pub fn setPosition(self: *IAkStdStream, in_move_offset: i64, in_move_method: AkMoveMethod, out_real_offset: *i64) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkStdStream_SetPosition(
                @ptrCast(self),
                in_move_offset,
                @intFromEnum(in_move_method),
                out_real_offset,
            ),
        );
    }

    pub fn cancel(self: *IAkStdStream) void {
        c.WWISEC_AK_IAkStdStream_Cancel(@ptrCast(self));
    }

    pub fn getData(self: *IAkStdStream, out_size: *u32) ?*anyopaque {
        return c.WWISEC_AK_IAkStdStream_GetData(@ptrCast(self), out_size);
    }

    pub fn getStatus(self: *IAkStdStream) AkStmStatus {
        return @enumFromInt(c.WWISEC_AK_IAkStdStream_GetStatus(@ptrCast(self)));
    }

    pub fn waitForPendingOperation(self: *IAkStdStream) AkStmStatus {
        return @enumFromInt(c.WWISEC_AK_IAkStdStream_WaitForPendingOperation(@ptrCast(self)));
    }

    pub fn createInstance(instance: *anyopaque, function_table: *const FunctionTable) *IAkStdStream {
        return @ptrCast(
            c.WWISEC_AK_IAkStdStream_CreateInstance(instance, @ptrCast(function_table)),
        );
    }

    pub fn destroyInstance(instance: *anyopaque) void {
        c.WWISEC_AK_IAkStdStream_DestroyInstance(@ptrCast(instance));
    }
};

pub const IAkAutoStream = opaque {
    pub const FunctionTable = extern struct {
        destructor: *const fn (self: *IAkStdStream) callconv(.C) void,
        destroy: *const fn (self: *IAkAutoStream) callconv(.C) void,
        get_info: *const fn (self: *IAkAutoStream, out_info: *AkStreamInfo) callconv(.C) void,
        get_file_descriptor: *const fn (self: *IAkAutoStream) callconv(.C) ?*anyopaque,
        get_heuristics: *const fn (self: *IAkAutoStream, out_heuristics: *AkAutoStmHeuristics) callconv(.C) void,
        set_heuristics: *const fn (self: *IAkAutoStream, in_heuristics: *AkAutoStmHeuristics) callconv(.C) common.AKRESULT,
        set_minimal_buffer_size: *const fn (self: *IAkAutoStream, in_min_buffer_size: u32) callconv(.C) common.AKRESULT,
        set_min_target_buffer_size: *const fn (self: *IAkAutoStream, in_min_target_buffer_size: u32) callconv(.C) common.AKRESULT,
        set_stream_name: *const fn (self: *IAkAutoStream, in_stream_name: [*:0]const common.AkOSChar) callconv(.C) common.AKRESULT,
        get_block_size: *const fn (self: *IAkAutoStream) callconv(.C) u32,
        query_buffering_status: *const fn (self: *IAkAutoStream, out_num_bytes_available: *u32) callconv(.C) common.AKRESULT,
        get_nominal_buffering: *const fn (self: *IAkAutoStream) callconv(.C) u32,
        start: *const fn (self: *IAkAutoStream) callconv(.C) common.AKRESULT,
        stop: *const fn (self: *IAkAutoStream) callconv(.C) common.AKRESULT,
        get_position: *const fn (self: *IAkAutoStream, out_end_of_stream: *bool) callconv(.C) u64,
        set_position: *const fn (self: *IAkAutoStream, in_move_offset: i64, in_move_method: AkMoveMethod, out_real_offset: *i64) callconv(.C) common.AKRESULT,
        get_buffer: *const fn (self: *IAkAutoStream, out_buffer: *?*anyopaque, out_size: *u32, in_wait: bool) callconv(.C) common.AKRESULT,
        release_buffer: *const fn (self: *IAkAutoStream) callconv(.C) common.AKRESULT,
    };

    pub fn destroy(self: *IAkAutoStream) void {
        c.WWISEC_AK_IAkAutoStream_Destroy(@ptrCast(self));
    }

    pub fn getInfo(self: *IAkAutoStream, allocator: std.mem.Allocator, out_info: *AkStreamInfo) !void {
        var raw_stream_info: NativeAkStreamInfo = undefined;
        c.WWISEC_AK_IAkAutoStream_GetInfo(@ptrCast(self), @ptrCast(&raw_stream_info));
        out_info.* = try AkStreamInfo.fromC(raw_stream_info, allocator);
    }

    pub fn getFileDescriptor(self: *IAkAutoStream) ?*anyopaque {
        return c.WWISEC_AK_IAkAutoStream_GetFileDescriptor(@ptrCast(self));
    }

    pub fn getHeuristics(self: *IAkAutoStream, out_heuristics: *AkAutoStmHeuristics) void {
        c.WWISEC_AK_IAkAutoStream_GetHeuristics(@ptrCast(self), @ptrCast(out_heuristics));
    }

    pub fn setHeuristics(self: *IAkAutoStream, in_heuristics: *AkAutoStmHeuristics) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkAutoStream_SetHeuristics(@ptrCast(self), @ptrCast(in_heuristics)),
        );
    }

    pub fn setMinimalBufferSize(self: *IAkAutoStream, in_min_buffer_size: u32) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkAutoStream_SetMinimalBufferSize(@ptrCast(self), in_min_buffer_size),
        );
    }

    pub fn setMinTargetBufferSize(self: *IAkAutoStream, in_min_target_buffer_size: u32) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkAutoStream_SetMinTargetBufferSize(@ptrCast(self), in_min_target_buffer_size),
        );
    }

    pub fn setStreamName(self: *IAkAutoStream, fallback_allocator: std.mem.Allocator, stream_name: []const u8) common.WwiseError!void {
        var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_oschar_allocator.get();

        var raw_stream_name = common.toOSChar(allocator, stream_name) catch return common.WwiseError.Fail;
        defer allocator.free(raw_stream_name);

        return common.handleAkResult(
            c.WWISEC_AK_IAkAutoStream_SetStreamName(@ptrCast(self), raw_stream_name),
        );
    }

    pub fn getBlockSize(self: *IAkAutoStream) u32 {
        return c.WWISEC_AK_IAkAutoStream_GetBlockSize(@ptrCast(self));
    }

    pub fn queryBufferingStatus(self: *IAkAutoStream, out_num_bytes_available: *u32) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkAutoStream_QueryBufferingStatus(@ptrCast(self), out_num_bytes_available),
        );
    }

    pub fn getNominalBuffering(self: *IAkAutoStream) u32 {
        return c.WWISEC_AK_IAkAutoStream_GetNominalBuffering(@ptrCast(self));
    }

    pub fn start(self: *IAkAutoStream) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkAutoStream_Start(@ptrCast(self)),
        );
    }

    pub fn stop(self: *IAkAutoStream) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkAutoStream_Stop(@ptrCast(self)),
        );
    }

    pub fn getPosition(self: *IAkAutoStream, out_end_of_stream: *bool) u64 {
        return c.WWISEC_AK_IAkAutoStream_GetPosition(@ptrCast(self), out_end_of_stream);
    }

    pub fn setPosition(self: *IAkAutoStream, in_move_offset: i64, in_move_method: AkMoveMethod, out_real_offset: *i64) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkAutoStream_SetPosition(@ptrCast(self), in_move_offset, @intFromEnum(in_move_method), out_real_offset),
        );
    }

    pub fn getBuffer(self: *IAkAutoStream, out_buffer: *?*anyopaque, out_size: *u32, in_wait: bool) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkAutoStream_GetBuffer(@ptrCast(self), out_buffer, out_size, in_wait),
        );
    }

    pub fn releaseBuffer(self: *IAkAutoStream) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkAutoStream_ReleaseBuffer(@ptrCast(self)),
        );
    }

    pub fn createInstance(instance: *anyopaque, function_table: *const FunctionTable) *IAkAutoStream {
        return @ptrCast(
            c.WWISEC_AK_IAkAutoStream_CreateInstance(instance, @ptrCast(function_table)),
        );
    }

    pub fn destroyInstance(instance: *anyopaque) void {
        c.WWISEC_AK_IAkAutoStream_DestroyInstance(@ptrCast(instance));
    }
};

pub const IAkStreamMgr = opaque {
    pub const FunctionTable = extern struct {
        destructor: *const fn (self: *IAkStreamMgr) callconv(.C) void,
        destroy: *const fn (
            self: *IAkStreamMgr,
        ) callconv(.C) void,
        get_stream_mgr_profile: *const fn (
            self: *IAkStreamMgr,
        ) callconv(.C) ?*IAkStreamMgrProfile,
        create_str_id: *const fn (
            self: *IAkStreamMgr,
            in_file_id: common.AkFileID,
            in_fs_flags: ?*AkFileSystemFlags,
            in_open_mode: AkOpenMode,
            out_stream: *?*IAkStdStream,
            in_sync_open: bool,
        ) callconv(.C) common.AKRESULT,
        create_std_string: *const fn (
            self: *IAkStreamMgr,
            in_file_name: [*c]const common.AkOSChar,
            in_fs_flags: ?*AkFileSystemFlags,
            in_open_mode: AkOpenMode,
            out_stream: *?*IAkStdStream,
            in_sync_open: bool,
        ) callconv(.C) common.AKRESULT,
        create_auto_string: *const fn (
            self: *IAkStreamMgr,
            in_file_name: [*c]const common.AkOSChar,
            in_fs_flags: ?*AkFileSystemFlags,
            in_heuristics: *const AkAutoStmHeuristics,
            in_buffer_settings: ?*AkAutoStmBufSettings,
            out_stream: *?*IAkAutoStream,
            in_sync_open: bool,
        ) callconv(.C) common.AKRESULT,
        create_auto_id: *const fn (
            self: *IAkStreamMgr,
            in_file_id: common.AkFileID,
            in_fs_flags: ?*AkFileSystemFlags,
            in_heuristics: *const AkAutoStmHeuristics,
            in_buffer_settings: ?*AkAutoStmBufSettings,
            out_stream: *?*IAkAutoStream,
            in_sync_open: bool,
        ) callconv(.C) common.AKRESULT,
        create_auto_memory: *const fn (
            self: *IAkStreamMgr,
            in_buffer: ?*anyopaque,
            in_size: u64,
            in_heuristics: *const AkAutoStmHeuristics,
            out_stream: *?*IAkAutoStream,
        ) callconv(.C) common.AKRESULT,
        pin_file_in_cache: *const fn (
            self: *IAkStreamMgr,
            in_file_id: common.AkFileID,
            in_fs_flags: ?*AkFileSystemFlags,
            in_priority: common.AkPriority,
        ) callconv(.C) common.AKRESULT,
        unpin_file_in_cache: *const fn (
            self: *IAkStreamMgr,
            in_file_id: common.AkFileID,
            in_priority: common.AkPriority,
        ) callconv(.C) common.AKRESULT,
        update_caching_priority: *const fn (
            self: *IAkStreamMgr,
            in_file_id: common.AkFileID,
            in_priority: common.AkPriority,
            in_old_priority: common.AkPriority,
        ) callconv(.C) common.AKRESULT,
        get_buffer_status_for_pinned_file: *const fn (
            self: *IAkStreamMgr,
            in_file_id: common.AkFileID,
            out_percent_buffered: *f32,
            out_cache_full: *bool,
        ) callconv(.C) common.AKRESULT,
        relocate_memory_stream: *const fn (
            self: *IAkStreamMgr,
            in_stream: *IAkAutoStream,
            in_new_start: ?*u8,
        ) callconv(.C) common.AKRESULT,
    };

    pub fn destroy(self: *IAkStreamMgr) void {
        c.WWISEC_AK_IAkStreamMgr_Destroy(@ptrCast(self));
    }

    pub fn getStreamMgrProfile(self: *IAkStreamMgr) ?*IAkStreamMgrProfile {
        return @ptrCast(
            c.WWISEC_AK_IAkStreamMgr_GetStreamMgrProfile(@ptrCast(self)),
        );
    }

    pub fn createStdString(
        self: *IAkStreamMgr,
        fallback_allocator: std.mem.Allocator,
        in_file_name: []const u8,
        in_fs_flags: ?*AkFileSystemFlags,
        in_open_mode: AkOpenMode,
        out_stream: *?*IAkStdStream,
        in_sync_open: bool,
    ) common.WwiseError!void {
        var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_char_allocator.get();

        const filename_oschar = common.toOSChar(allocator, in_file_name) catch return common.WwiseError.Fail;
        defer allocator.free(filename_oschar);

        return common.handleAkResult(
            c.WWISEC_AK_IAkStreamMgr_CreateStdString(
                @ptrCast(self),
                filename_oschar,
                @ptrCast(in_fs_flags),
                @intFromEnum(in_open_mode),
                @ptrCast(out_stream),
                in_sync_open,
            ),
        );
    }

    pub fn createStdId(
        self: *IAkStreamMgr,
        in_file_id: common.AkFileID,
        in_fs_flags: ?*AkFileSystemFlags,
        in_open_mode: AkOpenMode,
        out_stream: *?*IAkStdStream,
        in_sync_open: bool,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkStreamMgr_CreateStdID(
                @ptrCast(self),
                in_file_id,
                @ptrCast(in_fs_flags),
                @intFromEnum(in_open_mode),
                @ptrCast(out_stream),
                in_sync_open,
            ),
        );
    }

    pub fn createAutoString(
        self: *IAkStreamMgr,
        fallback_allocator: std.mem.Allocator,
        in_file_name: []const u8,
        in_fs_flags: ?*AkFileSystemFlags,
        in_heuristics: *const AkAutoStmHeuristics,
        in_buffer_settings: ?*AkAutoStmBufSettings,
        out_stream: *?*IAkAutoStream,
        in_sync_open: bool,
    ) common.WwiseError!void {
        var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
        var allocator = stack_char_allocator.get();

        const filename_oschar = common.toOSChar(allocator, in_file_name) catch return common.WwiseError.Fail;
        defer allocator.free(filename_oschar);

        return common.handleAkResult(
            c.WWISEC_AK_IAkStreamMgr_CreateAutoString(
                @ptrCast(self),
                filename_oschar,
                @ptrCast(in_fs_flags),
                @ptrCast(in_heuristics),
                @ptrCast(in_buffer_settings),
                @ptrCast(out_stream),
                in_sync_open,
            ),
        );
    }

    pub fn createAutoId(
        self: *IAkStreamMgr,
        in_file_id: common.AkFileID,
        in_fs_flags: ?*AkFileSystemFlags,
        in_heuristics: *const AkAutoStmHeuristics,
        in_buffer_settings: ?*AkAutoStmBufSettings,
        out_streamm: *?*IAkAutoStream,
        in_sync_open: bool,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkStreamMgr_CreateAutoID(
                @ptrCast(self),
                in_file_id,
                @ptrCast(in_fs_flags),
                @ptrCast(in_heuristics),
                @ptrCast(in_buffer_settings),
                @ptrCast(out_streamm),
                in_sync_open,
            ),
        );
    }

    pub fn createAutoMemory(
        self: *IAkStreamMgr,
        in_buffer: ?*anyopaque,
        in_size: u64,
        in_heuristics: *const AkAutoStmHeuristics,
        out_stream: *?*IAkAutoStream,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkStreamMgr_CreateAutoMemory(
                @ptrCast(self),
                in_buffer,
                in_size,
                @ptrCast(in_heuristics),
                @ptrCast(out_stream),
            ),
        );
    }

    pub fn pinFileInCache(
        self: *IAkStreamMgr,
        in_file_id: common.AkFileID,
        in_fs_flags: ?*AkFileSystemFlags,
        in_priority: common.AkPriority,
    ) common.WwiseError!void {
        return common.handleAkResult(c.WWISEC_AK_IAkStreamMgr_PinFileInCache(
            @ptrCast(self),
            in_file_id,
            @ptrCast(in_fs_flags),
            in_priority,
        ));
    }

    pub fn unpinFileInCache(
        self: *IAkStreamMgr,
        in_file_id: common.AkFileID,
        in_priority: common.AkPriority,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkStreamMgr_UnpinFileInCache(
                @ptrCast(self),
                in_file_id,
                in_priority,
            ),
        );
    }

    pub fn updateCachingPriority(
        self: *IAkStreamMgr,
        in_file_id: common.AkFileID,
        in_priority: common.AkPriority,
        in_old_priority: common.AkPriority,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkStreamMgr_UpdateCachingPriority(
                @ptrCast(self),
                in_file_id,
                in_priority,
                in_old_priority,
            ),
        );
    }

    pub fn getBufferStatusForPinnedFile(
        self: *IAkStreamMgr,
        in_file_id: common.AkFileID,
        out_percent_buffered: *f32,
        out_cache_full: *bool,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkStreamMgr_GetBufferStatusForPinnedFile(
                @ptrCast(self),
                in_file_id,
                out_percent_buffered,
                out_cache_full,
            ),
        );
    }

    pub fn relocateMemoryStream(
        self: *IAkStreamMgr,
        in_stream: *IAkAutoStream,
        in_new_start: ?*u8,
    ) common.WwiseError!void {
        return common.handleAkResult(
            c.WWISEC_AK_IAkStreamMgr_RelocateMemoryStream(
                @ptrCast(self),
                @ptrCast(in_stream),
                in_new_start,
            ),
        );
    }

    pub fn createInstance(instance: *anyopaque, function_table: *const FunctionTable) *IAkStreamMgr {
        return @ptrCast(
            c.WWISEC_AK_IAkStreamMgr_CreateInstance(instance, @ptrCast(function_table)),
        );
    }

    pub fn destroyInstance(instance: *anyopaque) void {
        c.WWISEC_AK_IAkStreamMgr_DestroyInstance(@ptrCast(instance));
    }

    pub fn get() ?*IAkStreamMgr {
        return @ptrCast(@alignCast(c.WWISEC_AK_IAkStreamMgr_Get()));
    }
};
