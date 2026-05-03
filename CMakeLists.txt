cmake_minimum_required(VERSION 3.10)
project(image_processor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(PROJECT_FILES
    cmd_line_args_parser.cpp
    cmd_line_args_parser.h
    filters_base/filter.h
    filters_base/matrix_filter.cpp
    filters_base/matrix_filter.h
    filters_base/filterpipeline.cpp
    filters_base/filterpipeline.h
    filters_base/filtercreators.cpp
    filters_base/filtercreators.h
    filters/crop_filter.cpp
    filters/crop_filter.h
    filters/edge_detection_filter.cpp
    filters/edge_detection_filter.h
    filters/grayscale_filter.cpp
    filters/grayscale_filter.h
    filters/negative_filter.cpp
    filters/negative_filter.h
    filters/sharpening_filter.cpp
    filters/sharpening_filter.h
    filters/solarize_filter.cpp
    filters/solarize_filter.h
    filter_makers/crop_filter_cmd_args_maker.cpp
    filter_makers/crop_filter_cmd_args_maker.h
    filter_makers/edge_detection_filter_cmd_args_maker.cpp
    filter_makers/edge_detection_filter_cmd_args_maker.h
    filter_makers/grayscale_filter_cmd_args_maker.cpp
    filter_makers/grayscale_filter_cmd_args_maker.h
    filter_makers/negative_filter_cmd_args_maker.cpp
    filter_makers/negative_filter_cmd_args_maker.h
    filter_makers/sharpening_filter_cmd_args_maker.cpp
    filter_makers/sharpening_filter_cmd_args_maker.h
    filter_makers/solarize_filter_cmd_args_maker.cpp
    filter_makers/solarize_filter_cmd_args_maker.h
    image/color.cpp
    image/color.h
    image/dib.cpp
    image/dib.h
    image/matrix.h
    my_tests/catch.hpp
)

add_executable(image_processor
    ${PROJECT_FILES}
    image_processor.cpp  
)



add_executable(test_matrix
    ${PROJECT_FILES}
    my_tests/test_matrix.cpp
)
target_include_directories(test_matrix PUBLIC .)

add_executable(test_color
    ${PROJECT_FILES}
    my_tests/test_color.cpp
)
target_include_directories(test_color PUBLIC .)

add_executable(test_bmp
    ${PROJECT_FILES}
    my_tests/test_bmp.cpp
)
target_include_directories(test_bmp PUBLIC .)

enable_testing()
add_test(NAME MatrixTest COMMAND test_matrix)
add_test(NAME ColorTest COMMAND test_color)
add_test(NAME BmpReaderWriterTest COMMAND test_bmp)
