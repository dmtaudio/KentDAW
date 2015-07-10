/*
  ==============================================================================

    Track.h
    Created: 10 Jul 2015 1:07:10pm
    Author:  Thomas

  ==============================================================================
*/

#ifndef AUDIO_TRACK_H_INCLUDED
#define AUDIO_TRACK_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioRegion.h"
#include <list>

class AudioTrack : public PositionableAudioSource {
public:

	AudioTrack();
	~AudioTrack();

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void releaseResources() override;
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
	void setNextReadPosition(int64 newPosition) override;
	int64 getNextReadPosition() const override;
	int64 getTotalLength() const override;
	bool isLooping() const override;


	/*
	Check if the region can be added and does not overlap with another one before adding
	*/
	bool add(const AudioRegion& region);
	void remove(const AudioRegion& region);
	void move(const AudioRegion& region, int64 newStartTime) const;

private:
	std::list<AudioRegion *> regions;
};


#endif // AUDIO_TRACK_H_INCLUDED

