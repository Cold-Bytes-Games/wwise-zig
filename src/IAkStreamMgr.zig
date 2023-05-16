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

pub const AkFileSystemFlags = struct {
    company_id: u32 = common.AK_INVALID_FILE_ID,
    codec_id: u32,
    custom_param_size: u32,
    custom_param: ?*anyopaque,
    is_language_specific: bool,
    is_automatic_stream: bool,
    cache_id: common.AkFileID,
    num_bytes_prefetch: u32,
    directory_hash: u32 = common.AK_INVALID_UNIQUE_ID,

    pub fn fromC(value: c.WWISEC_AkFileSystemFlags) AkFileSystemFlags {
        return .{
            .company_id = value.uCompanyID,
            .codec_id = value.uCodecID,
            .custom_param_size = value.uCustomParamSize,
            .custom_param = value.pCustomParam,
            .is_language_specific = value.bIsLanguageSpecific,
            .is_automatic_stream = value.bIsAutomaticStream,
            .cache_id = value.uCacheID,
            .num_bytes_prefetch = value.uNumBytesPrefetch,
            .directory_hash = value.uDirectoryHash,
        };
    }

    pub fn toC(self: AkFileSystemFlags) c.WWISEC_AkFileSystemFlags {
        return .{
            .uCompanyID = self.company_id,
            .uCodecID = self.codec_id,
            .uCustomParamSize = self.custom_param_size,
            .pCustomParam = self.custom_param,
            .bIsLanguageSpecific = self.is_language_specific,
            .bIsAutomaticStream = self.is_automatic_stream,
            .uCacheID = self.cache_id,
            .uNumBytesPrefetch = self.num_bytes_prefetch,
            .uDirectoryHash = self.directory_hash,
        };
    }
};

pub const AkStreamInfo = struct {
    device_id: common.AkDeviceID,
    name: []const u8,
    size: u64,
    is_open: bool,

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

pub const AkAutoStmHeuristics = struct {
    throughput: f32,
    loop_start: u32,
    loop_end: u32,
    min_num_buffers: u32,
    priority: common.AkPriority,

    pub fn fromC(value: c.WWISEC_AkAutoStmHeuristics) AkAutoStmHeuristics {
        return .{
            .throughout = value.fThroughput,
            .loop_start = value.uLoopStart,
            .loop_end = value.uLoopEnd,
            .min_num_buffers = value.uMinNumBuffers,
            .priority = value.priority,
        };
    }

    pub fn toC(self: AkAutoStmHeuristics) c.WWISEC_AkAutoStmHeuristics {
        return .{
            .fThroughput = self.throughout,
            .uLoopStart = self.loop_start,
            .uLoopEnd = self.loop_end,
            .uMinNumBuffers = self.min_num_buffers,
            .priority = self.priority,
        };
    }
};

pub const AkAutoStmBufSettings = struct {
    buffer_size: u32,
    min_buffer_size: u32,
    block_size: u32,

    pub fn fromC(value: c.WWISEC_AkAutoStmBufSettings) AkAutoStmBufSettings {
        return .{
            .buffer_size = value.uBufferSize,
            .min_buffer_size = value.uMinBufferSize,
            .block_size = value.uBlockSize,
        };
    }

    pub fn toC(self: AkAutoStmBufSettings) c.WWISEC_AkAutoStmBufSettings {
        return .{
            .uBufferSize = self.buffer_size,
            .uMinBufferSize = self.min_buffer_size,
            .uBlockSize = self.block_size,
        };
    }
};

pub const AkDeviceDesc = struct {
    device_id: common.AkDeviceID,
    can_write: bool,
    can_read: bool,
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

pub const AkDeviceData = struct {
    device_id: common.AkDeviceID,
    mem_size: u32,
    mem_used: u32,
    allocs: u32,
    frees: u32,
    peak_refd_mem_used: u32,
    unreferenced_cached_bytes: u32,
    granularity: u32,
    num_active_streams: u32,
    total_bytes_transferred: u32,
    low_level_bytes_transferred: u32,
    avg_cache_efficiency: f32,
    num_low_level_requests_completed: u32,
    num_low_level_requests_cancelled: u32,
    num_low_level_requests_pending: u32,
    custom_param: u32,
    cache_pinned_bytes: u32,

    pub fn fromC(value: c.WWISEC_AkDeviceData) AkDeviceData {
        return .{
            .device_id = value.deviceID,
            .mem_size = value.uMemSize,
            .mem_use = value.uMemUsed,
            .allocs = value.uAllocs,
            .frees = value.uFrees,
            .peak_refd_mem_used = value.uPeakRefdMemUsed,
            .unreferenced_cached_bytes = value.uUnreferencedCachedBytes,
            .granularity = value.uGranularity,
            .num_active_streams = value.uNumActiveStreams,
            .total_bytes_transferred = value.uTotalBytesTransferred,
            .low_level_bytes_transferred = value.uLowLevelBytesTransferred,
            .avg_cache_efficiency = value.fAvgCacheEfficiency,
            .num_low_level_requests_completed = value.uNumLowLevelRequestsCompleted,
            .num_low_level_requests_cancelled = value.uNumLowLevelRequestsCancelled,
            .num_low_level_requests_pending = value.uNumLowLevelRequestsPending,
            .custom_param = value.uCustomParam,
            .cache_pinned_bytes = value.uCachePinnedBytes,
        };
    }

    pub fn toC(self: AkDeviceData) c.WWISEC_AkDeviceData {
        return .{
            .deviceID = self.device_id,
            .uMemSize = self.mem_size,
            .uMemUsed = self.mem_used,
            .uAllocs = self.allocs,
            .uFrees = self.frees,
            .uPeakRefdMemUsed = self.peak_refd_mem_used,
            .uUnreferencedCachedBytes = self.unreferenced_cached_bytes,
            .uGranularity = self.granularity,
            .uNumActiveStreams = self.num_active_streams,
            .uTotalBytesTransferred = self.total_bytes_transferred,
            .uLowLevelBytesTransferred = self.low_level_bytes_transferred,
            .fAvgCacheEfficiency = self.avg_cache_efficiency,
            .uNumLowLevelRequestsCompleted = self.num_low_level_requests_completed,
            .uNumLowLevelRequestsCancelled = self.num_low_level_requests_cancelled,
            .uNumLowLevelRequestsPending = self.num_low_level_requests_pending,
            .uCustomParam = self.custom_param,
            .uCachePinnedBytes = self.cache_pinned_bytes,
        };
    }
};

pub const AkStreamRecord = struct {
    stream_id: u32,
    device_id: common.AkDeviceID,
    stream_name: []const u8,
    file_size: u64,
    custom_param_size: u32,
    custom_param: u32,
    is_auto_stream: bool,
    is_caching_stream: bool,

    pub fn fromC(value: c.WWISEC_AkStreamRecord, allocator: std.mem.Allocator) !AkStreamRecord {
        return .{
            .stream_id = value.uStreamID,
            .device_id = value.deviceID,
            .stream_name = try std.unicode.utf16leToUtf8Alloc(allocator, value.szStreamName),
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

pub const AkStreamData = struct {
    stream_id: u32,
    priority: u32,
    file_position: u64,
    target_buffering_size: u32,
    virtual_buffering_size: u32,
    buffered_size: u32,
    num_bytes_transfered: u32,
    num_bytes_transfered_low_level: u32,
    memory_referenced: u32,
    estimated_throughput: f32,
    active: bool,

    pub fn fromC(value: c.WWISEC_AkStreamData) AkStreamData {
        return AkStreamData{
            .stream_id = value.uStreamID,
            .priority = value.uPriority,
            .file_position = value.uFilePosition,
            .target_buffering_size = value.uTargetBufferingSize,
            .virtual_buffering_size = value.uVirtualBufferingSize,
            .buffered_size = value.uBufferedSize,
            .num_bytes_transfered = value.uNumBytesTransfered,
            .num_bytes_transfered_low_level = value.uNumBytesTransferedLowLevel,
            .memory_referenced = value.uMemoryReferenced,
            .estimated_throughput = value.fEstimatedThroughput,
            .active = value.bActive,
        };
    }

    pub fn toC(self: AkStreamData) c.WWISEC_AkStreamData {
        return .{
            .uStreamID = self.stream_id,
            .uPriority = self.priority,
            .uFilePosition = self.file_position,
            .uTargetBufferingSize = self.target_buffering_size,
            .uVirtualBufferingSize = self.virtual_buffering_size,
            .uBufferedSize = self.buffered_size,
            .uNumBytesTransfered = self.num_bytes_transfered,
            .uNumBytesTransferedLowLevel = self.num_bytes_transfered_low_level,
            .uMemoryReferenced = self.memory_referenced,
            .fEstimatedThroughput = self.estimated_throughput,
            .bActive = self.active,
        };
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

pub const IAkDeviceProfile = extern struct {};

pub const IAkStreamMgrProfile = extern struct {};

pub const IAkStdStream = extern struct {};

pub const IAkAutoStream = extern struct {};

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
        create_std_string: *const fn (
            self: *IAkStreamMgr,
            in_pszFileName: [*c]const c.AkOSChar,
            in_pFSFlags: ?*c.WWISEC_AkFileSystemFlags,
            in_eOpenMode: AkOpenMode,
            out_pStream: *?*IAkStdStream,
            in_bSyncOpen: bool,
        ) callconv(.C) c.WWISEC_AKRESULT,
        create_str_id: *const fn (
            self: *IAkStreamMgr,
            in_fileID: c.WWISEC_AkFileID,
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

            pub inline fn createStdString(
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

                const filename_oschar = try common.toOSChar(allocator, in_pszFileName);
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
                    filename_oschar,
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

            pub inline fn createAutoString(
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

            pub inline fn createAutoId(
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
