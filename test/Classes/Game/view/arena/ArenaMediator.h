#ifndef _ARENAMEDIATOR_H_
#define _ARENAMEDIATOR_H_

#include "mvc/Mediator.h"
#include "socket/command/s28/SCMD285.h"
#include "socket/command/s28/SCMD287.h"
#include "socket/command/s39/SCMD39D.h"
#include "socket/command/s36/SCMD366.h"

class ArenaProxy;
class GameDispatcher;
class ArenaUI;
class HeroRankView;
class ArenaMediator:public Mediator
{
public:
	enum
	{
		PVP_QUALIFYING_START = 0,
		PVP_QUALIFYING_RESULT,
		PVP_ARENACONTEST_RESULT,
		PVP_ARENACONTEST_LIST,
		PVP_FIGHTINGFISH,
	};

	ArenaMediator();
	~ArenaMediator();
public:
	virtual void handleNotification(int M2Vcmd, char* data);
	void openArena();
	void openArenaUI();
	void heroInfoHandler(SCMD285* cmd);
	void heroGetAwardHandler(SCMD287* cmd);
	int getMaxLevByRange(int);
	void winningStarHandler(char* cmd);
	void athleticsReportHandler(SCMD39D* cmd);

	void closeArenaHander();
	void getAwardHandler(CCNode* p, void* e);
	void getHeroRankAward();

	void showArena(CCNode* p, void* e);
	void CommandQualifying();
	void showArenaHandler();
	void lookRankHandler(CCNode* n, void* data);
	void challengeErrorHandler(SCMD366* param);
public:


	ArenaProxy* _arenaProxy;

	GameDispatcher* _dispatcher;
	ArenaUI* _arenaUI;
	HeroRankView* _heroRankView;				//”¢–€∞ÒUI;
};

#endif