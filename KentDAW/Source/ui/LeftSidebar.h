/*
  ==============================================================================

    LeftSidebar.h
    Created: 2 Jul 2015 1:18:32pm
    Author:  Matt

  ==============================================================================
*/

#ifndef LEFTSIDEBAR_H_INCLUDED
#define LEFTSIDEBAR_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class LeftSidebar    : public Component
{
public:
    LeftSidebar();
    ~LeftSidebar();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeftSidebar)
};


#endif  // LEFTSIDEBAR_H_INCLUDED
