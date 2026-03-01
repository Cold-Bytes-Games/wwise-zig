const c = @import("wwise_c");
const command_types = @import("command_types.zig");
const sound_engine_types = @import("sound_engine_types.zig");
const SpatialAudio = if (wwise_options.use_spatial_audio) @import("SpatialAudio.zig") else void;
const std = @import("std");
const wwise_options = @import("wwise_options");
const zig = @import("zig.zig");

header: *command_types.AkCommandBufferHeader = undefined,

const CommandBuffer = @This();

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

pub fn create(in_size: usize) CommandBuffer {
    return .{
        .header = command_types.AkCommandBufferHeader.fromC(c.AK_CommandBuffer_Create(in_size)),
    };
}

pub fn init(out_buffer: []u8, in_size: usize) CommandBuffer {
    return .{
        .header = command_types.AkCommandBufferHeader.fromC(c.AK_CommandBuffer_Init(@ptrCast(out_buffer), in_size)),
    };
}

pub fn destroy(self: *CommandBuffer) void {
    c.AK_CommandBuffer_Destroy(self.header.toC());
}

pub fn addRaw(self: *CommandBuffer, in_cmd_id: command_types.AkCommand) ?*anyopaque {
    return c.AK_CommandBuffer_Add(self.header.toC(), @intFromEnum(in_cmd_id));
}

pub fn add(self: *CommandBuffer, comptime T: type) ?*T {
    return @ptrCast(c.AK_CommandBuffer_Add(self.header.toC(), @intFromEnum(T.COMMAND_TYPE)));
}

pub fn stringSize(str: [*:0]const u8) usize {
    return c.AK_CommandBuffer_StringSize(str);
}

pub fn addString(self: *CommandBuffer, fallback_allocator: std.mem.Allocator, str: []const u8) !?[*:0]u8 {
    var stack_char_allocator = zig.stackCharAllocator(fallback_allocator);
    var allocator = stack_char_allocator.get();

    const raw_name = try zig.toCString(allocator, str);
    defer allocator.free(raw_name);

    return @ptrCast(c.AK_CommandBuffer_AddString(self.header.toC(), raw_name));
}

pub fn addStringZ(self: *CommandBuffer, str: [:0]const u8) ?[*:0]u8 {
    return @ptrCast(c.AK_CommandBuffer_AddString(self.header.toC(), @ptrCast(str)));
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

pub fn addExternalSources(self: *CommandBuffer, external_sources: []const sound_engine_types.AkExternalSourceInfo) ?[*]sound_engine_types.AkExternalSourceInfo {
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

pub fn remove(self: *CommandBuffer) void {
    c.AK_CommandBuffer_Remove(self.header.toC());
}

pub fn submit(self: *CommandBuffer) void {
    c.AK_CommandBuffer_Submit(self.header.toC());
}

pub fn submitNonBlocking(self: *CommandBuffer) zig.WwiseError!void {
    return zig.handleAkResult(
        @intCast(c.AK_CommandBuffer_SubmitNonBlocking(self.header.toC())),
    );
}

pub fn begin(self: *CommandBuffer, out_iterator: *command_types.AkCommandBufferIterator) void {
    return c.AK_CommandBuffer_Begin(self.header.toC(), @ptrCast(out_iterator));
}

pub fn next(iterator: *command_types.AkCommandBufferIterator) c_int {
    return c.AK_CommandBuffer_Next(@ptrCast(iterator));
}
