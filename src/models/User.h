#pragma once

BETTER_ENUM(UserRole, int, Admin, Normal);

class User
{
private:
	std::string _id;
	std::string _name;
	std::string _hashedPassword;
	std::string _role;

public:

	std::string Id() const { return _id; }
	void Id(std::string value) { _id = value; }

	std::string Name() const { return _name; }
	void Name(std::string value) { _name = value; }

	std::string HashedPassword() const { return _hashedPassword; }
	void HashedPassword(std::string hashedPassword) { _hashedPassword = hashedPassword; }

	UserRole Role() const { return UserRole::_from_string(_role.c_str()); }
	void Role(UserRole role) { _role = role._to_string(); }
	bool IsAdmin() const { return Role() == +UserRole::Admin; }

	User() = default;
	User(const std::string& id, const std::string& name, const std::string& hashedPassword, const UserRole& role);
};

void to_json(nlohmann::json& json, const User& user);
void from_json(const nlohmann::json& json, User& user);
