#include "AdminView.h"
#include "imgui.h"
#include <IconsMaterialDesign.h>
#include "../AppFontIndex.h"
#include "../imgui/imgui_extra.h"

AdminView::AdminView(const std::shared_ptr<AdminViewModel>& viewModel) : ViewBase<AdminViewModel>(viewModel)
{
}

void AdminView::Render()
{
	ImGui::BeginDefaultCenteredWindow("Admin Panel");

	ImGui::DrawWelcomeBack(_viewModel->UserName().c_str());

	if (ImGui::TransparentFullWidthButton(ICON_MD_ADD " Request"))
	{
		_viewModel->GoToRequestViewCommand();
	}

	ImGui::TransparentFullWidthButton(ICON_MD_DONE " Review");

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
