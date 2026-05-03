#include <memory>

#include "edge_detection_filter_cmd_args_maker.h"
#include "../filters/edge_detection_filter.h"

std::unique_ptr<BaseFilter> CreateEdgeDetectionFilterFromCmdArgs(const FilterDescriptor* fd, std::string* error_msg) {
    if (!fd) {
        if (error_msg) {
            *error_msg = "Filter descriptor is null.";
        }
        return nullptr;
    }
    if (fd->filter_name != "edge") {
        if (error_msg) {
            *error_msg = "Expected filter name 'edge', got '" + fd->filter_name + "'.";
        }
        return nullptr;
    }
    if (fd->GetFilterParamsCount() != 1) {
        if (error_msg) {
            *error_msg = "Edge Detection filter requires exactly 1 parameter (threshold), got " +
                         std::to_string(fd->GetFilterParamsCount()) + ".";
        }
        return nullptr;
    }

    double threshold = 0;
    try {
        threshold = std::stod(fd->filter_params[0]);
    } catch (const std::exception&) {
        if (error_msg) {
            *error_msg = "Invalid threshold: '" + fd->filter_params[0] + "' is not a valid number.";
        }
        return nullptr;
    }

    if (threshold < 0.0 || threshold > 1.0) {
        if (error_msg) {
            *error_msg = "Threshold must be between 0 and 1, got " + std::to_string(threshold) + ".";
        }
        return nullptr;
    }
    return std::make_unique<EdgeDetectionFilter>(threshold);
}
