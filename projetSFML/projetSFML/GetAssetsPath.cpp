//#define BUILD
#include <SFML/Graphics.hpp>
#include "windows.h"
#include "AssetsPath.h"


std::string getAppPath() {
	char cExeFilePath[256];
	GetModuleFileNameA(NULL, cExeFilePath, 256);
	std::string exeFilePath = cExeFilePath;
	int exeNamePos = exeFilePath.find_last_of("\\/");
	std::string appPath = exeFilePath.substr(0, exeNamePos + 1);
	return appPath;
}

std::string getAssetPath() {
	return getAppPath() + "Assets\\";
}

std::string getWorkingDir()
{
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}

std::string getRelativePath()
{
#ifdef BUILD
	return getAppPath();
#endif // BUILD
#ifndef BUILD
	return getWorkingDir();
#endif // !BUILD
}