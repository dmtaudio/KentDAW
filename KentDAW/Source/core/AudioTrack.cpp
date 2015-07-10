/*
  ==============================================================================

    Track.cpp
    Created: 10 Jul 2015 1:07:10pm
    Author:  Thomas

  ==============================================================================
*/

#include "AudioTrack.h"

AudioTrack::AudioTrack() {

}

AudioTrack::~AudioTrack() {

}

void AudioTrack::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
}

void AudioTrack::releaseResources() {
}

void AudioTrack::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {
}

void AudioTrack::setNextReadPosition(int64 newPosition) {
}

int64 AudioTrack::getNextReadPosition() const {
	return 0;
}

int64 AudioTrack::getTotalLength() const {
	return 0;
}

bool AudioTrack::isLooping() const {
	return true;
}

bool AudioTrack::add(const AudioRegion& region) {
	for (auto existingRegion : regions) {
		if (existingRegion->overlaps(region)) {
			return false;
		}
	}

	regions.push_back(&region);

	return true;
}

void AudioTrack::remove(const AudioRegion& region) {
	regions.remove(&region);
}

bool AudioTrack::move(AudioRegion& region, int64 newStartTime) const {
	auto newEndTime = newStartTime + region.getLength();

	for (auto existingRegion : regions) {
		if (&region != existingRegion && existingRegion->overlaps(newStartTime, newEndTime)) {
			return false;
		}
	}

	region.moveTo(newStartTime, newEndTime);

	return true;
}
