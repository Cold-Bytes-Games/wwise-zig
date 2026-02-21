const builtin = @import("builtin");
const c = @import("wwise_c");
const constants = @import("constants.zig");
const enums = @import("enums.zig");
const platform_types = @import("platform_types.zig");
const speaker_config = @import("speaker_config.zig");
const std = @import("std");
const typedefs = @import("typedefs.zig");
const zig = @import("zig.zig");

pub const AkAudioSettings = extern struct {
    num_samples_per_frame: u32 = 0,
    num_samples_per_second: u32 = 0,

    pub inline fn fromC(value: c.AkAudioSettings) AkAudioSettings {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkAudioSettings) c.AkAudioSettings {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkAudioSettings) == @sizeOf(c.AkAudioSettings));
    }
};

pub const AkDeviceDescription = struct {
    id_device: u32 = 0,
    device_name: []const u8 = &.{},
    device_state_mask: enums.AkAudioDeviceState = .{},
    is_default_device: bool = false,

    pub fn deinit(self: AkDeviceDescription, allocator: std.mem.Allocator) void {
        if (!std.mem.eql(u8, self.device_name[0..], "")) {
            allocator.free(self.device_name);
        }
    }

    pub fn fromC(allocator: std.mem.Allocator, value: c.AkDeviceDescription) !AkDeviceDescription {
        return .{
            .id_device = value.idDevice,
            .device_name = try zig.fromOSChar(allocator, @as(?[*:0]const platform_types.AkOSChar, @ptrCast(value.deviceName[0..]))),
            .device_state_mask = enums.AkAudioDeviceState.fromC(value.deviceStateMask),
            .is_default_device = value.isDefaultDevice,
        };
    }

    pub fn toC(self: AkDeviceDescription) !c.AkDeviceDescription {
        var result: c.AkDeviceDescription = undefined;
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

pub const AkMotionDeviceData = extern struct {
    device_type: enums.AkMotionDeviceType = .controller,
    input_profile: enums.AkMotionInputProfile = .rumble,

    pub inline fn fromC(value: c.AkMotionDeviceData) AkMotionDeviceData {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMotionDeviceData) c.AkMotionDeviceData {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkMotionDeviceData) == @sizeOf(c.AkMotionDeviceData));
    }
};

pub const Ak3DAudioSinkCapabilities = extern struct {
    channel_config: speaker_config.AkChannelConfig = .{},
    max_system_audio_objects: u32 = 0,
    available_system_audio_objects: u32 = 0,
    passthrough: bool = false,
    multi_channel_objects: bool = false,

    pub inline fn fromC(value: c.WWISEC_Ak3DAudioSinkCapabilities) Ak3DAudioSinkCapabilities {
        return @bitCast(value);
    }

    pub inline fn toC(self: Ak3DAudioSinkCapabilities) c.WWISEC_Ak3DAudioSinkCapabilities {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(Ak3DAudioSinkCapabilities) == @sizeOf(c.WWISEC_Ak3DAudioSinkCapabilities));
    }
};

pub const AkOutputDeviceInfo = extern struct {
    plugin_id: typedefs.AkPluginID = 0,
    audio_device_shareset: typedefs.AkUniqueID = 0,
    id_device: u32 = 0,
    channel_config: speaker_config.AkChannelConfig = .{},
    capabilities: Ak3DAudioSinkCapabilities = .{},
    custom_data: ?*anyopaque,

    pub inline fn fromC(value: c.WWISEC_AkOutputDeviceInfo) AkOutputDeviceInfo {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkOutputDeviceInfo) c.WWISEC_AkOutputDeviceInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkOutputDeviceInfo) == @sizeOf(c.WWISEC_AkOutputDeviceInfo));
    }
};

pub const AkObstructionOcclusionValues = extern struct {
    occlusion: f32 = 0.0,
    obstruction: f32 = 0.0,

    pub inline fn fromC(value: c.AkObstructionOcclusionValues) AkObstructionOcclusionValues {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkObstructionOcclusionValues) c.AkObstructionOcclusionValues {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkObstructionOcclusionValues) == @sizeOf(c.AkObstructionOcclusionValues));
    }
};

pub const AkAuxSendValue = extern struct {
    listener_id: typedefs.AkGameObjectID = constants.AK_INVALID_GAME_OBJECT,
    aux_bus_id: typedefs.AkAuxBusID = constants.AK_INVALID_AUX_ID,
    control_value: f32 = 0.0,

    pub inline fn fromC(value: c.AkAuxSendValue) AkAuxSendValue {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkAuxSendValue) c.AkAuxSendValue {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkAuxSendValue) == @sizeOf(c.AkAuxSendValue));
    }
};

pub const AkExternalSourceInfo = struct {
    external_src_cookie: u32 = 0,
    id_codec: typedefs.AkCodecID = 0,
    file: ?[]const u8 = null,
    in_memory: ?*anyopaque = null,
    memory_size: u32 = 0,
    id_file: typedefs.AkFileID = 0,

    pub fn fromC(allocator: std.mem.Allocator, value: c.AkExternalSourceInfo) !AkExternalSourceInfo {
        return .{
            .external_src_cookie = value.iExternalSrcCookie,
            .id_codec = value.idCodec,
            .file = if (value.szFile != null) try zig.fromCString(allocator, value.szFile) else null,
            .in_memory = value.pInMemory,
            .memory_size = value.uiMemorySize,
            .id_file = value.idFile,
        };
    }

    pub fn toC(self: AkExternalSourceInfo, allocator: std.mem.Allocator) !c.AkExternalSourceInfo {
        return .{
            .iExternalSrcCookie = self.external_src_cookie,
            .idCodec = self.id_codec,
            .szFile = if (self.file) |file| @as([*:0]u8, @ptrCast(try zig.toCString(allocator, file))) else null,
            .pInMemory = self.in_memory,
            .uiMemorySize = self.memory_size,
            .idFile = self.id_file,
        };
    }
};

pub const AkOutputSettings = extern struct {
    audio_device_shareset: typedefs.AkUniqueID = constants.AK_INVALID_UNIQUE_ID,
    id_device: u32 = 0,
    panning_rule: enums.AkPanningRule = .speakers,
    channel_config: speaker_config.AkChannelConfig = .{},

    pub const InitOptionalArgs = struct {
        id_device: typedefs.AkUniqueID = constants.AK_INVALID_UNIQUE_ID,
        channel_config: speaker_config.AkChannelConfig = .{},
        panning: enums.AkPanningRule = .speakers,
    };

    pub fn init(fallback_allocator: std.mem.Allocator, device_shareset: []const u8, optional_args: InitOptionalArgs) !AkOutputSettings {
        var raw_output_settings: c.WWISEC_AkOutputSettings = undefined;

        var stack_char_allocator = zig.stackCharAllocator(fallback_allocator);
        var allocator = stack_char_allocator.get();

        const device_shareset_cstr = try zig.toCString(allocator, device_shareset);
        defer allocator.free(device_shareset_cstr);

        c.WWISEC_AkOutputSettings_Init(&raw_output_settings, device_shareset_cstr, optional_args.id_device, optional_args.channel_config.toC(), @intFromEnum(optional_args.panning));

        return fromC(raw_output_settings);
    }

    pub inline fn fromC(value: c.WWISEC_AkOutputSettings) AkOutputSettings {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkOutputSettings) c.WWISEC_AkOutputSettings {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkOutputSettings) == @sizeOf(c.WWISEC_AkOutputSettings));
    }
};

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
