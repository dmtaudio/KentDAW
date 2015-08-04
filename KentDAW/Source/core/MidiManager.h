/*
  ==============================================================================

    MidiManager.h
    Created: 3 Aug 2015 10:46:58am
    Author:  dtl

  ==============================================================================
*/

#ifndef MIDIMANAGER_H_INCLUDED
#define MIDIMANAGER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>

class MidiManager : public MidiInputCallback
{
public:
    MidiManager();
    ~MidiManager();
    
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message);
    
    int getCurrentNoteNumber();
    double getCurrentNoteHz();
    int getCurrentControlNumber();
    int getCurrentControlValue();
    bool isMidiNoteOn();
    void midiNoteOff();
    bool getControlChange();
    void controlChangeOff();
    int getCurrentMidiVelocity();
    
private:
    MidiInput* input;
    
    int noteNumber;
    double noteHz;
    bool noteOn;
    int controlNumber;
    int controlValue;
    bool controlChange;
    int velocity;
    
    MidiManager (const MidiManager&);
    const MidiMessageCollector& operator= (const MidiManager&);
};




#endif  // MIDIMANAGER_H_INCLUDED
