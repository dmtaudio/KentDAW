/*
  ==============================================================================

    AudioMixer.h
    Created: 11 Jul 2015 1:51:41pm
    Author:  Matt

  ==============================================================================
*/

#ifndef MIXER_H_INCLUDED
#define MIXER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioTrack.h"
#include "AudioSourceProcessor.h"

class Mixer	: public AudioProcessorGraph
{
public:
	Mixer();
	~Mixer();

	void createProcessorFromSource(AudioTrack* source);
	void addMuteControl();
	void addPanningControl();
	void addFaderControl();

	void addtoGraph();
	void removeFromGraph(uint32 trackID);
	int trackNumber;


private:
	//std::list<AudioSourceProcessor> sources;
	HashMap<uint32, AudioSourceProcessor> sourceProcessors;
	HashMap<uint32, AudioTrack> sources; //Not Sure if this is needed
	AudioGraphIOProcessor* inputNode;
	AudioGraphIOProcessor* outputNode;

};


#endif  // MIXER_H_INCLUDED