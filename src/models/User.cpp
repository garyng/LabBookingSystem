#include "User.h"
#include <json.hpp>


User::User(const std::string& id, const std::string& name, const std::string& hashedPassword, const UserRole& role): _id(id),
                                                                                                                     _name(name),
                                                                                                                     _hashedPassword(hashedPassword),
                                                                                                                     _role(role._to_string())
{
}

void to_json(nlohmann::json& json, const User& user)
{
	json = nlohmann::json{
		{"Id", user.Id()},
		{"Name", user.Name()},
		{"HashedPassword", user.HashedPassword()},
		{"Role", user.Role()}
	};
}

void from_json(const nlohmann::json& json, User& user)
{
	user.Id(json.at("Id").get<std::string>());
	user.Name(json.at("Name").get<std::string>());
	user.HashedPassword(json.at("HashedPassword").get<std::string>());
	user.Role(UserRole::_from_string(
		json.at("Role")
		    .get<std::string>()
		    .c_str()));
}
