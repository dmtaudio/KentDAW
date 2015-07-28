/*
  ==============================================================================

    AudioRegionFactory.cpp
    Created: 25 Jul 2015 9:58:55pm
    Author:  Thomas

  ==============================================================================
*/

#include "AudioRegionFactory.h"
#include "SampleAudioRegion.h"

AudioRegionFactory::AudioRegionFactory() {
    afm.registerBasicFormats();
}

AudioRegion * AudioRegionFactory::_build(const String &path, int64 position)
{
    File file(path);
    AudioFormatReader *reader = afm.createReaderFor(file);

    if (reader != 0) {
        AudioRegion *region = new SampleAudioRegion(reader, position);

        return region;
    }

    return nullptr;
}
