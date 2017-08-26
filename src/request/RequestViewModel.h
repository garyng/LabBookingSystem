#pragma once
#include "../ViewModelBase.h"
#include <vector>
#include "../models/Request.h"

class RequestViewModel
	: public ViewModelBase
{
public:
	std::vector<std::shared_ptr<Request>> Requests;
	explicit RequestViewModel(const std::shared_ptr<NavigationService>& navigation);
};
