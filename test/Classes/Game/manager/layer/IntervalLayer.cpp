#include "IntervalLayer.h"
#include "view/backpack/components/BagView.h"
#include "view/backpack/components/BagCreate.h"
#include "view/bank/components/BankView.h"

#include "view/shop/components/ShopView.h"

#include "manager/OverPanelManage.h"
#include "manager/PopEventName.h"
#include "utils/TipsEquipCanvas.h"
#include "TextInputConfirm.h"
#include "TextFieldTTF.h"
#include "view/friend/components/FItemCheck.h"
#include "manager/TouchLayerEnum.h"
#include "view/arena/components/GiftPanel.h"
#include "view/arena/components/HeroRankView.h"
#include "Confirm.h"
#include "view/chat/components/ChannelBtnClickLayer.h"
#include "utils/ScaleUtil.h"
#include "view/guild/components/GuildEditView.h"
//#include "NewEAlert.h"

USING_NS_CC;



IntervalLayer::IntervalLayer()
{
	//ʹ�ɱ�����
	this->setIsTouchEnabled(true);

	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::IntervalLayer, true);
	setLastItemGID(NONEINT);
}

IntervalLayer::~IntervalLayer()
{}

//CC_PROPERTY(int32, _lastItemGID, LastItemGID)
int32 IntervalLayer::getLastItemGID()
{
	return _lastItemGID;
}

void IntervalLayer::setLastItemGID(int32 var)
{
	_lastItemGID = var;
}

//begin

void IntervalLayer::registerWithTouchDispatcher()
{
	this->setIsTouchEnabled (true);
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::IntervalLayer, true);
}

bool IntervalLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	//CCLog("TLE::IntervalLayer");
	//
	//setTouchState(TouchState_0);
	//
	bool rnt = false;

	CCPoint locationInView = touch->locationInView(touch->view());
    preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	//
	{
		CCNode* p_tec = (CCNode*)this->getChildByTag(IntervalLayerTAG_eqdrop);
		if (p_tec)
		{
			CCRect contentLayerRect = CCRectZero;
			contentLayerRect.origin = p_tec->getPosition();
			contentLayerRect.size = p_tec->getContentSize();

			if (CCRect::CCRectContainsPoint(contentLayerRect, preTouchPoint))
			{
				rnt = true;
			}
			else
			{//ɾ������TIPS��ʾ
				this->removeChildByTag(IntervalLayer::IntervalLayerTAG_eqdrop, true);
			}
		}
	}
	//ս������BTN TIP
	{
		CCNode* oldp = (CCNode*)this->getChildByTag(IntervalLayer::IntervalLayerTAG_EndBtnTips);
		if (oldp)
		{
			rnt = true;
		}	
	}
	//�����һ����
	{
		CCNode* oldp = (CCNode*)this->getChildByTag(IntervalLayer::IntervalLayerTAG_dungeonGua);
		if (oldp)
		{
			rnt = true;
		}	
	}

	//����ս��ʾ��
	{
		CCNode* oldp = (CCNode*)this->getChildByTag(IntervalLayerTAG_guild_silverMineTips);
		if (oldp)
		{
			rnt = true;
		}
	}
	//����ս���а�
	{
		CCNode* oldp = (CCNode*)this->getChildByTag(IntervalLayerTAG_guild_silverMineRank);
		if (oldp)
		{
			rnt = true;
		}
	}
	//������Ϣ�༭
	{
		CCNode* p_tec = (CCNode*)this->getChildByTag(IntervalLayerTAG_guild_editView);
		if (p_tec)
		{
			rnt = true;
		}
	}
	//�����Ա�˵�IntervalLayerTAG_guild_donateview
	{
		CCNode* p_tec = (CCNode*)this->getChildByTag(IntervalLayerTAG_guild_memberListMenu);
		if (p_tec)
		{
			rnt = true;
		}
	}
	//����Ƽ��������
	{
		CCNode* p_tec = (CCNode*)this->getChildByTag(IntervalLayerTAG_guild_donateview);
		if (p_tec)
		{
			rnt = true;
		}
	}
	//�����б����
	{
		CCNode* p_tec = (CCNode*)this->getChildByTag(IntervalLayerZ_GuildPre);
		if (p_tec)
		{
			rnt = true;
		}
	}
	//������Ϣ���
	{
		CCNode* p_tec = (CCNode*)this->getChildByTag(IntervalLayerZ_guild_info);
		if (p_tec)
		{
			rnt = true;
		}
	}
	//��Ը�ر������
	{
		CCNode* p_tec = (CCNode*)this->getChildByTag(IntervalLayerTAG_reserveDepot);
		if (p_tec && p_tec->getIsVisible())
		{
			rnt = true;
		}
	}
	//ռ�����
	{
		CCNode* p_tec = (CCNode*)this->getChildByTag(IntervalLayerTAG_ZX);
		if (p_tec)
		{
			rnt = true;
		}
	}
	
	//
	{
		CCNode* p_tec = (CCNode*)this->getChildByTag(IntervalLayerTAG_ore_help);
		if (p_tec && p_tec->getIsVisible())
		{
			rnt = true;
		}	
	}
	return rnt;
}

void IntervalLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{	

}

void IntervalLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{

} 
