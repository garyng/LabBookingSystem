#pragma once
#include "../ViewBase.h"
#include "AdminViewModel.h"

class AdminView
	: public ViewBase<AdminViewModel>
{
public:
	explicit AdminView(const std::shared_ptr<AdminViewModel>& viewModel);
	void Render() override;
};
