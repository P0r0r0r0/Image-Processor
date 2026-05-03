#pragma once

#include <vector>

#include "filter.h"
#include "../image/matrix.h"

class MatrixFilter : public BaseFilter {
public:
    explicit MatrixFilter(const std::vector<std::vector<double>>& convolution_matrix);

public:
    bool Apply(BmpReaderWriter* img) const override;

protected:
    Matrix<double> convolution_matrix_;
    size_t conv_matrix_size_;
};
