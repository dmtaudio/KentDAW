/*
  ==============================================================================

    MasterTrack.cpp
    Created: 10 Jul 2015 12:52:33pm
    Author:  Matt

  ==============================================================================
*/

#include "MasterTrack.h"

MasterTrack::MasterTrack(AudioFormatReader* const audioFormatReader,
	double sampleRateOfTheAudioDevice,
	bool enableBuffering)
	: sampleBuffer(2, 0),
	nextPosition(-1),
	audioBlockEndPosition(-2),
	sampleRate(sampleRateOfTheAudioDevice),
	samplesPerBlock(512)
{
}

MasterTrack::~MasterTrack()
{
}

void MasterTrack::prepareToPlay(int samplesPerBlock_, double sampleRate_)
{
	sampleRate = sampleRate_;
	samplesPerBlock = samplesPerBlock_;
}

void MasterTrack::releaseResources()
{
}

void MasterTrack::getNextAudioBlock(const AudioSourceChannelInfo& info)
{
	audioBlockEndPosition = nextPosition + info.numSamples;
	sampleBuffer.setDataToReferTo(info.buffer->getArrayOfChannels(), 2, info.buffer->getNumSamples());
}