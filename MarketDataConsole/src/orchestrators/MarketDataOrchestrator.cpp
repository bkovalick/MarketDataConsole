#include "orchestrators/MarketDataOrchestrator.h"
#include "logging/Logger.h"

void MarketDataOrchestrator::run(const Config& config)
{
	Logger::info("Run started");
	auto underlyings = config.underlyings;

	Logger::info("Loading option chains for {} underlyings", underlyings.size());

	auto optionChains = optionDataProvider_->getOptionChainByUnderlyings(underlyings);
	Logger::info("Loaded {} option chains", optionChains.size());

	Logger::info("Run finished");
}