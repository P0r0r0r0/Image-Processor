#include "dib.h"

#include <cstdint>
#include <fstream>
#include <ios>
#include <vector>

const size_t BIT_PER_PIXEL = 24;
const size_t BIT_PER_BYTE = 8;
const uint16_t BM = 0x4D42;

bool BmpReaderWriter::ReadFromFile(const std::string& path) {
    std::ifstream file(path, std::ios_base::binary);
    if (!file.is_open()) {
        return false;
    }
    return ReadFromStream(file);
}

bool BmpReaderWriter::ReadFromStream(std::istream& istr) {
    istr.read(reinterpret_cast<char*>(&bmp_header_), static_cast<std::streamsize>(BMP_HEADER_SIZE));
    if (static_cast<size_t>(istr.gcount()) != BMP_HEADER_SIZE) {
        return false;
    }

    istr.read(reinterpret_cast<char*>(&dib_header_), static_cast<std::streamsize>(DIB_HEADER_SIZE));
    if (static_cast<size_t>(istr.gcount()) != DIB_HEADER_SIZE || dib_header_.header_size != DIB_HEADER_SIZE ||
        dib_header_.bit_per_pixel != BIT_PER_PIXEL || dib_header_.compression != 0 || dib_header_.planes != 1) {
        return false;
    }

    int32_t width = dib_header_.width;
    int32_t height = dib_header_.height;
    if (width <= 0 || height <= 0) {
        return false;
    }

    pixels_ = Matrix<Color>(height, width);

    size_t row_bytes = width * dib_header_.bit_per_pixel / BIT_PER_BYTE;
    size_t padding = (4 - (row_bytes % 4)) % 4;  // до кратности 4 байтам
    size_t row_size_with_padding = row_bytes + padding;

    std::vector<char> row_buffer(row_size_with_padding);
    istr.seekg(bmp_header_.offset, std::ios_base::beg);

    for (int32_t y = height - 1; y >= 0; --y) {  // так как BMP хранит строки снизу вверх
        istr.read(row_buffer.data(), static_cast<std::streamsize>(row_size_with_padding));
        if (static_cast<size_t>(istr.gcount()) != row_size_with_padding) {
            return false;
        }
        for (int32_t x = 0; x < width; ++x) {
            uint8_t b = static_cast<uint8_t>(row_buffer[x * 3]);
            uint8_t g = static_cast<uint8_t>(row_buffer[x * 3 + 1]);
            uint8_t r = static_cast<uint8_t>(row_buffer[x * 3 + 2]);
            pixels_.GetEl(y, x).SetFromBytes(r, g, b);
        }
    }
    return true;
}

bool BmpReaderWriter::WriteToFile(const std::string& path) {
    std::ofstream file(path, std::ios_base::binary);
    if (!file.is_open()) {
        return false;
    }
    return WriteToStream(file);
}

bool BmpReaderWriter::WriteToStream(std::ostream& ostr) {
    if (!ostr.good() || pixels_.GetRowAmount() == 0 || pixels_.GetColAmount() == 0) {
        return false;
    }
    int32_t height = static_cast<int32_t>(pixels_.GetRowAmount());
    int32_t width = static_cast<int32_t>(pixels_.GetColAmount());
    size_t row_bytes = width * BIT_PER_PIXEL / BIT_PER_BYTE;
    size_t padding = (4 - (row_bytes % 4)) % 4;
    size_t row_size_with_padding = row_bytes + padding;
    size_t data_size = row_size_with_padding * height;
    size_t file_size = BMP_HEADER_SIZE + DIB_HEADER_SIZE + data_size;

    BmpHeader bmp_header = {};
    bmp_header.sign = BM;
    bmp_header.size = static_cast<uint32_t>(file_size);
    bmp_header.offset = static_cast<uint32_t>(BMP_HEADER_SIZE + DIB_HEADER_SIZE);

    DibHeader dib_header = {};
    dib_header.header_size = DIB_HEADER_SIZE;
    dib_header.width = width;
    dib_header.height = height;
    dib_header.planes = 1;
    dib_header.bit_per_pixel = BIT_PER_PIXEL;
    dib_header.compression = 0;
    dib_header.image_size = static_cast<uint32_t>(data_size);

    ostr.write(reinterpret_cast<const char*>(&bmp_header), static_cast<std::streamsize>(BMP_HEADER_SIZE));
    ostr.write(reinterpret_cast<const char*>(&dib_header), static_cast<std::streamsize>(DIB_HEADER_SIZE));

    std::vector<uint8_t> row_buffer(row_size_with_padding, 0);
    for (int32_t y = height - 1; y >= 0; --y) {
        for (int32_t x = 0; x < width; ++x) {
            row_buffer[x * 3] = static_cast<char>(pixels_.GetEl(y, x).GetBByte());
            row_buffer[x * 3 + 1] = static_cast<char>(pixels_.GetEl(y, x).GetGByte());
            row_buffer[x * 3 + 2] = static_cast<char>(pixels_.GetEl(y, x).GetRByte());
        }
        ostr.write(reinterpret_cast<const char*>(row_buffer.data()),
                   static_cast<std::streamsize>(row_size_with_padding));
    }
    return ostr.good();
}

void BmpReaderWriter::SetPixels(const Matrix<Color>& pixels) {
    pixels_ = pixels;
}
