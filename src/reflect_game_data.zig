const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");

pub const AK_MAX_NUM_TEXTURE = c.WWISEC_AK_MAX_NUM_TEXTURE;

pub const AkImageSourceName = extern struct {
    num_char: u32 = 0,
    name: ?[*:0]const u8 = null,

    pub fn fromC(value: c.WWISEC_AkImageSourceName) AkImageSourceName {
        return @bitCast(value);
    }

    pub fn toC(self: AkImageSourceName) c.WWISEC_AkImageSourceName {
        return @bitCast(self);
    }
};

pub const AkImageSourceTexture = extern struct {
    num_texture: u32 = 0,
    texture_ids: [AK_MAX_NUM_TEXTURE]common.AkUniqueID = undefined,

    pub fn fromC(value: c.WWISEC_AkImageSourceTexture) AkImageSourceTexture {
        return @bitCast(value);
    }

    pub fn toC(self: AkImageSourceTexture) c.WWISEC_AkImageSourceTexture {
        return @bitCast(self);
    }
};

pub const AkImageSourceParams = extern struct {
    source_position: common.AkVector64 = .{},
    distance_scaling_factor: f32 = 1.0,
    level: f32 = 1.0,
    diffraction: f32 = 0.0,
    diffraction_emitter_side: u8 = 0.0,
    diffraction_listener_side: u8 = 0.0,

    pub fn fromC(value: c.WWISEC_AkImageSourceParams) AkImageSourceParams {
        return @bitCast(value);
    }

    pub fn toC(self: AkImageSourceParams) c.WWISEC_AkImageSourceParams {
        return @bitCast(self);
    }
};

pub const AkReflectImageSource = extern struct {
    id: common.AkImageSourceID = std.math.maxInt(u32),
    params: AkImageSourceParams = .{},
    texture: AkImageSourceTexture = .{},
    name: AkImageSourceName = .{},

    pub fn fromC(value: c.WWISEC_AkReflectImageSource) AkReflectImageSource {
        return @bitCast(value);
    }

    pub fn toC(self: AkReflectImageSource) c.WWISEC_AkReflectImageSource {
        return @bitCast(self);
    }
};

pub const AkReflectGameData = extern struct {
    listener_id: common.AkGameObjectID = common.AK_INVALID_GAME_OBJECT,
    num_image_sources: u32 = 0,
    sources: [1]AkReflectImageSource = undefined,

    pub fn fromC(value: c.WWISEC_AkReflectGameData) AkReflectGameData {
        return @bitCast(value);
    }

    pub fn toC(self: AkReflectGameData) c.WWISEC_AkReflectGameData {
        return @bitCast(self);
    }

    pub fn getSize(num_sources: u32) u32 {
        return if (num_sources > 0) @sizeOf(AkReflectGameData) + (num_sources - 1) * @sizeOf(AkReflectImageSource) else @sizeOf(AkReflectGameData);
    }

    comptime {
        std.debug.assert(@sizeOf(AkReflectGameData) == @sizeOf(c.WWISEC_AkReflectGameData));
    }
};
