#pragma once

class DateLibraryTestsView
	: public IView
{
public:

	void Render() override
	{
		using namespace std;
		using namespace date;
		using namespace chrono;

		ImGui::Begin("Debug: Date Library Testing");
		sys_days date = day{17} / jan / 2017;
		sys_time<minutes> time = sys_time<minutes>(20h + 10min);
		date = date + days{ 1 };

		string strDate = format("%d/%m/%Y", date);
		ImGui::PrintValueLabel("Date string:", strDate);

		string strTime = format("%H:%M", time);
		ImGui::PrintValueLabel("Time string:", strTime);

		sys_days parsedDate = parse<sys_days>("%d/%m/%Y", strDate);
		strDate = format("%d/%m/%Y", parsedDate);
		ImGui::PrintValueLabel("Parsed date:", strDate);

		// todo: minute is not working..
		// date + time together?
		strTime = "01/01/1970" + strTime;
		sys_time<minutes> parsedTime = parse<sys_time<minutes>>("%H:%M", strTime);
		strTime = format("%H:%M", parsedTime);
		ImGui::PrintValueLabel("Parsed time:", strTime);

		ImGui::End();
	}

	template <class T>
	T parse(std::string fmt, std::string input)
	{
		std::istringstream in{input};
		T out;
		in >> date::parse(fmt, out);
		return out;
	}

	std::string Name() override { return "DateLibraryTestsView"; }
};
