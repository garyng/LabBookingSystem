#pragma once
class IStorage
{
public:
	virtual void Save() = 0;
	virtual void Load() = 0;
};
