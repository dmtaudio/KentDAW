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
    
    TimelineCursor(AudioTransportSource& source);
    ~TimelineCursor();
    
    class  Listener
    {
    public:
        Listener()          {}
        virtual ~Listener() {}
        
        virtual bool positionChanged(AudioTransportSource& source) = 0;
        virtual void transportChanged(AudioTransportSource& source) = 0;
    };
    
    void addListener(Listener* const listener) {listeners.add(listener);}
    void removeListener(Listener* const listener) {listeners.remove(listener);}
    
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
    ListenerList<Listener> listeners;
    
private:
    AudioTransportSource& _transporSource;
    double _currentSampleRate;
    double _trackLength, _oneOverTrackLength;
    double _zoomRatio, _offsetRatio;
    bool _stopTimer, _showCursor;
    
    Image cursor;
    
    int _previousXCoords, _currentXCoords;
    float _xScale;
    double _mouseX;
    
    void startTimerIfCursorIsVisible();
    void setPlayerPosition(int mouseX);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimelineCursor);
};



#endif  // TIMELINECURSOR_H_INCLUDED
