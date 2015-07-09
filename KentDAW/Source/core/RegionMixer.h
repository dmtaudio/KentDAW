/*
  ==============================================================================

    region.h
    Created: 9 Jul 2015 8:35:39pm
    Author:  Matt

  ==============================================================================
*/

#ifndef REGION_H_INCLUDED
#define REGION_H_INCLUDED

#include "Region.h"
#include "../JuceLibraryCode/JuceHeader.h"

class AudioRegionMixer : PositionableAudioSource
{
	AudioRegionMixer();
	~AudioRegionMixer();

	bool addRegion(const int& regionID,
		const int& startPosition,
		const int& endPosition,
		const int& regionBeginPosition,
		const String& absolutePathToFile,
		const double& sampleRateOfAudioDevice);
	bool modifyRegion(const int& regionID,
		const int& newStartPosition,
		const int& newEndPosition,
		const int& newRegionBeginPosition);
	bool removeRegion(const int regionID);
	bool removeAllRegions();

	void enableBuffering(bool enable);
	bool getBufferingState();

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
	void prepareAllRegionsToPlay();
	void releaseResources();
	void getNextAudioBlock(const AudioSourceChannelInfo& info);

	void setNextReadPosition(int64 newPosition);
	void setNextReadPositionOnAllRegions(int64 newPosition);
	int64 getReadPosition() const;
	int64 getTotalLength() const;
	bool isLooping() const;

private:

	bool findRegion(const int regionID, int& index);
	Array<void*> regions;
	int volatile nextPlayPosition;
	
	int totalLength;
	AudioSampleBuffer tempBuffer;
	int samplesPerBlockExpected;
	double sampleRate;
	bool bufferingEnabled;

	JUCE_LEAK_DETECTOR(AudioRegionMixer);
};

#endif  // REGION_H_INCLUDED