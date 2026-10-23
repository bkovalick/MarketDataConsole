#ifndef Config_H
#define Config_H

#include <filesystem>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "models/Types.h"

struct Config
{
    struct DataSource {
        std::string type;
        std::string path;
    };

    struct Strategy {
        std::string type;
    };

    DataSource dataSource;
    Strategy strategy;
    std::span<const std::string_view> underlyings;
    MarketTimePoint startDate;
    MarketTimePoint endDate;
    std::string logFile;

    static Config load(const std::filesystem::path& path);
};

#endif