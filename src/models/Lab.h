#pragma once

class Lab
{
private:
	std::string _id;
	std::string _description;
public:

	std::string Id() const { return _id; }
	void Id(std::string value) { _id = value; }

	std::string Description() const { return _description; }
	void Description(std::string value) { _description = value; }

	Lab() = default;
	Lab(const std::string& id, const std::string& description);
};

void to_json(nlohmann::json& json, const Lab& lab);
void from_json(const nlohmann::json& json, Lab& lab);
