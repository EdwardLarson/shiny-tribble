#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include <cassert>

namespace utility{

class LoggingService{
public:
	virtual ~LoggingService();

	virtual void log(const std::string& text) = 0;

protected:
	std::string outputFile;
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

	virtual void log(const std::string& text);

protected:
	std::string outBuffer;
};

}