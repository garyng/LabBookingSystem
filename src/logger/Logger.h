#pragma once
#include "ILogger.h"


class Logger
	: public ILogger
{
private:
	Logger() = default;
	static std::shared_ptr<ILogger> _defaultLogger;
public:
	static std::shared_ptr<ILogger> Instance();
};

