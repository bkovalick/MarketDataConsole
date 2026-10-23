#include "data/CsvOptionDataSource.h"

std::vector<RawOptionRowQuote> CsvOptionDataSource::getByUnderlying(std::string underlying) const
{ 
	return optionQuotes_; 
}

std::vector<RawOptionRowQuote> CsvOptionDataSource::getByUnderlyings(std::span<const std::string_view> underlyings) const
{ 
	return optionQuotes_; 
}

std::vector<RawOptionRowQuote> CsvOptionDataSource::getByUnderlyingsAndDateRange(
	std::span<const std::string_view> underlyings,
	MarketTimePoint start, 
	MarketTimePoint end) const 
{
	return optionQuotes_;
}

std::vector<RawOptionRowQuote> CsvOptionDataSource::getByDateRange(MarketTimePoint start, MarketTimePoint end) const
{ 
	return optionQuotes_; 
}

std::vector<RawOptionRowQuote> CsvOptionDataSource::getByDate(MarketTimePoint date) const
{ 
	return optionQuotes_; 
}