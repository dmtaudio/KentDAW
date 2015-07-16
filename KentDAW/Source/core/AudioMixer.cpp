/*
  ==============================================================================

    AudioMixer.cpp
    Created: 11 Jul 2015 1:51:41pm
    Author:  Matt

  ==============================================================================
*/

#include "AudioMixer.h"

AudioMixer::AudioMixer() {
	processorGraph = new AudioProcessorGraph();
	trackNumber = 1;
}

AudioMixer::~AudioMixer() {
}

void AudioMixer::resetGraph(int sampleRate, int bufferSize) {
	processorGraph->clear();
	inputNode = new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode);
	outputNode = new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode);
	//processorGraph->setPlayConfigDetails(processorGraph->getNumInputChannels(),processorGraph->getNumOutputChannels(), sampleRate, bufferSize);
	processorGraph->addNode(inputNode);
	processorGraph->addNode(outputNode);
	processorGraph->addConnection(1, 1, 2, 1);
	processorGraph->prepareToPlay(sampleRate, bufferSize);
}

ScopedPointer<AudioProcessorGraph> AudioMixer::getAudioProcessorGraph(){
	return processorGraph;
}

void AudioMixer::addTrack() {
	AudioTrack* track = new AudioTrack();
	createProcessorFromSource(track);
}

void AudioMixer::createProcessorFromSource(AudioTrack* source) {
	AudioSourceProcessor* asProcessor = new AudioSourceProcessor(source, false);
	//sources.push_back(asProcessor);
	//sourceProcessors.set(trackNumber, *asProcessor);
	//sources.set(trackNumber, *source);
	processorGraph->addNode(asProcessor, trackNumber); //temporary until other functions written
	//trackNumber++;
}

void AudioMixer::addMuteControl() {

}

void AudioMixer::addPanningControl() {

}

void AudioMixer::addFaderControl() {

}

void AudioMixer::removeFromGraph(uint32 trackID) {
	processorGraph->removeNode(trackID);
}