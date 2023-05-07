const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const settings = @import("settings.zig");

pub const AkOpenMode = enum(common.DefaultEnumType) {
    read,
    write,
    write_overwr,
    read_write,
};

pub const AkAutoStmBufSettings = extern struct {};

pub const AkAutoStmHeuristics = extern struct {};

pub const AkFileSystemFlags = extern struct {};

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
        getStreamMgrProfile: *const fn (
            self: *IAkStreamMgr,
        ) callconv(.C) ?*IAkStreamMgrProfile,
        create_std_string: *const fn (
            self: *IAkStreamMgr,
            in_pszFileName: [*c]const c.AkOSChar,
            in_pFSFlags: ?*AkFileSystemFlags,
            in_eOpenMode: AkOpenMode,
            out_pStream: *?*IAkStdStream,
            in_bSyncOpen: bool,
        ) callconv(.C) c.WWISEC_AKRESULT,
        create_str_id: *const fn (
            self: *IAkStreamMgr,
            in_fileID: c.WWISEC_AkFileID,
            in_pFSFlags: ?*AkFileSystemFlags,
            in_eOpenMode: AkOpenMode,
            out_pStream: *?*IAkStdStream,
            in_bSyncOpen: bool,
        ) callconv(.C) c.WWISEC_AKRESULT,
        create_auto_string: *const fn (
            self: *IAkStreamMgr,
            in_pszFileName: [*c]const c.AkOSChar,
            in_pFSFlags: ?*AkFileSystemFlags,
            in_heuristics: *const AkAutoStmHeuristics,
            in_pBufferSettings: ?*AkAutoStmBufSettings,
            out_pStream: *?*IAkAutoStream,
            in_bSyncOpen: bool,
        ) callconv(.C) c.WWISEC_AKRESULT,
        create_auto_id: *const fn (
            self: *IAkStreamMgr,
            in_fileID: c.WWISEC_AkFileID,
            in_pFSFlags: ?*AkFileSystemFlags,
            in_heuristics: *const AkAutoStmHeuristics,
            in_pBufferSettings: ?*AkAutoStmBufSettings,
            out_pStream: *?*IAkAutoStream,
            in_bSyncOpen: bool,
        ) callconv(.C) c.WWISEC_AKRESULT,
        create_auto_memory: *const fn (
            self: *IAkStreamMgr,
            in_pBuffer: ?*anyopaque,
            in_uSize: c.AkUInt64,
            in_heuristics: *const AkAutoStmHeuristics,
            out_pStream: *?*IAkAutoStream,
        ) callconv(.C) c.WWISEC_AKRESULT,
        pin_file_in_cache: *const fn (
            self: *IAkStreamMgr,
            in_fileID: c.WWISEC_AkFileID,
            in_pFSFlags: ?*AkFileSystemFlags,
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
                return @ptrCast(*const IAkStreamMgr.VTable, self.__v).getStreamMgrProfile(@ptrCast(*IAkStreamMgr, self));
            }

            pub inline fn createStdString(
                self: *T,
                fallback_allocator: std.mem.Allocator,
                in_pszFileName: []const u8,
                in_pFSFlags: *AkFileSystemFlags,
                in_eOpenMode: AkOpenMode,
                out_pStream: *?*IAkStdStream,
                in_bSyncOpen: bool,
            ) common.WwiseError!void {
                var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
                var allocator = stack_char_allocator.get();

                const filename_oschar = try common.toOSChar(allocator, in_pszFileName);
                defer allocator.free(filename_oschar);

                return common.handleAkResult(@ptrCast(*const IAkStreamMgr.VTable, self.__v).create_std_string(
                    @ptrCast(*IAkStreamMgr, self),
                    filename_oschar,
                    in_pFSFlags,
                    in_eOpenMode,
                    out_pStream,
                    in_bSyncOpen,
                ));
            }

            pub inline fn createStdId(
                self: *T,
                in_fileID: c.WWISEC_AkFileID,
                in_pFSFlags: ?*AkFileSystemFlags,
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
                in_pFSFlags: ?*AkFileSystemFlags,
                in_heuristics: *const AkAutoStmHeuristics,
                in_pBufferSettings: ?*AkAutoStmBufSettings,
                out_pStream: *?*IAkAutoStream,
                in_bSyncOpen: bool,
            ) common.WwiseError!void {
                var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
                var allocator = stack_char_allocator.get();

                const filename_oschar = try common.toOSChar(allocator, in_pszFileName);
                defer allocator.free(filename_oschar);

                return common.handleAkResult(@ptrCast(*const IAkStreamMgr.VTable, self.__v).create_auto_string(
                    @ptrCast(*IAkStreamMgr, self),
                    filename_oschar,
                    in_pFSFlags,
                    in_heuristics,
                    in_pBufferSettings,
                    out_pStream,
                    in_bSyncOpen,
                ));
            }

            pub inline fn createAutoId(
                self: *T,
                in_fileID: c.WWISEC_AkFileID,
                in_pFSFlags: ?*AkFileSystemFlags,
                in_heuristics: *const AkAutoStmHeuristics,
                in_pBufferSettings: ?*AkAutoStmBufSettings,
                out_pStream: *?*IAkAutoStream,
                in_bSyncOpen: bool,
            ) common.WwiseError!void {
                return common.handleAkResult(@ptrCast(*const IAkStreamMgr.VTable, self.__v).create_auto_id(
                    @ptrCast(*IAkStreamMgr, self),
                    in_fileID,
                    in_pFSFlags,
                    in_heuristics,
                    in_pBufferSettings,
                    out_pStream,
                    in_bSyncOpen,
                ));
            }

            pub inline fn createAutoMemory(
                self: *T,
                in_pBuffer: ?*anyopaque,
                in_uSize: c.AkUInt64,
                in_heuristics: *const AkAutoStmHeuristics,
                out_pStream: *?*IAkAutoStream,
            ) common.WwiseError!void {
                return common.handleAkResult(@ptrCast(*const IAkStreamMgr.VTable, self.__v).create_auto_memory(
                    @ptrCast(*IAkStreamMgr, self),
                    in_pBuffer,
                    in_uSize,
                    in_heuristics,
                    out_pStream,
                ));
            }

            pub inline fn pinFileInCache(
                self: *T,
                in_fileID: c.WWISEC_AkFileID,
                in_pFSFlags: ?*AkFileSystemFlags,
                in_uPriority: c.WWISEC_AkPriority,
            ) common.WwiseError!void {
                return common.handleAkResult(@ptrCast(*const IAkStreamMgr.VTable, self.__v).pin_file_in_cache(
                    @ptrCast(*IAkStreamMgr, self),
                    in_fileID,
                    in_pFSFlags,
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
