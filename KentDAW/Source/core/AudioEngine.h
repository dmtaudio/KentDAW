/*
 * File:   AudioEngine.h
 * Author: Dan
 *
 * Created on 02 June 2015, 16:34
 */

#ifndef AUDIOENGINE_H
#define	AUDIOENGINE_H

#include "../JuceLibraryCode/JuceHeader.h"

class AudioEngine : public MidiInputCallback{
public:
    
    AudioEngine();
    AudioEngine(const size_t numberOfChannels);
    virtual ~AudioEngine();
    
    void handleIncomingMidiMessage(MidiInput*, const MidiMessage&) override;
    void resetMidiMessages();
    MidiMessageCollector& getMidiMessageCollector() noexcept {return messageCollector;}
    
    static AudioDeviceManager& getSharedAudioDeviceManager();
    
    // Device information
    StringArray getAvailableDeviceNames();
    String setAudioDevice(const String& deviceName);
    String getCurrentDeviceName();
    StringArray getInputChannelNames();
    StringArray getOutputChannelNames();
    Array<double> getAvailableSampleRates();
    
    void setSampleRate(const double& sampleRate);
    double getSampleRate();
    
    // Global audio manipulation
    bool setMasterMute(bool enable);
    void setMasterGain(const float newGain);
    
    // Measurement for VU and other meters
    bool enableMeasurement(int channel, bool enable);
    bool resetMeasurementPeakValue(int channel);
    float getMeasuredDecayValue(int channel);
    float getMeasuredPeakValue(int channel);
    
    // File prelisten controls
    bool startPrelisten(const String &absFilenamePath, const int &startPos, const int &endPos);
    void stopPrelisten();
    
    // Transport controls
    void start();
    void stop();
    int getCurrentPosition();
    void setPosition(int positionInSamples);
    
    // CPU usage data
    double getProcessorUsage();
    
    enum ChannelType
    {
        INPUT = 1,
        OUTPUT = 0
    };
    
    BigInteger getDeviceChannels(ChannelType type);
    int getBitDepth();
    

private:
    CriticalSection lock;
    ScopedPointer<AudioSourcePlayer> sourcePlayer;
    AudioTransportSource transportSource;
    unsigned int regionIndex;
    MidiBuffer incomingMidi;
    MidiMessageCollector messageCollector;
    
    double masterGain;
    double deviceSampleRate;
    int deviceBitDepth;
    BigInteger deviceInputChannels, deviceOutputChannels;
    
    
    
    
};

#endif	/* AUDIOENGINE_H */

