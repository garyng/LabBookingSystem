#pragma once
#include "RequestViewModel.h"
#include "ViewBase.h"

class RequestView
	: public ViewBase<RequestViewModel>
{
private:
	void RenderNoRequestsView();
	void RenderRequestView();
	void RenderRequestList() const;
	void RenderAddRequestButton() const;
	void RenderRequestDetails() const;
	void RenderCancelButton(int requestId) const;
	void RenderStatusLabel(const Request& request) const;
	void PrintValueLabel(std::string label, std::string value) const;
	void PrintValueLabel(std::string label, std::string value, const ImVec4& valueLabelForeground) const;

public:
	void Render() override;
	std::string Name() override { return "RequestView"; }
	explicit RequestView(const std::shared_ptr<RequestViewModel>& viewModel);
};
