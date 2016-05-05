#include "AudioService.h"

using namespace audio;

AudioService::~AudioService(){
}

NullAudioService::NullAudioService() {

}

NullAudioService::~NullAudioService() {

}

void NullAudioService::playSound(int soundID) {

}

void NullAudioService::stopSound(int soundID) {

}

void NullAudioService::stopAllSounds() {

}