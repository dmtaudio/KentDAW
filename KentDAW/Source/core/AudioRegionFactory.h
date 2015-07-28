/*
  ==============================================================================

    AudioRegionFactory.h
    Created: 25 Jul 2015 9:58:55pm
    Author:  Thomas

  ==============================================================================
*/

#ifndef AUDIOREGIONFACTORY_H_INCLUDED
#define AUDIOREGIONFACTORY_H_INCLUDED

#include "AudioRegion.h"

class AudioRegionFactory {
public:
    static AudioRegion *build(const String &path, int64 position)
    {
        static AudioRegionFactory instance;
    
        return instance._build(path, position);
    }

private:
    AudioRegionFactory();

    AudioRegion *_build(const String &path, int64 position);

    AudioFormatManager afm;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioRegionFactory)
};

#endif  // AUDIOREGIONFACTORY_H_INCLUDED
