#pragma once

class IViewModel
{
public:
	virtual ~IViewModel() = default;
	std::string virtual Name() = 0;
	// reset the view model to its "clean" state
	// will be called by the navigation service 
	void virtual Reset() = 0;
};