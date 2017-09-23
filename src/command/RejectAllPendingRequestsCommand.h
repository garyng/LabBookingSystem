#pragma once
#include <memory>
#include <vector>
#include "models/Request.h"
#include "storage/RequestStorage.h"

class RejectAllPendingRequestsCommand
{
private:
	const std::shared_ptr<RequestStorage>& _requestStorage;
public:
	RejectAllPendingRequestsCommand(const std::shared_ptr<RequestStorage>& requestStorage)
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
				request.Status(RequestStatus::Rejected);
				request.ReviewerId(reviewerId);
			}
		}
		_requestStorage->Data(requests);
		_requestStorage->Save();
	}
};
