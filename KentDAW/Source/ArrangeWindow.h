/*
  ==============================================================================

    ArrangeWindow.h
    Created: 1 Jul 2015 2:44:20pm
    Author:  Matt

  ==============================================================================
*/

#ifndef ARRANGEWINDOW_H_INCLUDED
#define ARRANGEWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class ArrangeWindow    : public Component
{
public:
    ArrangeWindow();
    ~ArrangeWindow();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArrangeWindow)
};


#endif  // ARRANGEWINDOW_H_INCLUDED
