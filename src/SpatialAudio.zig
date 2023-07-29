const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");

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
