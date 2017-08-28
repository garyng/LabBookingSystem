#include "UserView.h"
#include "imconfig.h"
#include "imgui.h"
#include <IconsMaterialDesign.h>
#include "../imgui/imgui_extra.h"

UserView::UserView(const std::shared_ptr<UserViewModel>& viewModel): ViewBase<UserViewModel>(viewModel)
{
}

void UserView::Render()
{
	ImGui::BeginDefaultCenteredWindow("User Panel");

	ImGui::DrawWelcomeBack(_viewModel->UserName().c_str());

	ImGui::Selectable(ICON_MD_ADD " Request");

	if (ImGui::Selectable(ICON_MD_EXIT_TO_APP " Logout"))
	{
		ImGui::OpenPopup("Are you sure?");
	}

	ImGui::RenderOkCancelPopupModel("Are you sure?",
	                                {
		                                ICON_MD_WARNING " Logging out.",
		                                "Are you sure?"
	                                }, [&]()
	                                {
		                                _viewModel->LogoutCommand();
	                                });
	ImGui::End();
}
