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
	return true;
}

void AudioTrack::remove(const AudioRegion& region) {
}

void AudioTrack::move(const AudioRegion& region, int64 newStartTime) const {
}
