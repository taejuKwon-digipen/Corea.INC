#include <iostream>    // cout.rdbuf
#include "Logger.h"

Logger::Logger(Logger::Severity severity, bool useConsole, std::chrono::system_clock::time_point startTime) :
	minLevel(severity), outStream("Trace.log"), startTime(startTime) {
	if (useConsole == true) {
		outStream.set_rdbuf(std::cout.rdbuf());
	}
}

Logger::~Logger() {
	outStream.flush();
	outStream.close();
}

void Logger::Log(Logger::Severity severity, std::string message) {
	if (severity >= minLevel) {
		outStream.precision(4);
		outStream << '[' << std::fixed << GetSecondsSinceStart() << "]\t";

		switch (severity) {
		case Severity::Verbose:
			outStream << "Verb \t";
			break;
		case Severity::Debug:
			outStream << "Debug\t";
			break;
		case Severity::Error:
			outStream << "Error\t";
			break;
		case Severity::Event:
			outStream << "Event\t";
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

double Logger::GetSecondsSinceStart() {
	return std::chrono::duration<double>(std::chrono::system_clock::now() - startTime).count();
}