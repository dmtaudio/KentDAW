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
		thumbnail(512, formatManager,thumbnailCache)
{
	thumbnail.setSource(new FileInputSource(file));
}

RegionComponent::~RegionComponent()
{
}

void RegionComponent::setFile(const File & file)
{
}



void RegionComponent::paint (Graphics& g)
{
	g.fillAll(Colours::darkgrey);
	g.setColour(Colours::lightblue);
	Rectangle<int> thumbArea(getLocalBounds());
	thumbnail.drawChannels(g, thumbArea.reduced(2), _region->getStartTime(), _region->getEndTime(), 1.0f);
}

void RegionComponent::resized()
{

}
