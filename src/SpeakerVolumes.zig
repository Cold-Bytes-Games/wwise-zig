const std = @import("std");
const c = @import("wwise_c");
const common = @import("common.zig");

pub const VectorPtr = c.WWISEC_AK_SpeakerVolumes_VectorPtr;
pub const MatrixPtr = c.WWISEC_AK_SpeakerVolumes_MatrixPtr;
pub const ConstVectorPtr = c.WWISEC_AK_SpeakerVolumes_ConstVectorPtr;
pub const ConstMatrixPtr = c.WWISEC_AK_SpeakerVolumes_ConstMatrixPtr;
