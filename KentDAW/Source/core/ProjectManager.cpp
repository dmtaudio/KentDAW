/*
  ==============================================================================

    ProjectManager.cpp
    Created: 11 Jul 2015 9:26:48am
    Author:  Dtl + Matt

  ==============================================================================
*/

#include "ProjectManager.h"

ProjectManager::ProjectManager(AudioEngine *audioEngine, ArrangeWindow* arrangeWindow) : arrangeWindow(arrangeWindow),
    audioEngine(audioEngine),
	projectFilePathsArray()
{
	pElements = new XmlElement("Project_Elements");
	formatManager.registerBasicFormats();
	createBasicProject("Untitled Project");
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
		//stringFile = stringFile + ".mor";
		//savedFile = stringFile;

		bool overwrite = true;

		if (savedFile.existsAsFile())
		{
			overwrite = AlertWindow::showOkCancelBox(AlertWindow::WarningIcon, "A project by this name already exists!", "Would you like to overwrite this project file?");
		}

		if (overwrite == true)
		{
			savedFile.deleteFile();
			savedFile.create();
			
			//Create XML
			String xmlDoc = pElements->createDocument(String::empty, false);
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
		pElements = loadedXml->getChildByName("Project_Elements");
		loadedXml->removeChildElement(pElements, false);
	}
}

void ProjectManager::createBasicProject(const String &projName)
{
	pElements->deleteAllChildElements();

	//Add Settings as a child element to project
	XmlElement* projectSettings = new XmlElement("Settings");
	projectSettings->setAttribute("Project_Name", projName);
	pElements->addChildElement(projectSettings);

	//Add file paths and add projectFiles as a child element to project
	XmlElement* projectFilePathsXML = new XmlElement("File_Paths");
	int i = 1;
	for (auto file : projectFilePathsArray)
	{
		projectFilePathsXML->setAttribute((String)i, file);
		i++;
	}
	pElements->addChildElement(projectFilePathsXML);
}

void ProjectManager::importAudioFileToProjectManager()
{
	FileChooser chooser("Select a Wave file to play...",
		File::nonexistent,
		"*.wav");
	if (chooser.browseForFileToOpen()) {
		File audioFile(chooser.getResult());
		String filePath(audioFile.getFullPathName());
		projectFilePathsArray.add(filePath);
		AudioTrack *track = AudioTrackFactory::build();
		audioEngine->getMixer()->addTrack(track);
		AudioRegion *region = AudioRegionFactory::build(filePath, 0);
		track->add(*region);
		arrangeWindow->createGuiForTrack(track);
		arrangeWindow->AddRegionToTrackGUI(audioFile, 1);
	}
}