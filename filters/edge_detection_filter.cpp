#include <stdexcept>

#include "edge_detection_filter.h"
#include "grayscale_filter.h"

double const PARAM1 = 0.299;
double const PARAM2 = 0.587;
double const PARAM3 = 0.114;

EdgeDetectionFilter::EdgeDetectionFilter(double threshold)
    : MatrixFilter({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}), threshold_(threshold) {
}
bool EdgeDetectionFilter::Apply(BmpReaderWriter* img) const {
    if (!img) {
        return false;
    }

    const Matrix<Color>& img_pixels = img->GetPixels();
    size_t height = img_pixels.GetRowAmount();
    size_t width = img_pixels.GetColAmount();

    Matrix<Color> grayscale(height, width);
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            Color pixel = img_pixels.GetEl(y, x);
            double gray = PARAM1 * pixel.GetR() + PARAM2 * pixel.GetG() + PARAM3 * pixel.GetB();
            Color& gray_pixel = grayscale.GetEl(y, x);
            gray_pixel.SetR(gray);
            gray_pixel.SetG(gray);
            gray_pixel.SetB(gray);
        }
    }

    BmpReaderWriter temp_img;
    temp_img.SetPixels(grayscale);
    if (!MatrixFilter::Apply(&temp_img)) {
        return false;
    }

    const Matrix<Color>& convolved = temp_img.GetPixels();
    Matrix<Color> result(height, width);

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            Color pixel = convolved.GetEl(y, x);
            double value = pixel.GetR();
            Color& result_pixel = result.GetEl(y, x);
            if (value > threshold_) {
                result_pixel.SetR(1.0);
                result_pixel.SetG(1.0);
                result_pixel.SetB(1.0);
            } else {
                result_pixel.SetR(0.0);
                result_pixel.SetG(0.0);
                result_pixel.SetB(0.0);
            }
        }
    }
    img->SetPixels(result);
    return true;
}
