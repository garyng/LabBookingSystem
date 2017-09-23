#pragma once
#include <memory>
#include <coveo/linq.h>
#include "models/Request.h"
#include "storage/RequestStorage.h"
#include "IQuery.h"

class GetAllRequestByLabIdQuery
	: public IQuery
{
private:
	std::shared_ptr<RequestStorage> _requestStorage;
public:
	explicit GetAllRequestByLabIdQuery(const std::shared_ptr<RequestStorage>& requestStorage)
		: _requestStorage(requestStorage)
	{
	}

	std::vector<Request> Execute(std::string labId)
	{
		using namespace coveo::linq;

		return _requestStorage->Data()
			| where([&](Request r) { return r.LabId() == labId; })
			| to_vector();
	}
};
