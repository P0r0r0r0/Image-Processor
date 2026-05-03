#pragma once

#include <map>
#include <string>
#include <vector>

struct FilterDescriptor {
    size_t GetFilterParamsCount() const {
        return filter_params.size();
    }
    std::string filter_name;
    std::vector<std::string> filter_params;
};

class CmdLineArgsParser {
public:
    enum class ErrorCode {
        Ok,                   // все в порядке
        NotEnoughArgs,        // недостаточно аргументов
        UnknownFilter,        // неизвестный фильтр
        InvalidFilterParams,  // некорректное количество или формат параметров
        InvalidArgFormat      // некорректный формат аргумента (нет "-")
    };

    using FilterDescriptors = std::vector<FilterDescriptor>;

    const int MIN_ARG_COUNT = 3;  // имя программы, входной файл, выходной файл
public:
    CmdLineArgsParser();

public:
    ErrorCode Parse(int argc, char* argv[]);

    size_t GetFiltersCount() const {
        return filter_descriptors_.size();
    }

    const char* GetInFileName() const {
        return in_file_name_;
    }

    const char* GetOutFileName() const {
        return out_file_name_;
    }

    const FilterDescriptors& GetFilterDescriptors() const {
        return filter_descriptors_;
    }

    ErrorCode GetLastErrorCode() const {
        return last_code_;
    }

protected:
    char* in_file_name_;
    char* out_file_name_;
    FilterDescriptors filter_descriptors_;
    ErrorCode last_code_;
    std::map<std::string, size_t> filter_param_counts_;
};
