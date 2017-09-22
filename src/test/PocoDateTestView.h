#pragma once

class PocoDateTestView
	: public IView
{
public:
	void Render() override
	{
		using namespace std;
		using namespace Poco;

		ImGui::Begin("Debug: Poco Date Testing");

		LocalDateTime lnow;
		DateTime now{lnow.timestamp()};

		ImGui::PrintValueLabel("Custom format:", CustomFormat(now));
		ImGui::PrintValueLabel("ISO8601:", ISOFormat(now));
		ImGui::PrintValueLabel("From tm to date:", CustomFormat(from_tm_to_date(tm_today())));
		ImGui::PrintValueLabel("From tm to DateTime:", CustomFormat(from_tm_to_date_time(tm_today())));

		ImGui::Separator();
		string savedString = CustomFormat(now);
		ImGui::PrintValueLabel("Original:", savedString);
		ImGui::PrintValueLabel("From string with custom format:", CustomFormat(ParseCustomeFormat(savedString)));

		ImGui::Separator();

		DateTime base{lnow.timestamp()};
		ImGui::PrintValueLabel("Base:", CustomFormat(base));
		ImGui::PrintValueLabel("+ 30 mins", CustomFormat(base + Timespan{30 * Timespan::MINUTES}));
		ImGui::PrintValueLabel("+ 1 hr", CustomFormat(base + Timespan{1 * Timespan::HOURS}));

		ImGui::End();
	}

	std::string Name() override { return "PocoDateTestView"; }

	Poco::DateTime ParseISODate(std::string str)
	{
		int timezone;
		Poco::DateTime dt;
		Poco::DateTimeParser::parse(Poco::DateTimeFormat::ISO8601_FORMAT, str, dt, timezone);
		return dt;
		// return Poco::LocalDateTime{timezone, dt.timestamp()};
	}

	Poco::DateTime ParseCustomeFormat(std::string str)
	{
		int timezone;
		Poco::DateTime dt;
		Poco::DateTimeParser::parse("%Y/%m/%d %h:%M %A", str, dt, timezone);
		return dt;
	}

	std::string CustomFormat(Poco::DateTime dateTime)
	{
		return Poco::DateTimeFormatter::format(dateTime, "%Y/%m/%d %h:%M %A");
	}

	std::string ISOFormat(Poco::DateTime dateTime)
	{
		return Poco::DateTimeFormatter::format(dateTime, Poco::DateTimeFormat::ISO8601_FORMAT);
	}

	tm tm_today()
	{
		time_t rawTime;
		time(&rawTime);
		tm localTime;
		localtime_s(&localTime, &rawTime);
		return localTime;
	}

	Poco::DateTime from_tm_to_date(tm date)
	{
		return Poco::DateTime{date.tm_year + 1900, date.tm_mon + 1, date.tm_mday};
	}

	Poco::DateTime from_tm_to_date_time(tm dateTime)
	{
		return Poco::DateTime{dateTime.tm_year + 1900, dateTime.tm_mon + 1, dateTime.tm_mday, dateTime.tm_hour, dateTime.tm_min, dateTime.tm_sec};
	}
};
