#include "AdminView.h"
#include "imgui.h"
#include <IconsMaterialDesign.h>

AdminView::AdminView(const std::shared_ptr<AdminViewModel>& viewModel) : ViewBase<AdminViewModel>(viewModel)
{
}

void AdminView::Render()
{
	std::string title("Admin");
	ImGui::BeginDefaultWindow(title.c_str());
	ImGui::Selectable(ICON_MD_ADD " Request");
	ImGui::Selectable(ICON_MD_DONE " Review");
	ImGui::Selectable(ICON_MD_EXIT_TO_APP " Log Out");
	ImGui::End();
}
