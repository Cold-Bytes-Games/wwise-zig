const std = @import("std");
const c = @import("wwise_c");
const common = @import("common.zig");
const typedefs = @import("typedefs.zig");

pub const AkCandidateCallbackFunc = ?*const fn (in_id_event: typedefs.AkUniqueID, in_id_candidate: typedefs.AkUniqueID, in_cookie: ?*anyopaque) callconv(.c) bool;

pub const ResolveDialogueEventOptionalArgs = struct {
    id_sequence: typedefs.AkPlayingID = common.AK_INVALID_PLAYING_ID,
    candidate_callback_func: AkCandidateCallbackFunc = null,
    cookie: ?*anyopaque = null,
};

pub fn resolveDialogueEventID(in_event_id: typedefs.AkUniqueID, in_argument_values: []const common.AkArgumentValueID, optional_args: ResolveDialogueEventOptionalArgs) typedefs.AkUniqueID {
    return c.WWISEC_AK_SoundEngine_DynamicDialogue_ResolveDialogueEvent_ID(
        in_event_id,
        @ptrCast(@constCast(in_argument_values)),
        @truncate(in_argument_values.len),
        optional_args.id_sequence,
        optional_args.candidate_callback_func,
        optional_args.cookie,
    );
}

pub fn resolveDialogueEventString(fallback_allocator: std.mem.Allocator, in_event_name: []const u8, in_argument_value_names: []const []const u8, optional_args: ResolveDialogueEventOptionalArgs) !typedefs.AkUniqueID {
    var stack_oschar_allocator = common.stackCharAllocator(fallback_allocator);
    const char_allocator = stack_oschar_allocator.get();

    var area_allocator = std.heap.ArenaAllocator.init(char_allocator);
    defer area_allocator.deinit();

    const allocator = area_allocator.allocator();

    const raw_event_name = try common.toCString(allocator, in_event_name);

    var raw_argument_value_list: std.ArrayList([*:0]const u8) = .empty;
    defer raw_argument_value_list.deinit(allocator);

    for (in_argument_value_names) |argument_value_name| {
        const raw_argument_value_name = try common.toCString(allocator, argument_value_name);
        try raw_argument_value_list.append(allocator, raw_argument_value_name);
    }

    return c.WWISEC_AK_SoundEngine_DynamicDialogue_ResolveDialogueEvent_String(
        raw_event_name,
        @ptrCast(raw_argument_value_list.items),
        @truncate(raw_argument_value_list.items.len),
        optional_args.id_sequence,
        optional_args.candidate_callback_func,
        optional_args.cookie,
    );
}

pub fn getDialogueEventCustomPropertyValue(in_event_id: typedefs.AkUniqueID, in_prop_id: u32) common.WwiseError!i32 {
    var out_value: i32 = 0;

    try common.handleAkResult(
        c.WWISEC_AK_SoundEngine_DynamicDialogue_GetDialogueEventCustomPropertyValue(in_event_id, in_prop_id, &out_value),
    );

    return out_value;
}
