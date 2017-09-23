#pragma once
#include <memory>
#include <coveo/linq.h>
#include "models/Request.h"
#include "storage/RequestStorage.h"
#include "ICommand.h"

class CancelRequestByIdCommand
	: public ICommand
{
private:
	std::shared_ptr<RequestStorage> _requestStorage;
public:
	explicit CancelRequestByIdCommand(const std::shared_ptr<RequestStorage>& requestStorage)
		: _requestStorage(requestStorage)
	{
	}

	void Execute(int requestId)
	{
		using namespace coveo::linq;

		Request& result = _requestStorage->Data()
			| coveo::linq::first([&](Request request) { return request.Id() == requestId; });

		result.Status(RequestStatus::Cancelled);
		_requestStorage->Save();
	}
};
