#pragma once
class AppFontIndex
{
private:
	AppFontIndex(int index): Index(index)
	{
	}

public:
	static AppFontIndex RobotoRegular_Normal;
	static AppFontIndex RobotoLight_Title;
	static AppFontIndex RobotoBold_Normal;

	const int Index;
	operator int() const { return Index; }
	operator ImFont*() const { return ImGui::GetIO().Fonts->Fonts[Index]; }
};

AppFontIndex AppFontIndex::RobotoRegular_Normal(0);
AppFontIndex AppFontIndex::RobotoLight_Title(1);
AppFontIndex AppFontIndex::RobotoBold_Normal(2);
