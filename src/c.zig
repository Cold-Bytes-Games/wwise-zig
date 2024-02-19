const wwise_options = @import("wwise_options");

pub usingnamespace @cImport({
    if (wwise_options.use_communication) {
        @cDefine("WWISEC_USE_COMMUNICATION", "");
    }
    if (wwise_options.use_default_job_worker) {
        @cDefine("WWISEC_USE_DEFAULT_JOB_WORKER", "");
    }
    if (wwise_options.use_spatial_audio) {
        @cDefine("WWISEC_USE_SPATIAL_AUDIO", "");
    }
    if (wwise_options.include_default_io_hook_deferred) {
        @cDefine("WWISEC_INCLUDE_DEFAULT_IO_HOOK_DEFERRED", "");
    }
    if (wwise_options.include_file_package_io_deferred) {
        @cDefine("WWISEC_INCLUDE_FILE_PACKAGE_IO_DEFERRED", "");
    }

    @cInclude("WwiseC.h");
});
