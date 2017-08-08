#include "LoginView.h"
#include "imgui.h"

void LoginView::Render()
{
	ImGui::BeginDefaultWindow("Login");

	static char userIdBuffer[255];
	ImGui::InputText("UserId", userIdBuffer, 255);

	ImGui::End();
}
