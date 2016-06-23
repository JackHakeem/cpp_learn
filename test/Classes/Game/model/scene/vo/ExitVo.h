#ifndef HLQS_ExitVo_H_
#define HLQS_ExitVo_H_
#include "cocos2d.h"

USING_NS_CC;

class ExitVo: public CCNode
{
public:
	int _id;
	std::string _name;
	std::string _resId;
	int x;
	int y;
	int _mapId;
	bool isPid;
	bool isOpend;
	bool isCity;
	bool isDuplicate;
	std::vector<int> otherInfos; //Jump to other map Numbers, at present only a, 0 if the map of the world
public:
	ExitVo()
	{
		x = 0;;
		y = 0;
		_mapId = 0;
		isPid = false;
		isOpend = false;
		isCity = false;
		isDuplicate = false;
	}

	int id()
	{
		return _id;
	}
	void id(int value)
	{
		_id = value;
	}

	std::string name()
	{
		return _name;
	}
	void name(std::string value)
	{
		_name = value;
	}

	std::string resId()
	{
		return _resId;
	}

	void resId(std::string value)
	{
		_resId = value;
	}

	int mapId()
	{
		return _mapId;
	}

	void mapId(int id)
	{
		_mapId = id;
	}

	void otherInfo(int info)
	{
		otherInfos.push_back(info);
	}
};

#endif