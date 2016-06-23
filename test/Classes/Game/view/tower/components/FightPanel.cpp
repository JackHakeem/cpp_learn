#include "FightPanel.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "manager/LangManager.h"
#include "model/config/ConfigManager.h"
#include "manager/SourceCacheManage.h"
#include "utils/BitmapMovieClip.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "model/player/RoleManage.h"
#include "manager/TouchLayerEnum.h"
#include "../TowerMediator.h"
#include "manager/GlobalManage.h"
#include "model/backpack/BagProxy.h"
#include "manager/LevLimitConst.h"

static const int Tag_AwardTip = 1600;

FightPanel::FightPanel():_nextInspirePrac(0)
{
	_isInit = false;
	_isMaxFloor = false;
	_isMinFloor = false;

	m_timerGUA = 0;
	_curFloor = 0;
	_nextInspirePrac = 0;
	
	_isInit = false;
	_isMaxFloor = false;
	_isMinFloor = false;

	_historyFloor = 0;
	_curTile = 1;

	_isRoleMoving = false;

	_floorTileArr[0] = ccp(POSX(-302), POSX(95));
	_floorTileArr[1] = ccp(POSX(302), POSX(95));
	_floorTileArr[2] = ccp(POSX(-302), POSX(95));
	_floorTileArr[3] = ccp(POSX(302), POSX(95));
	_btnGUA = 0;
	_btnBeginImg = 0;
	roleMovieClip = NULL;
	roleMovieClip = NULL;
	m_bFightLock = false;
}

FightPanel::~FightPanel()
{

}


bool FightPanel::init()
{
	CCSize size = this->getContentSize();

	CCSize csIner( POSX(923), POSX(562) );
	this->setContentSize(csIner);


	CCUIBackground* _infoContainer = new CCUIBackground();
	_infoContainer->initWithSpriteFrame("ui2.png", 
		ccp(POSX(629), POSX(28)),
		ccp(2,2),
		CCSizeMake(POSX(281),POSX(504)));
	this->addChild(_infoContainer);
	_infoContainer->release();

	CCSprite* enBg = new CCSprite;
	enBg->initWithSpriteFrameName("tower_other/3.png");
	enBg->setAnchorPoint(CCPointZero);
	enBg->setPosition(ccp(POSX(12), POSX(27)));
	this->addChild(enBg);
	enBg->release();


	//guwu
	_txtPlus = CCLabelTTF::labelWithString(
		"",
		CCSizeMake( POSX(172), POSX(24) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24));
	_txtPlus->setPosition( ccp( POSX(16), POSX(449) ) );
	_txtPlus->setAnchorPoint(CCPointZero);
	addChild( _txtPlus );
	_txtPlus->setColor( ccc3(30,255,6) );
	_txtPlus->setIsVisible(false);

	//最佳成绩:
	_txtBestFloor = CCLabelTTF::labelWithString(
		"",
		CCSizeMake( POSX(258), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	_txtBestFloor->setPosition( ccp( POSX(643), POSX(499) ) );
	_txtBestFloor->setAnchorPoint(CCPointZero);
	addChild( _txtBestFloor );
	_txtBestFloor->setColor( ccc3(255,192,0) );

	//当前层数:
	_txtCurFloor = CCLabelTTF::labelWithString(
		"",
		CCSizeMake( POSX(258), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	_txtCurFloor->setPosition( ccp( POSX(643), POSX(499-15-18) ) );
	_txtCurFloor->setAnchorPoint(CCPointZero);
	addChild( _txtCurFloor );
	_txtCurFloor->setColor( ccc3(255,192,0) );

	//奖励:
	_txtBossTip = CCLabelTTF::labelWithString(
		"",
		CCSizeMake( POSX(258), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	_txtBossTip->setPosition( ccp( POSX(643), POSX(499-15*2-18*2-30) ) );
	_txtBossTip->setAnchorPoint(CCPointZero);
	addChild( _txtBossTip );
	_txtBossTip->setColor( ccWHITE );
	_txtBossTip->setIsVisible(false);

	//历练:
	_txtBossReward = CCLabelTTF::labelWithString(
		"",
		CCSizeMake( POSX(258), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	_txtBossReward->setPosition( ccp( POSX(643), POSX(499-15*3-18*3-30) ) );
	_txtBossReward->setAnchorPoint(CCPointZero);
	addChild( _txtBossReward );
	_txtBossReward->setColor( ccGREEN );
	_txtBossReward->setIsVisible(false);

	//下层怪物:
	CCLabelTTF* nextMonster = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("TOWR016").c_str(),
		CCSizeMake( POSX(18*5+20), POSX(18+4) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	nextMonster->setPosition( ccp( POSX(643), POSX(499-15*3-18*4-60) ) );
	nextMonster->setAnchorPoint(CCPointZero);
	addChild( nextMonster );
	nextMonster->setColor( ccWHITE );

	_nextMonster = CCLabelTTF::labelWithString(
		"",
		CCSizeMake( POSX(258), POSX(18+4) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	_nextMonster->setPosition( ccp( POSX(643+18*5+20), POSX(499-15*3-18*4-60) ) );
	_nextMonster->setAnchorPoint(CCPointZero);
	addChild( _nextMonster );
	_nextMonster->setColor( ccRED );
	
	//下层奖励:
	CCLabelTTF* nextAward = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("TOWR017").c_str(),
		CCSizeMake( POSX(258), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	nextAward->setPosition( ccp( POSX(643), POSX(499-15*5-18*5-20-90-15+92/2) ) );
	nextAward->setAnchorPoint(CCPointZero);
	addChild( nextAward );
	nextAward->setColor( ccWHITE );

	nextAward = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("TOWR117").c_str(),
		CCSizeMake( POSX(258), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	nextAward->setPosition( ccp( POSX(643-5+18*6), POSX(499-15*5-18*5-20-90-15+92/2) ) );
	nextAward->setAnchorPoint(CCPointZero);
	addChild( nextAward );
	nextAward->setColor( ccc3(255,192,0) );
	
	
	////离塔可获得:
	//CCLabelTTF* leaveGet = CCLabelTTF::labelWithString(
	//	ValuesUtil::Instance()->getString("TOWR018").c_str(),
	//	CCSizeMake( POSX(258), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	//leaveGet->setPosition( ccp( POSX(643-5), POSX(499-15*5-18*5-20-120-70-15+92/2) ) );
	//leaveGet->setAnchorPoint(CCPointZero);
	//addChild( leaveGet );
	//leaveGet->setColor( ccWHITE );

	// 层
	CCPoint pos = ccp( POSX(541), POSX(33) );
	_floorTextArr[0] = CCLabelTTF::labelWithString(
		"",
		CCSizeMake( POSX(85), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	_floorTextArr[0]->setPosition( pos );
	_floorTextArr[0]->setAnchorPoint(CCPointZero);
	addChild( _floorTextArr[0] );
	_floorTextArr[0]->setColor( ccWHITE );

	pos = ccp( POSX(5+5), POSX(121) );
	_floorTextArr[1] = CCLabelTTF::labelWithString(
		"",
		CCSizeMake( POSX(85), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	_floorTextArr[1]->setPosition( pos  );
	_floorTextArr[1]->setAnchorPoint(CCPointZero);
	addChild( _floorTextArr[1] );
	_floorTextArr[1]->setColor( ccWHITE );
	
	pos = ccp( POSX(534), POSX(220) );
	_floorTextArr[2] = CCLabelTTF::labelWithString(
		"",
		CCSizeMake( POSX(85), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	_floorTextArr[2]->setPosition( pos );
	_floorTextArr[2]->setAnchorPoint(CCPointZero);
	addChild( _floorTextArr[2] );
	_floorTextArr[2]->setColor( ccWHITE );
	
	pos = ccp( POSX(10+5), POSX(330) );
	_floorTextArr[3] = CCLabelTTF::labelWithString(
		"",
		CCSizeMake( POSX(85), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	_floorTextArr[3]->setPosition( pos );
	_floorTextArr[3]->setAnchorPoint(CCPointZero);
	addChild( _floorTextArr[3] );
	_floorTextArr[3]->setColor( ccWHITE );

	pos = ccp( POSX(527+15), POSX(424) );
	_floorTextArr[4] = CCLabelTTF::labelWithString(
		"",
		CCSizeMake( POSX(85), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	_floorTextArr[4]->setPosition( pos );
	_floorTextArr[4]->setAnchorPoint(CCPointZero);
	addChild( _floorTextArr[4], 1 );
	_floorTextArr[4]->setColor( ccWHITE );

	//CCSize awardCs( POSX(100), POSX(100));
	//nextAwardBg1 = new CCUIBackground();
	//nextAwardBg1->initWithSpriteFrame("ui.png", 
	//	ccp(POSX(643+108-30-5), POSX(499-15*5-18*5-20-90-15)),
	//	ccp(2,2),
	//	awardCs);
	//this->addChild(nextAwardBg1);
	//nextAwardBg1->release();
	//CCLabelTTF* awardTip = CCLabelTTF::labelWithString(
	//	"",
	//	CCSizeMake( POSX(18*4), POSX(18) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(18));
	//awardTip->setPosition( ccp( POSX(70-40), POSX(15) ) );
	//awardTip->setAnchorPoint(CCPointZero);
	//nextAwardBg1->addChild( awardTip,1,Tag_AwardTip );
	//awardTip->setColor( ccWHITE );
	//_nextAwardTip1 = awardTip;

	//nextAwardBg2 = new CCUIBackground();
	//nextAwardBg2->initWithSpriteFrame("ui.png", 
	//	ccp(POSX(643+108+105-30-15), POSX(499-15*5-18*5-20-90-15)),
	//	ccp(2,2),
	//	awardCs);
	//this->addChild(nextAwardBg2);
	//nextAwardBg2->release();
	//awardTip = CCLabelTTF::labelWithString(
	//	"",
	//	CCSizeMake( POSX(18*4), POSX(18) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(18));
	//awardTip->setPosition( ccp( POSX(70-40), POSX(15) ) );
	//awardTip->setAnchorPoint(CCPointZero);
	//nextAwardBg2->addChild( awardTip,1,Tag_AwardTip );
	//awardTip->setColor( ccWHITE );
	//_nextAwardTip2 = awardTip;

	//leaveAwardBg1 = new CCUIBackground();
	//leaveAwardBg1->initWithSpriteFrame("ui.png", 
	//	ccp(POSX(643+108-30-5), POSX(499-15*5-18*5-20-120-70-15)),
	//	ccp(2,2),
	//	awardCs);
	//this->addChild(leaveAwardBg1);
	//leaveAwardBg1->release();
	//awardTip = CCLabelTTF::labelWithString(
	//	"",
	//	CCSizeMake( POSX(18*4), POSX(18) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(18));
	//awardTip->setPosition( ccp( POSX(70-40), POSX(15) ) );
	//awardTip->setAnchorPoint(CCPointZero);
	//leaveAwardBg1->addChild( awardTip,1,Tag_AwardTip );
	//awardTip->setColor( ccWHITE );
	//_leaveAwardTip1 = awardTip;

	//leaveAwardBg2 = new CCUIBackground();
	//leaveAwardBg2->initWithSpriteFrame("ui.png", 
	//	ccp(POSX(643+108+105-30-15), POSX(499-15*5-18*5-20-120-70-15)),
	//	ccp(2,2),
	//	awardCs);
	//this->addChild(leaveAwardBg2);
	//leaveAwardBg2->release();
	//awardTip = CCLabelTTF::labelWithString(
	//	"",
	//	CCSizeMake( POSX(18*4), POSX(18) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(18));
	//awardTip->setPosition( ccp( POSX(70-40), POSX(15) ) );
	//awardTip->setAnchorPoint(CCPointZero);
	//leaveAwardBg2->addChild( awardTip,1,Tag_AwardTip );
	//awardTip->setColor( ccWHITE );
	//_leaveAwardTip2 = awardTip;

	{
		// foot 1 standing
		_footStandPos[0] = ccp(POSX(452), POSX(69));
		_footStandBg[0] = new CCSprite;
		_footStandBg[0]->initWithSpriteFrameName("tower/5.png");
		_footStandBg[0]->setAnchorPoint(CCPointZero);
		_footStandBg[0]->setPosition(ccp(POSX(371),POSX(21)));
		this->addChild(_footStandBg[0]);
		_footStandBg[0]->release();
	

		// foot 2 standing
		_footStandPos[1] = ccp(POSX(156),POSX(165));
		_footStandBg[1] = new CCSprite;
		_footStandBg[1]->initWithSpriteFrameName("tower/6.png");
		_footStandBg[1]->setAnchorPoint(CCPointZero);
		_footStandBg[1]->setPosition(ccp(POSX(68),POSX(117)));
		this->addChild(_footStandBg[1]);
		_footStandBg[1]->release();

		// foot 3 standing
		_footStandPos[2] = ccp(POSX(461),POSX(257));
		_footStandBg[2] = new CCSprite;
		_footStandBg[2]->initWithSpriteFrameName("tower/6.png");
		_footStandBg[2]->setAnchorPoint(CCPointZero);
		_footStandBg[2]->setPosition(ccp(POSX(373),POSX(209)));
		this->addChild(_footStandBg[2]);
		_footStandBg[2]->release();

		// foot 4 standing
		_footStandPos[3] = ccp(POSX(166),POSX(352));
		_footStandBg[3] = new CCSprite;
		_footStandBg[3]->initWithSpriteFrameName("tower/6.png");
		_footStandBg[3]->setAnchorPoint(CCPointZero);
		_footStandBg[3]->setPosition(ccp(POSX(78),POSX(306)));
		this->addChild(_footStandBg[3]);
		_footStandBg[3]->release();


		// foot 5 standing
		_footStandPos[4] = ccp(POSX(461),POSX(442));
		_footStandBg[4] = new CCSprite;
		_footStandBg[4]->initWithSpriteFrameName("tower/6.png");
		_footStandBg[4]->setAnchorPoint(CCPointZero);
		_footStandBg[4]->setPosition(ccp(POSX(370),POSX(398)));
		this->addChild(_footStandBg[4]);
		_footStandBg[4]->release();
	}

	// btn
	CCSize csBt( POSX(121), POSX(49 ));	
	{
		// jinbi btn
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			_btnGoldInspireImg = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(FightPanel::onGoldInspire) );
			_btnGoldInspireImg->setPosition( ccp( POSX(14)+csBt.width/2, POSX(487)+csBt.height/2 ) );
			CCMenu* _btnStrengUp = CCMenu::menuWithItems(_btnGoldInspireImg, 0);
			_btnStrengUp->setTouchLayer( TLE::WindowLayer_Common_btn );
			_btnStrengUp->setPosition( CCPointZero );
			this->addChild( _btnStrengUp );
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
				ValuesUtil::Instance()->getString( "TOWR019" ).c_str(),
				CCSizeMake(POSX(150), POSX(49)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
			txtLabel->setAnchorPoint(CCPointZero);
			txtLabel->setPosition( ccp( POSX(  (121-150)/2  ), 0 ) );
			_btnGoldInspireImg->addChild( txtLabel );
			_btnStrengUp->setIsVisible(false);
		}
	}

	{
		// lilian btn
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			_btnPracInspireImg = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(FightPanel::onPracInspire) );
			_btnPracInspireImg->setPosition( ccp( POSX(14)+csBt.width/2, POSX(31)+csBt.height/2 ) );
			CCMenu* _btnStrengUp = CCMenu::menuWithItems(_btnPracInspireImg, 0);
			_btnStrengUp->setTouchLayer( TLE::WindowLayer_Common_btn );
			_btnStrengUp->setPosition( CCPointZero );
			this->addChild( _btnStrengUp );
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
				ValuesUtil::Instance()->getString( "TOWR020" ).c_str(),
				CCSizeMake(POSX(150), POSX(49)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
			txtLabel->setAnchorPoint(CCPointZero);
			txtLabel->setPosition( ccp( POSX(  (121-150)/2  ), 0 ) );
			_btnPracInspireImg->addChild( txtLabel );
			_btnStrengUp->setIsVisible(false);
		}
	}

	{
		// 下一层 btn
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			_btnBeginImg = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(FightPanel::onFight) );
			_btnBeginImg->setPosition( ccp( POSX(643)+csBt.width/2, POSX(66-15)+csBt.height/2 ) );
			CCMenu* _btnStrengUp = CCMenu::menuWithItems(_btnBeginImg, 0);
			_btnStrengUp->setTouchLayer( TLE::WindowLayer_Common_btn );
			_btnStrengUp->setPosition( CCPointZero );
			this->addChild( _btnStrengUp );
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
				ValuesUtil::Instance()->getString( "TOWR021" ).c_str(),
				CCSizeMake(POSX(200), POSX(49)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
			txtLabel->setAnchorPoint(CCPointZero);
			txtLabel->setPosition( ccp( POSX(  (121-200)/2  ), 0 ) );
			_btnBeginImg->addChild( txtLabel );
		}
	}

	{
		// 离塔 btn
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			_btnLeavImg = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(FightPanel::onLeav) );
			_btnLeavImg->setPosition( ccp( POSX(643+130)+csBt.width/2, POSX(66-15)+csBt.height/2 ) );
			CCMenu* _btnStrengUp = CCMenu::menuWithItems(_btnLeavImg, 0);
			_btnStrengUp->setTouchLayer( TLE::WindowLayer_Common_btn );
			_btnStrengUp->setPosition( CCPointZero );
			this->addChild( _btnStrengUp );
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
				ValuesUtil::Instance()->getString( "TOWR022" ).c_str(),
				csBt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
			txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
			_btnLeavImg->addChild( txtLabel );
		}
	}

	{
		// 挂机 btn
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			_btnGUA = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(FightPanel::onGUA) );
			_btnGUA->setPosition( ccp( POSX(643+130)+csBt.width/2, POSX(66-15)+csBt.height/2+POSX(300) ) );
			CCMenu* _btnMenu = CCMenu::menuWithItems(_btnGUA, 0);
			_btnMenu->setTouchLayer( TLE::WindowLayer_Common_btn );
			_btnMenu->setPosition( CCPointZero );
			this->addChild( _btnMenu );
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
				ValuesUtil::Instance()->getString( "TOWR023" ).c_str(),
				csBt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
			txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
			_btnGUA->addChild( txtLabel );

			// LH 
			if (RoleManage::Instance()->roleLev() < LevLimitConst::Limit_Gua)
			{
				_btnGUA->setIsVisible(false);
			}
		}
	}	

	initRoleModel();

	this->setIsTouchEnabled(true);

	return true;
}



bool FightPanel::updateInfo(TowerPanel2Vo* vo)
{
	//_isMaxFloor = (vo->nextIcons == "");
	_isMinFloor = (vo->curIcons == "");
	_historyFloor = vo->maxFloor;
	
	if (!_txtCurFloor)
	{
		return false;
	}
	char tmp[128];
	sprintf(tmp, ValuesUtil::Instance()->getString("TOWR013").c_str(), vo->curFloor);
	_txtCurFloor->setString(tmp);

	if (!_isInit)
	{
		_curFloor = vo->curFloor;
	}
	else
	{
		if ( (vo->curFloor - _curFloor) > 1 ) // 战斗超时
		{
			curTile(_curTile+vo->curFloor - _curFloor);
			_curFloor = vo->curFloor;

			int index = _curTile-1;
			if ( _footStandBg[index] )
			{
				_footStandBg[index]->removeFromParentAndCleanup(true);

				CCPoint cp( POSX(177/2), POSX(96/2) );
				_footStandBg[index] = new CCSprite;
				_footStandBg[index]->initWithSpriteFrameName("tower/6.png");
				_footStandBg[index]->setAnchorPoint(CCPointZero);
				_footStandBg[index]->setPosition( ccpSub( _footStandPos[index], cp )  );
				this->addChild(_footStandBg[index]);
				_footStandBg[index]->release();
			}
			if (roleMovieClip)
			{
				roleMovieClip->setPosition( ccpAdd(  _footStandPos[index], ccp(0, POSX(125/2)))  );
			}
			
		}
	}

	if(vo->curFloor>_curFloor)
	{
		if(_isInit)	//这一句必须在_curFloor赋值之后
		{
			curTile(_curTile+1);
		}
		_curFloor = vo->curFloor;
	}
	else
	{
		if (roleMovieClip)
		{
			int tileIndex = _curTile;
			int state = 7;
			int action = BitmapMovieClip::ACTION_STAND;
			if(tileIndex == 2 || tileIndex == 4){
				state = 9;
			}

			roleMovieClip->setPosition( ccpAdd(  _footStandPos[tileIndex-1], ccp(0, POSX(125/2))) );
			_isRoleMoving = false;
			roleMovieClip->runActionEx( action, state );
		}
	}


	sprintf(tmp, ValuesUtil::Instance()->getString("TOWR012").c_str(), vo->maxFloor);
	_txtBestFloor->setString(tmp);

	_nextMonster->setString(vo->nextMonster.c_str());

	inspire(vo->inspire);
	nextInspirePrac(vo->inspirePrac);

	updateFloorText();
	updateBossRewardTip();
	displayBoss2(vo->showCurBoss);
	updateRewardIcon(vo->curIcons, vo->nextIcons);

	if ( _curTile == 5 )
	{
		onWalkEffComplete();
	}
	if(!_isInit) _isInit = true;
}

//由服务端返回状态确定是否显示隐藏Boss
void FightPanel::displayBoss2(bool isShow)
{
	//_hideBossArr[curTile].visible = isShow;
	//if(isShow)
	//{
	//	var numStr:String;
	//	if(_bossTips[curFloor]){
	//		numStr = _bossTips[curFloor].toString();
	//	}else{
	//		numStr = LangManager.getText("TWR010");
	//	}
	//	var tip:String = LangManager.getText("TWR014",numStr);
	//	new TipHelps().setToolTips(_hideBossArr[curTile] as MovieClip, tip);
	//}
}

void FightPanel::inspire( int inspire )
{
	if ( inspire < 0 )
	{
		inspire = inspire + 256;
	}
	_inspire = inspire;
	
	_txtPlus->setString( LangManager::getText("TWR012",inspire).c_str() );

	if (g_pGlobalManage->getTowerGUA() == 0)//if(挂ing) 不进
	{
		if(inspire > 190)
		{
			//鼓舞上限不能超过200%
			if (_btnGoldInspireImg)
			{
				_btnGoldInspireImg->setIsEnabled(false);
			}
		}else{
			_btnGoldInspireImg->setIsEnabled(true);
		}
		if(inspire >= 200)
		{
			//鼓舞上限200%
			_btnPracInspireImg->setIsEnabled(false);
		}else{
			_btnPracInspireImg->setIsEnabled(true);
		}	
	}
}

void FightPanel::updateFloorText()
{
	if(_curTile != 1)
		return;
	int txtFloor = 0;
	for(int i=1; i<=5; i++)
	{
		txtFloor = _curFloor + i - 1;
		if(txtFloor > 120)
		{
			//目前最高120级
			_floorTextArr[i-1]->setString("");
		}
		else
		{
			_floorTextArr[i-1]->setString( LangManager::getText("TWR004",txtFloor).c_str() );
		}
	}
}

//更新奖励图标
void FightPanel::updateRewardIcon( string curIcons, string nextIcons)
{
	vector<std::string> iconsvec = ConfigManager::splitStringByCharacter(curIcons,"|");
	vector<std::string> nextIconsvec = ConfigManager::splitStringByCharacter(nextIcons,"|");

	//if (nextAwardBg1->getChildByTag(Tag_AwardTip-1))
	//{
	//	nextAwardBg1->removeChildByTag(Tag_AwardTip-1, true);
	//}
	//if (nextAwardBg2->getChildByTag(Tag_AwardTip-1))
	//{
	//	nextAwardBg2->removeChildByTag(Tag_AwardTip-1, true);
	//}
	//if (leaveAwardBg1->getChildByTag(Tag_AwardTip-1))
	//{
	//	leaveAwardBg1->removeChildByTag(Tag_AwardTip-1, true);
	//}
	//if (leaveAwardBg2->getChildByTag(Tag_AwardTip-1))
	//{
	//	leaveAwardBg2->removeChildByTag(Tag_AwardTip-1, true);
	//}

	//loopHandle(iconsvec, 1);
	//loopHandle(nextIconsvec, 3);
}

void FightPanel::loopHandle( vector<std::string>& icons, int begin)
{
	//int j = begin;
	char tmp[128] = {0};
	for(int i=0; i<icons.size(); i++){
		vector<std::string> tmpArr = ConfigManager::splitStringByCharacter(icons[i], ",");
		if(tmpArr.size() != 3 || tmpArr[0] == "")
			continue;

		sprintf( tmp,"assets/icon/goods/%d.png", atoi(tmpArr[0].c_str()));
		CCSprite* pAward = new CCSprite;
		pAward->initWithFile(tmp);
		pAward->setAnchorPoint(CCPointZero);
		pAward->setPosition(ccp(5,5));
		pAward->setTag(Tag_AwardTip-1);
		CCLabelTTF* tip = 0;
		if (begin == 1)
		{
			if (i==0)
			{
				leaveAwardBg1->addChild( pAward,0 );
				tip = (CCLabelTTF*)leaveAwardBg1->getChildByTag(Tag_AwardTip);
			}
			else
			{
				leaveAwardBg2->addChild( pAward,0 );
				tip = (CCLabelTTF*)leaveAwardBg2->getChildByTag(Tag_AwardTip);
			}
		}
		else
		{
			if (i==0)
			{
				nextAwardBg1->addChild( pAward,0 );
				tip = (CCLabelTTF*)nextAwardBg1->getChildByTag(Tag_AwardTip);
			}
			else
			{
				nextAwardBg2->addChild( pAward,0 );
				tip = (CCLabelTTF*)nextAwardBg2->getChildByTag(Tag_AwardTip);
			}
		}
		pAward->release();

		if (tip)
		{
			tip->setString(tmpArr[1].c_str());
		}
	}
}

void FightPanel::updateBossRewardTip()
{
	int floorOfNextBoos = int((_curFloor + 10) / 10) * 10;

	if(floorOfNextBoos > 120)
	{
		//最高120层
		_txtBossTip->setString( LangManager::getText("TWR007").c_str() );
		_txtBossReward->setString( LangManager::getText("TWR008").c_str());
		return;
	}

	_txtBossTip->setString( LangManager::getText("TWR009",floorOfNextBoos).c_str() );

	string tip = "";
	char txt[128];
	std::map<int , int>::iterator it = _bossTips.find(floorOfNextBoos);
	if(it!=_bossTips.end()){
		sprintf( txt, ValuesUtil::Instance()->getString("TOWR015").c_str(), it->second );
		tip = txt;
	}else{
		tip = LangManager::getText("TWR010") + LangManager::getText("pat") ;
	}
	_txtBossReward->setString(tip.c_str());
}

void FightPanel::saveBossTips( std::list<SCMD3CF::SCMD3CFNode>& a_rewards )
{
	_bossTips.clear();
	std::list<SCMD3CF::SCMD3CFNode>::iterator it = a_rewards.begin();
	for ( ; it != a_rewards.end(); it++ )
	{
		SCMD3CF::SCMD3CFNode& node = *it;
		_bossTips[node.a_floor] = node.c_num;
	}
}

void FightPanel::initRoleModel()
{
	char _assetURL[128];
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	sprintf( _assetURL, "assets/res/%d", info->playerBaseInfo.cloth);

	CC_SAFE_RELEASE_NULL(roleMovieClip);
	roleMovieClip = new BitmapMovieClip();
	roleMovieClip->loadModelAsync(_assetURL, info->playerBaseInfo.cloth);
	//roleMovieClip = SourceCacheManage::Instance()->loadModel(
	//	_assetURL, info->playerBaseInfo.cloth, 0.1f, true);

	roleMovieClip->setAnchorPoint(ccp(0.5,0.5));
	roleMovieClip->setPosition(POSX(452), POSX(48+125 / 2));

	this->addChild(roleMovieClip, 2);
	roleMovieClip->release();

	if(roleMovieClip)
		roleMovieClip->runActionEx(BitmapMovieClip::ACTION_STAND, 7);

}

void FightPanel::curTile( int curTile )
{
	if(_isRoleMoving) return;
	_isRoleMoving = true;
	if(curTile < 1 || curTile > 5 || _curTile == curTile){
		_isRoleMoving = false;
		return;
	}
	_curTile = curTile;
	//updateTileIcon();
	//updateFloorText();
	updateRoleModel();
}

void FightPanel::updateRoleModel()
{
	if(_curTile == 1){
		_isRoleMoving = false;
		if(roleMovieClip)
			roleMovieClip->runActionEx(BitmapMovieClip::ACTION_STAND, 7);
		return;
	}

	if (! roleMovieClip)
		return;

	int tileIndex = _curTile - 1;
	int state = 7;
	int action = BitmapMovieClip::ACTION_WALK;
	if(tileIndex == 2 || tileIndex == 4){
		state = 9;
	}
	 
	CCSprite *pPlayerSprite = roleMovieClip->getPlayerSprite();
	if (! pPlayerSprite)
		return;

	roleMovieClip->runActionEx(action, state);
	pPlayerSprite->setIsVisible(true);

	CCFiniteTimeAction *pMoveAction = CCMoveTo::actionWithDuration(1.5f,
		_floorTileArr[tileIndex-1] );
	
	CCCallFunc *pGoldChangedFunc = CCCallFunc::actionWithTarget(this,
		callfunc_selector(FightPanel::onWalkEffComplete));
	CCAction *pAction = CCSequence::actions(pMoveAction, pGoldChangedFunc, NULL);
	
	pPlayerSprite->runAction(pAction);

	updateTileIcon();
}

void FightPanel::onWalkEffComplete()
{
	if(_curTile == 5)
	{	
		//hideAllBoss();	//此三行顺序不能变
		//_hideBossArr[1].visible = showBoss;

		//updateTileIcon();

		_curTile = 1;
		updateFloorText();
		_isRoleMoving = false;
		if (! roleMovieClip)
			return;

		roleMovieClip->setPosition( ccpAdd( _footStandPos[0], ccp(0, POSX(125/2)) ) );
		roleMovieClip->runActionEx(BitmapMovieClip::ACTION_STAND, 7);
	
		return;
	}

	updateTileIcon();

	int tileIndex = _curTile;
	int state = 7;
	if(tileIndex == 2 || tileIndex == 4){
		state = 9;
	}

	_isRoleMoving = false;
	if(! roleMovieClip)
		return;
	roleMovieClip->setPosition( ccpAdd(roleMovieClip->getPosition(), _floorTileArr[tileIndex-2]) );
	roleMovieClip->runActionEx(BitmapMovieClip::ACTION_STAND, state);

}

void FightPanel::onEnter()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Common, true);
	CCLayer::onEnter();
}

void FightPanel::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}	

bool FightPanel::ccTouchBegan(CCTouch* pTouch, CCEvent* event)
{
	return true;
}

void FightPanel::ccTouchEnded(CCTouch* pTouch, CCEvent* event)
{
	if (g_pGlobalManage->getTowerGUA() != 0)//gua ing
		return;

	if ( m_bFightLock )
	{
		return;
	}

	for ( int i = 0; i < 5; i++ )
	{
		if ( !_footStandBg[i] )
		{
			continue;
		}

		CCPoint itemPoint = getScreenPos(_footStandBg[i]);
		CCSize itemSize = _footStandBg[i]->getContentSize();
		CCPoint locationInView = pTouch->locationInView(pTouch->view());
		CCPoint currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
		if ( CCRect::CCRectContainsPoint(
			CCRectMake(itemPoint.x,itemPoint.y, itemSize.width,itemSize.height), currentTouchPoint)
			)
		{
			if ( _curTile == i )
			{
				onFight(0);
			}	
		}
	}
}


//金币鼓舞
void FightPanel::onGoldInspire(CCObject* obj)
{
	int hasGold = RoleManage::Instance()->accountInfo()->gold();
	if(hasGold < 10){
		//Alert.show(LangManager.getText("TWR015"));
		LangManager::msgShow("TWR015");
	}else{
		int a = 1;
		g_pTowerMediator->_towerView->dispatchEvent( TowerView::ON_TOWER_INSPIRE, &a );
	}
	_btnGoldInspireImg->setIsEnabled(false);
	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(FightPanel::lockBtnGold),
		this,0.2f,false);
}

void FightPanel::lockBtnGold(ccTime dt)
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(FightPanel::lockBtnGold), this);
	if (_btnGoldInspireImg && (_inspire<200))
	{
		_btnGoldInspireImg->setIsEnabled(true);
	}
}

void FightPanel::lockBtnPrac(ccTime dt)
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(FightPanel::lockBtnPrac), this);
	if (_btnPracInspireImg  && (_inspire<200))
	{
		_btnPracInspireImg->setIsEnabled(true);
	}
}

//历练鼓舞
void FightPanel::onPracInspire(CCObject* obj){
	int hasPrac = RoleManage::Instance()->accountInfo()->practice();
	if(hasPrac < _nextInspirePrac){
		//Alert.show(LangManager.getText("TWR016"));
		LangManager::msgShow("TWR016");
	}else{
		int a = 2;
		g_pTowerMediator->_towerView->dispatchEvent( TowerView::ON_TOWER_INSPIRE, &a );
		//dispatchEvent(new ParamEvent(ON_TOWER_INSPIRE, 2));
	}
	_btnPracInspireImg->setIsEnabled(false);
	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(FightPanel::lockBtnPrac),
		this,0.2f,false);
}

//攻略
void FightPanel::onRaiders(CCObject* obj){
	// 暂无
}

//爬塔战斗
void FightPanel::onFightGUA(CCObject* obj)
{
	if(_isRoleMoving)
		return;
	if(levAreaCheck()){
		return;
	}
	if(maxFloorCheck(_curFloor)){
		return;
	}
	int isGUA = 1;
	g_pTowerMediator->_towerView->dispatchEvent( TowerView::ON_TOWER_FIGHT, &isGUA );
}

//爬塔战斗
void FightPanel::onFight(CCObject* obj)
{
	m_bFightLock = true;
	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(FightPanel::lockFight), this, 2, false);
	_btnBeginImg->setIsEnabled(false);

	if(_isRoleMoving)
		return;
	if(levAreaCheck()){
		return;
	}
	if(maxFloorCheck(_curFloor)){
		return;
	}
	int isGUA = 0;
	g_pTowerMediator->_towerView->retain();
	g_pTowerMediator->_towerView->dispatchEvent( TowerView::ON_TOWER_FIGHT, &isGUA );
}

void FightPanel::lockFight( ccTime dt )
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(FightPanel::lockFight), this);
	_btnBeginImg->setIsEnabled(true);
	m_bFightLock = false;
}

//隐藏Boss战斗
void FightPanel::onBossFight(CCObject* obj){
	if(levAreaCheck()){
		return;
	}
	g_pTowerMediator->_towerView->dispatchEvent( TowerView::FIGHT_HIDE_BOSS, 0 );
}

//离塔
void FightPanel::onLeav(CCObject* obj){

	//g_pTowerMediator->_towerView->dispatchEvent( TowerView::ON_LEAVE_TOWER, 0 );
	unGUA(0);
	g_pTowerMediator->_towerView->onLeaveTower(obj);
}

//挂机
void FightPanel::onGUA(CCObject* obj)
{
	if (_curFloor >= _historyFloor )
	{
		LangManager::msgShow("TOWR073");
		return;
	}
	g_pTowerMediator->_towerView->cleanLayerGUA();

	if (_btnGoldInspireImg) _btnGoldInspireImg->setIsEnabled(false);
	if (_btnPracInspireImg) _btnPracInspireImg->setIsEnabled(false);
	if (_btnLeavImg) _btnLeavImg->setIsEnabled(false);

	_btnBeginImg->setIsEnabled(false);
	_btnBeginImg->setIsVisible(false);
	_btnGUA->setIsEnabled(false);
	schedule (schedule_selector (FightPanel::stepGUA));//keving , 0.5f
}

//挂机
void FightPanel::unGUA(CCObject* obj)
{
	if (_btnGUA) _btnGUA->setIsEnabled(true);
	if (_btnBeginImg)_btnBeginImg->setIsEnabled(true);

	if (_btnGoldInspireImg) _btnGoldInspireImg->setIsEnabled(true);
	if (_btnPracInspireImg) _btnPracInspireImg->setIsEnabled(true);
	if (_btnLeavImg) _btnLeavImg->setIsEnabled(true);
	_btnBeginImg->setIsVisible(true);

	g_pTowerMediator->_towerView->cleanLayerGUA();

	m_timerGUA = 0.0f;
	g_pGlobalManage->setTowerGUA(0); 
	this->unschedule(schedule_selector(FightPanel::stepGUA));
}

void FightPanel::stepGUA(float dt)
{
	if (_isRoleMoving == true)//移动中不计时
		return;

	if (g_pGlobalManage->getTowerGUA() == 0)
	{
		g_pGlobalManage->setTowerGUA(1);
	}
	else if (g_pGlobalManage->getTowerGUA() == 1)
	{

		if (m_timerGUA >= 0.0f)
		{

			m_timerGUA = 0.0f;

			BagProxy* bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
			if (bagProxy && bagProxy->getSpaceGridNum()<=0)
			{
				LangManager::msgShow("TOWR072");
				unGUA(0);
				return;
			}

			g_pGlobalManage->setTowerGUA(2);//卡发送CCMD3B6
			onFightGUA(0);
		}
	}
	else if (g_pGlobalManage->getTowerGUA() == 2)
	{}
	else if (g_pGlobalManage->getTowerGUA() == 3)//解卡接收SCMD3B7继续计时
	{
		m_timerGUA+=dt;
		if (m_timerGUA >= 2.0f)
		{
			m_timerGUA = 0.0f;
			g_pGlobalManage->setTowerGUA(1);
		}
	}
}


//检查是否已进入到下一等级区域但仍在塔内
bool FightPanel::levAreaCheck()
{
	bool key = false; 
	int roleLev = RoleManage::Instance()->roleLev();
	//if(_isMinFloor){
	//	//if(roleLev - _curFloor > 20) key = true;
	//}else{
	//	if(_curFloor <= 60){
	//		if(roleLev > 60) key = true;
	//	}else if(_curFloor <= 80){
	//		if(roleLev > 80) key = true;
	//	}else if(_curFloor <= 100){
	//		if(roleLev > 100) key = true;
	//	}else if(_curFloor <= 120){
	//		if(roleLev > 120) key = true;
	//	}
	//}
	if(key){
		//Alert.show(LangManager.getText("TWR041"));
		LangManager::msgShow("TWR041");
	}
	return key;
}

//判断是否已达当前等级区域最高层
bool FightPanel::maxFloorCheck(int curFloor)
{
	int roleLev = RoleManage::Instance()->roleLev();
	if ( (roleLev>=40)&&(roleLev<60) )
	{
		if(_curFloor == 60){
			_isMaxFloor = true;
		}
	} 
	else if ( (roleLev>=60)&&(roleLev<80) )
	{
		if(_curFloor == 80){
			_isMaxFloor = true;
		}
	}
	else if ( (roleLev>=80)&&(roleLev<100) )
	{
		if(_curFloor == 100){
			_isMaxFloor = true;
		}
	}
	else
	{
		if(_curFloor == 120){
			_isMaxFloor = true;
		}
	}

	if(_isMaxFloor){
		if(curFloor == 120){
			//Alert.show(LangManager.getText("TWR017"));
			LangManager::msgShow("TWR017");
		}else{
			//Alert.show(LangManager.getText("TWR018"));
			LangManager::msgShow("TWR018");
		}
		return true;
	}
	return false;
} 

void FightPanel::updateTileIcon()
{
	int index = _curTile-1;
	CCPoint cp( POSX(177/2), POSX(96/2) );
	if ( _footStandBg[index] )
	{

		if (index==4)
		{
			_footStandBg[0]->removeFromParentAndCleanup(true);

			_footStandBg[0] = new CCSprite;
			_footStandBg[0]->initWithSpriteFrameName("tower/5.png");
			_footStandBg[0]->setAnchorPoint(CCPointZero);
			_footStandBg[0]->setPosition(ccpSub( _footStandPos[0], cp ));
			this->addChild(_footStandBg[0]);
			_footStandBg[0]->release();

			for ( int i=1; i<5; i++)
			{
				_footStandBg[i]->removeFromParentAndCleanup(true);

				_footStandBg[i] = new CCSprite;
				_footStandBg[i]->initWithSpriteFrameName("tower/6.png");
				_footStandBg[i]->setAnchorPoint(CCPointZero);
				_footStandBg[i]->setPosition(ccpSub( _footStandPos[i], cp ));
				this->addChild(_footStandBg[i], 0);
				_footStandBg[i]->release();
			}
			
		}
		else
		{
			_footStandBg[index]->removeFromParentAndCleanup(true);

			_footStandBg[index] = new CCSprite;
			_footStandBg[index]->initWithSpriteFrameName("tower/5.png");
			_footStandBg[index]->setAnchorPoint(CCPointZero);
			_footStandBg[index]->setPosition(ccpSub( _footStandPos[index], cp ));
			this->addChild(_footStandBg[index]);
			_footStandBg[index]->release();
		}			
	}
}

void FightPanel::inspireTip(SCMD3AE* cmd)
{
	switch(cmd->a_result)
	{
	case 0:
		//０，失败
		LangManager::msgShow("TWR013");
		break;
	case 1:
		//１，成功
		inspire(cmd->b_inspire);
		break;
	case 2:
		//２，不变（请求鼓舞信息）
		break;
	}
	nextInspirePrac(cmd->c_nextPrac);
}

void FightPanel::nextInspirePrac( int c_nextPrac )
{
	_nextInspirePrac = c_nextPrac;
}

void FightPanel::reset()
{
	if(roleMovieClip)
	{
		CCPoint cp( POSX(177/2), POSX(96/2) );
		//roleMovieClip->setPosition(POSX(452), POSX(48+125 / 2));

		roleMovieClip->setPosition(_footStandPos[0]);
		roleMovieClip->runActionEx(BitmapMovieClip::ACTION_STAND, 7);

		for ( int i=1; i<5; i++)
		{
			_footStandBg[i]->removeFromParentAndCleanup(true);

			_footStandBg[i] = new CCSprite;
			_footStandBg[i]->initWithSpriteFrameName("tower/6.png");
			_footStandBg[i]->setAnchorPoint(CCPointZero);
			_footStandBg[i]->setPosition(ccpSub( _footStandPos[i], cp ));
			this->addChild(_footStandBg[i], 0);
			_footStandBg[i]->release();
		}

		if (_footStandBg[0])
		{
			_footStandBg[0]->removeFromParentAndCleanup(true);

			_footStandBg[0] = new CCSprite;
			_footStandBg[0]->initWithSpriteFrameName("tower/5.png");
			_footStandBg[0]->setAnchorPoint(CCPointZero);
			_footStandBg[0]->setPosition(ccpSub( _footStandPos[0], cp ));
			this->addChild(_footStandBg[0]);
			_footStandBg[0]->release();
		}
		
	}
	_curTile = 1;

	//_nextAwardTip1->setString("");
	//_nextAwardTip2->setString("");
	//_leaveAwardTip1->setString("");
	//_leaveAwardTip2->setString("");
}

void FightPanel::showButtonGua(bool var)
{
	if (_btnGUA)
	{
		_btnGUA->setIsVisible(var);
	}	
}
