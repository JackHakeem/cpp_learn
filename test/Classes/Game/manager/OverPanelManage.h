#ifndef _OVERPANELMANAGE_H_
#define _OVERPANELMANAGE_H_

#include "view/backpack/BagMediator.h"
#include "view/bank/BankMediator.h"
/**
	* This class is the main items of drag in management of each section of the moving back and forth between
	* @author Administrator
	* 
	*/
enum
{	
	OVER_0_NONE = 0,
	OVER_1_FIGURE,	
	OVER_2_BAG,					
	OVER_3_MALL,						
	OVER_4_MAIL,				
	OVER_5_STORE,			


	OVER_6_BANK,					
	OVER_7_BAG_ITEM,			
	OVER_8_BANK_ITEM,		
		
	OVER_10_SHOP,			
		
	OVER_11_FORMATION_HEAD,	
	OVER_12_FORMATION,	
	OVER_13_TASKVIEW,
	OVER_14_MAINSTRENGVIEW,
};
class BagMediator;
class BagProxy;
class GameDispatcher;
class OverPanelManage:public CCNode
{
public:

public:
	OverPanelManage();

	void goodsMove(int32 sid, int32 overName, float locX, float locY, int32 fromName=0, CCObject* other=0);
	void moveGoods(float locX, float locY, int32 oldsit);
	void moveBankGoods(float locX, float locY, int32 oldsit);
	void panelChange(uint32 type, uint32 siteNum);
	void throwGoods(CCObject* pSender);
	void putOnEquipment_forBtn(CCObject* pSender);
	void putOnEquipment(int sid,CCObject* pSender); // added by longhui 20120425
	void putDownEquipment(CCObject* pSender); // added by longhui 20120425
	void buttonBagToBank(CCObject* pSender);
	void buttonBankToBag(CCObject* pSender);
	void sellGoods(CCObject* pSender);
public:
	BagMediator* bagMediator;

	BagProxy* bagProxy;

	BankMediator* bankMediator;

	BankProxy* bankProxy;

	GameDispatcher* _dispatcher;

	int32 UseType;
	int32 sitGrid;

	BagGoods * _pCurBagGoods;

};

extern OverPanelManage* g_pOverPanelManage;

#endif