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
	: _region(region),
	_formatManager(formatManager),
	inputSource(file),
	thumbnailCache(5),
	thumbnail(512, formatManager, thumbnailCache)
{
	thumbnail.setSource(&inputSource);
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
	g.setColour(Colours::lightblue);
	Rectangle<int> thumbArea(getLocalBounds());
	thumbnail.drawChannels(g, thumbArea.reduced(2), 0, thumbnail.getTotalLength(), 1.0f);
}

void RegionComponent::resized()
{

}
