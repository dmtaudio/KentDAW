/*
  ==============================================================================

    RegionComponent.cpp
    Created: 2 Aug 2015 11:34:48pm
    Author:  Matt

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "RegionComponent.h"

//==============================================================================
RegionComponent::RegionComponent(AudioRegion* region, AudioFormatManager& formatManager, const File& file) 
	:	_region(region),
		thumbnailCache(5),
		thumbnail(1024, formatManager,thumbnailCache)
{
	thumbnail.setSource(new FileInputSource(file));
    setOpaque(true);
}

RegionComponent::~RegionComponent()
{
	thumbnail.clear();
	thumbnailCache.clear();
}

void RegionComponent::setFile(const File&)
{
}



void RegionComponent::paint (Graphics& g)
{
    g.fillAll(Colours::black);
	g.setColour(Colours::lightgreen);
	Rectangle<int> thumbArea(getLocalBounds());
	thumbnail.drawChannels(g, thumbArea.reduced(2), 0.0f, thumbnail.getTotalLength(), 1.0f);
}

void RegionComponent::resized()
{

}
