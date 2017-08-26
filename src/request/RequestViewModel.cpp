#include "RequestViewModel.h"
#include <ctime>

RequestViewModel::RequestViewModel(const std::shared_ptr<NavigationService>& navigation): ViewModelBase(navigation)
{
	srand(static_cast<unsigned>(time(nullptr)));
	RequestStatus status[4] = {RequestStatus::Accepted, RequestStatus::Rejected, RequestStatus::Pending, RequestStatus::Cancelled};
	for (int i = 0; i < 100; i++)
	{
		Requests.emplace_back(new Request(i, "LAB0001", "0123", "0001", status[rand() % 4]));
	}
}
