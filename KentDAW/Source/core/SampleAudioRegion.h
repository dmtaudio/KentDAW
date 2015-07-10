/*
  ==============================================================================

    SampleAudioRegion.h
    Created: 10 Jul 2015 1:28:41pm
    Author:  Thomas

  ==============================================================================
*/

#ifndef SAMPLEAUDIOREGION_H_INCLUDED
#define SAMPLEAUDIOREGION_H_INCLUDED
#include "AudioRegion.h"

class SampleAudioRegion : public AudioRegion {

public:
	SampleAudioRegion(AudioFormatReader* sample, int64 startTime, bool shouldLoop = false);

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

	void releaseResources() override;

	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;

	bool isLooping() const override;

private:
	AudioSampleBuffer _buffer;
	bool _shouldLoop;
	AudioFormatReader* _reader;
};


#endif // SAMPLEAUDIOREGION_H_INCLUDED

