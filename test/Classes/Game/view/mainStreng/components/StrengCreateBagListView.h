/**
 * build streng goods
 */
#ifndef _StrengCreateBagListView_H_
#define _StrengCreateBagListView_H_

#include "BaseType.h"
#include "cocos2d.h"
#include "utils/ScaleUtil.h"
#include "CCUIPartialScrollView.h"
using namespace cocos2d;

#define STRENG_CREATE_W POSX(538)
#define STRENG_CREATE_H POSX(428)

class StrengGoodsVo;
class StrengGoods;

class StrengCreateBagListView : public CCUIPartialScrollView
{
public:
	StrengCreateBagListView(const CCRect& mRect);
	~StrengCreateBagListView();

public:
	static StrengCreateBagListView* strengCreateBagListViewWithCCRect(const CCRect& mRect);

	bool init();
	//LAYER_NODE_FUNC(StrengCreateBagListView);
	void createGood( StrengGoodsVo* strengGoodsVo,int sitNum );
	void removeSkinChild();
	void updateTip( int id );
	StrengGoods* getStrengGoods( int id );
	//CCNode *getNewHandItem(int eqSitNum);

	void setDefaultGoodIndex(int val) { i = val; }

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void visit();

	int pages;
	int i;
private:
	std::map<int, StrengGoods*> _goodsDic;
	int m_iTouchState;

	CCPoint mTouchBeganPoint;
};

#endif
