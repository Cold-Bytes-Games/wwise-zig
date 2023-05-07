const std = @import("std");
const builtin = @import("builtin");
const c = @import("c.zig");
const wwise_options = @import("wwise_options");

pub const AkUniqueID = c.WWISEC_AkUniqueID;
pub const AkStateID = c.WWISEC_AkStateID;
pub const AkStateGroupID = c.WWISEC_AkStateGroupID;
pub const AkPlayingID = c.WWISEC_AkPlayingID;
pub const AkTimeMs = c.WWISEC_AkTimeMs;
pub const AkPortNumber = c.WWISEC_AkPortNumber;
pub const AkPitchValue = c.WWISEC_AkPitchValue;
pub const AkVolumeValue = c.WWISEC_AkVolumeValue;
pub const AkGameObjectID = c.WWISEC_AkGameObjectID;
pub const AkLPFType = c.WWISEC_AkLPFType;
pub const AkMemPoolId = c.WWISEC_AkMemPoolId;
pub const AkPluginID = c.WWISEC_AkPluginID;
pub const AkCodecID = c.WWISEC_AkCodecID;
pub const AkAuxBusID = c.WWISEC_AkAuxBusID;
pub const AkPluginParamID = c.WWISEC_AkPluginParamID;
pub const AkPriority = c.WWISEC_AkPriority;
pub const AkDataCompID = c.WWISEC_AkDataCompID;
pub const AkDataTypeID = c.WWISEC_AkDataTypeID;
pub const AkDataInterleaveID = c.WWISEC_AkDataInterleaveID;
pub const AkSwitchGroupID = c.WWISEC_AkSwitchGroupID;
pub const AkSwitchStateID = c.WWISEC_AkSwitchStateID;
pub const AkRtpcID = c.WWISEC_AkRtpcID;
pub const AkRtpcValue = c.WWISEC_AkRtpcValue;
pub const AkBankID = c.WWISEC_AkBankID;
pub const AkBankType = c.WWISEC_AkBankType;
pub const AkFileID = c.WWISEC_AkFileID;
pub const AkDeviceID = c.WWISEC_AkDeviceID;
pub const AkTriggerID = c.WWISEC_AkTriggerID;
pub const AkArgumentValueID = c.WWISEC_AkArgumentValueID;
pub const AkChannelMask = c.WWISEC_AkChannelMask;
pub const AkModulatorID = c.WWISEC_AkModulatorID;
pub const AkAcousticTextureID = c.WWISEC_AkAcousticTextureID;
pub const AkImageSourceID = c.WWISEC_AkImageSourceID;
pub const AkOutputDeviceID = c.WWISEC_AkOutputDeviceID;
pub const AkPipelineID = c.WWISEC_AkPipelineID;
pub const AkRayID = c.WWISEC_AkRayID;
pub const AkAudioObjectID = c.WWISEC_AkAudioObjectID;
pub const AkJobType = c.WWISEC_AkJobType;
pub const AK_INVALID_PLUGINID = c.WWISEC_AK_INVALID_PLUGINID;
pub const AK_INVALID_SHARE_SET_ID = c.WWISEC_AK_INVALID_SHARE_SET_ID;
pub const AK_INVALID_GAME_OBJECT = c.WWISEC_AK_INVALID_GAME_OBJECT;
pub const AK_INVALID_UNIQUE_ID = c.WWISEC_AK_INVALID_UNIQUE_ID;
pub const AK_INVALID_RTPC_ID = c.WWISEC_AK_INVALID_RTPC_ID;
pub const AK_INVALID_PLAYING_ID = c.WWISEC_AK_INVALID_PLAYING_ID;
pub const AK_DEFAULT_SWITCH_STATE = c.WWISEC_AK_DEFAULT_SWITCH_STATE;
pub const AK_INVALID_POOL_ID = c.WWISEC_AK_INVALID_POOL_ID;
pub const AK_DEFAULT_POOL_ID = c.WWISEC_AK_DEFAULT_POOL_ID;
pub const AK_INVALID_AUX_ID = c.WWISEC_AK_INVALID_AUX_ID;
pub const AK_INVALID_FILE_ID = c.WWISEC_AK_INVALID_FILE_ID;
pub const AK_INVALID_DEVICE_ID = c.WWISEC_AK_INVALID_DEVICE_ID;
pub const AK_INVALID_BANK_ID = c.WWISEC_AK_INVALID_BANK_ID;
pub const AK_FALLBACK_ARGUMENTVALUE_ID = c.WWISEC_AK_FALLBACK_ARGUMENTVALUE_ID;
pub const AK_INVALID_CHANNELMASK = c.WWISEC_AK_INVALID_CHANNELMASK;
pub const AK_INVALID_OUTPUT_DEVICE_ID = c.WWISEC_AK_INVALID_OUTPUT_DEVICE_ID;
pub const AK_INVALID_PIPELINE_ID = c.WWISEC_AK_INVALID_PIPELINE_ID;
pub const AK_INVALID_AUDIO_OBJECT_ID = c.WWISEC_AK_INVALID_AUDIO_OBJECT_ID;
pub const AK_DEFAULT_PRIORITY = c.WWISEC_AK_DEFAULT_PRIORITY;
pub const AK_MIN_PRIORITY = c.WWISEC_AK_MIN_PRIORITY;
pub const AK_MAX_PRIORITY = c.WWISEC_AK_MAX_PRIORITY;
pub const AK_DEFAULT_BANK_IO_PRIORITY = c.WWISEC_AK_DEFAULT_BANK_IO_PRIORITY;
pub const AK_DEFAULT_BANK_THROUGHPUT = c.WWISEC_AK_DEFAULT_BANK_THROUGHPUT;
pub const AK_SOUNDBANK_VERSION = c.WWISEC_AK_SOUNDBANK_VERSION;
pub const AkJobType_Generic = c.WWISEC_AkJobType_Generic;
pub const AkJobType_AudioProcessing = c.WWISEC_AkJobType_AudioProcessing;
pub const AkJobType_SpatialAudio = c.WWISEC_AkJobType_SpatialAudio;
pub const AK_NUM_JOB_TYPES = c.WWISEC_AK_NUM_JOB_TYPES;

pub const AkPanningRule = enum(u8) {
    speakers = c.WWISEC_AkPanningRule_Speakers,
    headphones = c.WWISEC_AkPanningRule_Headphones,
};

pub const WwiseError = error{
    NotImplemented,
    Fail,
    PartialSuccess,
    NotCompatible,
    AlreadyConnected,
    InvalidFile,
    AudioFileHeaderTooLarge,
    MaxReached,
    InvalidID,
    IDNotFound,
    InvalidInstanceID,
    NoMoreData,
    InvalidStateGroup,
    ChildAlreadyHasAParent,
    InvalidLanguage,
    CannotAddItseflAsAChild,
    InvalidParameter,
    ElementAlreadyInList,
    PathNotFound,
    PathNoVertices,
    PathNotRunning,
    PathNotPaused,
    PathNodeAlreadyInList,
    PathNodeNotInList,
    DataNeeded,
    NoDataNeeded,
    DataReady,
    NoDataReady,
    InsufficientMemory,
    Cancelled,
    UnknownBankID,
    BankReadError,
    InvalidSwitchType,
    FormatNotReady,
    WrongBankVersion,
    FileNotFound,
    DeviceNotReady,
    BankAlreadyLoaded,
    RenderedFX,
    ProcessNeeded,
    ProcessDone,
    MemManagerNotInitialized,
    StreamMgrNotInitialized,
    SSEInstructionsNotSupported,
    Busy,
    UnsupportedChannelConfig,
    PluginMediaNotAvailable,
    MustBeVirtualized,
    CommandTooLarge,
    RejectedByFilter,
    InvalidCustomPlatformName,
    DLLCannotLoad,
    DLLPathNotFound,
    NoJavaVM,
    OpenSLError,
    PluginNotRegistered,
    DataAlignmentError,
    DeviceNotCompatible,
    DuplicateUniqueID,
    InitBankNotLoaded,
    DeviceNotFound,
    PlayingIDNotFound,
    InvalidFloatValue,
    FileFormatMismatch,
    NoDistinctListener,
    ACP_Error,
    ResourceInUse,
    InvalidBankType,
    AlreadyInitialized,
    NotInitialized,
    FilePermissionError,
    UnknownFileError,
};

pub inline fn handleAkResult(result: c.WWISEC_AKRESULT) WwiseError!void {
    return switch (result) {
        c.WWISEC_AK_NotImplemented => return WwiseError.NotImplemented,
        c.WWISEC_AK_Success => return,
        c.WWISEC_AK_Fail => return WwiseError.Fail,
        c.WWISEC_AK_PartialSuccess => return WwiseError.PartialSuccess,
        c.WWISEC_AK_NotCompatible => return WwiseError.NotCompatible,
        c.WWISEC_AK_AlreadyConnected => return WwiseError.AlreadyConnected,
        c.WWISEC_AK_InvalidFile => return WwiseError.InvalidFile,
        c.WWISEC_AK_AudioFileHeaderTooLarge => return WwiseError.AudioFileHeaderTooLarge,
        c.WWISEC_AK_MaxReached => return WwiseError.MaxReached,
        c.WWISEC_AK_InvalidID => return WwiseError.InvalidID,
        c.WWISEC_AK_IDNotFound => return WwiseError.IDNotFound,
        c.WWISEC_AK_InvalidInstanceID => return WwiseError.InvalidInstanceID,
        c.WWISEC_AK_NoMoreData => return WwiseError.NoMoreData,
        c.WWISEC_AK_InvalidStateGroup => return WwiseError.InvalidStateGroup,
        c.WWISEC_AK_ChildAlreadyHasAParent => return WwiseError.ChildAlreadyHasAParent,
        c.WWISEC_AK_InvalidLanguage => return WwiseError.InvalidLanguage,
        c.WWISEC_AK_CannotAddItseflAsAChild => return WwiseError.CannotAddItseflAsAChild,
        c.WWISEC_AK_InvalidParameter => return WwiseError.InvalidParameter,
        c.WWISEC_AK_ElementAlreadyInList => return WwiseError.ElementAlreadyInList,
        c.WWISEC_AK_PathNotFound => return WwiseError.PathNotFound,
        c.WWISEC_AK_PathNoVertices => return WwiseError.PathNoVertices,
        c.WWISEC_AK_PathNotRunning => return WwiseError.PathNotRunning,
        c.WWISEC_AK_PathNotPaused => return WwiseError.PathNotPaused,
        c.WWISEC_AK_PathNodeAlreadyInList => return WwiseError.PathNodeAlreadyInList,
        c.WWISEC_AK_PathNodeNotInList => return WwiseError.PathNodeNotInList,
        c.WWISEC_AK_DataNeeded => return WwiseError.DataNeeded,
        c.WWISEC_AK_NoDataNeeded => return WwiseError.NoDataNeeded,
        c.WWISEC_AK_DataReady => return WwiseError.DataReady,
        c.WWISEC_AK_NoDataReady => return WwiseError.NoDataReady,
        c.WWISEC_AK_InsufficientMemory => return WwiseError.InsufficientMemory,
        c.WWISEC_AK_Cancelled => return WwiseError.Cancelled,
        c.WWISEC_AK_UnknownBankID => return WwiseError.UnknownBankID,
        c.WWISEC_AK_BankReadError => return WwiseError.BankReadError,
        c.WWISEC_AK_InvalidSwitchType => return WwiseError.InvalidSwitchType,
        c.WWISEC_AK_FormatNotReady => return WwiseError.FormatNotReady,
        c.WWISEC_AK_WrongBankVersion => return WwiseError.WrongBankVersion,
        c.WWISEC_AK_FileNotFound => return WwiseError.FileNotFound,
        c.WWISEC_AK_DeviceNotReady => return WwiseError.DeviceNotReady,
        c.WWISEC_AK_BankAlreadyLoaded => return WwiseError.BankAlreadyLoaded,
        c.WWISEC_AK_RenderedFX => return WwiseError.RenderedFX,
        c.WWISEC_AK_ProcessNeeded => return WwiseError.ProcessNeeded,
        c.WWISEC_AK_ProcessDone => return WwiseError.ProcessDone,
        c.WWISEC_AK_MemManagerNotInitialized => return WwiseError.MemManagerNotInitialized,
        c.WWISEC_AK_StreamMgrNotInitialized => return WwiseError.StreamMgrNotInitialized,
        c.WWISEC_AK_SSEInstructionsNotSupported => return WwiseError.SSEInstructionsNotSupported,
        c.WWISEC_AK_Busy => return WwiseError.Busy,
        c.WWISEC_AK_UnsupportedChannelConfig => return WwiseError.UnsupportedChannelConfig,
        c.WWISEC_AK_PluginMediaNotAvailable => return WwiseError.PluginMediaNotAvailable,
        c.WWISEC_AK_MustBeVirtualized => return WwiseError.MustBeVirtualized,
        c.WWISEC_AK_CommandTooLarge => return WwiseError.CommandTooLarge,
        c.WWISEC_AK_RejectedByFilter => return WwiseError.RejectedByFilter,
        c.WWISEC_AK_InvalidCustomPlatformName => return WwiseError.InvalidCustomPlatformName,
        c.WWISEC_AK_DLLCannotLoad => return WwiseError.DLLCannotLoad,
        c.WWISEC_AK_DLLPathNotFound => return WwiseError.DLLPathNotFound,
        c.WWISEC_AK_NoJavaVM => return WwiseError.NoJavaVM,
        c.WWISEC_AK_OpenSLError => return WwiseError.OpenSLError,
        c.WWISEC_AK_PluginNotRegistered => return WwiseError.PluginNotRegistered,
        c.WWISEC_AK_DataAlignmentError => return WwiseError.DataAlignmentError,
        c.WWISEC_AK_DeviceNotCompatible => return WwiseError.DeviceNotCompatible,
        c.WWISEC_AK_DuplicateUniqueID => return WwiseError.DuplicateUniqueID,
        c.WWISEC_AK_InitBankNotLoaded => return WwiseError.InitBankNotLoaded,
        c.WWISEC_AK_DeviceNotFound => return WwiseError.DeviceNotFound,
        c.WWISEC_AK_PlayingIDNotFound => return WwiseError.PlayingIDNotFound,
        c.WWISEC_AK_InvalidFloatValue => return WwiseError.InvalidFloatValue,
        c.WWISEC_AK_FileFormatMismatch => return WwiseError.FileFormatMismatch,
        c.WWISEC_AK_NoDistinctListener => return WwiseError.NoDistinctListener,
        c.WWISEC_AK_ACP_Error => return WwiseError.ACP_Error,
        c.WWISEC_AK_ResourceInUse => return WwiseError.ResourceInUse,
        c.WWISEC_AK_InvalidBankType => return WwiseError.InvalidBankType,
        c.WWISEC_AK_AlreadyInitialized => return WwiseError.AlreadyInitialized,
        c.WWISEC_AK_NotInitialized => return WwiseError.NotInitialized,
        c.WWISEC_AK_FilePermissionError => return WwiseError.FilePermissionError,
        c.WWISEC_AK_UnknownFileError => return WwiseError.UnknownFileError,
        else => return WwiseError.NotImplemented,
    };
}

pub const fromOSChar = blk: {
    if (builtin.os.tag == .windows) {
        break :blk fromOSCharUtf16;
    } else {
        break :blk fromCString;
    }
};

pub const toOSChar = blk: {
    if (builtin.os.tag == .windows) {
        break :blk toOSCharUtf16;
    } else {
        break :blk toCString;
    }
};

pub fn fromOSCharUtf16(allocator: std.mem.Allocator, value_opt: ?[*:0]const u16) ![]u8 {
    if (value_opt) |value| {
        return std.unicode.utf16leToUtf8Alloc(allocator, value[0..std.mem.len(value)]);
    }

    return "";
}

pub fn toOSCharUtf16(allocator: std.mem.Allocator, value: []const u8) ![:0]u16 {
    return std.unicode.utf8ToUtf16LeWithNull(allocator, value);
}

pub fn fromCString(allocator: std.mem.Allocator, value_opt: ?[*:0]const u8) ![]u8 {
    if (value_opt) |value| {
        return allocator.dupe(u8, value[0..std.mem.len(value)]);
    }

    return "";
}

pub fn toCString(allocator: std.mem.Allocator, value: []const u8) ![:0]u8 {
    return std.cstr.addNullByte(allocator, value);
}

pub fn stackCharAllocator(fallback_allocator: std.mem.Allocator) std.heap.StackFallbackAllocator(wwise_options.string_stack_size) {
    return std.heap.stackFallback(wwise_options.string_stack_size, fallback_allocator);
}

pub fn VirtualDestructor(comptime T: type) type {
    return switch (builtin.abi) {
        .msvc => extern struct {
            destructor: ?*const fn (self: *T) callconv(.C) void = null,

            pub fn call(self: @This(), instance: *T) void {
                if (self.destructor) |dtor| {
                    dtor(instance);
                }
            }
        },
        else => extern struct {
            destructor: ?*const fn (iself: *T) callconv(.C) void = null,
            destructor_with_delete: ?*const fn (iself: *T) callconv(.C) void = null,

            pub fn call(self: @This(), instance: *T) void {
                if (self.destructor) |dtor| {
                    dtor(instance);
                }
            }
        },
    };
}

pub fn CastMethods(comptime T: type) type {
    return extern struct {
        pub inline fn cast(instance: ?*anyopaque) *T {
            return @ptrCast(*T, @alignCast(@alignOf(*T), instance));
        }

        pub inline fn constCast(instance: ?*const anyopaque) *const T {
            return @ptrCast(*const T, @alignCast(@alignOf(*const T), instance));
        }
    };
}

pub const DefaultEnumType = switch (builtin.abi) {
    .msvc => i32,
    else => u32,
};
