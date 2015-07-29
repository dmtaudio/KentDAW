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
	sampleRate = device->getCurrentSampleRate();
	bufferSize = device->getCurrentBufferSizeSamples();

	slice = new TimeSliceThread("slice");
	
	resetGraph(sampleRate, bufferSize);
	
	//Node number is 3 as input node = node 1 and output node = node 2
	//Track 1 = node 3 - Track 1 channel strip = node 4
	//Track 2 = node 4 - Track 2 channel strip = node 5 etc...
	trackNumber = 1;
	nodeNumber = 3;
}

AudioMixer::~AudioMixer() {
}

void AudioMixer::resetGraph(int sampleRate, int bufferSize) {
	processorGraph->clear();
	inputNode = new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode);
	outputNode = new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode);
	//processorGraph->setPlayConfigDetails(processorGraph->getNumInputChannels(),processorGraph->getNumOutputChannels(), sampleRate, bufferSize);
	processorGraph->addNode(inputNode, 1);
	processorGraph->addNode(outputNode, 2);
	processorGraph->addConnection(1, 1, 2, 1);
	processorGraph->prepareToPlay(sampleRate, bufferSize);
}

ScopedPointer<AudioProcessorGraph> AudioMixer::getAudioProcessorGraph(){
	return processorGraph;
}

void AudioMixer::addTrack(AudioTrack *track) {
	trackSources.add(track);

	AudioTransportSource* transportSource = new AudioTransportSource();
	transportSource->setSource(track, 0, slice);
	transportSources.add(transportSource);

	AudioSourceProcessor* asProcessor = new AudioSourceProcessor(transportSource, false);
	asProcessor->setTrackNumber(trackNumber);
	trackNumber++;
	sourceProcessors.add(asProcessor);

	ChannelStripProcessor* channelStrip = new ChannelStripProcessor();
	channelStrips.add(channelStrip);

	addToGraph(asProcessor, channelStrip);
}

void AudioMixer::addToGraph(AudioSourceProcessor* asProcessor, ChannelStripProcessor* channelStrip)
{
	processorGraph->addNode(asProcessor, nodeNumber++);
	processorGraph->addNode(channelStrip, nodeNumber++);
	processorGraph->addConnection(nodeNumber - 2, 1, nodeNumber - 1, 1);
	processorGraph->addConnection(nodeNumber - 1, 1, 2, 1);
}

void AudioMixer::removeTrack(int trackNumber)
{
	//Remove track and related processors from arrays
	delete trackSources[trackNumber - 1];
	trackSources.remove(trackNumber - 1);

	delete transportSources[trackNumber - 1];
	transportSources.remove(trackNumber - 1);

	delete sourceProcessors[trackNumber - 1];
	sourceProcessors.remove(trackNumber - 1);

	delete channelStrips[trackNumber - 1];
	channelStrips.remove(trackNumber - 1);
	
	//reset trackNumber and nodeNumber to initial value
	trackNumber = 1;
	nodeNumber = 3;
	//reset the graph to allow track reallocation
	resetGraph(sampleRate, bufferSize);

	//If there are still tracks after removal; Add them back to the graph
	if (sourceProcessors.size() > 0)
	{
		for (int i = 0; i < sourceProcessors.size(); i++)
		{
			sourceProcessors[i]->setTrackNumber(trackNumber);
			trackNumber++;
			addToGraph(sourceProcessors[i], channelStrips[i]);
		}
	}
}

void AudioMixer::start()
{
    for(int i = 0; i < transportSources.size(); ++i)
    {
        transportSources[i]->start();
    }
}

void AudioMixer::stop()
{
    for(int i = 0; i < transportSources.size(); ++i)
    {
        transportSources[i]->stop();
    }
}

void AudioMixer::setPosition(double position)
{
    for(int i = 0; i < transportSources.size(); ++i)
    {
        if(transportSources[i]->getTotalLength() < position)
        {
            transportSources[i]->setPosition(position);
        }
        else
        {
            transportSources[i]->setLooping(false);
            transportSources[i]->setPosition(transportSources[i]->getTotalLength());
        }
    }
}