#include "LoggingService.h"

using namespace utility;


LoggingService::~LoggingService(){
}

//NullLoggingService
//========================================

NullLoggingService::NullLoggingService() {

}

NullLoggingService::~NullLoggingService() {

}

void NullLoggingService::log(const std::string& text) {

}

//DefaultLoggingService
//========================================

DefaultLoggingService::DefaultLoggingService(const std::string& filename)
	: outputStream(filename.c_str()){
	if (outputStream.good()) {
		outputStream << "=== BEGIN LOG === " << std::endl;
	}else {
		std::cerr << "ERROR: Attempt open " << filename << " for logging was unsuccessful" << std::endl;
	}
}

DefaultLoggingService::~DefaultLoggingService() {
	//when this object is destroyed, dump the output buffer into a text file
	if (outputStream.good()) {
		outputStream << "=== END LOG ===";
		outputStream.close();
	}
}

void DefaultLoggingService::log(const std::string& text) {
	//log this text to the output buffer
	if (outputStream.good()) {
		outputStream << text << std::endl;
	}
}