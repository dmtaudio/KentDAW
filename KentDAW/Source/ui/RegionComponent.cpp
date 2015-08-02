/*
  ==============================================================================

    RegionComponent.cpp
    Created: 2 Aug 2015 11:34:48pm
    Author:  Matt

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "RegionComponent.h"

//==============================================================================
RegionComponent::RegionComponent()
{
}

RegionComponent::~RegionComponent()
{
}

void RegionComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    g.drawText ("RegionComponent", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void RegionComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
