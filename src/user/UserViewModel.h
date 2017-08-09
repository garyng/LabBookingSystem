#pragma once
#include "../ViewModelBase.h"

class UserViewModel
	: public ViewModelBase
{
public:
	std::string _userId;
	explicit UserViewModel(const std::shared_ptr<NavigationService>& navigation);
};
