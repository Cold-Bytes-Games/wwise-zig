const wwise_options = @import("wwise_options");

pub const AkMemSettings = MemoryMgr.AkMemSettings;
pub const Comm = if (wwise_options.use_communication) @import("Comm.zig") else void;
pub const IOHooks = @import("IOHooks.zig");
pub const MemoryMgr = @import("MemoryMgr.zig");
pub const MusicEngine = @import("MusicEngine.zig");
pub const SoundEngine = @import("SoundEngine.zig");
pub const SpeakerVolumes = @import("SpeakerVolumes.zig");
pub const StreamMgr = @import("StreamMgr.zig");
pub usingnamespace @import("common_defs.zig");
pub usingnamespace @import("callback.zig");
pub usingnamespace @import("common.zig");
pub usingnamespace @import("IAkPlugin.zig");
pub usingnamespace @import("IAkStreamMgr.zig");
pub usingnamespace @import("midi_types.zig");
pub usingnamespace @import("settings.zig");
pub usingnamespace @import("speaker_config.zig");
