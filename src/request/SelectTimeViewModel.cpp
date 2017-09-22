#include "stdafx.h"
#include "SelectTimeViewModel.h"
#include "query/GetUserIdFromUserNameQuery.h"
#include "command/AddRequestCommand.h"

using namespace std;
using namespace Poco;
using namespace Data;
using namespace coveo::linq;

SelectTimeViewModel::SelectTimeViewModel(const shared_ptr<NavigationService>& navigation, const shared_ptr<RequestStorage>& requestStorage, const shared_ptr<UserStorage>& userStorage): ViewModelBase(navigation),
                                                                                                                                                                                         _requestStorage(requestStorage), _userStorage(userStorage)
{
	SelectedDateTime(Tomorrow());
}

void SelectTimeViewModel::Reset()
{
	SelectedDateTime(Tomorrow());
	SelectedStartTime({});
	SelectedEndTime({});
	_freeTimePeriods.clear();
	SelectedStartTimePeriodIndex(-1);
	SelectedStartTimeTimeIndex(-1);
	SelectedEndTimePeriodIndex(-1);
	SelectedEndTimeTimeIndex(-1);
}

void SelectTimeViewModel::LoadRequestsCommand()
{
	GetAllRequestByLabIdQuery query{_requestStorage};
	_requests = query.Execute(_labId);
}

void SelectTimeViewModel::RefreshTimeListCommand()
{
	if (IsSelectedTimeValid())
	{
		GetFreeTimePeriods(SelectedDate());
	}
}

void SelectTimeViewModel::GetFreeTimePeriods(Date selectedDate, Timespan incrementStep)
{
	using namespace std;
	using namespace coveo::linq;

	vector<TimePeriod> allocated = _requests
		| where([&](Request r) { return (r.Date() == selectedDate) && (r.IsAccepted() || r.IsPending()); })
		| select([](Request r) { return TimePeriod{r.StartTime(), r.EndTime()}; })
		| to_vector();

	_freeTimePeriods = GetGaps(allocated)
		| select([&](TimePeriod tp)
		{
			vector<Time> expanded = ExpandTimePeriod(tp, incrementStep);
			vector<string> expandedStrings = expanded
				| select([&](Time time) { return FormatTime(time); })
				| to_vector();
			return FreeTime{tp,expanded, expandedStrings};
		})
		| to_vector();
}

vector<Time> SelectTimeViewModel::ExpandTimePeriod(const TimePeriod& timePeriod, Timespan incrementStep)
{
	using namespace std;
	vector<Time> expanded;
	Time currentTime = timePeriod.StartTime();
	Time endTime = timePeriod.EndTime();

	DateTime currentDateTime{1970,1,1,currentTime.hour(), currentTime.minute(), currentTime.second()};
	DateTime endDateTime{1970,1,1,endTime.hour(), endTime.minute(), endTime.second()};

	while (currentDateTime <= endDateTime)
	{
		expanded.push_back(currentDateTime);
		currentDateTime += incrementStep;
	}
	return expanded;
}

vector<TimePeriod> SelectTimeViewModel::GetGaps(const vector<TimePeriod>& allocated, Time earliestTime, Time latestTime)
{
	using namespace std;
	using namespace Poco;

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

	vector<TimePeriod> freePeriods;
	freePeriods.reserve(allocated.size() + 2);

	if (allocated.size() == 0)
	{
		freePeriods.emplace_back(earliestTime, latestTime);
	}
	else
	{
		for (auto i = 1; i < allocated.size(); ++i)
		{
			freePeriods.emplace_back(allocated[i - 1].EndTime(), allocated[i].StartTime());
		}
		if (allocated.front().StartTime() != earliestTime)
		{
			freePeriods.emplace(freePeriods.begin(), earliestTime, allocated.front().StartTime());
		}
		if (allocated.back().EndTime() != latestTime)
		{
			freePeriods.insert(freePeriods.end(), {allocated.back().EndTime(), latestTime});
		}
	}

	return freePeriods;
}

void SelectTimeViewModel::RequestLabCommand()
{
	string labId = LabId();

	GetUserIdFromUserNameQuery query{_userStorage};
	string userId = query.Execute(UserName());

	AddRequestCommand command{_requestStorage};
	command.Execute(labId, userId, SelectedDate(), _selectedStartTime, _selectedEndTime);

	_navigation->GoBack();
}

DateTime SelectTimeViewModel::Tomorrow() const
{
	LocalDateTime today;
	today += 1 * Timespan::DAYS;
	return DateTime{today.timestamp()};
}

DateTime SelectTimeViewModel::Today() const
{
	return DateTime{LocalDateTime{}.timestamp()};
}

DateTime SelectTimeViewModel::ToDateTime(tm dateTime) const
{
	return DateTime{dateTime.tm_year + 1900, dateTime.tm_mon + 1, dateTime.tm_mday};
}

tm SelectTimeViewModel::ToTm(DateTime dateTime) const
{
	tm t;
	t.tm_sec = dateTime.second();
	t.tm_min = dateTime.minute();
	t.tm_hour = dateTime.hour();
	t.tm_mday = dateTime.day();
	t.tm_mon = dateTime.month() - 1;
	t.tm_year = dateTime.year() - 1900;
	t.tm_wday = dateTime.dayOfWeek();
	t.tm_yday = dateTime.dayOfYear();
	// t.tm_isdst  ?
	return t;
}

string SelectTimeViewModel::FormatDateTime(DateTime date) const
{
	return DateTimeFormatter::format(date, "%d/%m/%Y");
}

string SelectTimeViewModel::FormatTime(Time time) const
{
	return DateTimeFormatter::format(DateTime{1970,1,1,time.hour(),time.minute(),time.second()}, "%h:%M %A");
}
