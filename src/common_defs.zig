const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const SpeakerVolumes = @import("SpeakerVolumes.zig");
const speaker_config = @import("speaker_config.zig");

pub const AkMetering = extern struct {
    peak: SpeakerVolumes.VectorPtr,
    true_peak: SpeakerVolumes.VectorPtr,
    rms: SpeakerVolumes.VectorPtr,
    mean_power_k: f32,

    pub inline fn fromC(value: c.WWISEC_AK_AkMetering) AkMetering {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMetering) c.WWISEC_AK_AkMetering {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkMetering) == @sizeOf(c.WWISEC_AK_AkMetering));
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

pub const AkSampleType = c.WWISEC_AkSampleType;

pub const AkAudioBuffer = extern struct {
    data: ?*anyopaque,
    channel_config: speaker_config.AkChannelConfig,
    state: common.AKRESULT,
    max_frames: u16,
    valid_frames: u16,

    pub fn clearData(self: *AkAudioBuffer) void {
        c.WWISEC_AkAudioBuffer_ClearData(@ptrCast(self));
    }

    pub fn clear(self: *AkAudioBuffer) void {
        c.WWISEC_AkAudioBuffer_Clear(@ptrCast(self));
    }

    pub fn numChannels(self: *const AkAudioBuffer) u32 {
        return c.WWISEC_AkAudioBuffer_NumChannels(@ptrCast(self));
    }

    pub fn hasLFE(self: *const AkAudioBuffer) bool {
        return c.WWISEC_AkAudioBufer_HasLFE(@ptrCast(self));
    }

    pub fn getChannelConfig(self: *const AkAudioBuffer) speaker_config.AkChannelConfig {
        return speaker_config.AkChannelConfig.fromC(
            c.WWISEC_AkAudioBuffer_GetChannelConfig(@ptrCast(self)),
        );
    }

    pub fn getInterleavedData(self: *AkAudioBuffer) ?*anyopaque {
        return c.WWISEC_AkAudioBuffer_GetInterleavedData(@ptrCast(self));
    }

    pub fn attachInterleavedData(self: *AkAudioBuffer, in_data: ?*anyopaque, in_max_frames: u16, in_valid_frames: u16) void {
        c.WWISEC_AkAudioBuffer_AttachInterleavedData(@ptrCast(self), in_data, in_max_frames, in_valid_frames);
    }

    pub fn attachInterleavedData1(self: *AkAudioBuffer, in_data: ?*anyopaque, in_max_frames: u16, in_valid_frames: u16, in_channel_config: speaker_config.AkChannelConfig) void {
        c.WWISEC_AkAudioBuffer_AttachInterleavedData1(@ptrCast(self), in_data, in_max_frames, in_valid_frames, in_channel_config.toC());
    }

    pub fn hasData(self: *const AkAudioBuffer) bool {
        return c.WWISEC_AkAudioBuffer_HasData(@ptrCast(self));
    }

    pub fn standardToPipelineIndex(in_channel_config: speaker_config.AkChannelConfig, in_channel_idx: u32) u32 {
        return c.WWISEC_AkAudioBuffer_StandardToPipelineIndex(in_channel_config.toC(), in_channel_idx);
    }

    pub fn getChannel(self: *AkAudioBuffer, in_index: u32) [*]AkSampleType {
        return c.WWISEC_AkAudioBuffer_GetChannel(@ptrCast(self), in_index);
    }

    pub fn getLFE(self: *AkAudioBuffer) [*]AkSampleType {
        return c.WWISEC_AkAudioBuffer_GetLFE(@ptrCast(self));
    }

    pub fn zeroPadToMaxFrames(self: *AkAudioBuffer) void {
        return c.WWISEC_AkAudioBuffer_ZeroPadToMaxFrames(@ptrCast(self));
    }

    pub fn attachContiguousDeinterleavedData(self: *AkAudioBuffer, in_data: ?*anyopaque, in_max_frames: u16, in_valid_frames: u16, in_channel_config: speaker_config.AkChannelConfig) void {
        return c.WWISEC_AkAudioBuffer_AttachContiguousDeinterleavedData(@ptrCast(self), in_data, in_max_frames, in_valid_frames, in_channel_config.toC());
    }

    pub fn detachContiguousDeinterleavedData(self: *AkAudioBuffer) ?*anyopaque {
        return c.WWISEC_AkAudioBuffer_DetachContiguousDeinterleavedData(@ptrCast(self));
    }

    pub fn checkValidSamples(self: *AkAudioBuffer) bool {
        return c.WWISEC_AkAudioBuffer_CheckValidSamples(@ptrCast(self));
    }

    pub fn relocateMedia(self: *AkAudioBuffer, in_new_media: [*]u8, in_old_media: [*]u8) void {
        c.WWISEC_AkAudioBuffer_RelocateMedia(@ptrCast(self), in_new_media, in_old_media);
    }

    pub fn maxFrames(self: *const AkAudioBuffer) u16 {
        return c.WWISEC_AkAudioBuffer_MaxFrames(@ptrCast(self));
    }

    comptime {
        std.debug.assert(@sizeOf(AkAudioBuffer) == @sizeOf(c.WWISEC_AkAudioBuffer));
    }
};
