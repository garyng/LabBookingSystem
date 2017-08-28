#include "RequestViewModel.h"
#include <coveo/linq/linq.h>

using namespace std;
using namespace coveo::linq;

class GetUserIdFromUserNameQuery
{
private:
	std::shared_ptr<UserStorage> _userStorage;

public:
	explicit GetUserIdFromUserNameQuery(const std::shared_ptr<UserStorage>& userStorage)
		: _userStorage(userStorage)
	{
	}

	std::string Execute(std::string userName)
	{
		using namespace coveo::linq;
		User& result = _userStorage->Data()
			| first([&](User user) { return user.Name() == userName; });
		return result.Id();
	}
};

class GetRequestsByUserIdQuery
{
private:
	std::shared_ptr<RequestStorage> _requestStorage;
public:
	explicit GetRequestsByUserIdQuery(const std::shared_ptr<RequestStorage>& requestStorage)
		: _requestStorage(requestStorage)
	{
	}

	vector<Request> Execute(std::string userId)
	{
		return _requestStorage->Data()
			| where([&](Request request) { return request.UserId() == userId; })
			| to_vector();
	}
};

RequestViewModel::RequestViewModel(const std::shared_ptr<NavigationService>& navigation, const std::shared_ptr<UserStorage>& userStorage, const std::shared_ptr<RequestStorage>& requestStorage)
	: ViewModelBase(navigation), _requestStorage(requestStorage), _userStorage(userStorage)
{
}

void RequestViewModel::LoadUserRequestCommand()
{
	GetUserIdFromUserNameQuery userIdQuery(_userStorage);
	string userId = userIdQuery.Execute(_userName);

	GetRequestsByUserIdQuery requestQuery(_requestStorage);
	vector<Request> requests = requestQuery.Execute(userId);
	Requests(requests);
}
