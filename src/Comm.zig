const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");

pub const AK_COMM_DEFAULT_DISCOVERY_PORT = c.WWISEC_AK_COMM_DEFAULT_DISCOVERY_PORT;

const AK_COMM_SETTINGS_MAX_STRING_SIZE = c.WWISEC_AK_COMM_SETTINGS_MAX_STRING_SIZE;
const AK_COMM_SETTINGS_MAX_URL_SIZE = c.WWISEC_AK_COMM_SETTINGS_MAX_URL_SIZE;

pub const AkCommSettings = extern struct {
    ports: Ports = .{},
    comm_system: AkCommSystem = .socket,
    init_system_lib: bool = false,
    app_network_name: [AK_COMM_SETTINGS_MAX_STRING_SIZE]u8 = [_]u8{0} ** AK_COMM_SETTINGS_MAX_STRING_SIZE,
    comm_proxy_server_url: [AK_COMM_SETTINGS_MAX_URL_SIZE]u8 = [_]u8{0} ** AK_COMM_SETTINGS_MAX_URL_SIZE,

    pub const AkCommSystem = enum(common.DefaultEnumType) {
        socket,
        htcs,
    };

    pub const Ports = extern struct {
        discovery_broadcast: u16 = AK_COMM_DEFAULT_DISCOVERY_PORT,
        command: u16 = AK_COMM_DEFAULT_DISCOVERY_PORT + 1,

        pub fn fromC(value: c.WWISEC_AkCommSettings_Ports) Ports {
            return @bitCast(Ports, value);
        }

        pub fn toC(self: Ports) c.WWISEC_AkCommSettings_Ports {
            return @bitCast(c.WWISEC_AkCommSettings_Ports, self);
        }
    };

    pub fn setAppNetworkName(self: *AkCommSettings, app_network_name: []const u8) void {
        @memset(self.app_network_name[0..], 0);
        std.mem.copyForwards(u8, self.app_network_name[0..], app_network_name);
    }

    pub fn setCommProxyServelURL(self: *AkCommSettings, comm_proxy_server_url: []const u8) void {
        @memset(self.comm_proxy_server_url[0..], 0);
        std.mem.copyForwards(u8, self.app_network_name[0..], comm_proxy_server_url);
    }

    pub inline fn fromC(value: c.WWISEC_AkCommSettings) AkCommSettings {
        return @bitCast(AkCommSettings, value);
    }

    pub inline fn toC(self: AkCommSettings) c.WWISEC_AkCommSettings {
        return @bitCast(c.WWWISEC_AkCommSettings, self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkCommSettings) == @sizeOf(c.WWISEC_AkCommSettings));
        std.debug.assert(@offsetOf(AkCommSettings, "init_system_lib") == @offsetOf(c.WWISEC_AkCommSettings, "bInitSystemLib"));
    }
};

pub fn init(in_settings: *const AkCommSettings) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_Comm_Init(@ptrCast(*const c.WWISEC_AkCommSettings, in_settings)),
    );
}

pub fn getDefaultInitSettings(out_settings: *AkCommSettings) !void {
    c.WWISEC_AK_Comm_GetDefaultInitSettings(@ptrCast(*c.WWISEC_AkCommSettings, out_settings));
}

pub fn term() void {
    c.WWISEC_AK_Comm_Term();
}

pub fn reset() common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_Comm_Reset(),
    );
}

pub fn getCurrentSettings() *const AkCommSettings {
    return @ptrCast(*const AkCommSettings, c.WWISEC_AK_Comm_GetCurrentSettings());
}
