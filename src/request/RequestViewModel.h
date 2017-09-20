#pragma once
#include "ViewModelBase.h"
#include "models/Request.h"
#include "storage/RequestStorage.h"
#include "storage/UserStorage.h"

class RequestViewModel
	: public ViewModelBase
{
private:
	std::string _userName;
	std::vector<Request> _requests;
	int _selectedIndex;

	std::shared_ptr<RequestStorage> _requestStorage;
	std::shared_ptr<UserStorage> _userStorage;
public:
	std::string UserName() const { return _userName; }
	void UserName(std::string value) { _userName = value; }

	std::vector<Request> Requests() const { return _requests; }
	void Requests(std::vector<Request> value) { _requests = value; }

	int SelectedIndex() const { return _selectedIndex; }

	void SelectedIndex(int value) { _selectedIndex = value % _requests.size(); }

	void Reset() override
	{
		_selectedIndex = 0;
	}

	void LoadUserRequestCommand();
	void CancelRequestCommand(int requestId) const;
	void AddRequestCommand();

	explicit RequestViewModel(const std::shared_ptr<NavigationService>& navigation, const std::shared_ptr<UserStorage>& userStorage, const std::shared_ptr<RequestStorage>& requestStorage);
	std::string Name() override { return "RequestViewModel"; }
};
