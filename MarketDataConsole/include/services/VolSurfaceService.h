#ifndef VolSurfaceService_H
#define VolSurfaceService_H

#include <memory>

#include "providers/OptionDataProvider.h"

// We can rely on many providers to create this service. The idea is we pull the necessary data for this service to function
class VolSurfaceService
{
private:
	std::unique_ptr<OptionDataProvider> optionDataProvider_;

public:
	explicit VolSurfaceService(std::unique_ptr<OptionDataProvider> optionDataProvider) :
		optionDataProvider_(std::move(optionDataProvider))
	{}

};

#endif