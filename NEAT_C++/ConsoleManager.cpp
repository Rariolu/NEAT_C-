#include "ConsoleManager.h"

bool ConsoleManager::_enabled = true;

void ConsoleManager::Output(std::string text)
{
	if (_enabled)
	{
		Print(text);
	}
}

void ConsoleManager::Output(double num)
{
	Output(std::to_string(num));
}

void ConsoleManager::SetEnabled(bool enabled)
{
	_enabled = enabled;
}

bool ConsoleManager::GetEnabled()
{
	return _enabled;
}

void ConsoleManager::Print(std::string text)
{
	std::cout << text << std::endl;
}