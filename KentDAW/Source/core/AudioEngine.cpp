/*
 ==============================================================================
 
 AudioEngine.cpp
 Created: 31 Jul 2015 2:51:40pm
 Author:  dtl
 
 ==============================================================================
 */

#include "AudioEngine.h"

static AudioDeviceManager* sharedAudioDeviceManager;

AudioEngine::AudioEngine()
: graphPlayer(),
initialised(false)
{
	
	bool showMidiInputOptions = false;
	bool showMidiOutputSelector = false;
	bool showChanelsAsStereoPairs = true;
	bool hideAdvancedOptions = false;
	AudioDeviceSelectorComponent settings(getSharedAudioDeviceManager(), 0, 0, 1, 2,
		showMidiInputOptions,
		showMidiOutputSelector,
		showChanelsAsStereoPairs,
		hideAdvancedOptions);
	settings.setSize(500, 400);
	DialogWindow::showModalDialog(String("Audio Settings"),
		&settings,
		TopLevelWindow::getTopLevelWindow(0),
		Colours::white,
		true);
	
    deviceSampleRate = sharedAudioDeviceManager->getCurrentAudioDevice()->getCurrentSampleRate();
    deviceBitDepth = sharedAudioDeviceManager->getCurrentAudioDevice()->getCurrentBitDepth();
    deviceBufferSize = sharedAudioDeviceManager->getCurrentAudioDevice()->getCurrentBufferSizeSamples();
    
	//Create a mixer, set up the player and callback.
	mixer = new AudioMixer();

	if (!initialised) {
		graphPlayer.setProcessor(mixer->getAudioProcessorGraph());
		setDefaultDeviceCallback();
		mixer->resetGraph(deviceSampleRate, deviceBufferSize);
		initialised = true;
	}
}

AudioEngine::~AudioEngine()
{
	if(initialised) {
		sharedAudioDeviceManager->removeAudioCallback(&graphPlayer);
		graphPlayer.setProcessor(nullptr);
		initialised = false;
	}
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

void AudioEngine::setDefaultDeviceCallback()
{
    sharedAudioDeviceManager->addAudioCallback(&graphPlayer);
    sharedAudioDeviceManager->addMidiInputCallback(String::empty, &graphPlayer);
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

void AudioEngine::setCurrentAudioDevice(const String &deviceName)
{
    StringArray availableDeviceNames = getAvailableDeviceNames();
    
    String deviceString;
    
    if(availableDeviceNames.contains(deviceName))
    {
        sharedAudioDeviceManager->setCurrentAudioDeviceType(deviceName, true);
    }
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

void AudioEngine::setSampleRate(const double& sampleRate)
{
    Array<double> availableSampleRates = getAvailableSampleRates();
    if(availableSampleRates.contains(sampleRate))
    {
        AudioDeviceManager::AudioDeviceSetup setup;
        sharedAudioDeviceManager->getAudioDeviceSetup(setup);
        setup.sampleRate = sampleRate;
        sharedAudioDeviceManager->setAudioDeviceSetup(setup, true);
    }
}

double AudioEngine::getSampleRate()
{
    deviceSampleRate = sharedAudioDeviceManager->getCurrentAudioDevice()->getCurrentSampleRate();
    return deviceSampleRate;
}

int AudioEngine::getBitDepth()
{
    deviceBitDepth = sharedAudioDeviceManager->getCurrentAudioDevice()->getCurrentBitDepth();
    return deviceBitDepth;
}

BigInteger AudioEngine::getDeviceChannels(ChannelType type)
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
    else
    {
        // -1 signifies no channels
        return -1;
    }
}

AudioMixer* AudioEngine::getMixer()
{
    return mixer;
}
