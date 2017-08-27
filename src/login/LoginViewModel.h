#pragma once
#include "../ViewModelBase.h"
#include <string>
#include "../storage/IStorage.h"
#include "../storage/UserStorage.h"

class LoginViewModel
	: public ViewModelBase
{
private:
	std::shared_ptr<UserStorage> _userStorage;

public:
	LoginViewModel(const std::shared_ptr<NavigationService>& navigation, const std::shared_ptr<UserStorage>& userStorage);
	bool LoginCommand(std::string userId, std::string userPassword) const;
};
