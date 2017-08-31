#include "stdafx.h"
#include "LoginView.h"
#include "LoginViewModel.h"

LoginView::LoginView(const std::shared_ptr<LoginViewModel>& viewModel): ViewBase<LoginViewModel>(viewModel)
{
}

void LoginView::Render()
{
	ImGui::BeginDefaultCenteredWindow("Login");

	char userIdBuffer[255];
	FillCharBuffer(userIdBuffer, 255, _viewModel->UserId());
	ImGui::InputText(ICON_MD_PERM_IDENTITY " User ID", userIdBuffer, 255);
	_viewModel->UserId(userIdBuffer);

	char userPasswordBuffer[255];
	FillCharBuffer(userPasswordBuffer, 255, _viewModel->UserPassword());
	ImGui::InputText(ICON_MD_VPN_KEY" Password", userPasswordBuffer, 255, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);
	_viewModel->UserPassword(userPasswordBuffer);

	if (ImGui::FullWidthButton("Login"))
	{
		bool result = _viewModel->LoginCommand(std::string(userIdBuffer), std::string(userPasswordBuffer));

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
