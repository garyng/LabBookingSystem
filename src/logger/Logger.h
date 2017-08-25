#pragma once
#include "ConsoleLogger.h"
#include <memory>

class Logger
	: public ILogger
{
private:
	Logger() = default;
	static std::shared_ptr<ILogger> _defaultLogger;
public:
	static std::shared_ptr<ILogger> Instance();
};

