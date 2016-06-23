#include "view/figure/components/EquiptmentItem.h"
#include "utils/Utils.h"
#include "manager/LayerManager.h"
#include "utils/TipHelps.h"
#include "utils/ScaleUtil.h"

const int TAG_HIGH_LIGHT = 1001;
EquiptmentItem::EquiptmentItem(GoodsInfo* info, int sitNum, int page)
{
	//memcpy((void *)&_info,info,sizeof(_info));
	_info = info;
	myInfo = info;
	_sitNum = sitNum;
	_page = page;
	_eqTip = 0;
	init();
	initEquiptmentItem(info, sitNum, page);
}

EquiptmentItem::~EquiptmentItem()
{
	if (_info)
	{
		//char pathKey[128] = {0};
		//sprintf(pathKey , "assets/icon/goods/%d.png" , _info->goodId);
		//CCTextureCache::sharedTextureCache()->removeTextureForKeyDependently(pathKey);
		//CCTextureCache::sharedTextureCache()->removeUnusedTextures();
	}
	
	//cleanup();
	//CC_SAFE_DELETE(_info);
	CC_SAFE_DELETE(_eqTip);
}

bool EquiptmentItem::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
    return true;
}
void EquiptmentItem::initEquiptmentItem(GoodsInfo* info, int sitNum, int page)
{
	if (sitNum >= 6){return;};
	//this->removeAllChildrenWithCleanup(true);
	this->setAnchorPoint(ccp(0,0));
	this->setIsRelativeAnchorPoint(true);
//	float width = 0.0f;
//	float height = 0.0f;
	SpriteNode* pBack = new SpriteNode();

	char path[64];
	sprintf(path,"new/grid_%d.png", sitNum);
	//equip->initWithFile("assets/ui/pack/lock.png");
	if (pBack)
	{
		if (pBack->initWithSpriteFrameName(path))
		{
//			width = pBack->getContentSize().width;
//			height = pBack->getContentSize().height;
			this->setContentSize(pBack->getContentSize());
			if (this->getChildByTag(0))
			{
				this->removeChildByTag(0,true);
			}
			if (pBack)
			{
				this->addChild(pBack,0,0);

				pBack->release(); // jae 20121110
			}			
		}
		else
		{
			pBack->release();
		}
	}

	// add equipment to the grid
	if (info && 0 != info->id)
	{
		// quality pic
		memset(path,0,sizeof(path));
		sprintf(path,"pack/qualityfram_%d.png",info->quality);
		CCSprite * pQuality = CCSprite::spriteWithSpriteFrameName(path);
		//pQuality->initWithFile(path);
		if (this->getChildByTag(1))
		{
			this->removeChildByTag(1,true);
		}
		if (pQuality)
		{
			this->addChild(pQuality,1,1);
			if (info->quality >= 4)
			{
				pQuality->runAction(getAction());
			}			
		}
		
		//pQuality->release();

		// equip pic
		memset(path,0,sizeof(path));
		//sprintf(path,"goods/%d.png",info->goodId);
		//CCSprite * pEquip = CCSprite::spriteWithSpriteFrameName(path);

		//LH20130110
		sprintf(path,"assets/icon/goods/%d.png",info->goodId);
		CCSprite * pEquip = CCSprite::spriteWithFile(path);
		
		//pEquip->initWithFile(path);
		if (pEquip)
		{
			if (this->getChildByTag(2))
			{
				this->removeChildByTag(2,true);
			}
			if (pEquip)
			{
				this->addChild(pEquip,2,2);
				//pEquip->release();
			}
			
			//pEquip->release();
		}
	}

	int row = sitNum % 3;//
	int col = sitNum % 2;//
	this->setPosition(ccp(POSX(col * 280 + 70), POSX(480 - row * 100 - 16)));
	//set Tips
	if (!_eqTip)
	{
		_eqTip = new TipHelps();
	}
	_eqTip->init(true, TipConst::EQUIPMENT,false);
	_eqTip->setToolTips(this, this);

	// hight light
	CCSprite *pSpritelight = CCSprite::spriteWithSpriteFrameName("figure/select.png");
	pSpritelight->setTag(TAG_HIGH_LIGHT);
	pSpritelight->setIsVisible(false);
	this->addChild(pSpritelight, 10);
}

void EquiptmentItem::closeEquiptmentItem()
{
	removeAllChildrenWithCleanup(true);
}

void EquiptmentItem::onMouseDownHandler(CCPoint curTouchPoint)
{
	SpriteNode * copy;// = new SpriteNode();
	copy = (SpriteNode *)this->getChildByTag(2);
	if (!copy)
	{
		return;
	}
	if(LayerManager::windowLayer)
		LayerManager::windowLayer->addChild(copy,WindowLayer::WindowLayerZ_thisCopy,WindowLayer::WindowLayerTAG_thisCopy);
	copy->setPosition(getScreenPos(this->getChildByTag(2)));
}

void EquiptmentItem::onMouseMoveHnadler(CCPoint curTouchPoint)
{

}

void EquiptmentItem::onMouseUpHnadler(CCPoint curTouchPoint)
{
	if(!(LayerManager::windowLayer))
		return;

	SpriteNode* tmpCopy =  (SpriteNode*)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_thisCopy);
	if (tmpCopy)
	{
		LayerManager::windowLayer->removeChild(tmpCopy, true);
		// send equip on close 0x170

	}

}

void EquiptmentItem::setHighLight( bool isHighLight )
{
	CCSprite *pHighLightSprite = (CCSprite *) this->getChildByTag(TAG_HIGH_LIGHT);
	if(!pHighLightSprite)
	{
		return;
	}
	
	pHighLightSprite->setIsVisible(isHighLight);
}

CCAction * EquiptmentItem::getAction()
{
	CCFiniteTimeAction * actionFadeOut = CCFadeTo::actionWithDuration(0.5f , 128);
	CCFiniteTimeAction * actionFadeIn = CCFadeTo::actionWithDuration(0.5f , 255);
	CCAction* pAction = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(actionFadeIn, actionFadeOut));
	return pAction;
}
