#include "stdafx.h"
#include "RequestStorage.h"

using namespace std;
using namespace date;

std::vector<Request> RequestStorage::LoadDefault()
{
	sys_days date1 = day{ 15 } / date::oct / 2017;
	sys_days date2 = day{ 16 } / date::oct / 2017;
	sys_days date3 = day{ 17 } / date::oct / 2017;
	sys_days date4 = day{ 18 } / date::oct / 2017;

	return vector<Request>{
		{ 1, "LAB0001", "0021", "", date1, date1 + 8h, date1 + 10h, RequestStatus::Cancelled },
		{ 2, "LAB0001", "0021", "0001", date1, date1 + 8h + 30min, date1 + 12h, RequestStatus::Accepted },
		{ 3, "LAB0001", "0022", "", date1, date1 + 13h, date1 + 15h, RequestStatus::Pending },
		{ 4, "LAB0001", "0022", "0001", date1, date1 + 19h, date1 + 20h, RequestStatus::Rejected },
		{ 5, "LAB0001", "0021", "", date2, date2 + 13h, date2 + 15h, RequestStatus::Pending },
		{ 6, "LAB0001", "0021", "0001", date2, date2 + 8h, date2 + 20h, RequestStatus::Rejected },
		{ 7, "LAB0001", "0022", "0001", date3, date3 + 8h , date3 + 10h, RequestStatus::Cancelled },
		{ 8, "LAB0001", "0022", "0001", date3, date3 + 8h + 30min, date3 + 12h, RequestStatus::Accepted },
		{ 9, "LAB0001", "0022", "0001", date3, date3 + 13h, date3 + 15h, RequestStatus::Pending },
		{ 10, "LAB0001", "0022", "0001", date3, date3 + 19h, date3 + 20h, RequestStatus::Rejected },
		{ 11, "LAB0001", "0022", "0001", date4, date4 + 13h, date4 + 15h, RequestStatus::Pending },
		{ 12, "LAB0001", "0022", "0001", date4, date4 + 8h, date4 + 20h, RequestStatus::Rejected }

	};
}

std::string RequestStorage::GetDataFilename()
{
	return "requests.json";
}
