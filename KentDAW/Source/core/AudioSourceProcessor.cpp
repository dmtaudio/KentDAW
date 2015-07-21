/*
  ==============================================================================

    AudioSourceProcessor.cpp
    Created: 13 Jul 2015 11:03:02am
    Author:  dtl

  ==============================================================================
*/

#include "AudioSourceProcessor.h"

AudioSourceProcessor::AudioSourceProcessor(AudioSource* const input, const bool deleteSource_)
: source(input),
  deleteSource(deleteSource_)
{}

AudioSourceProcessor::~AudioSourceProcessor()
{
    if(deleteSource)
        delete source;
}

void AudioSourceProcessor::setTrackNumber(int newTrackNumber)
{
	trackNumber = newTrackNumber;
}

const String AudioSourceProcessor::getName() const
{
    return String("AudioSourceWrapper");
}

const String AudioSourceProcessor::getInputChannelName(const int channelIndex) const
{
    return String(channelIndex + 1);
}

const String AudioSourceProcessor::getOutputChannelName(const int channelIndex) const
{
    return String(channelIndex + 1);
}

void AudioSourceProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    source->prepareToPlay(samplesPerBlock, sampleRate);
}

void AudioSourceProcessor::releaseResources()
{
    source->releaseResources();
}

void AudioSourceProcessor::processBlock(AudioSampleBuffer &buffer, MidiBuffer &midiMessages)
{
    AudioSourceChannelInfo channelInfo;
    channelInfo.buffer = &buffer;
    channelInfo.startSample = 0;
    channelInfo.numSamples = buffer.getNumSamples();
    source->getNextAudioBlock(channelInfo);
    
}