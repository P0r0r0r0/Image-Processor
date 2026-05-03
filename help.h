#pragma once

#include <iostream>

void PrintHelp() {
    std::cout << "----------Image Processor----------\n"
              << "A console application for applying filters to BMP images.\n\n"
              << "Usage:\n"
              << "  image_processor <input_file> <output_file> [-filter1 [param1 param2 ...]] [-filter2 ...]\n\n"
              << "Arguments:\n"
              << "  <input_file>    Path to the input BMP file (24-bit, uncompressed, BITMAPINFOHEADER).\n"
              << "  <output_file>   Path to the output BMP file where the result will be saved.\n\n"
              << "Available filters:\n"
              << "  -crop <width> <height>\n"
              << "      Crops the image to the specified width and height from the top-left corner.\n"
              << "      If dimensions exceed the original size, uses the available area.\n"
              << "  -gs\n"
              << "      Converts the image to grayscale." << "  -neg\n"
              << "      Creates a negative of the image." << "  -sharp\n"
              << "      Sharpens the image using a sharpening matrix.\n"
              << "  -edge <threshold>\n"
              << "      Detects edges by converting to grayscale and applying an edge detection matrix.\n"
              << "      Pixels above the threshold become white, others black.\n"
              << "      Threshold must be between 0 and 1.\n"
              << "  -blur <sigma>\n"
              << "      Applies Gaussian blur with the specified sigma value.\n"
              << "      Sigma must be positive.\n"
              << "  -solarize <threshold>\n"
              << "      Applies a solarize effect, inverting colors above the specified threshold.\n"
              << "      Threshold must be between 0 and 1.\n";
}
