/*
  ==============================================================================

    ArrangeWindow.cpp
    Created: 1 Jul 2015 2:44:20pm
    Author:  Matt

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ArrangeWindow.h"
#include "../core/AudioTrackFactory.h"

//==============================================================================
ArrangeWindow::ArrangeWindow(AudioEngine *audioEngine) : audioEngine(audioEngine)
{

}

ArrangeWindow::~ArrangeWindow()
{
}

void ArrangeWindow::paint (Graphics& g)
{
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

}

void ArrangeWindow::createGuiForTrack(AudioTrack * track)
{
	
	//ChannelStripComponent *channelStrip = new ChannelStripComponent(track);
	//channelStrips.push_back(channelStrip);
    //addAndMakeVisible(channelStrip);
    //resized();

}