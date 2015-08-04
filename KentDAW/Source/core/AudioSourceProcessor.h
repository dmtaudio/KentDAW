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

	void setTrackNumber(int newTrackNumber);
    
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
    void releaseResources();
    
    const String getName() const;
    const String getInputChannelName(int channelIndex) const;
    const String getOutputChannelName(int channelIndex) const;
    
    bool isInputChannelStereoPair(int) const { return false; }
    bool isOutputChannelStereoPair(int) const { return false; }
    
    bool acceptsMidi() const { return false; }
    bool producesMidi() const { return false; }
    
    int getNumParameters() { return 0; }
    const String getParameterName(int) { return String::empty; }
    float getParameter(int) { return 0.0f; }
    const String getParameterText(int) { return String::empty; }
    void setParameter(int, float) {};
    
    int getNumPrograms() { return 0; }
    int getCurrentProgram() { return 0; }
    void setCurrentProgram(int) {};
    const String getProgramName(int) { return String::empty; }
    void changeProgramName(int,const String&) {};
    
    bool silenceInProducesSilenceOut() const { return false; }
    double getTailLengthSeconds() const { return 0.0f; }
    bool hasEditor() const { return false; }
    
    void getStateInformation(MemoryBlock&) {};
    void setStateInformation(const void*, int) {};
    
    AudioProcessorEditor* createEditor() { return 0; }
    
private:
    AudioSource* source;
    bool deleteSource;
	int trackNumber;
};





#endif  // AUDIOSOURCEPROCESSOR_H_INCLUDED
