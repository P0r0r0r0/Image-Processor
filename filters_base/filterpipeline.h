#pragma once

#include <memory>
#include <vector>

#include "filter.h"
#include "../image/dib.h"

class FilterPipeline {
public:
    using FilterCollection = std::vector<std::unique_ptr<BaseFilter>>;

public:
    FilterPipeline() = default;
    FilterPipeline(const FilterPipeline&) = delete;  // чтоб работать с unique_ptr
    FilterPipeline& operator=(const FilterPipeline&) = delete;
    FilterPipeline(FilterPipeline&&) noexcept = default;
    FilterPipeline& operator=(FilterPipeline&&) noexcept = default;
    ~FilterPipeline() = default;

public:
    bool Apply(BmpReaderWriter* img) const;

    std::unique_ptr<BaseFilter> AddFilter(std::unique_ptr<BaseFilter> filter);

    size_t GetFilterCount() const {
        return coll_.size();
    }

protected:
    FilterCollection coll_;
};
