/*
  ==============================================================================

    AudioRegion.cpp
    Created: 10 Jul 2015 1:15:42pm
    Author:  Thomas

  ==============================================================================
*/

#include "AudioRegion.h"


AudioRegion::AudioRegion(int64 startTime, int64 endTime, int64 position) : _startTime(startTime), _endTime(endTime), _position(position) {
}

void AudioRegion::setNextReadPosition(int64 newPosition) {
	_position = newPosition;
}

int64 AudioRegion::getNextReadPosition() const {
	return _position;
}

int64 AudioRegion::getStartTime() const {
	return _startTime;
}

int64 AudioRegion::getEndTime() const {
	return _endTime;
}

int64 AudioRegion::getTotalLength() const {
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
