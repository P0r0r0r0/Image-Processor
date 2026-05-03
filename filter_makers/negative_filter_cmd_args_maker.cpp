#include <memory>

#include "negative_filter_cmd_args_maker.h"
#include "../filters/negative_filter.h"

std::unique_ptr<BaseFilter> CreateNegativeFilterFromCmdArgs(const FilterDescriptor* fd, std::string* error_msg) {
    if (!fd) {
        if (error_msg) {
            *error_msg = "Filter descriptor is null.";
        }
        return nullptr;
    }
    if (fd->filter_name != "neg") {
        if (error_msg) {
            *error_msg = "Expected filter name 'neg', got '" + fd->filter_name + "'.";
        }
        return nullptr;
    }
    if (fd->GetFilterParamsCount() != 0) {
        if (error_msg) {
            *error_msg =
                "Negative filter requires no parameters, got " + std::to_string(fd->GetFilterParamsCount()) + ".";
        }
        return nullptr;
    }
    return std::make_unique<NegativeFilter>();
}
