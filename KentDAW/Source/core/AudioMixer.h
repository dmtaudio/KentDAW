/*
  ==============================================================================

    AudioMixer.h
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

class AudioMixer
{
public:
    AudioMixer();
    ~AudioMixer();
    
    void createDefaultNodes();    
    void addTrack(AudioTrack* track);
    void removeTrack(int trackNumber);
    void remapGraph();
    void resetGraph();
    int getPosition();
    
    AudioProcessorGraph* getProcessorGraph();
    
    void start();
    void stop();
    
    void setPosition(int position);
    
    struct Level
    {
        float peak;
        bool isClipping;
    };

private:
    int currentProcessor;
    
    int _position;
    
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
    
    TimeSliceThread* readAheadThread;
};



#endif  // AUDIOMIXER2_H_INCLUDED
