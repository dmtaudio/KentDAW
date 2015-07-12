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
    
    void showTransportWindow();
    
    enum FileMenuIDs
    {
        NewProject = 1000, // replace with binary or hex numbers when appropriate
		ImportAudio = 1005,
        Close = 1001
    };
    
    enum EditMenuIDs
    {
        Cut = 1002,
        Copy = 1003,
        Paste = 1004
    };

	enum ToolMenuIDs
	{
		Settings = 1006
	};
    
    enum WindowMenuIDs
    {
        TransportWindow = 1007
    };

private:
    Array<Component::SafePointer<Component>> windows;
    
	//Menu Bar
    ScopedPointer<MenuBarModel> menuModel;
    ScopedPointer<MenuBarComponent> menuBar;

	//Transport
    TransportComponent* transport;
    ScopedPointer<ArrangeWindow> arrangeWindow;

	//Left Side
	ScopedPointer<LeftSidebar> leftSideBar;

	//Right Side
    TimeSliceThread tsThread;
	DirectoryContentsList directoryList;
	FileTreeComponent fileTree;
	//ScopedPointer<RightSidebar> rightSideBar;

	//Status Bar
	ScopedPointer<StatusBar> statusBar;
    

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
