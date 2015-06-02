//
//  Transport.cpp
//  DAW
//
//  Created by Dan on 31/05/2015.
//
//

#include "Transport.h"
#include "BinaryData.h"

//==============================================================================
Transport::Transport()
{
    transportButtons.add(play = new ImageButton("Play"));
    transportButtons.add(stop = new ImageButton("Stop"));
    transportButtons.add(record = new ImageButton("Record"));
    transportButtons.add(forward = new ImageButton("Forward"));
    transportButtons.add(backward = new ImageButton("Backward"));
    transportButtons.add(toEnd = new ImageButton("End"));
    transportButtons.add(toStart = new ImageButton("Start"));
    initButtons(transportButtons);
    
    timeFont = new Font(20.0, 0);
    timeTicks = new Label();
    timeTicks->getTextValue().setValue("1 1 1 1");
    timeTicks->setFont(*timeFont);
    addAndMakeVisible(timeTicks);
    timeSecs = new Label();
    timeSecs->getTextValue().setValue("00:00:00:00.00");
    timeSecs->setFont(*timeFont);
    addAndMakeVisible(timeSecs);
}

Transport::~Transport()
{
    deleteAllChildren();
}

// iterate buttons array and set image to button
void Transport::initButtons(OwnedArray<ImageButton> &buttons)
{
    for(int i = 0; i < buttons.size(); ++i)
    {
        if(buttons[i]->ImageButton::getName() == "Play")
        {
            image = ImageCache::getFromMemory(BinaryData::playbutton_png, BinaryData::playbutton_pngSize);
            buttons[i]->ImageButton::setTooltip("Play track");
        } else if(buttons[i]->ImageButton::getName() == "Stop") {
            image = ImageCache::getFromMemory(BinaryData::stopbutton_png, BinaryData::stopbutton_pngSize);
            buttons[i]->ImageButton::setTooltip("Stop track");
        } else if(buttons[i]->ImageButton::getName() == "Record") {
            image = ImageCache::getFromMemory(BinaryData::recordbutton_png, BinaryData::recordbutton_pngSize);
            buttons[i]->ImageButton::setTooltip("Record track");
        } else if(buttons[i]->ImageButton::getName() == "Forward") {
            image = ImageCache::getFromMemory(BinaryData::forwardbutton_png, BinaryData::forwardbutton_pngSize);
            buttons[i]->ImageButton::setTooltip("Skip forward");
        } else if(buttons[i]->ImageButton::getName() == "Backward") {
            image = ImageCache::getFromMemory(BinaryData::backwardbutton_png, BinaryData::backwardbutton_pngSize);
            buttons[i]->ImageButton::setTooltip("Skip backward");
        } else if(buttons[i]->ImageButton::getName() == "End") {
            image = ImageCache::getFromMemory(BinaryData::toEndbutton_png, BinaryData::toEndbutton_pngSize);
            buttons[i]->ImageButton::setTooltip("Skip to end");
        } else if(buttons[i]->ImageButton::getName() == "Start") {
            image = ImageCache::getFromMemory(BinaryData::toStartbutton_png, BinaryData::toStartbutton_pngSize);
            buttons[i]->ImageButton::setTooltip("Skip to start");
        }
        setButtonImage(buttons[i]);
        addAndMakeVisible(buttons[i]);
    }
}

/* set buttons to image and apply opacity and colour constraint
   NOTE: we will need a seperate one of these for record and stop to change the image to green for play button and red for record
 */
void Transport::setButtonImage(ImageButton* button)
{
    button->setImages (true, true, true,
                       image, 0.7f, Colours::transparentBlack,
                       image, 1.0f, Colours::transparentBlack,
                       image, 1.0f, Colours::pink.withAlpha (0.8f),
                       0.5f);
}

void Transport::paint (Graphics& g)
{
    g.fillAll (Colour (Colours::hotpink));
    
    g.setFont (Font (16.0f));
    g.setColour (Colours::white);

    g.drawRoundedRectangle(getWidth() - 235, 0, 200, 50, 20, 2);

}

void Transport::resized()
{
    // set button bounds
    play->setBounds(150, 0, 50, 50);
    stop->setBounds(200, 0, 50, 50);
    record->setBounds(100, 0, 50, 50);
    forward->setBounds(250, 0, 50, 50);
    backward->setBounds(50, 0, 50, 50);
    toEnd->setBounds(300, 0, 50, 50);
    toStart->setBounds(0, 0, 50, 50);
    
    timeTicks->setBounds(getWidth()- 115, 0, 100, 30);
    timeSecs->setBounds(getWidth()- 215, 0, 100, 30);
    
}
