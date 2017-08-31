#pragma once
#include "JsonStorage.h"
#include "models/Request.h"

class RequestStorage
	: public JsonStorage<Request>
{
protected:
	std::vector<Request> LoadDefault() override;
	std::string GetDataFilename() override;
	
};
