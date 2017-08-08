#pragma once

class ViewBase
{
public:
	virtual ~ViewBase() = default;
	void virtual Render();
};
