/*
  ==============================================================================

    MainComponent.h
    Created: 12 Mar 2015 7:55:47pm
    Author:  Dan

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class MainComponent    : public Component
{
public:
    MainComponent();
    ~MainComponent();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
