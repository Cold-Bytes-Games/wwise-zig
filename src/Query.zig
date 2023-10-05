const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const SpeakerVolumes = @import("SpeakerVolumes.zig");
const speaker_config = @import("speaker_config.zig");

pub const AkPositioningInfo = extern struct {
    center_pct: f32 = 0,
    panner_type: common.AkSpeakerPanningType = .direct_speaker_assignment,
    @"3d_positioning_type": common.Ak3DPositionType = .emitter,
    hold_emitter_pos_and_orient: bool = false,
    @"3d_spatialization_mode": common.Ak3DSpatializationMode = .none,
    enable_attenuation: bool = false,
    use_cone_attenuation: bool = false,
    inner_angle: f32 = 0.0,
    outer_angle: f32 = 0.0,
    cone_max_attenuation: f32 = 0.0,
    lpf_cone: common.AkLPFType = 0,
    hpf_cone: common.AkLPFType = 0,
    max_distance: f32 = 0.0,
    vol_dry_at_max_dist: f32 = 0.0,
    vol_aux_game_def_at_max_dist: f32 = 0.0,
    vol_aux_user_def_at_max_dist: f32 = 0.0,
    lpf_value_at_max_dist: common.AkLPFType = 0.0,
    hpf_value_at_max_dist: common.AkLPFType = 0.0,

    pub inline fn fromC(value: c.WWISEC_AkPositioningInfo) AkPositioningInfo {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkPositioningInfo) c.WWISEC_AkPositioningInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkPositioningInfo) == @sizeOf(c.WWISEC_AkPositioningInfo));
    }
};

pub const AkObjectInfo = extern struct {
    obj_id: common.AkUniqueID = common.AK_INVALID_UNIQUE_ID,
    parent_id: common.AkUniqueID = common.AK_INVALID_UNIQUE_ID,
    depth: i32 = 0,

    pub inline fn fromC(value: c.WWISEC_AkObjectInfo) AkObjectInfo {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkObjectInfo) c.WWISEC_AkObjectInfo {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkObjectInfo) == @sizeOf(c.WWISEC_AkObjectInfo));
    }
};

pub fn getPosition(in_game_object_id: common.AkGameObjectID) common.WwiseError!common.AkSoundPosition {
    var result: common.AkSoundPosition = .{};

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetPosition(
            in_game_object_id,
            @ptrCast(&result),
        ),
    );

    return result;
}

pub fn getListeners(in_game_object_id: common.AkGameObjectID, out_listener_object_ids: [*]common.AkGameObjectID, oi_num_listeners: *u32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetListeners(
            in_game_object_id,
            out_listener_object_ids,
            oi_num_listeners,
        ),
    );
}

pub fn getListenerPosition(in_listener_id: common.AkGameObjectID) common.WwiseError!common.AkListenerPosition {
    var result: common.AkListenerPosition = .{};

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetListenerPosition(
            in_listener_id,
            @ptrCast(&result),
        ),
    );

    return result;
}

pub fn getListenerSpatialization(in_listener_id: common.AkGameObjectID, out_spatialized: *bool, out_volume_offsets: *[*]SpeakerVolumes.VectorPtr, out_channel_config: *speaker_config.AkChannelConfig) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetListenerSpatialization(
            in_listener_id,
            out_spatialized,
            @ptrCast(out_volume_offsets),
            @ptrCast(out_channel_config),
        ),
    );
}

pub const RTPCValue_type = enum(common.DefaultEnumType) {
    default = c.WWISEC_AK_SoundEngine_Query_RTPCValue_type_RTPCValue_Default,
    global = c.WWISEC_AK_SoundEngine_Query_RTPCValue_type_RTPCValue_Global,
    game_object = c.WWISEC_AK_SoundEngine_Query_RTPCValue_type_RTPCValue_GameObject,
    playing_id = c.WWISEC_AK_SoundEngine_Query_RTPCValue_type_RTPCValue_PlayingID,
    unavailable = c.WWISEC_AK_SoundEngine_Query_RTPCValue_type_RTPCValue_Unavailable,
};

pub fn getRTPCValueID(in_rtpc_id: common.AkRtpcID, in_game_object_id: common.AkGameObjectID, in_playing_id: common.AkPlayingID, out_value: *common.AkRtpcValue, io_value_type: *RTPCValue_type) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetRTPCValue_ID(
            in_rtpc_id,
            in_game_object_id,
            in_playing_id,
            out_value,
            @ptrCast(io_value_type),
        ),
    );
}

pub fn getRTPCValueString(fallback_allocator: std.mem.Allocator, in_rtpc_name: []const u8, in_game_object_id: common.AkGameObjectID, in_playing_id: common.AkPlayingID, out_value: *common.AkRtpcValue, io_value_type: *RTPCValue_type) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_rtpc_name = common.toCString(allocator, in_rtpc_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_rtpc_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetRTPCValue_String(
            raw_rtpc_name,
            in_game_object_id,
            in_playing_id,
            out_value,
            @ptrCast(io_value_type),
        ),
    );
}

pub fn getSwitchID(in_switch_group: common.AkSwitchGroupID, in_game_object_id: common.AkGameObjectID) common.WwiseError!common.AkSwitchStateID {
    var result: common.AkSwitchStateID = 0;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetSwitch_ID(
            in_switch_group,
            in_game_object_id,
            &result,
        ),
    );

    return result;
}

pub fn getSwitchString(fallback_allocator: std.mem.Allocator, in_switch_group_name: []const u8, in_game_object_id: common.AkGameObjectID) common.WwiseError!common.AkSwitchStateID {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_switch_group_name = common.toCString(allocator, in_switch_group_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_switch_group_name);

    var result: common.AkSwitchStateID = 0;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetSwitch_String(
            raw_switch_group_name,
            in_game_object_id,
            &result,
        ),
    );

    return result;
}

pub fn getStateID(in_state_group: common.AkStateGroupID) common.WwiseError!common.AkStateID {
    var result: common.AkStateID = 0;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetState_ID(
            in_state_group,
            &result,
        ),
    );

    return result;
}

pub fn getStateString(fallback_allocator: std.mem.Allocator, in_state_group_name: []const u8) common.WwiseError!common.AkStateID {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_state_group_name = common.toCString(allocator, in_state_group_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_state_group_name);

    var result: common.AkStateID = 0;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetState_String(
            raw_state_group_name,
            &result,
        ),
    );

    return result;
}

pub fn getGameObjectAuxSendValues(in_game_object_id: common.AkGameObjectID, out_aux_send_values: ?[*]common.AkAuxSendValue, io_num_send_values: *u32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetGameObjectAuxSendValues(
            in_game_object_id,
            @ptrCast(out_aux_send_values),
            io_num_send_values,
        ),
    );
}

pub fn getGameObjectDryLevelValue(in_emitter_id: common.AkGameObjectID, in_listener_id: common.AkGameObjectID) common.WwiseError!f32 {
    var result: f32 = 0.0;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetGameObjectDryLevelValue(
            in_emitter_id,
            in_listener_id,
            &result,
        ),
    );

    return result;
}

pub fn getObjectObstructionAndOcclusion(in_emitter_id: common.AkGameObjectID, in_listener_id: common.AkGameObjectID, out_obstruction_level: *f32, out_occlusion_level: *f32) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetObjectObstructionAndOcclusion(
            in_emitter_id,
            in_listener_id,
            out_obstruction_level,
            out_occlusion_level,
        ),
    );
}

pub fn queryAudioObjectIDsID(in_event_id: common.AkUniqueID, io_num_items: *u32, out_object_infos: ?[*]AkObjectInfo) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_QueryAudioObjectIDs_ID(
            in_event_id,
            io_num_items,
            @ptrCast(out_object_infos),
        ),
    );
}

pub fn queryAudioObjectIDsString(fallback_allocator: std.mem.Allocator, in_event_name: []const u8, io_num_items: *u32, out_object_infos: ?[*]AkObjectInfo) common.WwiseError!void {
    var stack_char_allocator = common.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    var raw_event_name = common.toCString(allocator, in_event_name) catch return common.WwiseError.Fail;
    defer allocator.free(raw_event_name);

    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_QueryAudioObjectIDs_String(
            raw_event_name,
            io_num_items,
            @ptrCast(out_object_infos),
        ),
    );
}

pub fn getPositioningInfo(in_object_id: common.AkUniqueID, out_positioning_info: *AkPositioningInfo) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetPositioningInfo(
            in_object_id,
            @ptrCast(out_positioning_info),
        ),
    );
}

pub const AkGameObjectsList = extern struct {
    items: ?[*]common.AkGameObjectID = null,
    length: u32 = 0,
    reserved: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_AK_SoundEngine_Query_AkGameObjectsList) AkGameObjectsList {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkGameObjectsList) c.WWISEC_AK_SoundEngine_Query_AkGameObjectsList {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkGameObjectsList) == @sizeOf(c.WWISEC_AK_SoundEngine_Query_AkGameObjectsList));
    }
};

pub fn getActiveGameObjects(io_game_object_list: *AkGameObjectsList) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetActiveGameObjects(@ptrCast(io_game_object_list)),
    );
}

pub fn WWISEC_AK_SoundEngine_Query_GetIsGameObjectActive(in_game_object_id: common.AkGameObjectID) bool {
    return c.WWISEC_AK_SoundEngine_Query_GetIsGameObjectActive(in_game_object_id);
}

pub const GameObjDst = extern struct {
    game_object_id: common.AkGameObjectID = common.AK_INVALID_GAME_OBJECT,
    distance: f32 = -1.0,

    pub inline fn fromC(value: c.WWISEC_AK_SoundEngine_Query_GameObjDst) GameObjDst {
        return @bitCast(value);
    }

    pub inline fn toC(self: GameObjDst) c.WWISEC_AK_SoundEngine_Query_GameObjDst {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(GameObjDst) == @sizeOf(c.WWISEC_AK_SoundEngine_Query_GameObjDst));
    }
};

pub const AkRadiusList = extern struct {
    items: ?[*]GameObjDst = null,
    length: u32 = 0,
    reserved: u32 = 0,

    pub inline fn fromC(value: c.WWISEC_AK_SoundEngine_Query_AkRadiusList) AkRadiusList {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkRadiusList) c.WWISEC_AK_SoundEngine_Query_AkRadiusList {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkRadiusList) == @sizeOf(c.WWISEC_AK_SoundEngine_Query_AkRadiusList));
    }
};

pub fn getMaxRadiusList(io_radius_list: *AkRadiusList) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetMaxRadius_List(@ptrCast(io_radius_list)),
    );
}

pub fn getMaxRadiusSingle(in_game_object_id: common.AkGameObjectID) f32 {
    return c.WWISEC_AK_SoundEngine_Query_GetMaxRadius_Single(in_game_object_id);
}

pub fn getEventIDFromPlayingID(in_playing_id: common.AkPlayingID) common.AkUniqueID {
    return c.WWISEC_AK_SoundEngine_Query_GetEventIDFromPlayingID(in_playing_id);
}

pub fn getGameObjectFromPlayingID(in_playing_id: common.AkPlayingID) common.AkGameObjectID {
    return c.WWISEC_AK_SoundEngine_Query_GetGameObjectFromPlayingID(in_playing_id);
}

pub fn getPlayingIDsFromGameObject(in_game_object_id: common.AkGameObjectID, io_num_ids: *u32, out_playing_ids: ?[*]common.AkPlayingID) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetPlayingIDsFromGameObject(
            in_game_object_id,
            io_num_ids,
            @ptrCast(out_playing_ids),
        ),
    );
}

pub fn getCustomPropertyValueInt(in_object_id: common.AkUniqueID, in_prop_id: u32) common.WwiseError!i32 {
    var out_value: i32 = 0;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetCustomPropertyValue_Int(
            in_object_id,
            in_prop_id,
            &out_value,
        ),
    );

    return out_value;
}

pub fn getCustomPropertyValueFloat(in_object_id: common.AkUniqueID, in_prop_id: u32) common.WwiseError!f32 {
    var out_value: f32 = 0.0;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_Query_GetCustomPropertyValue_Float(
            in_object_id,
            in_prop_id,
            &out_value,
        ),
    );

    return out_value;
}
