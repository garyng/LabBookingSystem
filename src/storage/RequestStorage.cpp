#include "stdafx.h"
#include "RequestStorage.h"

using namespace std;
using namespace Poco;

vector<Request> RequestStorage::LoadDefault()
{
	DateTime date1{2017,11,15};
	DateTime date2{2017,11,16};
	DateTime date3{2017,11,17};
	DateTime date4{2017,11,18};

	return vector<Request>{
		{1, "LAB0001", "0021", "", date1 + 8 * Timespan::HOURS, date1 + 10 * Timespan::HOURS, RequestStatus::Cancelled},
		{2, "LAB0001", "0021", "0001", date1 + 8 * Timespan::HOURS + 30 * Timespan::MINUTES, date1 + 12 * Timespan::HOURS, RequestStatus::Accepted},
		{3, "LAB0001", "0022", "", date1 + 13 * Timespan::HOURS, date1 + 15 * Timespan::HOURS, RequestStatus::Pending},
		{4, "LAB0001", "0022", "0001", date1 + 19 * Timespan::HOURS, date1 + 20 * Timespan::HOURS, RequestStatus::Rejected},
		{5, "LAB0001", "0021", "", date2 + 13 * Timespan::HOURS, date2 + 15 * Timespan::HOURS, RequestStatus::Pending},
		{6, "LAB0001", "0021", "0001", date2 + 8 * Timespan::HOURS, date2 + 20 * Timespan::HOURS, RequestStatus::Rejected},
		{7, "LAB0001", "0022", "0001", date3 + 8 * Timespan::HOURS , date3 + 10 * Timespan::HOURS, RequestStatus::Cancelled},
		{8, "LAB0001", "0022", "0001", date3 + 8 * Timespan::HOURS + 30 * Timespan::MINUTES, date3 + 12 * Timespan::HOURS, RequestStatus::Accepted},
		{9, "LAB0001", "0022", "0001", date3 + 13 * Timespan::HOURS, date3 + 15 * Timespan::HOURS, RequestStatus::Pending},
		{10, "LAB0001", "0022", "0001", date3 + 19 * Timespan::HOURS, date3 + 20 * Timespan::HOURS, RequestStatus::Rejected},
		{11, "LAB0001", "0022", "0001", date4 + 13 * Timespan::HOURS, date4 + 15 * Timespan::HOURS, RequestStatus::Pending},
		{12, "LAB0001", "0022", "0001", date4 + 8 * Timespan::HOURS, date4 + 20 * Timespan::HOURS, RequestStatus::Rejected}

	};
}

string RequestStorage::GetDataFilename()
{
	return "requests.json";
}
