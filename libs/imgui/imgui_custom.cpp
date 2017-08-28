#include <imgui.h>
#include "../../src/AppFontIndex.h"

namespace ImGui
{
	bool BeginDefaultCenteredWindow(const char* name)
	{
		// SetNextWindowPosCenter();
		return Begin(name, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
	}

	bool BeginDefaultCenteredResizableWindow(const char* name)
	{
		// SetNextWindowPosCenter();
		return Begin(name, nullptr, ImGuiWindowFlags_NoCollapse);
	}

	bool FullWidthButton(const char* label)
	{
		return Button(label, ImVec2(-1, 0));
	}

	bool BeginChildWithNBottomLineSpace(const char* str_id, int lines)
	{
		return BeginChild(str_id, ImVec2(0, -lines * GetItemsLineHeightWithSpacing()));
	}

	void DrawWelcomeBack(const char* name)
	{
		PushFont(AppFontIndex::RobotoLight_Title);
		Text("Welcome back,");
		SameLine();
		PopFont();
		PushFont(AppFontIndex::RobotoRegular_Title);
		Text(name);
		PopFont();
		Separator();
		Spacing();
	}

	void RenderPopupModal(std::string name, std::initializer_list<std::string> texts)
	{
		if (BeginPopupModal(name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			// each element is a seperate line

			for (std::string text : texts)
			{
				Text(text.c_str());
			}
			Spacing();
			Separator();
			if (FullWidthButton("OK"))
			{
				CloseCurrentPopup();
			}
			EndPopup();
		}
	}

	void HorizontallyCenteredText(std::string text)
	{
		float textWidth = CalcTextSize(text.c_str()).x;
		float windowWidth = GetWindowSize().x;
		float textX = windowWidth / 2 - textWidth / 2;
		SetCursorPosX(textX);
		Text(text.c_str());
	}

	void CentereredText(std::string text)
	{
		ImVec2 textSize = CalcTextSize(text.c_str());
		ImVec2 windowSize = GetWindowSize();
		float textX = windowSize.x / 2 - textSize.x / 2;
		float textY = windowSize.y / 2 - textSize.y / 2;
		SetCursorPosX(textX);
		SetCursorPosY(textY);
		Text(text.c_str());
	}
	
}
