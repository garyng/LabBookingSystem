#pragma once
#include <Poco/Data/Time.h>
#include <Poco/Data/Date.h>

BETTER_ENUM(RequestStatus, int, Pending, Accepted, Rejected, Cancelled);

namespace nlohmann
{
	using namespace Poco;

	template <>
	struct adl_serializer<DateTime>
	{
		static void to_json(json& j, const DateTime& date)
		{
			j = DateTimeFormatter::format(date, "%d/%m/%Y %h:%M %A");
		}

		static void from_json(const json& j, DateTime& date)
		{
			int timezone;
			date = DateTimeParser::parse("%d/%m/%Y %h:%M %A", j.get<std::string>(), timezone);
		}
	};
}

class Request
{
private:

	int _id;
	std::string _labId;
	std::string _userId;
	std::string _reviewerId;
	std::string _status;
	Poco::DateTime _startDateTime;
	Poco::DateTime _endDateTime;

public:

	int Id() const { return _id; }
	void Id(int value) { _id = value; }

	std::string LabId() const { return _labId; }
	void LabId(std::string value) { _labId = value; }

	std::string UserId() const { return _userId; }
	void UserId(std::string value) { _userId = value; }

	std::string ReviewerId() const { return _reviewerId; }
	void ReviewerId(std::string value) { _reviewerId = value; }


	std::string DateTimeFormat() const { return "%d/%m/%Y %h:%M %A"; }
	std::string DateFormat() const { return "%d/%m/%Y"; }
	std::string TimeFormat() const { return "%h:%M %A"; }

	Poco::DateTime StartDateTime() const { return _startDateTime; }
	void StartDateTime(Poco::DateTime value) { _startDateTime = value; }

	Poco::DateTime EndDateTime() const { return _endDateTime; }
	void EndDateTime(Poco::DateTime value) { _endDateTime = value; }

	Poco::Data::Date Date() const { return Poco::Data::Date{_startDateTime}; }
	Poco::Data::Time StartTime() const { return Poco::Data::Time{_startDateTime}; }
	Poco::Data::Time EndTime() const { return Poco::Data::Time{_endDateTime}; }

	std::string StartDateTimeFormatted() const { return Poco::DateTimeFormatter::format(_startDateTime, DateTimeFormat()); }
	std::string EndDateTimeFormatted() const { return Poco::DateTimeFormatter::format(_endDateTime, DateTimeFormat()); }
	std::string DateFormatted() const { return Poco::DateTimeFormatter::format(_startDateTime, DateFormat()); }
	std::string StartTimeFormatted() const { return Poco::DateTimeFormatter::format(_startDateTime, TimeFormat()); }
	std::string EndTimeFormatted() const { return Poco::DateTimeFormatter::format(_endDateTime, TimeFormat()); }

	RequestStatus Status() const { return RequestStatus::_from_string(_status.c_str()); }
	void Status(RequestStatus value) { _status = value._to_string(); }
	bool IsPending() const { return Status() == +RequestStatus::Pending; }
	bool IsCancelled() const { return Status() == +RequestStatus::Cancelled; }
	bool IsRejected() const { return Status() == +RequestStatus::Rejected; }
	bool IsAccepted() const { return Status() == +RequestStatus::Accepted; }
	bool WasReviewed() const { return Status() == +RequestStatus::Accepted || Status() == +RequestStatus::Rejected; }

	Request() = default;

	Request(int id, const std::string& labId, const std::string& userId, const std::string& reviewerId,
	        const Poco::DateTime& startDateTime, const Poco::DateTime& endDateTime,
	        const RequestStatus& status)
		: _id(id),
		  _labId(labId),
		  _userId(userId),
		  _reviewerId(reviewerId),
		  _startDateTime(startDateTime),
		  _endDateTime(endDateTime)
	{
		Status(status);
	}
};

void to_json(nlohmann::json& json, const Request& user);
void from_json(const nlohmann::json& json, Request& user);
