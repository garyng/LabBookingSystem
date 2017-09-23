#include "stdafx.h"
#include "SelectTimeView.h"
#include "test/ImGuiDateChooserTestView.h"
#include "imgui/imgui_extra.h"

using namespace std;
using namespace Poco;
using namespace Data;
using namespace coveo::linq;

SelectTimeView::SelectTimeView(const shared_ptr<SelectTimeViewModel>& viewModel)
	: ViewBase<SelectTimeViewModel>(viewModel)
{
}

void SelectTimeView::Render()
{
	ImGui::SetNextWindowSize(ImVec2(500, 600), ImGuiSetCond_FirstUseEver);
	ImGui::BeginDefaultCenteredResizableWindow("Select Time");

	if (ImGui::Selectable(ICON_MD_ARROW_BACK " Back"))
	{
		_viewModel->GoBackCommand();
	}

	static tm selectedDateBuffer;
	selectedDateBuffer = _viewModel->SelectedDateTimetm();
	if (ImGui::DateChooser("Select a date", selectedDateBuffer))
	{
		_viewModel->SelectedDateTime(selectedDateBuffer);
		_viewModel->RefreshTimeListCommand();
	}
	if (_viewModel->IsSelectedTimeValid())
	{
		if (_viewModel->FreeTimePeriods().size() == 0)
		{
			RenderNoFreeTimePeriodsAvailable();
		}
		else
		{
			RenderFreeTimePeriods();
		}
	}
	else
	{
		RenderDateInvalid();
	}

	ImGui::End();
}

void SelectTimeView::RenderDateInvalid()
{
	ImGui::PushFont(AppFontIndex::RobotoLight_Title1);

	ImGui::CenteredTexts({ICON_MD_ERROR_OUTLINE, "Invalid date!", ICON_MD_MUSIC_NOTE " I wish I could", "turn back time... " ICON_MD_MUSIC_NOTE});
	ImGui::PopFont();

	ImGui::HorizontallyCenteredText("pssst.. Today is " + Today());
}

void SelectTimeView::RenderNoFreeTimePeriodsAvailable()
{
	ImGui::PushFont(AppFontIndex::RobotoLight_Title1);

	ImGui::CenteredTexts({ICON_MD_PREGNANT_WOMAN, "I'm full..."});
	ImGui::PopFont();
}

void SelectTimeView::RenderFreeTimePeriods()
{
	ImGui::Spacing();
	ImGui::PushFont(AppFontIndex::RobotoLight_Title1);
	ImGui::Text(_viewModel->SelectedDateFormatted().c_str());
	ImGui::PopFont();
	ImGui::Spacing();
	ImGui::Separator();

	ImGui::Columns(2);

	ImGui::PushFont(AppFontIndex::RobotoBold_Normal);

	ImGui::Text("Start:");
	ImGui::NextColumn();
	ImGui::Text("End:");
	ImGui::NextColumn();

	ImGui::PopFont();

	static Selected selectedStartTime;
	selectedStartTime.PeriodIndex(_viewModel->SelectedStartTimePeriodIndex());
	selectedStartTime.TimeIndex(_viewModel->SelectedStartTimeTimeIndex());

	static Selected selectedEndTime;
	selectedEndTime.PeriodIndex(_viewModel->SelectedEndTimePeriodIndex());
	selectedEndTime.TimeIndex(_viewModel->SelectedEndTimeTimeIndex());

	static bool canAdd;

	int freePeriodIndex = 0;
	for (FreeTime& freeTimePeriod : _viewModel->FreeTimePeriods())
	{
		vector<Time> expandedTimePeriod = freeTimePeriod.ExpandedTimePeriod();
		vector<string> expandedTimePeriodStrings = freeTimePeriod.ExpandedTimePeriodStrings();

		RenderStartTimeList(freePeriodIndex, selectedStartTime, selectedEndTime, canAdd, expandedTimePeriodStrings, expandedTimePeriod);
		ImGui::NextColumn();
		RenderEndTimeList(freePeriodIndex, selectedStartTime, selectedEndTime, canAdd, expandedTimePeriodStrings, expandedTimePeriod);

		freePeriodIndex++;

		canAdd = !selectedStartTime.IsEmpty() && !selectedEndTime.IsEmpty();
	}

	ImGui::Columns(1);
	if (canAdd)
	{
		RenderSelectedTimeInfo(selectedStartTime, selectedEndTime);
		RenderAddTimeButton(_viewModel->LabId(), selectedStartTime.FormattedTime(), selectedEndTime.FormattedTime());
	}
}

void SelectTimeView::RenderStartTimeList(const int& freePeriodIndex, Selected& selectedStartTime, Selected& selectedEndTime, const bool& canAdd,
                                         vector<string>& expandedTimePeriodStrings, vector<Time> expandedTimePeriod)
{
	ImGui::BeginChildWithNBottomLineSpace("Start time", canAdd ? 3 : 0);
	{
		int freePeriodTextIndex = 0;
		for (string& freePeriodText : expandedTimePeriodStrings)
		{
			// skip the last entry
			// eg available time: 8 - 10AM but will only show 800, 830, 900, 930 (because they are vaild "start" time)
			if (&freePeriodText == &expandedTimePeriodStrings.back()) break;

			Time& time = expandedTimePeriod[freePeriodTextIndex];
			Selected currentSelected{freePeriodIndex, freePeriodTextIndex, time, freePeriodText};
			if (ImGui::Selectable(freePeriodText.c_str(), currentSelected == selectedStartTime))
			{
				selectedStartTime = currentSelected;
				_viewModel->SelectedStartTime(time);
				_viewModel->SelectedStartTimePeriodIndex(freePeriodIndex);
				_viewModel->SelectedStartTimeTimeIndex(freePeriodTextIndex);

				selectedEndTime = Selected{};
				_viewModel->SelectedEndTime({});
				_viewModel->SelectedEndTimePeriodIndex(-1);
				_viewModel->SelectedEndTimeTimeIndex(-1);
			}

			freePeriodTextIndex++;
		}
	}
	ImGui::EndChild();
}

void SelectTimeView::RenderEndTimeList(const int& freePeriodIndex, Selected& selectedStartTime, Selected& selectedEndTime, const bool& canAdd,
                                       vector<string>& expandedTimePeriodStrings, vector<Time> expandedTimePeriod)
{
	ImGui::BeginChildWithNBottomLineSpace("End time", canAdd ? 3 : 0);
	{
		// only render the end time for the selected start time
		if (freePeriodIndex == selectedStartTime.PeriodIndex())
		{
			int selectedStartTimeIndex = selectedStartTime.TimeIndex();
			int size = expandedTimePeriodStrings.size();
			// end time should not be equal to the selected start time
			for (int textIndex = selectedStartTimeIndex + 1; textIndex < size; textIndex++)
			{
				string& text = expandedTimePeriodStrings[textIndex];
				Time& time = expandedTimePeriod[textIndex];
				Selected currentSelectedEndTime{freePeriodIndex, textIndex,time,text};
				if (ImGui::Selectable(text.c_str(), currentSelectedEndTime == selectedEndTime))
				{
					selectedEndTime = currentSelectedEndTime;
					_viewModel->SelectedEndTime(time);
					_viewModel->SelectedEndTimePeriodIndex(freePeriodIndex);
					_viewModel->SelectedEndTimeTimeIndex(textIndex);
				}
			}
		}
		// there is no selected start time
		if (selectedStartTime.IsEmpty())
		{
			ImGui::PushFont(AppFontIndex::RobotoLight_Title1);
			ImGui::CenteredTexts({ICON_MD_BLUR_ON, "Wow! Much emptiness...", "Try choosing", "one of the available time?"});
			ImGui::PopFont();
		}
	}
	ImGui::EndChild();
}

void SelectTimeView::RenderSelectedTimeInfo(Selected& selectedStartTime, Selected& selectedEndTime)
{
	ImGui::Spacing();

	ImGui::PushFont(AppFontIndex::RobotoBold_Normal);
	ImGui::Text("Selected time slot: ");
	ImGui::PopFont();

	ImGui::PushFont(AppFontIndex::RobotoLight_Title1);
	ostringstream oss;
	oss << selectedStartTime.FormattedTime()
		<< " - "
		<< selectedEndTime.FormattedTime();

	ImGui::Text(oss.str().c_str());
	ImGui::PopFont();
}

void SelectTimeView::RenderAddTimeButton(string labId, string selectedStartTime, string selectedEndTime)
{
	if (ImGui::FullWidthButton(ICON_MD_ADD " Add"))
	{
		ImGui::OpenPopup("Confirmation");
	}
	ImGui::OkCancelPopupModal("Confirmation", ICON_MD_INFO_OUTLINE,
	                          {
		                          "Request " + labId + " for",
		                          selectedStartTime + " - " + selectedEndTime + "?"
	                          }, [&]()
                          {
	                          _viewModel->RequestLabCommand();
                          });
}

string SelectTimeView::Today() const
{
	return DateTimeFormatter::format(DateTime{LocalDateTime{}.timestamp()}, "%d/%m/%Y");
}
