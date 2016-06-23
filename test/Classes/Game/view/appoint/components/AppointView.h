#ifndef _APPOINT_VIEW_H_
#define _APPOINT_VIEW_H_
#include "PopContainer.h"
#include "model/appoint/vo/AppointVo.h"

class AppointView : public PopContainer
{
public:
	AppointView();
	~AppointView();

	void initView();
	void initText();
	void initButton();
	void initTrader();
	void initBless();
	void startFlasher();
	void stopFlasher();
	void updateGoldAppoint(int vipLev, int crystalLev);
	void updateBlessInfo(bool isOpen,int blessValue,int total);
	void updateInfo();
	void showTrader();
	void enableGoldBtn(bool enable, std::string tips);
	void onMenuClickListener(CCObject *pObject);

	void openBlessView();
	void closeBlessView();
	void reinit();
	void drawGoods();
	CCSprite *createTraderHeader(int id);
	void setTraderHeaderVisible(bool isVisible, int tag);
	void setTraderHighlight(bool isHighLight, int tag);
	AppointVo *getCurTraderInfo();
	void setCurTraderInfo(AppointVo *pAppointVo);
	AppointVo *_curTraderInfo;
	bool _canGoldAppoint;
	
};
#endif