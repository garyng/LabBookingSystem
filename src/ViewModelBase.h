#pragma once
#include <memory>
#include "services/NavigationService.h"

class ViewModelBase
{
protected:
	std::shared_ptr<NavigationService> _navigation;

public:
	ViewModelBase(const std::shared_ptr<NavigationService>& navigation);
};
