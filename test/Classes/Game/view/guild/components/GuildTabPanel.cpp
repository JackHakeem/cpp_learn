#include "GuildTabPanel.h"
#include "MemberPanel.h"
#include "VerifyPanel.h"
#include "TechPanel.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "GuildDispatcher.h"
#include "GuildEventConst.h"
#include "manager/ViewManager.h"

const float FontSize2 = 24.0f;

GuildTabPanel::GuildTabPanel()
{
	_curTab = 0;
	_curPanel = 0;
	_dispatcher = 0;
	_panelIndex = 0;
	_memberPanel = 0;
	_techPanel = 0;
	_verifyPanel = 0;
}

GuildTabPanel::~GuildTabPanel()
{
	//if (ViewManager::getInstance()->guildView)
	//{
	//	ViewManager::getInstance()->guildView->_tabPanel = 0;
	//}
}

bool GuildTabPanel::init()
{
	if (!LayerNode::init())
		return false;

	_dispatcher = GameDispatcher::getInstance();
	_guildDispatcher = GuildDispatcher::getInstance();
	initView();
	return true;
}

void GuildTabPanel::initView()
{
	_memberPanel = new MemberPanel();
	_memberPanel->init();
	this->addChild(_memberPanel,10);
	_memberPanel->release();
	_memberPanel->setIsVisible(false);

	_techPanel = new TechPanel();
	_techPanel->init();
	this->addChild(_techPanel);
	_techPanel->release();
	_techPanel->setIsVisible(false);

	_verifyPanel = new VerifyPanel();
	_verifyPanel->init();
	this->addChild(_verifyPanel);
	_verifyPanel->release();
	_verifyPanel->setIsVisible(false);

	//tab_btn
	{
		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_guild-1);//TLE::WindowLayer_Arena-1
		this->addChild(buttonMenu, GuildTabPanelZ_tabbtn, GuildTabPanelTAG_tabbtn);	
		for (int i = 1; i <= 4; i++)
		{
			//char tab_btn[50];
			//sprintf(tab_btn, "assets/ui/tab.png", i);
			CCMenuItemSprite *_btn = CCMenuItemImage::itemFromNormalSprite(
				CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
				CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
				CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
				this, 
				menu_selector(GuildTabPanel::onTabChange) );
			_btn->setPosition(ccp(POSX(250+160*(i-1)), POSX(640-30)));
			_btn->setTag(i);
			if (i == 1)
				_curTab = _btn;
			//if (i==3)
			//	_btn->setIsEnabled(false);//公会科技暂时不能用
			buttonMenu->addChild(_btn, 0, i);

			char strvalue[20];
			sprintf(strvalue, "GUILD01%d", i);
			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString(strvalue).c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
			pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
			_btn->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(255, 209, 153));	
		}	
	}
	//
	_curPanel = _memberPanel;
}

void GuildTabPanel::popOutPreView()
{
	int tmp = 1;
	_dispatcher->dispatchEvent(PopEventName::SHOW_UI_GUILD, &tmp);
}

void GuildTabPanel::onTabChange(CCObject* pSender)
{
	//if (!_curPanel)
	//	return;
	CCMenuItemImage* currentTarget = (CCMenuItemImage*)pSender;
	int tag = currentTarget->getTag();

	if (tag == 4)
	{
		popOutPreView();
		//_curTab->dispatchEvent(new MouseEvent(MouseEvent.CLICK));
		return;		
	}
	_curTab->setIsEnabled(true);
	_curTab = currentTarget;
	_curTab->setIsEnabled(false);
	if (this->_curPanel)
	{
		this->_curPanel->setIsVisible(false);
		//this->_curPanel->removeFromParentAndCleanup(true);
		//this->_curPanel = 0;
	}
	switch(tag)
	{
	case 1:
		{
			//_memberPanel = new MemberPanel();
			//_memberPanel->init();
			//this->addChild(_memberPanel);
			//_memberPanel->release();
			_curPanel->setPosition(ccpAdd(_curPanel->getPosition(), ccp(-1000, 0)));
			_curPanel = _memberPanel;
			_memberPanel->_memberList->moveToPageImmediately(1);
			_curPanel->setPosition(ccp(0, 0));
			_panelIndex = 0;
		}
		break;
	case 2:
		{
			//_techPanel = new TechPanel();
			//_techPanel->init();
			//this->addChild(_techPanel);
			//_techPanel->release();

			_curPanel = _techPanel;
			_curPanel->setPosition(ccp(0, 0));
			_panelIndex = 1;
		}
		break;
	case 3:
		{
			//_verifyPanel = new VerifyPanel();
			//_verifyPanel->init();
			//this->addChild(_verifyPanel);
			//_verifyPanel->release();
			_curPanel->setPosition(ccpAdd(_curPanel->getPosition(), ccp(-1000, 0)));
			_curPanel = _verifyPanel;
			_verifyPanel->_verifyList->moveToPageImmediately(1);
			_curPanel->setPosition(ccp(0, 0));
			_panelIndex = 2;
		}
		break;
	case 4:
		{
			_curPanel = 0;
			_panelIndex = 3;
			popOutPreView();
			return;	//注意此处
		}
		break;
	}
	_curPanel->setIsVisible(true);
	//请求更新当前面板的数据
	struct sdata
	{
		int type;
		int page;
		sdata()
		{
			type = 1;
			page = 1;
		}
	};
	sdata d;
	_guildDispatcher->dispatchEvent(getinitEventConst(), &d);
}

int GuildTabPanel::getinitEventConst()
{
	switch(_panelIndex){
		case 0:
			return GuildEventConst::GUILD_MEMBER_LIST;
			break;
		case 1:
			return GuildEventConst::GUILD_TECH_LIST;
			break;
		case 2:
			return GuildEventConst::GUILD_APPLY_LIST;
			break;
		default:
			return -1;
			break;
	}
}

/**
	* 打开tabPanel 里对外发送初始化当前列表的事件. 
	*/		
void GuildTabPanel::eventON()
{
	onTabChange(_curTab);
	//__skin["_tab1"].dispatchEvent(new MouseEvent(MouseEvent.CLICK));
}

/**
	* 返回当前面板, 可获取面板继承的基类的公共方法
	* @return 
	*/		
BaseListPanel* GuildTabPanel::getcurrentPanel()
{
	return _curPanel;
}

//CC_PROPERTY(MemberVo, _myMemberInfo, myMemberInfo)

MemberVo GuildTabPanel::getmyMemberInfo()
{
	return _myMemberInfo;
}
		
void GuildTabPanel::setmyMemberInfo(MemberVo vo)
{
	_myMemberInfo = vo;
	//_memberPanel->setmyMemberInfo(vo);
	//_verifyPanel->setmyMemberInfo(vo);
}

/**
	* 返回面板索引 
	* @return 
	*/		
int GuildTabPanel::getpanelIndex()
{
	return _panelIndex;
}