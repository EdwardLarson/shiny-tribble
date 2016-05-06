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

DefaultLoggingService::DefaultLoggingService(const std::string& filename){
	outputFile = filename;
}

DefaultLoggingService::~DefaultLoggingService() {
	//when this object is destroyed, dump the output buffer into a text file
	std::ofstream out_str( outputFile.c_str());
	if (out_str.good()) {
		out_str << "=== BEGIN LOG ===\n";
		out_str << outBuffer;
		out_str.close();
	}else {
		std::cerr << "ERROR: Unable to open file " << outputFile << std::endl;
	}
}

void DefaultLoggingService::log(const std::string& text) {
	//log this text to the output buffer
	std::cout << "LOGGED" << std::endl;
	outBuffer += text;
	outBuffer += '\n';
}