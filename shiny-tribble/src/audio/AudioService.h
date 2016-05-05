#pragma once

namespace audio{

class AudioService{
public:
	virtual ~AudioService();

	virtual void playSound(int soundID) = 0;

	virtual void stopSound(int soundID) = 0;

	virtual void stopAllSounds() = 0;
};

class NullAudioService: public AudioService {
public:
	NullAudioService();
	~NullAudioService();

	virtual void playSound(int soundID) override;

	virtual void stopSound(int soundID) override;

	virtual void stopAllSounds() override;
};

}