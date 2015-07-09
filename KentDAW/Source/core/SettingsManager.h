/*
  ==============================================================================

    SettingsManager.h
    Created: 7 Jul 2015 3:33:55pm
    Author:  Matt

  ==============================================================================
*/

#ifndef SETTINGSMANAGER_H_INCLUDED
#define SETTINGSMANAGER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class SettingsManager : public AudioDeviceSelectorComponent
{
public:
	SettingsManager(AudioDeviceManager &deviceManager,
		int minAudioInputChannels, 
		int maxAudioInputChannels, 
		int minAudioOutputChannels, 
		int maxAudioOutputChannels, 
		bool showMidiInputOptions, 
		bool showMidiOutputSelector, 
		bool showChannelsAsStereoPairs, 
		bool hideAdvancedOptionsWithButton);
	~SettingsManager();

private:

};

#endif  // SETTINGSMANAGER_H_INCLUDED
