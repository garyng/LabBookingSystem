#include "RequestViewModel.h"
#include <ctime>

RequestViewModel::RequestViewModel(const std::shared_ptr<NavigationService>& navigation): ViewModelBase(navigation)
{
	srand(time(nullptr));
	for (int i = 0; i < 100; i++)
	{
		Requests.emplace_back(new Request(i, rand() % 100 < 33 ? RequestStatus::Accepted : (rand() % 100 < 50 ? RequestStatus::Rejected : RequestStatus::Pending)));
	}
}
