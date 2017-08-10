#include <imgui.h>

namespace ImGui
{
	bool BeginDefaultWindow(const char* name)
	{
		//SetNextWindowPosCenter();
		return Begin(name, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
	}

	bool RightAlignedButton(const char* label)
	{
		return Button(label, ImVec2(-1, 0));
	}
}

