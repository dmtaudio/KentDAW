/*
  ==============================================================================

    SampleAudioRegion.cpp
    Created: 10 Jul 2015 1:28:41pm
    Author:  Thomas

  ==============================================================================
*/

#include "SampleAudioRegion.h"

SampleAudioRegion::SampleAudioRegion(AudioFormatReader* reader, int64 startTime, bool shouldLoop) :
	AudioRegion(startTime, startTime - reader->lengthInSamples, reader->lengthInSamples), _shouldLoop(shouldLoop), _reader(reader) {
}

void SampleAudioRegion::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
	_samples = samplesPerBlockExpected;
	_sampleRate = sampleRate;
}

void SampleAudioRegion::releaseResources() {
}

void SampleAudioRegion::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {
	_reader->read(bufferToFill.buffer, 0, _samples, _position, true, true);
}

bool SampleAudioRegion::isLooping() const {
	return _shouldLoop;
}
