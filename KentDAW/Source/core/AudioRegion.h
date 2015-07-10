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

class AudioRegion {
public:

	virtual ~AudioRegion() {
	}

	int64 getStartTime() const;
	int64 getEndTime() const;
	int64 getLength() const;
	void moveTo(int64 newStartTime, int64 newEndTime);
	bool overlaps(const AudioRegion& region) const;
	bool overlaps(int64 startTime, int64 endTime) const;

private:
	int64 _startTime;
	int64 _endTime;
	int64 _length;
};


#endif // AUDIOREGION_H_INCLUDED

