/*
  ==============================================================================

    ProjectManager.h
    Created: 11 Jul 2015 9:26:48am
    Author:  Matt + Dtl

  ==============================================================================
*/

#ifndef PROJECT_H_INCLUDED
#define PROJECT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioTrack.h"
#include "AudioEngine.h"

class ProjectManager
{
    
public:
    ProjectManager(AudioEngine* audioEngine);
    ~ProjectManager();

	//ProjectManager Management
	void saveProject();
	void loadProject();
	void createBasicProject(const String& projName);

	void importAudioFileToProjectManager();
    
private:
	AudioTrack* track;
	AudioEngine* audioEngine;
	ScopedPointer<XmlElement>pElements;
	Array<String> projectFilePathsArray;
	AudioFormatManager formatManager;
};
#endif  // PROJECT_H_INCLUDED