/*
  ==============================================================================

    Project.h
    Created: 11 Jul 2015 9:26:48am
    Author:  dtl

  ==============================================================================
*/

#ifndef PROJECT_H_INCLUDED
#define PROJECT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class Project
{
    
public:
    Project();
    ~Project();

	//void createBasicProject(const String& projName, const Array<String>);
	void saveProject();
	void loadProject();
	void setProjectDetails(int elementNumber, const String& projName, const Array<String> projFiles);
    
private:
	OwnedArray<XmlElement> projectElements;
};



#endif  // PROJECT_H_INCLUDED
