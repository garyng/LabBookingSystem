#include "stdafx.h"
#include "Request.h"

void to_json(nlohmann::json& json, const Request& request)
{
	json = nlohmann::json{
		{"Id", request.Id()},
		{"LabId", request.LabId()},
		{"UserId", request.UserId()},
		{"ReviewerId", request.ReviewerId()},
		{"Date", request.DateAsString()},
		{"StartTime", request.StartTimeAsString()},
		{"EndTime", request.EndTimeAsString()},
		{"Status", request.Status()._to_string()}
	};
}

void from_json(const nlohmann::json& json, Request& request)
{
	request.Id(json.at("Id").get<int>());
	request.LabId(json.at("LabId").get<std::string>());
	request.UserId(json.at("UserId").get<std::string>());
	request.ReviewerId(json.at("ReviewerId").get<std::string>());
	request.Date(json.at("Date").get<std::string>());
	request.StartTime(json.at("StartTime").get<std::string>());
	request.EndTime(json.at("EndTime").get<std::string>());
	request.Status(RequestStatus::_from_string(
			json.at("Status")
			    .get<std::string>()
			    .c_str())
	);
}
