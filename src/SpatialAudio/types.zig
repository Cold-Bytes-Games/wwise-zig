const ak_3d_objects = @import("../ak_3d_objects.zig");
const c = @import("wwise_c");
const constants = @import("../constants.zig");
const std = @import("std");
const typedefs = @import("../typedefs.zig");
const zig = @import("../zig.zig");

pub const AK_MAX_NUM_TEXTURE = c.AK_MAX_NUM_TEXTURE;
pub const AK_MAX_REFLECT_ORDER = c.AK_MAX_REFLECT_ORDER;
pub const AK_MAX_REFLECTION_PATH_LENGTH = c.AK_MAX_REFLECTION_PATH_LENGTH;
pub const AK_STOCHASTIC_RESERVE_LENGTH = c.AK_STOCHASTIC_RESERVE_LENGTH;
pub const AK_MAX_SOUND_PROPAGATION_DEPTH = c.AK_MAX_SOUND_PROPAGATION_DEPTH;
pub const AK_MAX_SOUND_PROPAGATION_WIDTH = c.AK_MAX_SOUND_PROPAGATION_WIDTH;
pub const AK_SA_EPSILON = c.AK_SA_EPSILON;
pub const AK_SA_DIFFRACTION_EPSILON = c.AK_SA_DIFFRACTION_EPSILON;
pub const AK_SA_DIFFRACTION_DOT_EPSILON = c.AK_SA_DIFFRACTION_DOT_EPSILON;
pub const AK_SA_PLANE_THICKNESS = c.AK_SA_PLANE_THICKNESS;
pub const AK_SA_MIN_ENVIRONMENT_ABSORPTION = c.AK_SA_MIN_ENVIRONMENT_ABSORPTION;
pub const AK_SA_MIN_ENVIRONMENT_SURFACE_AREA = c.AK_SA_MIN_ENVIRONMENT_SURFACE_AREA;

pub const AK_INVALID_VERTEX = c.AK_INVALID_VERTEX;
pub const AK_INVALID_TRIANGLE = c.AK_INVALID_TRIANGLE;
pub const AK_INVALID_SURFACE = c.AK_INVALID_SURFACE;
pub const AK_INVALID_SA_ID = c.AK_INVALID_SA_ID;

pub const AkTransmissionOperation = enum(zig.DefaultEnumType) {
    add = c.AkTransmissionOperation_Add,
    multiply = c.AkTransmissionOperation_Multiply,
    max = c.AkTransmissionOperation_Max,

    pub const default: AkTransmissionOperation = .max;
};

pub const AkRoomDistanceBehavior = enum(zig.DefaultEnumType) {
    subtract,
    exclude,

    pub const default: AkRoomDistanceBehavior = .subtract;
};

pub const AkSpatialAudioID = extern struct {
    id: c.AkSpatialAudioID = std.math.maxInt(c.AkSpatialAudioID),

    pub inline fn fromC(value: c.AkSpatialAudioID) AkSpatialAudioID {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkSpatialAudioID) c.AkSpatialAudioID {
        return @bitCast(self);
    }

    pub fn isValid(self: AkSpatialAudioID) bool {
        return self.id != std.math.maxInt(c.AkSpatialAudioID);
    }

    pub fn asGameObjectID(self: AkSpatialAudioID) typedefs.AkGameObjectID {
        return self.id;
    }
};

pub const AkRoomID = extern struct {
    id: c.AkRoomID = std.math.maxInt(c.AkRoomID),

    const OutdoorsGameObjID = c.WWISEC_AkRoomID_OutdoorsGameObjID;

    pub fn fromC(value: c.AkRoomID) AkRoomID {
        return @bitCast(value);
    }

    pub fn toC(self: AkRoomID) c.AkRoomID {
        return @bitCast(self);
    }

    pub fn isValid(self: AkRoomID) bool {
        return self.id != std.math.maxInt(c.AkRoomID);
    }

    pub fn asGameObjectID(self: AkRoomID) typedefs.AkGameObjectID {
        return if (self.isValid()) self.id else OutdoorsGameObjID;
    }

    pub fn fromGameObjectID(game_object_id: typedefs.AkGameObjectID) AkRoomID {
        return if (game_object_id != OutdoorsGameObjID) AkRoomID{ .id = game_object_id } else AkRoomID{};
    }
};

pub const AkVertex = ak_3d_objects.AkVector;

pub const AkPortalID = AkSpatialAudioID;
pub const AkGeometrySetID = AkSpatialAudioID;
pub const AkGeometryInstanceID = AkSpatialAudioID;

pub const AkImageSourceName = extern struct {
    num_char: u32 = 0,
    name: ?[*:0]u8 = null,

    pub inline fn fromC(value: c.AkImageSourceName) AkImageSourceName {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkImageSourceName) c.AkImageSourceName {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkImageSourceName) == @sizeOf(c.AkImageSourceName));
    }
};

pub const AkSpatialAudioInitSettings = extern struct {
    max_sound_propagation_depth: u32 = AK_MAX_SOUND_PROPAGATION_DEPTH,
    movement_threshold: f32 = 0.25,
    number_of_primary_rays: u32 = 35,
    max_reflection_order: u32 = 2,
    max_diffraction_order: u32 = 4,
    max_diffraction_paths: u32 = 8,
    max_global_reflection_paths: u32 = 0,
    max_emitter_room_aux_sends: u32 = 3,
    diffraction_on_reflections_order: u32 = 2,
    max_diffraction_angle_degrees: f32 = 180.0,
    max_path_length: f32 = 10000.0,
    cpu_limit_percentage: f32 = 0.0,
    load_balancing_spread: u32 = 1,
    smoothing_constant_ms: f32 = 0.0,
    adjacent_room_bleed: f32 = 1.0,
    enable_geometric_diffraction_and_transmission: bool = true,
    calc_emitter_virtual_position: bool = true,
    transmission_operation: AkTransmissionOperation = .default,
    clustering_min_points: u32 = 0,
    clustering_max_distance: f32 = 5.0,
    clustering_dead_zone_distance: f32 = 10.0,

    pub inline fn fromC(value: c.AkSpatialAudioInitSettings) AkSpatialAudioInitSettings {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkSpatialAudioInitSettings) c.AkSpatialAudioInitSettings {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkSpatialAudioInitSettings) == @sizeOf(c.AkSpatialAudioInitSettings));
    }
};

pub const AkImageSourceParams = extern struct {
    source_position: ak_3d_objects.AkVector64 = .{},
    distance_scaling_factor: f32 = 1.0,
    level: f32 = 1.0,
    diffraction: f32 = 0.0,
    occlusion: f32 = 0.0,
    diffraction_emitter_side: u8 = 0.0,
    diffraction_listener_side: u8 = 0.0,

    pub inline fn fromC(value: c.AkImageSourceParams) AkImageSourceParams {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkImageSourceParams) c.AkImageSourceParams {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkImageSourceParams) == @sizeOf(c.AkImageSourceParams));
    }
};

pub const AkImageSourceTexture = extern struct {
    num_texture: u32 = 0,
    texture_ids: [AK_MAX_NUM_TEXTURE]typedefs.AkUniqueID = undefined,

    pub inline fn fromC(value: c.AkImageSourceTexture) AkImageSourceTexture {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkImageSourceTexture) c.AkImageSourceTexture {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkImageSourceTexture) == @sizeOf(c.AkImageSourceTexture));
    }
};

pub const AkImageSourceSettings = extern struct {
    params: AkImageSourceParams = .{},
    texture: AkImageSourceTexture = .{},

    pub inline fn fromC(value: c.AkImageSourceSettings) AkImageSourceSettings {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkImageSourceSettings) c.AkImageSourceSettings {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkImageSourceSettings) == @sizeOf(c.AkImageSourceSettings));
    }
};

pub const AkExtent = extern struct {
    half_width: f32 = 0.0,
    half_height: f32 = 0.0,
    half_depth: f32 = 0.0,

    pub inline fn fromC(value: c.AkExtent) AkExtent {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkExtent) c.AkExtent {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkExtent) == @sizeOf(c.AkExtent));
    }
};

pub const AkTriangle = extern struct {
    point0: typedefs.AkVertIdx = AK_INVALID_VERTEX,
    point1: typedefs.AkVertIdx = AK_INVALID_VERTEX,
    point2: typedefs.AkVertIdx = AK_INVALID_VERTEX,
    surface: typedefs.AkSurfIdx = AK_INVALID_SURFACE,

    pub inline fn fromC(value: c.AkTriangle) AkTriangle {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkTriangle) c.AkTriangle {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkTriangle) == @sizeOf(c.AkTriangle));
    }
};

pub const AkAcousticSurface = extern struct {
    texture_id: u32 = constants.AK_INVALID_UNIQUE_ID,
    transmission_loss: f32 = 1.0,
    str_name: ?[*:0]const u8 = null,

    pub inline fn fromC(value: c.AkAcousticSurface) AkAcousticSurface {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkAcousticSurface) c.AkAcousticSurface {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkAcousticSurface) == @sizeOf(c.AkAcousticSurface));
    }
};

pub const AkReflectionPathInfo = extern struct {
    image_source: ak_3d_objects.AkVector64 = .{},
    path_point: [AK_MAX_REFLECTION_PATH_LENGTH]ak_3d_objects.AkVector64 = @splat(.{}),
    texture_ids: [AK_MAX_REFLECTION_PATH_LENGTH]u32 = @splat(0),
    num_path_points: u32 = 0,
    num_reflections: u32 = 0,
    diffraction: [AK_MAX_REFLECTION_PATH_LENGTH]f32 = @splat(0.0),
    level: f32 = 0.0,
    is_occluded: bool = false,

    pub inline fn fromC(value: c.AkReflectionPathInfo) AkReflectionPathInfo {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkReflectionPathInfo) c.AkReflectionPathInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkReflectionPathInfo) == @sizeOf(c.AkReflectionPathInfo));
    }
};

pub const AkDiffractionPathInfo = extern struct {
    nodes: [AK_MAX_SOUND_PROPAGATION_DEPTH]ak_3d_objects.AkVector64 = @splat(.{}),
    emitter_pos: ak_3d_objects.AkVector64 = .{},
    angles: [AK_MAX_SOUND_PROPAGATION_DEPTH]f32 = @splat(0.0),
    portals: [AK_MAX_SOUND_PROPAGATION_DEPTH]AkPortalID = @splat(.{}),
    rooms: [AK_MAX_SOUND_PROPAGATION_DEPTH + 1]AkRoomID = @splat(.{}),
    virtual_pos: ak_3d_objects.AkWorldTransform = .{},
    node_count: u32 = 0,
    diffraction: f32 = 0.0,
    transmission_loss: f32 = 0.0,
    tot_length: f32 = 0.0,
    obstruction_value: f32 = 0.0,
    occlusion_value: f32 = 0.0,
    gain: f32 = 0.0,

    pub inline fn fromC(value: c.AkDiffractionPathInfo) AkDiffractionPathInfo {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkDiffractionPathInfo) c.AkDiffractionPathInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkDiffractionPathInfo) == @sizeOf(c.AkDiffractionPathInfo));
    }
};

pub const AkPortalParams = extern struct {
    transform: ak_3d_objects.AkWorldTransform = .{},
    extent: AkExtent = .{},
    enabled: bool = false,
    front_room: AkRoomID = .{},
    back_room: AkRoomID = .{},
    adjacent_room_bleed: f32 = 1.0,

    pub inline fn fromC(value: c.AkPortalParams) AkPortalParams {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkPortalParams) c.AkPortalParams {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkPortalParams) == @sizeOf(c.AkPortalParams));
    }
};

pub const AkRoomParams = extern struct {
    front: ak_3d_objects.AkVector = .{ .z = 1.0 },
    up: ak_3d_objects.AkVector = .{ .y = 1.0 },
    reverb_aux_bus: typedefs.AkAuxBusID = constants.AK_INVALID_AUX_ID,
    reverb_level: f32 = 1.0,
    transmission_loss: f32 = 1.0,
    room_game_obj_aux_send_level_to_self: f32 = 0.0,
    room_game_obj_keep_registered: bool = false,
    geometry_instance_id: AkGeometrySetID = .{},
    room_priority: f32 = 100.0,
    distance_behavior: AkRoomDistanceBehavior = .default,

    pub inline fn fromC(value: c.AkRoomParams) AkRoomParams {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkRoomParams) c.AkRoomParams {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkRoomParams) == @sizeOf(c.AkRoomParams));
    }
};

pub const AkGeometryParams = extern struct {
    triangles: ?[*]const AkTriangle align(4) = null,
    num_triangles: typedefs.AkTriIdx align(4) = 0,
    vertices: ?[*]const AkVertex align(4) = null,
    num_vertices: typedefs.AkVertIdx align(4) = 0,
    surfaces: ?[*]const AkAcousticSurface align(4) = null,
    num_surfaces: typedefs.AkSurfIdx align(4) = 0,
    enable_diffraction: bool align(1) = false,
    enable_diffraction_on_boundary_edges: bool align(1) = false,

    // mlarouche: We can't convert directly from the translate-c AkGeometryParams
    // because it use #pragma pack(push, 4) on the C side and it is not translated
    // properly

    // pub inline fn fromC(value: c.AkGeometryParams) AkGeometryParams {
    //     return @bitCast(value);
    // }

    // pub inline fn toC(self: AkGeometryParams) c.AkGeometryParams {
    //     return @bitCast(self);
    // }

    // comptime {
    //     std.debug.assert(@sizeOf(AkGeometryParams) == @sizeOf(c.AkGeometryParams));
    // }
};

pub const AK_DEFAULT_GEOMETRY_POSITION_X = c.AK_DEFAULT_GEOMETRY_POSITION_X;
pub const AK_DEFAULT_GEOMETRY_POSITION_Y = c.AK_DEFAULT_GEOMETRY_POSITION_Y;
pub const AK_DEFAULT_GEOMETRY_POSITION_Z = c.AK_DEFAULT_GEOMETRY_POSITION_Z;
pub const AK_DEFAULT_GEOMETRY_FRONT_X = c.AK_DEFAULT_GEOMETRY_FRONT_X;
pub const AK_DEFAULT_GEOMETRY_FRONT_Y = c.AK_DEFAULT_GEOMETRY_FRONT_Y;
pub const AK_DEFAULT_GEOMETRY_FRONT_Z = c.AK_DEFAULT_GEOMETRY_FRONT_Z;
pub const AK_DEFAULT_GEOMETRY_TOP_X = c.AK_DEFAULT_GEOMETRY_TOP_X;
pub const AK_DEFAULT_GEOMETRY_TOP_Y = c.AK_DEFAULT_GEOMETRY_TOP_Y;
pub const AK_DEFAULT_GEOMETRY_TOP_Z = c.AK_DEFAULT_GEOMETRY_TOP_Z;

pub const AkGeometryInstanceParams = extern struct {
    position_and_orientation: ak_3d_objects.AkWorldTransform = .{
        .position = .{
            .x = AK_DEFAULT_GEOMETRY_POSITION_X,
            .y = AK_DEFAULT_GEOMETRY_POSITION_Y,
            .z = AK_DEFAULT_GEOMETRY_POSITION_Z,
        },
        .orientation_front = .{
            .x = AK_DEFAULT_GEOMETRY_FRONT_X,
            .y = AK_DEFAULT_GEOMETRY_FRONT_Y,
            .z = AK_DEFAULT_GEOMETRY_FRONT_Z,
        },
        .orientation_top = .{
            .x = AK_DEFAULT_GEOMETRY_TOP_X,
            .y = AK_DEFAULT_GEOMETRY_TOP_Y,
            .z = AK_DEFAULT_GEOMETRY_TOP_Z,
        },
    },
    scale: ak_3d_objects.AkVector = .{
        .x = 1,
        .y = 1,
        .z = 1,
    },
    geometry_set_id: AkGeometrySetID = .{},
    use_for_reflection_and_diffraction: bool = true,
    bypass_portal_subtraction: bool = false,
    is_solid: bool = false,

    pub inline fn fromC(value: c.AkGeometryInstanceParams) AkGeometryInstanceParams {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkGeometryInstanceParams) c.AkGeometryInstanceParams {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkGeometryInstanceParams) == @sizeOf(c.AkGeometryInstanceParams));
    }
};
