#include "VerifyPanel.h"
#include "GuildDispatcher.h"
#include "GuildEventConst.h"
#include "PageNav.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"


const float FontSize3 = 24.0f;

VerifyPanel::VerifyPanel()
{
	_verifyList = 0;
	
}

VerifyPanel::~VerifyPanel()
{}

bool VerifyPanel::init()
{
	if (!LayerNode::init())
		return false;

	_guildDispatcher = GuildDispatcher::getInstance();
	initBackground();
	initBody();
	_verifyList->m_pri = TLE::WindowLayer_guild-1;
	return true;
}

void VerifyPanel::initBackground()
{
	_pageNav = new PageNav();
	_pageNav->init();
	_pageNav->addEventListener(PageNav::PAGE_CHANGE, this, callfuncND_selector(VerifyPanel::onPageChange)); 
	this->addChild(_pageNav, 1, 99);
}

MemberVo VerifyPanel::getmyMemberInfo()
{
	return _myMemberInfo;
}
		
void VerifyPanel::setmyMemberInfo(MemberVo vo)
{
	_myMemberInfo = vo;
}

void VerifyPanel::initBody()
{
	_verifyList = CommonList::commonListScrollViewWithCCRect(CCRectMake(POSX(335), POSX(640-550), POSX(920-335), POSX(430)));
	//_verifyList->addEventListener(GuildEventConst.MEMBER_ITEM_CLICK, onListItemClick);弹出T人，升级个D野
	this->addChild(_verifyList);
	_verifyList->release();
	//
	float titleoffsetX = 338.0f;
	//申请人
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD087").c_str(), CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(386), POSX(640-124)));
		this->addChild(pLabel);
		pLabel->setColor(ccc3(255, 209, 153));		
	}
	//等级
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD089").c_str(), CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(500), POSX(640-124)));
		this->addChild(pLabel);
		pLabel->setColor(ccc3(255, 209, 153));		
	}
	////称号
	//{
	//	CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD090").c_str(), CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
	//	pLabel->setAnchorPoint(ccp(0, 0));
	//	pLabel->setPosition(ccp(POSX(635), POSX(640-124)));
	//	this->addChild(pLabel);
	//	pLabel->setColor(ccc3(255, 209, 153));		
	//}
	//申请时间
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD091").c_str(), CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(635), POSX(640-124)));
		this->addChild(pLabel);
		pLabel->setColor(ccc3(255, 209, 153));		
	}


}


/**
	* 设置分页, 外部接口 
	* @param max
	* @param index
	*/		
void VerifyPanel::setPage(int max, int index)
{
	_pageNav->setPage(max, index);
}
		
/**
	* 设置成员列表数据 
	* @param listDatas
	*/	
void VerifyPanel::updateList(std::list<GuildVoBase*>& listDatas)
{
	_verifyList->setDatas(listDatas, _pageNav->_curPage);

	sethasInit(true);
}
		

/**
	* 翻页
	* @param event
	* 
	*/
void VerifyPanel::onPageChange(CCNode* pSender, void* data)
{
	struct sdata
	{
		uint page;
		int type;

	};
	sdata obj;
	obj.page = *(int*)data;
	obj.type = 1;
	_guildDispatcher->dispatchEvent(GuildEventConst::GUILD_APPLY_LIST, &obj);
}