#ifndef OptionChain_H
#define OptionChain_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "OptionQuote.h"
#include "Types.h"

struct OptionChain {
	std::string underlying;
	double spot;
	MarketTimePoint asOf;
	std::vector<ExpirySlice> slices;
};

#endif