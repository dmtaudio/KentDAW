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
#include "AudioSourceProcessor.h"

class AudioMixer
{
public:
	AudioMixer();
	~AudioMixer();

	void createProcessorFromSource(AudioTrack* source);
	void addMuteControl();
	void addPanningControl();
	void addFaderControl();

	AudioProcessorGraph getAudioProcessorGraph();

	void addtoGraph();
	void removeFromGraph(uint32 trackID);
	int trackNumber;


private:
	//std::list<AudioSourceProcessor> sources;
	HashMap<uint32, AudioSourceProcessor> sourceProcessors;
	HashMap<uint32, AudioTrack> sources; //Not Sure if this is needed
	AudioProcessorGraph* processorGraph;
	AudioProcessorGraph::AudioGraphIOProcessor* inputNode;
	AudioProcessorGraph::AudioGraphIOProcessor* outputNode;

};


#endif  // AUDIOMIXER_H_INCLUDED