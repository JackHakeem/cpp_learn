#include "Exit.h"
#include "manager/SourceCacheManage.h"
#include "util/TileUtil.h"
#include "utils/ScaleUtil.h"

Exit::Exit()
{
	_nameTxt = NULL;
	exitMovieClip = NULL;
}

Exit::Exit(ExitVo& exitVo)
{
	_exitVo = exitVo;
	_id = exitVo._id;
	_eleName = exitVo._name;
	_otherInfos = exitVo.otherInfos;
	_type = EXIT_TYPE ;

	exitMovieClip = NULL;
	/*exitMovieClip = new BitmapMovieClip();
	exitMovieClip.delay = 100;
	exitMovieClip.blendMode = BlendMode.ADD
		addChild(exitMovieClip);*/

	_nameTxt = CCLabelTTF::labelWithString(_eleName.c_str(), "Arial", POSX(15));
	ccColor3B col= ccc3(0xed, 0xda, 0x36);
	/*
	if(_nameTxt)
	{
		_nameTxt->setColor(col);
		addChild(_nameTxt);
	}
	*/
	showRes();
}

void Exit::setExitVo(ExitVo& exitVo)
{
	_exitVo = exitVo;
	_id = exitVo._id;
	_eleName = exitVo._name;
	_otherInfos = exitVo.otherInfos;
}

void Exit::showRes()
{
	if(_exitVo.resId() != "0") 
	{
		//CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_RGBA4444 );
		_assetPath = "assets/effect/map/mapExit.plist";
		std::string _frameName = "mapExit_%02d.png";
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

		//Begin Kenfly 20121116
		if (exitMovieClip && exitMovieClip->getParent() == this)
		{
			removeChild(exitMovieClip, false);
			exitMovieClip->release();
		}

		exitMovieClip = new BitmapMovieClip();

		exitMovieClip->loadNormalAsync(_assetPath, _frameName, 12, 0.1f/*, this, callfuncOD_selector(Exit::loadCompleteHandler), NULL*/);

		this->addChild(exitMovieClip);
		exitMovieClip->setPosition(ccp(POSX(-10), POSX(90)));
		exitMovieClip->release();
		update();

		//End Kenfly 20121116

		//old
		//BitmapMovieClip* m = SourceCacheManage::Instance()->loadNormal(_assetPath, _frameName, 12, 0.1f, true);
		//if(m)
		//{
		//	if(exitMovieClip && exitMovieClip->getParent() == this)
		//	{
		//		removeChild(exitMovieClip, false);
		//		exitMovieClip->release();
		//	}

		//	exitMovieClip = m;

		//	if(exitMovieClip && exitMovieClip->getParent() == NULL)
		//	{
		//		addChild(exitMovieClip);
		//		exitMovieClip->setPosition(  ccp(POSX(-10), POSX(90))  );
		//		//Doyang 20120714
		//		exitMovieClip->release();
		//	}

		//	update();
		//}
		//CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_Default );
	}
}

void Exit::showDefaultRes()
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

// do not call this function
void Exit::loadCompleteHandler(CCObject* target, void* data) //Kenfly 20121116
{
	//Begin Kenfly 20121116
	if(_exitVo.resId() != "0" && exitMovieClip != NULL) 
	{
		_assetPath = "assets/effect/map/mapExit.plist";
		std::string _frameName = "mapExit_%02d.png";


		int res = exitMovieClip->loadNormalAsync(_assetPath, _frameName, 12, 0.1f);

		if (res != -1)
			updateAction();
	}
	//End Kenfly 20121116

	//Begin old
	//if(exitMovieClip && exitMovieClip->getParent() == this)
	//	removeChild(exitMovieClip, false);

	//exitMovieClip = SourceCacheManage::Instance()->getObject(_assetPath);
	//addChild(exitMovieClip);
	////Doyang 20120714
	//exitMovieClip->release();

	//update();
	//End old

}

void Exit::updateAction(bool repeat)
{
	Element::updateAction(repeat);
	/*exitMovieClip.scaleX = dirState.scale;
	exitMovieClip.gotoAndPlay1(1);*/
	if(exitMovieClip)
		exitMovieClip->runActionNormal();
}

void Exit::layout()
{
	if(!_nameTxt)
		return;

	if(_eleName != "")
		_nameTxt->setString(_eleName.c_str());
	_nameTxt->setPosition(ccp(POSX(22.0f), POSX(10.0f)));
}

void Exit::setGlow(bool value)
{
	Element::setGlow(value);
}

bool Exit::isHit()
{

	/*if(exitMovieClip==null || exitMovieClip.bitmapData==null)return false;
	var pixel:Number=exitMovieClip.bitmapData.getPixel32(exitMovieClip.bitmap.mouseX,exitMovieClip.bitmap.mouseY);
	return pixel>0;*/
	//return hitTest();
	return false;
} 

void Exit::dispose()
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

bool Exit::hitTest(CCPoint point)
{
	//bool isHit = false;

	//if(exitMovieClip && exitMovieClip.bitmapData)
	//{
	//	isHit =  exitMovieClip.bitmapData.hitTest(new Point(this.x+exitMovieClip.bitmap.x,this.y+exitMovieClip.bitmap.y),0x00,point);
	//}
	//if(!isHit && _bitmap)
	//{
	//	isHit =  _bitmap.bitmapData.hitTest(new Point(this.x+_bitmap.x,this.y+_bitmap.y),0x00,point);
	//}

	//Begin Kenfly 20130118
	//if(!exitMovieClip || !exitMovieClip->normalAnimation || !exitMovieClip->getPlayerSprite())
	//	return false;

	//CCSize size = exitMovieClip->getPlayerSprite()->getContentSize();

	if (! exitMovieClip)
		return false;
	CCSize size = exitMovieClip->getSize();
	//End Kenfly 20130118

	CCPoint pos = TileUtil::Instance()->changeTileToPixs(ccp(this->_exitVo.x, this->_exitVo.y));
	if(point.x > (pos.x - size.width / 2) && point.x < (pos.x + size.width / 2)
		&& point.y > (pos.y - size.height / 2) && point.y < (pos.y + size.height / 2))
		return true;

	return false;
}

Exit::Exit(const Exit& RightSides)
{
//    Element::Element(RightSides);

	if(!exitMovieClip)
		exitMovieClip = new BitmapMovieClip();
	memcpy((void*)exitMovieClip, (void*)RightSides.exitMovieClip, sizeof(*(RightSides.exitMovieClip)));

	if(_nameTxt)
		memcpy((void*)_nameTxt, (void*)RightSides._nameTxt, sizeof(*(RightSides._nameTxt)));

	*this = RightSides;
}

Exit& Exit::operator = (const Exit& RightSides)
{
	Element::operator = (RightSides);

	if(!exitMovieClip)
		exitMovieClip = new BitmapMovieClip();
	memcpy((void*)exitMovieClip, (void*)RightSides.exitMovieClip, sizeof(*(RightSides.exitMovieClip)));

	if(_nameTxt)
		memcpy((void*)_nameTxt, (void*)RightSides._nameTxt, sizeof(*(RightSides._nameTxt)));

	return *this;
}

Exit::~Exit()
{
	//exitMovieClip->dispose(true);
	//exitMovieClip->release();
}
