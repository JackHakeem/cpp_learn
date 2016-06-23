#include "LoaderItem.h"

LoaderItem::LoaderItem()
{
	reset();
}

void LoaderItem::reset()
{
	XML_TYPE = "xml";
	JPG_TYPE = "jpg";
	PNG_TYPE = "png";
	_everyLoad = false;
	_level = 0;
}

LoaderItem::LoaderItem(std::string path, int level)
{
	reset();
	_path = path;
	_level = level;
}

std::string LoaderItem::getPath()
{
	return _path;
}

void LoaderItem::setPath(std::string path)
{
	_path = path;
}
int LoaderItem::getLevel()
{
	return _level;
}

void LoaderItem::setLevel(int level)
{
	_level = level;
}

std::string LoaderItem::getType()
{
	int i = _path.length();
	if(_path.substr(-3 - i, 3) == XML_TYPE)
		return XML_TYPE;
	else if(_path.substr(-3 - i, 3) == JPG_TYPE)
		return JPG_TYPE;
	else if(_path.substr(-3 - i, 3) == PNG_TYPE)
		return PNG_TYPE;
	
		return NULL;
}