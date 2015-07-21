/*
  ==============================================================================

    MeterComponent.cpp
    Created: 29 Jun 2015 2:20:42pm
    Author:  dtl

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MeterComponent.h"


//==============================================================================
MeterComponent::MeterComponent()
{
    mLevel.peak = 0.0;
    mLevel.isClipping = false;
}

MeterComponent::~MeterComponent()
{
}

void MeterComponent::paint (Graphics& g)
{
    rect = getLocalBounds();
    g.fillAll (Colours::white);   // clear the background

    //g.setColour (Colours::black);
    g.drawRect (rect);   // draw an outline around the component
    rect.reduced(1, 1);
    
    float const peak = std::min (mLevel.peak, 1.0f);
    
    if (meterType.horizontal)
    {
        rect.setWidth (int (rect.getWidth () * peak + 0.5));
    }
    else
    {
        rect.setTop (int (rect.getBottom () - (rect.getHeight () * mLevel.peak + 0.5)));
    }
    
    if (mLevel.peak < 0.7f)
        g.setColour (Colours::green);
    else if (mLevel.peak < 1.0f)
        g.setColour (Colours::orange);
    else
        g.setColour (Colours::red);
    
    g.fillRect (rect);
}

void MeterComponent::setMeterLevel(AudioMixer::Level newLevel)
{
    mLevel = newLevel;
    repaint(rect);
}

void MeterComponent::setHorizontalType(bool isHorizontal)
{
    if(isHorizontal)
    {
        meterType.horizontal = true;
        meterType.vertical = false;
    }
    else
    {
        meterType.horizontal = false;
        meterType.vertical = true;
    }
}

void MeterComponent::setVerticalType(bool isVertical)
{
    if(isVertical)
    {
        meterType.vertical = true;
        meterType.horizontal = false;
        
    }
    else
    {
        meterType.vertical = true;
        meterType.horizontal = false;
    }
}

void MeterComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
