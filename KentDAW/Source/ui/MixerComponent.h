/*
  ==============================================================================

    MixerComponent.h
    Created: 21 Jul 2015 11:44:18am
    Author:  dtl

  ==============================================================================
*/

#ifndef MIXERCOMPONENT_H_INCLUDED
#define MIXERCOMPONENT_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class MixerComponent    : public Component
{
public:
    MixerComponent();
    ~MixerComponent();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MixerComponent)
};


#endif  // MIXERCOMPONENT_H_INCLUDED
