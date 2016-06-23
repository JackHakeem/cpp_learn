#ifndef HLQS_FightScene_H_
#define HLQS_FightScene_H_
#include "BaseScene.h"
#include "fight/FormationLoader.h"
#include "socket/command/s13/SCMD13D.h"
#include "socket/command/s3b/SCMD3B1.h"
#include "fight/FightEnd.h"

class FightScene: public BaseScene
{
public:
	enum
	{
		FIGHT_END_EVENT = 0,
		NORMAL_PLAY,
		SPEED_PLAY,
		ADDED_TO_STAGE,
	};

	enum
	{
		TAG_BTN_END = 1001,
		TAG_RESULT_LAYER = 2001,
	};

	int _type;
	int _battleType;
	bool _isNewHandLeader;
	std::map<std::string, FormationLoader*> _formationLoaderDic;
	CCLayer* _warPlace;
	CCLabelTTF *_roundLabel;
	FightEnd* _resultWin;
	CCMenu * _pEndFightMenu;
	CCMenu * _pFastFightMenu;
public:
	FightScene();
	~FightScene();
	void addedToStage(CCNode* n, void* data);
	void initUI();
	void showPeratingSP(bool value = true);
	CCLayer* createWarField(int x, int y, int scaleX = 1, int scaleY = 1);
	void loadWarFormation(int formationId, int x, int y, int scaleX = 1, int scaleY = 1, int alpha = 1);
	LiveThing* getLiveThing(int type, int id);
	void showResult(int result, int typeBattle, SCMD13D* reward = NULL, SCMD3B1* report = NULL);
	void showRound(int32 r);
	void stopActions();
	void dispose();
	void endFight(CCObject * pSender);
	void fastFight(CCObject * pSender);

	virtual void registerWithTouchDispatcher( void );
	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
	virtual void onExit();
};

#endif