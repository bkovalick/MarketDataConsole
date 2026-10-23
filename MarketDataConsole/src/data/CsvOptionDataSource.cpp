#include "data/CsvOptionDataSource.h"
#include "logging/Logger.h"

std::vector<RawOptionRowQuote> CsvOptionDataSource::getByUnderlying(std::string underlying) const
{ 
	return optionQuotes_; 
}

std::vector<RawOptionRowQuote> CsvOptionDataSource::getByUnderlyings(std::span<const std::string_view> underlyings) const
{ 
	return optionQuotes_; 
}

std::vector<RawOptionRowQuote> CsvOptionDataSource::getByUnderlyingsAndDateRange(
	std::span<const std::string> underlyings, 
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

//// inside the loader, once you write it
//Logger::info("Loading quotes from '{}'", dir_);
//// ... parse rows ...
//Logger::info("Loaded {} quotes ({} malformed rows skipped)", optionQuotes_.size(), skipped);