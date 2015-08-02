/*
  ==============================================================================

    AudioMixer2.cpp
    Created: 1 Aug 2015 10:23:26am
    Author:  dtl

  ==============================================================================
*/

#include "AudioMixer2.h"
#include "AudioEngine.h"
#include "AudioSourceProcessor.h"


AudioMixer2::AudioMixer2()
: currentProcessor()
{
    int iChannels(2), oChannels(2);
    double sampleRate(0.0f);
    int bufferSize(0);
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

AudioMixer2::~AudioMixer2(){}

void AudioMixer2::resetGraph()
{
    processorGraph->clear();
    createDefaultNodes();
    
}

void AudioMixer2::remapGraph()
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

void AudioMixer2::createDefaultNodes()
{
    AudioProcessorGraph::AudioGraphIOProcessor* inputNode = new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode);
    AudioProcessorGraph::AudioGraphIOProcessor* outputNode = new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode);

    processorGraph->addNode(inputNode, INPUT_NODE_ID);
    processorGraph->addNode(outputNode, OUTPUT_NODE_ID);
}

void AudioMixer2::addTrack(AudioTrack *track)
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
        
        ChannelStripProcessor* stripProcessor = new ChannelStripProcessor();
        processorGraph->addNode(stripProcessor, mixerNodeID);
        channelStripMap.set(mixerNodeID, stripProcessor);
        processorGraph->addConnection(trackNodeID, 0, mixerNodeID, 0);
        processorGraph->addConnection(trackNodeID, 1, mixerNodeID, 1);
        
        processorGraph->addConnection(mixerNodeID, 0, OUTPUT_NODE_ID, 0);
        processorGraph->addConnection(mixerNodeID, 1, OUTPUT_NODE_ID, 1);
        ++trackNodeID;
        ++mixerNodeID;
    }
}

void AudioMixer2::removeTrack(int trackNumber)
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
}

AudioProcessorGraph* AudioMixer2::getProcessorGraph()
{
    return processorGraph;
}

void AudioMixer2::start()
{
    HashMap<int, AudioTransportSource*>::Iterator i (transportMap);
    
    while(i.next())
    {
        i.getValue()->setNextReadPosition(0);
        i.getValue()->start();
    }
}

void AudioMixer2::stop()
{
    HashMap<int, AudioTransportSource*>::Iterator i (transportMap);
    
    while(i.next())
    {
        i.getValue()->stop();
    }
}

void AudioMixer2::setPosition(double position)
{
    for(int i = 0; i < transportMap.size(); ++i)
    {
        if(transportMap[i]->getTotalLength() < position)
            transportMap[i]->setPosition(position);
        else
        {
            transportMap[i]->setLooping(false);
            transportMap[i]->setPosition(transportMap[i]->getTotalLength());
        }
    }
}


