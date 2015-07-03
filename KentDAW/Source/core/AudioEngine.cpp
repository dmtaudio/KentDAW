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
: processor(nullptr),
  source(nullptr),
  sampleRate(0),
  bufferSize(0)
{
}

AudioCallBack::~AudioCallBack()
{
    setPlayableSource(nullptr);
    setPlayableProcessor(nullptr);
}

void AudioCallBack::setPlayableSource(AudioSource *newSource)
{
    callbackType = CallbackType::Source;
    if(source != newSource)
    {
        AudioSource* const previousSource = source;
        if(newSource != nullptr && bufferSize > 0 && sampleRate > 0)
        {
            newSource->prepareToPlay(bufferSize, sampleRate);
            {
                const ScopedLock sl(lock);
                source = newSource;
            }
        }
        if(previousSource != nullptr)
            previousSource->releaseResources();
    }
}

void AudioCallBack::setPlayableProcessor(AudioProcessor *newProcessor)
{
    callbackType = CallbackType::Processor;
    if(processor != newProcessor)
    {
        if(newProcessor != nullptr && bufferSize > 0 && sampleRate > 0)
        {
            newProcessor->setPlayConfigDetails(processorInputChannels, processorOutputChannels, sampleRate, bufferSize);
            newProcessor->prepareToPlay(sampleRate, bufferSize);
        }
        AudioProcessor* previousProcessor;
        {
            const ScopedLock sl(lock);
            previousProcessor = isPrepared ? processor : nullptr;
            processor = newProcessor;
            isPrepared = true;
        }
        
        if(previousProcessor != nullptr)
            previousProcessor->releaseResources();
    }
}

void AudioCallBack::audioDeviceIOCallback(const float** inputChannelData, int totalNumInputChannels, float** outputChannelData, int totalNumOutputChannels, int numSamples)
{
    jassert(sampleRate > 0 && bufferSize > 0);
    
    const ScopedLock sl(lock);
    switch(callbackType)
    {
        case Source:
            if(source != nullptr)
            {
                int numActiveChannels = 0, numInputs = 0, numOutputs = 0;
                // compact channels into an array of non-zero pointers
                for(int i = 0; i < totalNumInputChannels; ++i)
                {
                    if(inputChannelData[i] != nullptr)
                    {
                        do
                        {
                            sourceInputChannels[numInputs++] = inputChannelData[i];
                        }
                        while(numInputs >= numElementsInArray(sourceInputChannels));
                    }
                }
                
                for(int i = 0; i < totalNumOutputChannels; ++i)
                {
                    if(outputChannelData[i] != nullptr)
                    {
                        do
                        {
                            sourceOutputChannels[numOutputs++] = outputChannelData[i];
                        }
                        while(numOutputs >= numElementsInArray(sourceOutputChannels));
                    }
                }
                
                if(numInputs > numOutputs)
                {
                    tempBuffer.setSize(numInputs - numOutputs, numSamples, false, false, true);
                    
                    for(int i = 0; i < numOutputs; ++i)
                    {
                        sourceChannels[numActiveChannels] = sourceOutputChannels[i];
                        memcpy(sourceChannels[numActiveChannels], sourceInputChannels, sizeof(float) * (size_t)numSamples);
                        ++numActiveChannels;
                    }
                    
                    for(int i = numOutputs; i < numInputs; ++i)
                    {
                        sourceChannels[numActiveChannels] = tempBuffer.getWritePointer( i- numOutputs);
                        memcpy(sourceChannels[numActiveChannels], sourceInputChannels, sizeof(float) * (size_t)numSamples);
                        ++numActiveChannels;
                    }
                }
                else
                {
                    for(int i = 0; i < numOutputs; ++i)
                    {
                        sourceChannels[numActiveChannels] = sourceOutputChannels[i];
                        memcpy(sourceChannels[numActiveChannels], sourceInputChannels, sizeof(float) * (size_t)numSamples);
                        ++numActiveChannels;
                    }
                    
                    for(int i = numOutputs; i < numInputs; ++i)
                    {
                        sourceChannels[numActiveChannels] = sourceOutputChannels[i];
                        zeromem(sourceChannels, sizeof(float) * (size_t)numSamples);
                        ++numActiveChannels;
                    }
                }
                
                AudioSampleBuffer buffer(sourceChannels, numActiveChannels, numSamples);
                AudioSourceChannelInfo info(&buffer, 0, numSamples);
                source->getNextAudioBlock(info);
            }
            else
            {
                for (int i = 0; i < totalNumOutputChannels; ++i)
                    if (outputChannelData[i] != nullptr)
                        zeromem (outputChannelData[i], sizeof (float) * (size_t) numSamples);
            }
            break;
            
        case Processor:
            int totalNumChannels = 0;
            
            if(totalNumInputChannels > totalNumOutputChannels)
            {
                tempBuffer.setSize(totalNumInputChannels - totalNumOutputChannels, numSamples, false, false, true);
            
            
                for (int i = 0; i < totalNumOutputChannels; ++i)
                {
                    processorChannels[totalNumChannels] = outputChannelData[i];
                    memcpy (processorChannels[totalNumChannels], inputChannelData[i], sizeof (float) * (size_t) numSamples);
                    ++totalNumChannels;
                }
            
                for (int i = totalNumOutputChannels; i < totalNumInputChannels; ++i)
                {
                    processorChannels[totalNumChannels] = tempBuffer.getWritePointer (i - totalNumOutputChannels);
                    memcpy (processorChannels[totalNumChannels], inputChannelData[i], sizeof (float) * (size_t) numSamples);
                    ++totalNumChannels;
                }
            }
            else
            {
                for (int i = 0; i < totalNumInputChannels; ++i)
                {
                    processorChannels[totalNumChannels] = outputChannelData[i];
                    memcpy (processorChannels[totalNumChannels], inputChannelData[i], sizeof (float) * (size_t) numSamples);
                    ++totalNumChannels;
                }
        
                for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
                {
                    processorChannels[totalNumChannels] = outputChannelData[i];
                    zeromem (processorChannels[totalNumChannels], sizeof (float) * (size_t) numSamples);
                    ++totalNumChannels;
                }
            }
            AudioSampleBuffer buffer(processorChannels, totalNumChannels, numSamples);
            {
                const ScopedLock sl(lock);
                if(processor != nullptr)
                {
                    const ScopedLock cl(processor->getCallbackLock());
                    if(!processor->isSuspended())
                    {
                        processor->processBlock(buffer, incomingMidi);
                        return;
                    }
                }
            }
        
            for(int i = 0; i < totalNumOutputChannels; ++i)
                FloatVectorOperations::clear(outputChannelData[i], numSamples);
        break;
    }
}

void AudioCallBack::audioDeviceAboutToStart(AudioIODevice* device)
{
    prepareToPlay(device->getCurrentSampleRate(), device->getCurrentBufferSizeSamples());
    
}

void AudioCallBack::audioDeviceStopped()
{
    
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