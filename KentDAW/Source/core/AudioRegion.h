/*
  ==============================================================================

    AudioRegion.h
    Created: 10 Jul 2015 1:15:42pm
    Author:  Thomas

  ==============================================================================
*/

#ifndef AUDIOREGION_H_INCLUDED
#define AUDIOREGION_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class AudioRegion : public PositionableAudioSource {
public:

	virtual ~AudioRegion() {
	}

	virtual int64 getStartTime() const final;
	virtual int64 getEndTime() const final;
	virtual int64 getLength() const final;
	virtual void moveTo(int64 newStartTime, int64 newEndTime) final;
	virtual bool overlaps(const AudioRegion& region) const final;
	virtual bool overlaps(int64 startTime, int64 endTime) const final;

private:
	int64 _startTime;
	int64 _endTime;
	int64 _length;
};


#endif // AUDIOREGION_H_INCLUDED

