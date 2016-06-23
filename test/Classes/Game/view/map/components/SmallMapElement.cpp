#include "SmallMapElement.h"
#include "utils/ScaleUtil.h"
#include "model/scene/vo/NPCVo.h"
#include "NPCItem.h"
#include "manager/TouchLayerEnum.h"
#include "../MapMediator.h"
#include "manager/GlobalManage.h"
#include "control/AppFacade.h"
#include "manager/ImageManager.h"

SmallMapElement::SmallMapElement()
{}

bool SmallMapElement::createElement(int32 type, bool isRole, char* txt,NPCVo * vo)
{
	if (!LayerNode::init())
		return false;
	char _iconStr[100];
	if (isRole)
	{
		sprintf(_iconStr, "map/5.png");//->
	}
	else
	{
		switch(type)
		{
		case 2:
			sprintf(_iconStr, "map/2.png");//!
			break;
		case 3:
			sprintf(_iconStr, "map/3.png");//yin ?
			break;
		case 4:
			sprintf(_iconStr, "map/4.png");//golden ?
			break;
		default:
			sprintf(_iconStr, "map/1.png");//.
			break;
		}
	}
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/map/res_map.plist");
	CCSprite * pSprite1 = 0;
	CCSprite * pSprite2 = 0;
	if (isRole)
	{
 		pSprite1 = ImageManager::getRealSpriteFromImagePath(_iconStr);
 		pSprite2 = ImageManager::getRealSpriteFromImagePath(_iconStr);
//		pSprite1 = CCSprite::spriteWithSpriteFrameName(_iconStr);
//		pSprite2 = CCSprite::spriteWithSpriteFrameName(_iconStr);
//		pSprite1->setColor(ccc3(233,12,25));
//		pSprite2->setColor(ccc3(233,12,25));
		pSprite1->setScale(1.3);
		pSprite2->setScale(1.3);
	}
	else
	{
		pSprite1 = CCSprite::spriteWithSpriteFrameName(_iconStr);
		pSprite2 = CCSprite::spriteWithSpriteFrameName(_iconStr);
	}

	//LH20121025
	CCMenuItemSprite * pNpcItem = CCMenuItemSprite::itemFromNormalSprite(pSprite1 , pSprite2 , this , menu_selector(SmallMapElement::autoFind));
	pNpcItem->setTag(isRole ? 0 : vo->id);
	CCMenu * pMenu = CCMenu::menuWithItem(pNpcItem);
	pMenu->setPosition(ccp(0,0));
	pMenu->setAnchorPoint(ccp(0.5,0.5));
	pMenu->setTouchLayer(TLE::WindowLayer_Map);
	//

	if (type == 2 || type == 3 || type == 4)
		pMenu->setScale(1.0f);

	if (isRole)
		pMenu->setScale(1.0f);
	this->addChild(pMenu, isRole ? MapElementZ_icon+1 : MapElementZ_icon, MapElementTAG_icon);

	//_icon->release();

	if (txt)
	{
		//CCLabelTTF* pNpcLable = CCLabelTTF::labelWithString(txt, CCSizeMake(POSX(250), POSX(20)), CCTextAlignmentLeft, "Arial", POSX(18));
		CCLabelTTF* pNpcLable = CCLabelTTF::labelWithString(txt, "Arial", POSX(18));
		CCSize size = pNpcLable->getContentSize();
		pNpcLable->setAnchorPoint(ccp(0,0));
		if (isRole)
		{
			pNpcLable->setColor(ccc3(233, 25, 233));
			pNpcLable->setPosition(ccp(POSX(-50.0f), POSX(-35.0f)));
		}
		else
		{
			pNpcLable->setColor(ccc3(12, 233, 25));
			pNpcLable->setPosition(ccp(/*POSX(-25.0f)*/(-1) * size.width/2, POSX(-35.0f)));
		}
		this->addChild(pNpcLable, MapElementZ_txt, MapElementTAG_txt);	
	}

	//LH
	MapMediator * pSceneMtr = (MapMediator *)g_pFacade->retrieveMediator(AppFacade_MapMediator);
	addEventListener(NPCItem::GO_TO_NPC, pSceneMtr, callfuncND_selector(MapMediator::roleToNpc));

	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/map/res_map.plist");
	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/map/res_map.pvr.ccz");

	return true;
}

void SmallMapElement::iconSetRotation(float var)
{
	CCMenu* pMenu = (CCMenu*)this->getChildByTag(MapElementTAG_icon);
	if (pMenu)
	{
		CCMenuItemSprite * pMenuSprite = (CCMenuItemSprite *)pMenu->getChildByTag(0);
		if (pMenuSprite)
		{
			pMenuSprite->setRotation(var);
		}
	}
}

//LH
void SmallMapElement::autoFind(CCObject * pSender)
{
	int nTag = ((CCNode *)pSender)->getTag();
	if (nTag)
	{
		dispatchEvent(NPCItem::GO_TO_NPC, &nTag);
	}	
}