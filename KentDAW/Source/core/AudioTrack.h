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
	bool add(AudioRegion& region);
	void remove(AudioRegion& region);
	void updateTotalLengthIfNeeded(int64 new_end_time);
	bool move(AudioRegion& region, int64 newStartTime);

private:
	std::list<AudioRegion *> regions;
	int _samples;
	double _sampleRate;
	int64 _currentPosition;
	int64 _totalLength;
};


#endif // AUDIO_TRACK_H_INCLUDED

