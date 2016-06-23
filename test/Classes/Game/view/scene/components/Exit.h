#ifndef HLQS_Exit_H_
#define HLQS_Exit_H_

#include "Element.h"
#include "model/scene/vo/ExitVo.h"

class Exit: public Element
{
public:
	Exit();
	~Exit();
	Exit(ExitVo& exitVo);
	void setExitVo(ExitVo& exitVo);
	void showRes();
	void showDefaultRes();
	virtual void updateAction(bool repeat = true);
	virtual void layout();
	virtual void setGlow(bool value);
	virtual bool isHit();
	virtual void dispose();
	virtual bool hitTest(CCPoint point);
	void loadCompleteHandler(CCObject* target, void* data); //Kenfly 20121116
	Exit(const Exit&);
	Exit& operator = (const Exit&);

public:
	ExitVo _exitVo;
	std::string _assetPath;
	CCLabelTTF* _nameTxt;
	BitmapMovieClip* exitMovieClip;
};

#endif