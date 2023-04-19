const std = @import("std");
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

    var init_settings: AK.AkInitSettings = undefined;
    AK.SoundEngine.getDefaultInitSettings(&init_settings);

    var platform_init_settings: AK.AkPlatformInitSettings = undefined;
    AK.SoundEngine.getDefaultPlatformInitSettings(&platform_init_settings);

    init_settings.plugin_dll_path = "C:\\test";

    try AK.SoundEngine.init(std.testing.allocator, init_settings, platform_init_settings);
    defer AK.SoundEngine.term();
}
