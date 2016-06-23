#ifndef _STRENGFIGURECREATE_H_
#define _STRENGFIGURECREATE_H_

#include "BaseType.h"
#include "cocos2d.h"
#include "CCUIPartialScrollView.h"
using namespace cocos2d;

class FigureItem;

class StrengFigureCreate  : public CCUIPartialScrollView
{
public:
	StrengFigureCreate(const CCRect& mRect);
	~StrengFigureCreate();
	bool init();

public:
	static StrengFigureCreate* figureCreatScrollViewWithCCRect(const CCRect& mRect);
	void buildList();
	void itemClickHandler( FigureItem* pItem );
	void delList();

	//virtual void registerWithTouchDispatcher();
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	CCNode *getNewHandItem(int mercId);
	void moveToNextPageClick();
	void moveToPreviousPageClick();
	void onExit();
public:
	vector<FigureItem *> m_figures;
	FigureItem* _item;  // cur item
	int _totalPage;
};

#endif