#pragma once
#include <memory>
#include <vector>
#include "coveo/linq.h"
#include "models/Request.h"
#include "storage/RequestStorage.h"
#include "IQuery.h"

class GetRequestsByUserIdQuery
	: public IQuery
{
private:
	std::shared_ptr<RequestStorage> _requestStorage;
public:
	explicit GetRequestsByUserIdQuery(const std::shared_ptr<RequestStorage>& requestStorage)
		: _requestStorage(requestStorage)
	{
	}

	std::vector<Request> Execute(std::string userId)
	{
		using namespace coveo::linq;

		return _requestStorage->Data()
			| where([&](Request request) { return request.UserId() == userId; })
			| to_vector();
	}
};
