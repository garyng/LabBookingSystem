#include "stdafx.h"
#include "UserView.h"
#include "imgui/imgui_extra.h"

UserView::UserView(const std::shared_ptr<UserViewModel>& viewModel): ViewBase<UserViewModel>(viewModel)
{
}

void UserView::Render()
{
	ImGui::BeginDefaultCenteredWindow("User Panel");

	ImGui::DrawWelcomeBack(_viewModel->UserName().c_str());

	if (ImGui::TransparentFullWidthButton(ICON_MD_ADD " Request"))
	{
		_viewModel->GoToRequestViewCommand();
	}

	if (ImGui::TransparentFullWidthButton(ICON_MD_EXIT_TO_APP " Logout"))
	{
		ImGui::OpenPopup("Are you sure?");
	}

	ImGui::OkCancelPopupModal("Are you sure?", ICON_MD_WARNING,
	                          {
		                          "Logging out.",
		                          "Are you sure?"
	                          }, [&]()
	                          {
		                          _viewModel->LogoutCommand();
	                          });
	ImGui::End();
}
