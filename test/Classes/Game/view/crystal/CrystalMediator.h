#ifndef _CRYSTALMEDIATOR_H_
#define _CRYSTALMEDIATOR_H_
#include "mvc/Mediator.h"
#include "control/crystal/CrystalCommand.h"


USING_NS_CC;

class CrystalView;
class CrystalManager;
class CrystalMediator : public Mediator
{
public:
	CrystalMediator();
	~CrystalMediator();

	void crystalUpgradeListener(char * data);			// upgrade result
	void crystalActivateListener(char * data);		// activate
	void crystalInfoListener(char * data);			// crystal info response
	void initCrystalView();	
	void popCrystalView();
	void crystalUpgradeCDTimeListener(char * data);		// CD time response
	void crystalCDLeftTimeListener(char * data);		 // CD left time response

	void upgradeCrystalHandler(char * data);			// upgrade clicked

	void sendCrystalInfoReq();
	void reqMoney(uint8 type);
	void reqClearCD(int type,int cost);
    void respClearCD(char * pPacket);
	void reqUpgradeTime(int id);
	void respMoney(char * pPacket);

	enum 
	{
		INIT_CRYSTAL=0,
		UPGRADE_CRYSTAL,
		UPDATE_CDTIME,
		UPDATE_VIEW,
		UPDATE_CDLIST
	};
public:
	CrystalView * _crystalView;
	CrystalCommand * _crystalCommand;
	virtual void handleNotification(int M2Vcmd, char* data);

	void initCDList(char * data);                    //SCMD17F
	void updateCDTime(char *data);					// update CD time
	void updateCDList(char *data);					// update CD left time list
	void updateView();
	void updateDetailInfo(int id);
	void sendBuyCDListReq(int type);
	void sockBuyCrystalCDList(char * data);

	void popHandler(CCNode *pNode, void *data);
};

#endif