#pragma once
#include "SelectLabViewModel.h"

class SelectLabView
	: public ViewBase<SelectLabViewModel>
{
public:

	explicit SelectLabView(const std::shared_ptr<SelectLabViewModel>& viewModel);

	void Render() override;
	void RenderNoLabsView();
	void RenderLabView();
	void RenderLabList();
	void RenderLabDetails();
	void RenderSelectTimeButton();

	std::string Name() override { return "SelectLabView"; }
};
