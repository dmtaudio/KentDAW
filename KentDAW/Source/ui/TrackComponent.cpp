/*
  ==============================================================================

    TrackComponent.cpp
    Created: 2 Aug 2015 8:18:56pm
    Author:  Matt

  ==============================================================================
*/

#include "TrackComponent.h"

TrackComponent::TrackComponent(AudioTrack *track, int trackNumber)	: _track(track),
	regionComponents()
{
	_trackNumber = trackNumber;
}

TrackComponent::~TrackComponent()
{
}

void TrackComponent::createRegionGUI(AudioRegion* region, AudioFormatManager& formatManager, File& audioFile)
{
	RegionComponent *regionGUI = new RegionComponent(region, formatManager, audioFile);
	regionComponents.push_back(regionGUI);
	addAndMakeVisible(regionGUI);
	resized();

	setOpaque(true);
}

void TrackComponent::updateTrackRegions()
{
}

int TrackComponent::getTrackNumber()
{
	return _trackNumber;
}

void TrackComponent::setTrackNumber(int trackNumber)
{
	_trackNumber = trackNumber;
}

void TrackComponent::paint(Graphics & g)
{
	g.setColour(Colours::grey);
    g.fillAll();
    //g.drawRect(0, 0, getParentWidth(), getParentHeight());
}

void TrackComponent::resized()
{
	for (auto current = regionComponents.begin(), end = regionComponents.end(); current != end; ++current) {
		Rectangle<int> r(getLocalBounds().reduced(4));
		r.removeFromBottom(6);
		(*current)->setBounds(r.removeFromBottom(140));
	}
}
