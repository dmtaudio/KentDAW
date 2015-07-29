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
#include "../core/AudioEngine.h"



//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component,
                               public MenuBarModel,
                               public ApplicationCommandTarget,
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
    
    AudioEngine* getAudioEngine();
    
    enum FileMenuIDs
    {
        NewProject = 0x2000, 
		SaveProject = 0x2001,
		LoadProject = 0x2002,
		ImportAudio = 0x2003,
        Close = 0x2004
    };
    
    enum EditMenuIDs
    {
        Cut = 0x2005,
        Copy = 0x2006,
        Paste = 0x2008
    };

	enum ToolMenuIDs
	{
		Settings = 0x2009
	};
    
    enum WindowMenuIDs
    {
        TransportWindow = 0x2010
    };
    
    enum TransportIDs
    {
        ToStart = 0x201a,
        Backward = 0x201b,
        Record = 0x201c,
        Stop = 0x201d,
        Play = 0x201e,
        Forward = 0x201f,
        ToEnd = 0x2020
    };
    
    ApplicationCommandTarget* getNextCommandTarget() override;
    void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) override;
    void getAllCommands(Array<CommandID>& commands) override;
    bool perform (const ApplicationCommandTarget::InvocationInfo& info) override;

private:
    Array<Component*> windows;
    
    ScopedPointer<ApplicationCommandManager> commandManager;
	ProjectManager projectManager;
	//Menu Bar
    ScopedPointer<MenuBarModel> menuModel;
    ScopedPointer<MenuBarComponent> menuBar;

	//Transport
    ScopedPointer<TransportComponent> transport;
    ScopedPointer<TimerComponent> timer;
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
    
    // Audio Engine
    ScopedPointer<AudioEngine> audioEngine;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
