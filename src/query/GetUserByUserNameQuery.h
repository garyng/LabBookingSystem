#pragma once
#include <optional>
#include <coveo/linq/linq.h>
#include "../storage/UserStorage.h"
#include "../models/User.h"

class GetUserByUserNameQuery
{
private:
	std::shared_ptr<UserStorage> _userStorage;

public:
	GetUserByUserNameQuery(const std::shared_ptr<UserStorage>& userStorage) : _userStorage(userStorage)
	{
	}

	std::optional<User> Execute(std::string userName)
	{
		using namespace coveo::linq;

		if (_userStorage->Data()
			| coveo::linq::where([&](User user) { return user.Name() == userName; })
			| any())
		{
			return _userStorage->Data()
				| first([&](User user) { return user.Name() == userName; });
		}
		return {};
	}
};
