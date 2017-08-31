#pragma once
#include "ViewModelBase.h"
#include "storage/UserStorage.h"

class LoginViewModel
	: public ViewModelBase
{
private:
	std::string _userId;
	std::string _userPassword;

	std::shared_ptr<UserStorage> _userStorage;

public:
	std::string UserId() const { return _userId; }
	void UserId(std::string value) { _userId = value; }

	std::string UserPassword() const { return _userPassword; }
	void UserPassword(std::string value) { _userPassword = value; }

	void Reset() override
	{
		_userPassword = "";
	}

	LoginViewModel(const std::shared_ptr<NavigationService>& navigation, const std::shared_ptr<UserStorage>& userStorage);
	bool LoginCommand(std::string userId, std::string userPassword) const;
	
	std::string Name() override { return "LoginViewModel"; }
};
