/*
  ==============================================================================

    Track.cpp
    Created: 7 Jul 2015 3:21:38pm
    Author:  Matt

  ==============================================================================
*/

#include "Track.h"

class Track : public AudioSource
{
public:
    void prepareToPlay(int expectedSamplePerBlock, double sampleRate);
    void releaseResources();
    void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill);
};