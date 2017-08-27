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
	ImGui::BeginDefaultCenteredWindow("Login");

	static char userIdBuffer[255];
	ImGui::InputText(ICON_MD_PERM_IDENTITY " User ID", userIdBuffer, 255);

	static char userPasswordBuffer[255];
	ImGui::InputText(ICON_MD_VPN_KEY" Password", userPasswordBuffer, 255, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);

	// todo: constantly push userid and password
	// then you can generalize command model

	if (ImGui::FullWidthButton("Login"))
	{
		bool result = _viewModel->LoginCommand(std::string(userIdBuffer), std::string(userPasswordBuffer));

		if (!result)
		{
			ImGui::OpenPopup("Unable to login");
		}
	}
	RenderPasswordIncorrectDialog();

	ImGui::End();
}

void LoginView::RenderPasswordIncorrectDialog()
{
	if (ImGui::BeginPopupModal("Unable to login", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text(ICON_MD_ERROR_OUTLINE " Invalid username/password combination.");
		ImGui::Text("Please try again.");
		ImGui::Spacing();
		ImGui::Separator();
		if (ImGui::FullWidthButton("OK"))
		{
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}
