/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "../core/AudioEngine.h"

//==============================================================================
MainContentComponent::MainContentComponent()
	: tsThread("File Tree Test"),
	directoryList(nullptr, tsThread),
	fileTree(directoryList),
	projectManager()
{
    audioEngine = new AudioEngine();
    
    //Menu Bar
    menuBar = new MenuBarComponent(this);

	//Transport
    transport = new TransportComponent();
    timer = new TimerComponent();

	//Arrange Window
    arrangeWindow = new ArrangeWindow(audioEngine);

	//Left Side
	leftSideBar = new LeftSidebar();

	//Status Bar
	statusBar = new StatusBar();

	setOpaque(true);

    setSize (getParentWidth(), getParentHeight());
    {
        addAndMakeVisible(menuBar);
		addAndMakeVisible(arrangeWindow);
		addAndMakeVisible(leftSideBar);
		addAndMakeVisible(fileTree);
		addAndMakeVisible(statusBar);

		setOpaque(true);
    }    


	directoryList.setDirectory(File::getSpecialLocation(File::userHomeDirectory), true, true);
	tsThread.startThread(3);
	fileTree.setColour(FileTreeComponent::backgroundColourId, Colours::lightgrey.withAlpha(0.6f));
    fileTree.setDragAndDropDescription("Test");
}

MainContentComponent::~MainContentComponent()
{
    transport->setVisible(false);
    timer->setVisible(false);
}

void MainContentComponent::showTransportWindow()
{
    transport->addToDesktop (ComponentPeer::windowHasCloseButton);
    timer->addToDesktop(ComponentPeer::windowHasCloseButton);

    windows.add(transport);
    windows.add(timer);

    Rectangle<int> timerArea (0,0, getWidth()/2, 100);
    const RectanglePlacement placement1 (RectanglePlacement::xLeft + RectanglePlacement::yBottom + RectanglePlacement::doNotResize);
    Rectangle<int> timerResult (placement1.appliedTo (timerArea, Desktop::getInstance().getDisplays().getMainDisplay().userArea.reduced (20)));
    
    timer->setBounds(timerResult);
    timer->setVisible(true);
    timer->setAlwaysOnTop(true);
    
    Rectangle<int> buttonsArea (0,0, getWidth()/2, 100);
    const RectanglePlacement placement2 (RectanglePlacement::xLeft + RectanglePlacement::yBottom + RectanglePlacement::doNotResize);
    Rectangle<int> buttonsResult (placement2.appliedTo (buttonsArea, Desktop::getInstance().getDisplays().getMainDisplay().userArea.reduced (20)));
    transport->setBounds (buttonsResult);
    transport->setVisible (true);
    transport->setAlwaysOnTop(true);
}

StringArray MainContentComponent::getMenuBarNames()
{
    StringArray menuItems;
    menuItems.add("File");
    menuItems.add("Edit");
	menuItems.add("Tools");
    menuItems.add("Transport");
    menuItems.add("Arrange");
    menuItems.add("Window");
    menuItems.add("Help");
    
    return menuItems;
}

PopupMenu MainContentComponent::getMenuForIndex(int index, const String &name)
{
    PopupMenu menu;

    if(name == "File") {
        // Add file menu items
        menu.addItem(NewProject, "New Project");
		menu.addItem(SaveProject, "Save Project");
		menu.addItem(LoadProject, "Load Project");
		menu.addItem(ImportAudio, "Import Audio File");
        menu.addItem(Close, "Close");
	} else if (name == "Edit") {
		menu.addItem(Cut, "Cut");
		menu.addItem(Copy, "Copy");
		menu.addItem(Paste, "Paste");
	} else if (name == "Tools") {
		menu.addItem(Settings, "Settings");
    } else if(name == "Transport") {
        menu.addItem(Play, "Play");
        menu.addItem(Stop, "Stop");
    } else if(name == "Arrange") {
        
    } else if(name == "Window") {
        //menu.addItem(TransportWindow, "Transport");
        menu.addItem(TransportWindow, "Transport", true, false);
    } else if(name == "Help") {
        
    }
    return menu;
}

void MainContentComponent::menuItemSelected(int menuItemID, int index)
{
    switch(menuItemID)
    {
        case NewProject:
			projectManager.createBasicProject("Untitled Project");
            break;
		case SaveProject:
			projectManager.saveProject();
			break;
		case LoadProject:
			projectManager.loadProject();
			break;
		case ImportAudio:
			projectManager.importAudioFileToProjectManager();
			break;
        case Close:
            JUCEApplication::getInstance()->systemRequestedQuit();
            break;
        case Cut:
            break;
        case Copy:
            break;
        case Paste:
            break;
        case Play:
            audioEngine->getMixer()->start();
            break;
        case Stop:
            audioEngine->getMixer()->stop();
            break;
        case TransportWindow:
            if(!transport->isVisible() || !timer->isVisible())
            {
                showTransportWindow();
                transport->setVisible(true);
                timer->setVisible(true);
            }
            else
            {
                transport->setVisible(false);
                timer->setVisible(false);
            }
            break;
		case Settings:
			bool showMidiInputOptions = false;
			bool showMidiOutputSelector = false;
			bool showChanelsAsStereoPairs = true;
			bool hideAdvancedOptions = false;
            AudioDeviceSelectorComponent settings(AudioEngine::getSharedAudioDeviceManager(), 0, 0, 1, 2,
				showMidiInputOptions,
				showMidiOutputSelector,
				showChanelsAsStereoPairs,
				hideAdvancedOptions);
			settings.setSize(500, 400);
			DialogWindow::showModalDialog(String("Audio Settings"),
				&settings,
				TopLevelWindow::getTopLevelWindow(0),
				Colours::white,
				true);
			break;
    }
}

AudioEngine* MainContentComponent::getAudioEngine()
{
    return audioEngine;
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff001F36));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
}

void MainContentComponent::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..

    menuBar->setBounds(0, 0, getWidth(), 20);
	leftSideBar->setBounds(0, 20, getParentWidth() / 4, getParentHeight() - 50);
	arrangeWindow->setBounds(getParentWidth() / 4, 20, getParentWidth() / 2, (getParentHeight()/100)*80);
	
	//File Tree Right Side Of Screen
	Rectangle<int> fileTreeContainer((getParentWidth()/4)*3+1,20,getParentWidth()/4, getParentHeight()-50);
	fileTree.setBounds(fileTreeContainer);
	
	statusBar->setBounds(0, (getParentHeight() / 100) * 96, getParentWidth(), 30);
}

ApplicationCommandTarget* MainContentComponent::getNextCommandTarget()
{
    return findFirstTargetParentComponent();
}

void MainContentComponent::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
    const String fileCategory ("File Menu");
    const String editCategory ("Edit Menu");
    const String toolsCategory ("Tools Menu");
    const String windowCategory ("Window Menu");
    const String transportCategory ("Transport Controls");
    
    switch(commandID)
    {
        case MainContentComponent::FileMenuIDs::NewProject:
            result.setInfo ("New Project", "Create an new project", fileCategory, 0);
        case MainContentComponent::FileMenuIDs::ImportAudio:
            result.setInfo ("Import Audio", "Import audio into the project", fileCategory, 0);
        case MainContentComponent::FileMenuIDs::Close:
            result.setInfo ("Close", "Close the program", fileCategory, 0);
        case MainContentComponent::FileMenuIDs::LoadProject:
            result.setInfo ("Load", "Load the project", fileCategory, 0);
        case MainContentComponent::FileMenuIDs::SaveProject:
            result.setInfo ("Save", "Save the project", editCategory, 0);
        case MainContentComponent::EditMenuIDs::Copy:
            result.setInfo ("Copy", "Copy to the clipboard", editCategory, 0);
        case MainContentComponent::EditMenuIDs::Cut:
            result.setInfo ("Cut", "Cut to the clipboard", editCategory, 0);
        case MainContentComponent::EditMenuIDs::Paste:
            result.setInfo ("Paste", "Paste from the clipboard", editCategory, 0);
        case MainContentComponent::ToolMenuIDs::Settings:
            result.setInfo ("Settings", "Change the device settings", toolsCategory, 0);
        case MainContentComponent::WindowMenuIDs::TransportWindow:
            result.setInfo ("TransportWindow", "Show the transport window", toolsCategory, 0);
        case MainContentComponent::TransportIDs::Play:
            result.setInfo ("Play", "Play the track", transportCategory, 0);
        case MainContentComponent::TransportIDs::Stop:
            result.setInfo ("Stop", "Stop the track", transportCategory, 0);
        case MainContentComponent::TransportIDs::Forward:
            result.setInfo ("Forward", "Stop the track", transportCategory, 0);
    }
}
void MainContentComponent::getAllCommands(Array<CommandID>& commands)
{
    
}
bool MainContentComponent::perform (const ApplicationCommandTarget::InvocationInfo& info)
{
    return false;
}
