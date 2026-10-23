#ifndef OptionDataProvider_H
#define OptionDataProvider_H

#include <iostream>
#include <memory>
#include <span>
#include <string>
#include <unordered_map>
#include <map>
#include <charconv>
#include <stdexcept>
#include <string_view>

#include "data/OptionDataSource.h"
#include "models/OptionChain.h"
#include "models/TickerDetails.h"

class OptionDataProvider
{

private:
	std::unique_ptr<OptionDataSource> src_;
	std::vector<OptionChain> buildOptionChains(std::vector<RawOptionRowQuote> rawQuotes);

public:
	explicit OptionDataProvider(std::unique_ptr<OptionDataSource> src)
		: src_(std::move(src)) {}

	~OptionDataProvider() = default;

	std::vector<OptionChain> getOptionChainByUnderlyings(std::span<const std::string_view> underlyings);
};

#endif
