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

class ProjectManager
{
    
public:
    ProjectManager();
    ~ProjectManager();

	//ProjectManager Management
	void saveProject();
	void loadProject();
	void createBasicProject(const String& projName);

	void importAudioFileToProjectManager();
    
private:
	ScopedPointer<XmlElement>pElements;
	OwnedArray<XmlElement> projectElements;
	Array<String> projFilePaths;
	AudioFormatManager formatManager;
};



#endif  // PROJECT_H_INCLUDED
