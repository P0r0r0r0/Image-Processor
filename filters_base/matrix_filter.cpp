#include <algorithm>
#include <cassert>

#include "matrix_filter.h"

MatrixFilter::MatrixFilter(const std::vector<std::vector<double>>& convolution_matrix)
    : conv_matrix_size_{convolution_matrix.size()} {
    assert(conv_matrix_size_ > 0 && conv_matrix_size_ % 2 == 1);
    assert(convolution_matrix.size() == convolution_matrix[0].size());

    convolution_matrix_ = Matrix<double>(conv_matrix_size_, conv_matrix_size_);
    for (size_t i = 0; i < conv_matrix_size_; ++i) {
        for (size_t j = 0; j < conv_matrix_size_; ++j) {
            convolution_matrix_.GetEl(i, j) = convolution_matrix[i][j];
        }
    }
}

bool MatrixFilter::Apply(BmpReaderWriter* img) const {
    if (!img || img->GetPixels().GetRowAmount() == 0 || img->GetPixels().GetColAmount() == 0) {
        return false;
    }

    const Matrix<Color>& img_pixels = img->GetPixels();
    size_t height = img_pixels.GetRowAmount();
    size_t width = img_pixels.GetColAmount();
    Matrix<Color> result(height, width);

    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            Matrix<Color>::ConstSquareWindow window = img_pixels.GetSquareWindow(y, x, conv_matrix_size_);
            double r = 0.0;
            double g = 0.0;
            double b = 0.0;

            for (size_t ky = 0; ky < conv_matrix_size_; ++ky) {
                for (size_t kx = 0; kx < conv_matrix_size_; ++kx) {
                    Color pixel = window(ky, kx);
                    double weight = convolution_matrix_.GetEl(ky, kx);
                    r += pixel.GetR() * weight;
                    g += pixel.GetG() * weight;
                    b += pixel.GetB() * weight;
                }
            }

            Color& res_pixel = result.GetEl(y, x);
            if (res_pixel.SetR(std::max(0.0, std::min(1.0, r))) != Color::ErrorCode::Ok ||
                res_pixel.SetG(std::max(0.0, std::min(1.0, g))) != Color::ErrorCode::Ok ||
                res_pixel.SetB(std::max(0.0, std::min(1.0, b))) != Color::ErrorCode::Ok) {
                return false;
            }
        }
    }
    img->SetPixels(result);
    return true;
}
