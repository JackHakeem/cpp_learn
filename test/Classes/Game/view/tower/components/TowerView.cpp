#include "TowerView.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "manager/PopEventName.h"
#include "Confirm.h"
#include "manager/LayerManager.h"
#include "utils/ValuesUtil.h"
#include "model/player/RoleManage.h"
#include "socket/command/c3b/CCMD3B4.h"
#include "socket/network/GameServerSocket.h"
#include "manager/LangManager.h"
#include "../TowerMediator.h"
#include "socket/command/s3b/SCMD3B7.h"
#include "KKLabelTTF.h"
#include "manager/GlobalManage.h"
#include "socket/command/c3d/CCMD3DE.h"
#include "socket/command/c41/CCMD410.h"
#include "manager/ViewManager.h"
#include "manager/VIPMgr.h"
#include "manager/VIPLimitConst.h"
#include "MessageInfoBox.h"

TowerView::TowerView()
{
	pInnerLayer = 0;
	_panelEnter = 0;
	_panelFight = 0;

	for (int i = 0; i < 5; i++)
	{
		arrayGUAInfo[i] = 0;
		
	}
	GUARoundArray[0] = 4;
	GUARoundArray[1] = 0;
	GUARoundArray[2] = 1;
	GUARoundArray[3] = 2;
	GUARoundArray[4] = 3;



	m_enterNeedGold = 0;
	m_pLayerGUA = 0;
}

TowerView::~TowerView()
{
	ViewManager::getInstance()->_pTowerView = 0;
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/res_tower_goods.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/tower/res_tower.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/tower/res_tower_other.plist");
}

bool TowerView::init() 
{
	if(!CCLayer::init())
	{
		return false;
	}
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_tower_goods.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/tower/res_tower.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/tower/res_tower_other.plist");

	key = PopEventName::TOWER;

	this->setPosition(CCPointZero);
	this->setContentSize(CCDirector::sharedDirector()->getWinSize());
	this->setPopContentSize(this->getContentSize());

	CCSize csIner( POSX(923), POSX(562) );
	pInnerLayer = new CCLayer();
	if(!pInnerLayer || !pInnerLayer->init()) 
	{
		return false;
	}
	CCPoint innerLayerPosition = POS(ccp(17.0f, 12.0f), ScaleUtil::CENTER_TOP);
	pInnerLayer->setAnchorPoint(CCPointZero);
	pInnerLayer->setPosition(innerLayerPosition);
	pInnerLayer->setIsRelativeAnchorPoint(true);
	pInnerLayer->setContentSize(csIner);
	this->addChild(pInnerLayer);
	pInnerLayer->release();

	_panelEnter = new EnterPanel;
	_panelEnter->init();
	pInnerLayer->addChild(_panelEnter);
	_panelEnter->release();

	_panelFight = new FightPanel();
	_panelFight->init();
	pInnerLayer->addChild(_panelFight);
	_panelFight->release();
	_panelFight->setIsVisible(false);
    
	//title
	SpriteNode* title = new SpriteNode();
	title->initWithSpriteFrameName("tower/tower.png");
	pInnerLayer->addChild(title, 1);
	title->setPosition(ccp(POSX(403+20), POSX(541)));
	title->setAnchorPoint(CCPointZero);
	title->release();

	//
	m_pLayerGUA = new LayerNode();
	m_pLayerGUA->init();
	pInnerLayer->addChild(m_pLayerGUA, 100);
	m_pLayerGUA->release();
	m_pLayerGUA->setPosition(ccp(0, 0));

	return true;
}

//根据id返回对应的奖励类型
TypeObject TowerView::getRewardType(int id)
{
	TypeObject typeObj;
	switch(id)
	{
	case 1:		// 金币
		typeObj.rewardStr = ValuesUtil::Instance()->getString("gold");
		typeObj.iconStr = "11";
		break;
	case 2:		// 银币
		typeObj.rewardStr = ValuesUtil::Instance()->getString("silver");
		typeObj.iconStr = "12";
		break;
	case 3:		// 历练
		typeObj.rewardStr = ValuesUtil::Instance()->getString("pat");
		typeObj.iconStr = "13";
		break;
	case 4:		// 名声
		typeObj.rewardStr = ValuesUtil::Instance()->getString("rep");
		typeObj.iconStr = "14";
		break;
	case 5:		// 经验
		typeObj.rewardStr = ValuesUtil::Instance()->getString("exp");
		typeObj.iconStr = "";
		break;
	case 6:		// 精力
		typeObj.rewardStr = ValuesUtil::Instance()->getString("jinli");
		typeObj.iconStr = "";
		break;
	case 7:		// 魔晶石
		typeObj.rewardStr = ValuesUtil::Instance()->getString("stone");
		typeObj.iconStr = "17";
		break;
	default:	//物品
		{

		}
		break;
	}
	return typeObj;
}

void TowerView::updatePanelGUA(SCMD3B7* cmd)
{
	if (g_pGlobalManage->getTowerGUA() == 0)
		return;//非挂机状态返回

	static int s_StrColorCount = 0;//103, 228, 235

	int GUARoundArray0 = GUARoundArray[0];
	for (int i = 1; i < 5; i++)
	{
		GUARoundArray[i-1] = GUARoundArray[i];
	}
	GUARoundArray[4] = GUARoundArray0;

	for (int i = 0; i < 5; i++)
	{
		KKLabelTTF* ttf = arrayGUAInfo[GUARoundArray[i]];
		if (ttf)
		{
			ttf->setPosition(ccp(POSX(200), POSX(500-i*90)));
		}
	}


	int index = GUARoundArray[4];
	
	KKLabelTTF* pCell = new KKLabelTTF();
	pCell->init(30, 36.0f, CCSizeMake(550, 120));


	SCMD3B5Node node;
	std::list<SCMD3B5Node>& curRewards = cmd->i_curRewards;
	//std::list<SCMD3B5Node>& nextRewards = cmd->i_nextRewards;
	uint32 expValue;
	if (curRewards.size() != 0)
	{
		expValue = curRewards.begin()->b_rewardNum;
	}
	string iconStr = "";

	char strFloor[100];
	sprintf(strFloor, ValuesUtil::Instance()->getString("TOWR070").c_str(), cmd->f_afterFloor, expValue);
	iconStr += strFloor;


	//TypeObject typeObj;
	//std::list<SCMD3B5Node>::iterator itCur = curRewards.begin();
	//for (; itCur != curRewards.end(); itCur++)
	//{
	//	node = *itCur;
	//	typeObj = getRewardType(node.a_rewardId);
	//	
	//	char str[100];
	//	sprintf(str, ValuesUtil::Instance()->getString("TOWR071").c_str(), typeObj.rewardStr.c_str(), node.b_rewardNum);
	//	iconStr += str;
	//}

	pCell->add(iconStr, (s_StrColorCount++%2==0)?ccc3(255, 0, 0):ccc3(103, 228, 235));


	KKLabelTTF* pold = arrayGUAInfo[index];
	if (pold)
	{
		pold->removeFromParentAndCleanup(true);
	}

	arrayGUAInfo[index] = pCell;
	pCell->setPosition(ccp(POSX(200), POSX(500-4*90)));

	m_pLayerGUA->addChild(pCell, 1);

}

void TowerView::cleanLayerGUA()
{
	for (int i = 0; i < 5; i++)
	{
		arrayGUAInfo[i] = 0;
		
	}
	GUARoundArray[0] = 4;
	GUARoundArray[1] = 0;
	GUARoundArray[2] = 1;
	GUARoundArray[3] = 2;
	GUARoundArray[4] = 3;

	m_pLayerGUA->removeAllChildrenWithCleanup(true);
}

//更新宝箱提示信息
void TowerView::updateBoxTip( std::list<SCMD3CF::SCMD3CFNode>& a_rewards )
{
	//_panelEnter->updateBoxTip(tips);
	_panelFight->saveBossTips(a_rewards);
}

//打开幻龙塔面板信息
void TowerView::updatePanel1( TowerPanel1Vo* vo )
{
	_panelEnter->updateInfo(vo);

}

//服务端返回闯塔面板信息
void TowerView::updatePanel2(TowerPanel2Vo* vo)
{
	enterTowerFight2();
	_panelFight->updateInfo(vo);
}

//服务端返回鼓舞结果
void TowerView::updateInspire(SCMD3AE* cmd)
{
	_panelFight->inspireTip(cmd);
}


//打开幻龙塔排行榜
void TowerView::openTowerRank(CCObject* obj)
{
	dispatchEvent(TowerView::OPEN_TOWER_RANK,0);
}

//请求进入幻龙塔战斗界面
void TowerView::enterTowerFight1(CCObject* obj)
{
	dispatchEvent(TowerView::ENTER_TOWER_FIGHT, 0);
}

void TowerView::enterTowerFight2()
{
	_panelEnter->setIsVisible(false);
	_panelFight->setIsVisible(true);
	g_pTowerMediator->_isInTowerFightPanel = true;

	_panelFight->FightLock(false);
}

//请求鼓舞
void TowerView::onTowerInspire(CCObject* obj)
{
	dispatchEvent(TowerView::ON_TOWER_INSPIRE, 0);
}

//请求普通楼层战斗
void TowerView::onTowerFight(CCObject* obj)
{
	dispatchEvent(TowerView::ON_TOWER_FIGHT, 0);
}

//请求隐藏Boss战斗
void TowerView::fightHideBoss(CCObject* obj)
{
	dispatchEvent(TowerView::FIGHT_HIDE_BOSS,0);
}

//请求离塔
void TowerView::onLeaveTower(CCObject* obj)
{
	TowerProxy* _towerProxy = (TowerProxy*)g_pFacade->retrieveProxy( AppFacade_TOWER_PROXY_CHANGE );
	if( _towerProxy->numPay < _towerProxy->numFree )
	{
		Confirm* pConfirm = new Confirm();
		pConfirm->initWithParam( LangManager::getText("TWR024").c_str(),
			this, menu_selector(TowerView::shureToLeave),
			menu_selector(TowerView::cancelToLeave));
		LayerManager::tipsLayer->addChild(pConfirm,
			TipsLayer::TipsLayerZ_confirmFrame,
			TipsLayer::TipsLayerTAG_confirmFrame);
		pConfirm->release();
	}
	else
	{

		if (!VIPMgr::Instance()->hasVIPFunc(VIPLimitConst::VIP_GoldResetTower , RoleManage::Instance()->accountInfo()->vipLev()))
		{
			char path[128] = {0};
			sprintf(path , ValuesUtil::Instance()->getString("WLC010").c_str() , VIPLimitConst::VIP_GoldResetTower);
			MessageInfoBox::Instance()->show(path,ccc3(12,233,25));
			return;
		}

		m_enterNeedGold = 100 + (_towerProxy->numPay-1) * 100;

		Confirm* pConfirm = new Confirm();
		pConfirm->initWithParam( LangManager::getText("TOWR110", m_enterNeedGold).c_str(),
			this, menu_selector(TowerView::shureToLeave),
			menu_selector(TowerView::cancelToLeave));
		LayerManager::tipsLayer->addChild(pConfirm,
			TipsLayer::TipsLayerZ_confirmFrame,
			TipsLayer::TipsLayerTAG_confirmFrame);
		pConfirm->release();
	}

}

void TowerView::onVisibleChange(CCObject* obj)
{
	dispatchEvent(TowerView::ON_VISIBLE_CHANGE, 0);
	//if(e.param)
	//{
	//	_clostTip.setToolTips(_view["_btnClose"], LangManager.getText("TWR025"));
	//}
	//else
	//{
	//	_clostTip.stopToolTips();
	//}
}

void TowerView::shureToLeave(CCObject* obj)
{

	//CCMD410 cmd;
	//cmd.a_dunId = 0;
	//GameServerSocket::getInstance()->sendMessage(&cmd);
	////这里需要同步
	//LayerManager::loadingPic->socketWait( WMSG_DUNGEON_GUA, 0, 0);

	g_pGlobalManage->setTowerGUA(0);

	_panelFight->FightLock(true);


	dispatchEvent(TowerView::ON_LEAVE_TOWER, 0);

	//remove自己
	Confirm* pConfirm = (Confirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
}

void TowerView::cancelToLeave( CCObject* obj )
{
	//remove自己
	Confirm* pConfirm = (Confirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
}

void TowerView::okFunctionFightIn(CCObject* obj)
{
	//int lev = RoleManage::Instance()->roleLev();
	int beginFloor = 0;
	//if(lev <= 60){
	//	beginFloor = 41;
	//}else if(lev <= 80){
	//	beginFloor = 61;
	//}else if(lev <= 100){
	//	beginFloor = 81;
	//}else if(lev <= 120){
	//	beginFloor = 101;
	//}

	CCMD3B4 cmd;
	cmd.a_floor = beginFloor;

	int hasGold = RoleManage::Instance()->accountInfo()->gold();
	if(hasGold >= m_enterNeedGold)
	{
		cmd.b_isPay = 1;
		GameServerSocket::getInstance()->sendMessage(&cmd);
		//_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_APPLY_CLIMB_TOWER, cmd);
	enterTowerFight2();
	}
	else
	{
		//Alert.show(LangManager.getText("TWR029"));
		LangManager::msgShow("TWR029");
	}
	//remove自己
	Confirm* pConfirm = (Confirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
}



void TowerView::clickCloseHandler(CCObject* pSender)
{
	//
	//CCMD410 cmd;
	//cmd.a_isGUA = 0;
	//GameServerSocket::getInstance()->sendMessage(&cmd);
	////这里需要同步
	//LayerManager::loadingPic->socketWait( WMSG_DUNGEON_GUA, 0, 0);

	g_pGlobalManage->setTowerGUA(0);

	PopContainer::clickCloseHandler(0);
}