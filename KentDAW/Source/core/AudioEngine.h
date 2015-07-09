/*
 * File:   AudioEngine.h
 * Author: Dan
 *
 * Created on 02 June 2015, 16:34
 */

#ifndef AUDIOENGINE_H
#define	AUDIOENGINE_H

#include "../JuceLibraryCode/JuceHeader.h"


class AudioCallBack : public AudioIODeviceCallback,
                      public MidiInputCallback
{
public:
    AudioCallBack();
    
    virtual ~AudioCallBack();
    
    void setAudioSourcePlayer(AudioSource* source);
    void setProcessorPlayer(AudioProcessor* processor);
    void reset();
    void prepareToPlay();
    
    void audioDeviceIOCallback (const float** inputChannelData,
                                int totalNumInputChannels,
                                float** outputChannelData,
                                int totalNumOutputChannels,
                                int numSamples);
    void audioDeviceAboutToStart (AudioIODevice* device);
    void audioDeviceStopped();
    
    void prepareToPlay(double sampleRate, int blockSize);
    
private:
    CriticalSection lock;
    ScopedPointer<AudioSource> source;
    ScopedPointer<AudioSourcePlayer> sourcePlayer;
    ScopedPointer<AudioProcessor> processor;
    ScopedPointer<AudioProcessorPlayer> processorPlayer;
    HeapBlock<float*> channels;
    double sampleRate;
    int bufferSize;
    AudioSampleBuffer tempBuffer;
    float gain, previousGain;
    bool sourceSet, processorSet, isPrepared;
    BigInteger numChannelsIn, numChannelsOut;
    
    MidiBuffer incomingMidi;
    MidiMessageCollector messageCollector;
};

class AudioEngine {
public:
    
    static AudioDeviceManager& getSharedAudioDeviceManager();
    
    AudioEngine();
    AudioEngine(const size_t numberOfChannels);
    
    virtual ~AudioEngine();
    
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
    
    // This could be in the transport class, however as this controls the overall playback I think it's actually best here
    // Position controls
    int getCurrentPosition();
    void setPosition(int positionInSamples);
    
    // Transport controls
    void start();
    void stop();
    
    // CPU usage data
    double getProcessorUsage();
    
    enum ChannelType
    {
        INPUT = 1,
        OUTPUT = 0
    };
    
    double getDeviceSampleRate();
    BigInteger getDeviceChannels(ChannelType type);
    int getBitDepth();

protected:
    void setCallbackSampleRate(double sampleRate);
    
private:
    
    AudioCallBack* audioCallback;
    //AudioFormatManager& formatManager;
    double deviceSampleRate;
    BigInteger deviceInputChannels;
    BigInteger deviceOutputChannels;
    int deviceBitDepth;
};

#endif	/* AUDIOENGINE_H */

