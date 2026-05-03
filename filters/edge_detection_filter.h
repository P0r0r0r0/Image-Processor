#pragma once

#include "../filters_base/matrix_filter.h"
#include "../image/dib.h"

class EdgeDetectionFilter : public MatrixFilter {
public:
    explicit EdgeDetectionFilter(double threshold);
    bool Apply(BmpReaderWriter* img) const override;

private:
    double threshold_;
};
