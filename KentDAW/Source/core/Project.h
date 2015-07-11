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
    void createBasicProject(const String& projName, const Array<String>);
    
private:
};



#endif  // PROJECT_H_INCLUDED
