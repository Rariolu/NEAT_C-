#ifndef _CONSOLE_MANAGER_H
#define _CONSOLE_MANAGER_H

#include<iostream>
#include<string>

class ConsoleManager
{
	public:
		static void Output(std::string text);
		static void Output(double num);
		static void SetEnabled(bool enabled);
		static void Activate() { SetEnabled(true); }
		static void DeActivate() { SetEnabled(false); }
		static bool GetEnabled();
	private:
		static void Print(std::string text);
		static bool _enabled;
};

#endif