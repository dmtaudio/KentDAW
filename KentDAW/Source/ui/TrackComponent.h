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

class TrackComponent : public Component
	//private ScrollBarListener,
	//private Timer
{
public:
	TrackComponent(AudioTrack *track);
	~TrackComponent();

	void paint(Graphics& g);
	void resized();

private:
	AudioTrack *track;
};

#endif  // TRACKCOMPONENT_H_INCLUDED
