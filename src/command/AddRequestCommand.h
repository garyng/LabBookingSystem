#pragma once
#include <memory>
#include "models/Request.h"
#include "storage/RequestStorage.h"
#include "ICommand.h"

class AddRequestCommand
	: public ICommand
{
private:
	std::shared_ptr<RequestStorage> _requestStorage;
public:

	AddRequestCommand(const std::shared_ptr<RequestStorage>& requestStorage)
		: _requestStorage(requestStorage)
	{
	}

	void Execute(std::string labId, std::string userId, Poco::Data::Date date, Poco::Data::Time startTime, Poco::Data::Time endTime)
	{
		using namespace std;
		using namespace coveo::linq;
		using namespace Poco;
		using namespace Data;

		Request lastRequest = _requestStorage->Data()
			| order_by_descending([](Request r) { return r.Id(); })
			| first();
		int newId = lastRequest.Id() + 1;

		Request request{newId, labId, userId, "",
			DateTime{date.year(), date.month(), date.day(), startTime.hour(), startTime.minute(), startTime.second()},
			DateTime{date.year(), date.month(), date.day(), endTime.hour(), endTime.minute(), endTime.second()} ,RequestStatus::Pending};
		_requestStorage->Data().push_back(request);
		_requestStorage->Save();
	}
};
