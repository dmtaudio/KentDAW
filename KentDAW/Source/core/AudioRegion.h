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
protected:
	AudioRegion(int64 startTime, int64 endTime, int64 length);
	virtual ~AudioRegion() {
	}

public:

	void setNextReadPosition(int64 newPosition) override;
	int64 getNextReadPosition() const override;
	int64 getTotalLength() const override;

	virtual int64 getStartTime() const final;
	virtual int64 getEndTime() const final;
	virtual void moveTo(int64 newStartTime, int64 newEndTime) final;
	virtual bool overlaps(const AudioRegion& region) const final;
	virtual bool overlaps(int64 startTime, int64 endTime) const final;

protected:
	int64 _startTime;
	int64 _endTime;
	int64 _length;
	int64 _position;
	int _samples;
	double _sampleRate;
};


#endif // AUDIOREGION_H_INCLUDED

