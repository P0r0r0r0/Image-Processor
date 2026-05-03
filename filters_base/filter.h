#pragma once

#include "../image/dib.h"

class BaseFilter {
public:
    virtual ~BaseFilter() {
    }

public:
    virtual bool Apply(BmpReaderWriter* img) const = 0;
};
