#include "FListItem.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "FriendView.h"
#include "manager/ViewManager.h"
#include "FPContainer.h"
#include "FItemCheck.h"
#include "manager/LayerManager.h"
#include "FriendEventConst.h"
#include "manager/TouchLayerEnum.h"
#include "view/mainUI/PlayerMediator.h"
#include "manager/CDManage.h"
#include "manager/LangManager.h"
#include "view/chat/ChatMediator.h"
#include "view/chat/components/ChatPopContainer.h"
#include "manager/PopManage.h"

const float w_frame = 886.0f/2;
const float w_interval = 4.0f;
const float h_frame = 84.0f;
const float h_interval = 4.0f;
FListItem::FListItem()
{
	lastZhengliTime = 0;
}

FListItem::~FListItem()
{}

void FListItem::init(FriendInfoVo info, int32 btnCategory, int32 tag)
{
	_friendInfo = info;
		
	//this->setIsRelativeAnchorPoint(true);
    this->setAnchorPoint(ccp(0,0));

	//CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	//
	CCUIBackground* frame = new CCUIBackground();
	frame->initWithSpriteFrame("popuibg/bg2.png", 
		ccp(0,0),
		ccp(0,0),
		CCSizeMake(POSX(w_frame-w_interval), POSX(h_frame-h_interval)));
	this->addChild(frame, FListItemZ_frame, FListItemTAG_frame);
	//Doyang 20120712
	frame->release();

	this->setContentSize(CCSizeMake(POSX(900), POSX(100)));
	this->setvisibleSize(this->getContentSize());

	//
	float posx = (tag%2==0)?0.0f:w_frame;
	float posy = (h_frame + 6) *(4 - tag/2);
	this->setPosition(ccp(POSX(posx), POSX(posy)));

	setbtnIndex(btnCategory);
	//_btn_fight
	CCSprite *pFightNormalSprite = CCSprite::spriteWithSpriteFrameName("friend/fight.png");
	CCSprite *pFightPressedSprite = CCSprite::spriteWithSpriteFrameName("friend/fight.png");
	CCMenuItemSprite *_btn_fight = CCMenuItemSprite::itemFromNormalSprite(
		pFightNormalSprite,
		pFightPressedSprite,
			this, 
			menu_selector(FListItem::applyFight) );
		_btn_fight->setPosition(ccp(POSX(w_frame- 130) -_btn_fight->getContentSize().width/2, 
			_btn_fight->getContentSize().height/2 + POSX(10)));

		CCMenu *buttonMenu_btn_fight = new CCMenu();
		buttonMenu_btn_fight->init();
		buttonMenu_btn_fight->addChild(_btn_fight, 0, 0);
		buttonMenu_btn_fight->setPosition(ccp(0, 0));
		buttonMenu_btn_fight->setTouchLayer(TLE::WindowLayer_FriendTmpBTN);//TLE::WindowLayer_Friend-1
		this->addChild(buttonMenu_btn_fight, FriendViewZ_fight, FriendViewTAG_fight);
		buttonMenu_btn_fight->release();	
		if (_friendInfo.OF)
		{
			buttonMenu_btn_fight->setIsVisible(false);//不可见
		}

		//查看
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(!pNormalSprite || !pPressedSprite)
		{
			return;
		}
		CCMenuItemSprite *_btn_check = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite, 
			this, 
			menu_selector(FListItem::applyCheck) );
		_btn_check->setPosition(ccp(
			POSX(w_frame - 6)-_btn_check->getContentSize().width/2,// -50
			_btn_check->getContentSize().height - POSX(10)));

		_btn_check->setScaleX(0.8f);//规模

		CCMenu *buttonMenu_btn_check = new CCMenu();
		buttonMenu_btn_check->init();
		buttonMenu_btn_check->addChild(_btn_check, 0, 0);
		buttonMenu_btn_check->setPosition(ccp(0, 0));
		buttonMenu_btn_check->setTouchLayer(TLE::WindowLayer_FriendTmpBTN);
		this->addChild(buttonMenu_btn_check, FriendViewZ_check, FriendViewTAG_check);
		buttonMenu_btn_check->release();	
		
		CCLabelTTF* pLable_btn_check = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI004").c_str(),
			CCSizeMake(POSX(200), POSX(20)),
			CCTextAlignmentCenter,
			"Arial",
			POSX(20));
		pLable_btn_check->setPosition(ccp(_btn_check->getContentSize().width/2, _btn_check->getContentSize().height/2));
		_btn_check->addChild(pLable_btn_check, 2);
		pLable_btn_check->setColor(ccc3(254, 189, 0));
		pLable_btn_check->setScaleX(1.2f);
		if (_friendInfo.OF)
		{
			//buttonMenu_btn_check->setIsVisible(false);//不可见
		}

		//name
		CCLabelTTF* pLable_btn_name = CCLabelTTF::labelWithString(_friendInfo.name.c_str(),
			CCSizeMake(POSX(200), POSX(20)),
			CCTextAlignmentLeft,
			"Arial",
			POSX(20));
		pLable_btn_name->setPosition(ccp(pLable_btn_check->getPosition().x + POSX(120.0f), 
			pLable_btn_check->getPosition().y + POSX(30.0f)));
		_friendInfo.OF?pLable_btn_name->setColor(ccc3(124, 124, 124)):pLable_btn_name->setColor(ccc3(254, 189, 0));
		this->addChild(pLable_btn_name, FriendViewZ_name, FriendViewTAG_name);


		//等级两个字
		CCLabelTTF* pLable_btn_lvname = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI005").c_str(),
			CCSizeMake(POSX(200), POSX(20)),
			CCTextAlignmentLeft,
			"Arial",
			POSX(20));
		pLable_btn_lvname->setPosition(ccp( pLable_btn_check->getPosition().x + POSX(120.0f),
			pLable_btn_check->getPosition().y ));
		pLable_btn_lvname->setColor(ccc3(254, 189, 0));
		this->addChild(pLable_btn_lvname, FriendViewZ_lvname, FriendViewTAG_lvname);

		//等级
		char tmplvstr[30];
		sprintf(tmplvstr, "%d%s", _friendInfo.level, ValuesUtil::Instance()->getString("FRI006").c_str());
		CCLabelTTF* pLable_btn_lv = CCLabelTTF::labelWithString(tmplvstr,
			CCSizeMake(POSX(200), POSX(20)),
			CCTextAlignmentLeft,
			"Arial",
			POSX(20));
		pLable_btn_lv->setPosition(ccp( pLable_btn_check->getPosition().x + POSX(170.0f),
			pLable_btn_check->getPosition().y));
		_friendInfo.OF?pLable_btn_lv->setColor(ccc3(124, 124, 124)):pLable_btn_lv->setColor(ccc3(255, 255, 255));
		this->addChild(pLable_btn_lv, FriendViewZ_lv, FriendViewTAG_lv);

		//sex
		CCSprite* sex = new CCSprite();//如果不在线则跳到下两帧灰色图标
		char tmpsexstr[80];
		sprintf(tmpsexstr, "friend/%d.png", _friendInfo.OF?_friendInfo.sex+2:_friendInfo.sex);
		sex->setScale(0.8f);
		sex->initWithSpriteFrameName(tmpsexstr);
		this->addChild(sex, FriendViewZ_sex, FriendViewTAG_sex);
		sex->setPosition(ccp( pLable_btn_check->getPosition().x + -POSX(20.0f),
			pLable_btn_check->getPosition().y + POSX(18.0f)));

	//
	if (btnCategory == 0)
	{

	}
	else if (btnCategory == 1)
	{

	}
	else if (btnCategory == 3)
	{

	}
}

void FListItem::moveFriendOut(CCObject* pSender)
{
	struct sdata
	{
		std::string name;
		int32 position;
	};
	sdata d;
	d.name = this->_friendInfo.name;
	d.position = this->getTag();
	list()->dispatchEvent(FriendEventConst::MOVE_FRIEND_OUT, &d);
	//
	FItemCheck* pFC = (FItemCheck*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_friendCheck);
	if (pFC)
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_friendCheck, true);	
}

void FListItem::privateChat(CCObject* pSender)
{
	g_pPopManage->handleCloseHandler();

	FItemCheck* pFC = (FItemCheck*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_friendCheck);
	if (pFC)
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_friendCheck, true);


	ChatMediator* p = (ChatMediator*)g_pFacade->retrieveMediator(AppFacade_CHAT_CHANGE);
	if (p)
	{
		p->showChatViewHandler();
		if (p->_chatPopContainer)
		{
			p->_chatPopContainer->setPrivateChat(this->_friendInfo.name);
		}
	}	
}

void FListItem::applyRemove(CCObject* pSender)
{
	//
	FItemCheck* pFC = (FItemCheck*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_friendCheck);
	if (pFC)
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_friendCheck, true);
}

void FListItem::addPlayer(CCObject* pSender)
{
	//list.dispatchEvent(new ParamEvent(FriendEventConst.ADD_FRIEND, firendInfo));
	list()->_fpContainer->quickAddFriHandler(&_friendInfo);
	//
	FItemCheck* pFC = (FItemCheck*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_friendCheck);
	if (pFC)
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_friendCheck, true);	
}

void FListItem::moveToBlack(CCObject* pSender)
{
	list()->dispatchEvent(FriendEventConst::MOVE_TO_BLACK, &(this->_friendInfo.name));
	//
	FItemCheck* pFC = (FItemCheck*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_friendCheck);
	if (pFC)
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_friendCheck, true);
}

void FListItem::delPlayer(CCObject* pSender)
{
	list()->dispatchEvent(FriendEventConst::DEL_FRIEND, &(this->_friendInfo.name));
	//
	FItemCheck* pFC = (FItemCheck*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_friendCheck);
	if (pFC)
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_friendCheck, true);
}


void FListItem::applyFight(CCObject* pSender)
{
	if (CDManage::Instance()->getServerTime() - lastZhengliTime > 8000)
	{
		lastZhengliTime = CDManage::Instance()->getServerTime();	
	}
	else
	{
		LangManager::msgShow("FRI021");
		return;
	}


	PkParm parm;
	parm.id = _friendInfo.id;
	parm.lev = _friendInfo.level;
	parm.noLev = 2; // not defined;

	PlayerMediator* m = (PlayerMediator*)g_pFacade->retrieveMediator(AppFacade_PLAYER_MEDIATOR);
	if(m)
		m->playerPk((char*)&parm);


}

void FListItem::applyCheck(CCObject* pSender)
{
	FItemCheck* pFC = (FItemCheck*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_friendCheck);
	if (pFC)
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_friendCheck, true);

	pFC = new FItemCheck();
	pFC->initWithParam(this, getbtnIndex());
	LayerManager::tipsLayer->addChild(pFC, TipsLayer::TipsLayerZ_friendCheck, TipsLayer::TipsLayerTAG_friendCheck);
	pFC->release();

	
}



FriendView* FListItem::list()
{
	FriendView* fv = ViewManager::getInstance()->friendView;
	if (fv)
	{
		return fv;
	}
	return 0;
}

//CC_PROPERTY(int32, _btnIndex, btnIndex)
void FListItem::setbtnIndex(int32 index)
{
	_btnIndex = index;
}

int32 FListItem::getbtnIndex()
{
	return _btnIndex;
}