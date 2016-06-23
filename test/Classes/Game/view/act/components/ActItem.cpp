#include "ActItem.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "model/backpack/GoodsManager.h"
#include "CCUIBackground.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "utils/ColorUtil.h"
#include "model/config/ConfigManager.h"
#include "manager/LangManager.h"
#include "model/appoint/AppointManager.h"
#include "model/scene/MonsterManager.h"
#include "model/scene/SceneManager.h"
#include "view/task/components/TaskType.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "model/backpack/GoodsManager.h"
#include "model/com/GoodsToolTips.h"
#include "model/com/GoodsDynamicManager.h"
#include "utils/TipHelps.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "KKLabelTTF.h"
#include "manager/TimerManage.h"
#include "manager/ViewManager.h"
#include "HotList.h"
#include "ActView.h"

const float w_frame = 400;
const float w_frame_label = 360;
const float h_frame = 0;
const float FontSize = 20.0f;

ActItem::ActItem():_bg1(0)
{
	setIsExpand(true);
}

ActItem::~ActItem()
{

}

bool ActItem::init(SCMD38FNode node)
{
	if (!LayerNode::init())
		return false;

	float height=0;
    float factor = CCDirector::sharedDirector()->getContentScaleFactor();
	

	float heightX = POSX(30.0f);

	//start and end time
	if (getIsExpand() && node.g_isShowTime )
	{
		std::string szStartTime = TimerManage::formatServerTimeToDate(node.e_startTime);
		std::string szEndTime = TimerManage::formatServerTimeToDate(node.f_endTime);
		std::string strTime("");
		//
		strTime.append(ValuesUtil::Instance()->getString("ACT002"));
		strTime.append(szEndTime);
		KKLabelTTF* pLabelStart = new KKLabelTTF();
		pLabelStart->init(FontSize, 36.0f, CCSizeMake(w_frame_label, 120));
		pLabelStart->add(strTime, ccc3(12, 233, 25));
		pLabelStart->setPosition(ccp(15/2.0f, pLabelStart->m_iRow*pLabelStart->m_fFontRealHeight+height));
		this->addChild(pLabelStart, 2);
		pLabelStart->release();
		height += (pLabelStart->m_iRow+1)*pLabelStart->m_fFontRealHeight;
		//
		strTime = "";
		strTime.append(ValuesUtil::Instance()->getString("ACT001"));
		strTime.append(szStartTime);
		KKLabelTTF* pLabelEnd = new KKLabelTTF();
		pLabelEnd->init(FontSize, 36.0f, CCSizeMake(w_frame_label, 120));
		pLabelEnd->add(strTime, ccc3(12, 233, 25));
		pLabelEnd->setPosition(ccp(15/2.0f, pLabelEnd->m_iRow*pLabelEnd->m_fFontRealHeight+height));
		this->addChild(pLabelEnd, 2);
		pLabelEnd->release();
		height += (pLabelEnd->m_iRow+1)*pLabelEnd->m_fFontRealHeight;
	}
	
	//_txtContent
	if(getIsExpand())
	{
		KKLabelTTF* pLabel = new KKLabelTTF();
		pLabel->init(FontSize, 36.0f, CCSizeMake(w_frame_label, 120));
		pLabel->add(node.d_content, ccc3(240, 240, 232));
		pLabel->setPosition(ccp(15/2.0f, pLabel->m_iRow*pLabel->m_fFontRealHeight+height));
		this->addChild(pLabel, 2);
		pLabel->release();
		height += (pLabel->m_iRow+1)*pLabel->m_fFontRealHeight;
	}

	//_txtTitle
	{
		ActView * pActView = ViewManager::getInstance()->actView;
		HotList * pHotList = 0;
		if (pActView)
		{
			if (node.b_type == 0)
			{
				pHotList = pActView->_pHot;
			}
			else
			{
				pHotList = pActView->_pAct;
			}
		}

		std::string strTitle("");
		if (pHotList)
		{
			char path[16] = {0};
			sprintf(path , "[%d]" , pHotList->_index + 1);
			strTitle.append(path);
			strTitle.append(node.c_title);
			++pHotList->_index;
		}
		else
		{
			strTitle.append(node.c_title);
		}

		KKLabelTTF* pLabel = new KKLabelTTF();
		pLabel->init(FontSize+(8), 36.0f, CCSizeMake(w_frame_label, 120));
		pLabel->add(strTitle, ccc3(103, 228, 235));
		pLabel->setPosition(ccp(15/2.0f, pLabel->m_iRow*pLabel->m_fFontRealHeight+height + heightX/2));
		this->addChild(pLabel, 2);
		pLabel->release();
		height += (pLabel->m_iRow+1)*pLabel->m_fFontRealHeight;

		_minSize = CCSizeMake(POSX(w_frame) , POSX((pLabel->m_iRow+1)*pLabel->m_fFontRealHeight*factor ) + heightX);
		_maxSize = CCSizeMake(POSX(w_frame) , POSX(height*factor) + heightX);
	}

	//
	_bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("chat/chat_6.png", ccp(POSX(0), POSX(0)),ccp(0,0),
		CCSizeMake(POSX(w_frame), POSX(height*factor) + heightX));
	this->addChild(_bg1, 1);

	_bg1->release();
	//
	this->setvisibleSize(CCSizeMake(POSX(w_frame), POSX(height*factor) + heightX));
	this->setContentSize(CCSizeMake(POSX(w_frame), POSX(height*factor) + heightX));
	return true;
}

void ActItem::visit() // LH20121015
{
	CCLayer::visit();
	return;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	float scale = ScaleUtil::Instance()->getScaleFactoryOnAndroid(); 

	glEnable(GL_SCISSOR_TEST);

	CCPoint pos = _bg1->getParent()->convertToWorldSpace(_bg1->getPosition());
	CCSize sizeNew = _bg1->getContentSize();

	glScissor(pos.x * scale , pos.y * scale,
		sizeNew.width * scale , scale *sizeNew.height);
	CCLayer::visit();

	glDisable(GL_SCISSOR_TEST);
#else
	float scale = CCDirector::sharedDirector()->getContentScaleFactor();

	glEnable(GL_SCISSOR_TEST);

	CCPoint pos = _bg1->getParent()->convertToWorldSpace(_bg1->getPosition());
	CCSize sizeNew = _bg1->getContentSize();

	ActView * pActView = ViewManager::getInstance()->actView;
	HotList * pHotList = 0;
	if (pActView)
	{
		pHotList = pActView->_pAct;
		if (!pHotList)
		{
			pHotList = pActView->_pHot;
		}
	}
	
	if (pHotList)
	{
		if (pos.y >= pHotList->getWorldSpaceLeftBottomPoint().y + pHotList->getRect().size.height) 
		{
			pos.y = pHotList->getWorldSpaceLeftBottomPoint().y + pHotList->getRect().size.height;
		}
		else if (pos.y < pHotList->getWorldSpaceLeftBottomPoint().y)
		{
			pos.y = pHotList->getWorldSpaceLeftBottomPoint().y;
		}
	}
	
	glScissor(pos.x * scale , pos.y * scale,
		sizeNew.width * scale , scale *sizeNew.height);
	CCLayer::visit();

	glDisable(GL_SCISSOR_TEST);
#endif
}

void ActItem::setClipSize(CCSize size)
{
	if (_bg1)
	{
		CCPoint pos = _bg1->getPosition();
		CCSize preSize = _bg1->getContentSize();
		_bg1->setContentSize(size);
		_bg1->changeSize(size);
		_bg1->setPosition(ccp(pos.x , pos.y - (size.height - preSize.height)));
	}
	this->setContentSize(size);
	this->setvisibleSize(size);
}

