#include "BankGoods.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "manager/LayerManager.h"
#include "manager/OverPanelManage.h"
#include "manager/LayerManager.h"
#include "utils/TipHelps.h"
#include "utils/ScaleUtil.h"

const float FontSize = 20.0f;

BankGoods::BankGoods()
{
	_lock = false;
	_mySitNum = 0;
	isMove = false;
	isHasCopy = false;
	myInfo = 0;
	m_page = -1;
	myTip = 0;
	//thisCopy = 0;

}

BankGoods::~BankGoods()
{
	if (myTip)
	{
		SAFE_DELETE(myTip);
	}
}

/**
	*Each grid of the show, including items information, pictures and number shows, and set up the position of the grid
	* @param info GoodsInfo
	* @param sitNum position
	* @param page 
	* 
	*/	
bool BankGoods::initBankGoods(GoodsInfo* info, int32 sitNum, int32 page, bool lock)
{
	this->setIsTouchEnabled(true);
	_mySitNum = sitNum;
	myInfo = info;
	m_page = page;
	_lock = lock;

//	float32 width = 0;//unlock->getTexture()->getContentSize().width;
//	float32 height = 0;//unlock->getTexture()->getContentSize().height;
	if (lock)
	{/*
		this->initWithFile("assets/ui/pack/lock.png");
		*/
		//bottom
		SpriteNode* lock = new SpriteNode();
		lock->initWithSpriteFrameName("pack/lock.png");
//		width = lock->getTexture()->getContentSize().width;
//		height = lock->getTexture()->getContentSize().height;
		this->addChild(lock, RENDERZ_unlock_lock, RENDERTAG_unlock_lock);	
		this->setContentSize(/*lock->getTexture()->getContentSize()*/CCSizeMake(POSX(98), POSX(98)));

		lock->release();
		
	}
	else
	{
		//bottom
		/*this->initWithFile("assets/ui/pack/unlock.png");
		float32 unlockwidth = this->getTexture()->getContentSize().width;
		float32 unlockheight = this->getTexture()->getContentSize().height;
		*/
		SpriteNode* unlock = new SpriteNode();
		unlock->initWithSpriteFrameName("pack/unlock.png");
		//float32 width = unlock->getTexture()->getContentSize().width;
		//float32 height = unlock->getTexture()->getContentSize().height;
		this->addChild(unlock, RENDERZ_unlock_lock, RENDERTAG_unlock_lock);	
		this->setContentSize(/*unlock->getTexture()->getContentSize()*/CCSizeMake(POSX(98), POSX(98)));
		unlock->setPosition(ccp(0,0));
		unlock->release();
		
		//props
		SpriteNode* item = 0;
		if (info->id != 0)
		{//icon

			//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_icon.plist"); 

			char itemroad[70];
			//sprintf(itemroad, "goods/%d.png", info->goodId);// The current only a demo props ICON
			sprintf(itemroad, "assets/icon/goods/%d.png", info->goodId); // LH20130110
			item = new SpriteNode();
			//item->initWithSpriteFrameName(itemroad);
			bool var = item->initWithFile(itemroad);
			if (!var)
			{
				item->initWithFile("assets/icon/goods/unknown.png");
			}
			//float32 itemwidth = item->getTexture()->getContentSize().width;
			//float32 itemheight = item->getTexture()->getContentSize().height;
			this->addChild(item, RENDERZ_item, RENDERTAG_item);		
		//	item->setAnchorPoint(ccp(0, 0));
		//	item->setPosition(ccp(-itemwidth/2.0f, -itemheight/2.0f));
			item->release();
									
		 //Quality box
			char qualityframeroad[50];
			sprintf(qualityframeroad, "pack/qualityfram_%d.png", info->quality);//info->goodId The current only a demo props ICON
			SpriteNode* qualityframe = new SpriteNode();
			qualityframe->initWithSpriteFrameName(qualityframeroad);
			this->addChild(qualityframe, RENDERZ_qualityframe, RENDERTAG_qualityframe);		
			//qualityframe->setAnchorPoint(ccp(0.5, 0.5));
			qualityframe->setPosition(ccp(0, 0));
			qualityframe->release();
			
			// LH20120106
			if (info->type == 3 && item)
			{
				char str[10];
				sprintf(str, "%d/%d", info->number, info->explain.chipNeedNum);
				CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
					str, CCSizeMake(POSX(60), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));  

				pLabel->setPosition(ccp(POSX(60), POSX(12)));
				item->addChild(pLabel, RENDERZ_number, RENDERTAG_number);
				pLabel->setColor(ccc3(255, 255, 255));
			}
		}
		
	}
	
	int row = sitNum / 4;//
	int col = sitNum % 4;//

	//this->setIsRelativeAnchorPoint(true);
	//this->setAnchorPoint(ccp(0.5,0.5));
	this->setPosition(ccp(POSX(col*110+52), POSX(435-row*110)));
		
	//??TIPS
	if (!myTip)
	{
		myTip = new TipHelps();
	}
	myTip->init(true, TipConst::BANK);
	myTip->setToolTips(this, this);
	//

	return true;
}

/**
		 * µãÏÂ 
		 * @param e
		 * 

		private function onMouseDownHandler(e:MouseEvent):void
		{
			isMove = false;
			isHasCopy = true;
			// copy picture
			var myBMD:BitmapData;
			if(_pic && _pic.myBitmapData) 
				myBMD = _pic.myBitmapData.clone();
			
			thisCopy = Reflection.createInstance("goodsGrid");
			thisCopy["_txtNum"].text = numText.text;
			thisCopy["_icon"].addChild(new Bitmap(myBMD));
			thisCopy.mouseEnabled = false;
			thisCopy.mouseChildren = false;
			if(myInfo.quality>=1 && myInfo.quality<=7){
				thisCopy["_fmQuality"].gotoAndStop(myInfo.quality+1);
			}
			this.stage.addEventListener(MouseEvent.MOUSE_UP, onMouseUpHnadler);
			this.stage.addEventListener(MouseEvent.MOUSE_MOVE, onMouseMoveHnadler);
			myStage = this.stage;
		}
		 */

void BankGoods::onMouseDownHandler(CCPoint curTouchPoint)
{
	
	if (!this->getChildByTag(RENDERTAG_item))
		return;//No props of the grid, need not do props to move

	isMove = false;
	isHasCopy = true;

	//Cloning pictures
	char qualityframeroad[50];
	//sprintf(qualityframeroad, "goods/%d.png", myInfo->goodId);//info->goodId The current only a demo props ICON
	sprintf(qualityframeroad, "assets/icon/goods/%d.png", myInfo->goodId);
	SpriteNode* thisCopy = new SpriteNode();
	//thisCopy->initWithSpriteFrameName(qualityframeroad);
	thisCopy->initWithFile(qualityframeroad);
	LayerManager::windowLayer->addChild(thisCopy,WindowLayer::WindowLayerZ_thisCopy,WindowLayer::WindowLayerTAG_thisCopy);
	//thisCopy->setPosition(ccp(curTouchPoint.x+this->getPosition().x, curTouchPoint.y+this->getPosition().y));
	thisCopy->setPosition(getScreenPos(this));

	{
			char itemroad[70];
			sprintf(itemroad, "pack/unlock.png");//info->goodId The current only a demo props ICON
			SpriteNode* item = new SpriteNode();
			item->initWithSpriteFrameName(itemroad);
		//	float32 itemwidth = item->getTexture()->getContentSize().width;
		//	float32 itemheight = item->getTexture()->getContentSize().height;
			thisCopy->addChild(item, RENDERZ_unlock_lock-1, RENDERTAG_unlock_lock-1);		
			item->setAnchorPoint(ccp(0, 0));
		//	item->setPosition(ccp(-itemwidth/2.0f, -itemheight/2.0f));
			item->release();
			
		 //Quality box
			//char qualityframeroad[50];
			sprintf(qualityframeroad, "pack/qualityfram_%d.png", myInfo->quality);//info->goodId The current only a demo props ICON
			SpriteNode* qualityframe = new SpriteNode();
			qualityframe->initWithSpriteFrameName(qualityframeroad);
			thisCopy->addChild(qualityframe, RENDERZ_qualityframe, RENDERTAG_qualityframe);		
			qualityframe->setAnchorPoint(ccp(0, 0));
			qualityframe->setPosition(ccp(0, 0));
			qualityframe->release();
	}



	/*
		SpriteNode* sprite = new SpriteNode();
		sprite->init();
		sprite->setTextureRect( CCRectMake(0, 0, 98,98) );
		sprite->setColor(ccc3(0,0,0));
		sprite->setOpacity(128);
		sprite->setPosition(ccp(0,0));
		sprite->setAnchorPoint(ccp(0,0));
		thisCopy->addChild(sprite, 100);
		sprite->release();
		*/

	thisCopy->runAction(CCScaleTo::actionWithDuration(0.2f, 1.2f));//Increasingly large
	


	thisCopy->release();

	//Make ITEM and FRAME disappear
	reShowItemAndFrame(false);
}


/**
		 * Mobile drag icon
		 * @param e
		 * 
 */
void BankGoods::onMouseMoveHnadler(CCPoint curTouchPoint)
{
	if (!isHasCopy)
		return;//onMouseDownHandlerNo copy the picture, so don't have to do behind

	if (!isMove)
	{
		isMove = true;
		//OverPanelManage.getInstance().setMousechild(false);
	}
	SpriteNode* tmpThisCopy =  (SpriteNode*)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_thisCopy);
	if (!tmpThisCopy)
		return;

	//CCPoint tarpos = ccp(curTouchPoint.x - this->getPosition().x, curTouchPoint.y - this->getPosition().y);

	//CCPoint ppp = tmpThisCopy->getPosition();

	CCPoint ccc = ccpAdd(tmpThisCopy->getPosition(), curTouchPoint);

	tmpThisCopy->setPosition(ccp((ccc.x), (ccc.y)));
}

/**
	* up 
	* @param e
	* 
*/
void BankGoods::onMouseUpHnadler(CCPoint curTouchPoint)
{
	if (!isHasCopy)
		return;//onMouseDownHandlerNo copy the picture, so don't have to do behind

	isHasCopy = false;
	if (isMove)//If is after moving up the mouse, want to swap places
	{
		int tag = LayerManager::windowLayer->getCurNodeTag(curTouchPoint);
		if (tag > OVER_0_NONE)
		{//Up in the in the backpack
			g_pOverPanelManage->goodsMove(this->getTag(), tag, curTouchPoint.x, curTouchPoint.y, OVER_6_BANK);
			//OverPanelManage.getInstance().setMousechild(true);
		}
		else if (tag == OVER_0_NONE)
		{//Up in the backpack

			reShowItemAndFrame(true);
		}
		
	}
	else
	{
		reShowItemAndFrame(true);//The mouse bit-" don't move-" let go time to render
	}

	SpriteNode* tmpThisCopy =  (SpriteNode*)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_thisCopy);
	if (tmpThisCopy)
	{
		LayerManager::windowLayer->removeChild(tmpThisCopy, true);
	}
}

void BankGoods::reShowItemAndFrame(bool isShow)
{
	//The original ITEM pictures appear/disappear
	SpriteNode* item = (SpriteNode*)this->getChildByTag(RENDERTAG_item);
	if (item)
		item->setIsVisible(isShow);
	//The original color box pictures appear/disappear
	SpriteNode* qualityframe = (SpriteNode*)this->getChildByTag(RENDERTAG_qualityframe);
	if (qualityframe)
		qualityframe->setIsVisible(isShow);
}

CCSize BankGoods::getSrcContentSize()
{
    CCSize size = CCSizeMake(this->getContentSize().width, this->getContentSize().height);

	return size;
}