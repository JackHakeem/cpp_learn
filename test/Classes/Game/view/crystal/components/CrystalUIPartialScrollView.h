#ifndef _CRYSTALUIPARTIALSCROLLVIEW_H_
#define _CRYSTALUIPARTIALSCROLLVIEW_H_

#include "CCUIPartialScrollView.h"
#include "../CrystalMediator.h"
USING_NS_CC;

class CrystalUIPartialScrollView : public CCUIPartialScrollView
{
public:
//	CrystalUIPartialScrollView();
	virtual ~CrystalUIPartialScrollView();
public:

 	virtual void registerWithTouchDispatcher(void);
 	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	int getTouchPosIndex( CCPoint point );
	CrystalUIPartialScrollView(const CCRect & ccRect);
	static CrystalUIPartialScrollView * crystalScrollViewWithCCRect(const CCRect & ccRect);
	void addHightLightFocusImage(int index);

public:
	CrystalMediator * _crystalMediator;
	int _nPosIndex;
	CrystalProxy *_crystalProxy;

	int _nPreFocusPos;
};

extern CrystalUIPartialScrollView * g_pCrystalScrollView;

#endif