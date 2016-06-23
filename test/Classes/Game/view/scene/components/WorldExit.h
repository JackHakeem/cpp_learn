#ifndef HLQS_WorldExit_H_
#define HLQS_WorldExit_H_
#include "Element.h"
#include "model/scene/vo/ExitVo.h"

class WorldExit: public Element
{
public:
public:
	WorldExit();
	WorldExit(ExitVo& exitVo);
	void setExitVo(ExitVo& exitVo);
	void showRes();
	void showDefaultRes();
	virtual void updateAction(bool repeat = true);
	virtual void layout();
	virtual void setGlow(bool value);
	virtual bool isHit();
	virtual void dispose();
	virtual bool hitTest(CCPoint point);
	void loadCompleteHandler();
	void clickExit(CCObject* pSender);
public:
	ExitVo _exitVo;
	std::string _assetPath;
	std::string _textPath;
	CCSprite* sp;
	BitmapMovieClip* exitMovieClip;
	CCMenu *buttonMenu;
};

#endif