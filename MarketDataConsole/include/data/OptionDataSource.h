#ifndef OptionDataSource_H
#define OptionDataSource_H

#include <iostream>
#include <span>
#include <string>
#include <string_view>
#include <chrono>
#include <vector>

#include "models/RawOptionRowQuote.h"
#include "models/Types.h"

class OptionDataSource
{

public:
	virtual ~OptionDataSource() = default;

	virtual std::vector<RawOptionRowQuote> getByUnderlying(std::string underlying) const = 0;
	virtual std::vector<RawOptionRowQuote> getByUnderlyings(std::span<const std::string_view> underlyings) const = 0;
	virtual std::vector<RawOptionRowQuote> getByUnderlyingsAndDateRange(
		std::span<const std::string_view> underlyings, MarketTimePoint start, MarketTimePoint end) const = 0;
	virtual std::vector<RawOptionRowQuote> getByDateRange(MarketTimePoint start, MarketTimePoint end) const = 0;
	virtual std::vector<RawOptionRowQuote> getByDate(MarketTimePoint date) const = 0;
};

#endif