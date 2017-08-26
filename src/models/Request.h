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
	std::string _approverId;
	std::string _status;


public:
	int Id() const { return _id; }
	void Id(int value) { _id = value; }

	std::string LabId() const { return _labId; }
	void LabId(std::string value) { _labId = value; }

	std::string UserId() const { return _userId; }
	void UserId(std::string value) { _userId = value; }

	std::string ApproverId() const { return _approverId; }
	void ApproverId(std::string value) { _approverId = value; }

	std::string Status() const { return _status; }
	void Status(RequestStatus value) { _status = value._to_string(); }

	Request() = default;
	Request(int id, const RequestStatus& status, const std::string& labId, const std::string& userId, const std::string& approverId);
};

void to_json(nlohmann::json& json, const Request& user);
void from_json(const nlohmann::json& json, Request& user);