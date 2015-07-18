/*
  ==============================================================================

    GainProcessor.cpp
    Created: 18 Jul 2015 11:24:01am
    Author:  Matt

  ==============================================================================
*/

#include "GainProcessor.h"

//==============================================================================
GainProcessor::GainProcessor()
{
	gain = 1.0f;
}

GainProcessor::~GainProcessor()
{
}

int GainProcessor::getNumParameters()
{
	return 1;
}

float GainProcessor::getParameter(int index)
{
	return gain;
}

void GainProcessor::setParameter(int index, float newValue)
{
	gain = newValue;
}

const String GainProcessor::getParameterName(int index)
{
	return "Gain";
}

const String GainProcessor::getParameterText(int index)
{
	return String(gain);
}

const String GainProcessor::getInputChannelName(int channelIndex) const
{
	return String(channelIndex + 1);
}

const String GainProcessor::getOutputChannelName(int channelIndex) const
{
	return String(channelIndex + 1);
}

bool GainProcessor::isInputChannelStereoPair(int index) const
{
	return true;
}

bool GainProcessor::isOutputChannelStereoPair(int index) const
{
	return true;
}

bool GainProcessor::acceptsMidi() const
{
	#if JucePlugin_WantsMidiInput
		return true;
	#else
		return false;
	#endif
}

bool GainProcessor::producesMidi() const
{
	#if JucePlugin_ProducesMidiOutput
		return true;
	#else
		return false;
	#endif
}

bool GainProcessor::silenceInProducesSilenceOut() const
{
	return false;
}

double GainProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int GainProcessor::getNumPrograms()
{
	return 1;
}

int GainProcessor::getCurrentProgram()
{
	return 0;
}

void GainProcessor::setCurrentProgram(int index)
{
}

const String GainProcessor::getProgramName(int index)
{
	return String();
}

void GainProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void GainProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{

}

void GainProcessor::releaseResources()
{

}

void GainProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	buffer.applyGain(gain);

	for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
		buffer.clear(i, 0, buffer.getNumSamples());
}

void GainProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void GainProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}