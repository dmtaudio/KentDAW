/*
  ==============================================================================

    GainProcessor.cpp
    Created: 18 Jul 2015 11:24:01am
    Author:  Matt

  ==============================================================================
*/

#include "ChannelStripProcessor.h"

//==============================================================================
ChannelStripProcessor::ChannelStripProcessor()
{
	gain = 1.0f;
}

ChannelStripProcessor::~ChannelStripProcessor()
{
}

int ChannelStripProcessor::getNumParameters()
{
	return 1;
}

float ChannelStripProcessor::getParameter(int index)
{
	return gain;
}

void ChannelStripProcessor::setParameter(int index, float newValue)
{
	gain = newValue;
}

const String ChannelStripProcessor::getParameterName(int index)
{
	return "Gain";
}

const String ChannelStripProcessor::getParameterText(int index)
{
	return String(gain);
}

const String ChannelStripProcessor::getInputChannelName(int channelIndex) const
{
	return String(channelIndex + 1);
}

const String ChannelStripProcessor::getOutputChannelName(int channelIndex) const
{
	return String(channelIndex + 1);
}

bool ChannelStripProcessor::isInputChannelStereoPair(int index) const
{
	return true;
}

bool ChannelStripProcessor::isOutputChannelStereoPair(int index) const
{
	return true;
}

bool ChannelStripProcessor::acceptsMidi() const
{
	#if JucePlugin_WantsMidiInput
		return true;
	#else
		return false;
	#endif
}

bool ChannelStripProcessor::producesMidi() const
{
	#if JucePlugin_ProducesMidiOutput
		return true;
	#else
		return false;
	#endif
}

bool ChannelStripProcessor::silenceInProducesSilenceOut() const
{
	return false;
}

double ChannelStripProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int ChannelStripProcessor::getNumPrograms()
{
	return 1;
}

int ChannelStripProcessor::getCurrentProgram()
{
	return 0;
}

void ChannelStripProcessor::setCurrentProgram(int index)
{
}

const String ChannelStripProcessor::getProgramName(int index)
{
	return String();
}

void ChannelStripProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void ChannelStripProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{

}

void ChannelStripProcessor::releaseResources()
{

}

void ChannelStripProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	buffer.applyGain(gain);

	for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
		buffer.clear(i, 0, buffer.getNumSamples());
}

void ChannelStripProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void ChannelStripProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

const String ChannelStripProcessor::getName() const
{
	return "Channel Strip";
}

bool ChannelStripProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ChannelStripProcessor::createEditor()
{
	return nullptr;
}