/*
  ==============================================================================

    region.h
    Created: 9 Jul 2015 8:35:39pm
    Author:  Matt

  ==============================================================================
*/

#ifndef REGION_H_INCLUDED
#define REGION_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

struct Region
{
	/*
	The UNIQUE ID of a region
	*/
	int regionID;

	/*
	The start position of a region. The time is measured in samples.
	*/
	int startPostion;

	/*
	The end position of a region. The time is measured in samples and represents
	the first sample after the end of the region
	*/
	int endPosition;

	/*
	The point in time where the region begins on the timeline. The time is measured
	in samples.
	*/
	int regionBeginPosition;

	PositionableAudioSource* positionableAudioSource;
};

class AudioMixer : PositionableAudioSource
{
public:
	AudioMixer();
	~AudioMixer();

	/*
	Adds a new region
	*/
	bool addRegion(const int& regionID,
		const int& startPosition,
		const int& endPosition,
		const int& regionBeginPosition,
		const String& absolutePathToFile,
		const double& sampleRateOfAudioDevice);
	
	/*
	Modifies an existing region
	*/
	bool modifyRegion(const int& regionID,
		const int& newStartPosition,
		const int& newEndPosition,
		const int& newRegionBeginPosition);

	/*
	Removes a region
	*/
	bool removeRegion(const int regionID);

	/*
	Removes all regions
	*/
	bool removeAllRegions();

	void enableBuffering(bool enable);
	bool getBufferingState();

	/*
	AudioSource functions
	*/
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
	void prepareAllRegionsToPlay();
	void releaseResources();
	void getNextAudioBlock(const AudioSourceChannelInfo& info);

	/*
	PositionableAudioSource functions
	*/
	void setNextReadPosition(int64 newPosition);
	void setNextReadPositionOnAllRegions(int64 newPosition);
	int64 getReadPosition() const;
	int64 getTotalLength() const;
	bool isLooping() const;

private:
	bool findRegion(const int regionID, int& index);
	
	/*
	A container for each region
	*/
	Array<void*> regions;
	int volatile nextPlayPosition;
	
	int totalLength;
	AudioSampleBuffer sampleBuffer;
	int samplesPerBlockExpected;
	double sampleRate;
	bool bufferingEnabled;

	JUCE_LEAK_DETECTOR(AudioMixer);
};

#endif  // REGION_H_INCLUDED