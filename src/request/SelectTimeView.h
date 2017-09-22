#pragma once
#include "SelectTimeViewModel.h"

class Selected
{
private:
	int _periodIndex;
	int _timeIndex;
	std::string _formattedTime;
	Poco::Data::Time _time;

public:
	int PeriodIndex() const { return _periodIndex; }
	void PeriodIndex(int value) { _periodIndex = value; }

	int TimeIndex() const { return _timeIndex; }
	void TimeIndex(int value) { _timeIndex = value; }

	std::string FormattedTime() const { return _formattedTime; }
	bool IsEmpty() const { return _periodIndex == -1 || _timeIndex == -1; }
	Poco::Data::Time Time() const { return _time; }

	Selected(int periodIndex, int timeIndex, const Poco::Data::Time time, const std::string& formattedTime)
		: _periodIndex(periodIndex),
		  _time(time),
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

class SelectTimeView
	: public ViewBase<SelectTimeViewModel>
{
private:
	std::string Today() const;

public:
	explicit SelectTimeView(const std::shared_ptr<SelectTimeViewModel>& viewModel);

	void Render() override;
	void RenderDateInvalid();
	void RenderStartTimeList(const int& freePeriodIndex, Selected& selectedStartTime, Selected& selectedEndTime, const bool& canAdd,
	                         std::vector<std::string>& expandedTimePeriodStrings, std::vector<Poco::Data::Time> expandedTimePeriod);
	void RenderEndTimeList(const int& freePeriodIndex, Selected& selectedStartTime, Selected& selectedEndTime, const bool& canAdd,
	                       std::vector<std::string>& expandedTimePeriodStrings, std::vector<Poco::Data::Time> expandedTimePeriod);
	void RenderSelectedTimeInfo(Selected& selectedStartTime, Selected& selectedEndTime);
	void RenderAddTimeButton(std::string labId, std::string selectedStartTime, std::string selectedEndTime);

	std::string Name() override { return "SelectTimeView"; }
};
