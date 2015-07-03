/*
  ==============================================================================

    RightSidebar.h
    Created: 2 Jul 2015 1:18:49pm
    Author:  Matt

  ==============================================================================
*/

#ifndef RIGHTSIDEBAR_H_INCLUDED
#define RIGHTSIDEBAR_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class RightSidebar    : public Component
{
public:
	RightSidebar();
    ~RightSidebar();

    void paint (Graphics&);
    void resized();

private:
	DirectoryContentsList directoryList;
	FileTreeComponent fileTree;
	TimeSliceThread tsThread;
	/*
	void fileClicked(const File&, const MouseEvent&);
	void fileDoubleClicked(const File&);
	void browserRootChanged(const File&);
	void buttonClicked(Button* buttonThatWasClicked);
	void sliderValueChanged(Slider* sliderThatWasMoved);
	void changeListenerCallback(ChangeBroadcaster* source);
	void selectionChanged();
	*/
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RightSidebar)
};


#endif  // RIGHTSIDEBAR_H_INCLUDED
