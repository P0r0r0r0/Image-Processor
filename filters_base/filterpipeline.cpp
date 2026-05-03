#include <memory>

#include "filterpipeline.h"

bool FilterPipeline::Apply(BmpReaderWriter* img) const {
    if (!img) {
        return false;
    }

    for (const std::unique_ptr<BaseFilter>& filter : coll_) {
        if (!filter) {
            return false;
        }

        if (!filter->Apply(img)) {
            return false;
        }
    }
    return true;
}

std::unique_ptr<BaseFilter> FilterPipeline::AddFilter(std::unique_ptr<BaseFilter> filter) {
    coll_.push_back(std::move(filter));
    return filter;
}
