const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const reflect_game_data = @import("reflect_game_data.zig");

pub const AK_MAX_REFLECT_ORDER = c.WWISEC_AK_MAX_REFLECT_ORDER;
pub const AK_MAX_REFLECTION_PATH_LENGTH = c.WWISEC_AK_MAX_REFLECTION_PATH_LENGTH;
pub const AK_MAX_SOUND_PROPAGATION_DEPTH = c.WWISEC_AK_MAX_SOUND_PROPAGATION_DEPTH;
pub const AK_MAX_SOUND_PROPAGATION_WIDTH = c.WWISEC_AK_MAX_SOUND_PROPAGATION_WIDTH;
pub const AK_DEFAULT_MOVEMENT_THRESHOLD = c.WWISEC_AK_DEFAULT_MOVEMENT_THRESHOLD;
pub const AK_SA_EPSILON = c.WWISEC_AK_SA_EPSILON;
pub const AK_SA_DIFFRACTION_EPSILON = c.WWISEC_AK_SA_DIFFRACTION_EPSILON;
pub const AK_SA_DIFFRACTION_DOT_EPSILON = c.WWISEC_AK_SA_DIFFRACTION_DOT_EPSILON;
pub const AK_SA_PLANE_THICKNESS_RATIO = c.WWISEC_AK_SA_PLANE_THICKNESS_RATIO;
pub const AK_SA_MIN_ENVIRONMENT_ABSORPTION = c.WWISEC_AK_SA_MIN_ENVIRONMENT_ABSORPTION;
pub const AK_SA_MIN_ENVIRONMENT_SURFACE_AREA = c.WWISEC_AK_SA_MIN_ENVIRONMENT_SURFACE_AREA;

pub const kDefaultDiffractionMaxEdges = c.WWISEC_kDefaultDiffractionMaxEdges;
pub const kDefaultDiffractionMaxPaths = c.WWISEC_kDefaultDiffractionMaxPaths;
pub const kMaxDiffraction = c.WWISEC_kMaxDiffraction;

pub const kDiffractionMaxEdges = c.WWISEC_kDiffractionMaxEdges;
pub const kDiffractionMaxPaths = c.WWISEC_kDiffractionMaxPaths;
pub const kPortalToPortalDiffractionMaxPaths = c.WWISEC_kPortalToPortalDiffractionMaxPaths;

pub const AkVertIdx = c.WWISEC_AkVertIdx;
pub const AkTriIdx = c.WWISEC_AkTriIdx;
pub const AkSurfIdx = c.WWISEC_AkSurfIdx;
pub const AkEdgeIdx = c.WWISEC_AkEdgeIdx;
pub const AkEdgeReceptorIdx = c.WWISEC_AkEdgeReceptorIdx;

pub const AK_INVALID_VERTEX = c.WWISEC_AK_INVALID_VERTEX;
pub const AK_INVALID_TRIANGLE = c.WWISEC_AK_INVALID_TRIANGLE;
pub const AK_INVALID_SURFACE = c.WWISEC_AK_INVALID_SURFACE;
pub const AK_INVALID_EDGE = c.WWISEC_AK_INVALID_EDGE;

pub const AkSpatialAudioID = extern struct {
    id: u64 = std.math.maxInt(u64),

    pub fn fromC(value: c.WWISEC_AkSpatialAudioID) AkSpatialAudioID {
        return @bitCast(value);
    }

    pub fn toC(self: AkSpatialAudioID) c.WWISEC_AkSpatialAudioID {
        return @bitCast(self);
    }

    pub fn isValid(self: AkSpatialAudioID) bool {
        return self.id != std.math.maxInt(u64);
    }

    pub fn asGameObjectID(self: AkSpatialAudioID) common.AkGameObjectID {
        return self.id;
    }
};

pub const AkRoomID = extern struct {
    id: u64 = std.math.maxInt(u64),

    const OutdoorsGameObjID = c.WWISEC_OutdoorsGameObjID;

    pub fn fromC(value: c.WWISEC_AkRoomID) AkRoomID {
        return @bitCast(value);
    }

    pub fn toC(self: AkRoomID) c.WWISEC_AkRoomID {
        return @bitCast(self);
    }

    pub fn isValid(self: AkRoomID) bool {
        return self.id != std.math.maxInt(u64);
    }

    pub fn asGameObjectID(self: AkRoomID) common.AkGameObjectID {
        return if (self.isValid()) self.id else OutdoorsGameObjID;
    }

    pub fn fromGameObjectID(game_object_id: common.AkGameObjectID) AkRoomID {
        return if (game_object_id != OutdoorsGameObjID) AkRoomID{ .id = game_object_id } else AkRoomID{};
    }
};

pub const AkPortalID = AkSpatialAudioID;
pub const AkGeometrySetID = AkSpatialAudioID;
pub const AkGeometryInstanceID = AkSpatialAudioID;

pub fn getOutdoorRoomID() AkRoomID {
    return AkRoomID.fromC(c.WWISEC_AK_SpatialAudio_kOutdoorRoomID);
}

pub const AkSpatialAudioInitSettings = extern struct {
    max_sound_propagation_depth: u32 = AK_MAX_SOUND_PROPAGATION_DEPTH,
    movement_threshold: f32 = AK_DEFAULT_MOVEMENT_THRESHOLD,
    number_of_primary_rays: u32 = 100,
    max_reflection_order: u32 = 1,
    max_diffraction_order: u32 = 8,
    diffraction_on_reflections_or: u32 = 2,
    max_path_length: f32 = 10000.0,
    cpu_limit_percentage: f32 = 0.0,
    load_balancing_spread: u32 = 1,
    enable_geometric_diffraction_and_transmission: bool = true,
    calc_emitter_virtual_position: bool = true,

    pub fn fromC(value: c.WWISEC_AkSpatialAudioInitSettings) AkSpatialAudioInitSettings {
        return @bitCast(value);
    }

    pub fn toC(self: AkSpatialAudioInitSettings) c.WWISEC_AkSpatialAudioInitSettings {
        return @bitCast(self);
    }
};

pub const AkImageSourceSettings = extern struct {
    params: reflect_game_data.AkImageSourceParams = .{},
    texture: reflect_game_data.AkImageSourceTexture = .{},

    pub fn fromC(value: c.WWISEC_AkImageSourceSettings) AkImageSourceSettings {
        return @bitCast(value);
    }

    pub fn toC(self: AkImageSourceSettings) c.WWISEC_AkImageSourceSettings {
        return @bitCast(self);
    }
};

pub const AkVertex = extern struct {
    x: f32 = 0.0,
    y: f32 = 0.0,
    z: f32 = 0.0,

    pub fn fromC(value: c.WWISEC_AkVertex) AkVertex {
        return @bitCast(value);
    }

    pub fn toC(self: AkVertex) c.WWISEC_AkVertex {
        return @bitCast(self);
    }
};

pub const AkExtent = extern struct {
    half_width: f32 = 0.0,
    half_height: f32 = 0.0,
    half_depth: f32 = 0.0,

    pub fn fromC(value: c.WWISEC_AkExtent) AkExtent {
        return @bitCast(value);
    }

    pub fn toC(self: AkExtent) c.WWISEC_AkExtent {
        return @bitCast(self);
    }
};

pub const AkTriangle = extern struct {
    point0: AkVertIdx = AK_INVALID_VERTEX,
    point1: AkVertIdx = AK_INVALID_VERTEX,
    point2: AkVertIdx = AK_INVALID_VERTEX,
    surface: AkSurfIdx = AK_INVALID_SURFACE,

    pub fn fromC(value: c.WWISEC_AkTriangle) AkTriangle {
        return @bitCast(value);
    }

    pub fn toC(self: AkTriangle) c.WWISEC_AkTriangle {
        return @bitCast(self);
    }
};

pub const AkAcousticSurface = extern struct {
    texture_id: u32 = common.AK_INVALID_UNIQUE_ID,
    transmission_loss: f32 = 1.0,
    str_name: ?[*:0]const u8 = null,

    pub fn fromC(value: c.WWISEC_AkAcousticSurface) AkAcousticSurface {
        return @bitCast(value);
    }

    pub fn toC(self: AkAcousticSurface) c.WWISEC_AkAcousticSurface {
        return @bitCast(self);
    }
};

pub const AkReflectionPathInfo = extern struct {
    image_source: common.AkVector64 = .{},
    path_point: [AK_MAX_REFLECTION_PATH_LENGTH]common.AkVector64 = [_]common.AkVector64{.{}} ** AK_MAX_REFLECTION_PATH_LENGTH,
    surfaces: [AK_MAX_REFLECTION_PATH_LENGTH]AkAcousticSurface = [_]AkAcousticSurface{.{}} ** AK_MAX_REFLECTION_PATH_LENGTH,
    num_path_points: u32 = 0,
    num_reflections: u32 = 0,
    diffraction: [AK_MAX_REFLECTION_PATH_LENGTH]f32 = [_]f32{0.0} ** AK_MAX_REFLECTION_PATH_LENGTH,
    level: f32 = 0.0,
    is_occluded: bool = false,

    pub fn fromC(value: c.WWISEC_AkReflectionPathInfo) AkReflectionPathInfo {
        return @bitCast(value);
    }

    pub fn toC(self: AkReflectionPathInfo) c.WWISEC_AkReflectionPathInfo {
        return @bitCast(self);
    }
};

pub const AkDiffractionPathInfo = extern struct {
    nodes: [AK_MAX_SOUND_PROPAGATION_DEPTH]common.AkVector64 = [_]common.AkVector64{.{}} ** AK_MAX_SOUND_PROPAGATION_DEPTH,
    emitter_pos: common.AkVector64 = .{},
    angles: [AK_MAX_SOUND_PROPAGATION_DEPTH]f32 = [_]f32{0.0} ** AK_MAX_SOUND_PROPAGATION_DEPTH,
    portals: [AK_MAX_SOUND_PROPAGATION_DEPTH]AkPortalID = [_]AkPortalID{.{}} ** AK_MAX_SOUND_PROPAGATION_DEPTH,
    rooms: [AK_MAX_SOUND_PROPAGATION_DEPTH + 1]AkRoomID = [_]AkRoomID{.{}} ** (AK_MAX_SOUND_PROPAGATION_DEPTH + 1),
    virtual_pos: common.AkWorldTransform = .{},
    node_count: u32 = 0,
    diffraction: f32 = 0.0,
    transmission_lost: f32 = 0.0,
    tot_length: f32 = 0.0,
    obstruction_value: f32 = 0.0,

    pub fn fromC(value: c.WWISEC_AkDiffractionPathInfo) AkDiffractionPathInfo {
        return @bitCast(value);
    }

    pub fn toC(self: AkDiffractionPathInfo) c.WWISEC_AkDiffractionPathInfo {
        return @bitCast(self);
    }
};

pub const AkPortalParams = extern struct {
    transform: common.AkWorldTransform = .{},
    extent: AkExtent = .{},
    enabled: bool = false,
    front_room: AkRoomID = .{},
    back_room: AkRoomID = .{},

    pub fn fromC(value: c.WWISEC_AkPortalParams) AkPortalParams {
        return @bitCast(value);
    }

    pub fn toC(self: AkPortalParams) c.WWISEC_AkPortalParams {
        return @bitCast(self);
    }
};

pub const AkRoomParams = extern struct {
    front: common.AkVector = .{ .z = 1.0 },
    up: common.AkVector = .{ .y = 1.0 },
    reverb_aux_bus: common.AkAuxBusID = common.AK_INVALID_AUX_ID,
    reverb_level: f32 = 1.0,
    transmission_loss: f32 = 1.0,
    room_game_obj_aux_send_level_to_self: f32 = 0.0,
    room_game_obj_keep_registered: bool = false,
    geometry_instance_id: AkGeometrySetID = .{},

    pub fn fromC(value: c.WWISEC_AkRoomParams) AkRoomParams {
        return @bitCast(value);
    }

    pub fn toC(self: AkRoomParams) c.WWISEC_AkRoomParams {
        return @bitCast(self);
    }
};

pub const AkGeometryParams = extern struct {
    triangles: ?[*]AkTriangle = null,
    num_triangles: AkTriIdx = 0,
    vertices: ?[*]AkVertex = null,
    num_vertices: AkVertIdx = 0,
    surfaces: ?[*]AkAcousticSurface = null,
    num_surfaces: AkSurfIdx = 0,
    enable_diffraction: bool = false,
    enable_diffraction_on_boundary_edges: bool = false,
    enable_triangles: bool = true,

    pub fn fromC(value: c.WWISEC_AkGeometryParams) AkGeometryParams {
        return @bitCast(value);
    }

    pub fn toC(self: AkGeometryParams) c.WWISEC_AkGeometryParams {
        return @bitCast(self);
    }
};

pub const AK_DEFAULT_GEOMETRY_POSITION_X = c.WWISEC_AK_DEFAULT_GEOMETRY_POSITION_X;
pub const AK_DEFAULT_GEOMETRY_POSITION_Y = c.WWISEC_AK_DEFAULT_GEOMETRY_POSITION_Y;
pub const AK_DEFAULT_GEOMETRY_POSITION_Z = c.WWISEC_AK_DEFAULT_GEOMETRY_POSITION_Z;
pub const AK_DEFAULT_GEOMETRY_FRONT_X = c.WWISEC_AK_DEFAULT_GEOMETRY_FRONT_X;
pub const AK_DEFAULT_GEOMETRY_FRONT_Y = c.WWISEC_AK_DEFAULT_GEOMETRY_FRONT_Y;
pub const AK_DEFAULT_GEOMETRY_FRONT_Z = c.WWISEC_AK_DEFAULT_GEOMETRY_FRONT_Z;
pub const AK_DEFAULT_GEOMETRY_TOP_X = c.WWISEC_AK_DEFAULT_GEOMETRY_TOP_X;
pub const AK_DEFAULT_GEOMETRY_TOP_Y = c.WWISEC_AK_DEFAULT_GEOMETRY_TOP_Y;
pub const AK_DEFAULT_GEOMETRY_TOP_Z = c.WWISEC_AK_DEFAULT_GEOMETRY_TOP_Z;

pub const AkGeometryInstanceParams = extern struct {
    position_and_orientation: common.AkWorldTransform = .{
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
    scale: common.AkVector = .{
        .x = 1,
        .y = 1,
        .z = 1,
    },
    geometry_set_id: AkGeometrySetID = .{},
    room_id: AkRoomID = .{},

    pub fn fromC(value: c.WWISEC_AkGeometryInstanceParams) AkGeometryInstanceParams {
        return @bitCast(value);
    }

    pub fn toC(self: AkGeometryInstanceParams) c.WWISEC_AkGeometryInstanceParams {
        return @bitCast(self);
    }
};
