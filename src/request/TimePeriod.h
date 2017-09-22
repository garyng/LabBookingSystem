#pragma once

class TimePeriod
{
private:
	Poco::Data::Time _startTime;
	Poco::Data::Time _endTime;
public:
	Poco::Data::Time StartTime() const { return _startTime; }
	Poco::Data::Time EndTime() const { return _endTime; }

	TimePeriod(const Poco::Data::Time& startTime, const Poco::Data::Time& endTime)
		: _startTime(startTime),
		_endTime(endTime)
	{
	}
};