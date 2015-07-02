/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "TransportComponent.h"
#include "ArrangeWindow.h"
#include "LeftSidebar.h"
#include "RightSidebar.h"
#include "StatusBar.h"
#include "../JuceLibraryCode/JuceHeader.h"



//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component,
                               public MenuBarModel
{
public:
    
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&);
    void resized();
    
    StringArray getMenuBarNames();
    PopupMenu getMenuForIndex(int index, const String &name);
    void menuItemSelected(int menuItemID, int index);
    
    enum FileMenuIDs
    {
        NewProject = 1000, // replace with binary or hex numbers when appropriate
        Close = 1001
    };
    
    enum EditMenuIDs
    {
        Cut = 1002,
        Copy = 1003,
        Paste = 1004
    };

private:
    ScopedPointer<MenuBarModel> menuModel;
    ScopedPointer<MenuBarComponent> menuBar;
    ScopedPointer<TransportComponent> transport;
    ScopedPointer<ArrangeWindow> arrangeWindow;
	ScopedPointer<LeftSidebar> leftSideBar;
	ScopedPointer<RightSidebar> rightSideBar;
	ScopedPointer<StatusBar> statusBar;
    

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
