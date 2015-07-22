/*
  ==============================================================================

    ProjectManager.cpp
    Created: 11 Jul 2015 9:26:48am
    Author:  Dtl + Matt

  ==============================================================================
*/

#include "ProjectManager.h"

ProjectManager::ProjectManager() : projFilePaths()
{
	for (int i = 0; i < projectElements.size(); i++)
	{
		projectElements.add(new XmlElement(String(i)));
	}
}

ProjectManager::~ProjectManager()
{
}

/*
void ProjectManager::createBasicProjectManager(const String& projName, const Array<String> projFiles)
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
*/

void ProjectManager::saveProject()
{
	FileChooser locationChooser("Save your project...", File::getSpecialLocation
		(File::userHomeDirectory), "*.mor");

	if (locationChooser.browseForFileToSave(false))
	{
		File savedFile(locationChooser.getResult());
		String stringFile = savedFile.getFullPathName();
		stringFile = stringFile + ".mor";
		savedFile = stringFile;

		bool overwrite = true;

		if (savedFile.existsAsFile())
		{
			overwrite = AlertWindow::showOkCancelBox(AlertWindow::WarningIcon, "A project by this name already exists!", "Would you like to overwrite this project file?");
		}

		if (overwrite == true)
		{
			savedFile.deleteFile();
			savedFile.create();

			XmlElement *project = new XmlElement("SAVED_PROJECT");
			
			for (int i = 0; i < 2; i++)
			{
				project->addChildElement(projectElements[i]);
			}

			//Create XML
			String xmlDoc = project->createDocument(String::empty, false);
			//Append to savefile
			savedFile.appendText(xmlDoc);
		}
	}
}

void ProjectManager::loadProject()
{
	FileChooser loadFileChooser("Select a .mor file to load...",
		File::getSpecialLocation(File::userHomeDirectory), "*.mor");

	if (loadFileChooser.browseForFileToOpen())
	{
		File loadedFile(loadFileChooser.getResult());
		ScopedPointer<XmlElement> loadedXml = XmlDocument::parse(loadedFile);

		for (int i = 0; i < projectElements.size(); i++)
		{
			XmlElement* childToInsert = loadedXml->getChildByName(String(i));
			projectElements.insert(i, childToInsert);
			loadedXml->removeChildElement(childToInsert, false);
		}
	}
}

void ProjectManager::setProjectManagerDetails(int elementNumber, const String &projName)
{
	projectElements[elementNumber]->deleteAllChildElements();

	//Add Settings as a child element to project
	XmlElement* projectSettings = new XmlElement("Settings");
	projectSettings->setAttribute("ProjectManagerName", projName);
	projectElements[elementNumber]->addChildElement(projectSettings);

	//Add file paths and add projectFiles as a child element to project
	XmlElement* projectFiles = new XmlElement("Paths");
	for (auto file : projFilePaths)
	{
		int i = 1;
		projectFiles->setAttribute((String)i, file);
		i++;
	}
	projectElements[elementNumber]->addChildElement(projectFiles);
}

void ProjectManager::importAudioFileToProjectManager()
{
	FileChooser chooser("Select a Wave file to play...",
		File::nonexistent,
		"*.wav");
	if (chooser.browseForFileToOpen()) {
		File audioFile(chooser.getResult());
		String filePath(audioFile.getFullPathName());
		projFilePaths.add(filePath);
	}
}