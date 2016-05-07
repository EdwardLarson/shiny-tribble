#pragma once

#include <string>
#include <fstream>
#include <iostream>

#define ENDL '\n'

namespace utility{

class LoggingService{
public:
	virtual ~LoggingService();

	virtual void log(const std::string& text) = 0;

	template <class T>
	friend LoggingService& operator<<(LoggingService& ls, const T& item);

protected:
	std::ostream* outputStream;
};

class NullLoggingService: public LoggingService {
public:
	NullLoggingService();
	virtual ~NullLoggingService();

	virtual void log(const std::string& text) override;
};

class DefaultLoggingService : public LoggingService {
public:
	DefaultLoggingService(const std::string& filename);
	virtual ~DefaultLoggingService();

	virtual void log(const std::string& text) override;

protected:
	std::string outputFile;
};

class ConsoleLoggingService : public LoggingService {
public:
	ConsoleLoggingService();
	virtual ~ConsoleLoggingService();

	virtual void log(const std::string& text) override;
};

template <class T>
LoggingService& operator<<(LoggingService& ls, const T& item) {
	if (ls.outputStream != NULL) (*(ls.outputStream)) << item;

	return ls;
}

}