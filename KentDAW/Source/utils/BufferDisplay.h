/*
  ==============================================================================

    BufferDisplay.h
    Created: 7 Jul 2015 8:26:17pm
    Author:  dtl

  ==============================================================================
*/

#ifndef BUFFERDISPLAY_H_INCLUDED
#define BUFFERDISPLAY_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"

class BufferDisplay
{
public:
    BufferDisplay(AudioSampleBuffer* source, const float resampleRatio)
    : sample(source),
      ratio(resampleRatio)
    {}
    
    void createBufferDisplay(Graphics& g, const int x, const int y, const int width, const int height, const int channel = 0)
    {
        jassert(sample);
        
        const float halfHeight = (float) height * 0.5;
        
        float* sampleBuffer = sample->getSampleData(channel);
        const int numSamples = roundFloatToInt(sample->getNumSamples());
        
        for(int i = 0; i < width; ++i)
        {
            const int currentSample = (int) ((numSamples * i) / (float) width);
            const int nextSample = (int) ((numSamples * (i + 1) / (float) width));
        
            // find the absolute value of sampleBuffer at currentSample - the level of the audio signal
            float level = fabsf(sampleBuffer[currentSample]);
            
            for(int j = nextSample + 1; j < jmin(nextSample, numSamples - 1); ++j)
            {
                level = (level + fabsf(sampleBuffer[j])) * 0.5f;
            }
            
            if(level > 0.01f)
            {
                g.drawLine((float) x + i, (halfHeight + y) - (halfHeight + y) * level, (float) x + i, (halfHeight + y) - (halfHeight + y) * level);
                g.drawLine((float) x + i, (halfHeight + y) - (halfHeight + y) * level, (float) x + i, (halfHeight + y) - (halfHeight + y) * level, 0.8f);
            }
        }
    }
    
private:
    AudioSampleBuffer* sample;
    float ratio;
};



#endif  // BUFFERDISPLAY_H_INCLUDED
