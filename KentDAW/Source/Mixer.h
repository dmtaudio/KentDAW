
#ifndef __JUCE_HEADER_EB46FF61849DA256__
#define __JUCE_HEADER_EB46FF61849DA256__

#include "JuceHeader.h"

#define PI 3.14159265359
#define BUFFER_LENGTH 8192
#define SR 44100

class Mixer  : public Component,
public SliderListener,
public ComboBoxListener
{
public:
    Mixer ();
    ~Mixer();

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void sineWave();
    
    
    
private:
    ScopedPointer<Slider> mixerSlider;
    ScopedPointer<Label> trackLabel;
    ScopedPointer<ComboBox> inputCombo;
    
    
    double buffer[BUFFER_LENGTH];
    int16 x;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mixer)
};

#endif   // __JUCE_HEADER_EB46FF61849DA256__

