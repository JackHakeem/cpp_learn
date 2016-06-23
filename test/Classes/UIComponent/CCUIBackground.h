#ifndef _CCUIBACKGROUND_H_
#define _CCUIBACKGROUND_H_

#include "cocos2d.h"

USING_NS_CC;
class CCUIBackground: public CCLayer
{
public:
	enum
	{
		CCUIBackground_tl=0,
		CCUIBackground_tr,
		CCUIBackground_bl,
		CCUIBackground_br,
		CCUIBackground_t,
		CCUIBackground_b,
		CCUIBackground_l,
		CCUIBackground_r,
		CCUIBackground_n
	};
	CCUIBackground();
	virtual ~CCUIBackground();
	bool initWithFile(const char* filename, CCPoint pos, CCPoint offset, CCSize size, int alpha = 255);
	bool initWithSpriteFrame(const char* framename, CCPoint pos, CCPoint offset, CCSize size, int alpha = 255);
	void changeSize(CCSize size);
	void setAlpha(int value);
	virtual void setPosition(CCPoint var);
public:
	float widthtinterval;
	float heightinterval;
	float x;
	float y;
	float offsetX;
	float offsetY;
	CCSize srcsize;
	int alpha;
};

#endif