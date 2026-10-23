#ifndef RawOptionQuote_H
#define RawOptionQuote_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "Types.h"
#include "OptionQuote.h"

enum class OptionType { Call, Put };

struct RawOptionRowQuote {
    std::string underlying;
    std::string symbol;
    double strike{};
    MarketTimePoint expiry;
    double bid{}, ask{}, last{};
    double impliedVol{};
    int64_t volume{}, openInterest{};
    double spot{};
    MarketTimePoint asOf;
};

inline OptionQuote to_option_quote(RawOptionRowQuote&& raw)
{
	OptionQuote q;
	q.underlying = std::move(raw.underlying);
	q.symbol = std::move(raw.symbol);
	q.strike = raw.strike;
	q.expiry = raw.expiry;
	q.bid = raw.bid;
	q.ask = raw.ask;
	q.last = raw.last;
	q.impliedVol = raw.impliedVol;
	q.volume = raw.volume;
	q.openInterest = raw.openInterest;
	return q;
}

#endif