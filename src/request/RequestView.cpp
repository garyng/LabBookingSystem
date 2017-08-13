#include "RequestView.h"
#include "imconfig.h"
#include "imgui.h"
#include <string>
#include <IconsMaterialDesign.h>
#include "imgui_internal.h"

using namespace std;

RequestView::RequestView(const shared_ptr<RequestViewModel>& viewModel): ViewBase<RequestViewModel>(viewModel)
{
}

void RequestView::Render()
{
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
	ImGui::BeginDefaultCenteredResizableWindow("Request");

	ImGui::Selectable(ICON_MD_ARROW_BACK " Back");
	ImGui::Separator();

	ImGui::Columns(2);

	// todo: if no requests, then show "no requests"
	static int selectedIndex = 0;

	static char buffer[1024];
	ImGui::InputText(ICON_MD_SEARCH " Search", buffer, 1024);

	ImGui::BeginChild("RequestsList", ImVec2(0, -2 * ImGui::GetItemsLineHeightWithSpacing()));
	{
		for (size_t i = 0; i < _viewModel->Requests.size(); i++)
		{
			string label = "Request #" + to_string(_viewModel->Requests[i]->RequestId) + " " + _viewModel->Requests[i]->Status._to_string();
			if (ImGui::Selectable(label.c_str(), selectedIndex == i))
			{
				selectedIndex = i;
			}
		}
	}
	ImGui::EndChild();

	static int currentItem;
	const char* items[] = {"Accepted", "Pending", "Rejected"};
	ImGui::Combo("Filter By", &currentItem, items, IM_ARRAYSIZE(items));

	ImGui::RightAlignedButton(ICON_MD_ADD " New Request");


	ImGui::NextColumn();

	ImGui::BeginChild("RequestInfo", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing()));
	{
		string text = "Request #" + to_string(selectedIndex);
		ImGui::Text(text.c_str());
		ImGui::TextWrapped("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
		text = "Status: " + string(_viewModel->Requests[selectedIndex]->Status._to_string());
		ImGui::Text(text.c_str());
	}
	ImGui::EndChild();
	ImGui::BeginChild("RequestInfoFooter");
	{
		if (_viewModel->Requests[selectedIndex]->Status == +RequestStatus::Pending)
		{
			ImGui::RightAlignedButton(ICON_MD_CLOSE " Cancel Request");
		}
	}
	ImGui::EndChild();

	ImGui::End();
}
