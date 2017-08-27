#include "UserView.h"
#include "imconfig.h"
#include "imgui.h"
#include <IconsMaterialDesign.h>

UserView::UserView(const std::shared_ptr<UserViewModel>& viewModel): ViewBase<UserViewModel>(viewModel)
{
}

void UserView::Render()
{
	std::string name("User (" + _viewModel->UserName() + ")");
	ImGui::BeginDefaultCenteredWindow(name.c_str());
	ImGui::Selectable(ICON_MD_ADD " Request");
	ImGui::Selectable(ICON_MD_EXIT_TO_APP " Logout");
	ImGui::End();
}
