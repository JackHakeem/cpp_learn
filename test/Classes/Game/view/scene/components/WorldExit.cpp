#include "WorldExit.h"
#include "manager/SourceCacheManage.h"
#include "util/TileUtil.h"
#include "events/GameDispatcher.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "model/player/RoleManage.h"
#include "../SceneWorldMediator.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "MessageInfoBox.h"

WorldExit::WorldExit()
{
	exitMovieClip = NULL;
	sp = NULL;
	buttonMenu = NULL;
}

WorldExit::WorldExit(ExitVo& exitVo)
{
	_exitVo = exitVo;
	_id = exitVo._id;
	_eleName = exitVo._name;
	_otherInfos = exitVo.otherInfos;
	_type = EXIT_TYPE ;

	exitMovieClip = NULL;
	sp = NULL;
	buttonMenu = NULL;

	showRes();
}

void WorldExit::setExitVo(ExitVo& exitVo)
{
	_exitVo = exitVo;
	_id = exitVo._id;
	_eleName = exitVo._name;
	_otherInfos = exitVo.otherInfos;
}

void WorldExit::showRes()
{
	if(_exitVo.resId() != "0") 
	{
		// modify by LH 0726
		_assetPath = _exitVo.isOpend ? ("exit/%s.png") : ("exit/%s_0.png");
		_textPath = _exitVo.isOpend ? ("exit/%s_txt.png") : ("exit/%s_txt.png");
		char tmp[128] = {0};
		sprintf(tmp, _assetPath.c_str(), _exitVo.resId().c_str());
		//std::string tmp_str(tmp);

		CCSprite* p1 = CCSprite::spriteWithSpriteFrameName(tmp);
		CCSprite* p2 = CCSprite::spriteWithSpriteFrameName(tmp);
		CCMenuItemSprite *_button = CCMenuItemImage::itemFromNormalSprite(
			p1,
			p2,
			this, 
			menu_selector(WorldExit::clickExit));

		if(!_button)
			return;
		CCMenu *buttonMenu = CCMenu::menuWithItems(_button, NULL);
		if(buttonMenu && buttonMenu->getParent() == NULL)
		{
			buttonMenu->setPosition(CCPointZero);
			addChild(buttonMenu);
		}

		char tmp1[128] = {0};
		sprintf(tmp1, _textPath.c_str(), _exitVo.resId().c_str());
		sp = CCSprite::spriteWithSpriteFrameName(tmp1);
		if(sp && sp->getParent() == NULL)
		{
			// Doyang 20120724
			sp->setPosition(ccp(POSX(10), POSX(-20)));
			//sp->setAnchorPoint(CCPointZero);
			addChild(sp);
			//sp->release();
		}
		//if(SourceCacheManage::Instance()->has(_assetPath))
		//{
		//	BitmapMovieClip* old = exitMovieClip;
		//	exitMovieClip = SourceCacheManage::Instance()->getObject(_assetPath);
		//	if(old && old != exitMovieClip && old->getParent() == this)
		//	{
		//		removeChild(old, false);
		//		addChild(exitMovieClip);
		//	}
		//}
		//else
		//{
		//	//showDefaultRes();
		//	SourceCacheManage::Instance()->loadNormal(_assetPath, _frameName, 5);
		//	loadCompleteHandler();
		//}
	}
}

/*
CCImage *pImage = new CCImage();
pImage->initWithImageFile("1.png", CCImage::kFmtPng);
unsigned  char *pData = pImage->getData();
unsigned int i=0;
for(int x=0; x<pImage->getWidth(); ++x)
{
	for(int y=0; y<pImage->getHeight(); ++y)
	{
		unsigned int b = pData[i + 1];
		unsigned int g = pData[i + 2];
		unsigned int r = pData[i + 3];
		unsigned int gray = r * 0.3 + g * 0.59 + b * 0.11;
		if(gray > 255)
			gray = 255;
		else if(gray < 0)
			gray = 0;
		pData[i + 1] = pData[i + 2] = pData[i + 3] = (unsigned char) gray;
		i+= 4;
	}
}
CCTexture2D *pTexture = new CCTexture2D();
pTexture->initWithImage(pImage);
CCSprite *pSprite = new CCSprite();
pSprite->initWithTexture(pTexture);
pSprite->setAnchorPoint(CCPointZero);
pSprite->setPosition(CCPointZero);
this->addChild(pSprite);
*/

void WorldExit::clickExit(CCObject* pSender)
{
	//CCLog("click %s", _exitVo.resId().c_str());
	//dispatchEvent(SceneConst::CLICK_EXIT_IN_WORLDMAP, (void*)this);
	//CCLog("click %s", _exitVo.resId().c_str());
	//PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	//int mapId = _exitVo.id();

	// add by LH 0726
	if (!_exitVo.isOpend)
	{
		MessageInfoBox::Instance()->show(ValuesUtil::Instance()->getString("WRD001"),ccc3(12,233,25));
		return;
	}

	if(_exitVo.isCity)
	{
		SceneWorldMediator* m = (SceneWorldMediator*)g_pFacade->retrieveMediator(AppFacade_SCENEWORLD_MEDIATOR);
		if(m)
			m->roleMoveElement((IElement*)this);
	}
	//GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TRIGGER_EXIT, (void*)(&mapId));

	//if(g_pGlobalManage && LayerManager::sceneLayer)
		//g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());
}

void WorldExit::showDefaultRes()
{
	/*var shape:Shape = new Shape();
	shape.graphics.beginFill(0xE0EEE0, 0.1);
	shape.graphics.drawCircle(68, 68, 68);
	shape.graphics.endFill();
	var bitmapData:BitmapData = new BitmapData(136, 136, true, 0x000000);
	bitmapData.draw(shape);
	shape = null;
	_bitmap = new Bitmap(bitmapData);
	_bitmap.scaleY = 0.65;
	_bitmap.x = -68;
	_bitmap.y = -68;
	_bitmap.filters = [new GlowFilter(0xE0FFFF)];
	addChild(_bitmap);*/
	//CCSprite* sprite = CCSprite::spriteWithFile("HelloWorld.png");
	//addChild(sprite);
}

void WorldExit::loadCompleteHandler()
{
	if(exitMovieClip && exitMovieClip->getParent() == this)
		removeChild(exitMovieClip, false);

	exitMovieClip = SourceCacheManage::Instance()->getObject(_assetPath);
	addChild(exitMovieClip);

	update();
}

void WorldExit::updateAction(bool repeat) 
{
	Element::updateAction(repeat);
	/*exitMovieClip.scaleX = dirState.scale;
	exitMovieClip.gotoAndPlay1(1);*/
	if(exitMovieClip)
		exitMovieClip->runActionNormal();
}

void WorldExit::layout()
{
}

void WorldExit::setGlow(bool value)
{
	Element::setGlow(value);
	/*if(exitMovieClip)
		exitMovieClip->gotoAndStop(value?2:1);*/
}

bool WorldExit::isHit()
{

	/*if(exitMovieClip==null || exitMovieClip.bitmapData==null)return false;
	var pixel:Number=exitMovieClip.bitmapData.getPixel32(exitMovieClip.bitmap.mouseX,exitMovieClip.bitmap.mouseY);
	return pixel>0;*/
	//return hitTest();
	return false;
} 

void WorldExit::dispose()
{
	//trace(this.eleName, " dispose ");
	//if(isLoading){
	//	SourceCacheManage.getInstance().removeEventListener(Event.COMPLETE, loadCompleteHandler);
	//}
	//super.dispose();
	//exitMovieClip.dispose();
	//exitMovieClip = null;
	//if(_bitmap)
	//{
	//	this.removeChild(_bitmap);
	//	_bitmap.bitmapData.dispose();
	//	_bitmap = null;
	//}
	Element::dispose();
}

bool WorldExit::hitTest(CCPoint point)
{
	//bool isHit = false;

	//if(!exitMovieClip || !exitMovieClip->normalAnimation || !exitMovieClip->playeSprite)
	//	return false;

	CCSize size;
	if(sp)
		size = sp->getContentSize();
	CCPoint pos = ccp(POSX(this->_exitVo.x), POSX(this->_exitVo.y));
	if(point.x > (pos.x - size.width / 2) && point.x < (pos.x + size.width / 2)
		&& point.y > (pos.y - size.height / 2) && point.y < (pos.y + size.height / 2))
		return true;

	return false;
}
