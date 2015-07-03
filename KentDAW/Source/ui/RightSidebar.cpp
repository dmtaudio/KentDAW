/*
  ==============================================================================

    RightSidebar.cpp
    Created: 2 Jul 2015 1:18:49pm
    Author:  Matt

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "RightSidebar.h"

//==============================================================================
RightSidebar::RightSidebar()
	: tsThread("File Tree Test"),
	directoryList(nullptr, tsThread),
	fileTree(directoryList)
{
	addAndMakeVisible(fileTree);
}

RightSidebar::~RightSidebar()
{
}

void RightSidebar::paint (Graphics& g)
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
}

void RightSidebar::resized()
{
	fileTree.setBounds(0,0,getParentWidth(),getParentHeight())
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
