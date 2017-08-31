#pragma once
#include "services/NavigationService.h"
#include "logger/Logger.h"
#include "IViewModel.h"

class ViewModelBase
	: public IViewModel
{
protected:
	std::shared_ptr<NavigationService> _navigation;
	std::shared_ptr<ILogger> Log = Logger::Instance();

public:
	ViewModelBase(const std::shared_ptr<NavigationService>& navigation): _navigation(navigation)
	{
	}

	void GoBackCommand() const
	{
		_navigation->GoBack();
	}

	void Reset() override
	{
		// Do noting by default
	}
};
