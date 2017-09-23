#pragma once
#include <memory>
#include "models/Request.h"
#include "storage/RequestStorage.h"
#include "ICommand.h"

class RejectRequestByIdCommand
	: public ICommand
{
private:
	std::shared_ptr<RequestStorage> _requestStorage;
public:
	explicit RejectRequestByIdCommand(const std::shared_ptr<RequestStorage>& requestStorage)
		: _requestStorage(requestStorage)
	{
	}

	void Execute(int requestId)
	{
		using namespace coveo::linq;

		Request& result = _requestStorage->Data()
			| coveo::linq::first([&](Request request) { return request.Id() == requestId; });

		result.Status(RequestStatus::Rejected);
		_requestStorage->Save();
	}
};
