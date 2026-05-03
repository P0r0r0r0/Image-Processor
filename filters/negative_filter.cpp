#include "negative_filter.h"

bool NegativeFilter::Apply(BmpReaderWriter* img) const {
    if (!img) {
        return false;
    }
    const Matrix<Color>& img_pixels = img->GetPixels();
    size_t height = img_pixels.GetRowAmount();
    size_t width = img_pixels.GetColAmount();

    Matrix<Color> result(height, width);
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            Color pixel = img_pixels.GetEl(y, x);
            Color& res_pixel = result.GetEl(y, x);
            res_pixel.SetR(1.0 - pixel.GetR());
            res_pixel.SetG(1.0 - pixel.GetG());
            res_pixel.SetB(1.0 - pixel.GetB());
        }
    }
    img->SetPixels(result);
    return true;
}
