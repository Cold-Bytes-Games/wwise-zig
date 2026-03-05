const c = @import("wwise_c");
const command_types = @import("command_types.zig");
const sound_engine_types = @import("sound_engine_types.zig");
const SpatialAudio = if (wwise_options.use_spatial_audio) @import("SpatialAudio.zig") else void;
const std = @import("std");
const wwise_options = @import("wwise_options");
const zig = @import("zig.zig");

header: *command_types.AkCommandBufferHeader = undefined,

const CommandBuffer = @This();

const ErrorSet = error{
    CommandBufferCreateFailed,
    CommandBufferInitFailed,
    CommandBufferFull,
    OutOfMemory,
};

pub fn cmdSize(in_cmd_id: command_types.AkCommand) usize {
    return c.AK_CommandBuffer_CmdSize(@intFromEnum(in_cmd_id));
}

pub fn cmdSizeType(comptime CommandType: type) usize {
    if (!@hasDecl(CommandType, "COMMAND_TYPE")) {
        @compileError("Please add a valid COMMAND_TYPE to the struct");
    }

    return cmdSize(CommandType.COMMAND_TYPE);
}

pub fn minSize() usize {
    return c.AK_CommandBuffer_MinSize();
}

pub fn create(in_size: usize) ErrorSet!CommandBuffer {
    const result = c.AK_CommandBuffer_Create(in_size);
    if (result == null) {
        return ErrorSet.CommandBufferCreateFailed;
    }

    return .{
        .header = command_types.AkCommandBufferHeader.fromC(result.?),
    };
}

pub fn init(out_buffer: []u8, in_size: usize) ErrorSet!CommandBuffer {
    const result = c.AK_CommandBuffer_Init(@ptrCast(out_buffer), in_size);
    if (result == null) {
        return ErrorSet.CommandBufferInitFailed;
    }

    return .{
        .header = command_types.AkCommandBufferHeader.fromC(result.?),
    };
}

pub fn reset(self: *CommandBuffer, in_size: usize) ErrorSet!void {
    const result = c.AK_CommandBuffer_Init(@ptrCast(self.header), in_size);
    if (result == null) {
        return ErrorSet.CommandBufferInitFailed;
    }

    self.header = command_types.AkCommandBufferHeader.fromC(result.?);
}

pub fn destroy(self: CommandBuffer) void {
    c.AK_CommandBuffer_Destroy(self.header.toC());
}

pub fn addRaw(self: CommandBuffer, in_cmd_id: command_types.AkCommand) ?*align(4) anyopaque {
    return @alignCast(c.AK_CommandBuffer_Add(self.header.toC(), @intFromEnum(in_cmd_id)));
}

pub fn add(self: CommandBuffer, comptime T: type) ErrorSet!*align(4) T {
    const result = c.AK_CommandBuffer_Add(self.header.toC(), @intFromEnum(T.COMMAND_TYPE));
    if (result == null) {
        return ErrorSet.CommandBufferFull;
    }

    return @ptrCast(@alignCast(result));
}

pub fn stringSize(str: [*:0]const u8) usize {
    return c.AK_CommandBuffer_StringSize(str);
}

pub fn addString(self: CommandBuffer, fallback_allocator: std.mem.Allocator, str: []const u8) ErrorSet![*:0]u8 {
    var stack_char_allocator = zig.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_name = try zig.toCString(allocator, str);
    defer allocator.free(raw_name);

    const result = c.AK_CommandBuffer_AddString(self.header.toC(), raw_name);
    if (result == null) {
        return ErrorSet.CommandBufferFull;
    }

    return @ptrCast(result);
}

pub fn addStringZ(self: CommandBuffer, str: [:0]const u8) ![*:0]u8 {
    const result = c.AK_CommandBuffer_AddString(self.header.toC(), str);
    if (result == null) {
        return ErrorSet.CommandBufferFull;
    }

    return @ptrCast(result);
}

pub fn arraySize(item_size: usize, num_items: u16) usize {
    return c.AK_CommandBuffer_ArraySize(item_size, num_items);
}

pub fn addArrayRaw(self: *CommandBuffer, item_size: usize, num_items: u16, items: []const u8) ?[*]u8 {
    return @ptrCast(c.AK_CommandBuffer_AddArray(self.header.toC(), item_size, num_items, @ptrCast(items)));
}

pub fn addArray(self: *CommandBuffer, comptime T: type, items: []const T) ?[*]T {
    return @ptrCast(self.addArrayRaw(
        @sizeOf(T),
        @truncate(items.lens),
        std.mem.sliceAsBytes(items),
    ));
}

pub fn externalSourcesSize(external_sources: []const sound_engine_types.AkExternalSourceInfo) usize {
    return c.AK_CommandBuffer_ExternalSourcesSize(@truncate(external_sources.len), @ptrCast(external_sources));
}

pub fn addExternalSources(self: CommandBuffer, external_sources: []const sound_engine_types.AkExternalSourceInfo) ?[*]sound_engine_types.AkExternalSourceInfo {
    return @ptrCast(@alignCast(c.AK_CommandBuffer_AddExternalSources(
        self.header.toC(),
        @truncate(external_sources.len),
        @ptrCast(external_sources),
    )));
}

pub const geometrySize = blk: {
    if (wwise_options.use_spatial_audio) {
        break :blk struct {
            pub fn geometrySize(in_geometry_params: *const SpatialAudio.AkGeometryParams) usize {
                return c.AK_CommandBuffer_GeometrySize(@ptrCast(@alignCast(in_geometry_params)));
            }
        }.geometrySize;
    } else {
        break :blk void;
    }
};

pub const addGeometry = blk: {
    if (wwise_options.use_spatial_audio) {
        break :blk struct {
            pub fn addGeometry(self: *CommandBuffer, in_geometry_params: *const SpatialAudio.AkGeometryParams) ?*SpatialAudio.AkGeometryParams {
                return @ptrCast(@alignCast(
                    c.AK_CommandBuffer_AddGeometry(self.header.toC(), @ptrCast(@alignCast(in_geometry_params))),
                ));
            }
        }.addGeometry;
    } else {
        break :blk void;
    }
};

pub fn remove(self: CommandBuffer) void {
    c.AK_CommandBuffer_Remove(self.header.toC());
}

pub fn submit(self: CommandBuffer) void {
    c.AK_CommandBuffer_Submit(self.header.toC());
}

pub fn submitNonBlocking(self: CommandBuffer) zig.WwiseError!void {
    return zig.handleAkResult(
        @intCast(c.AK_CommandBuffer_SubmitNonBlocking(self.header.toC())),
    );
}

pub fn begin(self: CommandBuffer) command_types.AkCommandBufferIterator {
    var it: command_types.AkCommandBufferIterator = undefined;
    c.AK_CommandBuffer_Begin(self.header.toC(), @ptrCast(&it));
    return it;
}
