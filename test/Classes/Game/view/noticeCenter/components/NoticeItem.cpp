#include "NoticeItem.h"
#include "CCUIBackground.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "CenterView.h"
#include "manager/ViewManager.h"
#include "view/friend/components/FriendEventConst.h"
#include "manager/TouchLayerEnum.h"

const float w_frame = 700.0f;
const float h_frame = 80.0f;
const float str_start_x = 250.0f;
const float row_h = 20.0f;
const float fontsize = 18.0f;
const float btn_0_x = 530.0f;
const float btn_1_x = 630.0f;
NoticeItem::NoticeItem()
{}

NoticeItem::~NoticeItem()
{}

bool NoticeItem::init(NM_ELM_INFO* info, int type)
{
	if (!LayerNode::init() || !info)
		return false;
	
	m_info = *info;

	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("popuibg/bg1.png", ccp(POSX(0), POSX(0)), ccp(0,0), CCSizeMake(POSX(w_frame), POSX(h_frame)));
	this->addChild(_bg1, NoticeItemZ_bg, NoticeItemTAG_bg);
	//Doyang 20120712
	_bg1->release();

	this->setvisibleSize(CCSizeMake(POSX(w_frame), POSX(h_frame)));
	this->setContentSize(CCSizeMake(POSX(w_frame), POSX(h_frame)));

	SpriteNode* pIcon = new SpriteNode();
	pIcon->initWithFile("assets/ui/notice/tan_icon.png");
	this->addChild(pIcon, NoticeItemZ_icon, NoticeItemTAG_icon);
    pIcon->release();
	pIcon->setPosition(ccp(
		pIcon->getTexture()->getContentSize().width, 
		pIcon->getTexture()->getContentSize().height+POSX(10.0f)));

	switch (type)
	{
	case NoticeManager::ADD_FRI:
		{		
			{
				CCLabelTTF* pLable_1 = CCLabelTTF::labelWithString(info->data[0].c_str(), CCSizeMake(info->data[0].size() * POSX(fontsize), POSX(fontsize)),CCTextAlignmentLeft, "Arial", POSX(fontsize));
				pLable_1->setPosition(ccp(POSX(str_start_x), POSX(row_h*3)));
				pLable_1->setColor(info->color_data[0]);
				this->addChild(pLable_1, 0, 0);			
			}

			{
				float x = POSX(str_start_x);
				CCLabelTTF* pLable_1 = CCLabelTTF::labelWithString(info->data[1].c_str(), CCSizeMake(info->data[0].size() * POSX(fontsize), POSX(fontsize)),CCTextAlignmentLeft, "Arial", POSX(fontsize));
				pLable_1->setPosition(ccp(x, POSX(row_h*2)));
				pLable_1->setColor(info->color_data[1]);
				this->addChild(pLable_1, 0, 1);		
				
				x += POSX((info->data[1].size()/2) * fontsize);//info->data[1].size()*20;
				pLable_1 = CCLabelTTF::labelWithString(info->data[2].c_str(), CCSizeMake(info->data[0].size() * POSX(fontsize), POSX(fontsize)),CCTextAlignmentLeft, "Arial", POSX(fontsize));
				pLable_1->setPosition(ccp(x, POSX(row_h*2)));
				pLable_1->setColor(info->color_data[2]);
				this->addChild(pLable_1, 0, 2);	

				x += POSX((info->data[2].size()/2)*fontsize);
				pLable_1 = CCLabelTTF::labelWithString(info->data[3].c_str(), CCSizeMake(info->data[0].size() * POSX(fontsize), POSX(fontsize)),CCTextAlignmentLeft, "Arial", POSX(fontsize));
				pLable_1->setPosition(ccp(x, POSX(row_h*2)));
				pLable_1->setColor(info->color_data[3]);
				this->addChild(pLable_1, 0, 3);	
			}

			{
				CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
				CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
				if(!pNormalSprite || !pPressedSprite)
				{
					return false;
				}
				CCMenuItemSprite *_btn_0 = CCMenuItemSprite::itemFromNormalSprite(
					pNormalSprite,
					pPressedSprite, 
					this, 
					menu_selector(NoticeItem::onLink_ADD_FRI));//
				_btn_0->setPosition(ccp(POSX(btn_0_x), POSX(h_frame/2)) );

				_btn_0->setScaleX(0.7f);//规模

				CCMenu *buttonMenu = new CCMenu();
				buttonMenu->init();
				buttonMenu->setTouchLayer(TLE::WindowLayer_NoticeCenter-2200);
				buttonMenu->addChild(_btn_0, 0, 0);
				buttonMenu->setPosition(ccp(0, 0));
				this->addChild(buttonMenu);
				buttonMenu->release();	
		
				CCLabelTTF* pLable_btn = CCLabelTTF::labelWithString(info->data[4].c_str(), CCSizeMake(POSX(200), POSX(20)),CCTextAlignmentCenter, "Arial", POSX(20));
				pLable_btn->setPosition(ccp(buttonMenu->getPosition().x + _btn_0->getContentSize().width/2, 
					buttonMenu->getPosition().y + _btn_0->getContentSize().height/2));
				_btn_0->addChild(pLable_btn, 2);
				pLable_btn->setColor(ccc3(254, 189, 0));
				pLable_btn->setScaleX(1.3f);
			}

			{
				CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
				CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
				if(!pNormalSprite || !pPressedSprite)
				{
					return false;
				}
				CCMenuItemSprite *_btn_0 = CCMenuItemSprite::itemFromNormalSprite(
					pNormalSprite,
					pPressedSprite, 
					this, 
					menu_selector(NoticeItem::onLink_CLOSE_NOTE));//
				_btn_0->setPosition(ccp(POSX(btn_1_x), POSX(h_frame/2)) );

				_btn_0->setScaleX(0.7f);//规模

				CCMenu *buttonMenu = new CCMenu();
				buttonMenu->init();
				buttonMenu->setTouchLayer(TLE::WindowLayer_NoticeCenter-2200);
				buttonMenu->addChild(_btn_0, 0, 0);
				buttonMenu->setPosition(ccp(0, 0));
				this->addChild(buttonMenu);
				buttonMenu->release();	
		
				CCLabelTTF* pLable_btn = CCLabelTTF::labelWithString(info->data[5].c_str(), CCSizeMake(POSX(200), POSX(20)),CCTextAlignmentCenter, "Arial", POSX(20));
				pLable_btn->setPosition(ccp(buttonMenu->getPosition().x + _btn_0->getContentSize().width/2, 
					buttonMenu->getPosition().y+_btn_0->getContentSize().height/2));
				_btn_0->addChild(pLable_btn, 2);
				pLable_btn->setColor(ccc3(254, 189, 0));
				pLable_btn->setScaleX(1.3f);
			}
		}
		break;
	};
	return true;
}

CenterView* NoticeItem::view()
{
	//CenterView* tempVar = (CenterView*)this->getParent();
//	return tempVar ? tempVar : 0; 

	CenterView * sv = ViewManager::getInstance()->_centerView;
	return sv;
}
void NoticeItem::onLink_ADD_FRI(CCObject* pSender)
{
	//execute
	if (view())
	{
		struct sdata 
		{
			std::string name;
			int8 type;
		};
		sdata d;
		d.name = m_info.data[6];
		d.type = 0;//同意
		view()->dispatchEvent(CenterView::ADD_FRIEND, (void*)&d);
	}
		//
	g_pNoticeManager->delItemStr(NoticeManager::ADD_FRI, m_info.sit);
	//close
	view()->reLocate();
	//

}

void NoticeItem::onLink_CLOSE_NOTE(CCObject* pSender)
{
	//
	g_pNoticeManager->delItemStr(NoticeManager::ADD_FRI, m_info.sit);
	//close
	view()->reLocate();
}