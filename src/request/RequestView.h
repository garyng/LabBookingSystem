#pragma once
#include <memory>
#include "RequestViewModel.h"
#include "../ViewBase.h"
#include "imgui.h"

class RequestView
	: public ViewBase<RequestViewModel>
{
private:
	void RenderRequestList(char* searchBuffer, int& requestListSelectedIndex) const;
	void RenderRequestDetails(int requestListSelectedIndex) const;
	void PrintValueLabel(std::string label, std::string value) const;
	void PrintValueLabel(std::string label, std::string value, const ImVec4& valueLabelForeground) const;
	void RenderStatusLabel(const std::shared_ptr<Request>& request) const;

public:
	void Render() override;
	explicit RequestView(const std::shared_ptr<RequestViewModel>& viewModel);
};
