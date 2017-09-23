#pragma once
#include "storage/RequestStorage.h"
#include "query/GetUserIdFromUserNameQuery.h"

class ReviewViewModel
	: public ViewModelBase
{
private:
	std::shared_ptr<RequestStorage> _requestStorage;
	std::vector<Request> _allRequests;
	std::vector<Request> _requests;
	const std::shared_ptr<UserStorage>& _userStorage;

	std::string _adminUserName;
	bool _hasPendings;
	int _selectedIndex;
	int _selectedFilterIndex;

public:
	std::string AdminUserName() const { return _adminUserName; }
	void AdminUserName(std::string value) { _adminUserName = value; }


	std::vector<Request> Requests() const { return _requests; }
	void Requests(std::vector<Request> value) { _requests = value; }

	std::vector<Request> AllRequests() const { return _allRequests; }
	void AllRequests(std::vector<Request> value) { _allRequests = value; }

	bool HasPendings() const { return _hasPendings; }

	int SelectedIndex() const { return _selectedIndex; }
	void SelectedIndex(int value) { _selectedIndex = value; }

	int SelectedFilterIndex() const { return _selectedFilterIndex; }
	void SelectedFilterIndex(int value) { _selectedFilterIndex = value; }


	ReviewViewModel(const std::shared_ptr<NavigationService>& navigation,
	                const std::shared_ptr<RequestStorage>& requestStorage,
	                const std::shared_ptr<UserStorage>& userStorage)
		: ViewModelBase(navigation), _requestStorage(requestStorage), _userStorage(userStorage),
		  _hasPendings(false), _selectedIndex(-1), _selectedFilterIndex(0)
	{
	}

	void LoadAllRequestCommand();

	void FilterRequestsCommand();

	void AcceptAllPendingRequests();
	void RejectAllPendingRequests();
	void AcceptRequestCommand(int requestId);
	void RejectRequestCommand(int requestId);

	void Reset() override;

	std::string Name() override { return "ReviewViewModel"; }
};
