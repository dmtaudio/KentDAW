/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "AudioEngine.h"


//==============================================================================
MainContentComponent::MainContentComponent()
	: tsThread("File Tree Test"),
	directoryList(nullptr, tsThread),
	fileTree(directoryList)
{
	deviceManager.initialise(2, 2, nullptr, true);

	//Menu Bar
    menuBar = new MenuBarComponent(this);

	//Transport
    transport = new TransportComponent();

	//Arrange Window
    arrangeWindow = new ArrangeWindow();

	//Left Side
	leftSideBar = new LeftSidebar();

	//Status Bar
	statusBar = new StatusBar();

	setOpaque(true);

    setSize (getParentWidth(), getParentHeight());
    {
        addAndMakeVisible(menuBar);
		addAndMakeVisible(arrangeWindow);
        //addAndMakeVisible(transport);
		addAndMakeVisible(leftSideBar);
		addAndMakeVisible(fileTree);
		//addAndMakeVisible(rightSideBar);
		addAndMakeVisible(statusBar);

		setOpaque(true);
    }    


	directoryList.setDirectory(File::getSpecialLocation(File::userHomeDirectory), true, true);
	tsThread.startThread(3);
	fileTree.setColour(FileTreeComponent::backgroundColourId, Colours::lightgrey.withAlpha(0.6f));
}

MainContentComponent::~MainContentComponent()
{
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
		menu.addItem(ImportAudio, "Import Audio File");
        menu.addItem(Close, "Close");
	} else if (name == "Edit") {
		menu.addItem(Cut, "Cut");
		menu.addItem(Copy, "Copy");
		menu.addItem(Paste, "Paste");
	} else if (name == "Tools") {
		menu.addItem(Settings, "Settings");
    } else if(name == "Transport") {
        
    } else if(name == "Arrange") {
        
    } else if(name == "Window") {
        
    } else if(name == "Help") {
        
    }
    return menu;
}

void MainContentComponent::menuItemSelected(int menuItemID, int index)
{
    switch(menuItemID)
    {
        case NewProject:
            break;
		case ImportAudio:
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
	
	Rectangle<int> rec((getParentWidth()/4)*3+1,20,getParentWidth()/4, getParentHeight()-50);
	fileTree.setBounds(rec);
	
	statusBar->setBounds(0, (getParentHeight() / 100) * 96, getParentWidth(), 30);
    //transport->setBounds((getParentWidth()/100)*40,0, getWidth(), getHeight());
	
}