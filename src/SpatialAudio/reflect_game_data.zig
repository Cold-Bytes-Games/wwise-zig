const ak_3d_objects = @import("../ak_3d_objects.zig");
const c = @import("wwise_c");
const constants = @import("../constants.zig");
const spatial_audio_types = @import("types.zig");
const std = @import("std");
const typedefs = @import("../typedefs.zig");

pub const AkReflectImageSource = extern struct {
    id: typedefs.AkImageSourceID = std.math.maxInt(u32),
    params: spatial_audio_types.AkImageSourceParams = .{},
    texture: spatial_audio_types.AkImageSourceTexture = .{},
    name: spatial_audio_types.AkImageSourceName = .{},

    // mlarouche: We can't convert directly from the translate-c AkReflectImageSource
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.WWISEC_AkReflectImageSource) AkReflectImageSource {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkReflectImageSource) c.WWISEC_AkReflectImageSource {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkReflectImageSource) == @sizeOf(c.WWISEC_AkReflectImageSource));
    // }
};

pub const AkReflectGameData = extern struct {
    listener_id: typedefs.AkGameObjectID = constants.AK_INVALID_GAME_OBJECT,
    num_image_sources: u32 = 0,
    sources: [1]AkReflectImageSource = undefined,

    // mlarouche: We can't convert directly from the translate-c AkReflectGameData
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.WWISEC_AkReflectGameData) AkReflectGameData {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkReflectGameData) c.WWISEC_AkReflectGameData {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkReflectGameData) == @sizeOf(c.WWISEC_AkReflectGameData));
    // }
};
