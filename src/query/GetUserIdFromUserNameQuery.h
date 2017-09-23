#pragma once
#include <memory>
#include <string>
#include "models/User.h"
#include "storage/UserStorage.h"
#include "coveo/linq.h"
#include "IQuery.h"

class GetUserIdFromUserNameQuery
	: public IQuery
{
private:
	std::shared_ptr<UserStorage> _userStorage;

public:
	explicit GetUserIdFromUserNameQuery(const std::shared_ptr<UserStorage>& userStorage)
		: _userStorage(userStorage)
	{
	}

	std::string Execute(std::string userName)
	{
		using namespace coveo::linq;

		User& result = _userStorage->Data()
			| first([&](User user) { return user.Name() == userName; });
		return result.Id();
	}
};

