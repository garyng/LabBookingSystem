#pragma once
#include <memory>
#include "services/NavigationService.h"
#include "logger/Logger.h"


class ViewModelBase
{
protected:
	std::shared_ptr<NavigationService> _navigation;
	std::shared_ptr<ILogger> Log = Logger::Instance();

public:
	ViewModelBase(const std::shared_ptr<NavigationService>& navigation);
};
