#pragma once

#include <cstdint>
#include <string>

#include "color.h"
#include "matrix.h"

class BmpReaderWriter {
public:
    struct BmpHeader {
        uint16_t sign;
        uint32_t size;
        uint16_t reserve_a;
        uint16_t reserve_b;
        uint32_t offset;
    } __attribute__((packed));

    struct DibHeader {
        uint32_t header_size;
        int32_t width;
        int32_t height;
        uint16_t planes;
        uint16_t bit_per_pixel;
        uint32_t compression;
        uint32_t image_size;
        int32_t x_pixels_per_meter;
        int32_t y_pixels_per_meter;
        uint32_t colors_used_num;
        uint32_t colors_important_num;
    } __attribute__((packed));

    const size_t BMP_HEADER_SIZE = sizeof(BmpHeader);
    const size_t DIB_HEADER_SIZE = sizeof(DibHeader);

public:
    BmpReaderWriter() = default;
    ~BmpReaderWriter() = default;

    bool ReadFromFile(const std::string& path);

    bool ReadFromStream(std::istream& istr);

    bool WriteToFile(const std::string& path);

    bool WriteToStream(std::ostream& ostr);

    void SetPixels(const Matrix<Color>& pixels);

public:
    BmpHeader& GetBmpHeader() {
        return bmp_header_;
    }

    DibHeader& GetDibHeader() {
        return dib_header_;
    }

    Matrix<Color>& GetPixels() {
        return pixels_;
    }

    const Matrix<Color>& GetPixels() const {
        return pixels_;
    }

protected:
    BmpHeader bmp_header_ = {};
    DibHeader dib_header_ = {};
    Matrix<Color> pixels_;
};
