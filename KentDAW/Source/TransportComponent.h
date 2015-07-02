/*
  ==============================================================================

    TransportComponent.h
    Created: 1 Jul 2015 12:25:09pm
    Author:  dtl

  ==============================================================================
*/

#ifndef TRANSPORTCOMPONENT_H_INCLUDED
#define TRANSPORTCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class TransportComponent    : public Component,
                              public ApplicationCommandTarget,
                              public Button::Listener
{
public:
    
    class Listener
    {
    public:
        enum TransportEvent
        {
            Play,
            Record,
            Stop,
            Forward,
            Backward,
            toStart,
            toEnd
        };
        
        Listener();
        virtual ~Listener();
        virtual void updateTransportComponent(TransportComponent* transport, TransportEvent event);
    };
    
    TransportComponent();
    ~TransportComponent();
    
    void addListener(TransportComponent::Listener* listener);
    void removeListener(TransportComponent::Listener* listener);
    
    virtual void buttonClicked(Button* button);
    
    // Keyboard shortcut command interface
    virtual void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result);
    virtual void getAllCommands(Array<CommandID>& commands);
    virtual bool perform (const ApplicationCommandTarget::InvocationInfo& info);
    ApplicationCommandTarget* getNextCommandTarget();

    void paint (Graphics&);
    void resized();

private:
    ListenerList<TransportComponent::Listener> listenerList;
    
    Image image;

    OwnedArray<ImageButton> transportButtons;
    ImageButton* playButton;
    ImageButton* recordButton;
    ImageButton* stopButton;
    ImageButton* forwardButton;
    ImageButton* backwardButton;
    ImageButton* toStartButton;
    ImageButton* toEndButton;
    // Add buttons for looping and pausing, the pause button should replace the play button
    // when play is initialised
    
    int buttonWidth, buttonHeight;
    
    float normalImageOpacity = 1.0f;
    float hoveredImageOpacity = 1.0f;
    float pressedImageOpacity = 1.0f;
    
    Colour normalImageColour;
    Colour hoveredImageColour;
    Colour pressedImageColour;
    
    void setButtonImage(ImageButton* button);
    void initButtons(OwnedArray<ImageButton> &buttons);
    
    void setButtonBounds();
    void setButtonColours(Colour normal, Colour hovered, Colour pressed);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransportComponent)
};


#endif  // TRANSPORTCOMPONENT_H_INCLUDED
