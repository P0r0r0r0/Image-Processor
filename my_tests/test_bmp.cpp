/*#define CATCH_CONFIG_MAIN

#include <fstream>

#include "catch.hpp"
#include "../image/dib.h"

void CreateMinimalBMP(const std::string& filename, int width, int height) {
    std::ofstream file(filename, std::ios::binary);
    REQUIRE(file.is_open());

    file.write("BM", 2);
    uint32_t file_size = 14 + 40 + width * height * 3;
    file.write(reinterpret_cast<const char*>(&file_size), 4);
    uint16_t reserve_a = 0;
    file.write(reinterpret_cast<const char*>(&reserve_a), 2);
    uint16_t reserve_b = 0;
    file.write(reinterpret_cast<const char*>(&reserve_b), 2);
    uint32_t offset = 14 + 40;
    file.write(reinterpret_cast<const char*>(&offset), 4);

    uint32_t header_size = 40;
    file.write(reinterpret_cast<const char*>(&header_size), 4);
    file.write(reinterpret_cast<const char*>(&width), 4);
    file.write(reinterpret_cast<const char*>(&height), 4);
    uint16_t planes = 1;
    file.write(reinterpret_cast<const char*>(&planes), 2);
    uint16_t bit_per_pixel = 24;
    file.write(reinterpret_cast<const char*>(&bit_per_pixel), 2);
    uint32_t compression = 0;
    file.write(reinterpret_cast<const char*>(&compression), 4);
    uint32_t image_size = width * height * 3;
    file.write(reinterpret_cast<const char*>(&image_size), 4);
    int32_t x_pixels_per_meter = 2835;
    file.write(reinterpret_cast<const char*>(&x_pixels_per_meter), 4);
    int32_t y_pixels_per_meter = 2835;
    file.write(reinterpret_cast<const char*>(&y_pixels_per_meter), 4);
    uint32_t colors_used_num = 0;
    file.write(reinterpret_cast<const char*>(&colors_used_num), 4);
    uint32_t colors_important_num = 0;
    file.write(reinterpret_cast<const char*>(&colors_important_num), 4);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            uint8_t b = 255;
            uint8_t g = 192;
            uint8_t r = 203;
            file.write(reinterpret_cast<const char*>(&b), 1);
            file.write(reinterpret_cast<const char*>(&g), 1);
            file.write(reinterpret_cast<const char*>(&r), 1);
        }
        int padding = (4 - (width * 3) % 4) % 4;
        for (int p = 0; p < padding; ++p) {
            file.write("\0", 1);
        }
    }
    file.close();
}

TEST_CASE("BMP Read Valid File") {
    CreateMinimalBMP("test.bmp", 2, 2);
    BmpReaderWriter img;
    REQUIRE(img.ReadFromFile("test.bmp"));
    REQUIRE(img.GetDibHeader().width == 2);
    REQUIRE(img.GetDibHeader().height == 2);
    REQUIRE(img.GetPixels().GetRowAmount() == 2);
    REQUIRE(img.GetPixels().GetColAmount() == 2);
    REQUIRE(img.GetPixels()[0][0].GetBByte() == 255);
    REQUIRE(img.GetPixels()[0][0].GetGByte() == 192);
    REQUIRE(img.GetPixels()[0][0].GetRByte() == 203);
    std::remove("test.bmp");
}

TEST_CASE("BMP Read Non-Existent File") {
    BmpReaderWriter img;
    REQUIRE_FALSE(img.ReadFromFile("nonexistent.bmp"));
}

TEST_CASE("BMP Write And Read Back") {
    Matrix<Color> pixels(1, 1);
    pixels[0][0].SetFromBytes(100, 150, 200);
    BmpReaderWriter img;
    img.SetPixels(pixels);
    REQUIRE(img.WriteToFile("test_output.bmp"));

    BmpReaderWriter img2;
    REQUIRE(img2.ReadFromFile("test_output.bmp"));
    REQUIRE(img2.GetPixels().GetRowAmount() == 1);
    REQUIRE(img2.GetPixels().GetColAmount() == 1);
    REQUIRE(img2.GetPixels()[0][0].GetRByte() == 100);
    REQUIRE(img2.GetPixels()[0][0].GetGByte() == 150);
    REQUIRE(img2.GetPixels()[0][0].GetBByte() == 200);
    std::remove("test_output.bmp");
}
*/