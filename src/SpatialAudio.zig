const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const reflect_game_data = @import("reflect_game_data.zig");

pub const ReverbEstimation = @import("ReverbEstimation.zig");

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
    transmission_loss: f32 = 0.0,
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
    triangles: ?[*]const AkTriangle = null,
    num_triangles: AkTriIdx = 0,
    vertices: ?[*]const AkVertex = null,
    num_vertices: AkVertIdx = 0,
    surfaces: ?[*]const AkAcousticSurface = null,
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

pub fn init(in_init_settings: *const AkSpatialAudioInitSettings) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_Init(@ptrCast(in_init_settings)),
    );
}

pub fn registerListener(in_game_object_id: common.AkGameObjectID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_RegisterListener(in_game_object_id),
    );
}

pub fn unregisterListener(in_game_object_id: common.AkGameObjectID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_UnregisterListener(in_game_object_id),
    );
}

pub fn setGameObjectRadius(in_game_object_id: common.AkGameObjectID, in_outer_radius: f32, in_inner_radius: f32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetGameObjectRadius(in_game_object_id, in_outer_radius, in_inner_radius),
    );
}

pub const SetImageSourceOptionalArgs = struct {
    aux_bus_id: common.AkAuxBusID = common.AK_INVALID_AUX_ID,
    game_object_id: common.AkGameObjectID = common.AK_INVALID_GAME_OBJECT,
};

pub fn setImageSource(fallback_allocator: std.mem.Allocator, in_src_id: common.AkImageSourceID, in_info: *const AkImageSourceSettings, in_name: []const u8, optional_args: SetImageSourceOptionalArgs) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_name = common.toCString(allocator, in_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_name);

    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetImageSource(
            in_src_id,
            @ptrCast(in_info),
            raw_name,
            optional_args.aux_bus_id,
            optional_args.game_object_id,
        ),
    );
}

pub const RemoveImageSourceOptionalArgs = struct {
    aux_bus_id: common.AkAuxBusID = common.AK_INVALID_AUX_ID,
    game_object_id: common.AkGameObjectID = common.AK_INVALID_GAME_OBJECT,
};

pub fn removeImageSource(in_src_id: common.AkImageSourceID, optional_args: RemoveImageSourceOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_RemoveImageSource(
            in_src_id,
            optional_args.aux_bus_id,
            optional_args.game_object_id,
        ),
    );
}

pub const ClearImageSourcesOptionalArgs = struct {
    aux_bus_id: common.AkAuxBusID = common.AK_INVALID_AUX_ID,
    game_object_id: common.AkGameObjectID = common.AK_INVALID_GAME_OBJECT,
};

pub fn clearImageSources(optional_args: ClearImageSourcesOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_ClearImageSources(
            optional_args.aux_bus_id,
            optional_args.game_object_id,
        ),
    );
}

pub fn setGeometry(in_geom_set_id: AkGeometrySetID, in_params: *const AkGeometryParams) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetGeometry(
            in_geom_set_id.toC(),
            @ptrCast(in_params),
        ),
    );
}

pub fn removeGeometry(in_set_id: AkGeometrySetID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_RemoveGeometry(in_set_id.toC()),
    );
}

pub fn setGeometryInstance(in_geometry_instance_id: AkGeometryInstanceID, in_params: *const AkGeometryInstanceParams) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetGeometryInstance(
            in_geometry_instance_id.toC(),
            @ptrCast(in_params),
        ),
    );
}

pub fn removeGeometryInstance(in_geometry_instance_id: AkGeometryInstanceID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_RemoveGeometryInstance(in_geometry_instance_id.toC()),
    );
}

pub fn queryReflectionPaths(
    in_game_object_id: common.AkGameObjectID,
    in_position_index: u32,
    out_listener_pos: *common.AkVector64,
    out_emitter_pos: *common.AkVector64,
    out_paths: [*]AkReflectionPathInfo,
    io_array_size: *u32,
) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_QueryReflectionPaths(
            in_game_object_id,
            in_position_index,
            @ptrCast(out_listener_pos),
            @ptrCast(out_emitter_pos),
            @ptrCast(out_paths),
            io_array_size,
        ),
    );
}

pub const SetRoomOptionalArgs = struct {
    allocator: ?std.mem.Allocator = null,
    room_name: ?[]const u8 = null,
};

pub fn setRoom(in_room_id: AkRoomID, in_params: *const AkRoomParams, optional_args: SetRoomOptionalArgs) common.WwiseError!void {
    var area_allocator_opt: ?std.heap.ArenaAllocator = null;
    defer {
        if (area_allocator_opt) |area_allocator| {
            area_allocator.deinit();
        }
    }

    const raw_name = blk: {
        if (optional_args.allocator != null and optional_args.room_name != null) {
            area_allocator_opt = std.heap.ArenaAllocator.init(optional_args.allocator.?);

            const converted_name = common.toCString(area_allocator_opt.?.allocator(), optional_args.room_name.?) catch return common.WwiseError.Fail;

            break :blk @as(?[*:0]const u8, converted_name);
        }

        break :blk @as(?[*:0]const u8, null);
    };

    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetRoom(
            in_room_id.toC(),
            @ptrCast(in_params),
            raw_name,
        ),
    );
}

pub fn removeRoom(in_room_id: AkRoomID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_RemoveRoom(in_room_id.toC()),
    );
}

pub const SetPortalOptionalArgs = struct {
    allocator: ?std.mem.Allocator = null,
    portal_name: ?[]const u8 = null,
};

pub fn setPortal(in_portal_id: AkPortalID, in_params: *const AkPortalParams, optional_args: SetPortalOptionalArgs) common.WwiseError!void {
    var area_allocator_opt: ?std.heap.ArenaAllocator = null;
    defer {
        if (area_allocator_opt) |area_allocator| {
            area_allocator.deinit();
        }
    }

    const raw_name = blk: {
        if (optional_args.allocator != null and optional_args.portal_name != null) {
            area_allocator_opt = std.heap.ArenaAllocator.init(optional_args.allocator.?);

            const converted_name = common.toCString(area_allocator_opt.?.allocator(), optional_args.portal_name.?) catch return common.WwiseError.Fail;

            break :blk @as(?[*:0]const u8, converted_name);
        }

        break :blk @as(?[*:0]const u8, null);
    };

    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetPortal(
            in_portal_id.toC(),
            @ptrCast(in_params),
            raw_name,
        ),
    );
}

pub fn removePortal(in_portal_id: AkPortalID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_RemovePortal(in_portal_id.toC()),
    );
}

pub fn setGameObjectInRoom(in_game_object_id: common.AkGameObjectID, in_current_room_id: AkRoomID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetGameObjectInRoom(in_game_object_id, in_current_room_id.toC()),
    );
}

pub fn setReflectionsOrder(in_reflection_order: u32, in_update_paths: bool) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetReflectionsOrder(in_reflection_order, in_update_paths),
    );
}

pub fn setDiffractionOrder(in_diffraction_order: u32, in_update_paths: bool) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetDiffractionOrder(in_diffraction_order, in_update_paths),
    );
}

pub fn setNumberOfPrimaryRays(in_nb_primary_rays: u32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetNumberOfPrimaryRays(in_nb_primary_rays),
    );
}

pub fn setLoadBalancingSpread(in_nb_frames: u32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetLoadBalancingSpread(in_nb_frames),
    );
}

pub fn setEarlyReflectionsAuxSend(in_game_object_id: common.AkGameObjectID, in_aux_bus_id: common.AkAuxBusID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetEarlyReflectionsAuxSend(in_game_object_id, in_aux_bus_id),
    );
}

pub fn setEarlyReflectionsVolume(in_game_object_id: common.AkGameObjectID, in_send_volume: f32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetEarlyReflectionsVolume(in_game_object_id, in_send_volume),
    );
}

pub fn setPortalObstructionAndOcclusion(in_portal_id: AkPortalID, obstruction: f32, occlusion: f32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetPortalObstructionAndOcclusion(in_portal_id.toC(), obstruction, occlusion),
    );
}

pub fn setGameObjectToPortalObstruction(in_game_object_id: common.AkGameObjectID, in_portal_id: AkPortalID, in_obstruction: f32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetGameObjectToPortalObstruction(in_game_object_id, in_portal_id.toC(), in_obstruction),
    );
}

pub fn setPortalToPortalObstruction(in_portal_id_0: AkPortalID, in_portal_id_1: AkPortalID, in_obstruction: f32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetPortalToPortalObstruction(in_portal_id_0.toC(), in_portal_id_1.toC(), in_obstruction),
    );
}

pub fn queryWetDiffraction(in_portal: AkPortalID) common.WwiseError!f32 {
    var out_wet_diffraction: f32 = 0;

    try common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_QueryWetDiffraction(in_portal.toC(), &out_wet_diffraction),
    );

    return out_wet_diffraction;
}

pub fn queryDiffractionPaths(
    in_game_object_id: common.AkGameObjectID,
    in_position_index: u32,
    out_listener_pos: *common.AkVector64,
    out_emitter_pos: *common.AkVector64,
    out_paths: ?[*]AkDiffractionPathInfo,
    io_array_size: *u32,
) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_QueryDiffractionPaths(
            in_game_object_id,
            in_position_index,
            @ptrCast(out_listener_pos),
            @ptrCast(out_emitter_pos),
            @ptrCast(out_paths),
            io_array_size,
        ),
    );
}

pub fn resetStochasticEngine() common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_ResetStochasticEngine(),
    );
}
