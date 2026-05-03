#pragma once

#include "../filters_base/filter.h"
#include "../image/dib.h"

class CropFilter : public BaseFilter {
public:
    CropFilter(int width, int height) : width_(width), height_(height) {
    }
    bool Apply(BmpReaderWriter* img) const override;

private:
    int width_;
    int height_;
};
