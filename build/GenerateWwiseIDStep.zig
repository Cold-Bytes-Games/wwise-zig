const std = @import("std");
const Step = std.Build.Step;

const GenerateWwiseIDStep = @This();

step: Step,
output_file: std.Build.GeneratedFile,
id_file_path: []const u8,

pub const base_id: Step.Id = .custom;

pub const Options = struct {
    id_file_path: []const u8,
};

pub fn create(owner: *std.Build, options: Options) *GenerateWwiseIDStep {
    const self = owner.allocator.create(GenerateWwiseIDStep) catch @panic("OOM");

    self.* = .{
        .step = Step.init(.{
            .id = base_id,
            .name = "Generate Wwise ID Zig module",
            .owner = owner,
            .makeFn = make,
            .first_ret_addr = @returnAddress(),
        }),
        .id_file_path = options.id_file_path,
        .output_file = .{ .step = &self.step },
    };

    return self;
}

const NamespaceKeyword = "namespace";
const AkUniqueIDKeyword = "AkUniqueID";
const SpaceCount = 4;

pub fn writeIndent(writer: anytype, indent_factor: usize) !void {
    const spaces_to_insert = indent_factor * SpaceCount;
    try writer.writeByteNTimes(' ', spaces_to_insert);
}

fn make(step: *Step, prog_node: *std.Progress.Node) !void {
    _ = prog_node;
    const b = step.owner;
    const self = @fieldParentPtr(GenerateWwiseIDStep, "step", step);
    const gpa = b.allocator;
    const arena = b.allocator;

    var manifest = b.graph.cache.obtain();
    defer manifest.deinit();

    // Random bytes to make GenerateWwiseIDStep unique. Refresh this with new
    // random bytes when GenerateWwiseIDStep implementation is modified in a
    // non-backwards-compatible way.
    manifest.hash.add(@as(u32, 0xc01db1e6));

    const full_input_file_path = try std.fs.path.resolve(gpa, &.{self.id_file_path});
    defer gpa.free(full_input_file_path);

    _ = try manifest.addFile(full_input_file_path, null);

    const output_file_name = "wwise-ids.zig";

    if (try step.cacheHit(&manifest)) {
        const digest = manifest.final();
        self.output_file.path = try b.cache_root.join(arena, &.{
            "o", &digest, output_file_name,
        });
        return;
    }

    const input_file = try std.fs.cwd().openFile(full_input_file_path, .{});
    defer input_file.close();

    var read_buffer = std.io.bufferedReaderSize(4096, input_file.reader());
    var reader = read_buffer.reader();

    var output = std.ArrayList(u8).init(gpa);
    defer output.deinit();

    var write_buffer = std.io.bufferedWriter(output.writer());
    var writer = write_buffer.writer();

    var indent_factor: usize = 0;

    try writer.writeAll("pub const AK = @import(\"wwise-zig\");\n");

    var last_wrote_entry = true;

    while (true) {
        const read_line = try reader.readUntilDelimiterOrEofAlloc(gpa, '\n', 8 * 1024);
        if (read_line) |line| {
            const end_brace_index_opt = std.mem.indexOf(u8, line, "}");
            if (end_brace_index_opt != null) {
                if (indent_factor > 0) {
                    indent_factor -= 1;

                    try writeIndent(writer, indent_factor);
                    try writer.writeAll("};\n");
                }
            }

            const namespace_index_opt = std.mem.indexOf(u8, line, NamespaceKeyword);
            if (namespace_index_opt) |namespace_index| {
                const comment_index_opt = std.mem.indexOf(u8, line, "//");
                if (comment_index_opt != null) {
                    continue;
                }

                var start_name_index = namespace_index + NamespaceKeyword.len + 1;
                while (start_name_index < line.len and (line[start_name_index] == ' ' or line[start_name_index] == '\t')) {
                    start_name_index += 1;
                }

                var end_name_index = start_name_index;
                while (end_name_index < line.len and line[end_name_index] != '\r' and line[end_name_index] != '\n') {
                    end_name_index += 1;
                }

                const name = line[start_name_index..end_name_index];
                if (std.mem.eql(u8, name, "AK")) {
                    continue;
                }

                if (last_wrote_entry) {
                    try writer.writeAll("\n");
                }

                try writeIndent(writer, indent_factor);
                try writer.print("pub const {s} = struct {{\n", .{name});

                last_wrote_entry = false;
                indent_factor += 1;
            }

            const unique_id_index_opt = std.mem.indexOf(u8, line, AkUniqueIDKeyword);
            if (unique_id_index_opt) |unique_id_index| {
                var start_name_index = unique_id_index + AkUniqueIDKeyword.len + 1;
                while (start_name_index < line.len and (line[start_name_index] == ' ' or line[start_name_index] == '\t')) {
                    start_name_index += 1;
                }

                var end_name_index = start_name_index;
                while (end_name_index < line.len and line[end_name_index] != ' ') {
                    end_name_index += 1;
                }

                const name = line[start_name_index..end_name_index];

                var start_number_index = end_name_index;
                while (start_number_index < line.len and line[start_number_index] != '=') {
                    start_number_index += 1;
                }
                start_number_index += 1;
                while (start_number_index < line.len and (line[start_number_index] == ' ' or line[start_number_index] == '\t')) {
                    start_number_index += 1;
                }

                var end_number_index = start_number_index;
                while (end_number_index < line.len and line[end_number_index] != 'U') {
                    end_number_index += 1;
                }

                const number = line[start_number_index..end_number_index];
                try writeIndent(writer, indent_factor);
                try writer.print("pub const {s}: AK.AkUniqueID = {s};\n", .{ name, number });
                last_wrote_entry = true;
            }
        } else {
            break;
        }
    }

    try write_buffer.flush();

    const digest = manifest.final();

    const sub_path = try std.fs.path.join(arena, &.{ "o", &digest, output_file_name });
    const sub_path_dirname = std.fs.path.dirname(sub_path).?;

    b.cache_root.handle.makePath(sub_path_dirname) catch |err| {
        return step.fail("unable to make path '{}{s}': {s}", .{
            b.cache_root, sub_path_dirname, @errorName(err),
        });
    };

    b.cache_root.handle.writeFile(sub_path, output.items) catch |err| {
        return step.fail("unable to write file '{}{s}': {s}", .{
            b.cache_root, sub_path, @errorName(err),
        });
    };

    self.output_file.path = try b.cache_root.join(arena, &.{sub_path});
    try manifest.writeManifest();
}
