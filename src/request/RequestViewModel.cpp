#include "stdafx.h"
#include "RequestViewModel.h"
#include "query/GetRequestsByUserIdQuery.h"
#include "query/GetUserIdFromUserNameQuery.h"
#include "command/CancelRequestByIdCommand.h"
#include "SelectLabViewModel.h"

using namespace std;
using namespace coveo::linq;

RequestViewModel::RequestViewModel(const std::shared_ptr<NavigationService>& navigation, const std::shared_ptr<UserStorage>& userStorage, const std::shared_ptr<RequestStorage>& requestStorage)
	: ViewModelBase(navigation), _selectedIndex(-1), _requestStorage(requestStorage),
	  _userStorage(userStorage), _selectedFilterIndex(0)
{
}

void RequestViewModel::Reset()
{
	_selectedIndex = -1;
	_selectedFilterIndex = 0;
}

void RequestViewModel::LoadUserRequestCommand()
{
	GetUserIdFromUserNameQuery userIdQuery(_userStorage);
	string userId = userIdQuery.Execute(_userName);

	GetRequestsByUserIdQuery requestQuery(_requestStorage);
	vector<Request> requests = requestQuery.Execute(userId);

	_allRequests = requests;
	_requests = requests;
	FilterRequestsCommand();
}

void RequestViewModel::CancelRequestCommand(int requestId) const
{
	CancelRequestByIdCommand command(_requestStorage);
	command.Execute(requestId);
}

void RequestViewModel::AddRequestCommand()
{
	_navigation->GoTo<SelectLabViewModel>([&](shared_ptr<SelectLabViewModel> vm)
                                      {
	                                      vm->LoadAllLabsCommand();
	                                      vm->UserName(_userName);
                                      }, true);
}

void RequestViewModel::FilterRequestsCommand()
{
	// {"All", "Accepted", "Pending", "Rejected"}
	SelectedIndex(-1);
	switch (_selectedFilterIndex)
	{
		case 0:
			_requests = _allRequests;
			break;
		case 1:
			_requests = _allRequests
				| where([](Request r) { return r.Status() == +RequestStatus::Accepted; })
				| to_vector();
			break;
		case 2:
			_requests = _allRequests
				| where([](Request r) { return r.Status() == +RequestStatus::Pending; })
				| to_vector();
			break;
		case 3:
			_requests = _allRequests
				| where([](Request r) { return r.Status() == +RequestStatus::Rejected; })
				| to_vector();
			break;
	}
}
