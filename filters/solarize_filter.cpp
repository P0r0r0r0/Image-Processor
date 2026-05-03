#include <stdexcept>

#include "solarize_filter.h"

SolarizeFilter::SolarizeFilter(double threshold) : threshold_(threshold) {
}

bool SolarizeFilter::Apply(BmpReaderWriter* img) const {
    if (!img || img->GetPixels().GetRowAmount() == 0 || img->GetPixels().GetColAmount() == 0) {
        return false;
    }

    Matrix<Color>& pixels = img->GetPixels();
    size_t height = pixels.GetRowAmount();
    size_t width = pixels.GetColAmount();

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            Color& pixel = pixels[y][x];
            double r = pixel.GetR();
            double g = pixel.GetG();
            double b = pixel.GetB();

            if (r > threshold_) {
                r = 1.0 - r;
            }
            if (g > threshold_) {
                g = 1.0 - g;
            }
            if (b > threshold_) {
                b = 1.0 - b;
            }
            if (pixel.SetR(std::max(0.0, std::min(1.0, r))) != Color::ErrorCode::Ok ||
                pixel.SetG(std::max(0.0, std::min(1.0, g))) != Color::ErrorCode::Ok ||
                pixel.SetB(std::max(0.0, std::min(1.0, b))) != Color::ErrorCode::Ok) {
                return false;
            }
        }
    }
    return true;
}
