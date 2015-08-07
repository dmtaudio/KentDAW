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
#include "TimelineCursor.h"
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
    
    void setVisibleRange(Range<double> range);

    void paint (Graphics&);
    void resized();
    void createGuiForTrack(AudioTrack* track, int trackNumber);
	void addRegionToTrackGUI(AudioRegion* region, int trackNumber, AudioFormatManager& formatManager, File& audioFile);
	//void updateArrangeWindow();

private:
	AudioEngine *_audioEngine;
    ScopedPointer<TimelineCursor> cursor;
	//HashMap<int, TrackComponent*> trackComponents;
    std::vector<TrackComponent*> trackComponents;
    
    Range<double> _visibleRange;
    
    // just for testing
    AudioFormatManager formatManager;
    AudioFormatReader* reader;
    ScopedPointer<AudioFormatReaderSource> source;
    AudioTransportSource transport;
    
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArrangeWindow)

   
};

#endif  // ARRANGEWINDOW_H_INCLUDED
