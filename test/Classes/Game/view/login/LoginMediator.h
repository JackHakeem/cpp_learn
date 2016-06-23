#ifndef _LOGIN_MEDIATOR_H_
#define _LOGIN_MEDIATOR_H_

#include "view/BaseMediator.h"
#include "socket/command/s15/SCMD150.h"
#include "socket/command/s10/SCMD107.h"
#include "socket/command/s30/SCMD309.h"
#include "socket/command/s30/SCMD30A.h"
#include "socket/command/s17/SCMD17F.h"
#include "socket/command/s16/SCMD161.h"
#include "socket/command/s31/SCMD319.h"
#include "socket/command/s3c/SCMD3C9.h"
#include "socket/command/s18/SCMD18A.h"
#include "socket/command/s3c/SCMD3C8.h"

class LoginMediator : public BaseMediator
{
public:
	LoginMediator();
	virtual ~LoginMediator(){};

	void handleNotification(int M2Vcmd, char* data);
	void taskProcess(char *data);
	void taskAccept(char *data);
	void initScene(SCMD123* cmd);
	void onLogin();
	void initRoleInfo(SCMD107* cmd);
	void getUserInfo();
	void getUserInfoHandler();
	void mercenaryBaseInfo(SCMD309* cmd);
	void sockEquipInfo(SCMD30A* cmd);
	void initCD(SCMD17F* scmd17f);
	void initWorldBag(SCMD161* cmd);
	void initBank(SCMD161* cmd);
	void initPassiveSkill(SCMD319* cmd);
	void initTalentSkill(SCMD3C9* cmd);
	void initCrystal(SCMD18A* cmd);
	void sendHartbeatToServer( ccTime dt );

	void trialVipState(SCMD3C8 *pData);

	// Doyang 20121026
	void sendClientType();
public:
	int progress;
	int total;
	enum
	{
		GETUSERINFO = 0,
	};
};
#endif
