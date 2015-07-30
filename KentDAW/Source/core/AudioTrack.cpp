/*
  ==============================================================================

    Track.cpp
    Created: 10 Jul 2015 1:07:10pm
    Author:  Thomas

  ==============================================================================
*/

#include "AudioTrack.h"

AudioTrack::AudioTrack() : _samples(0), _sampleRate(0), _currentPosition(0), _totalLength(0) {

}

AudioTrack::~AudioTrack() {

}

void AudioTrack::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
	_samples = samplesPerBlockExpected;
	_sampleRate = sampleRate;

	for (auto region : regions) {
		region->prepareToPlay(samplesPerBlockExpected, sampleRate);
	}
}

void AudioTrack::releaseResources() {
	for (auto region : regions) {
		region->releaseResources();
	}
}

void AudioTrack::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {
	for (auto region : regions) {
		if (region->getStartTime() >= _currentPosition && region->getEndTime() <= _currentPosition) {
			region->getNextAudioBlock(bufferToFill);

			break;
		}
	}

	_currentPosition += 1;
}

void AudioTrack::setNextReadPosition(int64 newPosition) {
	_currentPosition = newPosition;
}

int64 AudioTrack::getNextReadPosition() const {
	return _currentPosition;
}

int64 AudioTrack::getTotalLength() const {
	return _totalLength;
}

bool AudioTrack::isLooping() const {
	return false;
}

bool AudioTrack::add(AudioRegion& region) {
	for (auto existingRegion : regions) {
		if (existingRegion->overlaps(region)) {
			return false;
		}
	}

	regions.push_back(&region);

	updateTotalLengthIfNeeded(region.getEndTime());
    region.prepareToPlay(_samples, _sampleRate);

	return true;
}

void AudioTrack::remove(AudioRegion& region) {
	regions.remove(&region);

	if (region.getEndTime() == _totalLength) {
		_totalLength = 0;

		for (auto existingRegion : regions) {
			if (_totalLength < existingRegion->getEndTime()) {
				_totalLength = existingRegion->getEndTime();
			}
		}
	}
}

bool AudioTrack::move(AudioRegion& region, int64 newStartTime) {
	auto newEndTime = newStartTime + region.getTotalLength();

	for (auto existingRegion : regions) {
		if (&region != existingRegion && existingRegion->overlaps(newStartTime, newEndTime)) {
			return false;
		}
	}

	region.moveTo(newStartTime, newEndTime);

	updateTotalLengthIfNeeded(newEndTime);

	return true;
}

void AudioTrack::updateTotalLengthIfNeeded(int64 newEndTime) {
	if (newEndTime > _totalLength) {
		_totalLength = newEndTime;
	}
}
