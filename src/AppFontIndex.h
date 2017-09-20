#pragma once

class AppFontIndex
{
private:
	AppFontIndex(int index) : Index(index)
	{
	}

public:
	static AppFontIndex RobotoRegular_Normal;
	static AppFontIndex RobotoLight_Title1;	// 30pt
	static AppFontIndex RobotoBold_Normal;
	static AppFontIndex RobotoRegular_Title;
	static AppFontIndex MaterialIcon_Title;
	static AppFontIndex RobotoLight_Title2;	// 27pt

	const int Index;
	operator int() const { return Index; }
	operator ImFont*() const { return ImGui::GetIO().Fonts->Fonts[Index]; }
};
