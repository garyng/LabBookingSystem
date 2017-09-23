#pragma once
#include "ReviewViewModel.h"

class ReviewView
	: public ViewBase<ReviewViewModel>
{
public:
	ReviewView(const std::shared_ptr<ReviewViewModel>& viewModel)
		: ViewBase<ReviewViewModel>(viewModel)
	{
	}

	void Render() override;
	void RenderNoRequestsView();
	void RenderRequestView();
	void RenderRequestList();

	void RenderFilterByComboBox();
	void RenderAcceptAllButton();
	void RenderRejectAllButton();

	void RenderRequestDetails() const;
	void RenderAcceptButton(int requestId) const;
	void RenderRejectButton(int requestId) const;

	void RenderNoRequestSelected() const;
	void RenderStatusLabel(const Request& request) const;
	bool SelectableStyleButton(std::string text) const;

	std::string Name() override { return "ReviewView"; }
};
