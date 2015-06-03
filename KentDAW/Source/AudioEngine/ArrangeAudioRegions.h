/* 
 * File:   ArrangeAudioRegions.h
 * Author: Dan
 *
 * Created on 02 June 2015, 20:52
 */

#ifndef ARRANGEAUDIOREGIONS_H
#define	ARRANGEAUDIOREGIONS_H

struct AudioRegion
{
    int regionID;
    int startPosition;
    int endPosition;
    int timelineStartPosition;
    
    PositionableAudioSource *regionAudioSource;
};

class ArrangeAudioRegions : public PositionableAudioSource {
public:
    ArrangeAudioRegions();
    ArrangeAudioRegions(const ArrangeAudioRegions& orig);
    virtual ~ArrangeAudioRegions();
    
    bool addRegion(const int &regionID, const int &startPosition, const int &endPosition, const int &timelineStartPosition, const double &deviceSampleRate);
    bool modifyRegion(const int &regionID, const int &newStartPosition, const int &newEndPosition, const int &newTimelineStartPosition);
    void removeRegion(const int regionID);
    void removeAllRegions();
    
    bool enableBuffering(bool enable);
    bool bufferingState();
    
    void prepareToPlay(int samplesPerBlock, double sampleRate);
    void prepareRegionsToPlay();
    
    void releaseResources();
    void getNextAudioBlock(const AudioSourceChannelInfo& info);
    
    void setNextReadPosition (int32 newPosition);
    
    int32 getNextReadPosition() const;
	
    int32 getTotalLength() const;
    
    bool isLooping() const;
private:

};

#endif	/* ARRANGEAUDIOREGIONS_H */

