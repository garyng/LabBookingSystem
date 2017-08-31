#pragma once
#include "AppColors.h"

class AppColorsTestView
	: public IView
{
public:
	std::string Name() override { return "AppColorsTestView"; }

	void Render() override
	{
		ImGui::Begin("Debug: App Color Tests");
		ImGui::TextColored(AppColors::DefaultWhite, "DefaultWhite");
		ImGui::TextColored(AppColors::Red500, "Red500");
		ImGui::TextColored(AppColors::Pink500, "Pink500");
		ImGui::TextColored(AppColors::Purple500, "Purple500");
		ImGui::TextColored(AppColors::DeepPurple500, "DeepPurple500");
		ImGui::TextColored(AppColors::Indigo500, "Indigo500");
		ImGui::TextColored(AppColors::Blue500, "Blue500");
		ImGui::TextColored(AppColors::LightBlue500, "LightBlue500");
		ImGui::TextColored(AppColors::Cyan500, "Cyan500");
		ImGui::TextColored(AppColors::Teal500, "Teal500");
		ImGui::TextColored(AppColors::Green500, "Green500");
		ImGui::TextColored(AppColors::LightGreen500, "LightGreen500");
		ImGui::TextColored(AppColors::Lime500, "Lime500");
		ImGui::TextColored(AppColors::Yellow500, "Yellow500");
		ImGui::TextColored(AppColors::Amber500, "Amber500");
		ImGui::TextColored(AppColors::Orange500, "Orange500");
		ImGui::TextColored(AppColors::DeepOrange500, "DeepOrange500");
		ImGui::TextColored(AppColors::Brown500, "Brown500");
		ImGui::TextColored(AppColors::Grey500, "Grey500");
		ImGui::TextColored(AppColors::BlueGrey500, "BlueGrey500");

		ImGui::End();
	}

};
