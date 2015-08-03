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

void TrackComponent::createRegionGUI(AudioRegion* region)
{
	RegionComponent *regionGUI = new RegionComponent(*region);
	regionComponents.push_back(regionGUI);
	addAndMakeVisible(regionGUI);
	resized();
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
	g.fillAll(Colours::black);

	g.setColour(Colours::grey);
	g.drawRect(0, 0, getParentWidth(), getParentHeight());
}

void TrackComponent::resized()
{
	/*
	int i = 0;

	for (auto current = regionComponents.begin(), end = regionComponents.end(); current != end; ++current) {
		(*current)->setBounds(0, i++ * 100, getParentWidth(), 100);
	}
	*/
}
