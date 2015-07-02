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
    
    enum CallbackType
    {
        Source,
        Processor
    };
    
    void setPlayableSource(AudioSource* source);
    void setPlayableProcessor(AudioProcessor* processor);
    
    void audioDeviceIOCallback (const float** inputChannelData,
                                int totalNumInputChannels,
                                float** outputChannelData,
                                int totalNumOutputChannels,
                                int numSamples);
    void audioDeviceAboutToStart (AudioIODevice* device);
    void audioDeviceStopped();
    
    void prepareToPlay(double sampleRate, int blockSize);
    
private:
    CallbackType callbackType;
    CriticalSection lock;
    AudioProcessor* processor;
    AudioSource* source;
    double sampleRate;
    int bufferSize;
    AudioSampleBuffer tempBuffer;
    // Audio source stuff
    float *sourceChannels[128], *sourceOutputChannels[128];
    const float* sourceInputChannels[128];
    float gain, previousGain;
    bool isPrepared;
    // Audio processor stuff
    int processorInputChannels, processorOutputChannels;
    HeapBlock<float*> processorChannels;
    MidiBuffer incomingMidi;
    
};

class AudioEngine {
public:
    AudioEngine();
    
    virtual ~AudioEngine();
    
    static AudioDeviceManager& getSharedAudioDeviceManager();
    
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

