#include <algorithm>

#include "crop_filter.h"

bool CropFilter::Apply(BmpReaderWriter* img) const {
    if (!img) {
        return false;
    }
    const Matrix<Color>& img_pixels = img->GetPixels();
    size_t img_height = img_pixels.GetRowAmount();
    size_t img_width = img_pixels.GetColAmount();

    // ограничиваем размеры доступными
    size_t new_width = std::min(static_cast<size_t>(width_), img_width);
    size_t new_height = std::min(static_cast<size_t>(height_), img_height);

    Matrix<Color> result(new_height, new_width);
    for (size_t y = 0; y < new_height; ++y) {
        for (size_t x = 0; x < new_width; ++x) {
            result.GetEl(y, x) = img_pixels.GetEl(y, x);
        }
    }
    img->SetPixels(result);
    return true;
}
