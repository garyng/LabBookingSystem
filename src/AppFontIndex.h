#pragma once
#include "test/AppColorsTestView.h"

class AppFontIndex
{
private:
	AppFontIndex(int index) : Index(index)
	{
	}

public:
	static AppFontIndex RobotoRegular_Normal;
	static AppFontIndex RobotoLight_Title;
	static AppFontIndex RobotoBold_Normal;
	static AppFontIndex RobotoRegular_Title;

	const int Index;
	operator int() const { return Index; }
	operator ImFont*() const { return ImGui::GetIO().Fonts->Fonts[Index]; }
};