/*
  ==============================================================================

    FileManager.h
    Created: 8 Jul 2015 8:31:52pm
    Author:  Matt

  ==============================================================================
*/

#ifndef FILEMANAGER_H_INCLUDED
#define FILEMANAGER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class FileManager
{
public:
	static FileManager& getInstance();

	bool canHandleFile(String path);

protected:
	FileManager();
	~FileManager();

private:
	AudioFormatManager formatManager;
};

#endif  // FILEMANAGER_H_INCLUDED
