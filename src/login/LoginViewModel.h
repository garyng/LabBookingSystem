#pragma once
#include "../ViewModelBase.h"
#include <string>

class LoginViewModel
	: public ViewModelBase
{
public:
	explicit LoginViewModel(const std::shared_ptr<NavigationService>& navigation);
	void LoginCommand(std::string userId, std::string userPassword) const;
};
