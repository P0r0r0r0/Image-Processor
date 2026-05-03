#include "grayscale_filter.h"

double const PARAM1 = 0.299;
double const PARAM2 = 0.587;
double const PARAM3 = 0.114;

bool GrayscaleFilter::Apply(BmpReaderWriter* img) const {
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
            double gray = PARAM1 * pixel.GetR() + PARAM2 * pixel.GetG() + PARAM3 * pixel.GetB();
            Color& res_pixel = result.GetEl(y, x);
            res_pixel.SetR(gray);
            res_pixel.SetG(gray);
            res_pixel.SetB(gray);
        }
    }
    img->SetPixels(result);
    return true;
}
