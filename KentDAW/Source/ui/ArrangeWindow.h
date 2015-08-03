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
#include "TrackComponent.h"
#include "../core/AudioTrack.h"
#include "../core/AudioRegion.h"
#include "../core/AudioEngine.h"
#include <vector>

//==============================================================================

class ArrangeWindow    : public Component
{
public:
    ArrangeWindow(AudioEngine *audioEngine);
    ~ArrangeWindow();

    void paint (Graphics&);
    void resized();
    void createGuiForTrack(AudioTrack* track);

	void AddRegionToTrackGUI(File & file, int trackNumber);

private:
	int trackNumber;
	AudioEngine *audioEngine;
	std::vector<TrackComponent*> trackComponents;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArrangeWindow)

   
};

#endif  // ARRANGEWINDOW_H_INCLUDED
