#pragma once

#include "../filters_base/filter.h"
#include "../image/dib.h"

class SolarizeFilter : public BaseFilter {
public:
    explicit SolarizeFilter(double threshold);
    bool Apply(BmpReaderWriter* img) const override;

private:
    double threshold_;
};
