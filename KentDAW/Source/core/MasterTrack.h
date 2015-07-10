/*
  ==============================================================================

    MasterTrack.h
    Created: 10 Jul 2015 12:52:33pm
    Author:  Matt

  ==============================================================================
*/

#ifndef MASTERTRACK_H_INCLUDED
#define MASTERTRACK_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class MasterTrack : public PositionableAudioSource
{
public:
	MasterTrack(AudioFormatReader* const audioFormatReader,
		double sampleRateOfTheAudioDevice,
		bool enableBuffering);
	~MasterTrack();
	
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
	void releaseResources();
	void getNextAudioBlock(const AudioSourceChannelInfo& info);

	void setNextReadPosition() const;
	int64 getNextReadPosition() const;
	int64 getTotalLength() const;
	bool isLooping() const;	

	void enableBuffering(bool enable);

private:

	double sampleRate;
	int samplesPerBlock;

	AudioSourceChannelInfo  channelInfo;
	AudioSampleBuffer		sampleBuffer;

	int volatile nextPosition;
	int currentPosition;
	int audioBlockEndPosition;

	Array<float*> sample;

	CriticalSection lock;
};

#endif  // MASTERTRACK_H_INCLUDED
