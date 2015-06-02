//
//  Transport.h
//  DAW
//
//  Created by Dan on 31/05/2015.
//
//

#ifndef TRANSPORT_H_INCLUDED
#define TRANSPORT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
 This component lives inside our window, and this is where you should put all
 your controls and content.
 */
class Transport  : public Component
{
public:
    
    //==============================================================================
    Transport();
    ~Transport();
    
    void paint (Graphics&);
    void resized();
    
    
private:
    Image image;
    Font *timeFont;
    
    OwnedArray<ImageButton> transportButtons;
    ImageButton *play;
    ImageButton *record;
    ImageButton *stop;
    ImageButton *forward;
    ImageButton *backward;
    ImageButton *toStart;
    ImageButton *toEnd;
    
    Label *timeTicks;
    Label *timeSecs;
    
    void setButtonImage(ImageButton* button);
    void initButtons(OwnedArray<ImageButton> &button);
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Transport)
};


#endif  // TRANSPORT_H_INCLUDED
