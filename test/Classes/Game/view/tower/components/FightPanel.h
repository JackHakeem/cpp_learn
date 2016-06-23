#ifndef _FightPanel_H_
#define _FightPanel_H_

#include "cocos2d.h"
#include "BaseType.h"
#include "CCUIBackground.h"
#include "model/tower/vo/TowerPanel2Vo.h"
#include "socket/command/s3c/SCMD3CF.h"
#include "utils/BitmapMovieClip.h"
#include "socket/command/s3a/SCMD3AE.h"

USING_NS_CC;

class FightPanel : public CCLayer
{
public:
	FightPanel();
	~FightPanel();

public:

	bool init();
	bool updateInfo(TowerPanel2Vo* vo);
	void inspire( int inspire );
	void updateFloorText();
	void displayBoss2(bool isShow);
	void updateRewardIcon( string curIcons, string nextIcons);
	void loopHandle( vector<std::string>& icons, int begin);
	void updateBossRewardTip();
	void saveBossTips( std::list<SCMD3CF::SCMD3CFNode>& a_rewards );
	void initRoleModel();
	void curTile( int _curTile );
	void updateRoleModel();
	void onEnter();
	void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	void onGoldInspire(CCObject* obj);
	void onPracInspire(CCObject* obj);
	void onRaiders(CCObject* obj);
	void onFight(CCObject* obj);
	void onBossFight(CCObject* obj);
	void onLeav(CCObject* obj);
	

	bool levAreaCheck();
	bool maxFloorCheck(int curFloor);
	void onWalkEffComplete();
	void updateTileIcon();
	void inspireTip(SCMD3AE* cmd);
	void nextInspirePrac( int c_nextPrac );
	void reset();
	void lockBtnGold(ccTime dt);
	void lockBtnPrac(ccTime dt);
	void showButtonGua(bool var);

	bool FightLock() const { return m_bFightLock; }
	void FightLock(bool val) { m_bFightLock = val; }
public:
	int _nextInspirePrac;		//下次历练鼓舞所需历练数量

	CCLabelTTF* _txtBestFloor;
	CCLabelTTF* _txtCurFloor;
	CCLabelTTF* _txtBossTip;
	CCLabelTTF* _txtBossReward;
	CCLabelTTF* _nextMonster;

	CCLabelTTF* _txtPlus;

	CCUIBackground* nextAwardBg1;
	CCUIBackground* nextAwardBg2;
	CCUIBackground* leaveAwardBg1;
	CCUIBackground* leaveAwardBg2;

	CCLabelTTF* _nextAwardTip1;
	CCLabelTTF* _nextAwardTip2;
	CCLabelTTF* _leaveAwardTip1;
	CCLabelTTF* _leaveAwardTip2;

	CCLabelTTF* _hideBoss;

	CCLabelTTF* _floorTextArr[5];

	CCPoint _footStandPos[5];
	CCSprite* _footStandBg[5];

	CCMenuItemSprite* _btnGoldInspireImg;	//金币鼓舞
	CCMenuItemSprite* _btnPracInspireImg;	//历练鼓舞
	
	//private var _pracInspireTip:TipHelps;	//历练鼓舞提示

	//private var _btnRaiders:SimpleButton;	//攻略
	CCMenuItemSprite* _btnBeginImg;		//开始闯塔
	CCMenuItemSprite* _btnLeavImg;		//离塔
	

	CCPoint _floorTileArr[4];
	//private var _floorTextArr:Array = [0];
	//private var _hideBossArr:Array = [0];

	int _curFloor; 	//当前所在层
	int _historyFloor;
	int _curTile;	// 1-5
	bool _isRoleMoving;
	bool _isInit;
	bool _isMaxFloor;
	bool _isMinFloor;
	bool m_bFightLock;
	std::map<int, int> _bossTips;

	BitmapMovieClip* roleMovieClip;
	int _inspire;
//挂机
public:
	void onGUA(CCObject* obj);
	void stepGUA(float dt);
	void unGUA(CCObject* obj);
	void onFightGUA(CCObject* obj);
	void lockFight( ccTime dt );
	float m_timerGUA;
	CCMenuItemSprite* _btnGUA;		//挂机
	

//
};

#endif