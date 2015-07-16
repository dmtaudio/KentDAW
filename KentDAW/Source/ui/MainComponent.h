/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "CommandIDs.h"
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
                               public MenuBarModel,
                               public ApplicationCommandTarget
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
    
    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands (Array <CommandID>& commands) override;
    void getCommandInfo (CommandID commandID, ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo& info) override;

private:
    Array<Component::SafePointer<Component>> windows;
    
    ScopedPointer<ApplicationCommandManager> commandManager;
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
