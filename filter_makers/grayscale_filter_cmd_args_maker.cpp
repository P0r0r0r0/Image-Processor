#include <memory>

#include "grayscale_filter_cmd_args_maker.h"
#include "../filters/grayscale_filter.h"

std::unique_ptr<BaseFilter> CreateGrayscaleFilterFromCmdArgs(const FilterDescriptor* fd, std::string* error_msg) {
    if (!fd) {
        if (error_msg) {
            *error_msg = "Filter descriptor is null.";
        }
        return nullptr;
    }
    if (fd->filter_name != "gs") {
        if (error_msg) {
            *error_msg = "Expected filter name 'gs', got '" + fd->filter_name + "'.";
        }
        return nullptr;
    }
    if (fd->GetFilterParamsCount() != 0) {
        if (error_msg) {
            *error_msg =
                "Grayscale filter requires no parameters, got " + std::to_string(fd->GetFilterParamsCount()) + ".";
        }
        return nullptr;
    }
    return std::make_unique<GrayscaleFilter>();
}
