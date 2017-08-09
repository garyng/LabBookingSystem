#pragma once
#include "../ViewModelBase.h"

class AdminViewModel
	: public ViewModelBase
{
public:
	explicit AdminViewModel(const std::shared_ptr<NavigationService>& navigation);
};
