#pragma once
#include <memory>
#include <vector>
#include "models/Lab.h"
#include "storage/LabStorage.h"
#include "IQuery.h"

class GetAllLabsQuery
	: public IQuery
{
private:
	std::shared_ptr<LabStorage> _labStorage;

public:
	explicit GetAllLabsQuery(const std::shared_ptr<LabStorage>& labStorage)
		: _labStorage(labStorage)
	{
	}


	std::vector<Lab> Execute()
	{
		return _labStorage->Data();
	}
};
