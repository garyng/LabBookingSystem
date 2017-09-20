#pragma once
#include "date/date_extra.h"

BETTER_ENUM(RequestStatus, int, Pending, Accepted, Rejected, Cancelled);

class Request
{
private:

	int _id;
	std::string _labId;
	std::string _userId;
	std::string _reviewerId;
	std::string _date;
	std::string _startTime;
	std::string _endTime;
	std::string _status;


	std::string FromTime(date::sys_time<std::chrono::minutes> time) const
	{
		return date::format("%H:%M", time);
	}

	date::sys_time<std::chrono::minutes> ToTime(std::string time) const
	{
		return date::parse_string<date::sys_time<std::chrono::minutes>>("%H:%M", _startTime);
	}

	std::string FromDate(date::sys_days value) const
	{
		return date::format("%d/%m/%Y", value);
	}

	date::sys_days ToDate(std::string date) const
	{
		return date::parse_string<date::sys_days>("%d/%m/%Y", date);
	}

	friend void to_json(nlohmann::json& json, const Request& user);
	friend void from_json(const nlohmann::json& json, Request& user);

public:

	int Id() const { return _id; }
	void Id(int value) { _id = value; }

	std::string LabId() const { return _labId; }
	void LabId(std::string value) { _labId = value; }

	std::string UserId() const { return _userId; }
	void UserId(std::string value) { _userId = value; }

	std::string ReviewerId() const { return _reviewerId; }
	void ReviewerId(std::string value) { _reviewerId = value; }

	date::sys_days Date() const { return ToDate(_date); }
	void Date(date::sys_days value) { _date = FromDate(value); }

	date::sys_time<std::chrono::minutes> StartTime() const { return ToTime(_startTime); }
	void StartTime(date::sys_time<std::chrono::minutes> value) { _startTime = FromTime(value); }

	date::sys_time<std::chrono::minutes> EndTime() const { return ToTime(_endTime); }
	void EndTime(date::sys_time<std::chrono::minutes> value) { _endTime = FromTime(value); }

	RequestStatus Status() const { return RequestStatus::_from_string(_status.c_str()); }
	void Status(RequestStatus value) { _status = value._to_string(); }
	bool IsPending() const { return Status() == +RequestStatus::Pending; }
	bool IsCancelled() const { return Status() == +RequestStatus::Cancelled; }
	bool IsAccepted() const { return Status() == +RequestStatus::Accepted; }
	bool WasReviewed() const { return Status() == +RequestStatus::Accepted || Status() == +RequestStatus::Rejected; }

	Request() = default;

	Request(int id, const std::string& labId, const std::string& userId, const std::string& reviewerId,
	        const date::sys_days& date, const date::sys_time<std::chrono::minutes>& startTime, const date::sys_time<std::chrono::minutes>& endTime,
	        const RequestStatus& status)
		: _id(id),
		  _labId(labId),
		  _userId(userId),
		  _reviewerId(reviewerId)
	{
		_date = FromDate(date);
		_startTime = FromTime(startTime);
		_endTime = FromTime(endTime);
		_status = status._to_string();
	}
};

void to_json(nlohmann::json& json, const Request& user);
void from_json(const nlohmann::json& json, Request& user);
