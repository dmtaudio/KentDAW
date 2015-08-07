/*
 ==============================================================================
 
 TimelineCursor.cpp
 Created: 4 Aug 2015 1:51:35pm
 Author:  dtl
 
 ==============================================================================
 */

#include "TimelineCursor.h"

TimelineCursor::TimelineCursor(AudioTransportSource& source, Range<double> parentRange)
: _transporSource(source), _currentSampleRate(44100.0), _zoomRatio(1.0),
_offsetRatio(0.0), _stopTimer(false), _showCursor(true), _visibleRange(parentRange),
_canMoveTransport(true)
{
    //_transporSource.addChangeListener(this);
    
}

TimelineCursor::~TimelineCursor()
{
    //_transporSource.removeChangeListener(this);
    stopTimer();
}

void TimelineCursor::setZoomRatio(double zoomRatio)
{
    if(zoomRatio < 0.0 || zoomRatio > 10000.0)
        zoomRatio = 1.0;
    
    _zoomRatio = zoomRatio;
    repaint();
}

void TimelineCursor::setStartOffsetRatio(double startOffset)
{
    _offsetRatio = startOffset;
    repaint();
}

void TimelineCursor::setCursorVisability(bool displayCursor)
{
    _showCursor = displayCursor;
    startTimerIfCursorIsVisible();
}

void TimelineCursor::paint(juce::Graphics &g)
{
    if(_showCursor)
        g.drawImageAt(cursor, _currentXCoords, 0);
}

void TimelineCursor::resized()
{
    cursor = Image(Image::RGB, 3, jmax(1, getHeight()), true);
    Graphics g(cursor);
    g.fillAll(Colours::black);
    g.setColour(Colours::grey);
    g.drawVerticalLine(1, 0.0f, (float) cursor.getHeight());
}

void TimelineCursor::timerCallback()
{
    if(_canMoveTransport)
        updateCursorPosition();

    repaint(_currentXCoords = 2, 0, 5, getHeight());

    if(_stopTimer)
    {
        _stopTimer = false;
        stopTimer();
    }
}

void TimelineCursor::mouseDown(const MouseEvent &e)
{
    if(_showCursor)
    {
        setMouseCursor(MouseCursor::IBeamCursor);
        setPlayerPosition(e.x);
        
        _stopTimer = false;
        startTimer(40);
        repaint();
    }
}

void TimelineCursor::mouseUp(const MouseEvent &e)
{
    if(_showCursor)
    {
        setMouseCursor(MouseCursor::NormalCursor);
        startTimerIfCursorIsVisible();
    }
}

void TimelineCursor::mouseDrag(const MouseEvent &e)
{
    if(_showCursor)
    {
        _currentXCoords = e.x;
        setPlayerPosition(_currentXCoords);
        repaint();
    }
    
}

void TimelineCursor::startTimerIfCursorIsVisible()
{
    if(_showCursor)
    {
        _stopTimer = false;
        startTimer(40);
    }
    else
    {
        _stopTimer = true;
    }
}

void TimelineCursor::setPlayerPosition(int mousePosX)
{
    double time = xToTime((float) mousePosX);
    double position = timeToSamples(time);
    _transporSource.setPosition(position);
}

void TimelineCursor::updateCursorPosition()
{
    _currentXCoords = timeToX(_transporSource.getCurrentPosition() - 0.75f
                              );
    repaint();
}

void TimelineCursor::setVisibleRange(Range<double> range)
{
    _visibleRange = range;
    updateCursorPosition();
    repaint();
}

float TimelineCursor::timeToX(const double time) const
{
    return getWidth() * (float) ((time - _visibleRange.getStart()) / (_visibleRange.getLength()));
}

float TimelineCursor::xToTime(const float x) const
{
    return (x / getWidth()) * (_visibleRange.getLength()) + _visibleRange.getStart();
}

float TimelineCursor::timeToSamples(const float time) const
{
    return time * _currentSampleRate;
}



