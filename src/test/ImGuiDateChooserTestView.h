#pragma once
#include "addons/imguidatechooser/imguidatechooser.h"

class ImGuiDateChooserTestView
	: public IView
{
public:
	void Render() override
	{
		using namespace date;
		using namespace std::chrono;
		using namespace std;

		ImGui::Begin("Debug: Date Chooser");
		static tm date;
		static sys_days selected;
		static sys_days today = today_sys_day();
		static bool isDateInvalid;
		if (ImGui::DateChooser("Choose a date", date))
		{
			selected = to_sys_day(date);
			isDateInvalid = selected < today;
		}
		if (isDateInvalid)
		{
			ImGui::TextColored(AppColors::Red500, "Invalid date!");
		}
		else
		{
			sys_time<minutes> startTime = sys_days{selected} + 8h; // 8am
			sys_time<minutes> endTime = sys_days{selected} + 20h; // 8pm
			int currentIndex = 0;

			struct CheckedDisabled
			{
				bool IsChecked;
				bool IsDisabled;
				bool IsOccupied;
			};

			/*static bool selected[12] = {true, true, true, true,
				false, false, false, false,
				false, false, false, false};*/

			static array<CheckedDisabled, 12> selecteds = {
				CheckedDisabled{true, true, true},CheckedDisabled{true, true, true},CheckedDisabled{true, true, true},CheckedDisabled{true, true, true},
				CheckedDisabled{false, false, false},CheckedDisabled{false, false, false},CheckedDisabled{false, false, false},CheckedDisabled{false, false, false},
				CheckedDisabled{false, false, false},CheckedDisabled{false, false, false},CheckedDisabled{false, false, false},CheckedDisabled{false, false, false}
			};

			static int selectedCount = 0;
			static vector<int> startAndEnd;
			startAndEnd.reserve(2);
			static int prevStart;
			static int prevEnd;
			while (startTime < endTime)
			{
				stringstream text;
				text << format("%I:%M %p", startTime) << "\n"
					<< "\t\t- " << "\n"
					<< format("%I:%M %p", startTime + 1h);
				if (OwnCheckButton(text.str().c_str(), &selecteds[currentIndex].IsChecked, selecteds[currentIndex].IsDisabled, selecteds[currentIndex].IsOccupied, ImVec2(80, 80)))
				{
					if (!selecteds[currentIndex].IsDisabled)
					{
						selectedCount++;
						startAndEnd.push_back(currentIndex);
					}
				}

				// todo: how ah?
				if (selectedCount == 2)
				{
					int start = min(startAndEnd.at(0), startAndEnd.at(1)) + 1;
					int end = max(startAndEnd.at(0), startAndEnd.at(1)) - 1;
					for (; start <= end; ++start)
					{
						selecteds[start].IsChecked = !selecteds[start].IsChecked;
					}
					startAndEnd.clear();
					prevStart = start - 1;
					prevEnd = end + 1;
				}
				if (selectedCount == 3)
				{
					for (; prevStart <= prevEnd; ++prevStart)
					{
						selecteds[prevStart].IsChecked = !selecteds[prevStart].IsChecked;
					}
					selectedCount = 1;

				}

				if (currentIndex % 4 < 3)
				{
					ImGui::SameLine();
				}
				startTime += 1h;
				currentIndex++;
			}
		}


		ImGui::End();
	}
	// todo: will this event work?
	// it's 5.16AM...
	bool OwnCheckButton(const char* label, bool* pvalue, bool is_disabled, bool is_occupied, const ImVec2& size_arg = ImVec2(0, 0))
	{
		bool clicked = false;
		*pvalue = is_disabled ? false : *pvalue;

		const bool isChecked = pvalue ? *pvalue : false;

		const ImGuiStyle& style(ImGui::GetStyle());
		ImVec4 TextColor = style.Colors[ImGuiCol_Text];
		ImVec4 CheckButtonColor;
		ImVec4 CheckButtonHoveredColor;
		ImVec4 CheckButtonActiveColor;
		if (isChecked)
		{
			CheckButtonColor = style.Colors[ImGuiCol_Header];
			CheckButtonHoveredColor = style.Colors[ImGuiCol_HeaderHovered];
			CheckButtonActiveColor = style.Colors[ImGuiCol_HeaderActive];
		}
		else
		{
			CheckButtonColor = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			CheckButtonHoveredColor = style.Colors[ImGuiCol_HeaderHovered];
			CheckButtonHoveredColor.w *= 0.5f;
			CheckButtonActiveColor = style.Colors[ImGuiCol_HeaderActive];
			CheckButtonActiveColor.w *= 0.5f;
		}

		if (is_disabled)
		{
			TextColor = style.Colors[ImGuiCol_TextDisabled];
			CheckButtonHoveredColor = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			CheckButtonActiveColor = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		}

		if (is_occupied)
		{
			TextColor = AppColors::Yellow500;
			TextColor.w *= 0.7f;
		}

		ImGui::PushStyleColor(ImGuiCol_Text, TextColor);
		ImGui::PushStyleColor(ImGuiCol_Button, CheckButtonColor);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, CheckButtonHoveredColor);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, CheckButtonActiveColor);

		if (ImGui::Button(label, size_arg))
		{
			if (pvalue)
			{
				*pvalue = !(*pvalue);
			}
			clicked = true;
		}
		ImGui::PopStyleColor(4);
		return clicked;
	}

	date::sys_days today_sys_day()
	{
		/*using namespace date;
		using namespace std::chrono;
		return floor<days>(system_clock::now() + 8h);*/

		time_t rawTime;
		time(&rawTime);
		tm localTime;
		localtime_s(&localTime, &rawTime);
		return to_sys_day(localTime);
	}

	date::sys_days to_sys_day(std::tm const& t)
	{
		using namespace date;
		using namespace std::chrono;
		return sys_days{year{t.tm_year + 1900} / (t.tm_mon + 1) / t.tm_mday};
	}

	date::sys_seconds to_sys_time(std::tm const& t)
	{
		using namespace date;
		using namespace std::chrono;
		return sys_days{year{t.tm_year + 1900} / (t.tm_mon + 1) / t.tm_mday} +
			hours{t.tm_hour} + minutes{t.tm_min} + seconds{t.tm_sec};
	}


	std::string Name() override { return "ImGuiDateChooserTestView"; }
};
