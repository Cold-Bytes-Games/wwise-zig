const std = @import("std");
const builtin = @import("builtin");
const c = @import("wwise_c");
const wwise_options = @import("wwise_options");

pub const AkOSChar = c.AkOSChar;
pub const AkUtf16 = c.AkUtf16;

pub const AK_MAX_PATH = c.AK_MAX_PATH;

pub const AK_BANK_PLATFORM_DATA_ALIGNMENT = c.AK_BANK_PLATFORM_DATA_ALIGNMENT;

pub const IAkSoftwareCodec = opaque {};
pub const IAkFileCodec = opaque {};
pub const IAkGrainCodec = opaque {};

pub const AkCreateFileSourceCallback = ?*const fn (in_ctx: ?*anyopaque) callconv(.c) ?*IAkSoftwareCodec;
pub const AkCreateBankSourceCallback = ?*const fn (in_ctx: ?*anyopaque) callconv(.c) ?*IAkSoftwareCodec;
pub const AkCreateFileCodecCallback = ?*const fn () callconv(.c) ?*IAkFileCodec;
pub const AkCreateGrainCodecCallback = ?*const fn () callconv(.c) ?*IAkGrainCodec;

pub const AkCodecDescriptor = extern struct {
    file_src_create_func: AkCreateFileSourceCallback,
    bank_src_create_func: AkCreateBankSourceCallback,
    file_codec_create_func: AkCreateFileCodecCallback,
    grain_codec_create_func: AkCreateGrainCodecCallback,

    pub fn fromC(value: c.WWISEC_AkCodecDescriptor) AkCodecDescriptor {
        return @bitCast(value);
    }

    pub fn toC(self: AkCodecDescriptor) c.WWISEC_AkCodecDescriptor {
        return @bitCast(self);
    }
};

pub const AkFileHandle = ?*anyopaque;

pub const AkAudioDeviceState = packed struct(DefaultEnumType) {
    active: bool = false,
    disabled: bool = false,
    not_present: bool = false,
    unplugged: bool = false,
    pad: u28 = 0,

    pub const All = AkAudioDeviceState{
        .active = true,
        .disabled = true,
        .not_present = true,
        .unplugged = true,
    };

    pub inline fn fromC(value: c.WWISEC_AkAudioDeviceState) AkAudioDeviceState {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkAudioDeviceState) c.WWISEC_AkAudioDeviceState {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@as(DefaultEnumType, @bitCast(AkAudioDeviceState{ .active = true })) == c.WWISEC_AkDeviceState_Active);
        std.debug.assert(@as(DefaultEnumType, @bitCast(AkAudioDeviceState{ .disabled = true })) == c.WWISEC_AkDeviceState_Disabled);
        std.debug.assert(@as(DefaultEnumType, @bitCast(AkAudioDeviceState{ .not_present = true })) == c.WWISEC_AkDeviceState_NotPresent);
        std.debug.assert(@as(DefaultEnumType, @bitCast(AkAudioDeviceState{ .unplugged = true })) == c.WWISEC_AkDeviceState_Unplugged);
    }
};

pub const AkDeviceDescription = struct {
    id_device: u32 = 0,
    device_name: []const u8 = "",
    device_state_mask: AkAudioDeviceState = .{},
    is_default_device: bool = false,

    pub fn deinit(self: AkDeviceDescription, allocator: std.mem.Allocator) void {
        if (!std.mem.eql(u8, self.device_name[0..], "")) {
            allocator.free(self.device_name);
        }
    }

    pub fn fromC(allocator: std.mem.Allocator, value: c.WWISEC_AkDeviceDescription) !AkDeviceDescription {
        return .{
            .id_device = value.idDevice,
            .device_name = try fromOSChar(allocator, @as(?[*:0]const AkOSChar, @ptrCast(value.deviceName[0..]))),
            .device_state_mask = AkAudioDeviceState.fromC(value.deviceStateMask),
            .is_default_device = value.isDefaultDevice,
        };
    }

    pub fn toC(self: AkDeviceDescription) !c.WWISEC_AkDeviceDescription {
        var result: c.WWISEC_AkDeviceDescription = undefined;
        result.idDevice = self.id_device;
        result.deviceStateMask = self.device_state_mask.toC();
        result.isDefaultDevice = self.is_default_device;

        @memset(result.deviceName[0..], 0);
        if (builtin.os.tag == .windows) {
            _ = try std.unicode.utf8ToUtf16Le(result.deviceName[0..], self.device_name);
        } else {
            @memcpy(result.deviceName[0..], self.device_name);
        }

        return result;
    }
};

pub const AkExternalSourceInfo = struct {
    external_src_cookie: u32 = 0,
    id_codec: AkCodecID = 0,
    file: ?[]const u8 = null,
    in_memory: ?*anyopaque = null,
    memory_size: u32 = 0,
    id_file: AkFileID = 0,

    pub fn fromC(allocator: std.mem.Allocator, value: c.WWISEC_AkExternalSourceInfo) !AkExternalSourceInfo {
        return .{
            .external_src_cookie = value.iExternalSrcCookie,
            .id_codec = value.idCodec,
            .file = if (value.szFile != null) try fromOSChar(allocator, value.szFile) else null,
            .in_memory = value.pInMemory,
            .memory_size = value.uiMemorySize,
            .id_file = value.idFile,
        };
    }

    pub fn toC(self: AkExternalSourceInfo, allocator: std.mem.Allocator) !c.WWISEC_AkExternalSourceInfo {
        return .{
            .iExternalSrcCookie = self.external_src_cookie,
            .idCodec = self.id_codec,
            .szFile = if (self.file) |file| @as([*]AkOSChar, @ptrCast(try toOSChar(allocator, file))) else null,
            .pInMemory = self.in_memory,
            .uiMemorySize = self.memory_size,
            .idFile = self.id_file,
        };
    }
};

pub const AkObstructionOcclusionValues = extern struct {
    occlusion: f32 = 0.0,
    obstruction: f32 = 0.0,

    pub inline fn fromC(value: c.WWISEC_AkObstructionOcclusionValues) AkObstructionOcclusionValues {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkObstructionOcclusionValues) c.WWISEC_AkObstructionOcclusionValues {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkObstructionOcclusionValues) == @sizeOf(c.WWISEC_AkObstructionOcclusionValues));
    }
};

pub const AkAuxSendValue = extern struct {
    listener_id: AkGameObjectID = AK_INVALID_GAME_OBJECT,
    aux_bus_id: AkAuxBusID = AK_INVALID_AUX_ID,
    control_value: f32 = 0.0,

    pub inline fn fromC(value: c.WWISEC_AkAuxSendValue) AkAuxSendValue {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkAuxSendValue) c.WWISEC_AkAuxSendValue {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkAuxSendValue) == @sizeOf(c.WWISEC_AkAuxSendValue));
    }
};

pub const AkAudioSettings = extern struct {
    num_samples_per_frame: u32 = 0,
    num_samples_per_second: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_AkAudioSettings) AkAudioSettings {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkAudioSettings) c.WWISEC_AkAudioSettings {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkAudioSettings) == @sizeOf(c.WWISEC_AkAudioSettings));
    }
};

pub const fromOSChar = blk: {
    if (builtin.os.tag == .windows) {
        break :blk fromOSCharUtf16;
    } else {
        break :blk fromCString;
    }
};

pub const toOSChar = blk: {
    if (builtin.os.tag == .windows) {
        break :blk toOSCharUtf16;
    } else {
        break :blk toCString;
    }
};

pub fn fromOSCharUtf16(allocator: std.mem.Allocator, value_opt: ?[*:0]const u16) ![]u8 {
    if (value_opt) |value| {
        return std.unicode.utf16LeToUtf8Alloc(allocator, value[0..std.mem.len(value)]);
    }

    return "";
}

pub fn toOSCharUtf16(allocator: std.mem.Allocator, value: []const u8) ![:0]u16 {
    return std.unicode.utf8ToUtf16LeAllocZ(allocator, value);
}

pub fn fromCString(allocator: std.mem.Allocator, value_opt: ?[*:0]const u8) ![]u8 {
    if (value_opt) |value| {
        return allocator.dupe(u8, value[0..std.mem.len(value)]);
    }

    return "";
}

pub fn toCString(allocator: std.mem.Allocator, value: []const u8) ![:0]u8 {
    return allocator.dupeZ(u8, value);
}

pub fn stackCharAllocator(fallback_allocator: std.mem.Allocator) std.heap.StackFallbackAllocator(wwise_options.string_stack_size) {
    return std.heap.stackFallback(wwise_options.string_stack_size, fallback_allocator);
}
