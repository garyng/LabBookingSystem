#pragma once

class TimePeriod
{
private:
	Poco::Data::Time _startTime;
	Poco::Data::Time _endTime;
public:
	Poco::Data::Time StartTime() const { return _startTime; }
	void StartTime(Poco::Data::Time value) { _startTime = value; }

	Poco::Data::Time EndTime() const { return _endTime; }
	void EndTime(Poco::Data::Time value) { _endTime = value; }

	TimePeriod(const Poco::Data::Time& startTime, const Poco::Data::Time& endTime)
		: _startTime(startTime),
		  _endTime(endTime)
	{
	}


};
