#include "stdafx.h"
#include "Request.h"

void to_json(nlohmann::json& json, const Request& request)
{
	json = nlohmann::json{
		{"Id", request.Id()},
		{"LabId", request.LabId()},
		{"UserId", request.UserId()},
		{"ReviewerId", request.ReviewerId()},
		{"StartDateTime", request.StartDateTime()},
		{"EndDateTime", request.EndDateTime()},
		{"Status", request.Status()._to_string()},
	};
}

void from_json(const nlohmann::json& json, Request& request)
{
	request.Id(json.at("Id").get<int>());
	request.LabId(json.at("LabId").get<std::string>());
	request.UserId(json.at("UserId").get<std::string>());
	request.ReviewerId(json.at("ReviewerId").get<std::string>());
	request.StartDateTime(json.at("StartDateTime").get<Poco::DateTime>());
	request.EndDateTime(json.at("EndDateTime").get<Poco::DateTime>());
	request.Status(RequestStatus::_from_string(
			json.at("Status")
			    .get<std::string>()
			    .c_str())
	);
}
