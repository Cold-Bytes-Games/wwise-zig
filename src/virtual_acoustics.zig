const std = @import("std");
const c = @import("c.zig");

pub const AkAcousticTexture = extern struct {
    id: u32 = 0,
    absorption_offset: f32 = 0.0,
    absorption_low: f32 = 0.0,
    absorption_mid_low: f32 = 0.0,
    absorption_mid_high: f32 = 0.0,
    absorption_high: f32 = 0.0,
    scattering: f32 = 0.0,

    pub fn fromC(value: c.WWISEC_AkAcousticTexture) AkAcousticTexture {
        return @bitCast(value);
    }

    pub fn toC(self: AkAcousticTexture) c.WWISEC_AkAcousticTexture {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkAcousticTexture) == @sizeOf(c.WWISEC_AkAcousticTexture));
    }
};
