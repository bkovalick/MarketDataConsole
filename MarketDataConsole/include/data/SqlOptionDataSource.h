#ifndef SqlOptionDataSource_H
#define SqlOptionDataSource_H

#include "OptionDataSource.h"
#include "models/RawOptionRowQuote.h"

class SqlOptionDataSource : public OptionDataSource
{
private:
	std::string connString_;

public:
	explicit SqlOptionDataSource(std::string connString) 
		: connString_(connString)
	{}

	std::vector<RawOptionRowQuote> getByUnderlying(std::string underlying) const;
	std::vector<RawOptionRowQuote> getByUnderlyings(std::span<const std::string_view> underlyings) const;
	std::vector<RawOptionRowQuote> getByUnderlyingsAndDateRange(
		std::span<const std::string_view> underlyings, MarketTimePoint start, MarketTimePoint end) const;
	std::vector<RawOptionRowQuote> getByDateRange(MarketTimePoint start, MarketTimePoint end) const;
	std::vector<RawOptionRowQuote> getByDate(MarketTimePoint date) const;
};


#endif
