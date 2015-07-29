/*
  ==============================================================================

    ArrangeWindow.h
    Created: 1 Jul 2015 2:44:20pm
    Author:  Matt

  ==============================================================================
*/

#ifndef ARRANGEWINDOW_H_INCLUDED
#define ARRANGEWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "ChannelStripComponent.h"
#include "../core/AudioTrack.h"
#include "../core/AudioEngine.h"
#include <list>

//==============================================================================
/*
*/
class ArrangeWindow    : public Viewport,
    Button::Listener
{
public:
    ArrangeWindow(AudioEngine *audioEngine);
    ~ArrangeWindow();

    void paint (Graphics&);
    void resized();
    void createGuiForTrack(AudioTrack *track);

private:
    TextButton *btn;
    AudioEngine *audioEngine;
    std::list<ChannelStripComponent *> channelStrips;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArrangeWindow)

        // Inherited via Listener
        virtual void buttonClicked(Button *) override;
};


#endif  // ARRANGEWINDOW_H_INCLUDED
