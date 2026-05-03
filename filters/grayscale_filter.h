#pragma once

#include "../filters_base/filter.h"
#include "../image/dib.h"

class GrayscaleFilter : public BaseFilter {
public:
    GrayscaleFilter() = default;
    bool Apply(BmpReaderWriter* img) const override;
};
