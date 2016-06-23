#include "manager/PopEventName.h"
#include "GuildView.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "GuildTabPanel.h"
#include "BaseListPanel.h"
#include <cmath>
#include "manager/LayerManager.h"
#include "GuildEditView.h"
#include "KKLabelTTF.h"
#include "GuildDispatcher.h"
#include "GuildEventConst.h"
#include "Confirm.h"
#include "model/guild/GuildManager.h"
#include "model/guild/vo/GuildLevInfo.h"
#include "model/player/vo/AccountInfoVo.h"
#include "model/player/RoleManage.h"
#include "CCTextureCache.h"
#include "../GuildListenerMediator.h"
#include "manager/ViewManager.h"
#include "../GuildMediator.h"
#include "control/AppFacade.h"
#include "../GuildMediator.h"

static const int TAG_PARENT = 1001;
static float FontSize = 26.0f;
static float FontSize2 = 20.0f;
static float FontSize3 = 22.0f;

GuildView::GuildView()
{
	_tabPanel = 0;
	_hasInit = false;
}

bool GuildView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	key = PopEventName::GUILD;

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/guild/res_guild.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/guild/res_guild.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/guild/res_guild_o.plist");

	//
	_container = new LayerNode();
	this->addChild(_container, 0, 0);
	this->setContentSize(CCDirector::sharedDirector()->getWinSize());
	this->setPopContentSize(this->getContentSize());
	_container->release();
	//const CCPoint& offsetPix = getOffsetPositionInPixels();
	//Doyang
	//_container->setPosition(ccpAdd(ccp(POSX(-960/2), POSX(-640/2)), POS(ccp(0, 0), ScaleUtil::CENTER)));

	_container->setPosition(POS(ccp(0,0), ScaleUtil::CENTER_TOP));
	_container->setAnchorPoint(CCPointZero);

	initView();

	return true;
}

void GuildView::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate( this, TLE::IntervalLayer_guild, true );
}

bool GuildView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

CCLabelTTF* GuildView::getLabel(int tag)
{
	CCLabelTTF* p = (CCLabelTTF*)_container->getChildByTag(tag);
	return p;
}

/**
	* ��������ڵ�TextField�� value 
	* @return 
	* 
	*/		
void GuildView::setguildInfo(GuildInfoVo& info)
{
	_guildInfo = info;

	char value[100];
	{
		sprintf(value, ValuesUtil::Instance()->getString("GUILD002").c_str(), info.emblemGrade);
		CCLabelTTF* _txtLevel = getLabel(GuildViewTAG_txtLevel);
		_txtLevel->setString(value);		
	}
	{
		CCLabelTTF* _txtName = getLabel(GuildViewTAG_txtName);
		_txtName->setString(info.name.c_str());		
	}
	{
		CCLabelTTF* _txtID = getLabel(GuildViewTAG_txtID);
		_txtID->setString(info.leaderName.c_str());		
	}
	{
		sprintf(value, "%d", info.rank);
		CCLabelTTF* _txtRank = getLabel(GuildViewTAG_txtRank);
		_txtRank->setString(value);		
	}
	{
		sprintf(value, "%d/%d", info.members, info.memberLimit);
		CCLabelTTF* _txtOnline = getLabel(GuildViewTAG_txtOnline);
		_txtOnline->setString(value);		
	}	
	{
		CCLabelTTF* _txtTime = getLabel(GuildViewTAG_txtTime);
		_txtTime->setString(info.ctime.c_str());		
	}
	{
		CCLabelTTF* _txtQQ = getLabel(GuildViewTAG_txtQQ);
		_txtQQ->setString(info.qq.c_str());		
	}
	{
		

		KKLabelTTF* _txtPost = (KKLabelTTF*)_container->getChildByTag(GuildViewTAG_txtPost);
		_txtPost->removeFromParentAndCleanup(true);

		KKLabelTTF* pLabel = new KKLabelTTF();
		pLabel->init(18, 20.0f, CCSizeMake((200), (100)));
		pLabel->setPosition(ccp(POSX(52), POSX(640-462)));
		std::string value = info.notice;
		pLabel->add(value, ccc3(255, 255, 255));
		_container->addChild(pLabel, GuildViewZ_txt, GuildViewTAG_txtPost);
		pLabel->release();
	}

			
	if(_guildInfo.emblemGrade >= 20)
	{
		CCMenu *buttonMenu = (CCMenu*)_container->getChildByTag(GuildViewTAG_btUpgrade);
		if (!buttonMenu) return;
		CCMenuItemImage* _btnUpgrade = (CCMenuItemImage*)buttonMenu->getChildByTag(0);
		if (!_btnUpgrade) return;
		_btnUpgrade->setIsEnabled(false);

		//new TipHelps().setToolTips(_icon, LangManager.getText("GLD045"));
	}
	else
	{
		/*int nextLev = _guildInfo.emblemGrade + 1;
		GuildLevInfo guildLevInfo = GuildManager.getInstance().getGuildLevInfo(_guildInfo.emblemGrade);
		if(!guildLevInfo) return;
		var cost:int = guildLevInfo.needGold;
		new TipHelps().setToolTips(_btnUpgrade, LangManager.getText("GLD046", nextLev, cost));
		new TipHelps().setToolTips(_icon, LangManager.getText("GLD047") + guildLevInfo.incMember);*/
	}
//	_icon.gotoAndStop(Math.ceil(info.emblemGrade / 4));
	changeIcon((int)ceil((double)(info.emblemGrade / 4.0f)));

	sethasInit(true);
	//hasInit = true;
}

void GuildView::setPage(int max, int index)
{
	if(!_tabPanel->getcurrentPanel()) return;
	_tabPanel->getcurrentPanel()->setPage(max, index);
}

bool GuildView::gethasInit()
{
	return _hasInit;
}

void GuildView::sethasInit(bool value)
{
	_hasInit = value;
	updateButton();
	//updateTimeWorkText();
	//this.alpha = 1;
}

void GuildView::updateList(std::list<GuildVoBase*> datas)
{
	if(!_tabPanel->getcurrentPanel()) 
		return;
	_tabPanel->getcurrentPanel()->updateList(datas);
}

int GuildView::getpanelIndex()
{
	return _tabPanel->getpanelIndex();
}

/**
	* �������ѵĹ���INFO 
	* @param info
	*/		
void GuildView::setmyMemberInfo(MemberVo& info)
{
	_myMemberInfo = info;
	_tabPanel->setmyMemberInfo(_myMemberInfo);
	updateButton();
}

MemberVo GuildView::getmyMemberInfo()
{
	return _myMemberInfo;
}
		
void GuildView::eventON()
{
	_tabPanel->eventON();
}

void GuildView::editGuildInfo(CCObject* pSender)//BTN�򿪱༭������Ϣ���?
{
	GuildEditView* oldp = (GuildEditView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_editView);
	if (!oldp)
	{
		oldp = new GuildEditView();
		oldp->init(&_guildInfo);
		LayerManager::intervalLayer->addChild(oldp, IntervalLayer::IntervalLayerZ_guild_editView, IntervalLayer::IntervalLayerTAG_guild_editView);
		oldp->release();
	}
}

void GuildView::exitGuildDispatcher(CCObject* pSender)
{
	//����ȷ�Ͽ�
	Confirm* pConfirm = new Confirm();
	pConfirm->initWithParam(LangManager::getText("GLD1019").c_str(), this, menu_selector(GuildView::sureExitGuild),menu_selector(GuildView::sureExitGuildCancel));
	LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
	pConfirm->release();	
}

void GuildView::sureExitGuildCancel(CCObject* pSender)
{
	//ɾ��ȷ�Ͽ�
	CCNode* pConfirm = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm)
		pConfirm->removeFromParentAndCleanup(true);
}

void GuildView::sureExitGuild(CCObject* pSender)
{
	GuildDispatcher::getInstance()->dispatchEvent(GuildEventConst::EXIT_GUILD, 0);
	//ɾ��ȷ�Ͽ�
	CCNode* pConfirm = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm)
		pConfirm->removeFromParentAndCleanup(true);

	clickCloseHandler(0);
}

void GuildView::abortGuildDispatcher(CCObject* pSender)//BTN�򿪽�ɢ�������?
{
	//����ȷ�Ͽ�
	Confirm* pConfirm = new Confirm();
	pConfirm->initWithParam(LangManager::getText("GLD043").c_str(), this, menu_selector(GuildView::sureAbortGuild),menu_selector(GuildView::sureAbortGuildCancel));
	LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
	pConfirm->release();
}

void GuildView::sureAbortGuild(CCObject* pSender)
{
	GuildDispatcher::getInstance()->dispatchEvent(GuildEventConst::REMOVE_GUILD, 0);
	//ɾ��ȷ�Ͽ�
	CCNode* pConfirm = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm)
		pConfirm->removeFromParentAndCleanup(true);
}

void GuildView::sureAbortGuildCancel(CCObject* pSender)
{
	//ɾ��ȷ�Ͽ�
	CCNode* pConfirm = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm)
		pConfirm->removeFromParentAndCleanup(true);	
}

/**
	* ���¹����������ఴť����״̬ 
	* @param verifyInit �Ƿ���֤��ʼ��
	*/		
void GuildView::updateButton()
{
	//if(!_hasInit || !_myMemberInfo) 
	//	return;
	if (!this->_container)
		return;
	CCNode* _editInfoBtn = (CCNode*)(this->_container->getChildByTag(GuildViewTAG_btnEditInfo));
	CCNode* _btnAbort = (CCNode*)(this->_container->getChildByTag(GuildViewTAG_btnAbort));
	CCNode* _btnCancelAbort = (CCNode*)(this->_container->getChildByTag(GuildViewTAG_btnCancelAbort));
	CCNode* _btnQuit = (CCNode*)(this->_container->getChildByTag(GuildViewTAG_btnQuit));
	
	if (_myMemberInfo.duty == LangManager::getText("GLD038"))
	{
		if (_editInfoBtn)
			_editInfoBtn->setIsVisible(true);
		if (_btnAbort)
			_btnAbort->setIsVisible(!(_guildInfo.state==1 ? true : false));
		if (_btnCancelAbort)
			_btnCancelAbort->setIsVisible(_guildInfo.state==1 ? true : false);		
		if (_btnQuit)
			_btnQuit->setIsVisible(false);
	}
	else if (_myMemberInfo.duty == LangManager::getText("GLD039"))
	{
		if (_editInfoBtn)
			_editInfoBtn->setIsVisible(true);
		if (_btnAbort)
			_btnAbort->setIsVisible(false);
		if (_btnCancelAbort)
			_btnCancelAbort->setIsVisible(false);
		if (_btnQuit)
			_btnQuit->setIsVisible(true);
	}
	else
	{
		if (_editInfoBtn)
			_editInfoBtn->setIsVisible(false);		
		if (_btnAbort)
			_btnAbort->setIsVisible(false);
		if (_btnCancelAbort)
			_btnCancelAbort->setIsVisible(false);
		if (_btnQuit)
			_btnQuit->setIsVisible(true);
	}
}

void GuildView::abortCancelDispatcher(CCObject* pSender)
{
	GuildDispatcher::getInstance()->dispatchEvent(GuildEventConst::REMOVE_GUILD_CANCEL, 0);
}

void GuildView::updateEmblemDispatcher(CCObject* pSender)
{
	int nextLev = _guildInfo.emblemGrade + 1;
	GuildLevInfo* guildLevInfo = GuildManager::Instance()->getGuildLevInfo(_guildInfo.emblemGrade);
	if(!guildLevInfo) return;
	int cost = guildLevInfo->needGold;
	AccountInfoVo& accountInfo = RoleManage::Instance()->_accountInfo;
	if(accountInfo._gold < cost)
	{
		LangManager::msgShow("GLD040");
		return;
	}
	else
	{
		char tipvalue[256];
		sprintf(tipvalue, LangManager::getText("GLD041").c_str(), cost, guildLevInfo->incMember, cost*100, cost*5);
		std::string tip = tipvalue;

		//����ȷ�Ͽ�
		Confirm* pConfirm = new Confirm();
		pConfirm->initWithParam(tip.c_str(), this, menu_selector(GuildView::okFunction),menu_selector(GuildView::okFunctionCancel));
		LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
		pConfirm->release();
	}
}
		
void GuildView::okFunction(CCObject* pSender)
{
	GuildDispatcher::getInstance()->dispatchEvent(GuildEventConst::UPDATE_EMBLEM, 0);
	//ɾ��ȷ�Ͽ�
	CCNode* pConfirm = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm)
		pConfirm->removeFromParentAndCleanup(true);	
}

void GuildView::okFunctionCancel(CCObject* pSender)
{
	//ɾ��ȷ�Ͽ�
	CCNode* pConfirm = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm)
		pConfirm->removeFromParentAndCleanup(true);	
}

CCNode * GuildView::getNewHandItem(int id)
{
	switch (id)
	{
	case 100:
		{

		}
		break;
	case 101:
		{

		}
		break;
	default:
		break;
	}
	return 0;
}

GuildView::~GuildView()
{
	if (ViewManager::getInstance()->guildView)
	{
		ViewManager::getInstance()->guildView = 0;
	}

	if (ViewManager::getInstance()->guildPreView)
	{
		ViewManager::getInstance()->guildPreView = 0;
	}
	
	GuildMediator * pM = (GuildMediator *)g_pFacade->retrieveMediator(AppFacade_GUILD_CHANGE);
	if (pM)
	{
		pM->_view = 0;
	}	

	g_pGuildListenerMediator->_view = 0;

	g_pGuildMediator->_view = 0;

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/guild/res_guild.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/guild/res_guild.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/guild/res_guild_o.plist");

	this->removeAllChildrenWithCleanup(true);

	CCTexture2D* pTex = CCTextureCache::sharedTextureCache()->textureForKey("assets/ui/guild/res_guild.pvr.ccz");
	if (pTex && pTex->retainCount()==1)
		CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/guild/res_guild.pvr.ccz");	

	pTex = CCTextureCache::sharedTextureCache()->textureForKey("assets/icon/guild/res_guild.pvr.ccz");
	if (pTex && pTex && pTex->retainCount()==1)
		CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/icon/guild/res_guild.pvr.ccz");

	pTex = CCTextureCache::sharedTextureCache()->textureForKey("assets/icon/guild/res_guild_o.pvr.ccz");
	if (pTex && pTex->retainCount()==1)
		CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/icon/guild/res_guild_o.pvr.ccz");
}
