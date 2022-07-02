#pragma once
#include <string>	// std::string
#include <fstream>		// std::ofstream
#include <iostream>
#include <chrono>    // std::chrono
#include "ScenePart.h"

class Logger
{
public:
	enum class Severity
	{
		Verbose,		// This option is for minor messages, which could be useful 
		Debug,			// This should only be used when you are currently trying to debug something
		Event,			// These are general events, such as key press, exit state, enter state, enter state finish
		Error,			// This is for an error, such as an asset is not found
	};
	Logger(Severity severity, Part part, bool useConsole, std::chrono::system_clock::time_point startTime);
	~Logger();
	void LogError(Part part, std::string text) { Log(Severity::Error, part, text); }
	void LogEvent(Part part, std::string text) { Log(Severity::Event, part, text); }
	void LogDebug(Part part, std::string text) { Log(Severity::Debug, part, text); }
	void LogVerbose(Part part, std::string text) { Log(Severity::Verbose, part, text); }
	void TextFile();

private:
	void Log(Severity, Part part, std::string displayText);
	double GetSecondsSinceStart();
	std::ofstream outStream;
	Severity minLevel;
	std::chrono::system_clock::time_point startTime;
};