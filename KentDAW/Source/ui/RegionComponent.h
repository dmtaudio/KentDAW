/*
  ==============================================================================

    RegionComponent.h
    Created: 2 Aug 2015 11:34:48pm
    Author:  Matt

  ==============================================================================
*/

#ifndef REGIONCOMPONENT_H_INCLUDED
#define REGIONCOMPONENT_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../core/AudioRegion.h"

//==============================================================================
/*
*/
class RegionComponent    : public Component
{
public:
    RegionComponent(AudioRegion* region, AudioFormatManager& formatManager, const File& file);
    ~RegionComponent();

	void setFile(const File& file);

    void paint (Graphics&);
    void resized();

private:
	AudioRegion* _region;
	AudioFormatManager& _formatManager;
	FileInputSource inputSource;
	AudioThumbnailCache thumbnailCache;
	AudioThumbnail thumbnail;
    
    inline double pixelsToTime(double pixels);
    inline double timeToPixels(double seconds);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RegionComponent)
};


#endif  // REGIONCOMPONENT_H_INCLUDED
