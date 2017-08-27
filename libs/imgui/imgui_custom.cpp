#include <imgui.h>

namespace ImGui
{
	bool BeginDefaultCenteredWindow(const char* name)
	{
		SetNextWindowPosCenter();
		return Begin(name, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
	}

	bool BeginDefaultCenteredResizableWindow(const char* name)
	{
		SetNextWindowPosCenter();
		return Begin(name, nullptr, ImGuiWindowFlags_NoCollapse);
	}


	bool FullWidthButton(const char* label)
	{
		return Button(label, ImVec2(-1, 0));
	}

	bool BeginChildWithNBottomLineSpace(const char* str_id, int lines)
	{
		return BeginChild(str_id, ImVec2(0, -lines * ImGui::GetItemsLineHeightWithSpacing()));
	}
}
