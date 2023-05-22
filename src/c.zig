const wwise_options = @import("wwise_options");

pub usingnamespace @cImport({
    if (wwise_options.include_default_io_hook_blocking) {
        @cDefine("WWISEC_INCLUDE_DEFAULT_IO_HOOK_BLOCKING", "");
    }
    if (wwise_options.include_default_io_hook_deferred) {
        @cDefine("WWISEC_INCLUDE_DEFAULT_IO_HOOK_DEFERRED", "");
    }
    if (wwise_options.include_file_package_io_blocking) {
        @cDefine("WWISEC_INCLUDE_FILE_PACKAGE_IO_BLOCKING", "");
    }
    if (wwise_options.include_file_package_io_deferred) {
        @cDefine("WWISEC_INCLUDE_FILE_PACKAGE_IO_DEFERRED", "");
    }

    @cInclude("WwiseC.h");
});
