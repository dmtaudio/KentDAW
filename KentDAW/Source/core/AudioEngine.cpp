/*
 * File:   AudioEngine.cpp
 * Author: Dan
 *
 * Created on 02 June 2015, 16:34
 *
 * AudioCallBack implementation derived from AudioSourcePlayer and AudioProcessorPlayer with custom code
 * and modifications.
 */

#include "AudioEngine.h"

static ScopedPointer<AudioDeviceManager> sharedAudioDeviceManager;

AudioCallBack::AudioCallBack()
: source(nullptr), sourcePlayer(nullptr),
  processor(nullptr), processorPlayer(nullptr),
  sampleRate(0), bufferSize(0),
  numInputChannels(0), numOutputChannels(0),
  ,tempBuffer(), messageCollector()
{
}

// set player source to null
AudioCallBack::~AudioCallBack()
{
    setAudioSourcePlayer(nullptr);
    setProcessorPlayer(nullptr);
}

// set the audio source for the player - takes an AudioSource.
void AudioCallBack::setAudioSourcePlayer(AudioSource *newSource)
{
    sourcePlayer->setSource(newSource);
    sourceSet = true;
    processorSet = false;
}

// set the audio processor for the player - takes an AudioProcessor
void AudioCallBack::setProcessorPlayer(AudioProcessor *newProcessor)
{
    processorPlayer->setProcessor(newProcessor);
    processorSet = true;
    sourceSet = false;
}

void AudioCallBack::unsetAudioSourcePlayer()
{
    setAudioSourcePlayer(nullptr);
    sourceSet = false;
}

void AudioCallBack::unsetProcessorPlayer()
{
    setProcessorPlayer(nullptr);
    processorSet = false;
}


void AudioCallBack::audioDeviceIOCallback(const float** inputChannelData, int totalNumInputChannels, float** outputChannelData, int totalNumOutputChannels, int numSamples)
{
    jassert(sampleRate > 0 && bufferSize > 0);
    
    const ScopedLock sl(lock);

    incomingMidi.clear();
    messageCollector.removeNextBlockOfMessages(incomingMidi, numSamples);

    
    if(sourceSet)
    sourcePlayer->audioDeviceIOCallback(inputChannelData, totalNumInputChannels, outputChannelData, totalNumInputChannels, numSamples);

    if(processorSet)
    processorPlayer->audioDeviceIOCallback(inputChannelData, totalNumInputChannels, outputChannelData, totalNumOutputChannels, numSamples);
}

void AudioCallBack::audioDeviceAboutToStart(AudioIODevice* device)
{
    if(processorSet)
    {
        const double newSampleRate = device->getCurrentSampleRate();
        const int newBufferSize = device->getCurrentSampleRate();
        const BigInteger numInputChannels = device->getActiveInputChannels();
        const BigInteger numOutputChannels = device->getActiveOutputChannels();
        
        const ScopedLock sl (lock);
        
        sampleRate = newSampleRate;
        bufferSize = newBufferSize;
        numChannelsIn = numInputChannels;
        numChannelsOut = numOutputChannels;
        
        messageCollector.reset(sampleRate);
        channels.calloc((size_t) jmax(numInputChannels, numOutputChannels) + 2);
        
        if(processor != nullptr)
        {
            if(isPrepared)
                processor->releaseResources();
            
            AudioProcessor* const oldProcessor = processor;
            setProcessor(nullptr);
            setProcessor(oldProcessor);
        }
    }
    else if(sourceSet)
    {
        sampleRate = device->getCurrentSampleRate();
        bufferSize = device->);
        
    }
}

void AudioCallBack::audioDeviceStopped()
{
    const ScopedLock sl(lock);
    
    if((processor != nullptr && isPrepared) || source != nullptr)
    {
        processor->releaseResources();
        source->releaseResources();
    }
    sampleRate = 0.0;
    bufferSize = 0;
    isPrepared = false;
    tempBuffer.setSize(1, 1);

void AudioCallBack::handleIncomingMidiMessage(MidiInput* input, const MidiMessage& message)
{
    messageCollector.addMessageToQueue(message);
}

AudioEngine::AudioEngine()
{
}

AudioEngine::~AudioEngine()
{
    sharedAudioDeviceManager = nullptr;
}

AudioDeviceManager& AudioEngine::getSharedAudioDeviceManager()
{
    if(sharedAudioDeviceManager == nullptr)
    {
        sharedAudioDeviceManager = new AudioDeviceManager();
        sharedAudioDeviceManager->initialise(2, 2, 0, true, String::empty, 0);
    }
    return *sharedAudioDeviceManager;
}

double AudioEngine::getDeviceSampleRate()
{
    if(sharedAudioDeviceManager != nullptr)
    {
        deviceSampleRate = sharedAudioDeviceManager->getCurrentAudioDevice()->getCurrentSampleRate();
        return deviceSampleRate;
    }
    else
    {
        // no samplerate, set to 0.0
        return 0.0;
    }
}

int AudioEngine::getBitDepth()
{
    if(sharedAudioDeviceManager != nullptr)
    {
        deviceBitDepth = sharedAudioDeviceManager->getCurrentAudioDevice()->getCurrentBitDepth();
        return deviceBitDepth;
    }
    else
    {
        return 0;
    }
}

BigInteger AudioEngine::getDeviceChannels(ChannelType type)
{
    if(sharedAudioDeviceManager != nullptr)
    {
        if(type == INPUT)
        {
            deviceInputChannels = sharedAudioDeviceManager->getCurrentAudioDevice()->getActiveInputChannels();
            return deviceInputChannels;
        }
        else if(type == OUTPUT)
        {
            deviceOutputChannels = sharedAudioDeviceManager->getCurrentAudioDevice()->getActiveOutputChannels();
            return deviceOutputChannels;
        }
    }
	return 0;
}