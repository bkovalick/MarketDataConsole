#include "config/Config.h"

#include <chrono>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

namespace {

MarketTimePoint parse_date(const std::string& text)
{
    std::istringstream in(text);
    std::chrono::sys_days day;
    in >> std::chrono::parse("%F", day);
    if (in.fail()) {
        throw std::runtime_error("Invalid date '" + text + "', expected YYYY-MM-DD");
    }
    return day;
}

}

Config Config::load(const std::filesystem::path& path)
{
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Cannot open config file: " + path.string());
    }

    const auto json = nlohmann::json::parse(file);

    Config config;
    config.dataSource.type = json.at("dataSource").at("type").get<std::string>();
    config.dataSource.path = json.at("dataSource").at("path").get<std::string>();
    config.strategy.type = json.at("strategy").at("type").get<std::string>();
    config.underlyings = json.at("underlyings").get<std::span<const std::string_view>>();
    config.startDate = parse_date(json.at("startDate").get<std::string>());
    config.endDate = parse_date(json.at("endDate").get<std::string>());
    config.logFile = json.value("logFile", "logs/marketdata.log");

    if (config.startDate > config.endDate) {
        throw std::runtime_error("startDate must not be after endDate");
    }
    if (config.underlyings.empty()) {
        throw std::runtime_error("At least one underlying is required");
    }

    return config;
}