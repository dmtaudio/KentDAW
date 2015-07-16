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
	fileTree(directoryList)
{
	//Menu Bar
    menuBar = new MenuBarComponent(this);

	//Transport
    transport = new TransportComponent();
    timer = new TimerComponent();

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
    transport->setVisible(false);
    delete transport;
    timer->setVisible(false);
    delete timer;
}

void MainContentComponent::showTransportWindow()
{
    //TransportComponent* transportComponent = transport;
    transport->addToDesktop (ComponentPeer::windowAppearsOnTaskbar);
    timer->addToDesktop(ComponentPeer::windowAppearsOnTaskbar);
    windows.add(transport);
    windows.add(timer);

    Rectangle<int> timerArea (0,0 , getWidth() / 2, 100);
    const RectanglePlacement placement1 (RectanglePlacement::xLeft + RectanglePlacement::yBottom + RectanglePlacement::doNotResize);
    Rectangle<int> timerResult (placement1.appliedTo (timerArea, Desktop::getInstance().getDisplays().getMainDisplay().userArea.reduced (20)));
    
    timer->setBounds(timerResult);
    timer->setVisible(true);
    timer->setAlwaysOnTop(true);
    
    Rectangle<int> buttonsArea (0,0 , getWidth(), 100);
    const RectanglePlacement placement2 (RectanglePlacement::xLeft + RectanglePlacement::yBottom + RectanglePlacement::doNotResize);
    Rectangle<int> buttonsResult (placement2.appliedTo (buttonsArea, Desktop::getInstance().getDisplays().getMainDisplay().userArea.reduced (20)));
    transport->setBounds (buttonsResult);
    transport->setVisible (true);
    transport->setAlwaysOnTop(true);
}

StringArray MainContentComponent::getMenuBarNames()
{
    const char* const names[] = { "File", "Edit", "Tools", "Transport", "Arrange", "Window", "Help", nullptr };
    return StringArray(names);
}

PopupMenu MainContentComponent::getMenuForIndex(int index, const String &name)
{
    PopupMenu menu;

    if(name == "File") {
        // Add file menu items
        menu.addCommandItem(commandManager, CommandIDs::newProject);
        menu.addCommandItem(commandManager, CommandIDs::importAudio);
        menu.addCommandItem(commandManager, CommandIDs::close);
	} else if (name == "Edit") {
        menu.addCommandItem(commandManager, CommandIDs::cut);
        menu.addCommandItem(commandManager, CommandIDs::copy);
		menu.addCommandItem(commandManager, CommandIDs::paste);
	} else if (name == "Tools") {
        menu.addCommandItem(commandManager, CommandIDs::settings);
    } else if(name == "Transport") {
        
    } else if(name == "Arrange") {
        
    } else if(name == "Window") {
        menu.addCommandItem(commandManager, CommandIDs::transport);
    } else if(name == "Help") {
        
    }
    return menu;
}

void MainContentComponent::menuItemSelected(int menuItemID, int index)
{
    switch(menuItemID)
    {
        case CommandIDs::newProject:
            break;
		case CommandIDs::importAudio:
            timer->stop();
			break;
        case CommandIDs::close:
            JUCEApplication::getInstance()->systemRequestedQuit();
            break;
        case CommandIDs::cut:
            break;
        case CommandIDs::copy:
            break;
        case CommandIDs::paste:
            break;
        case CommandIDs::transport:
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
		case CommandIDs::settings:
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

ApplicationCommandTarget* MainContentComponent::getNextCommandTarget()
{
    return findFirstTargetParentComponent();
}

void MainContentComponent::getAllCommands(Array<CommandID> &commands)
{
    const CommandID ids[] =
    {
        CommandIDs::newProject,
        CommandIDs::openProject,
        CommandIDs::close,
        CommandIDs::copy,
        CommandIDs::cut,
        CommandIDs::paste,
        CommandIDs::play,
        CommandIDs::stop,
        CommandIDs::record,
        CommandIDs::forward,
        CommandIDs::backward,
        CommandIDs::toStart,
        CommandIDs::toEnd,
        CommandIDs::transport
    };
    commands.addArray(ids, numElementsInArray(ids));
}

void MainContentComponent::getCommandInfo(const CommandID commandID, ApplicationCommandInfo &result)
{
    switch(commandID)
    {
            
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
}