#ifndef _CC_UI_PRINT_LINE_H_
#define _CC_UI_PRINT_LINE_H_
#include "cocos2d.h"

USING_NS_CC;

class CCUIPrintLine : public CCLayerColor
{
public:
	static CCUIPrintLine * initUIPrintLineWithCCRect(CCSize size,std::string strText,float fontsize = 20.0f);
	void visit(CCSize size);
private:
	CCUIPrintLine();
	virtual ~CCUIPrintLine();

	virtual bool init();
	virtual void visit();
	void loadItems();
	void setLineX(float vx);
public:
	CC_SYNTHESIZE(CCSize,_printSize,PrintSize);
	CC_SYNTHESIZE(CCRect,_printRect,PrintRect);
	CC_SYNTHESIZE(CCRect,_visitRect,VisitRect);
	CC_SYNTHESIZE(std::string,_printString,PrintString);
	CC_SYNTHESIZE(float,_fontSize,FontSize);
	CC_SYNTHESIZE(bool,_isLastLine,IsLastLine);

	enum
	{
		TAG_Labtxt =  101,
	};

public:
	float _deltaWidth;

private:
	float _lineX;

protected:
private:
};

#endif