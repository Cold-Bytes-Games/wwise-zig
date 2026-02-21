const c = @import("wwise_c");
const enums = @import("enums.zig");
const std = @import("std");
const typedefs = @import("typedefs.zig");

pub const AkVector64 = extern struct {
    x: f64 = 0.0,
    y: f64 = 0.0,
    z: f64 = 0.0,

    pub fn add(left: AkVector64, right: AkVector64) AkVector64 {
        return .{
            .x = left.x + right.x,
            .y = left.y + right.y,
            .z = left.z + right.z,
        };
    }

    pub fn sub(left: AkVector64, right: AkVector64) AkVector64 {
        return .{
            .x = left.x - right.x,
            .y = left.y - right.y,
            .z = left.z - right.z,
        };
    }

    pub fn zero(self: *AkVector64) void {
        self.x = 0.0;
        self.y = 0.0;
        self.z = 0.0;
    }

    pub inline fn toAkVector(self: AkVector64) AkVector {
        return .{
            .x = @truncate(self.x),
            .y = @truncate(self.y),
            .z = @truncate(self.z),
        };
    }

    pub inline fn fromC(value: c.AkVector64) AkVector64 {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkVector64) c.AkVector64 {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkVector64) == @sizeOf(c.AkVector64));
    }
};

pub const AkVector = extern struct {
    x: f32 = 0.0,
    y: f32 = 0.0,
    z: f32 = 0.0,

    pub fn add(left: AkVector, right: AkVector) AkVector {
        return .{
            .x = left.x + right.x,
            .y = left.y + right.y,
            .z = left.z + right.z,
        };
    }

    pub fn sub(left: AkVector, right: AkVector) AkVector {
        return .{
            .x = left.x - right.x,
            .y = left.y - right.y,
            .z = left.z - right.z,
        };
    }

    pub fn mulScalar(left: AkVector, right: f32) AkVector {
        return .{
            .x = left.x * right,
            .y = left.y * right,
            .z = left.z * right,
        };
    }

    pub fn divScalar(left: AkVector, right: f32) AkVector {
        return .{
            .x = left.x / right,
            .y = left.y / right,
            .z = left.z / right,
        };
    }

    pub fn zero(self: *AkVector) void {
        self.x = 0.0;
        self.y = 0.0;
        self.z = 0.0;
    }

    pub inline fn toAkVector64(self: AkVector) AkVector64 {
        return .{
            .x = self.x,
            .y = self.y,
            .z = self.z,
        };
    }

    pub inline fn fromC(value: c.AkVector) AkVector {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkVector) c.AkVector {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkVector) == @sizeOf(c.AkVector));
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

    pub inline fn fromC(value: c.AkWorldTransform) AkWorldTransform {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkWorldTransform) c.AkWorldTransform {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkWorldTransform) == @sizeOf(c.AkWorldTransform));
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

    pub inline fn fromC(value: c.AkTransform) AkTransform {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkTransform) c.AkTransform {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkTransform) == @sizeOf(c.AkTransform));
    }
};

pub const AkSoundPosition = AkWorldTransform;
pub const AkListenerPosition = AkWorldTransform;

pub const AkChannelEmitter = extern struct {
    position: AkWorldTransform = .{},
    input_channels: typedefs.AkChannelMask = 0,

    pub inline fn fromC(value: c.AkChannelEmitter) AkChannelEmitter {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkChannelEmitter) c.AkChannelEmitter {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkChannelEmitter) == @sizeOf(c.AkChannelEmitter));
    }
};

pub const AkPolarCoord = extern struct {
    r: f32 = 0.0,
    theta: f32 = 0.0,

    pub inline fn fromC(value: c.AkPolarCoord) AkPolarCoord {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkPolarCoord) c.AkPolarCoord {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkPolarCoord) == @sizeOf(c.AkPolarCoord));
    }
};

pub const AkSphericalCoord = extern struct {
    base: AkPolarCoord = .{},
    phi: f32 = 0.0,

    pub inline fn fromC(value: c.WWISEC_AkSphericalCoord) AkSphericalCoord {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkSphericalCoord) c.WWISEC_AkSphericalCoord {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkSphericalCoord) == @sizeOf(c.WWISEC_AkSphericalCoord));
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
    emitter_channel_mask: typedefs.AkChannelMask = 0xFFFFFFFF,
    id: typedefs.AkRayID = 0,
    listener_id: typedefs.AkGameObjectID = 0,

    pub fn getGainForConnectionType(self: AkEmitterListenerPair, in_type: enums.AkConnectionType) f32 {
        return switch (in_type) {
            .direct => self.dry_mix_gain,
            .game_def_send => self.game_def_aux_mix_gain,
            .user_def_send => self.user_def_aux_mix_gain,
            else => 1.0,
        };
    }

    pub inline fn fromC(value: c.WWISEC_AkEmitterListenerPair) AkEmitterListenerPair {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkEmitterListenerPair) c.WWISEC_AkEmitterListenerPair {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkEmitterListenerPair) == @sizeOf(c.WWISEC_AkEmitterListenerPair));
    }
};

pub const AkListener = extern struct {
    position: AkListenerPosition = .{},
    scaling_factor: f32 = 1.0,
    spatialized: bool = true,

    pub inline fn fromC(value: c.AkListener) AkListener {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkListener) c.AkListener {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkListener) == @sizeOf(c.AkListener));
    }
};
