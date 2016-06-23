#ifndef HLQS_FormationLoader_H_
#define HLQS_FormationLoader_H_
#include "cocos2d.h"

USING_NS_CC;

class FormationLoader: public CCLayer
{
public:
	std::string _url;
	CCSprite* _sp;
	int _x;
	int _y;
	int _scaleX;
	int _scaleY;
public:
	FormationLoader();
	void load(std::string& url);
	void strategyA(std::string& url);
	void strategyB(std::string& url);
	void dispose();

	void load(int id);

//Begin Kenfly 20121107 : load async
private:
	void loadCallback(CCObject* object, void* pData);
//End Kenfly
};

#endif