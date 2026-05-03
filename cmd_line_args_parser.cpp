#include "cmd_line_args_parser.h"

CmdLineArgsParser::CmdLineArgsParser() : in_file_name_{nullptr}, out_file_name_{nullptr}, last_code_{ErrorCode::Ok} {
    filter_param_counts_["crop"] = 2;
    filter_param_counts_["gs"] = 0;
    filter_param_counts_["neg"] = 0;
    filter_param_counts_["sharp"] = 0;
    filter_param_counts_["edge"] = 1;
    filter_param_counts_["solarize"] = 1;
}

CmdLineArgsParser::ErrorCode CmdLineArgsParser::Parse(int argc, char *argv[]) {
    if (argc < MIN_ARG_COUNT) {
        last_code_ = ErrorCode::NotEnoughArgs;
        return last_code_;
    }
    in_file_name_ = argv[1];
    out_file_name_ = argv[2];

    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.empty() || arg[0] != '-') {
            last_code_ = ErrorCode::InvalidArgFormat;
            return last_code_;
        }

        std::string filter_name = arg.substr(1);
        FilterDescriptor descriptor;
        descriptor.filter_name = filter_name;

        // проверка, что фильтр существует
        auto it = filter_param_counts_.find(filter_name);
        if (it == filter_param_counts_.end()) {
            last_code_ = ErrorCode::UnknownFilter;
            return last_code_;
        }

        size_t expected_params_num = it->second;

        // если аргументов слишком мало
        if (i + expected_params_num >= static_cast<size_t>(argc)) {
            last_code_ = ErrorCode::InvalidFilterParams;
            return last_code_;
        }

        for (size_t j = 0; j < expected_params_num; ++j) {
            descriptor.filter_params.push_back(argv[++i]);
        }

        // если параметров слишком много
        if (i + 1 < argc && argv[i + 1][0] != '-') {
            last_code_ = ErrorCode::InvalidFilterParams;
            return last_code_;
        }

        filter_descriptors_.push_back(descriptor);
    }

    last_code_ = ErrorCode::Ok;
    return last_code_;
}
