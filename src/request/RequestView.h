#pragma once
#include <memory>
#include "RequestViewModel.h"
#include "../ViewBase.h"

class RequestView
	: public ViewBase<RequestViewModel>
{
public:
	void Render() override;
	explicit RequestView(const std::shared_ptr<RequestViewModel>& viewModel);
};
