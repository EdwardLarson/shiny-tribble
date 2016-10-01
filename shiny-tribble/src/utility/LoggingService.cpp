#include "LoggingService.h"

using namespace utility;

LoggingService::~LoggingService(){
}

//NullLoggingService
//========================================

NullLoggingService::NullLoggingService() {
	outputStream = NULL;
}

NullLoggingService::~NullLoggingService() {

}

void NullLoggingService::log(const std::string& text) {

}

//DefaultLoggingService
//========================================

DefaultLoggingService::DefaultLoggingService(const std::string& filename): outputFile(filename) {
	outputStream = new std::ofstream(filename.c_str());
	if (outputStream->good()) {
		*outputStream << "=== BEGIN LOG === " << ENDL;
	}else {
		std::cerr << "ERROR: Attempt open " << filename << " for logging was unsuccessful" << ENDL;
	}
}

DefaultLoggingService::~DefaultLoggingService() {
	//when this object is destroyed, dump the output buffer into a text file
	if (outputStream != NULL && outputStream->good()) {
		*outputStream << "=== END LOG ===";
		((std::ofstream*) outputStream)->close();
	}
		
	if (outputStream != NULL) delete outputStream;
}

void DefaultLoggingService::log(const std::string& text) {
	//log this text to the output buffer
	if (outputStream != NULL && outputStream->good()) {
		*outputStream << text << std::endl;
	}
}

//ConsoleLoggingService
//========================================

ConsoleLoggingService::ConsoleLoggingService() {
	outputStream = &(std::cout);
}

//CRASH WHEN CALLING THIS FUNCTION
ConsoleLoggingService::~ConsoleLoggingService() {
	std::cout << "in console logging service destructor" << std::endl;
	//could be somehow trying to delete std::cout?
	outputStream = NULL;
	//could be interaction between virtual and inherited destructors?
	std::cout << "no problem?" << std::endl;
}

void ConsoleLoggingService::log(const std::string& text) {
	if (outputStream != NULL) {
		*outputStream << text << std::endl;
	}
}