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
    const String getInputChannelName() const;
    const String getOutputChannelName() const;
    
    bool isInputChannelStereoPair(int index) const { return false; }
    bool isOutputChannelStereoPair(int index) const { return false; }
    
    bool acceptsMidi() const = 0;
    bool producesMidi() const = 0;
    
private:
    AudioSource* source;
    bool deleteSource;
};





#endif  // AUDIOSOURCEPROCESSOR_H_INCLUDED
