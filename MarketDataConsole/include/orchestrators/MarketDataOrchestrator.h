#ifndef MarketDataOrchestrator_H
#define MarketDataOrchestrator_H

#include <memory>
#include <string>
#include <span>
#include <string_view>

#include "providers/OptionDataProvider.h"
#include "services/GenericTradingStrategy.h"
#include "config/Config.h"
#include "logging/Logger.h"

class MarketDataOrchestrator
{
private:
	std::unique_ptr<OptionDataProvider> optionDataProvider_;
	std::unique_ptr<GenericTradingStrategy> strategy_;

public:
	explicit MarketDataOrchestrator(std::unique_ptr<OptionDataProvider> optionDataProvider,
		std::unique_ptr<GenericTradingStrategy> strategy)
		: optionDataProvider_(std::move(optionDataProvider)), strategy_(std::move(strategy)) {};

	~MarketDataOrchestrator() = default;

	void run(const Config& config);
};

//class IStrategy {
//public:
//	virtual ~IStrategy() = default;
//	virtual std::vector<Signal> run(const std::vector<OptionChain>& chains) = 0;
//};
//
//class IResultStore {
//public:
//	virtual ~IResultStore() = default;
//	virtual void save(const std::vector<Signal>& signals) = 0;
//};
//
//class MarketDataOrchestrator {
//public:
//	MarketDataOrchestrator(std::unique_ptr<OptionDataProvider> provider,
//	                       std::unique_ptr<IStrategy> strategy,
//	                       std::unique_ptr<IResultStore> store)
//		: provider_(std::move(provider)), strategy_(std::move(strategy)), store_(std::move(store)) {}
//
//	void run_once(std::span<const std::string> underlyings)
//	{
//		auto chains = provider_->get_option_chain_by_underlyings(underlyings);
//		auto signals = strategy_->run(chains);
//		store_->save(signals);
//	}
//	// ...
//};
#endif