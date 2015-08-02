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
#include "MainComponent.h"
//==============================================================================
TimerComponent::TimerComponent()
: totalTime(0),
  isRunning(false),
  isRecording(false),
  totalRecordTime(0)
{
    timerFont = Font("Default Light", 30, Font::plain);
    startTimer(100);
}

TimerComponent::~TimerComponent()
{}

void TimerComponent::paint(Graphics& g)
{
    if(isRecording)
    {
        g.fillAll(Colour(58,58,58));
    }
    else
    {
        g.fillAll(Colour(58,58,58));
    }
    drawCurrentTime(g);
}

void TimerComponent::drawCurrentTime(Graphics& g)
{
    if(isRunning)
    {
        int64 current = Time::currentTimeMillis();
        int64 difference = current - lastTime;
        totalTime += difference;
        
        if(isRecording)
        {
            totalRecordTime += difference;
        }
        lastTime = Time::currentTimeMillis();
    }
    
    int minutes, seconds;
    
    if(isRecording)
    {
        g.setColour(Colour(255,0,0));
        minutes = floor(totalRecordTime/60000.0);
        seconds = floor((totalRecordTime - minutes*60000.0)/1000.0);
    }
    else
    {
        if(isRunning)
            g.setColour(Colours::green);
        else
            g.setColour(Colours::whitesmoke);
        
        minutes = floor(totalRecordTime/60000.0);
        seconds = floor((totalRecordTime - minutes*60000.0)/1000.0);
    }
    
    String m = formatTimeToString(minutes);
    String s = formatTimeToString(seconds);
    
    timerString = "";
    
    timerString += m;
    timerString += " : ";
    timerString += s;
    
    g.setFont(timerFont);
    g.drawText(timerString, getWidth()/2, 20, getWidth()/2, getHeight(), Justification::left, false);
}

void TimerComponent::start()
{
    if(!isRunning)
    {
        isRunning = true;
        lastTime = Time::currentTimeMillis();
    }
}

void TimerComponent::stop()
{
    if(isRunning)
    {
        isRunning = false;
        isRecording = false;
    }
}

void TimerComponent::startRecording()
{
    if(!isRecording)
    {
        isRecording = true;
        start();
    }
}

void TimerComponent::stopRecording()
{
    if(isRecording)
    {
        isRecording = false;
        stop();
    }
}

void TimerComponent::resetRecordTime()
{
    totalRecordTime = 0;
}

String TimerComponent::formatTimeToString(unsigned int val)
{
    char buff[500];
    String str;
    if(val < 10)
    {
        sprintf(buff, "0%u", val);
        str = buff;
    }
    else
    {
        sprintf(buff, "%u", val);
        str = buff;
    }
    return(str);
}

void TimerComponent::timerCallback()
{
    repaint();
}



TransportComponent::TransportComponent(AudioEngine* engine)
: loopButton(new ImageButton("Loop")),
  playButton(new ImageButton("Play")),
  recordButton(new ImageButton("Record")),
  stopButton(new ImageButton("Stop")),
  forwardButton(new ImageButton("Forward")),
  backwardButton(new ImageButton("Backward")),
  toStartButton(new ImageButton("ToStart")),
  toEndButton(new ImageButton("ToEnd")),
  buttonWidth(50), buttonHeight(50),
  _engine(engine)
{
    setButtonColours(Colours::transparentBlack, Colours::transparentBlack, Colours::transparentWhite);
    
    transportButtons.add(loopButton);
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
    
    loopButton->setTooltip("Loop.");
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
    removeAllChildren();
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
        if(buttons[button]->getName() == "Loop")
        {
            image = ImageCache::getFromMemory(BinaryData::loopbutton_png, BinaryData::loopbutton_pngSize);
        }
        else if(buttons[button]->getName() == "Play")
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
    
    loopButton->setBounds(startposition, 0, 50, 40);
    toStartButton->setBounds(loopButton->getRight(), 0, buttonWidth, buttonHeight);
    backwardButton->setBounds(toStartButton->getRight(), 0, buttonWidth, buttonHeight);
    recordButton->setBounds(backwardButton->getRight(), 0, buttonWidth, buttonHeight);
    playButton->setBounds(recordButton->getRight(), 0, buttonWidth, buttonHeight);
    stopButton->setBounds(playButton->getRight(), 0, buttonWidth, buttonHeight);
    forwardButton->setBounds(stopButton->getRight(), 0, buttonWidth, buttonHeight);
    toEndButton->setBounds(forwardButton->getRight(), 0, buttonWidth, buttonHeight);
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
        _engine->getMixer()->stop();
    }
    else if(button == playButton)
    {
        _engine->getMixer()->start();
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

void TransportComponent::paint (Graphics& g)
{
  
}

void TransportComponent::resized()
{
    setButtonBounds();
}
