#pragma once

#include "audio\AudioService.h"
#include "graphics\VideoService.h"
#include "utility\LoggingService.h"

class ServiceProvider
{
public:
	virtual ~ServiceProvider();

	static void clearServices();

	static audio::AudioService* getAudio();
	static graphics::VideoService* getVideo();
	static utility::LoggingService* getLogging();

	static void provideAudio(audio::AudioService* newAudio);
	static void provideVideo(graphics::VideoService* newVideo);
	static void provideLogging(utility::LoggingService* newLogging);

private:
	//Audio Service
	static audio::AudioService* audio_;
	//Video Service
	static graphics::VideoService* video_;
	//Logging Service
	static utility::LoggingService* logging_;
};