#include "Logger.h"
#include <memory>

std::shared_ptr<ILogger> Logger::_defaultLogger = nullptr;

std::shared_ptr<ILogger> Logger::Instance()
{
	if (!_defaultLogger)
	{
		_defaultLogger = std::make_shared<ConsoleLogger>();
	}
	return _defaultLogger;
}
