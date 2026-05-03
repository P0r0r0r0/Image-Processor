#include <cstdint>

#include "color.h"

Color::ErrorCode Color::Normalize(double r, double g, double b) {
    if (r < 0.0 || r > 1.0 || g < 0.0 || g > 1.0 || b < 0.0 || b > 1.0) {
        return ErrorCode::InvalidValue;
    }
    r_ = r;
    g_ = g;
    b_ = b;
    return ErrorCode::Ok;
}

void Color::SetFromBytes(uint8_t r, uint8_t g, uint8_t b) {
    r_ = static_cast<double>(r) / NORM_COEF;
    g_ = static_cast<double>(g) / NORM_COEF;
    b_ = static_cast<double>(b) / NORM_COEF;
}
