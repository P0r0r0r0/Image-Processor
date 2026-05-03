#include <memory>
#include <stdexcept>

#include "filtercreators.h"

void FilterCreatorFactory::RegisterFilterCreator(const std::string& filter_name, PFunFilterCreator filter_creator) {
    if (filter_name.empty()) {
        throw std::invalid_argument("Filter name cannot be empty.");
    }

    if (!filter_creator) {
        throw std::invalid_argument("Filter creator cannot be null.");
    }

    if (filter_creator_mapping_.find(filter_name) != filter_creator_mapping_.end()) {
        throw std::logic_error("Filter with name '" + filter_name + "' is already registered.");
    }
    filter_creator_mapping_.insert({filter_name, filter_creator});
}

std::unique_ptr<BaseFilter> FilterCreatorFactory::CreateFilter(const FilterDescriptor* fd, std::string* error_msg) {
    if (!fd) {
        if (error_msg) {
            *error_msg = "Filter descriptor is null.";
        }
        return nullptr;
    }

    auto filter_creator_it = filter_creator_mapping_.find(fd->filter_name);
    if (filter_creator_it == filter_creator_mapping_.end()) {
        if (error_msg) {
            *error_msg = "Unknown filter name: '" + fd->filter_name + "'.";
        }
        return nullptr;
    }
    PFunFilterCreator filter_creator = filter_creator_it->second;
    return filter_creator(fd, error_msg);
}

FilterPipeline FilterCreatorFactory::CreatePipeline(const CmdLineArgsParser::FilterDescriptors& descriptors,
                                                    std::string* error_msg) {
    FilterPipeline pipeline;
    for (const FilterDescriptor& descr : descriptors) {
        std::string local_error;
        std::unique_ptr<BaseFilter> filter = CreateFilter(&descr, &local_error);
        if (!filter) {
            if (error_msg) {
                *error_msg = "Failed to create filter '" + descr.filter_name + "': " + local_error;
            }
            return FilterPipeline();
        }
        pipeline.AddFilter(std::move(filter));
    }
    return pipeline;
}
