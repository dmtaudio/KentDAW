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
ArrangeWindow::ArrangeWindow(AudioEngine *audioEngine) : _audioEngine(audioEngine),
	trackComponents()
{
    formatManager.registerBasicFormats();
    reader = formatManager.createReaderFor(File("~/Documents/03_Borders.wav"));
    source = new AudioFormatReaderSource(reader, true);
    transport.setSource(source);
    _visibleRange = Range<double>(0.0, transport.getTotalLength());
    cursor = new TimelineCursor(transport, _visibleRange);
    addAndMakeVisible(cursor);
    cursor->setCursorVisability(true);
	//setOpaque(true);
}

ArrangeWindow::~ArrangeWindow()
{
}

void ArrangeWindow::setVisibleRange(Range<double> range)
{
    if(cursor != nullptr)
    {
        cursor->setVisibleRange(range);
        _visibleRange = range;
    }
}


void ArrangeWindow::paint (Graphics& g)
{
    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    //g.setColour (Colours::lightblue);
    //g.setFont (14.0f);
    //g.drawText ("ArrangeWindow", getLocalBounds(),
    //           Justification::centred, true);   // draw some placeholder text
}

void ArrangeWindow::resized()
{
	int i = 0;

	for (auto current = trackComponents.begin(), end = trackComponents.end(); current != end; ++current) {
		(*current)->setBounds(0, i++ * 100, getParentWidth(), 100);
	}
    cursor->setSize(getParentWidth(), getParentHeight());
}

void ArrangeWindow::createGuiForTrack(AudioTrack* track, int trackNumber)
{	
	TrackComponent *trackGUI = new TrackComponent(track, trackNumber);
	trackComponents.push_back(trackGUI);
	addAndMakeVisible(trackGUI);
	resized();
	
}

void ArrangeWindow::addRegionToTrackGUI(AudioRegion* region, int trackNumber, AudioFormatManager& formatManager, File& audioFile)
{
	for (auto current = trackComponents.begin(), end = trackComponents.end(); current != end; ++current) {
		if ((*current)->getTrackNumber() == trackNumber)
		{
			(*current)->createRegionGUI(region, formatManager, audioFile);
		}
	}
}