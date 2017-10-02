#include "stdafx.h"
#include "ReviewViewModel.h"
#include "query/GetAllRequestsQuery.h"
#include "command/AcceptAllPendingRequestsCommand.h"
#include "command/RejectAllPendingRequestsCommand.h"
#include "command/AcceptRequestByIdCommand.h"
#include "command/RejectRequestByIdCommand.h"

void ReviewViewModel::LoadAllRequestCommand()
{
	using namespace coveo::linq;

	GetAllRequestsQuery query{_requestStorage};
	_allRequests = query.Execute();
	_requests = _allRequests;

	_hasPendings = _allRequests
		| where([](Request r) { return r.IsPending(); })
		| any();

	FilterRequestsCommand();
}

void ReviewViewModel::FilterRequestsCommand()
{
	// {"Pending", "Accepted", "Rejected", "Cancelled", "All"};
	using namespace coveo::linq;

	SelectedIndex(-1);
	switch (_selectedFilterIndex)
	{
		case 0:
			_requests = _allRequests
				| where([](Request r) { return r.Status() == +RequestStatus::Pending; })
				| to_vector();
			break;
		case 1:
			_requests = _allRequests
				| where([](Request r) { return r.Status() == +RequestStatus::Accepted; })
				| to_vector();
			break;
		case 2:
			_requests = _allRequests
				| where([](Request r) { return r.Status() == +RequestStatus::Rejected; })
				| to_vector();
			break;
		case 3:
			_requests = _allRequests
				| where([](Request r) { return r.Status() == +RequestStatus::Cancelled; })
				| to_vector();
			break;
		case 4:
			_requests = _allRequests;
			break;
	}
}

void ReviewViewModel::AcceptAllPendingRequests()
{
	std::string adminUserName = AdminUserName();
	GetUserIdFromUserNameQuery query{_userStorage};
	std::string adminId = query.Execute(adminUserName);

	AcceptAllPendingRequestsCommand command{_requestStorage};
	command.Execute(adminId);
}

void ReviewViewModel::RejectAllPendingRequests()
{
	std::string adminUserName = AdminUserName();
	GetUserIdFromUserNameQuery query{_userStorage};
	std::string adminId = query.Execute(adminUserName);


	RejectAllPendingRequestsCommand command{_requestStorage};
	command.Execute(adminId);
}

void ReviewViewModel::AcceptRequestCommand(int requestId)
{
	AcceptRequestByIdCommand command{_requestStorage};
	command.Execute(requestId);
}

void ReviewViewModel::RejectRequestCommand(int requestId)
{
	RejectRequestByIdCommand command{_requestStorage};
	command.Execute(requestId);
}

void ReviewViewModel::Reset()
{
	_selectedIndex = -1;
	_selectedFilterIndex = 0;
}
