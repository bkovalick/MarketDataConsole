#ifndef GenericTradingStrategy_H
#define GenericTradingStrategy_H

#include <memory>

#include "providers/OptionDataProvider.h"

class GenericTradingStrategy 
{

private:

public:
	explicit GenericTradingStrategy() {};

	~GenericTradingStrategy() = default;

	void runStrategy();

};

#endif