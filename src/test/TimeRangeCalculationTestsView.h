#pragma once

class TimePeriod
{
private:
	date::sys_time<std::chrono::minutes> _startTime;
	date::sys_time<std::chrono::minutes> _endTime;
public:
	date::sys_time<std::chrono::minutes> StartTime() const { return _startTime; }
	date::sys_time<std::chrono::minutes> EndTime() const { return _endTime; }

	TimePeriod(const date::sys_time<std::chrono::minutes>& startTime, const date::sys_time<std::chrono::minutes>& endTime)
		: _startTime(startTime),
		  _endTime(endTime)
	{
	}
};

class TimeRangeCalculationTestsView
	: public IView
{
public:
	void Render() override
	{
		using namespace std;
		using namespace chrono;
		using namespace date;
		using namespace coveo::linq;

		ImGui::Begin("Debug: Time Range Calculation");

		static tm date = tm_today();
		static sys_days today = today_sys_day();
		static sys_days selected = today;
		static bool isDateInvalid = false;

		static sys_time<minutes> earliest = selected + 8h;
		static sys_time<minutes> latest = selected + 20h;

		auto d = 30min;

		vector<TimePeriod> allocatedSlots{{earliest + 1h, earliest + 2h},{earliest + 3h, earliest + 5h}};
		vector<TimePeriod> freePeriods = getGaps(allocatedSlots, earliest, latest);

		if (ImGui::DateChooser("Choose a date", date))
		{
			selected = to_sys_day(date);
			isDateInvalid = selected < today;
		}
		if (isDateInvalid)
		{
			ImGui::PushFont(AppFontIndex::RobotoLight_Title1);

			ImGui::CenteredTexts({ICON_MD_ERROR_OUTLINE, "Invalid date!", ICON_MD_MUSIC_NOTE " I wish I could", "turn back time... " ICON_MD_MUSIC_NOTE});

			ImGui::PopFont();
		}
		else
		{
			ImGui::Spacing();
			ImGui::PushFont(AppFontIndex::RobotoLight_Title1);
			ImGui::Text(format("%d/%m/%Y", selected).c_str());
			ImGui::PopFont();
			ImGui::Spacing();
			ImGui::Separator();

			class Selected
			{
			private:
				int _periodIndex;
				int _timeIndex;
				string _formattedTime;

			public:
				int PeriodIndex() const { return _periodIndex; }
				int TimeIndex() const { return _timeIndex; }
				string FormattedTime() const { return _formattedTime; }
				bool IsEmpty() const { return _periodIndex == -1 || _timeIndex == -1; }


				Selected(int periodIndex, int timeIndex, const string& formattedTime)
					: _periodIndex(periodIndex),
					  _timeIndex(timeIndex),
					  _formattedTime(formattedTime)
				{
				}

				Selected()
					: _periodIndex(-1), _timeIndex(-1)
				{
				}

				bool operator==(const Selected& other) const
				{
					return _periodIndex == other._periodIndex && _timeIndex == other._timeIndex;
				}
			};


			ImGui::Columns(2);

			ImGui::PushFont(AppFontIndex::RobotoBold_Normal);

			ImGui::Text("Start:");
			ImGui::NextColumn();
			ImGui::Text("End:");
			ImGui::NextColumn();

			ImGui::PopFont();


			static Selected selectedStartTime;
			static Selected selectedEndTime;

			static bool isAddingAllowed;


			for (auto freePeriodIndex = 0; freePeriodIndex < freePeriods.size(); ++freePeriodIndex)
			{
				TimePeriod& tp = freePeriods[freePeriodIndex];
				vector<string> expanded = expandTimePeriod(tp, 1h)
					| select([](sys_time<minutes> time) { return format("%I:%M %p", time); })
					| to_vector();

				ImGui::BeginChildWithNBottomLineSpace("Start time", isAddingAllowed ? 3 : 0);
				{
					// don't show the last time entry of each period
					// ie 8-9am wont show 9am
					for (int textIndex = 0; textIndex < expanded.size() - 1; ++textIndex)
					{
						string& text = expanded[textIndex];

						Selected currentSelected{freePeriodIndex, textIndex, text};

						if (ImGui::Selectable(text.c_str(), currentSelected == selectedStartTime))
						{
							selectedStartTime = currentSelected;
							// reset when start time changes
							selectedEndTime = Selected{};
						}
					}
				}
				ImGui::EndChild();
				ImGui::NextColumn();

				ImGui::BeginChildWithNBottomLineSpace("End time", isAddingAllowed ? 3 : 0);
				{
					// only render the expanded time periods of currently selected period
					if (freePeriodIndex == selectedStartTime.PeriodIndex())
					{
						int startTimeSelectedIndex = selectedStartTime.TimeIndex();
						for (int textIndex = startTimeSelectedIndex + 1; textIndex < expanded.size(); textIndex++)
						{
							string& text = expanded[textIndex];
							Selected currentSelected{freePeriodIndex, textIndex, text};
							if (ImGui::Selectable(text.c_str(), currentSelected == selectedEndTime))
							{
								selectedEndTime = currentSelected;
							}
						}
					}
					// if there is not selected start time
					if (selectedStartTime.IsEmpty())
					{
						ImGui::PushFont(AppFontIndex::RobotoLight_Title1);
						ImGui::CenteredTexts({ICON_MD_BLUR_ON, "Wow! Much emptiness...", "Try choosing", "one of the available time?"});
						ImGui::PopFont();
					}
				}
				ImGui::EndChild();

				isAddingAllowed = !selectedStartTime.IsEmpty() && !selectedEndTime.IsEmpty();
			}
			ImGui::Columns(1);
			if (isAddingAllowed)
			{
				ImGui::Text("Selected time slot: ");
				ImGui::PushFont(AppFontIndex::RobotoLight_Title1);
				ostringstream oss;
				oss << selectedStartTime.FormattedTime()
					<< " - "
					<< selectedEndTime.FormattedTime();

				ImGui::Text(oss.str().c_str());

				ImGui::PopFont();

				ImGui::FullWidthButton(ICON_MD_ADD " Add");
			}
		}

		ImGui::End();
	}

	std::vector<date::sys_time<std::chrono::minutes>> expandTimePeriod(const TimePeriod& period, std::chrono::minutes step)
	{
		std::vector<date::sys_time<std::chrono::minutes>> expanded;
		date::sys_time<std::chrono::minutes> current = period.StartTime();
		date::sys_time<std::chrono::minutes> end = period.EndTime();

		while (current <= end)
		{
			expanded.push_back(current);
			current += step;
		}
		return expanded;
	}

	/*std::vector<TimePeriod> getGaps(const std::vector<TimePeriod>& allocation, const date::sys_time<std::chrono::minutes>& earliest, const date::sys_time<std::chrono::minutes>& latest)
	{
		std::vector<TimePeriod> alloc;

		if (allocation.front().StartTime() != earliest)
		{
			alloc.emplace_back(earliest, earliest);
		}
		alloc.insert(alloc.end(), allocation.begin(), allocation.end());
		if (allocation.back().EndTime() != latest)
		{
			alloc.emplace_back(latest, latest);
		}

		for (auto i = 1; i < alloc.size(); ++i)
		{
			TimePeriod free{alloc[i - 1].EndTime(),alloc[i].StartTime()};
			std::cout << date::format("%I:%M %p", free.StartTime()) << " " << date::format("%I:%M %p", free.EndTime()) << std::endl;
		}

		return {};
	}*/

	std::vector<TimePeriod> getGaps(const std::vector<TimePeriod>& allocation, const date::sys_time<std::chrono::minutes>& earliest, const date::sys_time<std::chrono::minutes>& latest)
	{
		//	+-------+-------+-------+-------+-------+-------+-------+-------+-------+
		//	| 0800	| 0900	| 1000	| 1100	| 1200	| 1300	| 1400	| 1500	| 1600	|
		//	+-------+-------+-------+-------+-------+-------+-------+-------+-------+
		//	|		|xxxxxxx|xxxxxxx|		|		|xxxxxxx|xxxxxxx|xxxxxxx|		|
		//	|		|xxxxxxx|xxxxxxx|		|		|xxxxxxx|xxxxxxx|xxxxxxx|		|
		//	+-------+-------+-------+-------+-------+-------+-------+-------+-------+
		//						|						|
		//						+-----------------------+
		//									| end of previous - start of current => free 
		//									v
		//	+-------+-------+-------+-------+-------+-------+-------+-------+-------+
		//	| 0800	| 0900	| 1000	| 1100	| 1200	| 1300	| 1400	| 1500	| 1600	|
		//	+-------+-------+-------+-------+-------+-------+-------+-------+-------+
		//	|		|xxxxxxx|		|+++++++|+++++++|		|xxxxxxx|xxxxxxx|		|
		//	|		|xxxxxxx|		|+++++++|+++++++|		|xxxxxxx|xxxxxxx|		|
		//	+-------+-------+-------+-------+-------+-------+-------+-------+-------+
		//				|												|
		//	------------+												+------------
		//		| 8AM - start of first => free									| end of last - 8PM => free
		//		v																V
		//	+-------+-------+-------+-------+-------+-------+-------+-------+-------+
		//	| 0800	| 0900	| 1000	| 1100	| 1200	| 1300	| 1400	| 1500	| 1600	|
		//	+-------+-------+-------+-------+-------+-------+-------+-------+-------+
		//	|+++++++|		|		|+++++++|+++++++|		|		|		|+++++++|
		//	|+++++++|		|		|+++++++|+++++++|		|		|		|+++++++|
		//	+-------+-------+-------+-------+-------+-------+-------+-------+-------+

		std::vector<TimePeriod> freePeriods;
		freePeriods.reserve(allocation.size() + 2);

		for (auto i = 1; i < allocation.size(); ++i)
		{
			freePeriods.emplace_back(allocation[i - 1].EndTime(), allocation[i].StartTime());
		}
		if (allocation.front().StartTime() != earliest)
		{
			// use emplace?
			// freePeriods.insert(freePeriods.begin(), {earliest, allocation.front().StartTime()});
			freePeriods.emplace(freePeriods.begin(), earliest, allocation.front().StartTime());
			// freePeriods.insert(freePeriods.begin(), { });
		}
		if (allocation.back().EndTime() != latest)
		{
			freePeriods.insert(freePeriods.end(), {allocation.back().EndTime(), latest});
		}

		/*for (auto& period : freePeriods)
		{
			std::cout << date::format("%I:%M %p", period.StartTime()) << " " << date::format("%I:%M %p", period.EndTime()) << std::endl;
		}*/

		return freePeriods;
	}

	tm tm_today()
	{
		time_t rawTime;
		time(&rawTime);
		tm localTime;
		localtime_s(&localTime, &rawTime);
		return localTime;
	}

	date::sys_days today_sys_day()
	{
		/*using namespace date;
		using namespace std::chrono;
		return floor<days>(system_clock::now() + 8h);*/

		return to_sys_day(tm_today());
	}

	date::sys_days to_sys_day(tm const& t)
	{
		using namespace date;
		using namespace std::chrono;
		return sys_days{year{t.tm_year + 1900} / (t.tm_mon + 1) / t.tm_mday};
	}

	date::sys_seconds to_sys_time(tm const& t)
	{
		using namespace date;
		using namespace std::chrono;
		return sys_days{year{t.tm_year + 1900} / (t.tm_mon + 1) / t.tm_mday} +
			hours{t.tm_hour} + minutes{t.tm_min} + seconds{t.tm_sec};
	}

	std::string Name() override { return "TimeRangeCalculationTestsView"; }
};
