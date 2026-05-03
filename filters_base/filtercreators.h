#pragma once

#include <map>
#include <memory>
#include <string>

#include "filter.h"
#include "filterpipeline.h"
#include "../cmd_line_args_parser.h"

class FilterCreatorFactory {
public:
    using PFunFilterCreator = std::unique_ptr<BaseFilter> (*)(const FilterDescriptor* fd, std::string* error_msg);
    using FilterName2CreatorMap = std::map<std::string, PFunFilterCreator>;

public:
    FilterCreatorFactory(){};

    std::unique_ptr<BaseFilter> CreateFilter(const FilterDescriptor* fd, std::string* error_msg = nullptr);

    FilterPipeline CreatePipeline(const CmdLineArgsParser::FilterDescriptors& descriptors,
                                  std::string* error_msg = nullptr);

    void RegisterFilterCreator(const std::string& filter_name, PFunFilterCreator filter_creator);

protected:
    FilterName2CreatorMap filter_creator_mapping_;
};
