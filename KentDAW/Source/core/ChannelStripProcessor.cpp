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
	panning = 0.5f;
	muteGain = 0.0f;
	muted = false;
}

ChannelStripProcessor::~ChannelStripProcessor()
{
}

int ChannelStripProcessor::getNumParameters()
{
	return 3;
}

float ChannelStripProcessor::getParameter(int index)
{
	if (index == 1)
	{
		return gain;
	}
	else if (index == 2)
	{
		return panning;
	}
	else if (index == 3)
	{
		return muteGain;
	}
}

void ChannelStripProcessor::setParameter(int index, float newValue)
{
	if (index == 1)
	{
		gain = newValue;
	}
	else if (index == 2)
	{
		panning = newValue;
	}
}

void ChannelStripProcessor::setMuteParameter()
{
	if (muted)
	{
		muted == false;
	}
	else
	{
		muted == true;
	}
}

const String ChannelStripProcessor::getParameterName(int index)
{
	if (index == 1)
	{
		return "Gain";
	}
	else if (index == 2)
	{
		return "Panning";
	}
	else if (index == 3)
	{
		return "Mute";
	}
}

const String ChannelStripProcessor::getParameterText(int index)
{
	if (index == 1)
	{
		return String(gain);
	}
	else if (index == 2)
	{
		return String(panning);
	}
	else if (index == 3)
	{
		return String(muted);
	}
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
	if (!muted)
	{
		if (panning == 0.5)
		{
			buffer.applyGain(gain);
		}
		else if (panning < 0.5)
		{
			buffer.applyGain(0, 0, buffer.getNumSamples(), gain);
			buffer.applyGain(1, 0, buffer.getNumSamples(), gain / panning);
		}
		else if (panning > 0.5)
		{
			buffer.applyGain(0, 0, buffer.getNumSamples(), gain / (panning - 0.5));
			buffer.applyGain(1, 0, buffer.getNumSamples(), gain);
		}
	}
	else if (muted)
	{
		buffer.applyGain(0.0);
	}

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