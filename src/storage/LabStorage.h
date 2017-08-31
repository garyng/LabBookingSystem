#pragma once
#include "JsonStorage.h"
#include "models/Lab.h"

class LabStorage
	: public JsonStorage<Lab>
{
protected:
	std::vector<Lab> LoadDefault() override;
	std::string GetDataFilename() override;
};
