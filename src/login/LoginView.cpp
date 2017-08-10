#include "LoginView.h"
#include <IconsMaterialDesign.h>
#include "imgui.h"
#include "../services/NavigationService.h"
#include "LoginViewModel.h"

LoginView::LoginView(const std::shared_ptr<LoginViewModel>& viewModel): ViewBase<LoginViewModel>(viewModel)
{
}

void LoginView::Render()
{
	ImGui::BeginDefaultWindow("Login");

	static char userIdBuffer[255];
	ImGui::InputText(ICON_MD_PERM_IDENTITY " User ID", userIdBuffer, 255);

	static char userPasswordBuffer[255];
	ImGui::InputText(ICON_MD_VPN_KEY" Password", userPasswordBuffer, 255, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);

	// todo: constantly push userid and password
	// then you can generalize command model

	if (ImGui::RightAlignedButton("Login"))
	{
		_viewModel->LoginCommand(std::string(userIdBuffer), std::string(userPasswordBuffer));
		// todo: if login failed then popup
	}

	ImGui::End();
}
