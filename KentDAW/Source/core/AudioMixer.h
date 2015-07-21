/*
  ==============================================================================

    AudioMixer.h
    Created: 11 Jul 2015 1:51:41pm
    Author:  Matt

  ==============================================================================
*/

#ifndef AUDIOMIXER_H_INCLUDED
#define AUDIOMIXER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioTrack.h"
#include "ChannelStripProcessor.h"
#include "AudioSourceProcessor.h"

class AudioMixer
{
public:
	AudioMixer();
	~AudioMixer();

	void resetGraph(int sampleRate, int bufferSize);
	ScopedPointer<AudioProcessorGraph> getAudioProcessorGraph();

	void addTrack();
	void removeTrack(int trackNumber);

	void addToGraph(AudioSourceProcessor* asProcessor, ChannelStripProcessor* channelStrip);
	
    
    // level type for meter
    struct Level
    {
        float peak;
        bool isClipping;
    };

private:
	//std::list<AudioSourceProcessor> sources;
	Array<AudioTrack*>trackSources;
	Array<AudioTransportSource*> transportSources;
	Array<ChannelStripProcessor*> channelStrips;
	Array<AudioSourceProcessor*> sourceProcessors;
	TimeSliceThread* slice;
	ScopedPointer<AudioProcessorGraph> processorGraph;
	AudioProcessorGraph::AudioGraphIOProcessor* inputNode;
	AudioProcessorGraph::AudioGraphIOProcessor* outputNode;

	uint32 nodeNumber;
	int trackNumber;
	int sampleRate;
	int bufferSize;
};


#endif  // AUDIOMIXER_H_INCLUDED