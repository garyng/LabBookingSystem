#pragma once

class IViewModel
{
public:
	virtual ~IViewModel() = default;
	std::string virtual Name() = 0;
};