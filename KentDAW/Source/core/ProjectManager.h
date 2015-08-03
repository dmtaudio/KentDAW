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
#include "AudioRegionFactory.h"
#include "AudioTrackFactory.h"
#include "../ui/ArrangeWindow.h"

class ProjectManager
{
    
public:
    ProjectManager(AudioEngine* audioEngine, ArrangeWindow* arrangeWindow);
    ~ProjectManager();

	//ProjectManager Management
	void saveProject();
	void loadProject();
	void createBasicProject(const String& projName);

	void importAudioFileToProjectManager();
    
private:
	int _trackNumber;
	AudioTrack* track;
	ArrangeWindow* arrangeWindow;
	AudioEngine* _audioEngine;
	ScopedPointer<XmlElement>pElements;
	Array<String> projectFilePathsArray;
	AudioFormatManager formatManager;
};
#endif  // PROJECT_H_INCLUDED