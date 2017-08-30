#pragma once
#include <memory>
#include "RequestViewModel.h"
#include "../ViewBase.h"
#include "imgui.h"

class RequestView
	: public ViewBase<RequestViewModel>
{
private:
	void RenderNoRequestsView();
	void RenderRequestView();
	void RenderRequestList(char* searchBuffer, int& requestListSelectedIndex) const;
	void RenderAddRequestButton() const;
	void RenderRequestDetails(int requestListSelectedIndex) const;
	void RenderStatusLabel(const Request& request) const;
	void PrintValueLabel(std::string label, std::string value) const;
	void PrintValueLabel(std::string label, std::string value, const ImVec4& valueLabelForeground) const;

public:
	void Render() override;
	std::string Name() override { return "RequestView"; }
	explicit RequestView(const std::shared_ptr<RequestViewModel>& viewModel);
};
