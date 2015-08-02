/*
 ==============================================================================
 
 AudioEngine.h
 Created: 31 Jul 2015 2:51:40pm
 Author:  dtl
 
 ==============================================================================
 */

#ifndef AUDIOENGINE_H_INCLUDED
#define AUDIOENGINE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioMixer.h"

class AudioEngine
{
public:
    AudioEngine();
    ~AudioEngine();
    
    static AudioDeviceManager& getSharedAudioDeviceManager();
    
    // Set the device callback either to the default
    void setDefaultDeviceCallback();
    void setDeviceCallback(AudioIODeviceCallback* callback);
    
    // Deivce Information
    StringArray getAvailableDeviceNames();
    void setCurrentAudioDevice(const String& deviceName);
    String getCurrentDeviceName();
    StringArray getInputChannelNames();
    StringArray getOutputChannelNames();
    Array<double> getAvailableSampleRates();
    
    // Sample rate accessors
    void setSampleRate(const double& sampleRate);
    double getSampleRate();
    
    // Bit depth accessors
    int getBitDepth();
    
    // Channel Info
    enum ChannelType { INPUT, OUTPUT };
    BigInteger getDeviceChannels(ChannelType type);
    
    double getProcessorUsage();
    AudioMixer* getMixer();
    
private:
    // Callback related stuff
    CriticalSection lock;
    AudioProcessorPlayer graphPlayer;
    AudioMixer* mixer;
    
    // Midi
    MidiBuffer incomingMidi;
    MidiMessageCollector messageCollector;
    
    // Device Info
    double deviceSampleRate;
    int deviceBitDepth;
    int deviceBufferSize;
    BigInteger deviceInputChannels, deviceOutputChannels;

	// Graph
	bool initialised;
};

#endif  // AUDIOENGINE_H_INCLUDED

