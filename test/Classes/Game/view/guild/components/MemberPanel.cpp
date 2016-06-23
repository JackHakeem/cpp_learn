#include "MemberPanel.h"
#include "GuildDispatcher.h"
#include "GuildEventConst.h"
#include "PageNav.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "ListMenu.h"
#include "manager/LayerManager.h"
#include "manager/LangManager.h"
#include "GuildTabPanel.h"
#include "Confirm.h"
#include "model/newhand/NewhandManager.h"
#include "socket/command/c1c/CCMD1CA.h"

const float FontSize3 = 24.0f;

MemberPanel::MemberPanel()
{
	m_tmp_duty2CCMD1B9 = 0;
	_memberList = 0;
}

MemberPanel::~MemberPanel()
{}

bool MemberPanel::init()
{
	if (!LayerNode::init())
		return false;

	_guildDispatcher = GuildDispatcher::getInstance();
	initBackground();
	initBody();
	_memberList->m_pri = TLE::WindowLayer_guild-1;
	return true;
}

void MemberPanel::initBackground()
{
	_pageNav = new PageNav();
	_pageNav->init();
	_pageNav->addEventListener(PageNav::PAGE_CHANGE, this, callfuncND_selector(MemberPanel::onPageChange)); 
	this->addChild(_pageNav, 1, 99);
}
//
//MemberVo MemberPanel::getmyMemberInfo()
//{
//	return _myMemberInfo;
//}
//		
//void MemberPanel::setmyMemberInfo(MemberVo vo)
//{
//	_myMemberInfo = vo;
//}

void MemberPanel::initBody()
{
	_memberList = CommonList::commonListScrollViewWithCCRect(CCRectMake(POSX(335), POSX(640-550), POSX(920-335), POSX(430)));
	//_memberList->addEventListener(GuildEventConst.MEMBER_ITEM_CLICK, onListItemClick);弹出T人，升级个D野
	this->addChild(_memberList);
	_memberList->release();
	//
	float titleoffsetX = 338.0f;
	//职位
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD081").c_str(), CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(0+titleoffsetX), POSX(640-124)));
		this->addChild(pLabel);
		pLabel->setColor(ccc3(255, 209, 153));		
	}
	//姓名
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD082").c_str(), CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(90+titleoffsetX), POSX(640-124)));
		this->addChild(pLabel);
		pLabel->setColor(ccc3(255, 209, 153));		
	}
	//等级
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD083").c_str(), CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(180+titleoffsetX), POSX(640-124)));
		this->addChild(pLabel);
		pLabel->setColor(ccc3(255, 209, 153));		
	}
	//贡献度
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD084").c_str(), CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(270+titleoffsetX), POSX(640-124)));
		this->addChild(pLabel);
		pLabel->setColor(ccc3(255, 209, 153));		
	}
	////称号
	//{
	//	CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD085").c_str(), CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
	//	pLabel->setAnchorPoint(ccp(0, 0));
	//	pLabel->setPosition(ccp(POSX(30), POSX(640-124)));
	//	this->addChild(pLabel);
	//	pLabel->setColor(ccc3(255, 209, 153));		
	//}
	//状态
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD086").c_str(), CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(360+titleoffsetX), POSX(640-124)));
		this->addChild(pLabel);
		pLabel->setColor(ccc3(255, 209, 153));		
	}
}

/**
	* 设置分页, 外部接口 
	* @param max
	* @param index
	*/		
void MemberPanel::setPage(int max, int index)
{
	_pageNav->setPage(max, index);
}
		
/**
	* 设置成员列表数据 
	* @param listDatas
	*/	
void MemberPanel::updateList(std::list<GuildVoBase*>& listDatas)
{
	_memberList->setDatas(listDatas, _pageNav->_curPage);

	sethasInit(true);
}
		

/**
	* 翻页
	* @param event
	* 
	*/
void MemberPanel::onPageChange(CCNode* pSender, void* data)
{
	struct sdata
	{
		uint page;
		int type;

	};
	sdata obj;
	obj.page = *(int*)data;
	obj.type = 1;
	_guildDispatcher->dispatchEvent(GuildEventConst::GUILD_MEMBER_LIST, &obj);
}

/**
	* 更改职务 
	*/		
void MemberPanel::ChangeDuty(int duty)
{
	GuildTabPanel* par = (GuildTabPanel*)this->getParent();
	int dutyID = dutyToId(par->getmyMemberInfo().duty);
	if(dutyID < 4){
		LangManager::msgShow("GLD065");
		return;
	}
	if(dutyToId(_currentMember.duty) == dutyToId(par->getmyMemberInfo().duty))
	{
		char value[100];
		sprintf(value, ValuesUtil::Instance()->getString("GLD068").c_str(), _currentMember.name.c_str(), _currentMember.duty.c_str());
		LangManager::msgStr(value);
		return;
	}
	std::string nextDuty = "";
	switch(duty)
	{
		case ListMenu_ShiftLeader:			//转移会长
			{
				char value[100];
				sprintf(value, ValuesUtil::Instance()->getString("GLD069").c_str(), LangManager::getText("GLD038").c_str(), _currentMember.name.c_str());
				nextDuty = value;
			}
			break;
		case ListMenu_ViceLeader:			//更改职务 -> 副会长
			{
				char value[100];
				sprintf(value, ValuesUtil::Instance()->getString("GLD070").c_str(), _currentMember.name.c_str(), LangManager::getText("GLD039").c_str());
				nextDuty = value;
			}
			break;
		case ListMenu_Officer:					//更改职务 -> 官员
			{
				char value[100];
				sprintf(value, ValuesUtil::Instance()->getString("GLD070").c_str(), _currentMember.name.c_str(), LangManager::getText("GLD058").c_str());
				nextDuty = value;
			}
			break;
		case ListMenu_Member:				//更改职务 -> 会员
			{
				char value[100];
				sprintf(value, ValuesUtil::Instance()->getString("GLD070").c_str(), _currentMember.name.c_str(), LangManager::getText("GLD059").c_str());
				nextDuty = value;
			}
			break;
	}
	m_tmp_duty2CCMD1B9 = duty;
	//弹出确认框
	Confirm* pConfirm = new Confirm();
	//tmp_num = num;
	//tmp_money = money;
	//tmp_sitNum = index;
	pConfirm->initWithParam(nextDuty.c_str(), this, menu_selector(MemberPanel::confirmChangeDuty),menu_selector(MemberPanel::confirmChangeDutyCancel));
	LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
	pConfirm->release();
	//Alert.show(nextDuty, "", 1, confirmChangeDuty, null, Sentence.CONFIRM, Sentence.CANCEL, duty);
}

#include "socket/command/c1b/CCMD1B9.h"
void MemberPanel::confirmChangeDuty(CCObject* pSender)
{
	CCMD1B9 cmd;
	cmd.a_memberName = _currentMember.name;

	int duty = m_tmp_duty2CCMD1B9;

	cmd.b_position = duty;
	_guildDispatcher->dispatchEvent(GuildEventConst::LEADER_SHIF, &cmd);

	//删除确认框
	CCNode* pConfirm = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm)
		pConfirm->removeFromParentAndCleanup(true);
	//删除成员查看列表
	ListMenu* oldp = (ListMenu*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_memberListMenu);
	if (oldp)
		LayerManager::intervalLayer->removeChildByTag(IntervalLayer::IntervalLayerTAG_guild_memberListMenu, true);
}

void MemberPanel::confirmChangeDutyCancel(CCObject* pSender)
{
	//删除确认框
	CCNode* pConfirm = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm)
		pConfirm->removeFromParentAndCleanup(true);
}

/**
	* 弹出菜单响应事件 
	* @param event
	*/		
void MemberPanel::onFuncClick(CCObject* pSender)
{
	CCNode* p = (CCNode*)pSender;
	if (!p)
		return;
	int param = p->getTag();
	switch(param)
	{
		case ListMenu_ShiftLeader:			//转移会长
		case ListMenu_ViceLeader:			//更改职务 -> 副会长
		case ListMenu_Officer:					//更改职务 -> 官员
		case ListMenu_Member:				//更改职务 -> 会员
			ChangeDuty(param);
			break;
		case ListMenu_ExpelledMember:	//开除会员
			{
				expelledMember();
			}
			break;
		case ListMenu_ViewInformation:	//查看信息
			//GameDispatcher.getInstance().dispatchEvent(new ParamEvent(GameDispatcher.SHOW_OTHER_FIGURE, {id:_currentMember.id, name:_currentMember.name}));
			break;
		case ListMenu_PrivateChat:		//发起私聊
			//GameDispatcher.getInstance().dispatchEvent(new ParamEvent(GameDispatcher.PRIVATE_CHAT, _currentMember.name));
			break;
		case ListMenu_AddFriend:				//添加好友
			//_guildDispatcher.dispatchEvent(new ParamEvent(GuildEventConst.ADD_FRIEND, _currentMember.name));
			break;
		case ListMenu_InviteToTeam:		//邀请组队
			//_guildDispatcher.dispatchEvent(new ParamEvent(GuildEventConst.INVITE_TEAM, _currentMember.id));
			break;
		case ListMenu_CopyName:			//复制名称
			//System.setClipboard(_currentMember.name);
			break;
	}
}

void MemberPanel::onListItemClick(CCObject* pSender)
{
	CCNode* p = (CCNode*)pSender;
	int itemtag = p->getTag();

	int index = 0;
	for (std::list<GuildVoBase*>::iterator it = _memberList->_itemArr.begin(); it != _memberList->_itemArr.end(); it++,index++)
	{
		if (index == itemtag)
		{
			_currentMember = *(MemberVo*)*it;
			break;
		}
	}
	
	//打开成员查看列表
	ListMenu* oldp = (ListMenu*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_memberListMenu);
	if (!oldp)
	{
		oldp = new ListMenu();
		oldp->init(this);
		LayerManager::intervalLayer->addChild(oldp, IntervalLayer::IntervalLayerZ_guild_memberListMenu, IntervalLayer::IntervalLayerTAG_guild_memberListMenu);
		oldp->release();

		//如果还没开启好友功能，则禁用“加为好友”菜单
		bool isFriendOpen = NewhandManager::Instance()->isOpenButton(6);
		if (!isFriendOpen)
		{
			//this.itemEnableByName(isFriendOpen, "AddFriend");
		}
		
		//如果点击的是自己，则禁用所有菜单条目
		GuildTabPanel* par = (GuildTabPanel*)this->getParent();
		oldp->itemEnableAll(par->getmyMemberInfo().id != _currentMember.id);
	}


}

		
/**
	* 开除会员 
	*/		

void MemberPanel::expelledMember()
{
	GuildTabPanel* par = (GuildTabPanel*)this->getParent();
	int dutyID = dutyToId(par->getmyMemberInfo().duty);
	if(dutyID < 3)
	{	//副会长以下不能T人
		LangManager::msgShow("GLD065");
		return;
	}else if(dutyID==3 && this->_currentMember.dutyValue()==4){
		LangManager::msgShow("GLD066");
		return;
	}

	//弹出确认框
	Confirm* pConfirm = new Confirm();
	char str[80];
	sprintf(str, ValuesUtil::Instance()->getString("GLD067").c_str(), _currentMember.name.c_str());
	std::string stdstr = str;
	pConfirm->initWithParam(stdstr.c_str(), this, menu_selector(MemberPanel::confirmExpelledMember),menu_selector(MemberPanel::confirmExpelledMemberCancel));
	LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
	pConfirm->release();
}

int MemberPanel::dutyToId(std::string duty)
{
	if(duty == ValuesUtil::Instance()->getString("GLD038") || duty == "ShiftLeader") return 4;
	if(duty == ValuesUtil::Instance()->getString("GLD039") || duty == "ViceLeader") return 3;
	if(duty == ValuesUtil::Instance()->getString("GLD058") || duty == "Officer") return 2;
	if(duty == ValuesUtil::Instance()->getString("GLD059") || duty == "Member") return 1;
	return 0;
}
		
/* 确定开除会员的处理 */
void MemberPanel::confirmExpelledMember(CCObject* pSender)
{
	//向服务端请求开除会员
	CCMD1CA cmd;
	cmd.a_pName = _currentMember.name;
	_guildDispatcher->dispatchEvent(GuildEventConst::EXPEL_MEMBER, &cmd);
	//重新请求成员列表
	struct sdata
	{
		uint page;
		int type;
	};
	sdata d;
	d.type = 1;
	d.page = _pageNav->_curPage;
	_guildDispatcher->dispatchEvent(GuildEventConst::GUILD_MEMBER_LIST, &d);
	//删除确认框
	CCNode* pConfirm = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm)
		pConfirm->removeFromParentAndCleanup(true);
	//删除成员查看列表
	ListMenu* oldp = (ListMenu*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_memberListMenu);
	if (oldp)
		LayerManager::intervalLayer->removeChildByTag(IntervalLayer::IntervalLayerTAG_guild_memberListMenu, true);
}

void MemberPanel::confirmExpelledMemberCancel(CCObject* pSender)
{
	CCNode* pConfirm = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm)
		pConfirm->removeFromParentAndCleanup(true);
}
