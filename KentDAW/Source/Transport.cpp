//
//  Transport.cpp
//  DAW
//
//  Created by Dan on 31/05/2015.
//
//

#include "Transport.h"

//==============================================================================
Transport::Transport()
{
    play = new ImageButton("Play");
    play->s
    addAndMakeVisible(*play);
    stop = new ImageButton("Stop");
    addAndMakeVisible(*stop);
    record = new TextButton("Record");
    addAndMakeVisible(*record);
    forward = new TextButton("Forward");
    addAndMakeVisible(*forward);
    backward = new TextButton("Backward");
    addAndMakeVisible(*backward);
    toEnd = new TextButton("End");
    addAndMakeVisible(*toEnd);
    toStart = new TextButton("Start");
    
}

Transport::~Transport()
{
    deleteAllChildren();
}

void Transport::paint (Graphics& g)
{
    g.fillAll (Colour (0xFFFFFF));
    
    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
}

void Transport::resized()
{
    play->setBounds(0, 0, 50, 20);
    stop->setBounds(40, 0, 50, 20);
}
