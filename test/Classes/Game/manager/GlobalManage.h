#ifndef _GLOBALMANAGE_H_
#define _GLOBALMANAGE_H_

#include "BaseType.h"

/**
* Global variable manager
* @author Administrator
* 
*/

class GameView;
class ServerListVo;
class GlobalManage:public CCIEventDispatcher
{
public:
	enum
	{
		MINE_TIME_CHANGE,
	};
	GlobalManage();
	~GlobalManage();
public:
//	CC_PROPERTY(int32, _FocusGIDFactory, FocusGIDFactory)		//Factory take the new global focus ID scheme
	CC_PROPERTY(int32, _CurFocusGID, CurFocusGID)				//The current global focus ID
	CC_PROPERTY(bool, _isInGame, IsInGame)
	CC_SYNTHESIZE(bool,_isHasPop,IsHasPop)
	CC_SYNTHESIZE(bool,isInWordMap,IsInWordMap)
	CC_SYNTHESIZE(bool, _isShowAllUILock, IsShowAllUILock)
	CC_SYNTHESIZE(int, _RoleSpeed, RoleSpeed)
	CC_SYNTHESIZE(bool, _isInCopyMap, IsInCopyMap)
    CC_SYNTHESIZE(bool, _isHideOtherPlayers, IsHideOtherPlayers)
	CC_SYNTHESIZE(bool, _isInWorldBoss, IsInWorldBoss)
	CC_SYNTHESIZE(bool, _isStorySystemOpen, IsStorySystemOpen)

    //Doyang 20120811
    CC_SYNTHESIZE(bool, _isShowEndFightButton, IsShowEndFightButton)

	bool isFCM();
	void isFCM(bool value);
	bool isEnterGame();
	void isEnterGame(bool value);
	bool isOnBusiness();
	void isOnBusiness(bool value);
	bool isOnMeditation();
	void isOnMeditation(bool value);
	bool canMove();
	void canMove(bool value);
	bool inMineTime();
	void inMineTime(bool value);

	bool inGongTime();
	void inGongTime(bool value);

	void setisInFight( bool bValue );
	bool getisInFight();
	//isInFight _Jae
	void showAllUIEx(bool bValue);
public:
	void showAllUI(bool bValue);
	void setTowerGUA(int value);
	int getTowerGUA();

	void setDunGUA(int value);
	int getDunGUA();
	void setDunMapId(int value);
	int getDunMapId();

	void switchBattleEffect( bool bVar )
	{
		m_bLoadingOver = bVar;
	}
public:
	GameView* gameView;      //  The game scene
	int guild;
	bool isGm;
	bool _isEnterGame;
	bool isReport;

	bool g_isRedMonster;
	//add by edwardliu
	bool isInDream;
	bool _isInFight;
	bool isInStory;
	bool isGuest;
	bool _isFCM;
	bool _isOnBusiness;
	bool _isOnMeditation;
	bool _canMove;
	int bFollowerId;
	int followerId;
	bool isSmallMapReady;
	bool isInArmyFight;
	bool isRoleHidden;
	bool _inMineTime;
	bool _inGongTime;
	int m_iTowerGUA;
	int m_iDunGUA;
	int m_iDunGUAMapid;
	int g_netDelay;

	bool canOperate;  // ’Î∂‘≤Èø¥’Ω±®µ»π˝øÏµƒŒ Ã‚ 
	CCRenderTexture *_pRt;

	CCNode * _curNewTips; // new reward tips

	bool _isChangeScene;
	bool IsChangeScene() const { return _isChangeScene; }
	void IsChangeScene(bool val) { _isChangeScene = val; }

	int m_nNumberOfSprites;
	int NumberOfSprites() const { return m_nNumberOfSprites; }
	void NumberOfSprites(int val) { m_nNumberOfSprites = val; }
	int m_nNumberOfLoadedSprites;
	void loadOneProgress( int iGoCnt );

	int _exchangeType;
	void setExchangeType(int type);
	int getExchangeType() { return _exchangeType; }
	void startResourceLoadingSync();
	//void startLoading();
	void loadUIImages();

	DWORD d1;
	DWORD d2;

	bool m_bLoadingOver;
	int m_canSCMD133Enable;//if(gua) fang zhi lin jie tiao jian .because if(gua) no SCMD132 recv

	bool needCreatTraderPlayer;
	bool _tradeMapLimit;

	bool m_bBattleEffectOn;
};

extern GlobalManage* g_pGlobalManage;

#endif