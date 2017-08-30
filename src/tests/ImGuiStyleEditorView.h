#pragma once
#include <imgui.h>
#include "../IView.h"

class ImGuiStyleEditorView
	: public IView
{
public:
	void Render() override
	{
		ImGui::ShowStyleEditor();
	}

	std::string Name() override { return "ImGuiStyleEditorView"; }
};
