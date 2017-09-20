#pragma once

namespace date
{
	template <class T>
	T parse_string(std::string fmt, std::string input)
	{
		std::istringstream in{ input };
		T out;
		in >> parse(fmt, out);
		return out;
	}
}