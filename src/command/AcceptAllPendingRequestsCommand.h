#pragma once
#include <memory>
#include <vector>
#include "models/Request.h"
#include "storage/RequestStorage.h"
#include "ICommand.h"

class AcceptAllPendingRequestsCommand
	: public ICommand
{
private:
	const std::shared_ptr<RequestStorage>& _requestStorage;
public:
	AcceptAllPendingRequestsCommand(const std::shared_ptr<RequestStorage>& requestStorage)
		: _requestStorage(requestStorage)
	{
	}

	void Execute(std::string reviewerId)
	{
		std::vector<Request> requests = _requestStorage->Data();
		for (Request& request : requests)
		{
			if (request.IsPending())
			{
				request.Status(RequestStatus::Accepted);
				request.ReviewerId(reviewerId);
			}
		}
		_requestStorage->Data(requests);
		_requestStorage->Save();
	}
};
