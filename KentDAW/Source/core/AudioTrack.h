/*
  ==============================================================================

    Track.h
    Created: 7 Jul 2015 3:21:38pm
    Author:  Matt

  ==============================================================================
*/

#ifndef TRACK_H_INCLUDED
#define TRACK_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class Track : public AudioSource
{
public:
    
     // types of track
    enum TrackType { None = 0, Audio, Midi };
     // track controls
    enum ControlType { Record, Mute, Solo };
     // constructor
    Track();
     // destructor
    ~Track();
     // clear the track
     void clear();
     // open track
     void open();
     // close track
     void close();
     // set track type
     void setTrackType(TrackType type);
     // get track type
     TrackType getTrackType() const;
     // set track name
     void setTrackName(String name);
     // get track name
     String getTrackName();
     
    
    void prepareToPlay(int expectedSamplePerBlock, double sampleRate);
    void releaseResources();
    void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill);
     
private:
     OwnedArray<AudioSampleBuffer>& clips;
};

#endif  // TRACK_H_INCLUDED
