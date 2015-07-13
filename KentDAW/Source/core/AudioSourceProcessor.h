/*
  ==============================================================================

    AudioSourceProcessor.h
    Created: 13 Jul 2015 11:03:02am
    Author:  dtl

  ==============================================================================
*/

#ifndef AUDIOSOURCEPROCESSOR_H_INCLUDED
#define AUDIOSOURCEPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class AudioSourceProcessor : public AudioProcessor
{
public:
    AudioSourceProcessor(AudioSource* const input, bool deleteSource);
    ~AudioSourceProcessor();
    
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
    void releaseResources();
    
    const String getName() const;
    const String getInputChannelName(const int channelIndex) const;
    const String getOutputChannelName(const int channelIndex) const;
    
    bool isInputChannelStereoPair(int index) const { return false; }
    bool isOutputChannelStereoPair(int index) const { return false; }
    
    bool acceptsMidi() const { return false; }
    bool producesMidi() const { return false; }
    
    int getNumParameters() { return 0; }
    const String getParameterName(int paramaterIndex) { return String::empty; }
    float getParameter(int parameterIndex) { return 0.0f; }
    const String getParameterText(int parameterIndex) { return String::empty; }
    void setParameter(int parameterIndex, float newValue) {};
    
    int getNumPrograms() { return 0; }
    int getCurrentProgram() { return 0; }
    void setCurrentProgram(int index) {};
    const String getProgramName(int index) { return String::empty; }
    void changeProgramName(int index,const String& name) {};
    
    bool silenceInProducesOutput() const { return false; }
    double getTailLengthSeconds() const { return 0.0f; }
    bool hasEditor() const { return false; }
    
    void getStateInformation(MemoryBlock& destData) {};
    void setStateInformation(const void* data, int sizeBytes) {};
    
    AudioProcessorEditor* createEditor() { return 0; }
    
private:
    AudioSource* source;
    bool deleteSource;
};





#endif  // AUDIOSOURCEPROCESSOR_H_INCLUDED
