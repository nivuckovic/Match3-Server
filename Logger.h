#pragma once

#include <iostream>
#include <windows.h> 

class Logger
{
public:
	static void Log(std::string&& name, std::string& message)
	{
		std::cout << name << ": " << message << std::endl;
	}

	static void Log(std::string&& name, std::string&& message)
	{
		std::cout << name << ": " << message << std::endl;
	}

	static void Log(std::string& name, std::string&& message)
	{
		std::cout << name << ": " << message << std::endl;
	}

	static void LogColor(std::string& name, std::string& message, int color)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
	
		std::cout << name + ": ";
		SetConsoleTextAttribute(hConsole, 15);
		
		Log(message);
	}

	static void Log(std::string& name, std::string& message)
	{
		std::cout << name << ": " << message << std::endl;
	}

	static void Log(std::string& message)
	{
		std::cout << message << std::endl;
	}

	static void Log(std::string&& message)
	{
		std::cout << message << std::endl;
	}

};