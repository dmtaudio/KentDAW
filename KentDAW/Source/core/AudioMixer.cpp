/*
  ==============================================================================

    AudioMixer.cpp
    Created: 1 Aug 2015 10:23:26am
    Author:  dtl

  ==============================================================================
*/

#include "AudioMixer.h"
#include "AudioEngine.h"
#include "AudioSourceProcessor.h"


AudioMixer::AudioMixer()
: currentProcessor()
{
    int iChannels(2), oChannels(2);
    sampleRate = 0.0;
    bufferSize = 0;
    trackNodeID = 4000;
    mixerNodeID = 5000;
    AudioIODevice* current = AudioEngine::getSharedAudioDeviceManager().getCurrentAudioDevice();
    sampleRate = current->getCurrentSampleRate();
    bufferSize = current->getCurrentBufferSizeSamples();
    
    processorGraph = new AudioProcessorGraph();
    
    processorGraph->setPlayConfigDetails(iChannels, // number of inputs
                         oChannels, // number of outputs
                         sampleRate, // sampleRate
                         bufferSize);
    
}

AudioMixer::~AudioMixer()
{
    processorGraph->clear();
    delete processorGraph;
}

void AudioMixer::resetGraph()
{
    processorGraph->clear();
    createDefaultNodes();
}

void AudioMixer::createDefaultNodes()
{
    auto input = new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode);
    auto output = new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode);
    processorGraph->addNode(input, INPUT_NODE_ID);
    processorGraph->addNode(output, OUTPUT_NODE_ID);
}

void AudioMixer::addTrack(AudioTrack *track)
{
    if(track != 0)
    {
        trackMap.set(trackNodeID, track);
        AudioTransportSource* trackTransport = new AudioTransportSource();
        trackTransport->setSource(track);
        transportMap.set(trackNodeID, trackTransport);
        AudioSourceProcessor* trackProcessor = new AudioSourceProcessor(trackTransport, false);
        sourceProcessorMap.set(trackNodeID, trackProcessor);
        processorGraph->addNode(trackProcessor, trackNodeID);
        trackProcessor->setPlayConfigDetails(2, 2, sampleRate, bufferSize);
        
        ChannelStripProcessor* stripProcessor = new ChannelStripProcessor();
        processorGraph->addNode(stripProcessor, mixerNodeID);
        stripProcessor->setPlayConfigDetails(2, 2, sampleRate, bufferSize);
        channelStripMap.set(mixerNodeID, stripProcessor);
        processorGraph->addConnection(trackNodeID, 0, mixerNodeID, 0);
        processorGraph->addConnection(trackNodeID, 1, mixerNodeID, 1);
        
        
        processorGraph->addConnection(mixerNodeID, 0, OUTPUT_NODE_ID, 0);
        processorGraph->addConnection(mixerNodeID, 1, OUTPUT_NODE_ID, 1);
        ++trackNodeID;
        ++mixerNodeID;
    }
}

void AudioMixer::remapGraph()
{
    int node = 4000;
    HashMap<int, AudioTrack*>::Iterator track (trackMap);
    while(track.next())
    {
        trackMap.set(node, track.getValue());
        ++node;
    }
    trackMap.remove(trackMap.size() - 1);
    node = 4000;
    HashMap<int, AudioTransportSource*>::Iterator transport (transportMap);
    while(transport.next())
    {
        transportMap.set(node, transport.getValue());
        ++node;
    }
    transportMap.remove(transportMap.size() - 1);
    node = 4000;
    HashMap<int, AudioSourceProcessor*>::Iterator processor (sourceProcessorMap);
    while(processor.next())
    {
        sourceProcessorMap.set(node, processor.getValue());
        processorGraph->addNode(processor.getValue(), node);
        ++node;
    }
    sourceProcessorMap.remove(sourceProcessorMap.size() - 1);
    node = 5000;
    HashMap<int, ChannelStripProcessor*>::Iterator channelStrip (channelStripMap);
    while(channelStrip.next())
    {
        channelStripMap.set(node, channelStrip.getValue());
        processorGraph->addNode(channelStrip.getValue(), node);
        processorGraph->addConnection(node, 0, node - 1000, 0);
        processorGraph->addConnection(node, 1, node - 1000, 1);
        processorGraph->addConnection(node, 0, OUTPUT_NODE_ID, 0);
        processorGraph->addConnection(node, 1, OUTPUT_NODE_ID, 1);
        ++node;
    }
    channelStripMap.remove(channelStripMap.size() - 1);
}

void AudioMixer::removeTrack(int trackNumber)
{
    resetGraph();
    int node = 4000 + (trackNumber - 1);
    HashMap<int, AudioTrack*>::Iterator track (trackMap);
    while(track.next())
    {
        if(track.getKey() == node)
        {
            delete track.getValue();
        }
    }
    trackMap.remove(node);
    HashMap<int, AudioTransportSource*>::Iterator transport (transportMap);
    while(transport.next())
    {
        if(transport.getKey() == node)
        {
            delete transport.getValue();
        }
    }
    transportMap.remove(node);
    HashMap<int, AudioSourceProcessor*>::Iterator source(sourceProcessorMap);
    while(source.next())
    {
        if(source.getKey() == node)
        {
            delete source.getValue();
        }
    }
    sourceProcessorMap.remove(node);
    node = 5000 + (trackNumber - 1);
    HashMap<int, ChannelStripProcessor*>::Iterator channelStrip(channelStripMap);
    while(channelStrip.next())
    {
        if(source.getKey() == node)
        {
            delete source.getValue();
        }
    }
    channelStripMap.remove(node);
	remapGraph();
}

AudioProcessorGraph* AudioMixer::getProcessorGraph()
{
    return processorGraph;
}

void AudioMixer::start()
{
    HashMap<int, AudioTransportSource*>::Iterator i (transportMap);
    
    while(i.next())
    {
        i.getValue()->setNextReadPosition(0);
        i.getValue()->start();
    }
}

void AudioMixer::stop()
{
    HashMap<int, AudioTransportSource*>::Iterator i (transportMap);
    
    while(i.next())
    {
        i.getValue()->stop();
    }
}

void AudioMixer::setPosition(int position)
{
    for(int i = 0; i < transportMap.size(); i++)
    {
        transportMap[i]->setPosition(position);
        _position = position;
    }
}

int AudioMixer::getPosition()
{
    return _position;
}



