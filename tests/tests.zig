const std = @import("std");
const builtin = @import("builtin");
const AK = @import("wwise-zig");

test "MemoryMgr init" {
    var memory_settings: AK.AkMemSettings = .{};
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    try std.testing.expect(AK.MemoryMgr.isInitialized());
}

test "MemoryMgr dump to file" {
    var memory_settings: AK.AkMemSettings = .{};
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    try AK.MemoryMgr.dumpToFile(std.testing.allocator, "test.dat");
}

test "AkSoundEngine init" {
    var memory_settings: AK.AkMemSettings = .{};
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    var stream_settings: AK.StreamMgr.AkStreamMgrSettings = .{};
    AK.StreamMgr.getDefaultSettings(&stream_settings);

    var stream_mgr = AK.StreamMgr.create(&stream_settings);
    try std.testing.expect(stream_mgr != null);
    try std.testing.expect(AK.IAkStreamMgr.get() != null);

    var device_settings: AK.StreamMgr.AkDeviceSettings = .{};
    AK.StreamMgr.getDefaultDeviceSettings(&device_settings);

    var init_settings: AK.AkInitSettings = .{};
    try AK.SoundEngine.getDefaultInitSettings(std.testing.allocator, &init_settings);

    var platform_init_settings: AK.AkPlatformInitSettings = .{};
    AK.SoundEngine.getDefaultPlatformInitSettings(&platform_init_settings);

    init_settings.plugin_dll_path = "C:\\test";

    try AK.SoundEngine.init(std.testing.allocator, &init_settings, &platform_init_settings);
    defer AK.SoundEngine.term();
}

test "AkDeviceDesc toC()" {
    var device_desc = AK.AkDeviceDesc{
        .device_id = 0,
        .can_write = true,
        .can_read = true,
        .device_name = "Zig test",
    };

    var raw_device_desc = try device_desc.toC();

    try std.testing.expectEqualSlices(u16, std.unicode.utf8ToUtf16LeStringLiteral("Zig test"), raw_device_desc.device_name[0..raw_device_desc.string_size]);
    try std.testing.expectEqual(device_desc.device_name.len, raw_device_desc.string_size);
}

test "AkStreamRecord toC()" {
    var stream_record = AK.AkStreamRecord{
        .stream_id = 0,
        .device_id = 0,
        .stream_name = "Test Stream",
        .file_size = 123456,
        .custom_param_size = 256,
        .custom_param = 42,
        .is_auto_stream = false,
        .is_caching_stream = true,
    };

    var raw_stream_record = try stream_record.toC();

    try std.testing.expectEqualSlices(u16, std.unicode.utf8ToUtf16LeStringLiteral("Test Stream"), raw_stream_record.szStreamName[0..raw_stream_record.uStringSize]);
    try std.testing.expectEqual(stream_record.stream_name.len, raw_stream_record.uStringSize);
}

test "CAkDefaultIOHookBlocking create" {
    if (AK.IOHooks.CAkDefaultIOHookBlocking == void) {
        return error.SkipZigTest;
    }

    var memory_settings: AK.AkMemSettings = .{};
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    var stream_settings: AK.StreamMgr.AkStreamMgrSettings = .{};
    AK.StreamMgr.getDefaultSettings(&stream_settings);

    var stream_mgr = AK.StreamMgr.create(&stream_settings);
    try std.testing.expect(stream_mgr != null);
    try std.testing.expect(AK.IAkStreamMgr.get() != null);

    var device_settings: AK.StreamMgr.AkDeviceSettings = .{};
    AK.StreamMgr.getDefaultDeviceSettings(&device_settings);

    var io_hook = try AK.IOHooks.CAkDefaultIOHookBlocking.create(std.testing.allocator);
    defer io_hook.destroy(std.testing.allocator);

    try io_hook.init(&device_settings, false);
    defer io_hook.term();

    try io_hook.setBasePath(std.testing.allocator, ".");

    var init_settings: AK.AkInitSettings = .{};
    try AK.SoundEngine.getDefaultInitSettings(std.testing.allocator, &init_settings);

    var platform_init_settings: AK.AkPlatformInitSettings = .{};
    AK.SoundEngine.getDefaultPlatformInitSettings(&platform_init_settings);

    try AK.SoundEngine.init(std.testing.allocator, &init_settings, &platform_init_settings);
    defer AK.SoundEngine.term();
}

test "CAkDefaultIOHookDeferred create" {
    if (AK.IOHooks.CAkDefaultIOHookDeferred == void) {
        return error.SkipZigTest;
    }

    var memory_settings: AK.AkMemSettings = .{};
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    var stream_settings: AK.StreamMgr.AkStreamMgrSettings = .{};
    AK.StreamMgr.getDefaultSettings(&stream_settings);

    var stream_mgr = AK.StreamMgr.create(&stream_settings);
    try std.testing.expect(stream_mgr != null);
    try std.testing.expect(AK.IAkStreamMgr.get() != null);

    var device_settings: AK.StreamMgr.AkDeviceSettings = .{};
    AK.StreamMgr.getDefaultDeviceSettings(&device_settings);
    device_settings.scheduler_type_flags = AK.StreamMgr.AK_SCHEDULER_DEFERRED_LINED_UP;

    var io_hook = try AK.IOHooks.CAkDefaultIOHookDeferred.create(std.testing.allocator);
    defer io_hook.destroy(std.testing.allocator);

    try io_hook.init(&device_settings, false);
    defer io_hook.term();

    try io_hook.setBasePath(std.testing.allocator, ".");

    var init_settings: AK.AkInitSettings = .{};
    try AK.SoundEngine.getDefaultInitSettings(std.testing.allocator, &init_settings);

    var platform_init_settings: AK.AkPlatformInitSettings = .{};
    AK.SoundEngine.getDefaultPlatformInitSettings(&platform_init_settings);

    try AK.SoundEngine.init(std.testing.allocator, &init_settings, &platform_init_settings);
    defer AK.SoundEngine.term();
}

test "CAkFilePackageLowLevelIOBlocking create" {
    if (AK.IOHooks.CAkFilePackageLowLevelIOBlocking == void) {
        return error.SkipZigTest;
    }

    var memory_settings: AK.AkMemSettings = .{};
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    var stream_settings: AK.StreamMgr.AkStreamMgrSettings = .{};
    AK.StreamMgr.getDefaultSettings(&stream_settings);

    var stream_mgr = AK.StreamMgr.create(&stream_settings);
    try std.testing.expect(stream_mgr != null);
    try std.testing.expect(AK.IAkStreamMgr.get() != null);

    var device_settings: AK.StreamMgr.AkDeviceSettings = .{};
    AK.StreamMgr.getDefaultDeviceSettings(&device_settings);

    var io_hook = try AK.IOHooks.CAkFilePackageLowLevelIOBlocking.create(std.testing.allocator);
    defer io_hook.destroy(std.testing.allocator);

    try io_hook.init(&device_settings, false);
    defer io_hook.term();

    try io_hook.setBasePath(std.testing.allocator, ".");

    const no_package_error = io_hook.loadFilePackage(std.testing.allocator, "NoPackage.pck");
    try std.testing.expectError(AK.WwiseError.FileNotFound, no_package_error);

    var init_settings: AK.AkInitSettings = .{};
    try AK.SoundEngine.getDefaultInitSettings(std.testing.allocator, &init_settings);

    var platform_init_settings: AK.AkPlatformInitSettings = .{};
    AK.SoundEngine.getDefaultPlatformInitSettings(&platform_init_settings);

    try AK.SoundEngine.init(std.testing.allocator, &init_settings, &platform_init_settings);
    defer AK.SoundEngine.term();
}

test "CAkFilePackageLowLevelIODeferred create" {
    if (AK.IOHooks.CAkFilePackageLowLevelIODeferred == void) {
        return error.SkipZigTest;
    }

    var memory_settings: AK.AkMemSettings = .{};
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    var stream_settings: AK.StreamMgr.AkStreamMgrSettings = .{};
    AK.StreamMgr.getDefaultSettings(&stream_settings);

    var stream_mgr = AK.StreamMgr.create(&stream_settings);
    try std.testing.expect(stream_mgr != null);
    try std.testing.expect(AK.IAkStreamMgr.get() != null);

    var device_settings: AK.StreamMgr.AkDeviceSettings = .{};
    AK.StreamMgr.getDefaultDeviceSettings(&device_settings);
    device_settings.scheduler_type_flags = AK.StreamMgr.AK_SCHEDULER_DEFERRED_LINED_UP;

    var io_hook = try AK.IOHooks.CAkFilePackageLowLevelIODeferred.create(std.testing.allocator);
    defer io_hook.destroy(std.testing.allocator);

    try io_hook.init(&device_settings, false);
    defer io_hook.term();

    try io_hook.setBasePath(std.testing.allocator, ".");

    const no_package_error = io_hook.loadFilePackage(std.testing.allocator, "NoPackage.pck");
    try std.testing.expectError(AK.WwiseError.FileNotFound, no_package_error);

    var init_settings: AK.AkInitSettings = .{};
    try AK.SoundEngine.getDefaultInitSettings(std.testing.allocator, &init_settings);

    var platform_init_settings: AK.AkPlatformInitSettings = .{};
    AK.SoundEngine.getDefaultPlatformInitSettings(&platform_init_settings);

    try AK.SoundEngine.init(std.testing.allocator, &init_settings, &platform_init_settings);
    defer AK.SoundEngine.term();
}

test "AkCommunication init" {
    if (AK.Comm == void) {
        return error.SkipZigTest;
    }

    var memory_settings: AK.AkMemSettings = .{};
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    var stream_settings: AK.StreamMgr.AkStreamMgrSettings = .{};
    AK.StreamMgr.getDefaultSettings(&stream_settings);

    var stream_mgr = AK.StreamMgr.create(&stream_settings);
    try std.testing.expect(stream_mgr != null);
    try std.testing.expect(AK.IAkStreamMgr.get() != null);

    var device_settings: AK.StreamMgr.AkDeviceSettings = .{};
    AK.StreamMgr.getDefaultDeviceSettings(&device_settings);

    var init_settings: AK.AkInitSettings = .{};
    try AK.SoundEngine.getDefaultInitSettings(std.testing.allocator, &init_settings);

    var platform_init_settings: AK.AkPlatformInitSettings = .{};
    AK.SoundEngine.getDefaultPlatformInitSettings(&platform_init_settings);

    try AK.SoundEngine.init(std.testing.allocator, &init_settings, &platform_init_settings);
    defer AK.SoundEngine.term();

    var comm_settings: AK.Comm.AkCommSettings = .{};
    try AK.Comm.getDefaultInitSettings(&comm_settings);

    comm_settings.setAppNetworkName("wwise-zig test");

    try AK.Comm.init(&comm_settings);
    defer AK.Comm.term();

    const current_comm_settings = AK.Comm.getCurrentSettings();
    try std.testing.expectEqual(comm_settings.ports, current_comm_settings.ports);
    try std.testing.expectEqual(comm_settings.comm_system, current_comm_settings.comm_system);
    try std.testing.expectEqual(comm_settings.init_system_lib, current_comm_settings.init_system_lib);
    try std.testing.expectEqualSlices(u8, comm_settings.app_network_name[0..], current_comm_settings.app_network_name[0..]);
    try std.testing.expectEqualSlices(u8, comm_settings.comm_proxy_server_url[0..], current_comm_settings.comm_proxy_server_url[0..]);
}

test "AkMusicEngine init" {
    var memory_settings: AK.AkMemSettings = .{};
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    var stream_settings: AK.StreamMgr.AkStreamMgrSettings = .{};
    AK.StreamMgr.getDefaultSettings(&stream_settings);

    var stream_mgr = AK.StreamMgr.create(&stream_settings);
    try std.testing.expect(stream_mgr != null);
    try std.testing.expect(AK.IAkStreamMgr.get() != null);

    var device_settings: AK.StreamMgr.AkDeviceSettings = .{};
    AK.StreamMgr.getDefaultDeviceSettings(&device_settings);

    var init_settings: AK.AkInitSettings = .{};
    try AK.SoundEngine.getDefaultInitSettings(std.testing.allocator, &init_settings);

    var platform_init_settings: AK.AkPlatformInitSettings = .{};
    AK.SoundEngine.getDefaultPlatformInitSettings(&platform_init_settings);

    init_settings.plugin_dll_path = "C:\\test";

    try AK.SoundEngine.init(std.testing.allocator, &init_settings, &platform_init_settings);
    defer AK.SoundEngine.term();

    var music_settings: AK.MusicEngine.AkMusicSettings = .{};
    AK.MusicEngine.getDefaultInitSettings(&music_settings);

    try AK.MusicEngine.init(&music_settings);
    defer AK.MusicEngine.term();
}

const DummyFileHandle = struct {
    file_size: usize = 1024,
    bytes_read: usize = 0,
    bytes_written: usize = 0,
    is_writing: bool = false,
    is_string: bool = false,
};

const ZigTestIAkOHookBlocking = struct {
    destructor_called: bool = false,
    close_called: bool = false,
    get_block_size_called: bool = false,
    get_device_desc_called: bool = false,
    get_device_data_called: bool = false,
    read_called: bool = false,
    write_called: bool = false,
    close_size: i64 = 0,

    pub fn destructor(self: *ZigTestIAkOHookBlocking) callconv(.C) void {
        self.destructor_called = true;
    }

    pub fn close(self: *ZigTestIAkOHookBlocking, in_file_desc: *AK.StreamMgr.AkFileDesc) callconv(.C) AK.AKRESULT {
        self.close_size = in_file_desc.file_size;
        self.close_called = true;

        return .success;
    }

    pub fn getBlockSize(self: *ZigTestIAkOHookBlocking, in_file_desc: *AK.StreamMgr.AkFileDesc) callconv(.C) u32 {
        _ = in_file_desc;
        self.get_block_size_called = true;
        return 512;
    }

    pub fn getDeviceDesc(self: *ZigTestIAkOHookBlocking, out_device_desc: *AK.NativeAkDeviceDesc) callconv(.C) void {
        self.get_device_desc_called = true;

        var zig_device_desc = AK.AkDeviceDesc{};
        zig_device_desc.can_write = false;
        zig_device_desc.can_read = true;
        zig_device_desc.device_name = "wwise-zig IO";

        out_device_desc.* = zig_device_desc.toC() catch unreachable;
    }

    pub fn getDeviceData(self: *ZigTestIAkOHookBlocking) callconv(.C) u32 {
        self.get_device_data_called = true;
        return 4269;
    }

    pub fn read(self: *ZigTestIAkOHookBlocking, in_file_desc: *AK.StreamMgr.AkFileDesc, in_heuristics: *AK.StreamMgr.AkIoHeuristics, out_buffer: ?*anyopaque, in_transfer_info: *AK.StreamMgr.AkIOTransferInfo) callconv(.C) AK.AKRESULT {
        _ = in_file_desc;
        _ = in_heuristics;

        self.read_called = true;

        if (out_buffer) |checked_buffer| {
            var read_buffer = @as([*]u8, @ptrCast(checked_buffer));
            @memset(read_buffer[in_transfer_info.file_position..in_transfer_info.requested_size], 0xC1);
        }

        return .success;
    }

    pub fn write(self: *ZigTestIAkOHookBlocking, in_file_desc: *AK.StreamMgr.AkFileDesc, in_heuristics: *AK.StreamMgr.AkIoHeuristics, in_data: ?*anyopaque, in_transfer_info: *AK.StreamMgr.AkIOTransferInfo) callconv(.C) AK.AKRESULT {
        _ = in_heuristics;
        _ = in_transfer_info;
        _ = in_data;
        _ = in_file_desc;

        self.write_called = true;

        return .success;
    }

    pub fn createIAkIOHookBlocking(self: *ZigTestIAkOHookBlocking) *AK.StreamMgr.IAkIOHookBlocking {
        return AK.StreamMgr.IAkIOHookBlocking.createInstance(
            self,
            &AK.StreamMgr.IAkIOHookBlocking.FunctionTable{
                .destructor = @ptrCast(&destructor),
                .close = @ptrCast(&close),
                .get_block_size = @ptrCast(&getBlockSize),
                .get_device_desc = @ptrCast(&getDeviceDesc),
                .get_device_data = @ptrCast(&getDeviceData),
                .read = @ptrCast(&read),
                .write = @ptrCast(&write),
            },
        );
    }
};

const ZigTestIAkFileLocationResolver = struct {
    open_string_called: bool = false,
    open_id_called: bool = false,
    output_searched_paths_string_called: bool = false,
    output_searched_paths_id_called: bool = false,
    area_allocator: std.heap.ArenaAllocator = undefined,

    pub fn destructor(self: *ZigTestIAkFileLocationResolver) callconv(.C) void {
        self.area_allocator.deinit();
    }

    pub fn openString(
        self: *ZigTestIAkFileLocationResolver,
        in_file_name: [*]const AK.AkOSChar,
        in_open_mode: AK.AkOpenMode,
        in_flags: ?*AK.AkFileSystemFlags,
        io_sync_open: *bool,
        io_file_desc: *AK.StreamMgr.AkFileDesc,
    ) callconv(.C) AK.AKRESULT {
        _ = io_sync_open;
        _ = in_flags;
        _ = in_file_name;

        self.open_string_called = true;

        var file_handle = self.area_allocator.allocator().create(DummyFileHandle) catch return .insufficient_memory;
        file_handle.* = DummyFileHandle{ .is_string = true, .is_writing = (in_open_mode == .write or in_open_mode == .write_ovrwr or in_open_mode == .read_write) };

        io_file_desc.file_size = @intCast(file_handle.file_size);
        io_file_desc.file_handle = file_handle;

        return .success;
    }

    pub fn openID(
        self: *ZigTestIAkFileLocationResolver,
        in_file_id: AK.AkFileID,
        in_open_mode: AK.AkOpenMode,
        in_flags: ?*AK.AkFileSystemFlags,
        io_sync_open: *bool,
        io_file_desc: *AK.StreamMgr.AkFileDesc,
    ) callconv(.C) AK.AKRESULT {
        _ = io_sync_open;
        _ = in_flags;
        _ = in_file_id;

        self.open_id_called = true;

        var file_handle = self.area_allocator.allocator().create(DummyFileHandle) catch return .insufficient_memory;
        file_handle.* = DummyFileHandle{ .is_string = false, .is_writing = (in_open_mode == .write or in_open_mode == .write_ovrwr or in_open_mode == .read_write) };

        io_file_desc.file_size = @intCast(file_handle.file_size);
        io_file_desc.file_handle = file_handle;

        return .success;
    }

    pub fn outputSearchedPathsString(
        self: *ZigTestIAkFileLocationResolver,
        in_result: *const AK.AKRESULT,
        in_file_name: [*]const AK.AkOSChar,
        in_flags: ?*AK.AkFileSystemFlags,
        in_open_mode: AK.AkOpenMode,
        out_searched_path: *[*]const AK.AkOSChar,
        in_path_size: i32,
    ) callconv(.C) AK.AKRESULT {
        _ = in_path_size;
        _ = out_searched_path;
        _ = in_open_mode;
        _ = in_flags;
        _ = in_file_name;
        _ = in_result;
        _ = self;
        return .not_implemented;
    }

    pub fn outputSearchedPathsID(
        self: *ZigTestIAkFileLocationResolver,
        in_result: *const AK.AKRESULT,
        in_file_id: AK.AkFileID,
        in_flags: ?*AK.AkFileSystemFlags,
        in_open_mode: AK.AkOpenMode,
        out_searched_path: *[*]const AK.AkOSChar,
        in_path_size: i32,
    ) callconv(.C) AK.AKRESULT {
        _ = in_path_size;
        _ = out_searched_path;
        _ = in_open_mode;
        _ = in_flags;
        _ = in_file_id;
        _ = in_result;
        _ = self;
        return .not_implemented;
    }

    pub fn createIAkFileLocationResolver(self: *ZigTestIAkFileLocationResolver) *AK.StreamMgr.IAkFileLocationResolver {
        return AK.StreamMgr.IAkFileLocationResolver.createInstance(
            self,
            &AK.StreamMgr.IAkFileLocationResolver.FunctionTable{
                .destructor = @ptrCast(&destructor),
                .open_string = @ptrCast(&openString),
                .open_id = @ptrCast(&openID),
                .output_searched_paths_string = @ptrCast(&outputSearchedPathsString),
                .output_searched_paths_id = @ptrCast(&outputSearchedPathsID),
            },
        );
    }
};

test "Verify IAkIOHookBlocking Zig inheritance from and to C++ by itself" {
    var memory_settings: AK.AkMemSettings = .{};
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    var zig_io_blocking = ZigTestIAkOHookBlocking{};

    {
        var native_io_blocking = zig_io_blocking.createIAkIOHookBlocking();
        defer AK.StreamMgr.IAkIOHookBlocking.destroyInstance(native_io_blocking);

        const file_desc = AK.StreamMgr.AkFileDesc{
            .file_size = 123456,
        };

        const heuristics = AK.StreamMgr.AkIoHeuristics{};

        const block_size = native_io_blocking.getBlockSize(&file_desc);
        try std.testing.expectEqual(@as(u32, 512), block_size);
        try std.testing.expect(zig_io_blocking.get_block_size_called);

        var device_desc = AK.AkDeviceDesc{};
        defer std.testing.allocator.free(device_desc.device_name);

        try native_io_blocking.getDeviceDesc(std.testing.allocator, &device_desc);
        try std.testing.expectEqualStrings("wwise-zig IO", device_desc.device_name);
        try std.testing.expect(device_desc.can_read);
        try std.testing.expect(!device_desc.can_write);
        try std.testing.expect(zig_io_blocking.get_device_desc_called);

        const device_data = native_io_blocking.getDeviceData();
        try std.testing.expectEqual(@as(u32, 4269), device_data);
        try std.testing.expect(zig_io_blocking.get_device_data_called);

        var transfer_info = AK.StreamMgr.AkIOTransferInfo{};

        try native_io_blocking.read(&file_desc, &heuristics, null, &transfer_info);
        try std.testing.expect(zig_io_blocking.read_called);

        try native_io_blocking.write(&file_desc, &heuristics, null, &transfer_info);
        try std.testing.expect(zig_io_blocking.write_called);

        try native_io_blocking.close(&file_desc);
        try std.testing.expect(zig_io_blocking.close_called);
        try std.testing.expectEqual(file_desc.file_size, zig_io_blocking.close_size);
    }

    try std.testing.expect(zig_io_blocking.destructor_called);
}

test "Dummy I/O Hook works" {
    var zig_io_blocking = ZigTestIAkOHookBlocking{};
    var zig_file_resolver = ZigTestIAkFileLocationResolver{};

    {
        var memory_settings: AK.AkMemSettings = .{};
        AK.MemoryMgr.getDefaultSettings(&memory_settings);

        try AK.MemoryMgr.init(&memory_settings);
        defer AK.MemoryMgr.term();

        var stream_settings: AK.StreamMgr.AkStreamMgrSettings = .{};
        AK.StreamMgr.getDefaultSettings(&stream_settings);

        var stream_mgr = AK.StreamMgr.create(&stream_settings);
        try std.testing.expect(stream_mgr != null);
        try std.testing.expect(AK.IAkStreamMgr.get() != null);

        var device_settings: AK.StreamMgr.AkDeviceSettings = .{};
        AK.StreamMgr.getDefaultDeviceSettings(&device_settings);

        // Init file location resolver

        zig_file_resolver.area_allocator = std.heap.ArenaAllocator.init(std.testing.allocator);

        var native_file_resolver = zig_file_resolver.createIAkFileLocationResolver();
        defer AK.StreamMgr.IAkFileLocationResolver.destroyInstance(native_file_resolver);

        AK.StreamMgr.setFileLocationResolver(native_file_resolver);

        var native_io_blocking = zig_io_blocking.createIAkIOHookBlocking();
        defer AK.StreamMgr.IAkIOHookBlocking.destroyInstance(native_io_blocking);

        var device_id = AK.StreamMgr.createDevice(&device_settings, @ptrCast(native_io_blocking));
        defer AK.StreamMgr.destroyDevice(device_id) catch {};

        var init_settings: AK.AkInitSettings = .{};
        try AK.SoundEngine.getDefaultInitSettings(std.testing.allocator, &init_settings);

        var platform_init_settings: AK.AkPlatformInitSettings = .{};
        AK.SoundEngine.getDefaultPlatformInitSettings(&platform_init_settings);

        try AK.SoundEngine.init(std.testing.allocator, &init_settings, &platform_init_settings);
        defer AK.SoundEngine.term();

        const load_bank_error = AK.SoundEngine.loadBankString(std.testing.allocator, "test.bnk", .{});
        try std.testing.expectError(AK.WwiseError.InvalidFile, load_bank_error);
    }

    try std.testing.expect(zig_io_blocking.close_called);
    try std.testing.expect(zig_io_blocking.get_block_size_called);
    try std.testing.expect(!zig_io_blocking.get_device_desc_called);
    try std.testing.expect(zig_io_blocking.read_called);
    try std.testing.expect(zig_io_blocking.destructor_called);
    try std.testing.expect(!zig_io_blocking.write_called);
    try std.testing.expectEqual(@as(i64, 1024), zig_io_blocking.close_size);

    try std.testing.expect(zig_file_resolver.open_string_called);
    try std.testing.expect(!zig_file_resolver.open_id_called);
}
