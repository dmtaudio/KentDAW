/*
  ==============================================================================

    AudioTrackFactory.h
    Created: 29 Jul 2015 11:24:28pm
    Author:  Thomas

  ==============================================================================
*/

#ifndef AUDIOTRACKFACTORY_H_INCLUDED
#define AUDIOTRACKFACTORY_H_INCLUDED

#include "AudioTrack.h"

class AudioTrackFactory {
public:
    static AudioTrack *build()
    {
        static AudioTrackFactory instance;

        return instance._build();
    }

private:
    AudioTrackFactory() {}

    AudioTrack *_build();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioTrackFactory)
};


#endif  // AUDIOTRACKFACTORY_H_INCLUDED
