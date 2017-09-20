﻿#include "stdafx.h"
#include "RequestView.h"
#include "AppFontIndex.h"
#include "AppColors.h"
#include "imgui/imgui_extra.h"


using namespace std;

RequestView::RequestView(const shared_ptr<RequestViewModel>& viewModel): ViewBase<RequestViewModel>(viewModel)
{
}

void RequestView::Render()
{
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
	ImGui::BeginDefaultCenteredResizableWindow("Request");

	if (ImGui::Selectable(ICON_MD_ARROW_BACK " Back"))
	{
		_viewModel->GoBackCommand();
	}

	if (_viewModel->Requests().size() > 0)
	{
		RenderRequestView();
	}
	else
	{
		RenderNoRequestsView();
	}

	ImGui::End();
}

void RequestView::RenderNoRequestsView()
{
	ImGui::PushFont(AppFontIndex::RobotoLight_Title);

	ImGui::BeginChildWithNBottomLineSpace("Centered Text", 1);
	{
		ImGui::CenteredTexts({"Much nothingness...", "Try to click on the " ICON_MD_ADD " New Request button!"});
	}
	ImGui::EndChild();

	ImGui::PopFont();
	RenderAddRequestButton();
}

void RequestView::RenderRequestView()
{
	ImGui::Columns(2);

	RenderRequestList();

	ImGui::NextColumn();

	RenderRequestDetails();
}


void RequestView::RenderRequestList() const
{
	ImGui::BeginChildWithNBottomLineSpace("RequestsList", 2);
	{
		for (size_t i = 0; i < _viewModel->Requests().size(); i++)
		{
			Request request = _viewModel->Requests().at(i);
			stringstream ss;
			ss << "#" << request.Id() << " "
				<< request.LabId()
				<< " - " << request.Status()._to_string();

			if (ImGui::Selectable(ss.str().c_str(), i == _viewModel->SelectedIndex()))
			{
				_viewModel->SelectedIndex(i);
			};
		}
	}
	ImGui::EndChild();

	const char* filterByItems[] = {"All", "Accepted", "Pending", "Rejected"};
	static int filterByCurrentItemIndex;
	{
		ImGui::Combo("Filter By", &filterByCurrentItemIndex, filterByItems, IM_ARRAYSIZE(filterByItems));
	}

	RenderAddRequestButton();
}

void RequestView::RenderAddRequestButton() const
{
	ImGui::FullWidthButton(ICON_MD_ADD " New Request");
	// todo: new request
}

void RequestView::RenderRequestDetails() const
{
	Request request = _viewModel->Requests().at(_viewModel->SelectedIndex());
	ImGui::BeginChildWithNBottomLineSpace("RequestDetails", 1);
	{
		ImGui::PushFont(AppFontIndex::RobotoLight_Title);
		string title = "Request #" + to_string(request.Id());
		ImGui::Text(title.c_str());
		ImGui::PopFont();
		ImGui::Separator();

		PrintValueLabel("Lab Id:", request.LabId());

		RenderStatusLabel(request);

		if (request.WasReviewed())
		{
			PrintValueLabel("Reviewed by:", request.ReviewerId());
		}
	}
	ImGui::EndChild();
	if (request.IsPending())
	{
		RenderCancelButton(request.Id());
	}
}

void RequestView::RenderCancelButton(int requestId) const
{
	if (ImGui::FullWidthButton(ICON_MD_CLOSE " Cancel Request"))
	{
		ImGui::OpenPopup("Are you sure?");
	}
	ImGui::OkCancelPopupModal("Are you sure?", ICON_MD_WARNING,
	                          {
		                          "Do you want to cancel this request?"
	                          }, [&]()
                          {
	                          _viewModel->CancelRequestCommand(requestId);
                          });
	_viewModel->LoadUserRequestCommand();
}

void RequestView::RenderStatusLabel(const Request& request) const
{
	ImVec4 color;
	switch (request.Status())
	{
		case RequestStatus::Rejected:
			color = AppColors::Red500;
			break;
		case RequestStatus::Pending:
			color = AppColors::Yellow500;
			break;
		case RequestStatus::Accepted:
			color = AppColors::Green500;
			break;
		case RequestStatus::Cancelled:
			color = AppColors::DefaultWhite;
			break;
	}
	PrintValueLabel("Status:", request.Status()._to_string(), color);
}

void RequestView::PrintValueLabel(string label, string value) const
{
	ImGui::PushFont(AppFontIndex::RobotoBold_Normal);
	ImGui::Text(label.c_str());
	ImGui::PopFont();
	ImGui::Text(value.c_str());
}

void RequestView::PrintValueLabel(string label, string value, const ImVec4& valueLabelForeground) const
{
	ImGui::PushFont(AppFontIndex::RobotoBold_Normal);
	ImGui::Text(label.c_str());
	ImGui::PopFont();
	ImGui::TextColored(valueLabelForeground, value.c_str());
}
