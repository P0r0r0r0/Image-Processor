#pragma once

#include <memory>

#include "../cmd_line_args_parser.h"
#include "../filters_base/filter.h"

std::unique_ptr<BaseFilter> CreateSharpeningFilterFromCmdArgs(const FilterDescriptor* fd,
                                                              std::string* error_msg = nullptr);
