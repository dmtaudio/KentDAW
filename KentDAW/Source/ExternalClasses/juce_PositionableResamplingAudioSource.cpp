/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-6 by Raw Material Software ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   JUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with JUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

  ------------------------------------------------------------------------------

   If you'd like to release a closed-source product which uses JUCE, commercial
   licenses are also available: visit www.rawmaterialsoftware.com/juce for
   more information.

  ==============================================================================
*/

#include "../../../juce_core/basics/juce_StandardHeader.h"

BEGIN_JUCE_NAMESPACE

#include "juce_PositionableResamplingAudioSource.h"


//==============================================================================
PositionableResamplingAudioSource::PositionableResamplingAudioSource (PositionableAudioSource* const inputSource,
                                                                      const bool deleteInputWhenDeleted_)
    : input (inputSource),
      deleteInputWhenDeleted (deleteInputWhenDeleted_),
      ratio (1.0),
      lastRatio (1.0),
      buffer (2, 0),
      sampsInBuffer (0),
      nextPlayPos (0),
      looping (false)
{
    jassert (input != 0);
}

PositionableResamplingAudioSource::~PositionableResamplingAudioSource()
{
    if (deleteInputWhenDeleted)
        delete input;
}

//==============================================================================
void PositionableResamplingAudioSource::setResamplingRatio (const double samplesInPerOutputSample)
{
    jassert (samplesInPerOutputSample > 0);

    ratio = jmax (0.0, samplesInPerOutputSample);
}

//==============================================================================
void PositionableResamplingAudioSource::setLooping (const bool shouldLoop) throw()
{
    looping = shouldLoop;
}

bool PositionableResamplingAudioSource::isLooping() const
{
    return input ? input->isLooping () : looping;
}

//==============================================================================
void PositionableResamplingAudioSource::setNextReadPosition (int newPosition)
{
    nextPlayPos = (int) (newPosition / ratio);

    input->setNextReadPosition (newPosition);
}

int PositionableResamplingAudioSource::getNextReadPosition() const
{
    return (looping) ? (nextPlayPos % (int) (input->getTotalLength () / ratio))
                     : nextPlayPos;
}

int PositionableResamplingAudioSource::getTotalLength() const
{
    return (int) (input->getTotalLength () / ratio);
}


//==============================================================================
void PositionableResamplingAudioSource::prepareToPlay (int samplesPerBlockExpected,
                                                       double sampleRate)
{
    input->prepareToPlay (samplesPerBlockExpected, sampleRate);

    buffer.setSize (2, roundDoubleToInt (samplesPerBlockExpected * ratio) + 32);
    buffer.clear();
    sampsInBuffer = 0;
    bufferPos = 0;
    subSampleOffset = 0.0;

    createLowPass (ratio);
    resetFilters();
}

void PositionableResamplingAudioSource::releaseResources()
{
    input->releaseResources();
    buffer.setSize (2, 0);
}

void PositionableResamplingAudioSource::getNextAudioBlock (const AudioSourceChannelInfo& info)
{
    if (lastRatio != ratio)
    {
        createLowPass (ratio);
        lastRatio = ratio;
    }

    const int sampsNeeded = roundDoubleToInt (info.numSamples * ratio) + 2;

    int bufferSize = buffer.getNumSamples();

    if (bufferSize < sampsNeeded + 8)
    {
        bufferPos %= bufferSize;
        bufferSize = sampsNeeded + 32;
        buffer.setSize (buffer.getNumChannels(), bufferSize, true, true);
    }

    bufferPos %= bufferSize;

    int endOfBufferPos = bufferPos + sampsInBuffer;

    while (sampsNeeded > sampsInBuffer)
    {
        endOfBufferPos %= bufferSize;

        int numToDo = jmin (sampsNeeded - sampsInBuffer,
                            bufferSize - endOfBufferPos);

        AudioSourceChannelInfo readInfo;
        readInfo.buffer = &buffer;
        readInfo.numSamples = numToDo;
        readInfo.startSample = endOfBufferPos;

        input->getNextAudioBlock (readInfo);

        if (ratio > 1.0)
        {
            // for down-sampling, pre-apply the filter..

            for (int i = jmin (2, info.buffer->getNumChannels()); --i >= 0;)
                applyFilter (buffer.getSampleData (i, endOfBufferPos), numToDo, filterStates[i]);
        }

        sampsInBuffer += numToDo;
        endOfBufferPos += numToDo;
    }

    float* dl = info.buffer->getSampleData (0, info.startSample);
    float* dr = (info.buffer->getNumChannels() > 1) ? info.buffer->getSampleData (1, info.startSample) : 0;

    const float* const bl = buffer.getSampleData (0, 0);
    const float* const br = buffer.getSampleData (1, 0);

    int nextPos = (bufferPos + 1) % bufferSize;

    for (int m = info.numSamples; --m >= 0;)
    {
        const float alpha = (float) subSampleOffset;
        const float invAlpha = 1.0f - alpha;

        *dl++ = bl [bufferPos] * invAlpha + bl [nextPos] * alpha;

        if (dr != 0)
            *dr++ = br [bufferPos] * invAlpha + br [nextPos] * alpha;

        subSampleOffset += ratio;

        jassert (sampsInBuffer > 0);

        while (subSampleOffset >= 1.0)
        {
            if (++bufferPos >= bufferSize)
                bufferPos = 0;

            --sampsInBuffer;

            nextPos = (bufferPos + 1) % bufferSize;
            subSampleOffset -= 1.0;
        }
    }

    if (ratio < 1.0)
    {
        // for up-sampling, apply the filter after transposing..

        for (int i = jmin (2, info.buffer->getNumChannels()); --i >= 0;)
            applyFilter (info.buffer->getSampleData (i, info.startSample), info.numSamples, filterStates[i]);
    }

    jassert (sampsInBuffer >= 0);
}

//==============================================================================
void PositionableResamplingAudioSource::createLowPass (const double ratio)
{
    const double proportionalRate = (ratio > 1.0) ? 0.5 / ratio
                                                  : 0.5 * ratio;

    const double n = 1.0 / tan (double_Pi * jmax (0.001, proportionalRate));
    const double nSquared = n * n;
    const double c1 = 1.0 / (1.0 + sqrt (2.0) * n + nSquared);

    setFilterCoefficients (c1,
                           c1 * 2.0f,
                           c1,
                           1.0,
                           c1 * 2.0 * (1.0 - nSquared),
                           c1 * (1.0 - sqrt (2.0) * n + nSquared));
}

void PositionableResamplingAudioSource::setFilterCoefficients (double c1, double c2, double c3, double c4, double c5, double c6)
{
    const double a = 1.0 / c4;

    c1 *= a;
    c2 *= a;
    c3 *= a;
    c5 *= a;
    c6 *= a;

    coefficients[0] = c1;
    coefficients[1] = c2;
    coefficients[2] = c3;
    coefficients[3] = c4;
    coefficients[4] = c5;
    coefficients[5] = c6;
}

void PositionableResamplingAudioSource::resetFilters()
{
    zeromem (filterStates, sizeof (filterStates));
}

void PositionableResamplingAudioSource::applyFilter (float* samples, int num, FilterState& fs)
{
    while (--num >= 0)
    {
        const double in = *samples;

        double out = coefficients[0] * in
                     + coefficients[1] * fs.x1
                     + coefficients[2] * fs.x2
                     - coefficients[4] * fs.y1
                     - coefficients[5] * fs.y2;

#ifdef JUCE_INTEL
        if (! (out < -1.0e-8 || out > 1.0e-8))
            out = 0;
#endif

        fs.x2 = fs.x1;
        fs.x1 = in;
        fs.y2 = fs.y1;
        fs.y1 = out;

        *samples++ = (float) out;
    }
}

END_JUCE_NAMESPACE
