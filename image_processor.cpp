#include <cassert>
#include <iostream>
#include <memory>

#include "filters_base/filtercreators.h"
#include "filter_makers/crop_filter_cmd_args_maker.h"
#include "filter_makers/edge_detection_filter_cmd_args_maker.h"
#include "filter_makers/grayscale_filter_cmd_args_maker.h"
#include "filter_makers/negative_filter_cmd_args_maker.h"
#include "filter_makers/sharpening_filter_cmd_args_maker.h"
#include "filter_makers/solarize_filter_cmd_args_maker.h"
#include "help.h"
#include "image/color.h"
#include "image/matrix.h"

int main(int argc, char** argv) {
    if (argc == 1) {
        PrintHelp();
        return 0;
    }

    FilterCreatorFactory factory;
    factory.RegisterFilterCreator("crop", CreateCropFilterFromCmdArgs);
    factory.RegisterFilterCreator("gs", CreateGrayscaleFilterFromCmdArgs);
    factory.RegisterFilterCreator("neg", CreateNegativeFilterFromCmdArgs);
    factory.RegisterFilterCreator("sharp", CreateSharpeningFilterFromCmdArgs);
    factory.RegisterFilterCreator("edge", CreateEdgeDetectionFilterFromCmdArgs);
    factory.RegisterFilterCreator("solarize", CreateSolarizeFilterFromCmdArgs);

    CmdLineArgsParser parser;
    CmdLineArgsParser::ErrorCode parse_result = parser.Parse(argc, argv);
    if (parse_result != CmdLineArgsParser::ErrorCode::Ok) {
        std::cerr << "Error parsing command line arguments: ";
        switch (parse_result) {
            case CmdLineArgsParser::ErrorCode::NotEnoughArgs:
                std::cerr << "Not enough arguments. Expected at least " << parser.MIN_ARG_COUNT
                          << " (program name, input file, output file), got " << argc << ".";
                break;
            case CmdLineArgsParser::ErrorCode::InvalidArgFormat:
                std::cerr << "Invalid argument format. Filter names must start with '-'.";
                break;
            case CmdLineArgsParser::ErrorCode::UnknownFilter:
                std::cerr << "Unknown filter name.";
                break;
            case CmdLineArgsParser::ErrorCode::InvalidFilterParams:
                std::cerr << "Some filters have invalid params";
                break;
            default:
                std::cerr << "Unknown error.";
                break;
        }
        std::cerr << std::endl;
        return 1;
    }

    BmpReaderWriter img;
    if (!img.ReadFromFile(parser.GetInFileName())) {
        std::cerr << "Failed to read input file: " << parser.GetInFileName() << std::endl;
        return 1;
    }

    std::vector<std::unique_ptr<BaseFilter>> filters;
    std::string pipeline_error;
    FilterPipeline pipeline = factory.CreatePipeline(parser.GetFilterDescriptors(), &pipeline_error);
    if (pipeline.GetFilterCount() == 0 && !parser.GetFilterDescriptors().empty()) {
        std::cerr << "Error: " << pipeline_error << std::endl;
        return 1;
    }

    for (const auto& desc : parser.GetFilterDescriptors()) {
        std::string filter_error;
        std::unique_ptr<BaseFilter> filter = factory.CreateFilter(&desc, &filter_error);
        if (!filter) {
            std::cerr << "Error creating filter '" << desc.filter_name << "': " << filter_error << std::endl;
            return 1;
        }
        filters.push_back(std::move(filter));
    }

    if (!pipeline.Apply(&img)) {
        std::cerr << "Failed to apply filters." << std::endl;
        return 1;
    }

    if (!img.WriteToFile(parser.GetOutFileName())) {
        std::cerr << "Failed to write output file: " << parser.GetOutFileName() << std::endl;
        return 1;
    }

    std::cout << "Image processed successfully." << std::endl;
    return 0;
}
