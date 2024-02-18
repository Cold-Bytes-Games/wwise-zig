const std = @import("std");
const builtin = @import("builtin");
const c = @import("c.zig");
const wwise_options = @import("wwise_options");

pub const AkOSChar = c.AkOSChar;
pub const AkUtf16 = c.AkUtf16;

pub const AkUniqueID = c.WWISEC_AkUniqueID;
pub const AkStateID = c.WWISEC_AkStateID;
pub const AkStateGroupID = c.WWISEC_AkStateGroupID;
pub const AkPlayingID = c.WWISEC_AkPlayingID;
pub const AkTimeMs = c.WWISEC_AkTimeMs;
pub const AkPortNumber = c.WWISEC_AkPortNumber;
pub const AkPitchValue = c.WWISEC_AkPitchValue;
pub const AkVolumeValue = c.WWISEC_AkVolumeValue;
pub const AkGameObjectID = c.WWISEC_AkGameObjectID;
pub const AkLPFType = c.WWISEC_AkLPFType;
pub const AkMemPoolId = c.WWISEC_AkMemPoolId;
pub const AkPluginID = c.WWISEC_AkPluginID;
pub const AkCodecID = c.WWISEC_AkCodecID;
pub const AkAuxBusID = c.WWISEC_AkAuxBusID;
pub const AkPluginParamID = c.WWISEC_AkPluginParamID;
pub const AkPriority = c.WWISEC_AkPriority;
pub const AkDataCompID = c.WWISEC_AkDataCompID;
pub const AkDataTypeID = c.WWISEC_AkDataTypeID;
pub const AkDataInterleaveID = c.WWISEC_AkDataInterleaveID;
pub const AkSwitchGroupID = c.WWISEC_AkSwitchGroupID;
pub const AkSwitchStateID = c.WWISEC_AkSwitchStateID;
pub const AkRtpcID = c.WWISEC_AkRtpcID;
pub const AkRtpcValue = c.WWISEC_AkRtpcValue;
pub const AkBankID = c.WWISEC_AkBankID;
pub const AkFileID = c.WWISEC_AkFileID;
pub const AkDeviceID = c.WWISEC_AkDeviceID;
pub const AkTriggerID = c.WWISEC_AkTriggerID;
pub const AkArgumentValueID = c.WWISEC_AkArgumentValueID;
pub const AkChannelMask = c.WWISEC_AkChannelMask;
pub const AkModulatorID = c.WWISEC_AkModulatorID;
pub const AkAcousticTextureID = c.WWISEC_AkAcousticTextureID;
pub const AkImageSourceID = c.WWISEC_AkImageSourceID;
pub const AkOutputDeviceID = c.WWISEC_AkOutputDeviceID;
pub const AkPipelineID = c.WWISEC_AkPipelineID;
pub const AkRayID = c.WWISEC_AkRayID;
pub const AkAudioObjectID = c.WWISEC_AkAudioObjectID;
pub const AkJobType = c.WWISEC_AkJobType;

pub const AkJobType_Generic = c.WWISEC_AkJobType_Generic;
pub const AkJobType_AudioProcessing = c.WWISEC_AkJobType_AudioProcessing;
pub const AkJobType_SpatialAudio = c.WWISEC_AkJobType_SpatialAudio;

pub const AK_INVALID_PLUGINID = c.WWISEC_AK_INVALID_PLUGINID;
pub const AK_INVALID_SHARE_SET_ID = c.WWISEC_AK_INVALID_SHARE_SET_ID;
pub const AK_INVALID_GAME_OBJECT = c.WWISEC_AK_INVALID_GAME_OBJECT;
pub const AK_INVALID_UNIQUE_ID = c.WWISEC_AK_INVALID_UNIQUE_ID;
pub const AK_INVALID_RTPC_ID = c.WWISEC_AK_INVALID_RTPC_ID;
pub const AK_INVALID_PLAYING_ID = c.WWISEC_AK_INVALID_PLAYING_ID;
pub const AK_DEFAULT_SWITCH_STATE = c.WWISEC_AK_DEFAULT_SWITCH_STATE;
pub const AK_INVALID_POOL_ID = c.WWISEC_AK_INVALID_POOL_ID;
pub const AK_DEFAULT_POOL_ID = c.WWISEC_AK_DEFAULT_POOL_ID;
pub const AK_INVALID_AUX_ID = c.WWISEC_AK_INVALID_AUX_ID;
pub const AK_INVALID_FILE_ID = c.WWISEC_AK_INVALID_FILE_ID;
pub const AK_INVALID_DEVICE_ID = c.WWISEC_AK_INVALID_DEVICE_ID;
pub const AK_INVALID_BANK_ID = c.WWISEC_AK_INVALID_BANK_ID;
pub const AK_FALLBACK_ARGUMENTVALUE_ID = c.WWISEC_AK_FALLBACK_ARGUMENTVALUE_ID;
pub const AK_INVALID_CHANNELMASK = c.WWISEC_AK_INVALID_CHANNELMASK;
pub const AK_INVALID_OUTPUT_DEVICE_ID = c.WWISEC_AK_INVALID_OUTPUT_DEVICE_ID;
pub const AK_INVALID_PIPELINE_ID = c.WWISEC_AK_INVALID_PIPELINE_ID;
pub const AK_INVALID_AUDIO_OBJECT_ID = c.WWISEC_AK_INVALID_AUDIO_OBJECT_ID;
pub const AK_DEFAULT_PRIORITY = c.WWISEC_AK_DEFAULT_PRIORITY;
pub const AK_MIN_PRIORITY = c.WWISEC_AK_MIN_PRIORITY;
pub const AK_MAX_PRIORITY = c.WWISEC_AK_MAX_PRIORITY;
pub const AK_DEFAULT_BANK_IO_PRIORITY = c.WWISEC_AK_DEFAULT_BANK_IO_PRIORITY;
pub const AK_DEFAULT_BANK_THROUGHPUT = c.WWISEC_AK_DEFAULT_BANK_THROUGHPUT;
pub const AK_SOUNDBANK_VERSION = c.WWISEC_AK_SOUNDBANK_VERSION;
pub const AK_NUM_JOB_TYPES = c.WWISEC_AK_NUM_JOB_TYPES;
pub const AK_MAX_PATH = c.AK_MAX_PATH;
pub const AK_MAX_LANGUAGE_NAME_SIZE = c.WWISEC_AK_MAX_LANGUAGE_NAME_SIZE;

pub const AKCOMPANYID_PLUGINDEV_MIN = c.WWISEC_AKCOMPANYID_PLUGINDEV_MIN;
pub const AKCOMPANYID_PLUGINDEV_MAX = c.WWISEC_AKCOMPANYID_PLUGINDEV_MAX;

pub const AKCOMPANYID_AUDIOKINETIC = c.WWISEC_AKCOMPANYID_AUDIOKINETIC;
pub const AKCOMPANYID_AUDIOKINETIC_EXTERNAL = c.WWISEC_AKCOMPANYID_AUDIOKINETIC_EXTERNAL;
pub const AKCOMPANYID_MCDSP = c.WWISEC_AKCOMPANYID_MCDSP;
pub const AKCOMPANYID_WAVEARTS = c.WWISEC_AKCOMPANYID_WAVEARTS;
pub const AKCOMPANYID_PHONETICARTS = c.WWISEC_AKCOMPANYID_PHONETICARTS;
pub const AKCOMPANYID_IZOTOPE = c.WWISEC_AKCOMPANYID_IZOTOPE;
pub const AKCOMPANYID_CRANKCASEAUDIO = c.WWISEC_AKCOMPANYID_CRANKCASEAUDIO;
pub const AKCOMPANYID_IOSONO = c.WWISEC_AKCOMPANYID_IOSONO;
pub const AKCOMPANYID_AUROTECHNOLOGIES = c.WWISEC_AKCOMPANYID_AUROTECHNOLOGIES;
pub const AKCOMPANYID_DOLBY = c.WWISEC_AKCOMPANYID_DOLBY;
pub const AKCOMPANYID_TWOBIGEARS = c.WWISEC_AKCOMPANYID_TWOBIGEARS;
pub const AKCOMPANYID_OCULUS = c.WWISEC_AKCOMPANYID_OCULUS;
pub const AKCOMPANYID_BLUERIPPLESOUND = c.WWISEC_AKCOMPANYID_BLUERIPPLESOUND;
pub const AKCOMPANYID_ENZIEN = c.WWISEC_AKCOMPANYID_ENZIEN;
pub const AKCOMPANYID_KROTOS = c.WWISEC_AKCOMPANYID_KROTOS;
pub const AKCOMPANYID_NURULIZE = c.WWISEC_AKCOMPANYID_NURULIZE;
pub const AKCOMPANYID_SUPERPOWERED = c.WWISEC_AKCOMPANYID_SUPERPOWERED;
pub const AKCOMPANYID_GOOGLE = c.WWISEC_AKCOMPANYID_GOOGLE;
pub const AKCOMPANYID_VISISONICS = c.WWISEC_AKCOMPANYID_VISISONICS;

pub const AKCODECID_BANK = c.WWISEC_AKCODECID_BANK;
pub const AKCODECID_PCM = c.WWISEC_AKCODECID_PCM;
pub const AKCODECID_ADPCM = c.WWISEC_AKCODECID_ADPCM;
pub const AKCODECID_XMA = c.WWISEC_AKCODECID_XMA;
pub const AKCODECID_VORBIS = c.WWISEC_AKCODECID_VORBIS;
pub const AKCODECID_WIIADPCM = c.WWISEC_AKCODECID_WIIADPCM;
pub const AKCODECID_PCMEX = c.WWISEC_AKCODECID_PCMEX;
pub const AKCODECID_EXTERNAL_SOURCE = c.WWISEC_AKCODECID_EXTERNAL_SOURCE;
pub const AKCODECID_XWMA = c.WWISEC_AKCODECID_XWMA;
pub const AKCODECID_FILE_PACKAGE = c.WWISEC_AKCODECID_FILE_PACKAGE;
pub const AKCODECID_ATRAC9 = c.WWISEC_AKCODECID_ATRAC9;
pub const AKCODECID_VAG = c.WWISEC_AKCODECID_VAG;
pub const AKCODECID_PROFILERCAPTURE = c.WWISEC_AKCODECID_PROFILERCAPTURE;
pub const AKCODECID_ANALYSISFILE = c.WWISEC_AKCODECID_ANALYSISFILE;
pub const AKCODECID_MIDI = c.WWISEC_AKCODECID_MIDI;
pub const AKCODECID_OPUSNX = c.WWISEC_AKCODECID_OPUSNX;
pub const AKCODECID_CAF = c.WWISEC_AKCODECID_CAF;
pub const AKCODECID_AKOPUS = c.WWISEC_AKCODECID_AKOPUS;
pub const AKCODECID_AKOPUS_WEM = c.WWISEC_AKCODECID_AKOPUS_WEM;
pub const AKCODECID_MEMORYMGR_DUMP = c.WWISEC_AKCODECID_MEMORYMGR_DUMP;
pub const AKCODECID_SONY360 = c.WWISEC_AKCODECID_SONY360;

pub const AKCODECID_BANK_EVENT = c.WWISEC_AKCODECID_BANK_EVENT;
pub const AKCODECID_BANK_BUS = c.WWISEC_AKCODECID_BANK_BUS;

pub const AKPLUGINID_METER = c.WWISEC_AKPLUGINID_METER;
pub const AKPLUGINID_RECORDER = c.WWISEC_AKPLUGINID_RECORDER;
pub const AKPLUGINID_IMPACTER = c.WWISEC_AKPLUGINID_IMPACTER;
pub const AKPLUGINID_SYSTEM_OUTPUT_META = c.WWISEC_AKPLUGINID_SYSTEM_OUTPUT_META;
pub const AKPLUGINID_AUDIO_OBJECT_ATTENUATION_META = c.WWISEC_AKPLUGINID_AUDIO_OBJECT_ATTENUATION_META;
pub const AKPLUGINID_AUDIO_OBJECT_PRIORITY_META = c.WWISEC_AKPLUGINID_AUDIO_OBJECT_PRIORITY_META;

pub const AKEXTENSIONID_SPATIALAUDIO = c.WWISEC_AKEXTENSIONID_SPATIALAUDIO;
pub const AKEXTENSIONID_INTERACTIVEMUSIC = c.WWISEC_AKEXTENSIONID_INTERACTIVEMUSIC;
pub const AKEXTENSIONID_MIDIDEVICEMGR = c.WWISEC_AKEXTENSIONID_MIDIDEVICEMGR;

pub const AK_WAVE_FORMAT_VAG = c.WWISEC_AK_WAVE_FORMAT_VAG;
pub const AK_WAVE_FORMAT_AT9 = c.WWISEC_AK_WAVE_FORMAT_AT9;
pub const AK_WAVE_FORMAT_VORBIS = c.WWISEC_AK_WAVE_FORMAT_VORBIS;
pub const AK_WAVE_FORMAT_OPUSNX = c.WWISEC_AK_WAVE_FORMAT_OPUSNX;
pub const AK_WAVE_FORMAT_OPUS = c.WWISEC_AK_WAVE_FORMAT_OPUS;
pub const AK_WAVE_FORMAT_OPUS_WEM = c.WWISEC_AK_WAVE_FORMAT_OPUS_WEM;
pub const WAVE_FORMAT_XMA2 = c.WWISEC_WAVE_FORMAT_XMA2;

pub const AK_BANK_PLATFORM_DATA_ALIGNMENT = c.AK_BANK_PLATFORM_DATA_ALIGNMENT;

pub const IAkSoftwareCodec = opaque {};
pub const IAkFileCodec = opaque {};
pub const IAkGrainCodec = opaque {};

pub const AkCreateFileSourceCallback = ?*const fn (in_ctx: ?*anyopaque) callconv(.C) ?*IAkSoftwareCodec;
pub const AkCreateBankSourceCallback = ?*const fn (in_ctx: ?*anyopaque) callconv(.C) ?*IAkSoftwareCodec;
pub const AkCreateFileCodecCallback = ?*const fn () callconv(.C) ?*IAkFileCodec;
pub const AkCreateGrainCodecCallback = ?*const fn () callconv(.C) ?*IAkGrainCodec;

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

pub const AkBankType = enum(u32) {
    user = c.WWISEC_AkBankType_User,
    event = c.WWISEC_AkBankType_Event,
    bus = c.WWISEC_AkBankType_Bus,
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

pub const AkConnectionType = enum(DefaultEnumType) {
    direct = c.WWISEC_ConnectionType_Direct,
    game_def_send = c.WWISEC_ConnectionType_GameDefSend,
    user_def_send = c.WWISEC_ConnectionType_UserDefSend,
    reflections_send = c.WWISEC_ConnectionType_ReflectionsSend,
};

pub const AkVector64 = extern struct {
    x: f64 = 0.0,
    y: f64 = 0.0,
    z: f64 = 0.0,

    pub inline fn toAkVector(self: AkVector64) AkVector {
        return .{
            .x = @truncate(self.x),
            .y = @truncate(self.y),
            .z = @truncate(self.z),
        };
    }

    pub inline fn fromC(value: c.WWISEC_AkVector64) AkVector64 {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkVector64) c.WWISEC_AkVector64 {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkVector64) == @sizeOf(c.WWISEC_AkVector64));
    }
};

pub const AkVector = extern struct {
    x: f32 = 0.0,
    y: f32 = 0.0,
    z: f32 = 0.0,

    pub inline fn toAkVector64(self: AkVector) AkVector64 {
        return .{
            .x = self.x,
            .y = self.y,
            .z = self.z,
        };
    }

    pub inline fn fromC(value: c.WWISEC_AkVector) AkVector {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkVector) c.WWISEC_AkVector {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkVector) == @sizeOf(c.WWISEC_AkVector));
    }
};

pub const AkWorldTransform = extern struct {
    orientation_front: AkVector = .{},
    orientation_top: AkVector = .{},
    position: AkVector64 = .{},

    pub inline fn toAkTransform(self: AkWorldTransform) AkTransform {
        return .{
            .orientation_front = self.orientation_front,
            .orientation_top = self.orientation_top,
            .position = self.position.toAkVector(),
        };
    }

    pub inline fn fromC(value: c.WWISEC_AkWorldTransform) AkWorldTransform {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkWorldTransform) c.WWISEC_AkWorldTransform {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkWorldTransform) == @sizeOf(c.WWISEC_AkWorldTransform));
    }
};

pub const AkTransform = extern struct {
    orientation_front: AkVector = .{},
    orientation_top: AkVector = .{},
    position: AkVector = .{},

    pub inline fn toAkWorldTransform(self: AkTransform) AkWorldTransform {
        return .{
            .orientation_front = self.orientation_front,
            .orientation_top = self.orientation_top,
            .position = self.position.toAkVector64(),
        };
    }

    pub inline fn fromC(value: c.WWISEC_AkTransform) AkTransform {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkTransform) c.WWISEC_AkTransform {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkTransform) == @sizeOf(c.WWISEC_AkTransform));
    }
};

pub const AkSoundPosition = AkWorldTransform;
pub const AkListenerPosition = AkWorldTransform;

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

pub const AkChannelEmitter = extern struct {
    position: AkWorldTransform = .{},
    input_channels: AkChannelMask = 0,
    padding: [4]u8 = [_]u8{0} ** 4,

    pub inline fn fromC(value: c.WWISEC_AkChannelEmitter) AkChannelEmitter {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkChannelEmitter) c.WWISEC_AkChannelEmitter {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkChannelEmitter) == @sizeOf(c.WWISEC_AkChannelEmitter));
    }
};

pub const AkEmitterListenerPair = extern struct {
    emitter: AkWorldTransform = .{},
    distance: f32 = 0.0,
    emitter_angle: f32 = 0.0,
    listener_angle: f32 = 0.0,
    dry_mix_gain: f32 = 1.0,
    game_def_aux_mix_gain: f32 = 1.0,
    user_def_aux_mix_gain: f32 = 1.0,
    occlusion: f32 = 0.0,
    obstruction: f32 = 0.0,
    diffraction: f32 = 0.0,
    transmission_loss: f32 = 0.0,
    spread: f32 = 0.0,
    aperture: f32 = 100.0,
    scaling_factor: f32 = 1.0,
    path_gain: f32 = 1.0,
    emitter_channel_mask: AkChannelMask = 0xFFFFFFFF,
    id: AkRayID = 0,
    listener_id: AkGameObjectID = 0,

    pub fn getGainForConnectionType(self: AkEmitterListenerPair, in_type: AkConnectionType) f32 {
        return switch (in_type) {
            .direct => self.dry_mix_gain,
            .game_def_send => self.game_def_aux_mix_gain,
            .user_def_send => self.user_def_aux_mix_gain,
            else => 1.0,
        };
    }

    pub fn fromC(value: c.WWISEC_AkEmitterListenerPair) AkEmitterListenerPair {
        return @bitCast(value);
    }

    pub fn toC(self: AkEmitterListenerPair) c.WWISEC_AkEmitterListenerPair {
        return @bitCast(self);
    }
};

pub const AkSetPositionFlags = packed struct(u8) {
    emitter: bool = false,
    listener: bool = false,
    pad: u6 = 0,

    pub const Default = AkSetPositionFlags{ .emitter = true, .listener = true };

    pub inline fn fromC(value: c.WWISEC_AkSetPositionFlags) AkSetPositionFlags {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkSetPositionFlags) c.WWISEC_AkSetPositionFlags {
        return @as(u8, @bitCast(self));
    }

    comptime {
        std.debug.assert(@as(u8, @bitCast(AkSetPositionFlags{ .emitter = true })) == c.WWISEC_AkSetPositionFlags_Emitter);
        std.debug.assert(@as(u8, @bitCast(AkSetPositionFlags{ .listener = true })) == c.WWISEC_AkSetPositionFlags_Listener);
        std.debug.assert(Default.toC() == c.WWISEC_AkSetPositionFlags_Default);
    }
};

pub const AkSpeakerPanningType = enum(u8) {
    direct_speaker_assignment = c.WWISEC_AkSpeakerPanningType_AK_DirectSpeakerAssignment,
    balance_fadee_height = c.WWISEC_AkSpeakerPanningType_AK_BalanceFadeHeight,
    steering_panner = c.WWISEC_AkSpeakerPanningType_AK_SteeringPanner,
};

pub const Ak3DPositionType = enum(u8) {
    emitter = c.WWISEC_Ak3DPositionType_AK_3DPositionType_Emitter,
    emitter_with_automation = c.WWISEC_Ak3DPositionType_AK_3DPositionType_EmitterWithAutomation,
    listener_with_automation = c.WWISEC_Ak3DPositionType_AK_3DPositionType_ListenerWithAutomation,
};

pub const AkPanningRule = enum(u8) {
    speakers = c.WWISEC_AkPanningRule_Speakers,
    headphones = c.WWISEC_AkPanningRule_Headphones,
};

pub const Ak3DSpatializationMode = enum(u8) {
    none = c.WWISEC_Ak3DSpatializationMode_AK_SpatializationMode_None,
    position_only = c.WWISEC_Ak3DSpatializationMode_AK_SpatializationMode_PositionOnly,
    position_and_orientation = c.WWISEC_Ak3DSpatializationMode_AK_SpatializationMode_PositionAndOrientation,
};

pub const AkMeteringFlags = packed struct(u8) {
    enable_bus_meter_peak: bool = false,
    enable_bus_meter_true_peak: bool = false,
    enable_bus_meter_rms: bool = false,
    reserved0: bool = false,
    enable_bus_meter_kpower: bool = false,
    enable_bus_meter_3d_meter: bool = false,
    reserved1: u2 = 0,

    pub inline fn fromC(value: c.WWISEC_AkMeteringFlags) AkMeteringFlags {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMeteringFlags) c.WWISEC_AkMeteringFlags {
        return @bitCast(self);
    }
};

pub const AkPluginType = enum(u8) {
    none = c.WWISEC_AkPluginTypeNone,
    codec = c.WWISEC_AkPluginTypeCodec,
    source = c.WWISEC_AkPluginTypeSource,
    effect = c.WWISEC_AkPluginTypeEffect,
    mixer = c.WWISEC_AkPluginTypeMixer,
    sink = c.WWISEC_AkPluginTypeSink,
    global_extension = c.WWISEC_AkPluginTypeGlobalExtension,
    metadata = c.WWISEC_AkPluginTypeMetadata,
};

pub const AKRESULT = enum(DefaultEnumType) {
    not_implemented = 0,
    success = 1,
    fail = 2,
    partial_success = 3,
    not_compatible = 4,
    already_connected = 5,
    invalid_file = 7,
    audio_file_header_too_large = 8,
    max_reached = 9,
    invalid_id = 14,
    id_not_found = 15,
    invalid_instance_id = 16,
    no_more_data = 17,
    invalid_state_group = 20,
    child_already_has_a_parent = 21,
    invalid_language = 22,
    cannot_add_itself_as_a_child = 23,
    invalid_parameter = 31,
    element_already_in_list = 35,
    path_not_found = 36,
    path_no_vertices = 37,
    path_not_running = 38,
    path_not_paused = 39,
    path_node_already_in_list = 40,
    path_node_not_in_list = 41,
    data_needed = 43,
    no_data_needed = 44,
    data_ready = 45,
    no_data_ready = 46,
    insufficient_memory = 52,
    cancelled = 53,
    unknown_bank_id = 54,
    bank_read_error = 56,
    invalid_switch_type = 57,
    format_not_ready = 63,
    wrong_bank_version = 64,
    file_not_found = 66,
    device_not_ready = 67,
    bank_already_loaded = 69,
    rendered_fx = 71,
    process_needed = 72,
    process_done = 73,
    mem_manager_not_initialized = 74,
    stream_mgr_not_initialized = 75,
    sse_instructions_not_supported = 76,
    busy = 77,
    unsupported_channel_config = 78,
    plugin_media_not_available = 79,
    must_be_virtualized = 80,
    command_too_large = 81,
    rejected_by_filter = 82,
    invalid_custom_platform_name = 83,
    dll_cannot_load = 84,
    dll_path_not_found = 85,
    no_java_vm = 86,
    open_sl_error = 87,
    plugin_not_registered = 88,
    data_alignment_error = 89,
    device_not_compatible = 90,
    duplicate_unique_id = 91,
    init_bank_not_loaded = 92,
    device_not_found = 93,
    playing_id_not_found = 94,
    invalid_float_value = 95,
    file_format_mismatch = 96,
    no_distinct_listener = 97,
    acp_error = 98,
    resource_in_use = 99,
    invalid_bank_type = 100,
    already_initialized = 101,
    not_initialized = 102,
    file_permission_error = 103,
    unknown_file_error = 104,
    too_many_concurrent_operations = 105,
    invalid_file_size = 106,
    deferred = 107,
    file_path_too_long = 108,
    invalid_state = 109,
};

pub const AkGroupType = enum(DefaultEnumType) {
    @"switch" = c.WWISEC_AkGroupType_Switch,
    state = c.WWISEC_AkGroupType_State,
};

pub const AkCurveInterpolation = enum(DefaultEnumType) {
    log3 = c.WWISEC_AkCurveInterpolation_Log3,
    sine = c.WWISEC_AkCurveInterpolation_Sine,
    log1 = c.WWISEC_AkCurveInterpolation_Log1,
    inv_scurve = c.WWISEC_AkCurveInterpolation_InvSCurve,
    linear = c.WWISEC_AkCurveInterpolation_Linear,
    scurve = c.WWISEC_AkCurveInterpolation_SCurve,
    exp1 = c.WWISEC_AkCurveInterpolation_Exp1,
    sine_recip = c.WWISEC_AkCurveInterpolation_SineRecip,
    exp3 = c.WWISEC_AkCurveInterpolation_Exp3,
    constant = c.WWISEC_AkCurveInterpolation_Constant,
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

pub const WwiseError = error{
    NotImplemented,
    Fail,
    PartialSuccess,
    NotCompatible,
    AlreadyConnected,
    InvalidFile,
    AudioFileHeaderTooLarge,
    MaxReached,
    InvalidID,
    IDNotFound,
    InvalidInstanceID,
    NoMoreData,
    InvalidStateGroup,
    ChildAlreadyHasAParent,
    InvalidLanguage,
    CannotAddItselfAsAChild,
    InvalidParameter,
    ElementAlreadyInList,
    PathNotFound,
    PathNoVertices,
    PathNotRunning,
    PathNotPaused,
    PathNodeAlreadyInList,
    PathNodeNotInList,
    DataNeeded,
    NoDataNeeded,
    DataReady,
    NoDataReady,
    InsufficientMemory,
    Cancelled,
    UnknownBankID,
    BankReadError,
    InvalidSwitchType,
    FormatNotReady,
    WrongBankVersion,
    FileNotFound,
    DeviceNotReady,
    BankAlreadyLoaded,
    RenderedFX,
    ProcessNeeded,
    ProcessDone,
    MemManagerNotInitialized,
    StreamMgrNotInitialized,
    SSEInstructionsNotSupported,
    Busy,
    UnsupportedChannelConfig,
    PluginMediaNotAvailable,
    MustBeVirtualized,
    CommandTooLarge,
    RejectedByFilter,
    InvalidCustomPlatformName,
    DLLCannotLoad,
    DLLPathNotFound,
    NoJavaVM,
    OpenSLError,
    PluginNotRegistered,
    DataAlignmentError,
    DeviceNotCompatible,
    DuplicateUniqueID,
    InitBankNotLoaded,
    DeviceNotFound,
    PlayingIDNotFound,
    InvalidFloatValue,
    FileFormatMismatch,
    NoDistinctListener,
    ACP_Error,
    ResourceInUse,
    InvalidBankType,
    AlreadyInitialized,
    NotInitialized,
    FilePermissionError,
    UnknownFileError,
    TooManyConcurrentOperations,
    InvalidFileSize,
    Deferred,
    FilePathTooLong,
    InvalidState,
};

pub inline fn handleAkResult(result: c.WWISEC_AKRESULT) WwiseError!void {
    return switch (result) {
        c.WWISEC_AK_NotImplemented => return WwiseError.NotImplemented,
        c.WWISEC_AK_Success => return,
        c.WWISEC_AK_Fail => return WwiseError.Fail,
        c.WWISEC_AK_PartialSuccess => return WwiseError.PartialSuccess,
        c.WWISEC_AK_NotCompatible => return WwiseError.NotCompatible,
        c.WWISEC_AK_AlreadyConnected => return WwiseError.AlreadyConnected,
        c.WWISEC_AK_InvalidFile => return WwiseError.InvalidFile,
        c.WWISEC_AK_AudioFileHeaderTooLarge => return WwiseError.AudioFileHeaderTooLarge,
        c.WWISEC_AK_MaxReached => return WwiseError.MaxReached,
        c.WWISEC_AK_InvalidID => return WwiseError.InvalidID,
        c.WWISEC_AK_IDNotFound => return WwiseError.IDNotFound,
        c.WWISEC_AK_InvalidInstanceID => return WwiseError.InvalidInstanceID,
        c.WWISEC_AK_NoMoreData => return WwiseError.NoMoreData,
        c.WWISEC_AK_InvalidStateGroup => return WwiseError.InvalidStateGroup,
        c.WWISEC_AK_ChildAlreadyHasAParent => return WwiseError.ChildAlreadyHasAParent,
        c.WWISEC_AK_InvalidLanguage => return WwiseError.InvalidLanguage,
        c.WWISEC_AK_CannotAddItseflAsAChild => return WwiseError.CannotAddItseflAsAChild,
        c.WWISEC_AK_InvalidParameter => return WwiseError.InvalidParameter,
        c.WWISEC_AK_ElementAlreadyInList => return WwiseError.ElementAlreadyInList,
        c.WWISEC_AK_PathNotFound => return WwiseError.PathNotFound,
        c.WWISEC_AK_PathNoVertices => return WwiseError.PathNoVertices,
        c.WWISEC_AK_PathNotRunning => return WwiseError.PathNotRunning,
        c.WWISEC_AK_PathNotPaused => return WwiseError.PathNotPaused,
        c.WWISEC_AK_PathNodeAlreadyInList => return WwiseError.PathNodeAlreadyInList,
        c.WWISEC_AK_PathNodeNotInList => return WwiseError.PathNodeNotInList,
        c.WWISEC_AK_DataNeeded => return WwiseError.DataNeeded,
        c.WWISEC_AK_NoDataNeeded => return WwiseError.NoDataNeeded,
        c.WWISEC_AK_DataReady => return WwiseError.DataReady,
        c.WWISEC_AK_NoDataReady => return WwiseError.NoDataReady,
        c.WWISEC_AK_InsufficientMemory => return WwiseError.InsufficientMemory,
        c.WWISEC_AK_Cancelled => return WwiseError.Cancelled,
        c.WWISEC_AK_UnknownBankID => return WwiseError.UnknownBankID,
        c.WWISEC_AK_BankReadError => return WwiseError.BankReadError,
        c.WWISEC_AK_InvalidSwitchType => return WwiseError.InvalidSwitchType,
        c.WWISEC_AK_FormatNotReady => return WwiseError.FormatNotReady,
        c.WWISEC_AK_WrongBankVersion => return WwiseError.WrongBankVersion,
        c.WWISEC_AK_FileNotFound => return WwiseError.FileNotFound,
        c.WWISEC_AK_DeviceNotReady => return WwiseError.DeviceNotReady,
        c.WWISEC_AK_BankAlreadyLoaded => return WwiseError.BankAlreadyLoaded,
        c.WWISEC_AK_RenderedFX => return WwiseError.RenderedFX,
        c.WWISEC_AK_ProcessNeeded => return WwiseError.ProcessNeeded,
        c.WWISEC_AK_ProcessDone => return WwiseError.ProcessDone,
        c.WWISEC_AK_MemManagerNotInitialized => return WwiseError.MemManagerNotInitialized,
        c.WWISEC_AK_StreamMgrNotInitialized => return WwiseError.StreamMgrNotInitialized,
        c.WWISEC_AK_SSEInstructionsNotSupported => return WwiseError.SSEInstructionsNotSupported,
        c.WWISEC_AK_Busy => return WwiseError.Busy,
        c.WWISEC_AK_UnsupportedChannelConfig => return WwiseError.UnsupportedChannelConfig,
        c.WWISEC_AK_PluginMediaNotAvailable => return WwiseError.PluginMediaNotAvailable,
        c.WWISEC_AK_MustBeVirtualized => return WwiseError.MustBeVirtualized,
        c.WWISEC_AK_CommandTooLarge => return WwiseError.CommandTooLarge,
        c.WWISEC_AK_RejectedByFilter => return WwiseError.RejectedByFilter,
        c.WWISEC_AK_InvalidCustomPlatformName => return WwiseError.InvalidCustomPlatformName,
        c.WWISEC_AK_DLLCannotLoad => return WwiseError.DLLCannotLoad,
        c.WWISEC_AK_DLLPathNotFound => return WwiseError.DLLPathNotFound,
        c.WWISEC_AK_NoJavaVM => return WwiseError.NoJavaVM,
        c.WWISEC_AK_OpenSLError => return WwiseError.OpenSLError,
        c.WWISEC_AK_PluginNotRegistered => return WwiseError.PluginNotRegistered,
        c.WWISEC_AK_DataAlignmentError => return WwiseError.DataAlignmentError,
        c.WWISEC_AK_DeviceNotCompatible => return WwiseError.DeviceNotCompatible,
        c.WWISEC_AK_DuplicateUniqueID => return WwiseError.DuplicateUniqueID,
        c.WWISEC_AK_InitBankNotLoaded => return WwiseError.InitBankNotLoaded,
        c.WWISEC_AK_DeviceNotFound => return WwiseError.DeviceNotFound,
        c.WWISEC_AK_PlayingIDNotFound => return WwiseError.PlayingIDNotFound,
        c.WWISEC_AK_InvalidFloatValue => return WwiseError.InvalidFloatValue,
        c.WWISEC_AK_FileFormatMismatch => return WwiseError.FileFormatMismatch,
        c.WWISEC_AK_NoDistinctListener => return WwiseError.NoDistinctListener,
        c.WWISEC_AK_ACP_Error => return WwiseError.ACP_Error,
        c.WWISEC_AK_ResourceInUse => return WwiseError.ResourceInUse,
        c.WWISEC_AK_InvalidBankType => return WwiseError.InvalidBankType,
        c.WWISEC_AK_AlreadyInitialized => return WwiseError.AlreadyInitialized,
        c.WWISEC_AK_NotInitialized => return WwiseError.NotInitialized,
        c.WWISEC_AK_FilePermissionError => return WwiseError.FilePermissionError,
        c.WWISEC_AK_UnknownFileError => return WwiseError.UnknownFileError,
        else => return WwiseError.NotImplemented,
    };
}

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
        return std.unicode.utf16leToUtf8Alloc(allocator, value[0..std.mem.len(value)]);
    }

    return "";
}

pub fn toOSCharUtf16(allocator: std.mem.Allocator, value: []const u8) ![:0]u16 {
    return std.unicode.utf8ToUtf16LeWithNull(allocator, value);
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

pub const DefaultEnumType = switch (builtin.abi) {
    .msvc => i32,
    else => u32,
};
