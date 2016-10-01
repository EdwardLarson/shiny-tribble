#include "ServiceProvider.h"

audio::AudioService* ServiceProvider::audio_ = NULL;
graphics::VideoService* ServiceProvider::video_ = NULL;
utility::LoggingService* ServiceProvider::logging_ = NULL;

ServiceProvider::~ServiceProvider(){
}

void ServiceProvider::clearServices() {
	if (audio_ != NULL) delete audio_;
	if (video_ != NULL) delete video_;
	if (logging_ != NULL) delete logging_;
}

audio::AudioService& ServiceProvider::getAudio() {
	if (audio_ == NULL) audio_ = new audio::NullAudioService();
	return *audio_;
}

graphics::VideoService& ServiceProvider::getVideo() {
	if (video_ == NULL) video_ = new graphics::NullVideoService();
	return *video_;
}

utility::LoggingService& ServiceProvider::getLogging() {
	if (logging_ == NULL) logging_ = new utility::NullLoggingService();
	return *logging_;
}

void ServiceProvider::provideAudio(audio::AudioService* newAudio) {
	delete audio_;
	audio_ = newAudio;
}

void ServiceProvider::provideVideo(graphics::VideoService* newVideo) {
	delete video_;
	video_ = newVideo;
}

void ServiceProvider::provideLogging(utility::LoggingService* newLogging) {
	std::cout << "checkpoint i" << std::endl;
	delete logging_;
	std::cout << "checkpoint ii" << std::endl;
	logging_ = newLogging;
}