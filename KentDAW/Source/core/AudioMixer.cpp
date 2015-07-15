/*
  ==============================================================================

    AudioMixer.cpp
    Created: 11 Jul 2015 1:51:41pm
    Author:  Matt

  ==============================================================================
*/

#include "AudioMixer.h"

AudioMixer::AudioMixer(int sampleRate, int bufferSize) {
	processorGraph = new AudioProcessorGraph();
	inputNode = new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode);
	outputNode = new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode);
	processorGraph->setPlayConfigDetails(0, 2, sampleRate, bufferSize);
	processorGraph->addNode(inputNode);
	processorGraph->addNode(outputNode);
	processorGraph->addConnection(1, 1, 2, 1);
	processorGraph->prepareToPlay(sampleRate, bufferSize);

	trackNumber = 1;
}

AudioMixer::~AudioMixer() {
}

AudioProcessorGraph AudioMixer::getAudioProcessorGraph(){
	//return
}

void AudioMixer::createProcessorFromSource(AudioTrack* source)
{
	//AudioSourceProcessor asProcessor(source, false);
	//sources.push_back(asProcessor);
	//sourceProcessors.set(trackNumber, asProcessor);
	//sources.set(trackNumber, *source);
	//addNode(&asProcessor, trackNumber); //temporary untill other functions written
	//trackNumber++;
}

void AudioMixer::addMuteControl()
{

}

void AudioMixer::addPanningControl()
{

}

void AudioMixer::addFaderControl()
{

}

void AudioMixer::addtoGraph()
{

}

void AudioMixer::removeFromGraph(uint32 trackID)
{
	processorGraph->removeNode(trackID);
}