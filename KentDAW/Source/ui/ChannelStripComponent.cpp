/*
  ==============================================================================

    ChannelStripComponent.cpp
    Created: 21 Jul 2015 11:43:55am
    Author:  dtl

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include <list>
#include "ChannelStripComponent.h"
#include "../core/AudioRegionFactory.h"

//==============================================================================
ChannelStripComponent::ChannelStripComponent()
{
    // just for testing purposes
    mLevel.peak = 0.3;
    mLevel.isClipping = false;
    
    addAndMakeVisible(meter = new MeterComponent());
    
    addAndMakeVisible(label = new Label(String::empty, String::empty));
    label->setFont(Font(11.0f, Font::FontStyleFlags::plain));
    label->setJustificationType(Justification::centred);
    label->setEditable(false, true);
    label->addListener(this);
    
    // some method should be used to return the name of a track
    String trackLabel = "Track";
    label->setText(trackLabel, NotificationType::sendNotification);
    
    addAndMakeVisible(volumeSlider = new Slider(trackLabel + " v"));
    volumeSlider->setSliderStyle(Slider::SliderStyle::LinearVertical);
    volumeSlider->setRange(0.000001, 1.25, 0.000001);
    volumeSlider->setSkewFactor(0.5f);
    volumeSlider->setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    volumeSlider->setValue(mLevel.peak);
    
    addAndMakeVisible(panPot = new Slider(trackLabel + " p"));
    panPot->setRange(0, 1, 0.00001);
    panPot->setSliderStyle(Slider::RotaryVerticalDrag);
    panPot->setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    panPot->setColour(Slider::rotarySliderFillColourId, Colour(0x7fffff));
    panPot->setColour(Slider::rotarySliderOutlineColourId, Colour(0x8cffff));
    panPot->setValue(0.5f);
    panPot->addListener(this);
    
    addAndMakeVisible(muteButton = new ToggleButton("Mute"));
    muteButton->setColour(TextButton::buttonColourId, Colours::blue);
    muteButton->addListener(this);
    
    addAndMakeVisible(soloButton = new ToggleButton("Solo"));
    soloButton->setColour(TextButton::buttonColourId, Colours::yellow);
    soloButton->addListener(this);
    
}

ChannelStripComponent::~ChannelStripComponent()
{
    deleteAllChildren();
}

void ChannelStripComponent::paint (Graphics& g)
{
    Colour backgroundColour = Colours::transparentBlack;
    
    g.setGradientFill(ColourGradient(backgroundColour.brighter(0.25f), 0, 0, backgroundColour.darker(0.25f), 0, getHeight(), 0));
    
    g.fillAll ();   // clear the background
    
    g.drawLine(0, 0, getWidth(), getHeight());

}

void ChannelStripComponent::resized()
{
    int panSize = 32;
    int volumeWidth = 15;
    int volumeHeight = 127;
    int meterWidth = 6;
    int labelHeight = 14;
    
    int remainingWidth = (getWidth() - volumeWidth) / 2;
    int offsetY = (getHeight() - volumeHeight - panSize - labelHeight);
    int totalHeight = volumeHeight - 7;
    
    int buttonSize = 16;
    int buttonsOffset = (getHeight() - volumeHeight - panSize - labelHeight) - 5;
    
    muteButton->setBounds(0, buttonsOffset - buttonSize * 3, getWidth(), buttonSize);
    soloButton->setBounds(0, buttonsOffset - buttonSize * 2, getWidth(), buttonSize);
    
    panPot->setBounds((getWidth() - panSize) / 2, (getHeight() - volumeHeight - panSize - labelHeight), panSize, panSize);
    
    volumeSlider->setBounds(remainingWidth, (getHeight() - volumeHeight - labelHeight), volumeWidth, volumeHeight);
    
    label->setBounds(0, getHeight() - labelHeight, getWidth(), labelHeight);
    
    meter->setVisible(true);
    meter->setBounds((getWidth() - remainingWidth) + (remainingWidth - meterWidth) / 2, offsetY, meterWidth, totalHeight);
    
}

bool ChannelStripComponent::isInterestedInFileDrag(const StringArray & files)
{
    bool accepted;
    std::list<String> extensions;
    extensions.push_back(".wav");
    extensions.push_back(".flac");

    for (auto currentFile = files.begin(), end = files.end(); currentFile != end; ++currentFile) {
        accepted = false;
        for (auto extension = extensions.begin(), endExtensions = extensions.end(); extension != endExtensions; ++extension) {
            if (currentFile->endsWith(*extension)) {
                accepted = true;
                break;
            }
        }

        if (!accepted) {
            return false;
        }
    }

    return true;
}

void ChannelStripComponent::filesDropped(const StringArray & files, int x, int y)
{
    for (auto current = files.begin(), end = files.end(); current != end; ++current) {
        AudioRegion *region = AudioRegionFactory::build(*current, 0);

        track.add(*region);
    }
}

void ChannelStripComponent::sliderValueChanged(Slider* movedSlider)
{
    if(movedSlider == volumeSlider)
    {
        mLevel.peak = volumeSlider->getValue();
        if(mLevel.peak > 1.0f)
        {
            mLevel.isClipping = true;
        }
        meter->setMeterLevel(mLevel);
        String volume = (String) volumeSlider->getValue();
        label->setText(volume, NotificationType::dontSendNotification);
    }
    else if(movedSlider == panPot)
    {
        // set something
    }
}

void ChannelStripComponent::labelTextChanged(Label* changedLabel)
{
    // change this to something sensible
    //label->setText("This text has been changed", NotificationType::dontSendNotification);
}

void ChannelStripComponent::buttonClicked(Button* clickedButton)
{
    if(clickedButton == muteButton)
    {
        const bool isMuted = clickedButton->getToggleState();
        
        if(isMuted)
        {
            mLevel.peak = 0.0f;
            mLevel.isClipping = false;
            
            meter->setMeterLevel(mLevel);
        }
    }
    else if(clickedButton == soloButton)
    {
        // ask parent to mute everything else somehow
    }
}


