const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");

pub const AK_COMM_DEFAULT_DISCOVERY_PORT = c.WWISEC_AK_COMM_DEFAULT_DISCOVERY_PORT;

const AK_COMM_SETTINGS_MAX_STRING_SIZE = c.WWISEC_AK_COMM_SETTINGS_MAX_STRING_SIZE;
const AK_COMM_SETTINGS_MAX_URL_SIZE = c.WWISEC_AK_COMM_SETTINGS_MAX_URL_SIZE;

pub const AkCommSettings = struct {
    ports: Ports = .{},
    comm_system: AkCommSystem = .socket,
    init_system_lib: bool = false,
    app_network_name: [AK_COMM_SETTINGS_MAX_STRING_SIZE]u8 = [_]u8{0} ** AK_COMM_SETTINGS_MAX_STRING_SIZE,
    comm_proxy_server_url: [AK_COMM_SETTINGS_MAX_URL_SIZE]u8 = [_]u8{0} ** AK_COMM_SETTINGS_MAX_URL_SIZE,

    pub const AkCommSystem = enum(common.DefaultEnumType) {
        socket,
        htcs,
    };

    pub const Ports = struct {
        discovery_broadcast: u16 = AK_COMM_DEFAULT_DISCOVERY_PORT,
        command: u16 = AK_COMM_DEFAULT_DISCOVERY_PORT + 1,

        pub fn fromC(value: c.WWISEC_AkCommSettings_Ports) Ports {
            return .{
                .discovery_broadcast = value.uDiscoveryBroadcast,
                .command = value.uCommand,
            };
        }

        pub fn toC(self: Ports) c.WWISEC_AkCommSettings_Ports {
            return .{
                .uDiscoveryBroadcast = self.discovery_broadcast,
                .uCommand = self.command,
            };
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

    pub fn fromC(value: c.WWISEC_AkCommSettings) AkCommSettings {
        var result: AkCommSettings = .{};
        result.ports = Ports.fromC(value.ports);
        result.comm_system = @intToEnum(AkCommSystem, value.commSystem);
        result.init_system_lib = value.bInitSystemLib;

        @memcpy(result.app_network_name[0..], value.szAppNetworkName[0..]);
        @memcpy(result.comm_proxy_server_url[0..], value.szCommProxyServerUrl[0..]);
        return result;
    }

    pub fn toC(self: AkCommSettings) c.WWISEC_AkCommSettings {
        var result = std.mem.zeroes(c.WWISEC_AkCommSettings);

        result.ports = self.ports.toC();
        result.commSystem = @enumToInt(self.comm_system);
        result.bInitSystemLib = self.init_system_lib;

        @memcpy(result.szAppNetworkName[0..], self.app_network_name[0..]);
        @memcpy(result.szCommProxyServerUrl[0..], self.comm_proxy_server_url[0..]);

        return result;
    }
};

pub fn init(in_settings: AkCommSettings) common.WwiseError!void {
    var raw_settings = in_settings.toC();

    return common.handleAkResult(
        c.WWISEC_AK_Comm_Init(&raw_settings),
    );
}

pub fn getDefaultInitSettings(out_settings: *AkCommSettings) !void {
    var raw_settings: c.WWISEC_AkCommSettings = std.mem.zeroes(c.WWISEC_AkCommSettings);
    c.WWISEC_AK_Comm_GetDefaultInitSettings(&raw_settings);
    out_settings.* = AkCommSettings.fromC(raw_settings);
}

pub fn term() void {
    c.WWISEC_AK_Comm_Term();
}

pub fn reset() common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_Comm_Reset(),
    );
}

pub fn getCurrentSettings() AkCommSettings {
    var raw_settings = c.WWISEC_AK_Comm_GetCurrentSettings();
    return AkCommSettings.fromC(raw_settings);
}
