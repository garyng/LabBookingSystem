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

	bool TransparentFullWidthButton(const char* label)
	{
		PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		bool result = FullWidthButton(label);
		PopStyleColor();
		return result;
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

	void OkPopupModal(std::string name, std::string icon, std::initializer_list<std::string> texts)
	{
		SetNextWindowPosCenter();
		if (BeginPopupModal(name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			HorizontallyCenteredText("");

			PushFont(AppFontIndex::MaterialIcon_Title);
			Text(icon.c_str());
			PopFont();
			SameLine();

			BeginGroup();
			{
				for (std::string text : texts)
				{
					Text(text.c_str());
				}
			}
			EndGroup();
			HorizontallyCenteredText("");
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

	void CenteredTexts(std::string text)
	{
		ImVec2 textSize = CalcTextSize(text.c_str());
		ImVec2 windowSize = GetWindowSize();
		float textX = windowSize.x / 2 - textSize.x / 2;
		float textY = windowSize.y / 2 - textSize.y / 2;
		SetCursorPosX(textX);
		SetCursorPosY(textY);
		Text(text.c_str());
	}

	void CenteredTexts(std::initializer_list<std::string> texts)
	{
		std::vector<std::pair<std::string, ImVec2>> textsAndSizes;

		float allTextHeight = 0.0f;
		for (std::string text : texts)
		{
			ImVec2 textSize = CalcTextSize(text.c_str());
			allTextHeight += textSize.y;
			textsAndSizes.emplace_back(text, textSize);
		}
		ImVec2 windowSize = GetWindowSize();

		// to vertically center the whole text
		float currentY = windowSize.y / 2 - allTextHeight / 2;

		SetCursorPosY(currentY);

		for (auto textAndSize : textsAndSizes)
		{
			std::string text = textAndSize.first;
			ImVec2 textSize = textAndSize.second;

			float currentX = windowSize.x / 2 - textSize.x / 2;
			SetCursorPosX(currentX);

			Text(text.c_str());

			currentY += textSize.y;
		}
	}
}
