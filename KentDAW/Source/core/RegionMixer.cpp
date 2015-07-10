/*
  ==============================================================================

    region.cpp
    Created: 9 Jul 2015 8:35:39pm
    Author:  Matt

  ==============================================================================
*/

#include "RegionMixer.h"

AudioRegionMixer::AudioRegionMixer()
	: sampleBuffer(2, 0),
	nextPlayPosition(0),
	totalLength(0),
	samplesPerBlockExpected(0),
	sampleRate(44100.0),
	bufferingEnabled(false)
{
}

AudioRegionMixer::~AudioRegionMixer()
{
	removeAllRegions();
}

bool AudioRegionMixer::addRegion(const int& regionID,
	const int& startPosition,
	const int& endPosition,
	const int& regionBeginPosition,
	const String& abosolutePathToFile,
	const double& sampleRateOfAudioDevice)
{
	int index;
	bool foundTheRegion = findRegion(regionID, index);
	if (foundTheRegion)
	{
		return false;
	}

	File audioFile(abosolutePathToFile);

	AudioFormatManager audioFormatManager;
	audioFormatManager.registerBasicFormats();

	AudioFormatReader* audioFormatReader = audioFormatManager.createReaderFor(audioFile);

	if (audioFormatReader == 0)
	{
		delete audioFormatReader;
		return false;
	}
	else
	{
		Region* audioRegionToAdd = new Region();
		audioRegionToAdd->regionID = regionID;
		audioRegionToAdd->startPostion = startPosition;
		audioRegionToAdd->endPosition = endPosition;
		audioRegionToAdd->regionBeginPosition = regionBeginPosition;

		regions.add(audioRegionToAdd);

		if (totalLength < endPosition)
		{
			totalLength = endPosition;
		}

		return true;
	}
}

bool AudioRegionMixer::modifyRegion(const int& regionID,
	const int& newStartPosition,
	const int& newEndPosition,
	const int& newRegionBeginPosition)
{
	int index;
	bool foundTheRegion = findRegion(regionID, index);

	if (foundTheRegion)
	{
		Region* audioRegionToModify = (Region*)regions[index];

		if (newStartPosition >= newEndPosition
			|| newStartPosition < newRegionBeginPosition
			|| newEndPosition - newRegionBeginPosition
			
	}
}