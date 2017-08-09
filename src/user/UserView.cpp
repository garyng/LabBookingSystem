#include "UserView.h"
#include "imconfig.h"
#include "imgui.h"
#include <IconsFontAwesome.h>

UserView::UserView(const std::shared_ptr<UserViewModel>& viewModel): _viewModel(viewModel)
{
}

void UserView::Render()
{
	// user name?
	std::string name("User (" + _viewModel->_userId + ")");
	ImGui::BeginDefaultWindow(name.c_str());
	ImGui::PushItemWidth(-1);
	ImGui::Button(ICON_FA_QUESTION " Request");
	ImGui::Button(ICON_FA_SIGN_OUT " Logout");;
	ImGui::End();
}
