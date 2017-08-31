#pragma once

class AppColors
{
private:
	AppColors(ImVec4 color) : Color(color)
	{
	}

public:
	static AppColors DefaultWhite;
	static AppColors Red500;
	static AppColors Pink500;
	static AppColors Purple500;
	static AppColors DeepPurple500;
	static AppColors Indigo500;
	static AppColors Blue500;
	static AppColors LightBlue500;
	static AppColors Cyan500;
	static AppColors Teal500;
	static AppColors Green500;
	static AppColors LightGreen500;
	static AppColors Lime500;
	static AppColors Yellow500;
	static AppColors Amber500;
	static AppColors Orange500;
	static AppColors DeepOrange500;
	static AppColors Brown500;
	static AppColors Grey500;
	static AppColors BlueGrey500;

	const ImVec4 Color;
	operator ImVec4() const { return Color; }
};
