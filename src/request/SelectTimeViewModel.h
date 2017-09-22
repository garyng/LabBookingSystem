#pragma once
#include "storage/RequestStorage.h"
#include "models/Request.h"
#include "TimePeriod.h"
#include "query/GetAllRequestByLabIdQuery.h"
#include "storage/UserStorage.h"
#include "RequestViewModel.h"
#include "SelectLabViewModel.h"

class FreeTime
{
	TimePeriod _Period;
	std::vector<Poco::Data::Time> _expandedTimePeriod;
	std::vector<std::string> _expandedTimePeriodStrings;

public:
	TimePeriod Period() const { return _Period; }
	std::vector<Poco::Data::Time> ExpandedTimePeriod() const { return _expandedTimePeriod; }
	std::vector<std::string> ExpandedTimePeriodStrings() const { return _expandedTimePeriodStrings; }

	FreeTime(const TimePeriod& period, const std::vector<Poco::Data::Time>& expandedTimePeriod, const std::vector<std::string>& expandedTimePeriodStrings)
		: _Period(period),
		  _expandedTimePeriod(expandedTimePeriod),
		  _expandedTimePeriodStrings(expandedTimePeriodStrings)
	{
	}
};

class SelectTimeViewModel
	: public ViewModelBase
{
private:
	std::string _labId;
	std::vector<Request> _requests;
	std::vector<TimePeriod> _allocatedTimePeriods;
	std::shared_ptr<RequestStorage> _requestStorage;
	std::shared_ptr<UserStorage> _userStorage;

	Poco::DateTime _selectedDateTime;
	std::vector<FreeTime> _freeTimePeriods;
	Poco::Data::Time _selectedStartTime;
	Poco::Data::Time _selectedEndTime;

public:
	std::string LabId() const { return _labId; }
	void LabId(std::string value) { _labId = value; }

	std::string _userName;
	std::string UserName() const { return _userName; }
	void UserName(std::string value) { _userName = value; }

	std::vector<Request> Requests() const { return _requests; }
	void Requests(std::vector<Request> value) { _requests = value; }

	std::vector<FreeTime> FreeTimePeriods() const { return _freeTimePeriods; }

	SelectTimeViewModel(const std::shared_ptr<NavigationService>& navigation,
	                    const std::shared_ptr<RequestStorage>& requestStorage, const std::shared_ptr<UserStorage>& userStorage);

	void Reset() override;
	void LoadRequestsCommand();


	Poco::DateTime SelectedDateTime() const { return _selectedDateTime; }
	tm SelectedDateTimetm() const { return ToTm(_selectedDateTime); }
	Poco::Data::Date SelectedDate() const { return _selectedDateTime; }
	std::string SelectedDateFormatted() const { return FormatDateTime(_selectedDateTime); }
	void SelectedDateTime(Poco::DateTime value) { _selectedDateTime = value; }
	void SelectedDateTime(tm value) { _selectedDateTime = ToDateTime(value); }
	bool IsSelectedTimeValid() const { return _selectedDateTime > Today(); }

	void RefreshTimeListCommand();

	void GetFreeTimePeriods(Poco::Data::Date selectedDate, Poco::Timespan incrementStep = 30 * Poco::Timespan::MINUTES);
	// expand start and end time to a list of continuous time with a specified increment
	// eg: 8AM - 9AM => 8AM 8.30AM 9AM
	std::vector<Poco::Data::Time> ExpandTimePeriod(const TimePeriod& timePeriod, Poco::Timespan incrementStep);
	std::vector<TimePeriod> GetGaps(const std::vector<TimePeriod>& allocated,
	                                Poco::Data::Time earliestTime = Poco::Data::Time{8,0,0}, Poco::Data::Time latestTime = Poco::Data::Time{20,0,0});


	Poco::Data::Time SelectedStartTime() const { return _selectedStartTime; }
	void SelectedStartTime(Poco::Data::Time value) { _selectedStartTime = value; }

	Poco::Data::Time SelectedEndTime() const { return _selectedEndTime; }
	void SelectedEndTime(Poco::Data::Time value) { _selectedEndTime = value; }

	// to reset the select item on the view
	int _selectedStartTimePeriodIndex;
	int SelectedStartTimePeriodIndex() const { return _selectedStartTimePeriodIndex; }
	void SelectedStartTimePeriodIndex(int value) { _selectedStartTimePeriodIndex = value; }

	int _selectedStartTimeTimeIndex;
	int SelectedStartTimeTimeIndex() const { return _selectedStartTimeTimeIndex; }
	void SelectedStartTimeTimeIndex(int value) { _selectedStartTimeTimeIndex = value; }

	int _selectedEndTimePeriodIndex;
	int SelectedEndTimePeriodIndex() const { return _selectedEndTimePeriodIndex; }
	void SelectedEndTimePeriodIndex(int value) { _selectedEndTimePeriodIndex = value; }

	int _selectedEndTimeTimeIndex;
	int SelectedEndTimeTimeIndex() const { return _selectedEndTimeTimeIndex; }
	void SelectedEndTimeTimeIndex(int value) { _selectedEndTimeTimeIndex = value; }

	void RequestLabCommand();

	Poco::DateTime Tomorrow() const;
	Poco::DateTime Today() const;
	// Convert tm to DateTime, with 00:00 as time
	Poco::DateTime ToDateTime(tm dateTime) const;
	// Convert DateTime to tm
	tm ToTm(Poco::DateTime dateTime) const;
	std::string FormatDateTime(Poco::DateTime date) const;
	std::string FormatTime(Poco::Data::Time time) const;
	std::string Name() override { return "SelectTimeViewModel"; }
};
