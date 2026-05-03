#pragma once

#include "../filters_base/filter.h"
#include "../image/dib.h"

class NegativeFilter : public BaseFilter {
public:
    NegativeFilter() = default;
    bool Apply(BmpReaderWriter* img) const override;
};
