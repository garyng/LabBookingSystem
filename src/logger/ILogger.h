#pragma once

class ILogger
{
public:
	virtual ~ILogger() = default;
	virtual void Debug(std::string message) = 0;
	virtual void Info(std::string message) = 0;
	virtual void Warn(std::string message) = 0;
	virtual void Error(std::string message) = 0;
};
