#include "TechPanel.h"
#include "utils/ScaleUtil.h"

#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "GuildDispatcher.h"
#include "GuildEventConst.h"
#include "CCUIBackground.h"
#include "model/guild/vo/TechVo.h"
#include <cmath>
#include "manager/LayerManager.h"
#include "MemberPanel.h"
#include "socket/command/c1d/CCMD1D5.h"
#include "socket/network/GateServerSocket.h"
#include "view/guild/components/DonateView.h"
#include "view/guild/GuildListenerMediator.h"#include "model/guild/vo/TechVo.h"
#include "utils/ValuesUtil.h"
#include "socket/command/c1c/CCMD1C4.h"

const float FontSize2 = 30.0f;
static const int Tag_BtnDefault = 200;

TechPanel::TechPanel()
{
	for(int i=0; i<10; i++)
	{
		_items[i] = 0;
	}
	picBg = 0;
	_curItemIndex = 1;
	hasInit = false;
	_curVo = 0;
}

TechPanel::~TechPanel()
{
	for (int i = 0; i < _arrVo.size(); i++)
	{
		TechVo* vo = _arrVo[i];
		CC_SAFE_DELETE(vo);
	}
	_arrVo.clear();
}

bool TechPanel::init()
{
	if (!LayerNode::init())
		return false;

	_guildDispatch = GuildDispatcher::getInstance();
	//CCLayerColor* pColor = CCLayerColor::layerWithColorWidthHeight(ccc4(0,0,255,100),
	//	this->getContentSize().width, this->getContentSize().height);
	//this->addChild(pColor);
	int offsetY = 50;

	picBg = new CCUIBackground();
	picBg->initWithSpriteFrame( "ui.png",
		ccp(POSX(369), POSX(170+offsetY)),
		ccp(POSX(0),POSX(0)), CCSizeMake( POSX(100), POSX(100) ) );
	this->addChild( picBg );
	picBg->setAnchorPoint(CCPointZero);
	picBg->release();

	for ( int i = 0; i < 10; i++ )
	{
		selectedSpriteImage[i] = new CCUIBackground();
		selectedSpriteImage[i]->initWithSpriteFrame( "ui.png",
			ccp(POSX(350+112*(i%5)), POSX(427-106*(i/5))),
			ccp(POSX(0),POSX(0)), CCSizeMake( POSX(100), POSX(100) ) );
		this->addChild( selectedSpriteImage[i] );
		selectedSpriteImage[i]->setAnchorPoint(CCPointZero);
		selectedSpriteImage[i]->release();
	}
	

	//_btnDonate
	{
		CCSprite *pNormalNewSprite = CCSprite::spriteWithSpriteFrameName("button3_0.png");
		CCSprite *pPressedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_1.png");
		CCSprite *pSelectedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_2.png");
		if(!pNormalNewSprite || !pPressedNewSprite || !pSelectedNewSprite)
		{
			return false;
		}
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalNewSprite,
			pPressedNewSprite,
			pSelectedNewSprite,
			this, 
			menu_selector(TechPanel::onDonateClick) );
		_btn->setPosition(ccp(POSX(635-150), POSX(640-550)));
		_btn->setTag(0);
		_btn->setScale(1.5f);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_guild-2);
		this->addChild(buttonMenu, 1);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("GLD1018").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(255, 209, 153));	
		pLabel->setScale(0.5f);
	}
	//_btnDefault
	{
		CCSprite *pNormalNewSprite = CCSprite::spriteWithSpriteFrameName("button3_0.png");
		CCSprite *pPressedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_1.png");
		CCSprite *pSelectedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_2.png");
		if(!pNormalNewSprite || !pPressedNewSprite || !pSelectedNewSprite)
		{
			return false;
		}
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalNewSprite,
			pPressedNewSprite,
			pSelectedNewSprite,
			this, 
			menu_selector(TechPanel::onDefaultClick) );
		_btn->setPosition(ccp(POSX(635+150), POSX(640-550)));
		_btn->setTag(0);
		_btn->setScale(1.5f);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_guild-2);
		this->addChild(buttonMenu, 1);
		buttonMenu->setTag(Tag_BtnDefault);

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("GLD1017").c_str(),
			CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(255, 209, 153));	
		pLabel->setScale(0.5f);
	}
	
	
	//等级
	{
		_techName = CCLabelTTF::labelWithString(
			"",
			CCSizeMake(POSX(126), POSX(24)), CCTextAlignmentLeft, "Arial", POSX(24));
		_techName->setAnchorPoint(ccp(0, 0));
		_techName->setPosition(ccp(POSX(474), POSX(235+offsetY)));
		this->addChild(_techName, 1);
		_techName->setColor(ccc3(233, 211, 24));

		_techLev = CCLabelTTF::labelWithString(
			"", 
			CCSizeMake(POSX(200), POSX(24)), CCTextAlignmentLeft, "Arial", POSX(24));
		_techLev->setAnchorPoint(ccp(0, 0));
		_techLev->setPosition(ccp(POSX(474+130), POSX(235+offsetY)));
		this->addChild(_techLev, 1);
		_techLev->setColor(ccWHITE);
	}

	//进度条上面的文字
	{
		// success rate bar
		CCSprite* spBgProgress = CCSprite::spriteWithSpriteFrameName("streng/expBg.png");
		spBgProgress->setPosition(ccp(POSX(474), POSX(197-7+offsetY)));
		spBgProgress->setAnchorPoint( CCPointZero );
		this->addChild( spBgProgress );
		_rateBar = CCSprite::spriteWithSpriteFrameName( "streng/up.png" );
		_rateBar->setPosition( ccp( POSX(2), POSX(9) ) );
		_rateBar->setAnchorPoint( CCPointZero );
		spBgProgress->addChild( _rateBar );
		_rateBar->setScaleX( 100 * 0.01f );

		_techRate = CCLabelTTF::labelWithString(
			"",
			CCSizeMake(POSX(319), POSX(24)), CCTextAlignmentCenter, "Arial", POSX(24));
		_techRate->setAnchorPoint(ccp(0, 0));
		_techRate->setPosition(ccp(POSX(474), POSX(197+offsetY)));
		this->addChild(_techRate, 1);
		_techRate->setColor(ccYELLOW);
	}

	//科技升级提示文字
	{
		_techPrompt = CCLabelTTF::labelWithString(
			"",
			CCSizeMake(POSX(330), POSX(17)), CCTextAlignmentLeft, "Arial", POSX(17));
		_techPrompt->setAnchorPoint(ccp(0, 0));
		_techPrompt->setPosition(ccp(POSX(474), POSX(167+offsetY)));
		this->addChild(_techPrompt, 1);
		_techPrompt->setColor(ccWHITE);
	}

	{
		_techTips = CCLabelTTF::labelWithString(
			"",
			CCSizeMake(POSX(420), POSX(17*2+5)), CCTextAlignmentLeft, "Arial", POSX(17));
		_techTips->setAnchorPoint(ccp(0, 0));
		_techTips->setPosition(ccp(POSX(474), POSX(167-(197-167)-20+offsetY)));
		this->addChild(_techTips, 1);
		_techTips->setColor(ccWHITE);
	}

	m_selectedSpriteImageUp = new CCUIBackground();
	m_selectedSpriteImageUp->initWithSpriteFrame( "train/gold_back.png",
		ccpAdd( ccp(0, POSX(2)), selectedSpriteImage[0]->getPosition() ),
		CCPointZero, CCSizeMake( POSX(100), POSX(100) ) );
	this->addChild( m_selectedSpriteImageUp );
	m_selectedSpriteImageUp->setAnchorPoint(CCPointZero);
	m_selectedSpriteImageUp->release();
	
	this->setIsTouchEnabled(true);
	
	return true;

}

void TechPanel::onDonateClick(CCObject* pSender)
{
	//打开成员查看列表
	DonateView* _donateView = (DonateView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_donateview);
	if (!_donateView && _curVo)
	{
		_donateView = new DonateView();
		_donateView->init(_curVo->id);
		LayerManager::intervalLayer->addChild(_donateView, IntervalLayer::IntervalLayerZ_guild_donateview, IntervalLayer::IntervalLayerTAG_guild_donateview);
		_donateView->release();
		_donateView->setIsVisible(false);//等收到SCMD1D6再出现
		g_pGuildListenerMediator->applyDonateViewData(0, 0);//向服务端请求捐献银币界面数据
		_donateView->addEventListener(GuildEventConst::DONATE_MONEY, g_pGuildListenerMediator, callfuncND_selector(GuildListenerMediator::donateHandler));
	}
}

void TechPanel::onDefaultClick(CCObject* pSender)
{
	CCMD1C4 cmd;
	cmd.a_scienceId = _curVo->id;
	//request change default technical
	_guildDispatch->dispatchEvent(GuildEventConst::DEGAULT_TECH_CHANGE, (void*)&cmd);
	for(int i=0; i<(int)_arrVo.size(); i++)
	{
		TechVo* vo = _arrVo[i];
		if(vo->isDefault)
		{
			vo->isDefault = false;
			//_voToItem[vo]["_default"].visible = false;
		}
	}
	_curVo->isDefault = true;
	CCMenu* _btnSetDefault = (CCMenu*)this->getChildByTag(Tag_BtnDefault);
	if (_btnSetDefault)
	{
		_btnSetDefault->setIsVisible(false);
	}

	string tmpStr = _curVo->isDefault?( LangManager::getText("GLD055") + "\n" ):string("");
	tmpStr =  tmpStr+_curVo->des;
	_techTips->setString(tmpStr.c_str());
	//setDefaultIconBg();
}

TechVo* TechPanel::getcurVo()
{
	return 0;
	//return _itemToVo[curItem];

}

/**
* 设置成员列表数据 
* @param listDatas 
*/	
void TechPanel::updateList(std::list<GuildVoBase*>& listDatas)
{
	for (int i = 0; i < _arrVo.size(); i++)
	{
		TechVo* vo = _arrVo[i];
		CC_SAFE_DELETE(vo);
	}
	_arrVo.clear();

	//_arrVo = listDatas;
	std::list<GuildVoBase*>::iterator it;
	int index = 0;
	for ( it = listDatas.begin(); it != listDatas.end(); it++)
	{
		if (index>=9)
		{
			break;
		}
		TechVo* vo = (TechVo*)(*it);
		if ( vo->id == 905 )
		{
			continue;
		}
		_arrVo.push_back(vo);
		if (_items[index])
		{
			_items[index]->removeFromParentAndCleanup(true);

			_items[index] = 0;
		}
		if (!_items[index])
		{
			_items[index] = new CCSprite;
			_items[index]->initWithSpriteFrameName(vo->icon.c_str());
			_items[index]->setAnchorPoint(CCPointZero);
			_items[index]->setPosition(ccp(POSX(11),POSX(11)));
			selectedSpriteImage[index]->addChild(_items[index]);
			_items[index]->release();
		}
		index++;
	}
	//reflectionItemToVo();
	if(!hasInit)
	{
		it = listDatas.begin();
		_curVo = (TechVo*)*it;
		_curItemIndex = 0;
	}
	else
	{
		if ( _curItemIndex < _arrVo.size() )
		{
			_curVo = _arrVo[_curItemIndex];
		}
	}
	if (_curVo->isDefault)
	{
		CCMenu* _btnSetDefault = (CCMenu*)this->getChildByTag(Tag_BtnDefault);
		if (_btnSetDefault)
		{
			_btnSetDefault->setIsVisible(false);
		}
	}
	onItemClick(0);
	hasInit = true;
}

void TechPanel::onItemClick(CCObject* obj)
{
	//curItem.gotoAndStop("up");
	//var item:MovieClip = e.currentTarget as MovieClip;
	//item.gotoAndStop("selected");
	//_curItemIndex = int(item.name.charAt(item.name.length-1));
	//updateIcon(_items[0], curVo);
	//updateText();
	if (!_curVo)
	{
		return;
	}

	CCSprite* picTech = (CCSprite*)picBg->getChildByTag(1001);
	if (picTech)
	{
		picTech->removeFromParentAndCleanup(true);
		picTech = 0;
	}
	if (!picTech)
	{
		CCSprite* picTech = new CCSprite;
		picTech->initWithSpriteFrameName(_curVo->icon.c_str());
		picTech->setAnchorPoint(CCPointZero);
		picTech->setPosition(ccp(POSX(11),POSX(11)));
		picTech->setTag(1001);
		picBg->addChild(picTech);
		picTech->release();
	}

	_techName->setString(_curVo->name.c_str());
	char tmp[54];
	sprintf(tmp, ValuesUtil::Instance()->getString("RCR008").c_str(), _curVo->level);
	_techLev->setString(tmp);
	sprintf(tmp, "%d / %d", _curVo->moneyHave, _curVo->moneyNeed);
	_techRate->setString(tmp);

	_rateBar->setScaleX( (float)_curVo->moneyHave / (float)_curVo->moneyNeed );//rate bar

	if(_curVo->level>99) 
	{
		string str = _curVo->name + LangManager::getText("GLD053");
		_techPrompt->setString(str.c_str());
	}
	else
	{
		string str = _curVo->name
			+ LangManager::getText("GLD054", (_curVo->level+1), (_curVo->moneyNeed-_curVo->moneyHave));
		_techPrompt->setString(str.c_str());
	}

	string tmpStr = _curVo->isDefault?( LangManager::getText("GLD055") + "\n" ):string("");
	tmpStr =  tmpStr+_curVo->des;
	_techTips->setString(tmpStr.c_str());

	if (_curVo->isDefault)
	{
		CCMenu* _btnSetDefault = (CCMenu*)this->getChildByTag(Tag_BtnDefault);
		if (_btnSetDefault)
		{
			_btnSetDefault->setIsVisible(false);
		}
	}
	else
	{
		CCMenu* _btnSetDefault = (CCMenu*)this->getChildByTag(Tag_BtnDefault);
		if (_btnSetDefault)
		{
			_btnSetDefault->setIsVisible(true);
		}
	}

	m_selectedSpriteImageUp->setPosition( ccpAdd( ccp(0, 2),selectedSpriteImage[_curItemIndex]->getPosition() )  );
}

void TechPanel::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_guild-2, true);
}

bool TechPanel::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	for(int i=0; i<10; i++)
	{
		if (!_items[i])
		{
			break;
		}
		CCPoint itemPoint = getScreenPos(selectedSpriteImage[i]);
		CCSize itemSize = selectedSpriteImage[i]->getContentSize();
		CCPoint locationInView = pTouch->locationInView(pTouch->view());
		CCPoint currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
		if ( CCRect::CCRectContainsPoint(CCRectMake(itemPoint.x,itemPoint.y, itemSize.width,itemSize.height), currentTouchPoint) )
		{
			return true;
		}
	}
	return false;
}

void TechPanel::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	for(int i=0; i<10; i++)
	{
		if (!_items[i])
		{
			break;
		}
		CCPoint itemPoint = getScreenPos(selectedSpriteImage[i]);
		CCSize itemSize = selectedSpriteImage[i]->getContentSize();
		CCPoint locationInView = pTouch->locationInView(pTouch->view());
		CCPoint currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
		if ( CCRect::CCRectContainsPoint(CCRectMake(itemPoint.x,itemPoint.y, itemSize.width,itemSize.height), currentTouchPoint) )
		{
			_curVo = _arrVo[i];
			_curItemIndex = i;
			onItemClick(0);
		}
	}

}