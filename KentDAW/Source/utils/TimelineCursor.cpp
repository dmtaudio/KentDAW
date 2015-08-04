/*
  ==============================================================================

    TimelineCursor.cpp
    Created: 4 Aug 2015 1:51:35pm
    Author:  dtl

  ==============================================================================
*/

#include "TimelineCursor.h"

TimelineCursor::TimelineCursor(AudioTransportSource& source)
: _transporSource(source), _currentSampleRate(44100.0), _zoomRatio(1.0),
  _offsetRatio(0.0), _stopTimer(false), _showCursor(true)
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
    startTimer();
}

void TimelineCursor::paint(juce::Graphics &g)
{
    if(_showCursor)
        g.drawImageAt(cursor, _currentXCoords - 1, 0);
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
    const int firstPixel = roundToInt(getWidth() * _offsetRatio);
    _previousXCoords = _currentXCoords;
    _currentXCoords = firstPixel + roundToInt(getWidth() * _oneOverTrackLength * _transporSource.getCurrentPosition() / _zoomRatio);
    if(_currentXCoords != _previousXCoords)
    {
        repaint(_previousXCoords = 2, 0, 5, getHeight());
        repaint(_currentXCoords = 2, 0, 5, getHeight());
    }
    if(_stopTimer)
    {
        _stopTimer = false;
        stopTimer();
    }
}

void TimelineCursor::transportStateChanged(AudioTransportSource *source)
{
    if(source == &_transporSource)
        startTimer();
}

void TimelineCursor::mouseDown(const MouseEvent &e)
{
    if(_showCursor)
    {
        setMouseCursor(MouseCursor::IBeamCursor);
        _xScale = (float) ((_trackLength / getWidth() * _zoomRatio));
        setPlayerPosition(e.x);
        
        _stopTimer = false;
        Timer::startTimer(40);
        repaint();
    }
}

void TimelineCursor::mouseUp(const MouseEvent &)
{
    if(_showCursor)
    {
        setMouseCursor(MouseCursor::NormalCursor);
        startTimer();
    }
}

void TimelineCursor::mouseDrag(const MouseEvent &e)
{
    if(_showCursor)
        setPlayerPosition(e.x);
}

void TimelineCursor::startTimer()
{
    if(_showCursor)
    {
        _stopTimer = false;
        Timer::startTimer(40);
    }
    else
    {
        _stopTimer = true;
    }
}

void TimelineCursor::setPlayerPosition(int)
{
    const int firstPixel = roundToInt(getWidth() * _offsetRatio);
    double position = _xScale * (_mouseX - firstPixel);
    _transporSource.setPosition(position);
}




