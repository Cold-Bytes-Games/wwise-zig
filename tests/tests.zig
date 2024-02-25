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

    const stream_mgr = AK.StreamMgr.create(&stream_settings);
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
        .is_auto_stream = false,
        .is_caching_stream = true,
    };

    var raw_stream_record = try stream_record.toC();

    try std.testing.expectEqualSlices(u16, std.unicode.utf8ToUtf16LeStringLiteral("Test Stream"), raw_stream_record.stream_name[0..raw_stream_record.string_size]);
    try std.testing.expectEqual(stream_record.stream_name.len, raw_stream_record.string_size);
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

    const stream_mgr = AK.StreamMgr.create(&stream_settings);
    try std.testing.expect(stream_mgr != null);
    try std.testing.expect(AK.IAkStreamMgr.get() != null);

    var device_settings: AK.StreamMgr.AkDeviceSettings = .{};
    AK.StreamMgr.getDefaultDeviceSettings(&device_settings);

    var io_hook = try AK.IOHooks.CAkDefaultIOHookDeferred.create(std.testing.allocator);
    defer io_hook.destroy(std.testing.allocator);

    try io_hook.init(&device_settings);
    defer io_hook.term();

    try io_hook.setBasePath(std.testing.allocator, ".");

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

    const stream_mgr = AK.StreamMgr.create(&stream_settings);
    try std.testing.expect(stream_mgr != null);
    try std.testing.expect(AK.IAkStreamMgr.get() != null);

    var device_settings: AK.StreamMgr.AkDeviceSettings = .{};
    AK.StreamMgr.getDefaultDeviceSettings(&device_settings);

    var io_hook = try AK.IOHooks.CAkFilePackageLowLevelIODeferred.create(std.testing.allocator);
    defer io_hook.destroy(std.testing.allocator);

    try io_hook.init(&device_settings);
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

    const stream_mgr = AK.StreamMgr.create(&stream_settings);
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

    const stream_mgr = AK.StreamMgr.create(&stream_settings);
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

const ZigTestIAkLowLevelIOHook = struct {
    destructor_called: bool = false,
    close_called: bool = false,
    get_block_size_called: bool = false,
    get_device_desc_called: bool = false,
    get_device_data_called: bool = false,
    batch_open_called: bool = false,
    batch_read_called: bool = false,
    batch_write_called: bool = false,
    batch_cancel_called: bool = false,
    output_searched_path_called: bool = false,
    close_size: i64 = 0,
    dummy_file_desc: AK.StreamMgr.AkFileDesc = undefined,

    pub fn destructor(self: *ZigTestIAkLowLevelIOHook) callconv(.C) void {
        self.destructor_called = true;
    }

    pub fn close(self: *ZigTestIAkLowLevelIOHook, in_file_desc: *AK.StreamMgr.AkFileDesc) callconv(.C) AK.AKRESULT {
        self.close_size = in_file_desc.file_size;
        self.close_called = true;

        return .success;
    }

    pub fn getBlockSize(self: *ZigTestIAkLowLevelIOHook, in_file_desc: *AK.StreamMgr.AkFileDesc) callconv(.C) u32 {
        _ = in_file_desc;
        self.get_block_size_called = true;
        return 512;
    }

    pub fn getDeviceDesc(self: *ZigTestIAkLowLevelIOHook, out_device_desc: *AK.NativeAkDeviceDesc) callconv(.C) void {
        self.get_device_desc_called = true;

        var zig_device_desc = AK.AkDeviceDesc{};
        zig_device_desc.can_write = false;
        zig_device_desc.can_read = true;
        zig_device_desc.device_name = "wwise-zig IO";

        out_device_desc.* = zig_device_desc.toC() catch unreachable;
    }

    pub fn getDeviceData(self: *ZigTestIAkLowLevelIOHook) callconv(.C) u32 {
        self.get_device_data_called = true;
        return 4269;
    }

    pub fn batchOpen(
        self: *ZigTestIAkLowLevelIOHook,
        in_num_files: u32,
        in_items: [*]*AK.StreamMgr.NativeAkAsyncFileOpenData,
    ) callconv(.C) void {
        for (0..in_num_files) |index| {
            self.dummy_file_desc.file_size = 6942;
            self.dummy_file_desc.device_id = 0;

            in_items[index].file_desc = &self.dummy_file_desc;

            if (in_items[index].callback) |callback| {
                callback(in_items[index], .success);
            }
        }

        self.batch_open_called = true;
    }

    pub fn batchRead(
        self: *ZigTestIAkLowLevelIOHook,
        in_num_transfers: u32,
        in_transfer_items: [*]AK.StreamMgr.IAkLowLevelIOHook.BatchIoTransferItem,
    ) callconv(.C) void {
        for (0..in_num_transfers) |index| {
            if (in_transfer_items[index].transfer_info) |transfer_info| {
                if (transfer_info.callback) |callback| {
                    callback(in_transfer_items[index].transfer_info, .fail);
                }
            }
        }

        self.batch_read_called = true;
    }

    pub fn batchWrite(
        self: *ZigTestIAkLowLevelIOHook,
        in_num_transfers: u32,
        in_transfer_items: [*]AK.StreamMgr.IAkLowLevelIOHook.BatchIoTransferItem,
    ) callconv(.C) void {
        for (0..in_num_transfers) |index| {
            if (in_transfer_items[index].transfer_info) |transfer_info| {
                if (transfer_info.callback) |callback| {
                    callback(in_transfer_items[index].transfer_info, .fail);
                }
            }
        }

        self.batch_write_called = true;
    }

    pub fn batchCancel(
        self: *ZigTestIAkLowLevelIOHook,
        in_num_transfers: u32,
        in_transfer_items: [*]AK.StreamMgr.IAkLowLevelIOHook.BatchIoTransferItem,
        io_cancel_all_transfers_for_this_file: [*]*bool,
    ) callconv(.C) void {
        _ = io_cancel_all_transfers_for_this_file;
        _ = in_transfer_items;
        _ = in_num_transfers;
        self.batch_cancel_called = true;
    }

    pub fn outputSearchedPaths(
        self: *ZigTestIAkLowLevelIOHook,
        in_result: AK.AKRESULT,
        in_file_open: *const AK.NativeAkFileOpenData,
        out_searched_path: [*]AK.AkOSChar,
        in_path_size: i32,
    ) callconv(.C) AK.AKRESULT {
        _ = in_path_size;
        _ = out_searched_path;
        _ = in_file_open;
        _ = in_result;
        self.output_searched_path_called = true;
        return .success;
    }

    pub fn createIAkLowLevelIOHook(self: *ZigTestIAkLowLevelIOHook) *AK.StreamMgr.IAkLowLevelIOHook {
        return AK.StreamMgr.IAkLowLevelIOHook.createInstance(
            self,
            &AK.StreamMgr.IAkLowLevelIOHook.FunctionTable{
                .destructor = @ptrCast(&destructor),
                .close = @ptrCast(&close),
                .get_block_size = @ptrCast(&getBlockSize),
                .get_device_desc = @ptrCast(&getDeviceDesc),
                .get_device_data = @ptrCast(&getDeviceData),
                .batch_open = @ptrCast(&batchOpen),
                .batch_read = @ptrCast(&batchRead),
                .batch_write = @ptrCast(&batchWrite),
                .batch_cancel = @ptrCast(&batchCancel),
                .output_searched_paths = @ptrCast(&outputSearchedPaths),
            },
        );
    }
};

const ZigTestIAkFileLocationResolver = struct {
    destructor_called: bool = false,
    get_next_preferred_device_called: bool = false,

    pub fn destructor(self: *ZigTestIAkFileLocationResolver) callconv(.C) void {
        self.destructor_called = true;
    }

    pub fn getNextPreferredDevice(
        self: *ZigTestIAkFileLocationResolver,
        in_file_open: *AK.StreamMgr.NativeAkAsyncFileOpenData,
        io_id_device: *AK.AkDeviceID,
    ) callconv(.C) AK.AKRESULT {
        _ = in_file_open;
        io_id_device.* = 0;
        self.get_next_preferred_device_called = true;

        return .success;
    }

    pub fn createIAkFileLocationResolver(self: *ZigTestIAkFileLocationResolver) *AK.StreamMgr.IAkFileLocationResolver {
        return AK.StreamMgr.IAkFileLocationResolver.createInstance(
            self,
            &AK.StreamMgr.IAkFileLocationResolver.FunctionTable{
                .destructor = @ptrCast(&destructor),
                .get_next_preferred_device = @ptrCast(&getNextPreferredDevice),
            },
        );
    }
};

test "Verify IAkLowLevelIOHook Zig inheritance from and to C++ by itself" {
    var memory_settings: AK.AkMemSettings = .{};
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    var zig_io_hook = ZigTestIAkLowLevelIOHook{};

    {
        var native_io_hook = zig_io_hook.createIAkLowLevelIOHook();
        defer AK.StreamMgr.IAkLowLevelIOHook.destroyInstance(native_io_hook);

        const file_desc = AK.StreamMgr.AkFileDesc{
            .file_size = 123456,
        };

        const block_size = native_io_hook.getBlockSize(&file_desc);
        try std.testing.expectEqual(@as(u32, 512), block_size);
        try std.testing.expect(zig_io_hook.get_block_size_called);

        var device_desc = AK.AkDeviceDesc{};
        defer std.testing.allocator.free(device_desc.device_name);

        try native_io_hook.getDeviceDesc(std.testing.allocator, &device_desc);
        try std.testing.expectEqualStrings("wwise-zig IO", device_desc.device_name);
        try std.testing.expect(device_desc.can_read);
        try std.testing.expect(!device_desc.can_write);
        try std.testing.expect(zig_io_hook.get_device_desc_called);

        const device_data = native_io_hook.getDeviceData();
        try std.testing.expectEqual(@as(u32, 4269), device_data);
        try std.testing.expect(zig_io_hook.get_device_data_called);

        var batch_transfers = [1]AK.StreamMgr.IAkLowLevelIOHook.BatchIoTransferItem{.{}};
        var async_file_open: [1]AK.StreamMgr.NativeAkAsyncFileOpenData = undefined;

        native_io_hook.batchOpen(0, @ptrCast(@alignCast(&async_file_open)));
        try std.testing.expect(zig_io_hook.batch_open_called);

        native_io_hook.batchRead(0, &batch_transfers);
        try std.testing.expect(zig_io_hook.batch_read_called);

        native_io_hook.batchWrite(0, &batch_transfers);
        try std.testing.expect(zig_io_hook.batch_write_called);

        try native_io_hook.close(&file_desc);
        try std.testing.expect(zig_io_hook.close_called);
        try std.testing.expectEqual(file_desc.file_size, zig_io_hook.close_size);
    }

    try std.testing.expect(zig_io_hook.destructor_called);
}

test "Dummy I/O Hook works" {
    var zig_io_hook = ZigTestIAkLowLevelIOHook{};
    var zig_file_resolver = ZigTestIAkFileLocationResolver{};

    {
        var memory_settings: AK.AkMemSettings = .{};
        AK.MemoryMgr.getDefaultSettings(&memory_settings);

        try AK.MemoryMgr.init(&memory_settings);
        defer AK.MemoryMgr.term();

        var stream_settings: AK.StreamMgr.AkStreamMgrSettings = .{};
        AK.StreamMgr.getDefaultSettings(&stream_settings);

        const stream_mgr = AK.StreamMgr.create(&stream_settings);
        try std.testing.expect(stream_mgr != null);
        try std.testing.expect(AK.IAkStreamMgr.get() != null);

        var device_settings: AK.StreamMgr.AkDeviceSettings = .{};
        AK.StreamMgr.getDefaultDeviceSettings(&device_settings);

        // Init file location resolver
        const native_file_resolver = zig_file_resolver.createIAkFileLocationResolver();
        defer AK.StreamMgr.IAkFileLocationResolver.destroyInstance(native_file_resolver);

        AK.StreamMgr.setFileLocationResolver(native_file_resolver);

        const native_io_hook = zig_io_hook.createIAkLowLevelIOHook();
        defer AK.StreamMgr.IAkLowLevelIOHook.destroyInstance(native_io_hook);

        const device_id = try AK.StreamMgr.createDevice(&device_settings, @ptrCast(native_io_hook));
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

    try std.testing.expect(zig_io_hook.close_called);
    try std.testing.expect(!zig_io_hook.get_block_size_called);
    try std.testing.expect(!zig_io_hook.get_device_desc_called);
    try std.testing.expect(zig_io_hook.batch_open_called);
    try std.testing.expect(zig_io_hook.batch_read_called);
    try std.testing.expect(!zig_io_hook.batch_write_called);
    try std.testing.expect(zig_io_hook.destructor_called);
    try std.testing.expectEqual(@as(i64, 6942), zig_io_hook.close_size);

    try std.testing.expect(zig_file_resolver.get_next_preferred_device_called);
}
