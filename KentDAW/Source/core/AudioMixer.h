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

	void addTrack();
	//void createProcessorFromSource(AudioTrack* source);
	void addMuteControl();
	void addPanningControl();
	void addFaderControl();
	
	ScopedPointer<AudioProcessorGraph> getAudioProcessorGraph();

	void addtoGraph();
	void removeFromGraph(uint32 trackID);
	
    
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
	//HashMap<uint32, AudioSourceProcessor> sourceProcessors;
	//HashMap<uint32, AudioTrack> sources; //Not Sure if this is needed
	ScopedPointer<AudioProcessorGraph> processorGraph;
	AudioProcessorGraph::AudioGraphIOProcessor* inputNode;
	AudioProcessorGraph::AudioGraphIOProcessor* outputNode;

	uint64 nodeNumber;
};


#endif  // AUDIOMIXER_H_INCLUDED