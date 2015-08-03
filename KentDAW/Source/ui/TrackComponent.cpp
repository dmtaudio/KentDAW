/*
  ==============================================================================

    TrackComponent.cpp
    Created: 2 Aug 2015 8:18:56pm
    Author:  Matt

  ==============================================================================
*/

#include "TrackComponent.h"

TrackComponent::TrackComponent(AudioTrack *track)	: track(track)
{
}

TrackComponent::~TrackComponent()
{
}

void TrackComponent::updateTrackRegions()
{
}

void TrackComponent::paint(Graphics & g)
{
	g.fillAll(Colours::black);   // clear the background

	g.setColour(Colours::grey);
	g.drawRect(0, 0, getParentWidth(), getParentHeight());   // draw an outline around the component
}

void TrackComponent::resized()
{

}
