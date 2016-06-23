#include "Item.h"
#include "model/com/ResourceManage.h"
#include "manager/TimerManage.h"

Item::Item(ItemVo &itemVo)
{
	init();
	_id = itemVo.getID();
	_eleName = itemVo.getName();
	_type = ITEM_TYPE;	
//	this.mouseChildren = false;
//	this.mouseEnabled = false;			
	_itemVo = itemVo;			
	itemMovieClip = new BitmapMovieClip();
	itemMovieClip->_x = 100;  
	itemMovieClip->_y = 110;  // 
	this->addChild(itemMovieClip);
    itemMovieClip->release();//kevinchange0810
	_res = *ResourceManage::Instance()->getRes(1,itemVo.getResId());
	_nameTxt = CCLabelTTF::labelWithString("",CCSizeMake(0,0),CCTextAlignmentCenter,g_sSimHeiFont,20);
	_nameTxt->setColor(ccc3(0xED,0xDA,0x36));
	this->addChild(_nameTxt);		
	dispatcher = GameDispatcher::getInstance();
	showRes();
}

void Item::showRes()
{
	if (!_itemVo.getResId())
	{
		itemMovieClip->_delay = _res.timer;
		_assetURL = _res.modelUrl();
		TimerManage::Instance()->add( 1.0f, schedule_selector(Item::layout), this );
		layout();
		//var callback:Function = function():{	update();	}
		//this.itemMovieClip.translate(_assetURL,BitmapMovieClip.URL_TYPE, callback, LoadLevel.MIDDILE);
	}
}

void Item::layout(ccTime dt)
{
	if(_eleName != "")
	{
		_nameTxt = CCLabelTTF::labelWithString(_eleName.c_str(),CCSizeMake(100,0),CCTextAlignmentCenter,g_sSimHeiFont,20); ;
	}
	_nameTxt->setPosition(ccp(_nameTxt->getContentSize().width/2,10));
// 	_nameTxt->y = 10;
// 	_nameTxt->x = -_nameTxt->autoSize>>1;
}

void Item::updateAction(bool repeat)
{
	this->Element::updateAction(repeat);
	//itemMovieClip->scaleX = dirState.scale;
	//itemMovieClip.gotoAndPlay1(1);  //	itemMovieClip.gotoAndStop(1);
}

void Item::setGlow(bool bValue)
{
	this->Element::setGlow(bValue);
}

bool Item::isHit()
{
	//if(!itemMovieClip || itemMovieClip->bitmapData==null){return false;}
	//var pixel:Number=itemMovieClip.bitmapData.getPixel32(itemMovieClip.bitmap.mouseX,itemMovieClip.bitmap.mouseY);
	//return pixel>0;
	return 0;
}

bool Item::hitTest(CCPoint point)
{
	return 0;
}

void Item::dispose()
{
	this->Element::dispose();
}