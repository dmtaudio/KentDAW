/*
  ==============================================================================

    StatusBar.h
    Created: 2 Jul 2015 1:44:18pm
    Author:  Matt

  ==============================================================================
*/

#ifndef STATUSBAR_H_INCLUDED
#define STATUSBAR_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class StatusBar    : public Component
{
public:
    StatusBar();
    ~StatusBar();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StatusBar)
};


#endif  // STATUSBAR_H_INCLUDED
