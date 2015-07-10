/*
  ==============================================================================

    AudioRegion.cpp
    Created: 10 Jul 2015 1:15:42pm
    Author:  Thomas

  ==============================================================================
*/

#include "AudioRegion.h"

int64 AudioRegion::getStartTime() const {
	return _startTime;
}


int64 AudioRegion::getEndTime() const {
	return _endTime;
}

int64 AudioRegion::getLength() const {
	return _length;
}

void AudioRegion::moveTo(int64 newStartTime, int64 newEndTime) {
	_startTime = newStartTime;
	_endTime = newEndTime;
}

bool AudioRegion::overlaps(const AudioRegion& region) const {
	return overlaps(region.getStartTime(), region.getEndTime());
}

bool AudioRegion::overlaps(int64 startTime, int64 endTime) const {
	return _startTime >= startTime && _startTime <= endTime || _endTime >= startTime && _endTime <= endTime;
}
