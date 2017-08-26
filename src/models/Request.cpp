#include "Request.h"

Request::Request(int id, const std::string& labId, const std::string& userId, const std::string& reviewerId, const RequestStatus& status): _id(id),
                                                                                                                                         _labId(labId),
                                                                                                                                         _userId(userId),
                                                                                                                                         _reviewerId(reviewerId),
                                                                                                                                         _status(status._to_string())
{
}

void to_json(nlohmann::json& json, const Request& request)
{
	json = nlohmann::json{
		{"Id", request.Id()},
		{"LabId", request.LabId()},
		{"UserId", request.UserId()},
		{"ReviewerId", request.ReviewerId()},
		{"Status", request.Status()._to_string()}
	};
}

void from_json(const nlohmann::json& json, Request& request)
{
	request.Id(json.at("Id").get<int>());
	request.LabId(json.at("LabId").get<std::string>());
	request.UserId(json.at("UserId").get<std::string>());
	request.ReviewerId(json.at("ReviewerId").get<std::string>());
	request.Status(RequestStatus::_from_string(
			json.at("Status")
			    .get<std::string>()
			    .c_str())
	);
}
