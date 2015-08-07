/*
 ==============================================================================
 
 TimelineCursor.h
 Created: 4 Aug 2015 1:51:35pm
 Author:  dtl
 
 ==============================================================================
 */

#ifndef TIMELINECURSOR_H_INCLUDED
#define TIMELINECURSOR_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"

class TimelineCursor : public Component,
                       public Timer
{
    
public:
    
    TimelineCursor(AudioTransportSource& source, Range<double> parentRange);
    ~TimelineCursor();
    
    void setVisibleRange(Range<double> range);
    
    void setZoomRatio(double zoomRatio);
    void setStartOffsetRatio(double startOffset);
    void setCursorVisability(bool displayCursor);
    
    void positionChanged(AudioTransportSource* source);
    
    void paint(Graphics &g);
    void resized();
    
    void mouseDown(const MouseEvent &e);
    void mouseUp(const MouseEvent &e);
    void mouseDrag(const MouseEvent &e);
    
    void start();
    void stop();
    
    void timerCallback();
    
    //void changeListenerCallback (ChangeBroadcaster* source);
    
protected:
    void updateCursorPosition();
    
private:
    AudioTransportSource& _transporSource;
    double _currentSampleRate;
    double _trackLength;
    double _zoomRatio, _offsetRatio;
    bool _stopTimer, _showCursor;
    Range<double> _visibleRange;
    bool _followTransport, _canMoveTransport;
    
    Image cursor;
    
    int _currentXCoords;
    double _mouseX;
    
    float timeToX(const double time) const;
    float xToTime(const float x) const;
    float timeToSamples(const float time) const;
    
    void startTimerIfCursorIsVisible();
    void setPlayerPosition(int mouseX);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimelineCursor);
};



#endif  // TIMELINECURSOR_H_INCLUDED
