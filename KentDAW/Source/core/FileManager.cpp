/*
  ==============================================================================

    FileManager.cpp
    Created: 8 Jul 2015 8:31:52pm
    Author:  Matt

  ==============================================================================
*/

#include "FileManager.h"

FileManager::FileManager()
{
	formatManager.registerBasicFormats();
}

FileManager::~FileManager()
{
}

FileManager& FileManager::getInstance()
{
	static FileManager instance;

	return instance;
}

bool FileManager::canHandleFile(String path)
{
	return formatManager.findFormatForFileExtension(File(path).getFileExtension()) != nullptr;
}

