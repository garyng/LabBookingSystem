#pragma once
#include <memory>
#include <vector>
#include "models/Request.h"
#include "storage/RequestStorage.h"

class GetAllRequestsQuery
{
private:
	const std::shared_ptr<RequestStorage>& _requestStorage;

public:
	GetAllRequestsQuery(const std::shared_ptr<RequestStorage>& requestStorage)
		: _requestStorage(requestStorage)
	{
	}

	std::vector<Request> Execute()
	{
		return _requestStorage->Data();
	}
};
