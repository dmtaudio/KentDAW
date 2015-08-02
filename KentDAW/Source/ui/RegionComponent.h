/*
  ==============================================================================

    RegionComponent.h
    Created: 2 Aug 2015 11:34:48pm
    Author:  Matt

  ==============================================================================
*/

#ifndef REGIONCOMPONENT_H_INCLUDED
#define REGIONCOMPONENT_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class RegionComponent    : public Component
{
public:
    RegionComponent();
    ~RegionComponent();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RegionComponent)
};


#endif  // REGIONCOMPONENT_H_INCLUDED
