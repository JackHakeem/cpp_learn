#ifndef _APPOINT_BLESS_VIEW_H_
#define _APPOINT_BLESS_VIEW_H_
#include "CCLayer.h"
#include "model/appoint/vo/AppointBlessVo.h"

USING_NS_CC;

class AppointBlessView : public CCLayerColor
{
public:
	AppointBlessView();

	void initView();
	void buildList();
	void updateGoodsState(int lev);
	void updateExchangeState(int blessValue);

	virtual void registerWithTouchDispatcher(void);
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void onMenuItemClickListener(CCObject *pSender);
	CCLayer *createItemCell(int id, AppointBlessVo *pData);
};
#endif