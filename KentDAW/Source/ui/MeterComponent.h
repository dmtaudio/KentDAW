/*
  ==============================================================================

    MeterComponent.h
    Created: 29 Jun 2015 2:20:42pm
    Author:  dtl

  ==============================================================================
*/

#ifndef METERCOMPONENT_H_INCLUDED
#define METERCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "../core/AudioMixer.h"

//==============================================================================
/*
*/
class MeterComponent    : public Component
{
public:
    MeterComponent();
    ~MeterComponent();
    
    struct Type
    {
        bool horizontal;
        bool vertical;
    };
    

    void paint (Graphics&);
    void resized();

    void setMeterLevel(AudioMixer::Level newLevel);
    
    void setHorizontalType(bool isHorizontal);
    void setVerticalType(bool isVertical);
    
private:
    Rectangle<int> rect;
    AudioMixer::Level mLevel;
    Type meterType;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterComponent)
};


#endif  // METERCOMPONENT_H_INCLUDED
