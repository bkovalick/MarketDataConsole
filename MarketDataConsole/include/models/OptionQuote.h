#ifndef OptionQuote_H
#define OptionQuote_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <memory>
#include <map>

#include "Types.h"

struct OptionQuote {
	double bid{}, ask{}, last{}, strike{};
	double impliedVol{};
	int64_t volume{}, openInterest{};
	std::string underlying, symbol;
	MarketTimePoint expiry;
};

struct StrikeLevel {
	double strike;
	OptionQuote call;
	OptionQuote put;
};

struct ExpirySlice {
	std::string expiry; 
	std::map<double, StrikeLevel> strikes;
};

#endif