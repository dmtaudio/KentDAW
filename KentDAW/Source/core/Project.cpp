/*
  ==============================================================================

    Project.cpp
    Created: 11 Jul 2015 9:26:48am
    Author:  dtl

  ==============================================================================
*/

#include "Project.h"

void Project::createBasicProject(const String& projName)
{
    XmlElement project("PROJECT");
    
    XmlElement* projectSettings = new XmlElement("Settings");
    
    projectSettings->setAttribute("name", projName);
    
    project.addChildElement(projectSettings);
    String xmlDoc = project.createDocument(String::empty);
}