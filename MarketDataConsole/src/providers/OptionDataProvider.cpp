#include "providers/OptionDataProvider.h"
#include "logging/Logger.h"

std::vector<OptionChain> OptionDataProvider::buildOptionChains(std::vector<RawOptionRowQuote> rawQuotes)
{
	std::unordered_map<std::string,
		std::map<std::string, std::map<double, StrikeLevel>>> grouped;

	std::unordered_map<std::string, double> spots;
	for (auto& quote : rawQuotes) {
		const TickerDetails details = TickerDetails::parse_quote_details(quote);

		spots[quote.symbol] = quote.spot;

		auto& strikeMap = grouped[details.symbol][details.expiration];
		auto [it, inserted] = strikeMap.try_emplace(details.strike);

		if (inserted) {
			it->second.strike = details.strike;
		}
		
		if (details.isCall) {
			it->second.call = to_option_quote(std::move(quote));
		}
		else {
			it->second.put = to_option_quote(std::move(quote));
		}
	}

	std::vector<OptionChain> optionChains;
	optionChains.reserve(grouped.size());

	for (auto& [underlying, by_expiry] : grouped) {
		auto& optionChain = optionChains.emplace_back();
		optionChain.underlying = underlying;
		optionChain.spot = spots[underlying];
		optionChain.asOf = std::chrono::system_clock::now();

		for (auto& [expiry, by_strike] : by_expiry) {
			ExpirySlice slice;
			slice.expiry = expiry;
			slice.strikes = std::move(by_strike);

			optionChain.slices.push_back(std::move(slice));
		}
	}

	Logger::info("Built {} option chains from raw quotes", optionChains.size());
	return optionChains;
}

std::vector<OptionChain> OptionDataProvider::getOptionChainByUnderlyings(std::span<const std::string_view> underlyings)
{
	auto rows = src_->getByUnderlyings(underlyings);
	Logger::info("Source returned {} raw quotes", rows.size());
	if (rows.empty()) {
		Logger::error("No quotes returned for the requested underlyings");
	}
	return buildOptionChains(std::move(rows));
}