/*
  ==============================================================================

    AudioMixer2.h
    Created: 1 Aug 2015 10:23:26am
    Author:  dtl

  ==============================================================================
*/

#ifndef AUDIOMIXER2_H_INCLUDED
#define AUDIOMIXER2_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioTrack.h"
#include "AudioSourceProcessor.h"
#include "ChannelStripProcessor.h"

class AudioMixer2
{
public:
    AudioMixer2();
    ~AudioMixer2();
    
    void createDefaultNodes();    
    void addTrack(AudioTrack* track);
    void removeTrack(int trackNumber);
    void remapGraph();
    void resetGraph();
    
    AudioProcessorGraph* getProcessorGraph();
    
    void start();
    void stop();
    
    void setPosition(double position);

private:
    int currentProcessor;
    
    AudioProcessorGraph* processorGraph;
    
    // track stuff
    HashMap<int, AudioTrack*> trackMap;
    HashMap<int, AudioTransportSource*> transportMap;
    HashMap<int, AudioSourceProcessor*> sourceProcessorMap;
    
    // mixer stuff
    HashMap<int, ChannelStripProcessor*> channelStripMap;
    
    enum NodeIDs
    {
        INPUT_NODE_ID = 2001,
        OUTPUT_NODE_ID = 2002
    };
    
    int trackNodeID, mixerNodeID;
};



#endif  // AUDIOMIXER2_H_INCLUDED
