#ifndef TickerDetails_H
#define TickerDetails_H

#include <iostream>
#include <memory>
#include <span>
#include <string>
#include <unordered_map>
#include <map>
#include <charconv>
#include <stdexcept>
#include <string_view>

#include "RawOptionRowQuote.h"

struct TickerDetails
{
	std::string symbol;      // underlying root, e.g. "AAPL"
	std::string expiration;  // ISO date, e.g. "2023-01-20"
	double strike{};
	bool isCall{};

	static TickerDetails parse_quote_details(const RawOptionRowQuote& rawQuote)
	{
		std::string_view s = rawQuote.symbol;

		// Strip the optional provider prefix ("O:") and surrounding spaces.
		if (s.starts_with("O:")) {
			s.remove_prefix(2);
		}
		while (!s.empty() && s.front() == ' ') s.remove_prefix(1);
		while (!s.empty() && s.back() == ' ') s.remove_suffix(1);

		// Minimum: 1 char root + 6 date + 1 type + 8 strike.
		constexpr size_t suffixLen = 6 + 1 + 8;
		if (s.size() < suffixLen + 1) {
			throw std::invalid_argument("Invalid option symbol: " + rawQuote.symbol);
		}

		const std::string_view root = s.substr(0, s.size() - suffixLen);
		const std::string_view date = s.substr(root.size(), 6);
		const char typeChar = s[root.size() + 6];
		const std::string_view strikeDigits = s.substr(root.size() + 7, 8);

		if (typeChar != 'C' && typeChar != 'P') {
			throw std::invalid_argument("Invalid option type in symbol: " + rawQuote.symbol);
		}

		long long strikeThousandths = 0;
		const auto [ptr, ec] = std::from_chars(
			strikeDigits.data(), strikeDigits.data() + strikeDigits.size(), strikeThousandths);
		if (ec != std::errc{} || ptr != strikeDigits.data() + strikeDigits.size()) {
			throw std::invalid_argument("Invalid strike in symbol: " + rawQuote.symbol);
		}

		for (char c : date) {
			if (c < '0' || c > '9') {
				throw std::invalid_argument("Invalid expiry in symbol: " + rawQuote.symbol);
			}
		}

		TickerDetails details;
		details.symbol.assign(root);
		details.expiration = "20" + std::string(date.substr(0, 2)) + "-"
			+ std::string(date.substr(2, 2)) + "-"
			+ std::string(date.substr(4, 2));
		details.strike = static_cast<double>(strikeThousandths) / 1000.0;
		details.isCall = (typeChar == 'C');
		return details;
	}
};

#endif