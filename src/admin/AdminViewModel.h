#pragma once
#include "../ViewModelBase.h"

class AdminViewModel
	: public ViewModelBase
{
private:
	std::string _userName;
public:
	std::string UserName() const { return _userName; }
	void UserName(std::string value) { _userName = value; }

	explicit AdminViewModel(const std::shared_ptr<NavigationService>& navigation);
	void LogoutCommand() const;
	void GoToRequestViewCommand() const;
};
