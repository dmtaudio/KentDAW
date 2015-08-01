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
    btn = new TextButton("Add track", "Add track");

    addAndMakeVisible(btn);
    btn->addListener(this);
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
    int i = 0;

    for (auto current = channelStrips.begin(), end = channelStrips.end(); current != end; ++current) {
        (*current)->setBounds(0, i++ * 300, 100, 300 * 0.6);
    }

    btn->setBounds(getWidth() / 2 - btn->getWidth() / 2, 0, 200, 60);
}

void ArrangeWindow::createGuiForTrack(AudioTrack * track)
{
    ChannelStripComponent *channelStrip = new ChannelStripComponent(track);

    channelStrips.push_back(channelStrip);
    addAndMakeVisible(channelStrip);
    resized();
}

void ArrangeWindow::buttonClicked(Button *button)
{
    if (button == btn) {
        AudioTrack *track = AudioTrackFactory::build();

        // Command stuff
        //audioEngine->getMixer()->addTrack(track);
        createGuiForTrack(track);
    }
}
