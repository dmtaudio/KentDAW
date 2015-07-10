/*
  ==============================================================================

    AudioMixer.h
    Created: 10 Jul 2015 12:59:41pm
    Author:  Thomas

  ==============================================================================
*/

#ifndef AUDIOMIXER_H_INCLUDED
#define AUDIOMIXER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <list>
#include "AudioTrack.h"

class AudioMixer
{
public:
	AudioMixer();
	~AudioMixer();

private:
	MixerAudioSource mixerAudioSource;
	std::list<AudioTrack *> tracks;
};

#endif  // AUDIOMIXER_H_INCLUDED
