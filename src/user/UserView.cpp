#include "UserView.h"
#include "imconfig.h"
#include "imgui.h"
#include <IconsMaterialDesign.h>

UserView::UserView(const std::shared_ptr<UserViewModel>& viewModel): ViewBase<UserViewModel>(viewModel)
{
}

void UserView::Render()
{
	// user name?
	std::string name("User (" + _viewModel->_userId + ")");
	ImGui::BeginDefaultWindow(name.c_str());
	ImGui::Button(ICON_MD_ADD " Request");
	ImGui::Button(ICON_MD_EXIT_TO_APP " Logout");;
	ImGui::End();
}
