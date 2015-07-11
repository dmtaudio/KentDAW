/*
  ==============================================================================

    Project.cpp
    Created: 11 Jul 2015 9:26:48am
    Author:  dtl

  ==============================================================================
*/

#include "Project.h"

void Project::createBasicProject(const String& projName, const Array<String> projFiles)
{
    XmlElement project("PROJECT");
    XmlElement* projectSettings = new XmlElement("Settings");
    
    projectSettings->setAttribute("name", projName);
    
    XmlElement files("FILES");
    XmlElement* projectFiles = new XmlElement("Paths");
    
    for(auto file : projFiles)
    {
        int i = 1;
        projectFiles->setAttribute((String)i, file);
        i++;
    }
    
    project.addChildElement(projectSettings);
    String xmlDoc = project.createDocument(String::empty);
}