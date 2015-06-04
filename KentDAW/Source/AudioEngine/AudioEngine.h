/* 
 * File:   AudioEngine.h
 * Author: Dan
 *
 * Created on 02 June 2015, 16:34
 */

#ifndef AUDIOENGINE_H
#define	AUDIOENGINE_H

#include "../JuceLibraryCode/JuceHeader.h"

#define TRANSPORT_BUFFER 2048

class AudioEngine {
public:
    AudioEngine();
    
    virtual ~AudioEngine();
    
    // Audio device control
    StringArray getAvailableAudioDevices();
    String setAudioDevice();
    const String &getCurrentAudioDeviceName();
    
    // Get channel names
    StringArray getOutputChannelNames();
    
    // Sample rate control
    std::vector<double> getAvailableSampleRates();
    String setSampleRate(const double& sr);
    double getSampleRate();
    
    // Buffer control
    std::vector<int> getAvailableBufferSizes();
    int defaultBufferSize();
    int currentBufferSize();   
    String setBufferSize(const int &bufferSizeSamps);
    
    // Track manipulation
    bool setGain(int channel, double gain);
    bool setSolo(int channel, bool enable);
    bool setMute(int channel, bool enable);
    
    // Measurement for VU and other meters
    bool enableMeasurement(int channel, bool enable);
    bool resetMeasurementPeakValue(int channel);
    float getMeasuredDecayValue(int channel);
    float getMeasuredPeakValue(int channel);
    
    // Modify routing
    void setNewOutputRouting(int channel, int outputChannel);
    void setPreviewOutputs(BigInteger prelistenOutputs);
    void setPreviewGain(double preListenGain);
    void enableNewRouting();
    
    // File prelisten controls
    bool startPrelisten(const String &absFilenamePath, const int &startPos, const int &endPos);
    void stopPrelisten();
    
    // Position controls
    int getCurrentPosition();
    void setPosition(int positionInSamples);
    
    // Transport controls
    void start();
    void stop();
    
    // CPU usage data
    double getProcessorUsage();
    
    // Audio region controls
    bool addAudioRegion(const int regionID, const int startPos, const int duration, const int fileOffset, String absFilenamePath);
    bool modifyAudioRegion(const int regionID, const int newStartPos, const int newDuration, const int newOffset);
    bool removeRegion(const int regionID);
    void removeAllRegions();
    
    // Modify master gain
    void setMasterGain(const float newGain);
    
private:
// member variables go here
};

#endif	/* AUDIOENGINE_H */

