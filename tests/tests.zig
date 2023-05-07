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

test "vtable" {
    const TestInterface = extern struct {
        __v: *const Base.VTable = &vtable,
        default_value: i32 = 0,

        const vtable = Base.VTable{
            .virtual_destructor = .{
                .destructor = __destructor,
            },
            .print = _print,
        };

        const Base = AK.StreamMgr.TestVTable;
        const Self = @This();

        pub usingnamespace Base.Methods(Self);
        pub usingnamespace AK.CastMethods(@This());

        fn _print(iself: *Base, value: i32) callconv(.C) void {
            const self = Self.toMutableSelf(iself);
            std.debug.print("param={}, self={}\n", .{ value, self.default_value });
        }

        fn __destructor(iself: *Base) callconv(.C) void {
            var self = Self.toMutableSelf(iself);
            std.debug.print("Inside Zig TestInterface destructor, default_value={}\n", .{self.default_value});
        }
    };

    var zig_interface = TestInterface{
        .default_value = 1234,
    };

    AK.StreamMgr.setTestInstance(AK.StreamMgr.TestVTable.cast(&zig_interface));
    AK.StreamMgr.testCall();
    zig_interface.deinit();
}
