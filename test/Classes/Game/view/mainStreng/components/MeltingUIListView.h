#ifndef _MeltingUIListView_H_
#define _MeltingUIListView_H_
#include "UIListView/CCUIListView.h"
#include "MeltingBagGoods.h"


class MeltingUIListView : public CCUIListView
{
public:
	MeltingUIListView();
	static MeltingUIListView* listViewWithCCRect(const CCRect& mRect, bool isHorizontal);
	virtual void onItemClick( int position );

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void update( ccTime dt );

public:
	float m_fStep;
	int m_state;
	bool m_bDraded;
	MeltingBagGoods* m_pClickGood;
	CCTouch *m_pTouch;
	CCEvent *m_pEvent;
	float m_fYMove;
	CCPoint preTouchPoint;
};


#endif
