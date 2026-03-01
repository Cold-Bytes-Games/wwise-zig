const ak_3d_objects = @import("ak_3d_objects.zig");
const c = @import("wwise_c");
const constants = @import("constants.zig");
const reflect_game_data = @import("SpatialAudio/reflect_game_data.zig");
const spatial_audio_types = @import("SpatialAudio/types.zig");
const std = @import("std");
const typedefs = @import("typedefs.zig");
const zig = @import("zig.zig");

pub const ReverbEstimation = @import("SpatialAudio/ReverbEstimation.zig");

pub const AK_MAX_NUM_TEXTURE = spatial_audio_types.AK_MAX_NUM_TEXTURE;
pub const AK_MAX_REFLECT_ORDER = spatial_audio_types.AK_MAX_REFLECT_ORDER;
pub const AK_MAX_REFLECTION_PATH_LENGTH = spatial_audio_types.AK_MAX_REFLECTION_PATH_LENGTH;
pub const AK_STOCHASTIC_RESERVE_LENGTH = spatial_audio_types.AK_STOCHASTIC_RESERVE_LENGTH;
pub const AK_MAX_SOUND_PROPAGATION_DEPTH = spatial_audio_types.AK_MAX_SOUND_PROPAGATION_DEPTH;
pub const AK_MAX_SOUND_PROPAGATION_WIDTH = spatial_audio_types.AK_MAX_SOUND_PROPAGATION_WIDTH;
pub const AK_SA_EPSILON = spatial_audio_types.AK_SA_EPSILON;
pub const AK_SA_DIFFRACTION_EPSILON = spatial_audio_types.AK_SA_DIFFRACTION_EPSILON;
pub const AK_SA_DIFFRACTION_DOT_EPSILON = spatial_audio_types.AK_SA_DIFFRACTION_DOT_EPSILON;
pub const AK_SA_PLANE_THICKNESS = spatial_audio_types.AK_SA_PLANE_THICKNESS;
pub const AK_SA_MIN_ENVIRONMENT_ABSORPTION = spatial_audio_types.AK_SA_MIN_ENVIRONMENT_ABSORPTION;
pub const AK_SA_MIN_ENVIRONMENT_SURFACE_AREA = spatial_audio_types.AK_SA_MIN_ENVIRONMENT_SURFACE_AREA;

pub const AK_INVALID_VERTEX = spatial_audio_types.AK_INVALID_VERTEX;
pub const AK_INVALID_TRIANGLE = spatial_audio_types.AK_INVALID_TRIANGLE;
pub const AK_INVALID_SURFACE = spatial_audio_types.AK_INVALID_SURFACE;
pub const AK_INVALID_SA_ID = spatial_audio_types.AK_INVALID_SA_ID;

pub const AkTransmissionOperation = spatial_audio_types.AkTransmissionOperation;
pub const AkRoomDistanceBehavior = spatial_audio_types.AkRoomDistanceBehavior;

pub const AkSpatialAudioID = spatial_audio_types.AkSpatialAudioID;
pub const AkRoomID = spatial_audio_types.AkRoomID;
pub const AkVertex = spatial_audio_types.AkVertex;
pub const AkPortalID = spatial_audio_types.AkPortalID;
pub const AkGeometrySetID = spatial_audio_types.AkGeometrySetID;
pub const AkGeometryInstanceID = spatial_audio_types.AkGeometryInstanceID;

pub const AkImageSourceName = spatial_audio_types.AkImageSourceName;
pub const AkSpatialAudioInitSettings = spatial_audio_types.AkSpatialAudioInitSettings;
pub const AkImageSourceParams = spatial_audio_types.AkImageSourceParams;
pub const AkImageSourceTexture = spatial_audio_types.AkImageSourceTexture;
pub const AkImageSourceSettings = spatial_audio_types.AkImageSourceSettings;
pub const AkExtent = spatial_audio_types.AkExtent;
pub const AkTriangle = spatial_audio_types.AkTriangle;
pub const AkAcousticSurface = spatial_audio_types.AkAcousticSurface;
pub const AkReflectionPathInfo = spatial_audio_types.AkReflectionPathInfo;
pub const AkDiffractionPathInfo = spatial_audio_types.AkDiffractionPathInfo;
pub const AkPortalParams = spatial_audio_types.AkPortalParams;
pub const AkRoomParams = spatial_audio_types.AkRoomParams;
pub const AkGeometryParams = spatial_audio_types.AkGeometryParams;

pub const AK_DEFAULT_GEOMETRY_POSITION_X = spatial_audio_types.AK_DEFAULT_GEOMETRY_POSITION_X;
pub const AK_DEFAULT_GEOMETRY_POSITION_Y = spatial_audio_types.AK_DEFAULT_GEOMETRY_POSITION_Y;
pub const AK_DEFAULT_GEOMETRY_POSITION_Z = spatial_audio_types.AK_DEFAULT_GEOMETRY_POSITION_Z;
pub const AK_DEFAULT_GEOMETRY_FRONT_X = spatial_audio_types.AK_DEFAULT_GEOMETRY_FRONT_X;
pub const AK_DEFAULT_GEOMETRY_FRONT_Y = spatial_audio_types.AK_DEFAULT_GEOMETRY_FRONT_Y;
pub const AK_DEFAULT_GEOMETRY_FRONT_Z = spatial_audio_types.AK_DEFAULT_GEOMETRY_FRONT_Z;
pub const AK_DEFAULT_GEOMETRY_TOP_X = spatial_audio_types.AK_DEFAULT_GEOMETRY_TOP_X;
pub const AK_DEFAULT_GEOMETRY_TOP_Y = spatial_audio_types.AK_DEFAULT_GEOMETRY_TOP_Y;
pub const AK_DEFAULT_GEOMETRY_TOP_Z = spatial_audio_types.AK_DEFAULT_GEOMETRY_TOP_Z;

pub const AkGeometryInstanceParams = spatial_audio_types.AkGeometryInstanceParams;

pub const AkReflectImageSource = reflect_game_data.AkReflectImageSource;
pub const AkReflectGameData = reflect_game_data.AkReflectGameData;

pub fn getOutdoorRoomID() AkRoomID {
    return AkRoomID.fromC(c.WWISEC_AK_SpatialAudio_kOutdoorRoomID);
}

pub fn init(in_init_settings: *const AkSpatialAudioInitSettings) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_Init(@ptrCast(in_init_settings)),
    );
}

pub fn registerListener(in_game_object_id: typedefs.AkGameObjectID) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_RegisterListener(in_game_object_id),
    );
}

pub fn unregisterListener(in_game_object_id: typedefs.AkGameObjectID) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_UnregisterListener(in_game_object_id),
    );
}

pub fn setGameObjectRadius(in_game_object_id: typedefs.AkGameObjectID, in_outer_radius: f32, in_inner_radius: f32) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetGameObjectRadius(in_game_object_id, in_outer_radius, in_inner_radius),
    );
}

pub const SetImageSourceOptionalArgs = struct {
    aux_bus_id: typedefs.AkAuxBusID = constants.AK_INVALID_AUX_ID,
    game_object_id: typedefs.AkGameObjectID = constants.AK_INVALID_GAME_OBJECT,
};

pub fn setImageSource(fallback_allocator: std.mem.Allocator, in_src_id: typedefs.AkImageSourceID, in_info: *const AkImageSourceSettings, in_name: []const u8, optional_args: SetImageSourceOptionalArgs) zig.WwiseError!void {
    var stack_char_allocator = zig.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_name = zig.toCString(allocator, in_name) catch return zig.WwiseError.Fail;
    defer allocator.free(raw_name);

    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetImageSource(
            in_src_id,
            @ptrCast(@alignCast(in_info)),
            raw_name,
            optional_args.aux_bus_id,
            optional_args.game_object_id,
        ),
    );
}

pub const RemoveImageSourceOptionalArgs = struct {
    aux_bus_id: typedefs.AkAuxBusID = constants.AK_INVALID_AUX_ID,
    game_object_id: typedefs.AkGameObjectID = constants.AK_INVALID_GAME_OBJECT,
};

pub fn removeImageSource(in_src_id: typedefs.AkImageSourceID, optional_args: RemoveImageSourceOptionalArgs) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_RemoveImageSource(
            in_src_id,
            optional_args.aux_bus_id,
            optional_args.game_object_id,
        ),
    );
}

pub const ClearImageSourcesOptionalArgs = struct {
    aux_bus_id: typedefs.AkAuxBusID = constants.AK_INVALID_AUX_ID,
    game_object_id: typedefs.AkGameObjectID = constants.AK_INVALID_GAME_OBJECT,
};

pub fn clearImageSources(optional_args: ClearImageSourcesOptionalArgs) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_ClearImageSources(
            optional_args.aux_bus_id,
            optional_args.game_object_id,
        ),
    );
}

pub fn setGeometry(in_geom_set_id: AkGeometrySetID, in_params: *const AkGeometryParams) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetGeometry(
            in_geom_set_id.toC(),
            @ptrCast(@alignCast(in_params)),
        ),
    );
}

pub fn removeGeometry(in_set_id: AkGeometrySetID) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_RemoveGeometry(in_set_id.toC()),
    );
}

pub fn setGeometryInstance(in_geometry_instance_id: AkGeometryInstanceID, in_params: *const AkGeometryInstanceParams) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetGeometryInstance(
            in_geometry_instance_id.toC(),
            @ptrCast(@alignCast(in_params)),
        ),
    );
}

pub fn removeGeometryInstance(in_geometry_instance_id: AkGeometryInstanceID) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_RemoveGeometryInstance(in_geometry_instance_id.toC()),
    );
}

pub fn queryReflectionPaths(
    in_game_object_id: typedefs.AkGameObjectID,
    in_position_index: u32,
    out_listener_pos: *ak_3d_objects.AkVector64,
    out_emitter_pos: *ak_3d_objects.AkVector64,
    out_paths: [*]AkReflectionPathInfo,
    io_array_size: *u32,
) zig.WwiseError!void {
    return zig.handleAkResult(
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

pub fn setRoom(in_room_id: AkRoomID, in_params: *const AkRoomParams, optional_args: SetRoomOptionalArgs) zig.WwiseError!void {
    var area_allocator_opt: ?std.heap.ArenaAllocator = null;
    defer {
        if (area_allocator_opt) |area_allocator| {
            area_allocator.deinit();
        }
    }

    const raw_name = blk: {
        if (optional_args.allocator != null and optional_args.room_name != null) {
            area_allocator_opt = std.heap.ArenaAllocator.init(optional_args.allocator.?);

            const converted_name = zig.toCString(area_allocator_opt.?.allocator(), optional_args.room_name.?) catch return zig.WwiseError.Fail;

            break :blk @as(?[*:0]const u8, converted_name);
        }

        break :blk @as(?[*:0]const u8, null);
    };

    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetRoom(
            in_room_id.toC(),
            @ptrCast(@alignCast(in_params)),
            raw_name,
        ),
    );
}

pub fn removeRoom(in_room_id: AkRoomID) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_RemoveRoom(in_room_id.toC()),
    );
}

pub const SetPortalOptionalArgs = struct {
    allocator: ?std.mem.Allocator = null,
    portal_name: ?[]const u8 = null,
};

pub fn setPortal(in_portal_id: AkPortalID, in_params: *const AkPortalParams, optional_args: SetPortalOptionalArgs) zig.WwiseError!void {
    var area_allocator_opt: ?std.heap.ArenaAllocator = null;
    defer {
        if (area_allocator_opt) |area_allocator| {
            area_allocator.deinit();
        }
    }

    const raw_name = blk: {
        if (optional_args.allocator != null and optional_args.portal_name != null) {
            area_allocator_opt = std.heap.ArenaAllocator.init(optional_args.allocator.?);

            const converted_name = zig.toCString(area_allocator_opt.?.allocator(), optional_args.portal_name.?) catch return zig.WwiseError.Fail;

            break :blk @as(?[*:0]const u8, converted_name);
        }

        break :blk @as(?[*:0]const u8, null);
    };

    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetPortal(
            in_portal_id.toC(),
            @ptrCast(@alignCast(in_params)),
            raw_name,
        ),
    );
}

pub fn removePortal(in_portal_id: AkPortalID) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_RemovePortal(in_portal_id.toC()),
    );
}

pub fn setReverbZone(in_reverb_zone: AkRoomID, in_parent_room: AkRoomID, in_transition_region_width: f32) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetReverbZone(in_reverb_zone.toC(), in_parent_room.toC(), in_transition_region_width),
    );
}

pub fn removeReverbZone(in_reverb_zone: AkRoomID) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_RemoveReverbZone(in_reverb_zone.toC()),
    );
}

pub fn setGameObjectInRoom(in_game_object_id: typedefs.AkGameObjectID, in_current_room_id: AkRoomID) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetGameObjectInRoom(in_game_object_id, in_current_room_id.toC()),
    );
}

pub fn unsetGameObjectInRoom(in_game_object_id: typedefs.AkGameObjectID) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_UnsetGameObjectInRoom(in_game_object_id),
    );
}

pub fn setAdjacentRoomBleed(in_adjacent_room_bleed: f32) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetAdjacentRoomBleed(in_adjacent_room_bleed),
    );
}

pub fn setReflectionsOrder(in_reflection_order: u32, in_update_paths: bool) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetReflectionsOrder(in_reflection_order, in_update_paths),
    );
}

pub fn setDiffractionOrder(in_diffraction_order: u32, in_update_paths: bool) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetDiffractionOrder(in_diffraction_order, in_update_paths),
    );
}

pub fn setMaxGlobalReflectionPaths(in_max_global_reflection_paths: u32) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetMaxGlobalReflectionPaths(in_max_global_reflection_paths),
    );
}

pub const SetMaxDiffractionPathsOptionalArgs = struct {
    game_object_id: typedefs.AkGameObjectID = constants.AK_INVALID_GAME_OBJECT,
};
pub fn setMaxDiffractionPaths(in_max_diffraction_paths: u32, optional_args: SetMaxDiffractionPathsOptionalArgs) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetMaxDiffractionPaths(
            in_max_diffraction_paths,
            optional_args.game_object_id,
        ),
    );
}

pub fn setMaxEmitterRoomAuxSends(in_max_emitter_room_aux_sends: u32) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetMaxEmitterRoomAuxSends(in_max_emitter_room_aux_sends),
    );
}

pub fn setNumberOfPrimaryRays(in_nb_primary_rays: u32) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetNumberOfPrimaryRays(in_nb_primary_rays),
    );
}

pub fn setLoadBalancingSpread(in_nb_frames: u32) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetLoadBalancingSpread(in_nb_frames),
    );
}

pub const SetSmoothingConstantOptionalArgs = struct {
    game_object_id: typedefs.AkGameObjectID = constants.AK_INVALID_GAME_OBJECT,
};
pub fn setSmoothingConstant(in_smoothing_constant_ms: f32, optional_args: SetSmoothingConstantOptionalArgs) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetSmoothingConstant(
            in_smoothing_constant_ms,
            optional_args.game_object_id,
        ),
    );
}

pub fn setEarlyReflectionsAuxSend(in_game_object_id: typedefs.AkGameObjectID, in_aux_bus_id: typedefs.AkAuxBusID) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetEarlyReflectionsAuxSend(in_game_object_id, in_aux_bus_id),
    );
}

pub fn setEarlyReflectionsVolume(in_game_object_id: typedefs.AkGameObjectID, in_send_volume: f32) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetEarlyReflectionsVolume(in_game_object_id, in_send_volume),
    );
}

pub const SetPortalObstructionAndOcclusionOptionalArgs = struct {
    transition: bool = false,
};
pub fn setPortalObstructionAndOcclusion(in_portal_id: AkPortalID, obstruction: f32, occlusion: f32, optional_args: SetPortalObstructionAndOcclusionOptionalArgs) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetPortalObstructionAndOcclusion(in_portal_id.toC(), obstruction, occlusion, optional_args.transition),
    );
}

pub fn setGameObjectToPortalObstruction(in_game_object_id: typedefs.AkGameObjectID, in_portal_id: AkPortalID, in_obstruction: f32) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetGameObjectToPortalObstruction(in_game_object_id, in_portal_id.toC(), in_obstruction),
    );
}

pub fn setPortalToPortalObstruction(in_portal_id_0: AkPortalID, in_portal_id_1: AkPortalID, in_obstruction: f32) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetPortalToPortalObstruction(in_portal_id_0.toC(), in_portal_id_1.toC(), in_obstruction),
    );
}

pub fn queryWetDiffraction(in_portal: AkPortalID) zig.WwiseError!f32 {
    var out_wet_diffraction: f32 = 0;

    try zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_QueryWetDiffraction(in_portal.toC(), &out_wet_diffraction),
    );

    return out_wet_diffraction;
}

pub fn queryDiffractionPaths(
    in_game_object_id: typedefs.AkGameObjectID,
    in_position_index: u32,
    out_listener_pos: *ak_3d_objects.AkVector64,
    out_emitter_pos: *ak_3d_objects.AkVector64,
    out_paths: ?[*]AkDiffractionPathInfo,
    io_array_size: *u32,
) zig.WwiseError!void {
    return zig.handleAkResult(
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

pub fn setTransmissionOperation(in_operation: AkTransmissionOperation) zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_SetTransmissionOperation(@intFromEnum(in_operation)),
    );
}

pub fn resetStochasticEngine() zig.WwiseError!void {
    return zig.handleAkResult(
        c.WWISEC_AK_SpatialAudio_ResetStochasticEngine(),
    );
}
