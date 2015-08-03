/*
  ==============================================================================

    EQProcessor.h
    Created: 3 Aug 2015 1:23:32pm
    Author:  dtl

  ==============================================================================
*/

#ifndef EQPROCESSOR_H_INCLUDED
#define EQPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class EQProcessor : public AudioProcessor
{
public:
    
    enum FilterType
    {
        LowPass1Pole,
        LowPass2Pole,
        HighPass1Pole,
        HighPass2Pole,
        BandPass,
        LowShelf,
        HighShelf
    };
    
    EQProcessor(FilterType type, float freq, float qFactor);
    ~EQProcessor();
    
    const String getName () const = 0;
    virtual void prepareToPlay (double sampleRate, int estimatedSamplesPerBlock) = 0;
    virtual void releaseResources () = 0;
    virtual void processBlock (AudioSampleBuffer &buffer, MidiBuffer &midiMessages) = 0;
    virtual void processBlockBypassed (AudioSampleBuffer &buffer, MidiBuffer &midiMessages);
    
    void setFrequency(float freq);
    void setQFactor(float qFactor);
    void setFreqAndQFactor(float freq, float qFactor);
    void setFilterType(FilterType type);
    void setGain(float dB);
    
    void calculateCoefficients();
    void resetCoefficents();


private:
    
    struct C
    {
        float c1, c2;
    };
    
    FilterType _type;
    float _freq;
    float _qFactor;
    double _sampleRate;
    int _samplesPerBlock;
    double _dB;
    int _order;
    
    float _cs[3], _old_cs[3];
    float _ds[3], _old_ds[3];
    C _x, _y, _old_x, _old_y;
};


#endif  // EQPROCESSOR_H_INCLUDED
