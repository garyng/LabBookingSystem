#include "stdafx.h"
#include "ReviewView.h"
#include "imgui/imgui_extra.h"

void ReviewView::Render()
{
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
	ImGui::BeginDefaultCenteredResizableWindow("Review");

	if (ImGui::Selectable(ICON_MD_ARROW_BACK " Back"))
	{
		_viewModel->GoBackCommand();
	}
	if (_viewModel->AllRequests().size() > 0)
	{
		RenderRequestView();
	}
	else
	{
		RenderNoRequestsView();
	}

	ImGui::End();
}

void ReviewView::RenderNoRequestsView()
{
	ImGui::PushFont(AppFontIndex::RobotoLight_Title1);

	ImGui::BeginChildWithNBottomLineSpace("Centered Text", 1);
	{
		ImGui::CenteredTexts({ICON_MD_BLUR_ON ,"Nothing to show.."});
	}
	ImGui::EndChild();

	ImGui::PopFont();
}

void ReviewView::RenderRequestView()
{
	ImGui::Columns(2);

	RenderRequestList();

	ImGui::NextColumn();

	RenderRequestDetails();
}

void ReviewView::RenderRequestList()
{
	ImGui::BeginChildWithNBottomLineSpace("RequestList", _viewModel->HasPendings() ? 3 : 1);
	{
		if (_viewModel->Requests().size() == 0)
		{
			ImGui::PushFont(AppFontIndex::RobotoLight_Title1);
			ImGui::CenteredTexts({"Nothing here..."});
			ImGui::PopFont();
		}
		else
		{
			int i = 0;
			for (Request& request : _viewModel->Requests())
			{
				std::stringstream ss;
				ss << "#" << request.Id() << " "
					<< request.LabId()
					<< " - " << request.Status()._to_string();

				if (ImGui::Selectable(ss.str().c_str(), i == _viewModel->SelectedIndex()))
				{
					_viewModel->SelectedIndex(i);
				};
				i++;
			}
		}
	}
	ImGui::EndChild();

	RenderFilterByComboBox();
	if (_viewModel->HasPendings())
	{
		RenderAcceptAllButton();
		RenderRejectAllButton();
	}
}

void ReviewView::RenderFilterByComboBox()
{
	const char* filterByItems[] = {"Pending", "Accepted", "Rejected", "All"};
	int filterByCurrentItemIndex = _viewModel->SelectedFilterIndex();

	if (ImGui::Combo(ICON_MD_FILTER_LIST " Filter By", &filterByCurrentItemIndex, filterByItems, IM_ARRAYSIZE(filterByItems)))
	{
		_viewModel->SelectedFilterIndex(filterByCurrentItemIndex);
		_viewModel->FilterRequestsCommand();
	}
}

void ReviewView::RenderAcceptAllButton()
{
	if (ImGui::FullWidthButton(ICON_MD_DONE_ALL " Accept All"))
	{
		ImGui::OpenPopup("Are you sure?##AcceptAll");
	}
	ImGui::OkCancelPopupModal("Are you sure?##AcceptAll", ICON_MD_INFO_OUTLINE, {
		                          "Accept all pending requests?"}, [&]()
                          {
	                          _viewModel->AcceptAllPendingRequests();
	                          _viewModel->LoadAllRequestCommand();
                          });
}

void ReviewView::RenderRejectAllButton()
{
	if (ImGui::FullWidthButton(ICON_MD_CLOSE " Reject All"))
	{
		ImGui::OpenPopup("Are you sure?##Reject All");
	}
	ImGui::OkCancelPopupModal("Are you sure?##Reject All", ICON_MD_INFO_OUTLINE, {
		                          "Reject all pending requests?"}, [&]()
                          {
	                          _viewModel->RejectAllPendingRequests();
	                          _viewModel->LoadAllRequestCommand();
                          });
}

void ReviewView::RenderRequestDetails() const
{
	int selectedIndex = _viewModel->SelectedIndex();

	if (selectedIndex < 0 || selectedIndex > _viewModel->Requests().size())
	{
		RenderNoRequestSelected();
		return;
	}

	Request request = _viewModel->Requests().at(selectedIndex);
	ImGui::BeginChildWithNBottomLineSpace("RequestDetails", request.IsPending() ? 2 : 0);
	{
		ImGui::PushFont(AppFontIndex::RobotoLight_Title1);
		std::string title = "Request #" + std::to_string(request.Id());
		ImGui::Text(title.c_str());
		ImGui::PopFont();
		ImGui::Separator();

		ImGui::PrintValueLabel("Lab Id:", request.LabId());
		ImGui::PrintValueLabel("Requested by:", request.UserId());

		RenderStatusLabel(request);

		if (request.WasReviewed())
		{
			ImGui::PrintValueLabel("Reviewed by:", request.ReviewerId());
		}

		ImGui::PrintValueLabel("Date:", request.DateFormatted());

		std::string time = request.StartTimeFormatted() + " - " + request.EndTimeFormatted();
		ImGui::PrintValueLabel("Time:", time);
	}
	ImGui::EndChild();
	if (request.IsPending())
	{
		RenderAcceptButton(request.Id());
		RenderRejectButton(request.Id());
	}
}

void ReviewView::RenderAcceptButton(int requestId) const
{
	if (SelectableStyleButton(ICON_MD_DONE " Accept"))
	{
		ImGui::OpenPopup("Are you sure?##Accept");
	}
	ImGui::OkCancelPopupModal("Are you sure?##Accept", ICON_MD_INFO_OUTLINE, {
		                          "Accept request #" + std::to_string(requestId) + "?"}, [&]()
                          {
	                          _viewModel->AcceptRequestCommand(requestId);
	                          _viewModel->LoadAllRequestCommand();
                          });
}

void ReviewView::RenderRejectButton(int requestId) const
{
	if (SelectableStyleButton(ICON_MD_REMOVE " Reject"))
	{
		ImGui::OpenPopup("Are you sure?##Reject");
	}
	ImGui::OkCancelPopupModal("Are you sure?##Reject", ICON_MD_INFO_OUTLINE, {
		                          "Reject request #" + std::to_string(requestId) + "?"}, [&]()
                          {
	                          _viewModel->RejectRequestCommand(requestId);
	                          _viewModel->LoadAllRequestCommand();
                          });
}

void ReviewView::RenderNoRequestSelected() const
{
	ImGui::PushFont(AppFontIndex::RobotoLight_Title1);

	ImGui::BeginChildWithNBottomLineSpace("Centered Text", 1);
	{
		ImGui::CenteredTexts({"Nothing to show"});
	}
	ImGui::EndChild();

	ImGui::PopFont();
}

void ReviewView::RenderStatusLabel(const Request& request) const
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
	ImGui::PrintValueLabel("Status:", request.Status()._to_string(), color);
}

bool ReviewView::SelectableStyleButton(std::string text) const
{
	const ImGuiStyle& style(ImGui::GetStyle());
	ImGui::PushStyleColor(ImGuiCol_Button, style.Colors[ImGuiCol_Header]);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, style.Colors[ImGuiCol_HeaderHovered]);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, style.Colors[ImGuiCol_HeaderActive]);
	bool isClicked = ImGui::FullWidthButton(text.c_str());
	ImGui::PopStyleColor(3);
	return isClicked;
}
