/*
  ==============================================================================

    ChannelStripComponent.h
    Created: 21 Jul 2015 11:43:55am
    Author:  dtl

  ==============================================================================
*/

#ifndef CHANNELSTRIPCOMPONENT_H_INCLUDED
#define CHANNELSTRIPCOMPONENT_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../core/AudioMixer.h"
#include "MeterComponent.h"

//==============================================================================
/*
*/
class ChannelStripComponent    : public Component,
                                 public SliderListener,
                                 public ButtonListener,
                                 public LabelListener
{
public:
    ChannelStripComponent();
    ~ChannelStripComponent();
    
    void sliderValueChanged(Slider* movedSlider);
    void buttonClicked(Button* clickedButton);
    void labelTextChanged(Label* changedLabel);
    
    void paint(Graphics& g);
    void resized();
    
private:
    Label* label;
    Slider* volumeSlider;
    Slider* panPot;
    
    ToggleButton* muteButton;
    ToggleButton* soloButton;
    
    MeterComponent* meter;
    AudioMixer::Level mLevel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelStripComponent)
};


#endif  // CHANNELSTRIPCOMPONENT_H_INCLUDED

