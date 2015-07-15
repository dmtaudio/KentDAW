/*
  ==============================================================================

    Mixer.cpp
    Created: 11 Jul 2015 1:51:41pm
    Author:  Matt

  ==============================================================================
*/

#include "Mixer.h"

Mixer::Mixer() {
	inputNode = new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode);
	outputNode = new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode);
	setPlayConfigDetails(0, 2, 44100, 512);
	addNode(inputNode);
	addNode(outputNode);
	addConnection(1, 1, 2, 1);
	prepareToPlay(44100, 512);

	trackNumber = 1;
}

Mixer::~Mixer() {
}

void Mixer::createProcessorFromSource(AudioTrack* source)
{
	AudioSourceProcessor asProcessor(source, false);
	//sources.push_back(asProcessor);
	sourceProcessors.set(trackNumber, asProcessor);
	sources.set(trackNumber, *source);
	addNode(&asProcessor, trackNumber); //temporary untill other functions written
	trackNumber++;
}

void Mixer::addMuteControl()
{

}

void Mixer::addPanningControl()
{

}

void Mixer::addFaderControl()
{

}

void Mixer::addtoGraph()
{

}

void Mixer::removeFromGraph(uint32 trackID)
{
	removeNode(trackID);
}