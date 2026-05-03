#include <memory>

#include "crop_filter_cmd_args_maker.h"
#include "../filters/crop_filter.h"

std::unique_ptr<BaseFilter> CreateCropFilterFromCmdArgs(const FilterDescriptor* fd, std::string* error_msg) {
    if (!fd) {
        if (error_msg) {
            *error_msg = "Filter descriptor is null.";
        }
        return nullptr;
    }
    if (fd->filter_name != "crop") {
        if (error_msg) {
            *error_msg = "Expected filter name 'crop', got '" + fd->filter_name + "'.";
        }
        return nullptr;
    }
    if (fd->GetFilterParamsCount() != 2) {
        if (error_msg) {
            *error_msg = "Crop filter requires exactly 2 parameters (width, height), got " +
                         std::to_string(fd->GetFilterParamsCount()) + ".";
        }
        return nullptr;
    }

    int width = 0;
    int height = 0;
    try {
        width = std::stoi(fd->filter_params[0]);
        height = std::stoi(fd->filter_params[1]);
    } catch (const std::exception&) {
        if (error_msg) {
            *error_msg = "Invalid width or height: '" + fd->filter_params[0] + "' or '" + fd->filter_params[1] +
                         "' is not a valid integer.";
        }
        return nullptr;
    }

    if (width <= 0 || height <= 0) {
        if (error_msg) {
            *error_msg = "Width and height must be positive, got width=" + std::to_string(width) +
                         ", height=" + std::to_string(height) + ".";
        }
        return nullptr;
    }
    return std::make_unique<CropFilter>(width, height);
}
