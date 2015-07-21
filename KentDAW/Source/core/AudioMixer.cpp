/*
  ==============================================================================

    AudioMixer.cpp
    Created: 11 Jul 2015 1:51:41pm
    Author:  Matt

  ==============================================================================
*/

#include "AudioMixer.h"
#include "AudioEngine.h"

AudioMixer::AudioMixer()
			:	trackSources(),
				transportSources(),
				channelStrips(),
				sourceProcessors()
{
	processorGraph = new AudioProcessorGraph();
	AudioIODevice* device = AudioEngine::getSharedAudioDeviceManager().getCurrentAudioDevice();
	int sampleRate = device->getCurrentSampleRate();
	int bufferSize = device->getCurrentBufferSizeSamples();

	slice = new TimeSliceThread("slice");
	
	resetGraph(sampleRate, bufferSize);
	
	//Node number is 3 as input node = node 1 and output node = node 2
	//Track 1 = node 3 Track 1 channel strip = node 4
	//Track 2 = node 4 Track 2 channel strip = node 5 etc...
	nodeNumber = 3;
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
	trackSources.add(track);

	AudioTransportSource* transportSource = new AudioTransportSource();
	transportSource->setSource(track, 0, slice);
	transportSources.add(transportSource);

	AudioSourceProcessor* asProcessor = new AudioSourceProcessor(transportSource, false);
	sourceProcessors.add(asProcessor);

	ChannelStripProcessor* channelStrip = new ChannelStripProcessor();
	channelStrips.add(channelStrip);

	processorGraph->addNode(asProcessor, nodeNumber);
	nodeNumber++;
	processorGraph->addNode(channelStrip, nodeNumber);
	nodeNumber++;
	processorGraph->addConnection(nodeNumber - 1, 1, nodeNumber, 1);
	processorGraph->addConnection(nodeNumber, 1, 2, 1);
}

/*
void AudioMixer::createProcessorFromSource(AudioTrack* source) {
	AudioSourceProcessor* asProcessor = new AudioSourceProcessor(source, false);
	//sources.push_back(asProcessor);
	//sourceProcessors.set(trackNumber, *asProcessor);
	//sources.set(trackNumber, *source);
	processorGraph->addNode(asProcessor, trackNumber); //temporary until other functions written
	//trackNumber++;
}
*/

void AudioMixer::addMuteControl() {

}

void AudioMixer::addPanningControl() {

}

void AudioMixer::addFaderControl() {

}

void AudioMixer::removeFromGraph(uint32 trackID) {
	processorGraph->removeNode(trackID);
}