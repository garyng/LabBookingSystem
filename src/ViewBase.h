#pragma once
#include <imgui.h>

class ViewBase
{
public:
	virtual ~ViewBase() = default;
	void virtual Render();
};
