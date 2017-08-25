#pragma once
#include "JsonStorage.h"
#include "../models/User.h"

class UserStorage
	: public JsonStorage<User>
{
protected:
	std::vector<User> LoadDefault() override;
	std::string GetDataFilename() override;
};
