#ifndef CsvOptionDataSource_H
#define CsvOptionDataSource_H

#include <iostream>
#include <span>
#include <string>
#include <filesystem>
#include <chrono>
#include <vector>

#include "OptionDataSource.h"
#include "models/RawOptionRowQuote.h"

class CsvOptionDataSource : public OptionDataSource
{
private:
	std::string dir_;
	std::vector<RawOptionRowQuote> optionQuotes_;

public:
	explicit CsvOptionDataSource(std::string dir)
		: dir_(dir) 
	{}

	std::vector<RawOptionRowQuote> getByUnderlying(std::string underlying) const;
	std::vector<RawOptionRowQuote> getByUnderlyings(std::span<const std::string_view> underlyings) const;
	std::vector<RawOptionRowQuote> getByUnderlyingsAndDateRange(
		std::span<const std::string> underlyings, MarketTimePoint start, MarketTimePoint end) const;
	std::vector<RawOptionRowQuote> getByDateRange(MarketTimePoint start, MarketTimePoint end) const;
	std::vector<RawOptionRowQuote> getByDate(MarketTimePoint date) const;
};

#endif
