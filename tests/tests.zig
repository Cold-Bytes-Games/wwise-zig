const std = @import("std");
const builtin = @import("builtin");
const AK = @import("wwise-zig");

test "MemoryMgr init" {
    var memory_settings: AK.AkMemSettings = undefined;
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    try std.testing.expect(AK.MemoryMgr.isInitialized());
}

test "MemoryMgr dump to file" {
    var memory_settings: AK.AkMemSettings = undefined;
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    try AK.MemoryMgr.dumpToFile(std.testing.allocator, "test.dat");
}

test "AkSoundEngine init" {
    var memory_settings: AK.AkMemSettings = undefined;
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    var stream_settings: AK.StreamMgr.AkStreamMgrSettings = undefined;
    AK.StreamMgr.getDefaultSettings(&stream_settings);

    var stream_mgr = AK.StreamMgr.create(&stream_settings);
    try std.testing.expect(stream_mgr != null);
    try std.testing.expect(AK.IAkStreamMgr.get() != null);

    var device_settings: AK.StreamMgr.AkDeviceSettings = undefined;
    AK.StreamMgr.getDefaultDeviceSettings(&device_settings);

    var init_settings: AK.AkInitSettings = undefined;
    AK.SoundEngine.getDefaultInitSettings(&init_settings);

    var platform_init_settings: AK.AkPlatformInitSettings = undefined;
    AK.SoundEngine.getDefaultPlatformInitSettings(&platform_init_settings);

    init_settings.plugin_dll_path = "C:\\test";

    try AK.SoundEngine.init(std.testing.allocator, init_settings, platform_init_settings);
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

    try std.testing.expectEqualSlices(u16, std.unicode.utf8ToUtf16LeStringLiteral("Zig test"), raw_device_desc.szDeviceName[0..raw_device_desc.uStringSize]);
    try std.testing.expectEqual(device_desc.device_name.len, raw_device_desc.uStringSize);
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

    if (builtin.os.tag == .linux) {
        return error.SkipZigTest;
    }

    var memory_settings: AK.AkMemSettings = undefined;

    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    var stream_settings: AK.StreamMgr.AkStreamMgrSettings = undefined;
    AK.StreamMgr.getDefaultSettings(&stream_settings);

    var stream_mgr = AK.StreamMgr.create(&stream_settings);
    try std.testing.expect(stream_mgr != null);
    try std.testing.expect(AK.IAkStreamMgr.get() != null);

    var device_settings: AK.StreamMgr.AkDeviceSettings = undefined;
    AK.StreamMgr.getDefaultDeviceSettings(&device_settings);

    var io_hook = try AK.IOHooks.CAkDefaultIOHookBlocking.create(std.testing.allocator);
    defer io_hook.destroy(std.testing.allocator);

    try io_hook.init(device_settings, false);
    defer io_hook.term();

    try io_hook.setBasePath(std.testing.allocator, ".");

    var init_settings: AK.AkInitSettings = undefined;
    AK.SoundEngine.getDefaultInitSettings(&init_settings);

    var platform_init_settings: AK.AkPlatformInitSettings = undefined;
    AK.SoundEngine.getDefaultPlatformInitSettings(&platform_init_settings);

    try AK.SoundEngine.init(std.testing.allocator, init_settings, platform_init_settings);
    defer AK.SoundEngine.term();
}

test "CAkDefaultIOHookDeferred create" {
    if (AK.IOHooks.CAkDefaultIOHookDeferred == void) {
        return error.SkipZigTest;
    }

    if (builtin.os.tag == .linux) {
        return error.SkipZigTest;
    }

    var memory_settings: AK.AkMemSettings = undefined;
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    var stream_settings: AK.StreamMgr.AkStreamMgrSettings = undefined;
    AK.StreamMgr.getDefaultSettings(&stream_settings);

    var stream_mgr = AK.StreamMgr.create(&stream_settings);
    try std.testing.expect(stream_mgr != null);
    try std.testing.expect(AK.IAkStreamMgr.get() != null);

    var device_settings: AK.StreamMgr.AkDeviceSettings = undefined;
    AK.StreamMgr.getDefaultDeviceSettings(&device_settings);
    device_settings.scheduler_type_flags = AK.StreamMgr.AK_SCHEDULER_DEFERRED_LINED_UP;

    var io_hook = try AK.IOHooks.CAkDefaultIOHookDeferred.create(std.testing.allocator);
    defer io_hook.destroy(std.testing.allocator);

    try io_hook.init(device_settings, false);
    defer io_hook.term();

    try io_hook.setBasePath(std.testing.allocator, ".");

    var init_settings: AK.AkInitSettings = undefined;
    AK.SoundEngine.getDefaultInitSettings(&init_settings);

    var platform_init_settings: AK.AkPlatformInitSettings = undefined;
    AK.SoundEngine.getDefaultPlatformInitSettings(&platform_init_settings);

    try AK.SoundEngine.init(std.testing.allocator, init_settings, platform_init_settings);
    defer AK.SoundEngine.term();
}

test "CAkFilePackageLowLevelIOBlocking create" {
    if (AK.IOHooks.CAkFilePackageLowLevelIOBlocking == void) {
        return error.SkipZigTest;
    }

    if (builtin.os.tag == .linux) {
        return error.SkipZigTest;
    }

    var memory_settings: AK.AkMemSettings = undefined;
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    var stream_settings: AK.StreamMgr.AkStreamMgrSettings = undefined;
    AK.StreamMgr.getDefaultSettings(&stream_settings);

    var stream_mgr = AK.StreamMgr.create(&stream_settings);
    try std.testing.expect(stream_mgr != null);
    try std.testing.expect(AK.IAkStreamMgr.get() != null);

    var device_settings: AK.StreamMgr.AkDeviceSettings = undefined;
    AK.StreamMgr.getDefaultDeviceSettings(&device_settings);

    var io_hook = try AK.IOHooks.CAkFilePackageLowLevelIOBlocking.create(std.testing.allocator);
    defer io_hook.destroy(std.testing.allocator);

    try io_hook.init(device_settings, false);
    defer io_hook.term();

    try io_hook.setBasePath(std.testing.allocator, ".");

    const no_package_error = io_hook.loadFilePackage(std.testing.allocator, "NoPackage.pck");
    try std.testing.expectError(AK.WwiseError.FileNotFound, no_package_error);

    var init_settings: AK.AkInitSettings = undefined;
    AK.SoundEngine.getDefaultInitSettings(&init_settings);

    var platform_init_settings: AK.AkPlatformInitSettings = undefined;
    AK.SoundEngine.getDefaultPlatformInitSettings(&platform_init_settings);

    try AK.SoundEngine.init(std.testing.allocator, init_settings, platform_init_settings);
    defer AK.SoundEngine.term();
}

test "CAkFilePackageLowLevelIODeferred create" {
    if (AK.IOHooks.CAkFilePackageLowLevelIODeferred == void) {
        return error.SkipZigTest;
    }

    if (builtin.os.tag == .linux) {
        return error.SkipZigTest;
    }

    var memory_settings: AK.AkMemSettings = undefined;
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    var stream_settings: AK.StreamMgr.AkStreamMgrSettings = undefined;
    AK.StreamMgr.getDefaultSettings(&stream_settings);

    var stream_mgr = AK.StreamMgr.create(&stream_settings);
    try std.testing.expect(stream_mgr != null);
    try std.testing.expect(AK.IAkStreamMgr.get() != null);

    var device_settings: AK.StreamMgr.AkDeviceSettings = undefined;
    AK.StreamMgr.getDefaultDeviceSettings(&device_settings);
    device_settings.scheduler_type_flags = AK.StreamMgr.AK_SCHEDULER_DEFERRED_LINED_UP;

    var io_hook = try AK.IOHooks.CAkFilePackageLowLevelIODeferred.create(std.testing.allocator);
    defer io_hook.destroy(std.testing.allocator);

    try io_hook.init(device_settings, false);
    defer io_hook.term();

    try io_hook.setBasePath(std.testing.allocator, ".");

    const no_package_error = io_hook.loadFilePackage(std.testing.allocator, "NoPackage.pck");
    try std.testing.expectError(AK.WwiseError.FileNotFound, no_package_error);

    var init_settings: AK.AkInitSettings = undefined;
    AK.SoundEngine.getDefaultInitSettings(&init_settings);

    var platform_init_settings: AK.AkPlatformInitSettings = undefined;
    AK.SoundEngine.getDefaultPlatformInitSettings(&platform_init_settings);

    try AK.SoundEngine.init(std.testing.allocator, init_settings, platform_init_settings);
    defer AK.SoundEngine.term();
}

test "AkCommunication init" {
    if (AK.Comm == void) {
        return error.SkipZigTest;
    }

    var memory_settings: AK.AkMemSettings = undefined;
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    var stream_settings: AK.StreamMgr.AkStreamMgrSettings = undefined;
    AK.StreamMgr.getDefaultSettings(&stream_settings);

    var stream_mgr = AK.StreamMgr.create(&stream_settings);
    try std.testing.expect(stream_mgr != null);
    try std.testing.expect(AK.IAkStreamMgr.get() != null);

    var device_settings: AK.StreamMgr.AkDeviceSettings = undefined;
    AK.StreamMgr.getDefaultDeviceSettings(&device_settings);

    var init_settings: AK.AkInitSettings = undefined;
    AK.SoundEngine.getDefaultInitSettings(&init_settings);

    var platform_init_settings: AK.AkPlatformInitSettings = undefined;
    AK.SoundEngine.getDefaultPlatformInitSettings(&platform_init_settings);

    try AK.SoundEngine.init(std.testing.allocator, init_settings, platform_init_settings);
    defer AK.SoundEngine.term();

    var comm_settings: AK.Comm.AkCommSettings = undefined;
    try AK.Comm.getDefaultInitSettings(&comm_settings);

    comm_settings.setAppNetworkName("wwise-zig test");

    try AK.Comm.init(comm_settings);
    defer AK.Comm.term();
}

test "AkMusicEngine init" {
    var memory_settings: AK.AkMemSettings = undefined;
    AK.MemoryMgr.getDefaultSettings(&memory_settings);

    try AK.MemoryMgr.init(&memory_settings);
    defer AK.MemoryMgr.term();

    var stream_settings: AK.StreamMgr.AkStreamMgrSettings = undefined;
    AK.StreamMgr.getDefaultSettings(&stream_settings);

    var stream_mgr = AK.StreamMgr.create(&stream_settings);
    try std.testing.expect(stream_mgr != null);
    try std.testing.expect(AK.IAkStreamMgr.get() != null);

    var device_settings: AK.StreamMgr.AkDeviceSettings = undefined;
    AK.StreamMgr.getDefaultDeviceSettings(&device_settings);

    var init_settings: AK.AkInitSettings = undefined;
    AK.SoundEngine.getDefaultInitSettings(&init_settings);

    var platform_init_settings: AK.AkPlatformInitSettings = undefined;
    AK.SoundEngine.getDefaultPlatformInitSettings(&platform_init_settings);

    init_settings.plugin_dll_path = "C:\\test";

    try AK.SoundEngine.init(std.testing.allocator, init_settings, platform_init_settings);
    defer AK.SoundEngine.term();

    var music_settings: AK.MusicEngine.AkMusicSettings = undefined;
    AK.MusicEngine.getDefaultInitSettings(&music_settings);

    try AK.MusicEngine.init(&music_settings);
    defer AK.MusicEngine.term();
}
