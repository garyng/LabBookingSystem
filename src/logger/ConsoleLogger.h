#pragma once
#include "ILogger.h"
#include <iostream>

class ConsoleLogger
	: public ILogger
{
public:
	void Debug(std::string message) override
	{
		std::cout << "[Debug] " << message << std::endl;
	}

	void Info(std::string message) override
	{
		std::cout << "[Info] " << message << std::endl;
	}

	void Warn(std::string message) override
	{
		std::cout << "[Warn] " << message << std::endl;
	}

	void Error(std::string message) override
	{
		std::cout << "[Error] " << message << std::endl;
	}
};