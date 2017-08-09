#include "AdminView.h"
#include "imgui.h"
#include <IconsFontAwesome.h>

AdminView::AdminView(const std::shared_ptr<AdminViewModel>& viewModel) : ViewBase<AdminViewModel>(viewModel)
{
}

void AdminView::Render()
{
	std::string title("Admin");
	ImGui::BeginDefaultWindow(title.c_str());
	ImGui::Button(ICON_FA_QUESTION " Request");
	ImGui::Button(ICON_FA_CHECK " Review");
	ImGui::Button(ICON_FA_SIGN_OUT " Log Out");
	ImGui::End();
}