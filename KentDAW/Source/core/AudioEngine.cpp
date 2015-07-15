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

static AudioDeviceManager* sharedAudioDeviceManager;

AudioEngine::AudioEngine()
: graphPlayer()
{
    getSharedAudioDeviceManager();
    deviceSampleRate = getSharedAudioDeviceManager().getCurrentAudioDevice()->getCurrentSampleRate();
    deviceBitDepth = getSharedAudioDeviceManager().getCurrentAudioDevice()->getCurrentBitDepth();
    deviceBufferSize = getSharedAudioDeviceManager().getCurrentAudioDevice()->getCurrentBufferSizeSamples();
    setDeviceCallback();
    mixer = new AudioMixer();
	graphPlayer->setProcessor(mixer->getAudioProcessorGraph());
	mixer->resetGraph(deviceSampleRate, deviceBufferSize);
   
}

AudioEngine::~AudioEngine()
{
}

void AudioEngine::handleIncomingMidiMessage(MidiInput* input, const MidiMessage& message)
{
    messageCollector.addMessageToQueue(message);
}

void AudioEngine::resetMidiMessages()
{
    messageCollector.reset(getSampleRate());
}

AudioDeviceManager& AudioEngine::getSharedAudioDeviceManager()
{
    if(sharedAudioDeviceManager == nullptr)
    {
        int numInputChannels = 2;
        int numOutputChannels = 2;
        sharedAudioDeviceManager = new AudioDeviceManager();
        sharedAudioDeviceManager->initialise(numInputChannels, numOutputChannels, 0, true);
    }
    return *sharedAudioDeviceManager;
}

void AudioEngine::setDeviceCallback()
{
    sharedAudioDeviceManager->addAudioCallback(graphPlayer);
}

void AudioEngine::setDeviceCallback(AudioIODeviceCallback* callback)
{
    sharedAudioDeviceManager->addAudioCallback(callback);
}

StringArray AudioEngine::getAvailableDeviceNames()
{
    AudioIODeviceType* audioIODeviceType = 0;
    audioIODeviceType->scanForDevices();
    StringArray deviceNames;
    deviceNames = audioIODeviceType->getDeviceNames(false);
    
    return deviceNames;
}

String AudioEngine::setAudioDevice(const String &deviceName)
{
    StringArray availableDeviceNames = getAvailableDeviceNames();
    
    String deviceString;
    
    if(availableDeviceNames.contains(deviceName))
    {
        // do some stuff
    }
    return deviceString;
}

String AudioEngine::getCurrentDeviceName()
{
    AudioIODevice* currentDevice = sharedAudioDeviceManager->getCurrentAudioDevice();
    return currentDevice->getName();
}

StringArray AudioEngine::getInputChannelNames()
{
    AudioIODevice* currentDevice = sharedAudioDeviceManager->getCurrentAudioDevice();
    return currentDevice->getInputChannelNames();
}

StringArray AudioEngine::getOutputChannelNames()
{
    AudioIODevice* currentDevice = sharedAudioDeviceManager->getCurrentAudioDevice();
    return currentDevice->getOutputChannelNames();
}

Array<double> AudioEngine::getAvailableSampleRates()
{
    Array<double> availableSampleRates;
    AudioIODevice* currentDevice = sharedAudioDeviceManager->getCurrentAudioDevice();
    availableSampleRates = currentDevice->getAvailableSampleRates();
    return availableSampleRates;
}

void AudioEngine::setSampleRate(const double &sampleRate)
{
    Array<double> availableSampleRates = getAvailableSampleRates();
    
    if(availableSampleRates.contains(sampleRate))
    {
        bool isPlaying = transportSource->isPlaying();
        int currentPosition;
        if(isPlaying)
        {
            currentPosition = getCurrentPosition();
            stop();
        }
    }
}

double AudioEngine::getSampleRate()
{
    if(sharedAudioDeviceManager != nullptr)
    {
        deviceSampleRate = sharedAudioDeviceManager->getCurrentAudioDevice()->getCurrentSampleRate();
        return deviceSampleRate;
    }
    return 0.0f;
}

bool AudioEngine::setMasterMute(bool enable)
{
    if(enable)
    {
        return enable;
    }
    else
    {
        transportSource->setGain(masterGain);
        return false;
    }
}

void AudioEngine::setMasterGain(const float newGain)
{
    masterGain = newGain;
}

bool AudioEngine::enableMeasurement(int channel, bool enable)
{
    return false;
}

bool AudioEngine::resetMeasurementPeakValue(int channel)
{
    return false;
}

float AudioEngine::getMeasuredDecayValue(int channel)
{
    return 0.0f;
}

float AudioEngine::getMeasuredPeakValue(int channel)
{
    return 0.0f;
}

bool AudioEngine::startPrelisten(const String &absFilenamePath, const int &startPos, const int &endPos)
{
    return false;
}

void AudioEngine::stopPrelisten()
{
}

void AudioEngine::start()
{
}

void AudioEngine::stop()
{
}

int AudioEngine::getCurrentPosition()
{
    AudioIODevice* audioDevice = sharedAudioDeviceManager->getCurrentAudioDevice();
    double deviceSampleRate = audioDevice->getCurrentSampleRate();
    //return (int) transportSource->getCurrentPosition() * deviceSampleRate;
    return 0;
}

void AudioEngine::setPosition(int positionInSamples)
{
    double deviceSampleRate = getSampleRate();
    double positionInSeconds = (double)positionInSamples / deviceSampleRate;
}

double AudioEngine::getProcessorUsage()
{
    return sharedAudioDeviceManager->getCpuUsage();
}

int AudioEngine::getBitDepth()
{
    if(sharedAudioDeviceManager != nullptr)
    {
        deviceBitDepth = sharedAudioDeviceManager->getCurrentAudioDevice()->getCurrentBitDepth();
        return deviceBitDepth;
    }
    else
        return 0;
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
