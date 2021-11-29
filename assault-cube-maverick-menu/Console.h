#pragma once
#include <Windows.h>
#include <string>
#include <iostream>

class Console {
private:
	HANDLE hConsole;
	BOOL isDebug = false;
public:
	Console(BOOL debug=false)
	{
		AllocConsole();
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		isDebug = debug;
	}

	~Console()
	{
		FreeConsole();
	}

	void SetConsoleColor(int color)
	{
		SetConsoleTextAttribute(hConsole, color);
	}

	void Failure(std::string name)
	{
		if (isDebug)
		{
			SetConsoleColor(0x0C);
			std::cout << "[ Failed ] ";
			SetConsoleColor(15);
			std::cout << name << std::endl;
		}
	}

	void Success(std::string name)
	{
		if (isDebug)
		{
			SetConsoleColor(0x0A);
			std::cout << "[ Success ] ";
			SetConsoleColor(15);
			std::cout << name << std::endl;
		}
	}

	void LogAddress(const char* name, DWORD address)
	{

		if (isDebug)
		{
			SetConsoleColor(14);
			std::cout << "[ Found ] ";
			SetConsoleColor(15);
			std::cout << name << " @ ";
			SetConsoleColor(11);
			std::cout << std::hex << address << std::endl;
			SetConsoleColor(15);
		}
	}

	void LogString(const char* name, std::string address)
	{

		if (isDebug)
		{
			SetConsoleColor(14);
			std::cout << "[ Found ] ";
			SetConsoleColor(15);
			std::cout << name << " @ ";
			SetConsoleColor(11);
			std::cout << address << std::endl;
			SetConsoleColor(15);
		}
	}
	void LogInt(const char* name, int address)
	{

		if (isDebug)
		{
			SetConsoleColor(14);
			std::cout << "[ Found ] ";
			SetConsoleColor(15);
			std::cout << name << " @ ";
			SetConsoleColor(11);
			std::cout << address << std::endl;
			SetConsoleColor(15);
		}
	}

	void Log(std::string name)
	{

		if (isDebug)
		{
			SetConsoleColor(11);
			std::cout << "[ Log ] ";
			SetConsoleColor(15);
			std::cout << name << std::endl;
		}
	}

};
extern Console* _Console;