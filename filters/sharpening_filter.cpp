#include "sharpening_filter.h"

const std::vector<std::vector<double>> CONV_MATRIX = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

SharpeningFilter::SharpeningFilter() : MatrixFilter(CONV_MATRIX) {
}
