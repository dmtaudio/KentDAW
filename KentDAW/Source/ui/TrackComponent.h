/*
  ==============================================================================

    TrackComponent.h
    Created: 2 Aug 2015 8:18:56pm
    Author:  Matt

  ==============================================================================
*/

#ifndef TRACKCOMPONENT_H_INCLUDED
#define TRACKCOMPONENT_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../core/AudioTrack.h"
#include "RegionComponent.h"

class TrackComponent : public Component
	//private ScrollBarListener
	//private Timer
{
public:
	TrackComponent(AudioTrack *track, int trackNumber);
	~TrackComponent();

	void createRegionGUI(AudioRegion* region, AudioFormatManager& formatManager, File& audioFile);
	void updateTrackRegions();
	int getTrackNumber();
	void setTrackNumber(int trackNumber);

	void paint(Graphics& g);
	void resized();

private:
	std::vector<RegionComponent*> regionComponents;
	AudioTrack *_track;
	int _trackNumber;
};

#endif  // TRACKCOMPONENT_H_INCLUDED
