#include "Lab.h"

Lab::Lab(const std::string& id, const std::string& description): _id(id),
                                                                 _description(description)
{
}

void to_json(nlohmann::json& json, const Lab& lab)
{
	json = nlohmann::json{
		{"Id", lab.Id()},
		{"Description", lab.Description()}
	};
}

void from_json(const nlohmann::json& json, Lab& lab)
{
	lab.Id(json.at("Id").get<std::string>());
	lab.Description(json.at("Description").get<std::string>());
}
