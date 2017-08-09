#include <imgui.h>

namespace ImGui
{
	void BeginDefaultWindow(const char* name)
	{
		//SetNextWindowPosCenter();
		Begin(name, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
	}
}

