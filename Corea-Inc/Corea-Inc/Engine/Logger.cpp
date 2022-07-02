#include <iostream>    // cout.rdbuf
#include "Logger.h"
#include <stdio.h>
#include <windows.h>
#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15 
#define PINK 16
#define ORANGE 17

Logger::Logger(Logger::Severity severity, Part part, bool useConsole, std::chrono::system_clock::time_point startTime) :
	minLevel(severity), outStream("Trace.log"), startTime(startTime)
{
	if (useConsole == true) {
		outStream.set_rdbuf(std::cout.rdbuf());
	}
}

Logger::~Logger()
{
	outStream.flush();
}

void Logger::Log(Logger::Severity severity, Part part, std::string message)
{
	if (severity >= minLevel) {
		outStream.precision(4);
		outStream << '[' << std::fixed << GetSecondsSinceStart() << "]\t";

		switch (severity) {
		case Severity::Verbose:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGRAY);
			outStream << "Verb \t";
			break;
		case Severity::Debug:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
			outStream << "Debug\t";
			break;
		case Severity::Error:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
			outStream << "Error\t";
			break;
		case Severity::Event:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTBLUE);
			outStream << "Event\t";
			break;
		}
		
		switch (part)
		{
		case Part::Item:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED);
			outStream << "ITEM PART \t";
			break;
		case Part::Field:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGRAY);
			outStream << "FIELD PART \t";
			break;
		case Part::HumanR:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTMAGENTA);
			outStream << "HUMAN RESOURCES PART \t";
			break;
		case Part::Enemy:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ORANGE);
			outStream << "ENEMY PART \t";
			break;
		case Part::Entire:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			outStream << "ENTIRE PART \t";
			break;
		}
		outStream << message;

#ifdef _DEBUG
		outStream << std::endl;
#else
		outStream << '\n';
#endif
	}
}

double Logger::GetSecondsSinceStart()
{
	return std::chrono::duration<double>(std::chrono::system_clock::now() - startTime).count();
}

void Logger::TextFile()
{
	using namespace std;
	ofstream logger;
	logger.open("Log Data");

	if (!logger)
	{
		cerr << "Can not find File" << endl;
		ofstream("Log Data");
		exit(100);
	}

	logger << GetSecondsSinceStart();
}