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
#include "../core/ProjectManager.h"



//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component,
                               public MenuBarModel,
                               public DragAndDropContainer
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
		SaveProject = 1001,
		LoadProject = 1002,
		ImportAudio = 1003,
        Close = 1004
    };
    
    enum EditMenuIDs
    {
        Cut = 1005,
        Copy = 1006,
        Paste = 1007
    };

	enum ToolMenuIDs
	{
		Settings = 1008
	};
    
    enum WindowMenuIDs
    {
        TransportWindow = 1009
    };

private:
    Array<Component::SafePointer<Component>> windows;
    
    ScopedPointer<ApplicationCommandManager> commandManager;
	ProjectManager projectManager;
	//Menu Bar
    ScopedPointer<MenuBarModel> menuModel;
    ScopedPointer<MenuBarComponent> menuBar;

	//Transport
    TransportComponent* transport;
    TimerComponent* timer;
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
