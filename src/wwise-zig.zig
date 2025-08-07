const wwise_options = @import("wwise_options");

pub const AkMemSettings = MemoryMgr.AkMemSettings;
pub const Comm = if (wwise_options.use_communication) @import("Comm.zig") else void;
pub const IOHooks = @import("IOHooks.zig");
pub const JobWorkerMgr = if (wwise_options.use_default_job_worker) @import("JobWorkerMgr.zig") else void;
pub const MemoryMgr = @import("MemoryMgr.zig");
pub const Monitor = @import("Monitor.zig");
pub const MusicEngine = @import("MusicEngine.zig");
pub const SoundEngine = @import("SoundEngine.zig");
pub const SpatialAudio = if (wwise_options.use_spatial_audio) @import("SpatialAudio.zig") else void;
pub const SpeakerVolumes = @import("SpeakerVolumes.zig");
pub const StreamMgr = @import("StreamMgr.zig");
pub const TempAlloc = @import("TempAlloc.zig");

// callbacks.zig
const callbacks = @import("callbacks.zig");
pub const AkCallbackType = callbacks.AkCallbackType;
pub const AkCallbackInfo = callbacks.AkCallbackInfo;
pub const AkEventCallbackInfo = callbacks.AkEventCallbackInfo;
pub const AkMIDIEventCallbackInfo = callbacks.AkMIDIEventCallbackInfo;
pub const AkMarkerCallbackInfo = callbacks.AkMarkerCallbackInfo;
pub const AkDurationCallbackInfo = callbacks.AkDurationCallbackInfo;
pub const AkDynamicSequenceItemCallbackInfo = callbacks.AkDynamicSequenceItemCallbackInfo;
pub const AkSpeakerVolumeMatrixCallbackInfo = callbacks.AkSpeakerVolumeMatrixCallbackInfo;
pub const AkBusMeteringCallbackInfo = callbacks.AkBusMeteringCallbackInfo;
pub const AkOutputDeviceMeteringCallbackInfo = callbacks.AkOutputDeviceMeteringCallbackInfo;
pub const AkMusicPlaylistCallbackInfo = callbacks.AkMusicPlaylistCallbackInfo;
pub const AkSegmentInfo = callbacks.AkSegmentInfo;
pub const AkMusicSyncCallbackInfo = callbacks.AkMusicSyncCallbackInfo;
pub const AkResourceMonitorDataSummary = callbacks.AkResourceMonitorDataSummary;
pub const AkCallbackFunc = callbacks.AkCallbackFunc;
pub const AkBusCallbackFunc = callbacks.AkBusCallbackFunc;
pub const AkBusMeteringCallbackFunc = callbacks.AkBusMeteringCallbackFunc;
pub const AkOutputDeviceMeteringCallbackFunc = callbacks.AkOutputDeviceMeteringCallbackFunc;
pub const AkBankCallbackFunc = callbacks.AkBankCallbackFunc;
pub const AkGlobalCallbackLocation = callbacks.AkGlobalCallbackLocation;
pub const AkGlobalCallbackFunc = callbacks.AkGlobalCallbackFunc;
pub const AkResourceMonitorCallbackFunc = callbacks.AkResourceMonitorCallbackFunc;
pub const AkAudioDeviceEvent = callbacks.AkAudioDeviceEvent;
pub const AkDeviceStatusCallbackFunc = callbacks.AkDeviceStatusCallbackFunc;
pub const AkCaptureCallbackFunc = callbacks.AkCaptureCallbackFunc;

// common.zig
pub usingnamespace @import("common.zig");
pub usingnamespace @import("common_defs.zig");
pub usingnamespace @import("error_message_translator.zig");
pub usingnamespace @import("IAkPlugin.zig");
pub usingnamespace @import("IAkPluginMemAlloc.zig");
pub usingnamespace @import("IAkStreamMgr.zig");
pub usingnamespace @import("IBytes.zig");
pub usingnamespace @import("midi_types.zig");
pub usingnamespace @import("platform_context.zig");
pub usingnamespace @import("settings.zig");
pub usingnamespace @import("speaker_config.zig");
pub usingnamespace @import("virtual_acoustics.zig");
pub usingnamespace @import("wwise_platform.zig");

pub const reflect_game_data = if (wwise_options.use_spatial_audio) @import("reflect_game_data.zig") else struct {};
pub const Windows = if (wwise_options.platform == .windows) @import("win_sound_engine.zig") else struct {};

comptime {
    @setEvalBranchQuota(5000);
    @import("std").testing.refAllDeclsRecursive(@This());
}
