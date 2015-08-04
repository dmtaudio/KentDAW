/*
  ==============================================================================

    EQProcessor.cpp
    Created: 3 Aug 2015 1:23:32pm
    Author:  dtl

  ==============================================================================
*/

#include "EQProcessor.h"

EQProcessor::EQProcessor(FilterType type, float freq, float qFactor)
: _type(type), _freq(freq), _qFactor(qFactor), _sampleRate(44100),
  _dB(0.0f), _order(0)
{}

EQProcessor::~EQProcessor()
{
    
}

void EQProcessor::prepareToPlay(double sampleRate_, int)
{
    _sampleRate = (int) sampleRate_;
    
    for(auto c : _cs)
        c = 0.0f;
    for(auto c : _old_cs)
        c = 0.0f;
    for(auto d : _ds)
        d = 0.0f;
    for(auto d : _old_ds)
        d = 0.0f;
    
    resetCoefficents();

    
}

void EQProcessor::calculateCoefficients()
{
    
}

void EQProcessor::resetCoefficents()
{
    _x.c1 = 0.0f;
    _x.c2 = 0.0f;
    _y.c1 = 0.0f;
    _y.c2 = 0.0f;
    _old_x = _x;
    _old_y = _y;
}

void processBlockBypassed (AudioSampleBuffer &, MidiBuffer &)
{
    
}

void EQProcessor::setFreqAndQFactor(float freq, float qFactor)
{
    setFrequency(freq);
    setQFactor(qFactor);
}

void EQProcessor::setFrequency(float freq)
{
    _freq = freq;
}

void EQProcessor::setQFactor(float qFactor)
{
    _qFactor = qFactor;
}