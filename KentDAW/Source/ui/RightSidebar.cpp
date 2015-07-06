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
		//Adds a File Tree Component to the right hand side of the GUI
	    addAndMakeVisible(fileTree);

	    directoryList.setDirectory(File::getSpecialLocation(File::userHomeDirectory), true, true);
	    tsThread.startThread(3);

		fileTree.setColour(FileTreeComponent::backgroundColourId, Colours::lightgrey.withAlpha(0.6f));
    	//fileTree.addListener(this);
	    setOpaque(true);
}

RightSidebar::~RightSidebar()
{
	//fileTree.removeListener(this);
	//deleteAllChildren();
	//fileTree.removeListener(this);
}

void RightSidebar::paint (Graphics& g)
{
	
    g.setColour (Colours::lightblue);

}

void RightSidebar::resized()
{
	Rectangle<int> rec(getLocalBounds().reduced(4));
	fileTree.setBounds(rec);
	// This method is where you should set the bounds of any child
	// components that your component contains..

}

/*
void selectionChanged() {}
void fileClicked(const File&, const MouseEvent&) {}
void fileDoubleClicked(const File&) {}
void browserRootChanged(const File&) {}
*/