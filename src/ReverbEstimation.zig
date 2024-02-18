const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const virtual_acoustics = @import("virtual_acoustics.zig");

pub fn calculateSlope(texture: *const virtual_acoustics.AkAcousticTexture) f32 {
    return c.WWISEC_AK_SpatialAudio_ReverbEstimation_CalculateSlope(@ptrCast(texture));
}

pub fn getAverageAbsorptionValues(in_textures: *virtual_acoustics.AkAcousticTexture, in_surface_areas: *f32, in_num_textures: i32, out_average: *virtual_acoustics.AkAcousticTexture) void {
    return c.WWISEC_AK_SpatialAudio_ReverbEstimation_GetAverageAbsorptionValues(
        @ptrCast(in_textures),
        in_surface_areas,
        in_num_textures,
        @ptrCast(out_average),
    );
}

pub fn estimateT60Decay(in_volume_cubic_meters: f32, in_surface_area_squared_meters: f32, in_environment_average_absorption: f32) common.WwiseError!f32 {
    var out_decay_estimate: f32 = 0.0;

    try common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_ReverbEstimation_EstimateT60Decay(
            in_volume_cubic_meters,
            in_surface_area_squared_meters,
            in_environment_average_absorption,
            &out_decay_estimate,
        ),
    );

    return out_decay_estimate;
}

pub const EstimateTimeToFirstReflectionOptionalArgs = struct {
    speed_of_sound: f32 = 343.0,
};

pub fn estimateTimeToFirstReflection(in_environment_extent_meters: common.AkVector, out_time_to_first_reflection_ms: *f32, optional_args: EstimateTimeToFirstReflectionOptionalArgs) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_SpatialAudio_ReverbEstimation_EstimateTimeToFirstReflection(
            in_environment_extent_meters.toC(),
            out_time_to_first_reflection_ms,
            optional_args.speed_of_sound,
        ),
    );
}

pub fn estimateHFDamping(in_texture: ?[*]virtual_acoustics.AkAcousticTexture, in_surface_areas: ?*f32, in_num_textures: i32) f32 {
    return c.WWISEC_AK_SpatialAudio_ReverbEstimation_EstimateHFDamping(
        @ptrCast(in_texture),
        in_surface_areas,
        in_num_textures,
    );
}
