/*
  ==============================================================================

    MidiManager.cpp
    Created: 3 Aug 2015 10:46:58am
    Author:  dtl

  ==============================================================================
*/

#include "MidiManager.h"

MidiManager::MidiManager()
: noteNumber(0), velocity(0)
{
    controlChangeOff();
    input = MidiInput::openDevice(MidiInput::getDefaultDeviceIndex(), this);
    if(input)
        input->start();
}

MidiManager::~MidiManager()
{
    input->stop();
    if(input)
        delete input;
}

void MidiManager::handleIncomingMidiMessage(MidiInput*, const MidiMessage &message)
{
    if(message.isNoteOn())
    {
        noteOn = true;
        noteNumber = message.getNoteNumber();
        noteHz = message.getMidiNoteInHertz(noteNumber);
        velocity = message.getVelocity();
    }
    
    if(message.isController())
    {
        controlChange = true;
        controlNumber = message.getControllerNumber();
        controlValue = message.getControllerValue();
    }
}

int MidiManager::getCurrentNoteNumber()
{
    return noteNumber;
}

float MidiManager::getCurrentNoteHz()
{
    return noteHz;
}

int MidiManager::getCurrentControlNumber()
{
    return controlNumber;
}

int MidiManager::getCurrentControlValue()
{
    return controlValue;
}

bool MidiManager::isMidiNoteOn()
{
    return noteOn;
}

void MidiManager::midiNoteOff()
{
    noteOn = false;
}

bool MidiManager::getControlChange()
{
    return controlChange;
}

void MidiManager::controlChangeOff()
{
    controlChange = false;
}

int MidiManager::getCurrentMidiVelocity()
{
    return velocity;
}