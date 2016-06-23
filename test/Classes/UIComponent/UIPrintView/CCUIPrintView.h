#ifndef _CC_UI_PRINT_VIEW_H_
#define _CC_UI_PRINT_VIEW_H_
#include "cocos2d.h"

USING_NS_CC;

class CCUIPrintLine;

class CCUIPrintView : public CCLayer
{
public:
	static CCUIPrintView * initUIPrintViewWithCCRect(CCRect &rect,std::string strText,float time = 0.15f,float fontsize = 20.0f);
	void run();
	void doFollow();
	virtual void callBackFun(){}
	CCUIPrintView();
	virtual ~CCUIPrintView();
	virtual bool init();
	void loadItems();

private:

	std::vector<string> createLineString(std::string strText);
	void step(ccTime dt);
	void stop();
public:
	enum
	{
		TAG_LAB_TXT = 101,
	};

	CC_SYNTHESIZE(CCRect,_printRect,PrintRect);
	CC_SYNTHESIZE(std::string,_printString,PrintString);
	CC_SYNTHESIZE(float,_fontSize,FontSize);
	CC_SYNTHESIZE(float,_deltaTime,DeltaTime);
	
	int _nLineCount;
	int _nByteCount;
	int _nMaxLineCount;
	int _nVisitWidth;
	const char * _strLineArr[64];
	CCUIPrintLine * _pLinePtr[64];
	std::vector<std::string> _strList;

protected:
private:
};

#endif