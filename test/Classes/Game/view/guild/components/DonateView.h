#pragma once

#include "BaseType.h"
class TextFieldTTF;
class DonateView:public LayerNode
{
public:
	enum
	{
		Z_money,
		Z_btnCut,
		Z_btnAdd,
		Z_btnMax,
		Z_limit,
		Z_btnOK,
		Z_btnCancel,
	};
	enum
	{
		TAG_money,		
		TAG_btnCut,
		TAG_btnAdd,
		TAG_btnMax,
		TAG_limit,
		TAG_btnOK,
		TAG_btnCancel,
	};
	DonateView();
	~DonateView();

	bool init(int techID);
	void onBtnCut(CCObject* pSender);
	int getmoneytext();
	void setmoneytext(int value);
	void onBtnAdd(CCObject* pSender);
	int onMoneyCheck(int money);
	void onBtnMax(CCObject* pSender);
	void onBtnOK(CCObject* pSender);
	void onBtnCancel(CCObject* pSender);
	void update();
	void setdonated(uint value);
	void setdonateMax(uint value);
	void dispear(CCObject* pSender);
public:
	TextFieldTTF* _money;
	uint _techID;			//当前科技ID
	uint _donated;			//今日已捐献银币数
	uint _donateMax;		//每日捐献上限
	int _ownedMoney;		//角色拥有的银币
	CCLabelTTF* _limit;
};