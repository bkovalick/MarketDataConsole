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
    MarketTimePoint startDate;
    MarketTimePoint endDate;
    std::string logFile;

    Config() = default;
    Config(Config&&) noexcept = default;
    Config& operator=(Config&&) noexcept = default;
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

    std::span<const std::string_view> underlyings() const { return underlyingViews_; }

    static Config load(const std::filesystem::path& path);

private:
    std::vector<std::string> underlyingStorage_;
    std::vector<std::string_view> underlyingViews_;
};

#endif