#ifndef HLQS_LoaderItem_h
#define HLQS_LoaderItem_h

#include "cocos2d.h"
using namespace cocos2d;

class LoaderItem
{
private:
	std::string XML_TYPE;
	std::string JPG_TYPE;
	std::string PNG_TYPE;
	bool _everyLoad;

public:
	int _level;
	std::string _path;

public:
	LoaderItem();
	void reset();
	LoaderItem(std::string path, int level = 0);
	std::string getPath();
	void setPath(std::string);
	int getLevel();
	void setLevel(int level);
	std::string getType();
};

#endif