#pragma once
#include "../IView.h"
#include <string>
#include "../AppFontIndex.h"
#include <IconsMaterialDesign.h>

class AppFontsTestView
	: public IView
{
public:
	void Render() override
	{
		ImGui::Begin("Debug: App Font Tests");

		TextWithFont("RobotoRegular_Normal " ICON_MD_ADD, AppFontIndex::RobotoRegular_Normal);
		TextWithFont("RobotoLight_Title " ICON_MD_QUESTION_ANSWER, AppFontIndex::RobotoLight_Title);
		TextWithFont("RobotoBold_Normal " ICON_MD_WARNING, AppFontIndex::RobotoBold_Normal);
		TextWithFont("RobotoRegular_Title " ICON_MD_CANCEL, AppFontIndex::RobotoRegular_Title);

		ImGui::End();
	}

	void TextWithFont(std::string text, AppFontIndex font) const
	{
		ImGui::PushFont(font);
		ImGui::Text(text.c_str());
		ImGui::PopFont();
	}

	std::string Name() override { return "AppFontsTestView"; }
};
