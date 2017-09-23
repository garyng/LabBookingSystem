#pragma once
#include "storage/UserStorage.h"
#include <coveo/linq/linq.h>
#include "ICommand.h"

class UserLoginCommand
	: public ICommand
{
private:
	std::shared_ptr<UserStorage> _userStorage;
public:
	UserLoginCommand(const std::shared_ptr<UserStorage>& userStorage) : _userStorage(userStorage)
	{
	}


	bool Execute(std::string userName, std::string passwordHash)
	{
		using namespace coveo::linq;

		return _userStorage->Data()
			| where([&](User user) { return user.Name() == userName && user.HashedPassword() == passwordHash; })
			| any();
	}
};
