const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");
const settings = @import("settings.zig");

pub const InitSettings = extern struct {
    execution_time_usec: u32 = 0,
    num_worker_threads: u32 = 2,
    thread_worker_properties: ?[*]settings.AkThreadProperties = null,

    pub fn fromC(value: c.WWISEC_AK_JobWorkerMgr_InitSettings) InitSettings {
        return @bitCast(value);
    }

    pub fn toC(self: InitSettings) c.WWISEC_AK_JobWorkerMgr_InitSettings {
        return @bitCast(self);
    }

    pub fn getJobMgrSettigns(self: *InitSettings) settings.AkJobMgrSettings {
        var raw_job_mgr_settings: c.WWISEC_AkJobMgrSettings = undefined;
        c.WWISEC_AK_JobWorkerMgr_InitSettings_GetJobMgrSettings(@ptrCast(self), &raw_job_mgr_settings);
        return settings.AkJobMgrSettings.fromC(raw_job_mgr_settings);
    }
};

pub fn getDefaultInitSettings(out_init_settings: *InitSettings) void {
    return c.WWISEC_AK_JobWorkerMgr_GetDefaultInitSettings(@ptrCast(out_init_settings));
}

pub fn isInnitialized() bool {
    return c.WWISEC_AK_JobWorkerMgr_IsInitialized();
}

pub fn initWorkers(in_impl_init_settings: *const InitSettings) common.WwiseError!void {
    return common.handleAkResult(
        c.WWISEC_AK_JobWorkerMgr_InitWorkers(@ptrCast(in_impl_init_settings)),
    );
}

pub fn termWorkers() void {
    c.WWISEC_AK_JobWorkerMgr_TermWorkers();
}
