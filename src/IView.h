#pragma once

class IView
{
public:
	virtual ~IView() = default;
	void virtual Render() = 0;
	std::string virtual Name() = 0;
};
