const c = @import("wwise_c");
const enums = @import("enums.zig");
const std = @import("std");
const zig = @import("zig.zig");

pub const IMMDevice = anyopaque;

pub fn getDeviceID(in_pDevice: ?*IMMDevice) u32 {
    return c.WWISEC_AK_GetDeviceID(@ptrCast(in_pDevice));
}

pub fn getDeviceIDFromName(fallback_allocator: std.mem.Allocator, in_token: []const u8) !u32 {
    var stack_char_allocator = zig.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_token = try zig.toOSCharUtf16(allocator, in_token);
    defer allocator.free(raw_token);

    return c.WWISEC_AK_GetDeviceIDFromName(raw_token);
}

pub const GetWindowsDeviceNameOptionalArgs = struct {
    device_state_mask: enums.AkAudioDeviceState = enums.AkAudioDeviceState.All,
};

pub fn getWindowsDeviceName(allocator: std.mem.Allocator, index: i32, out_device_id: *u32, optional_args: GetWindowsDeviceNameOptionalArgs) ![]u8 {
    const raw_name = c.WWISEC_AK_GetWindowsDeviceName(index, out_device_id, optional_args.device_state_mask.toC());

    const converted_name = try zig.fromOSCharUtf16(allocator, raw_name);
    return converted_name;
}

pub const GetWindowsDeviceCountOptionalArgs = struct {
    device_state_mask: enums.AkAudioDeviceState = enums.AkAudioDeviceState.All,
};

pub fn getWindowsDeviceCount(optional_args: GetWindowsDeviceCountOptionalArgs) u32 {
    return c.WWISEC_AK_GetWindowsDeviceCount(optional_args.device_state_mask.toC());
}

pub const GetWindowsDeviceOptionalArgs = struct {
    device_state_mask: enums.AkAudioDeviceState = enums.AkAudioDeviceState.All,
};

pub fn getWindowsDevice(in_index: i32, out_device_id: *u32, out_device: **IMMDevice, optional_args: GetWindowsDeviceOptionalArgs) bool {
    return c.WWISEC_AK_GetWindowsDevice(in_index, out_device_id, @ptrCast(out_device), optional_args.device_state_mask.toC());
}
