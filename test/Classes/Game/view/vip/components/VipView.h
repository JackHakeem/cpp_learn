#ifndef _VIP_VIEW_H_
#define _VIP_VIEW_H_
#include "PopContainer.h"
#include "VipScrollView.h"
#include "events/GameDispatcher.h"

class VipView : public PopContainer, VipScrollViewListener
{
public:
	VipView();
	~VipView();

	void openVipView();
	virtual bool init();
	void initPlayerInfo();
	void initView();
	void resetVipLev();
	void onPurchaseItemClickListener(CCObject *pSender);
	void onPrePageItemClickListener(CCObject *pSender);
	void onNextPageItemClickListener(CCObject *pSender);
	VipScrollView *_pScrollView;
	void updatePlayerInfo();
	virtual void removeDataObjectChild();
private:
	CCLayer *buildInfomationView();

	virtual void onScrollListener( int pageId );
	void updateVipGiftInfo( int vipId );

	GameDispatcher *_dispatcher;
    int _buyGold;
	//int _barScall;
	/*int _gold;
	int _nextGold;
	int _lev;
	int _gap;*/

	//char *_pRate;
};
#endif