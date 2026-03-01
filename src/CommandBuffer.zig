const c = @import("wwise_c");
const command_types = @import("command_types.zig");
const std = @import("std");
const zig = @import("zig.zig");

pub fn cmdSize(in_cmd_id: command_types.AkCommand) usize {
    return c.AK_CommandBuffer_CmdSize(@intFromEnum(in_cmd_id));
}

pub fn cmdSizeType(comptime CommandType: type) usize {
    if (!@hasDecl(CommandType, "COMMAND_TYPE")) {
        @compileError("Please add a valid COMMAND_TYPE to the struct");
    }

    return cmdSize(CommandType.COMMAND_TYPE);
}
