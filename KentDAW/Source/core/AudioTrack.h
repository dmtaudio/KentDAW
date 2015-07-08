/*
  ==============================================================================

    Track.h
    Created: 7 Jul 2015 3:21:38pm
    Author:  Matt

  ==============================================================================
*/

#ifndef AUDIO_TRACK_H_INCLUDED
#define AUDIO_TRACK_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

namespace audio {
	class Track : public AudioSource {
	public:
		void prepareToPlay(int expectedSamplePerBlock, double sampleRate);
		void releaseResources();
		void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill);
	};
}

#endif // AUDIO_TRACK_H_INCLUDED

