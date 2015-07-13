/*
  ==============================================================================

    TimelineComponent.h
    Created: 13 Jul 2015 1:48:47am
    Author:  dtl

  ==============================================================================
*/

#ifndef TIMELINECOMPONENT_H_INCLUDED
#define TIMELINECOMPONENT_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class TimelineComponent    : public Component
{
public:
    TimelineComponent();
    ~TimelineComponent();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimelineComponent)
};


#endif  // TIMELINECOMPONENT_H_INCLUDED
