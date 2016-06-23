#include "EnterPanel.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "manager/LangManager.h"
#include "model/player/RoleManage.h"
#include "manager/TouchLayerEnum.h"
#include "../TowerMediator.h"

static const int Tag_Foloor = 1350;
static const int Tag_Foloor_txt = 1650;

EnterPanel::EnterPanel()
{
	_txtMyRank = 0;

	_txtTopRank = 0;
	_txtFreeNum = 0;

	_txtLastFloor = 0;
	_txtLevArea = 0;
	_txtFloorArea = 0;
	m_pPanel1vo = 0;
}

EnterPanel::~EnterPanel()
{

}


bool EnterPanel::init()
{
	CCSize csIner( POSX(923), POSX(562) );
	this->setContentSize(csIner);

	CCUIBackground* _infoContainer = new CCUIBackground();
	_infoContainer->initWithSpriteFrame("ui2.png", 
		ccp(POSX(629), POSX(28)),
		ccp(2,2),
		CCSizeMake(POSX(281),POSX(504)));
	this->addChild(_infoContainer);
	_infoContainer->release();
	//CCLayerColor* pLayerColor1 = CCLayerColor::layerWithColorWidthHeight(
	//	ccc4( 0, 255, 0, 100 ), strengSize.width, strengSize.height );
	//_strengCreate->addChild( pLayerColor1 );

	CCSprite* enBg = new CCSprite;
	enBg->initWithSpriteFrameName("tower/2.png");
	enBg->setAnchorPoint(CCPointZero);
	enBg->setPosition(ccp(POSX(12), POSX(27)));
	this->addChild(enBg);
	enBg->release();

	//我的排行:
	//CCLabelTTF* _sItemsName = CCLabelTTF::labelWithString(
	//	ValuesUtil::Instance()->getString("TOWR001").c_str(),
	//	CCSizeMake( POSX(92), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	//_sItemsName->setPosition( ccp( POSX(643), POSX(499) ) );
	//_sItemsName->setAnchorPoint(CCPointZero);
	//addChild( _sItemsName );
	//_sItemsName->setColor( ccc3(255,192,0) );

	_txtMyRank = CCLabelTTF::labelWithString(
		"0",
		CCSizeMake( POSX(43), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	_txtMyRank->setPosition( ccp( POSX(643+92+2), POSX(499) ) );
	_txtMyRank->setAnchorPoint(CCPointZero);
	addChild( _txtMyRank );
	_txtMyRank->setColor( ccWHITE );
	_txtMyRank->setIsVisible(false);

	//排名top4 说明
	CCLabelTTF* _sItemsName = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("TOWR002").c_str(),
		CCSizeMake( POSX(300), POSX(22) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	_sItemsName->setPosition( ccp( POSX(643), POSX(479-25-10) ) );
	_sItemsName->setAnchorPoint(CCPointZero);
	addChild( _sItemsName );
	_sItemsName->setColor( ccc3(255,192,0) );

	_txtTopRank = CCLabelTTF::labelWithString(
		"",
		CCSizeMake( POSX(300), POSX(18*4+15) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	_txtTopRank->setPosition( ccp( POSX(643), POSX(479-18*4-25-15*2-10) ) );
	_txtTopRank->setAnchorPoint(CCPointZero);
	addChild( _txtTopRank );
	_txtTopRank->setColor( ccc3(0,255,12) );

	////免费闯塔次数 说明
	//_sItemsName = CCLabelTTF::labelWithString(
	//	ValuesUtil::Instance()->getString("TOWR003").c_str(),
	//	CCSizeMake( POSX(240), POSX(28) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24));
	//_sItemsName->setPosition( ccp( POSX(210), POSX(143) ) );
	//_sItemsName->setAnchorPoint(CCPointZero);
	//addChild( _sItemsName );
	//_sItemsName->setColor( ccc3(255,192,0) );

	//_txtFreeNum = CCLabelTTF::labelWithString(
	//	"",
	//	CCSizeMake( POSX(244), POSX(28) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24));
	//_txtFreeNum->setPosition( ccp( POSX(240 + 162 + 20), POSX(143) ) );
	//_txtFreeNum->setAnchorPoint(CCPointZero);
	//addChild( _txtFreeNum );
	//_txtFreeNum->setColor( ccGREEN );

	// 上次成绩
	_txtLastFloor = CCLabelTTF::labelWithString(
		"",
		CCSizeMake( POSX(171), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	_txtLastFloor->setPosition( ccp( POSX(30), POSX(496) ) );
	_txtLastFloor->setAnchorPoint(CCPointZero);
	addChild( _txtLastFloor, 1 );
	_txtLastFloor->setColor( ccc3(255,192,0) );
	_txtLastFloor->setIsVisible(false); // delete this time

	// award btn
	CCSize csBt( POSX(121), POSX(49 ));
	{
		{
			CCMenuItemSprite *pStrengUpItem = CCMenuItemSprite::itemFromNormalSprite(
				CCSprite::spriteWithSpriteFrameName("button.png"),
				CCSprite::spriteWithSpriteFrameName("button1.png"),
				CCSprite::spriteWithSpriteFrameName("button2.png"),
				this,
				menu_selector(EnterPanel::takeRankAward) );
			pStrengUpItem->setPosition( ccp( POSX(718)+csBt.width/2, POSX(67)+csBt.height/2 ) );
			CCMenu* _btnStrengUp = CCMenu::menuWithItems(pStrengUpItem, 0);
			_btnStrengUp->setTouchLayer( TLE::WindowLayer_Common_btn );
			_btnStrengUp->setPosition( CCPointZero );
			this->addChild( _btnStrengUp );
			//_btnStrengUp->setIsVisible(false);// for temp!
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
				ValuesUtil::Instance()->getString( "TOWR106" ).c_str(),
				CCSizeMake(POSX(150), POSX(49)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
			txtLabel->setAnchorPoint(CCPointZero);
			txtLabel->setPosition( ccp( POSX(  (121-150)/2  ), 0 ) );
			pStrengUpItem->addChild( txtLabel );
		}
	}

	//当前所在等级区域 说明
	_sItemsName = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("TOWR005").c_str(),
		CCSizeMake( POSX(253), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	_sItemsName->setPosition( ccp( POSX(648), POSX(235) ) );
	_sItemsName->setAnchorPoint(CCPointZero);
	addChild( _sItemsName );
	_sItemsName->setColor( ccWHITE );

	_txtLevArea = CCLabelTTF::labelWithString(
		"",
		CCSizeMake( POSX(256), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	_txtLevArea->setPosition( ccp( POSX(648), POSX(204) ) );
	_txtLevArea->setAnchorPoint(CCPointZero);
	addChild( _txtLevArea );
	_txtLevArea->setColor( ccGREEN );

	//对应的挑战层数为 说明  ----> 占领塔的玩家每两天可额外领取宝箱奖励
	_sItemsName = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("TOWR007").c_str(),
		CCSizeMake( POSX(253), POSX(18*3+10) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	_sItemsName->setPosition( ccp( POSX(648), POSX(156-15) ) );
	_sItemsName->setAnchorPoint(CCPointZero);
	addChild( _sItemsName );
	_sItemsName->setColor( ccWHITE );

	//_txtFloorArea = CCLabelTTF::labelWithString(
	//	"",
	//	CCSizeMake( POSX(256), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
	//_txtFloorArea->setPosition( ccp( POSX(648), POSX(156-15) ) );
	//_txtFloorArea->setAnchorPoint(CCPointZero);
	//addChild( _txtFloorArea );
	//_txtFloorArea->setColor( ccGREEN );

	// board btn	
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *pStrengUpItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(EnterPanel::openTowerRank) );
			pStrengUpItem->setPosition( ccp( POSX(780+2)+csBt.width/2, POSX(477)+csBt.height/2 ) );
			CCMenu* _btnStrengUp = CCMenu::menuWithItems(pStrengUpItem, 0);
			_btnStrengUp->setTouchLayer( TLE::WindowLayer_Common_btn );
			_btnStrengUp->setPosition( CCPointZero );
			this->addChild( _btnStrengUp );
			//_btnStrengUp->setIsVisible(false);//for temp!
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
				ValuesUtil::Instance()->getString( "TOWR009" ).c_str(),
				csBt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
			txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
			pStrengUpItem->addChild( txtLabel );
		}
	}

	// in btn
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *pStrengUpItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				g_pTowerMediator->_towerView,
				menu_selector(TowerView::enterTowerFight1) );
			pStrengUpItem->setPosition( ccp( POSX(270)+csBt.width/2, POSX(66)+csBt.height/2 ) );//270,64
			CCMenu* _btnStrengUp = CCMenu::menuWithItems(pStrengUpItem, 0);
			_btnStrengUp->setTouchLayer( TLE::WindowLayer_Common_btn );
			_btnStrengUp->setPosition( CCPointZero );
			this->addChild( _btnStrengUp );
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
				ValuesUtil::Instance()->getString( "TOWR010" ).c_str(),
				csBt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
			txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
			pStrengUpItem->addChild( txtLabel );
		}
	}
	
	//floors
	char txttmp[20] = {0};
	int tag = 1, start = 0;
	if (RoleManage::Instance()->roleLev() < 80)
	{ 
		start = 1;
	}
	else 
	{
		start = 5;
	}
	
	for ( int i = start; i <= start+7; i++)
	{
		sprintf( txttmp, ValuesUtil::Instance()->getString("TOWR011").c_str(), i );
		CCLabelTTF* txtFolor = CCLabelTTF::labelWithString(
			txttmp,
			CCSizeMake( POSX(90), POSX(28) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(28));
		txtFolor->setAnchorPoint(CCPointZero);
		txtFolor->setPosition( ccp(POSX(45+((i-start)%2)*479+4), POSX(12+((i-start)/2)*124)+12) );
		addChild( txtFolor, 1, Tag_Foloor_txt+tag );
		txtFolor->setColor( ccGRAY );
		tag++;
	}
	

	return true;
}

void EnterPanel::takeRankAward(CCObject* ojb)
{
	//if (m_pPanel1vo->myRank==0)
	//{
	//	LangManager::msgShow("TOWR111");
	//	return;
	//}
	
	g_pTowerMediator->_towerView->dispatchEvent( TowerView::ON_TAKE_AWARD, 0 );
}

void EnterPanel::openTowerRank(CCObject* ojb)
{
	g_pTowerMediator->_towerView->dispatchEvent( TowerView::OPEN_TOWER_RANK, 0 );
}

// 4)	闯塔分等级段，41-60层：45-60级，61-80层：61-80级，81-100层：81-100级，101-120层：101-120级；
void EnterPanel::updateMyArea()
{
	TowerProxy* _towerProxy = (TowerProxy*)g_pFacade->retrieveProxy( AppFacade_TOWER_PROXY_CHANGE );
	if (!_towerProxy->getpanel1Vo())
	{
		return;
	}
	int lev = /*RoleManage::Instance()->roleLev()*/_towerProxy->getpanel1Vo()->maxFloor;
	//int lev = RoleManage::Instance()->roleLev();
	if(lev <= 20){
		_txtLevArea->setString( LangManager::getText("TOWR006",1,40).c_str() );
		//_txtFloorArea->setString( LangManager::getText("TOWR008",61,80).c_str() );
		updateBox(1);
	}else if(lev <= 40){
		_txtLevArea->setString( LangManager::getText("TOWR006",1,40).c_str() );
		//_txtFloorArea->setString( LangManager::getText("TOWR008",61,80).c_str() );
		updateBox(2);
	}else if(lev <= 60){
		_txtLevArea->setString( LangManager::getText("TOWR006",41,60).c_str() );
		//_txtFloorArea->setString( LangManager::getText("TOWR008",61,80).c_str() );
		updateBox(3);
	}
	else if(lev <= 80){
		_txtLevArea->setString( LangManager::getText("TOWR006",61,80).c_str() );
		//_txtFloorArea->setString( LangManager::getText("TOWR008",61,80).c_str() );
		updateBox(4);
	}else if(lev <= 100){
		_txtLevArea->setString( LangManager::getText("TOWR006",81,100).c_str() );
		//_txtFloorArea->setString( LangManager::getText("TOWR008",81,100).c_str() );
		updateBox(3);
	}else if(lev <= 120){
		_txtLevArea->setString( LangManager::getText("TOWR006",101,120).c_str() );
		//_txtFloorArea->setString( LangManager::getText("TOWR008",101,120).c_str() );
		updateBox(4);
	}
}


void EnterPanel::enableBox(int floor, bool hightlight)
{
	if (this->getChildByTag(Tag_Foloor+floor))
	{
		this->removeChildByTag(Tag_Foloor+floor, true);
	}

	CCLabelTTF* pFolortxt = (CCLabelTTF*)this->getChildByTag(Tag_Foloor_txt+floor);

	if (hightlight)
	{
		CCSprite* pBox = new CCSprite;
		pBox->initWithSpriteFrameName("tower/1.png");
		pBox->setAnchorPoint(CCPointZero);
		pBox->setPosition( ccp(POSX(27+((floor-1)%2)*479), POSX(22+((floor-1)/2)*124)) );
		this->addChild(pBox, 0, Tag_Foloor+floor);
		pBox->release();

		if (pFolortxt)
		{
			pFolortxt->setColor(ccc3(254,233,0));
		}
	} 
	else
	{
		CCSprite* pBox = new CCSprite;
		pBox->initWithSpriteFrameName("tower/7.png");
		pBox->setAnchorPoint(CCPointZero);
		pBox->setPosition( ccp(POSX(27+((floor-1)%2)*479), POSX(22+((floor-1)/2)*124)) );
		this->addChild(pBox, 0, Tag_Foloor+floor);
		pBox->release();

		if (pFolortxt)
		{
			pFolortxt->setColor(ccc3(127,127,127));
		}
	}
}

void EnterPanel::updateBox(int area)
{
	int i;
	switch(area)
	{
	case 1:
		for(i=1; i<=8; i++)
		{
			if ( (i==1) || (i==2) )
			{
				enableBox(i, true);
				continue;
			}
			enableBox(i, false);
		}
		break;
	case 2:
		for(i=1; i<=8; i++)
		{
			if ( (i==3) || (i==4) )
			{
				enableBox(i, true);
				continue;
			}
			enableBox(i, false);
		}
		break;
	case 3:
		for(i=1; i<=8; i++)
		{
			if ( (i==5) || (i==6) )
			{
				enableBox(i, true);
				continue;
			}
			enableBox(i, false);
		}
		break;
	case 4:
		for(i=1; i<=8; i++)
		{
			if ( (i==7) || (i==8) )
			{
				enableBox(i, true);
				continue;
			}
			enableBox(i, false);
		}
		break;
	}
}

void EnterPanel::updateInfo(TowerPanel1Vo* vo)
{
	TowerProxy* _towerProxy = (TowerProxy*)g_pFacade->retrieveProxy( AppFacade_TOWER_PROXY_CHANGE );
	if (!_towerProxy->getpanel1Vo())
	{
		return;
	}

	m_pPanel1vo = vo;

	ValuesUtil::Instance()->getString("COM657").c_str();
	_txtLastFloor->setString( LangManager::getText("COM657", vo->lastFloor).c_str() );
	if (vo->myRank!=0)
	{
		char tmp[10];
		int rankmy = 120-vo->myRank;
		sprintf( tmp, "%d", 1+(rankmy%120) );
		_txtMyRank->setString(tmp);
	}
	_txtTopRank->setString(vo->topRank.c_str());
	updateMyArea();

	if ( (m_iPreRolelv<80) && (_towerProxy->getpanel1Vo()->maxFloor>=80) )
	{
		//floors
		char txttmp[20] = {0};
		int tag = 1;
		for ( int i = 5; i <= 12; i++)
		{
			sprintf( txttmp, ValuesUtil::Instance()->getString("TOWR011").c_str(), i );
			CCLabelTTF* label = (CCLabelTTF*)this->getChildByTag(Tag_Foloor_txt+tag);
			if (label)
			{
				label->setString(txttmp);
			}
			tag++;
		}
	}
	m_iPreRolelv = /*RoleManage::Instance()->roleLev()*/vo->maxFloor;
}
//
//void EnterPanel::updateBoxTip(tips)
//{
//	const RewardType:Array = ["", Sentence.GOLD, Sentence.SILVER, Sentence.PRACTICE, Sentence.REPUTATION, Sentence.EXPERIENCE, Sentence.VIGOR, Sentence.STONE];
//	for each(var node:SCMD3CFNode in tips){
//		var floor:int = node.a_floor.value / 10;
//		var tip:String = LangManager.getText("TWR001",floor)+makeColor(node.c_num+Sentence.PRACTICE)+"；";
//
//		var tmpStr:String = "";
//		for each(var node2:SCMD3B5Node in node.d_floorReward){
//			var rewardId:int = node2.a_rewardId;
//			if(rewardId < RewardType.length){
//				tmpStr += makeColor(node2.b_rewardNum+RewardType[rewardId]+"") + LangManager.getText("COM658");
//			}
//		}
//		if(tmpStr.substr(-1) == LangManager.getText("COM658")){
//			tmpStr = tmpStr.substr(0, tmpStr.length-1);
//		}
//		tip += LangManager.getText("TWR002",floor) + tmpStr;
//
//		var box:MovieClip = _panel["_box"+floor];
//		if(box){
//			new TipHelps().setToolTips(box, tip);
//		}
//	}
//	for(var i:int=1; i<=4; i++){
//		box = _panel["_box"+i];
//		if(box){
//			tip = LangManager.getText("TWR003");
//			new TipHelps().setToolTips(box, tip);
//		}
//	}
//
//	function makeColor(content:String):String{
//		return "<font color='#00FF00'>"+content+"</font>";
//	}
//}