#include <exception>
#include <memory>
#include <stdexcept>
#include <string>

#include "config/Config.h"
#include "data/CsvOptionDataSource.h"
#include "logging/Logger.h"
#include "providers/OptionDataProvider.h"
#include "services/GenericTradingStrategy.h"
#include "orchestrators/MarketDataOrchestrator.h"

int main(int argc, char* argv[])
{
    try {
        const auto config = Config::load(argc > 1 ? argv[1] : "config/config.json");

        Logger::init(config.logFile);
        Logger::info("Starting Market Loading Service");
        Logger::info("Data source: {} '{}', strategy: {}, {} underlyings",
            config.dataSource.type, config.dataSource.path, config.strategy.type, config.underlyings.size());

        if (config.dataSource.type != "csv") {
            throw std::runtime_error("Unsupported data source type: " + config.dataSource.type);
        }
        if (config.strategy.type != "generic") {
            throw std::runtime_error("Unsupported strategy type: " + config.strategy.type);
        }

        auto csvOptionDataSource = std::make_unique<CsvOptionDataSource>(config.dataSource.path);
        auto optionDataProvider = std::make_unique<OptionDataProvider>(std::move(csvOptionDataSource));
        auto tradingStrategy = std::make_unique<GenericTradingStrategy>();

        auto orchestrator = MarketDataOrchestrator(std::move(optionDataProvider), std::move(tradingStrategy));
        orchestrator.run(config);
    }
    catch (const std::exception& e) {
        Logger::error("Fatal error: {}", e.what());
        return 1;
    }

    Logger::info("Ending Market Loading Service");
    return 0;
}