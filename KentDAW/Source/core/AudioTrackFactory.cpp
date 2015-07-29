/*
  ==============================================================================

    AudioTrackFactory.cpp
    Created: 29 Jul 2015 11:24:28pm
    Author:  Thomas

  ==============================================================================
*/

#include "AudioTrackFactory.h"

AudioTrack * AudioTrackFactory::_build()
{
    return new AudioTrack();
}
