#pragma once
#include "../ViewModelBase.h"

class UserViewModel
	: public ViewModelBase
{
private:
public:
	std::string _userName;
	std::string UserName() const { return _userName; }
	void UserName(std::string value) { _userName = value; }

	explicit UserViewModel(const std::shared_ptr<NavigationService>& navigation);
	void LogoutCommand() const;
};
