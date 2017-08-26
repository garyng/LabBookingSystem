#include "RequestStorage.h"

std::vector<Request> RequestStorage::LoadDefault()
{
	return std::vector<Request>{
		{1, "LAB0015", "0013", "", RequestStatus::Pending},
		{2, "LAB0015", "0011", "0001", RequestStatus::Accepted},
		{3, "LAB0003", "0016", "", RequestStatus::Pending},
		{4, "LAB0011", "0007", "", RequestStatus::Pending},
		{5, "LAB0008", "0019", "", RequestStatus::Pending},
		{6, "LAB0004", "0019", "", RequestStatus::Pending},
		{7, "LAB0010", "0007", "0001", RequestStatus::Rejected},
		{8, "LAB0016", "0007", "0001", RequestStatus::Rejected},
		{9, "LAB0002", "0007", "0001", RequestStatus::Accepted},
		{10, "LAB0017", "0018", "0001", RequestStatus::Accepted},
		{11, "LAB0005", "0005", "0001", RequestStatus::Accepted},
		{12, "LAB0003", "0018", "0001", RequestStatus::Accepted},
		{13, "LAB0004", "0011", "", RequestStatus::Pending},
		{14, "LAB0015", "0004", "0001", RequestStatus::Rejected},
		{15, "LAB0014", "0004", "", RequestStatus::Pending},
		{16, "LAB0018", "0002", "0001", RequestStatus::Rejected},
		{17, "LAB0014", "0002", "", RequestStatus::Pending},
		{18, "LAB0007", "0002", "0001", RequestStatus::Accepted},
		{19, "LAB0003", "0002", "", RequestStatus::Pending},
		{20, "LAB0004", "0002", "", RequestStatus::Pending}
	};
}

std::string RequestStorage::GetDataFilename()
{
	return "requests.json";
}
