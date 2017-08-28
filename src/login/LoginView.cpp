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

	if (ImGui::FullWidthButton("Login"))
	{
		bool result = _viewModel->LoginCommand(std::string(userIdBuffer), std::string(userPasswordBuffer));

		ClearBuffer(userPasswordBuffer, 0);

		if (!result)
		{
			ImGui::OpenPopup("Unable to login");
		}
	}
	ImGui::OkPopupModal("Unable to login",
	                    ICON_MD_ERROR_OUTLINE,
	                    {
		                    "Invalid username/password combination.",
		                    "Please try again."
	                    });
	ImGui::End();
}
