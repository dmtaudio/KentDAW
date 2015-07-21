/*
  ==============================================================================

    ArrangeWindow.cpp
    Created: 1 Jul 2015 2:44:20pm
    Author:  Matt

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ArrangeWindow.h"

//==============================================================================
ArrangeWindow::ArrangeWindow()
{
    addAndMakeVisible(channelStrip = new ChannelStripComponent());
}

ArrangeWindow::~ArrangeWindow()
{
}

void ArrangeWindow::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

	
    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    g.drawText ("ArrangeWindow", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void ArrangeWindow::resized()
{
    channelStrip->setBounds(0, 0, 200, 300);

}
