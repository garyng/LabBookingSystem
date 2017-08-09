#include "LoginView.h"
#include <IconsFontAwesome.h>
#include "imgui.h"
#include "../services/NavigationService.h"
#include "LoginViewModel.h"

LoginView::LoginView(const std::shared_ptr<LoginViewModel>& loginViewModel): _viewModel(loginViewModel)
{
}

void LoginView::Render()
{
	ImGui::BeginDefaultWindow("Login");

	static char userIdBuffer[255];
	ImGui::InputText(ICON_FA_USER " User ID", userIdBuffer, 255);

	static char userPasswordBuffer[255];
	ImGui::InputText(ICON_FA_KEY " Password", userPasswordBuffer, 255, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);

	// todo: constantly push userid and password
	// then you can generalize command model

	if (ImGui::Button(ICON_FA_SIGN_IN " Login"))
	{
		_viewModel->LoginCommand(std::string(userIdBuffer), std::string(userPasswordBuffer));
		// todo: if login failed then popup
	}

	ImGui::End();
}
