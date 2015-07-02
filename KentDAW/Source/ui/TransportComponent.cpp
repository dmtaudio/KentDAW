/*
  ==============================================================================

    TransportComponent.cpp
    Created: 1 Jul 2015 12:25:09pm
    Author:  dtl

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "BinaryData.h"
#include "TransportComponent.h"

//==============================================================================
TransportComponent::TransportComponent()
: playButton(new ImageButton("Play")),
  recordButton(new ImageButton("Record")),
  stopButton(new ImageButton("Stop")),
  forwardButton(new ImageButton("Forward")),
  backwardButton(new ImageButton("Backward")),
  toStartButton(new ImageButton("ToStart")),
  toEndButton(new ImageButton("ToEnd")),
  buttonWidth(50), buttonHeight(50)
{
    setButtonColours(Colours::transparentBlack, Colours::transparentBlack, Colours::transparentWhite);
    
    transportButtons.add(playButton);
    transportButtons.add(recordButton);
    transportButtons.add(stopButton);
    transportButtons.add(forwardButton);
    transportButtons.add(backwardButton);
    transportButtons.add(toStartButton);
    transportButtons.add(toEndButton);
    initButtons(transportButtons);
    
    setButtonBounds();
    
    for(int i = 0; i < transportButtons.size(); ++i)
    {
        addAndMakeVisible(transportButtons[i]);
        transportButtons[i]->addListener(this);
    }
    
    toEndButton->setTooltip("Skip to end.");
    forwardButton->setTooltip("Fast forward.");
    stopButton->setTooltip("Stop.");
    playButton->setTooltip("Play.");
    recordButton->setTooltip("Record.");
    backwardButton->setTooltip("Fast rewind.");
    toStartButton->setTooltip("Skip to start.");
    
    playButton->addShortcut(KeyPress(KeyPress::spaceKey));
    toStartButton->addShortcut(KeyPress(KeyPress::returnKey));
    
}

TransportComponent::~TransportComponent()
{
    //deleteAllChildren();
}

void TransportComponent::setButtonColours(Colour normal, Colour hovered, Colour pressed)
{
    normalImageColour = normal;
    hoveredImageColour = hovered;
    pressedImageColour = pressed;
}

void TransportComponent::setButtonImage(ImageButton *button)
{
    button->setImages(false, true, true, image, normalImageOpacity, normalImageColour, image, hoveredImageOpacity, hoveredImageColour, image, pressedImageOpacity, pressedImageColour, 0.0f);
}

void TransportComponent::initButtons(OwnedArray<juce::ImageButton> &buttons)
{
    for(int button = 0; button < buttons.size(); ++button)
    {
        if(buttons[button]->getName() == "Play")
        {
            image = ImageCache::getFromMemory(BinaryData::playbutton_png, BinaryData::playbutton_pngSize);
        }
        else if(buttons[button]->getName() == "Record")
        {
            image = ImageCache::getFromMemory(BinaryData::recordbutton_png, BinaryData::recordbutton_pngSize);
        }
        else if(buttons[button]->getName() == "Stop")
        {
            image = ImageCache::getFromMemory(BinaryData::stopbutton_png, BinaryData::stopbutton_pngSize);
        }
        else if(buttons[button]->getName() == "Forward")
        {
            image = ImageCache::getFromMemory(BinaryData::forwardbutton_png, BinaryData::forwardbutton_pngSize);
        }
        else if(buttons[button]->getName() == "Backward")
        {
            image = ImageCache::getFromMemory(BinaryData::backwardbutton_png, BinaryData::backwardbutton_pngSize);
        }
        else if(buttons[button]->getName() == "ToStart")
        {
            image = ImageCache::getFromMemory(BinaryData::toStartbutton_png, BinaryData::toStartbutton_pngSize);
        }
        else if(buttons[button]->getName() == "ToEnd")
        {
            image = ImageCache::getFromMemory(BinaryData::toEndbutton_png, BinaryData::toEndbutton_pngSize);
        }
        setButtonImage(buttons[button]);
        addAndMakeVisible(buttons[button]);
    }
}

void TransportComponent::setButtonBounds()
{
	auto startposition = ((getWidth() - 8 * buttonWidth) / 2);
    
    toEndButton->setBounds(startposition, 0, 50, 40);
    forwardButton->setBounds(toEndButton->getRight(), 0, buttonWidth, buttonHeight);
    stopButton->setBounds(forwardButton->getRight(), 0, buttonWidth, buttonHeight);
    playButton->setBounds(stopButton->getRight(), 0, buttonWidth, buttonHeight);
    recordButton->setBounds(playButton->getRight(), 0, buttonWidth, buttonHeight);
    backwardButton->setBounds(recordButton->getRight(), 0, buttonWidth, buttonHeight);
    toStartButton->setBounds(backwardButton->getRight(), 0, buttonWidth, buttonHeight);
}

void TransportComponent::addListener(TransportComponent::Listener *listener)
{
    listenerList.add(listener);    
}

void TransportComponent::removeListener(TransportComponent::Listener *listener)
{
    listenerList.remove(listener);
}

void TransportComponent::buttonClicked(Button *button)
{
    if(button == toEndButton)
    {
        
    }
    else if(button == forwardButton)
    {
        
    }
    else if(button == stopButton)
    {
        
    }
    else if(button == playButton)
    {
        
    }
    else if (button == recordButton)
    {
        
    }
    else if(button == backwardButton)
    {
        
    }
    else if(button == toStartButton)
    {
        
    }
}

void TransportComponent::getCommandInfo(CommandID commandID, ApplicationCommandInfo &result)
{
    
}

bool TransportComponent::perform(const ApplicationCommandTarget::InvocationInfo &info)
{
    return false;
}

void TransportComponent::getAllCommands(Array<CommandID> &commands)
{
    
}

ApplicationCommandTarget* TransportComponent::getNextCommandTarget()
{
	return nullptr;
}



void TransportComponent::paint (Graphics& g)
{
  
}

void TransportComponent::resized()
{
    setButtonBounds();
}
