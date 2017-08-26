#pragma once
#include <string>
#include <enum.h>
#include <json.hpp>

BETTER_ENUM(RequestStatus, int, Pending, Accepted, Rejected);

class Request
{
private:
	int _id;
	std::string _labId;
	std::string _userId;
	std::string _reviewerId;
	std::string _status;


public:
	int Id() const { return _id; }
	void Id(int value) { _id = value; }

	std::string LabId() const { return _labId; }
	void LabId(std::string value) { _labId = value; }

	std::string UserId() const { return _userId; }
	void UserId(std::string value) { _userId = value; }

	std::string ReviewerId() const { return _reviewerId; }
	void ReviewerId(std::string value) { _reviewerId = value; }

	RequestStatus Status() const { return RequestStatus::_from_string(_status.c_str()); }
	void Status(RequestStatus value) { _status = value._to_string(); }

	Request() = default;
	Request(int id, const std::string& labId, const std::string& userId, const std::string& reviewerId, const RequestStatus& status);
};

void to_json(nlohmann::json& json, const Request& user);
void from_json(const nlohmann::json& json, Request& user);