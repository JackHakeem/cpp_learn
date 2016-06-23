//
//  Element.cpp
//  HLQS
//
//  Created by edward liu on 12-3-4.
//  Copyright (c) 2012年 4399. All rights reserved.
//

#include "Element.h"
#include <math.h>
#include "utils/Utils.h"
#include "model/scene/vo/SceneConst.h"
#include "manager/SourceCacheManage.h"
#include "util/TileUtil.h"
#include "utils/Timer.h"
#include "utils/ScaleUtil.h"

Element::Element()
{
    startPoint.x = 0.0f;
    startPoint.y = 0.0f;
    endPoint.x = 0.0f;
    endPoint.y = 0.0f;
    
    m_mapPoint.x = 0.0f;
    m_mapPoint.y = 0.0f;
    
    m_mapStartPoint.x = 0.0f;
    m_mapStartPoint.y = 0.0f;
    
    m_mapEndPoint.x = 0.0f;
    m_mapEndPoint.y = 0.0f;
	
	//m_baseSprite = new CCSprite();
	m_baseSprite = NULL;

	//from flash
	_angle = 0.0f;
	stepX = 0.0f;
	stepY = 0.0f;
	_speed = 0.0f;
	moveTime = 0;

	oldTime = 0;
	_tmpx = 0.0f;
	_tmpy = 0.0f;
	canRedraw = false;
	isLoading = false;
	hasDispose = false;

	//int _id = 0;
	_isInteractive = true;

	poseState = NULL;
	dirState = NULL;
	init();
}

Element::~Element()
{
	if(poseState)
	{
		delete poseState;
		poseState = 0; // LH0713
	}

	if(dirState)
	{
		delete dirState;
		dirState = 0; // LH0713
	}
}

bool Element::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	if(!poseState)
	{
		poseState = new PoseState();
		poseState->_suzhuType = getThingType();
	}
	if(!dirState)
		dirState = new DirState();

	poseState->addEventListener(SceneConst::CHANGE, this, callfuncND_selector(Element::changePoseHandler));
	dirState->addEventListener(SceneConst::CHANGE, this, callfuncND_selector(Element::changeDirHandler));

	poseState->state(SceneConst::STAND);
	dirState->state(2);

    return true;
}

void Element::setBaseSpritePos(float x,float y)
{
	if(m_baseSprite)
		m_baseSprite->setPosition(ccp(x, y));
    return;
}

void Element::setStartPoint(float x, float y)
{
    startPoint.x = x;
    startPoint.y = y;
}

CCPoint * Element::getStartPoint()
{
    return &startPoint;
}

void Element::setEndPoint(float x,float y)
{
    endPoint.x = x;
    endPoint.y = y;
}

CCPoint *  Element::getEndPoint()
{
    return &endPoint;
}

//add by edwardliu
CCPoint Element::getMapEndPoint()
{
    return m_mapEndPoint;
}

CCPoint Element::getMapStartPoint()
{
    return m_mapStartPoint;
}

void Element::setStartPointByScreen(CCPoint cp, CCPoint pos_map, CCPoint pos_layer, float height, float width)
{
    startPoint.x = cp.x;
    startPoint.y = cp.y;
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    m_mapStartPoint.x = (float)width / 2.0f + cp.x + pos_map.x + pos_layer.x;
    m_mapStartPoint.y = (float)height / 2.0f + cp.y - screenSize.height - pos_map.y - pos_layer.y;
    
	setPosition(ccp(cp.x, (float)screenSize.height - cp.y));
}

void Element::setStartPointByMapCell(CCPoint cell, CCPoint pos,  CCPoint pos_layer, float height, float width)
{
    //CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    float w = TileUtil::Instance()->getTileWidth();
	float h = TileUtil::Instance()->getTileHeight();
    m_mapStartPoint.x = cell.x * w + w / 2.0;
    m_mapStartPoint.y = cell.y * h + h / 2.0;
    
    CCPoint cp;
    cp.x = m_mapStartPoint.x + pos.x + pos_layer.x - (float)width / 2.0f;
    cp.y = pos.y + pos_layer.y + (float)height / 2.0f - m_mapStartPoint.y;

    //m_baseSprite->setPosition(ccp(cp.x, cp.y));
	//by edward 0406
	setPosition(ccp(cp.x, cp.y));
}

void Element::setStartPointByMap(CCPoint map, CCPoint pos,  CCPoint pos_layer, float height, float width)
{
	//setPosition(map);
	//return;
	//CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	m_mapStartPoint.x = map.x;
	m_mapStartPoint.y = map.y;

	CCPoint cp;
	cp.x = m_mapStartPoint.x + pos.x + pos_layer.x - (float)width / 2.0f;
	cp.y = pos.y + pos_layer.y + (float)height / 2.0f - m_mapStartPoint.y;

	//m_baseSprite->setPosition(ccp(cp.x, cp.y));
	//by edward 0406
	setPosition(ccp(cp.x, cp.y));//cp.y
}

CCPoint Element::setEndPointByScreen(CCPoint cp, CCPoint pos_map, CCPoint pos_layer, float height, float width)
{
    endPoint.x = cp.x;
    endPoint.y = cp.y;
    
	    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    m_mapEndPoint.x = (float)width / 2.0f + cp.x - pos_map.x - pos_layer.x;
    m_mapEndPoint.y = (float)height / 2.0f + cp.y - screenSize.height + pos_map.y + pos_layer.y;
    
	return m_mapEndPoint;
    //CCLog("----m_startPoint.x[%f], m_mapEndPoint.x [%f]= (float)width / 2.0f [%f]+ cp.x [%f]+ pos.x [%f] + [%f]",m_mapStartPoint.x, m_mapEndPoint.x, (float)width / 2.0f, cp.x , pos_map.x, pos_layer.x);
    //CCLog("----m_startPoint.y[%f],m_mapEndPoint.y [%f]= (float)height / 2.0f [%f]+ cp.y [%f]- screenSize.height [%f] - pos.y [%f] - pos_map.y[%f]",m_mapStartPoint.y, m_mapEndPoint.y, (float)height / 2.0f , cp.y , screenSize.height , pos_layer.y);
}


//void Element::setStartPointByMapCell(CCPoint cp)
//{
//    m_mapStartPoint.x = cp.x * (float)TILE_WIDTH + (float)TILE_WIDTH / 2.0f;
//    m_mapStartPoint.y = cp.y * (float)TILE_HEIGHT + (float)TILE_HEIGHT / 2.0f;
//}



void Element::setCurrentStartPoint(CCPoint pos, float h, float w)
{
    CCPoint pt;
	if(m_baseSprite)
		pt = m_baseSprite->getPosition();
    m_mapStartPoint.x = w / 2.0f + pt.x - pos.x;
    m_mapStartPoint.y = h / 2.0f - pt.y + pos.y;
}

void Element::mapStartPoint(CCPoint pos)
{
	m_mapStartPoint = pos;
}

CCPoint *  Element::getMapCurrentPoint()
{
    return &m_mapStartPoint;
}

CCPoint Element::getMapCurrentCell()
{
    CCPoint cell;
    cell.x = (float)((int)m_mapStartPoint.x / TileUtil::Instance()->getTileWidth());
    cell.y = (float)((int)m_mapStartPoint.y / TileUtil::Instance()->getTileHeight());
    return cell;
}


//from flash
void Element::changePoseHandler(CCNode* n, void* data)
{
	poseChange();
	redraw();
}

void Element::changeDirHandler(CCNode* n, void* data)
{
	redraw();
}

void Element::redraw()
{
	canRedraw = true;
}

void Element::dispose()
{
	hasDispose = true;
	if(poseState)
		poseState->removeEventListener(SceneConst::CHANGE);
	if(dirState)
		dirState->removeEventListener(SceneConst::CHANGE);

	if(poseState)
	{
		delete poseState;
		poseState = NULL;
	}
	
	if(dirState)
	{
		delete dirState;
		dirState = NULL;
	}

	redraw();
}

void Element::nextPosition()
{
	if(canRedraw)
	{
		update();
	}
	if(moveTime==0 || (poseState && poseState->lockMove()))
		return;

//	CCLog("---------render time : %f", Timer::millisecondNow());
//	CCLog("----moveTime:%d, stepX:%f, stepY:%f, _tmpx:%f, _tmpy:%f ", moveTime, stepX, stepY, _tmpx, _tmpy);
	moveTime--;
	
	_tmpx += stepX;
	_tmpy -= stepY;
	
	m_mapStartPoint.x += stepX;
	m_mapStartPoint.y += stepY;

	updatePosition();

	
	struct Data
	{
		bool first;
		Element* player;
	};
	Data d;
	d.first = true;
	d.player = this;

	dispatchEvent(SceneConst::CHANGE_POSITION, (void*)(&d));
	//it seemed do nothing, the next
	if(stepX!=0)
		dispatchEvent(SceneConst::CHANGE_POSITION_X, (void*)(&d));

	if(stepY!=0)
		dispatchEvent(SceneConst::CHANGE_POSITION_Y, (void*)(&d));

	if(moveTime==0)
		moveComplete();
}

void Element::updatePosition()
{
	CCPoint pos;
	pos.x = _tmpx;
	pos.y = _tmpy;
	setPosition(pos);
}

void Element::move1(CCPoint point, int delay)
{
	CCPoint pos = getMapStartPoint();
	float disX = point.x - pos.x;
	float disY = point.y - pos.y;
	_angle = atan2(disY, disX);
	_endPoint = point;
	if(poseState)
		poseState->state(SceneConst::MOVE);
	
	float dis = sqrt(disX * disX + disY * disY);
	int n = 0;
	if(delay > 0)
	{
		//n = round( 24 * delay / 1000); + 0.5 表示四舍五入
		n = int(24.0f * (float)delay / 1000.0f + 0.5);
	}
	else
	{
		//n = round(dis/ Utils::Instance()->changeSpeedToPixs(_speed));
		n = int(dis / Utils::Instance()->changeSpeedToPixs(_speed) + 0.5);
	}

	if(n==0) 
	{
		moveComplete();
		return;
	}
	float stepLen = dis/n;
	stepX = stepLen * cos(_angle);
	stepY = stepLen * sin(_angle);
	moveTime = n;

	CCPoint pos1 = getPosition();
	_tmpx = pos1.x;
	_tmpy = pos1.y;
	dirToPoint(point);

	if(poseState)
		poseState->state(SceneConst::MOVE);
}

void Element::dirToPoint(CCPoint point)
{
	CCPoint pos = getMapStartPoint();
	int tmpdir = Utils::Instance()->getDir(pos.x, pos.y, point.x, point.y);
	if(dirState)
		dirState->state(tmpdir);
}

BitmapMovieClip* Element::loadDefautRes()
{
	//std::string DefautAsset = "assets/res/1/model";
	/*if(!(SourceCacheManage::Instance()->has(DefautAsset)))
	{
		SourceCacheManage::Instance()->load(DefautAsset, 10);
	}

	BitmapMovieClip* m =  SourceCacheManage::Instance()->getObject(DefautAsset);
	if(m)
	{
		return m;
	}*/

	std::string DefautAsset = "assets/res/1";
	BitmapMovieClip* movieClip = SourceCacheManage::Instance()->loadModel(DefautAsset, 1, 0.1f, true);

	return movieClip;
}

/**
*完成后处理函数 
* 
*/
void Element::moveComplete()
{
	moveTime=0;
	_endPoint = ccp(0.0f, 0.0f);
}

void Element::update(bool repeat)
{
	updateAction(repeat);
	updateInfo();
	layout();
}

void Element::layout()
{}

void Element::updateAction(bool repeat)
{
	canRedraw = false;
}


void Element::updateInfo()
{
}



void Element::stop()
{
	moveComplete();
}

	
void Element::speed(float value)
{
	_speed = value;
			
}
float Element::speed()
{
	return _speed;
}		

//void Element::id(int value)
//{
//	_id = value;
//}
//
//int Element::id()
//{
//	return _id;
//}

void Element::eleName(std::string value)
{
	_eleName = value;
}
std::string Element::eleName()
{
	return _eleName;
}

ResourceVo Element::getResource()
{
	return _res;
}

void Element::setResource(ResourceVo &info)
{
	_res = info;
}

//void Element::otherInfos(std::vector<int>& value)
//{
//	_otherInfos = value;
//}
//std::vector<int>* Element::otherInfos()
//{
//	return &(_otherInfos);
//}

//void Element::type(std::string value)
//{
//	_type = value;
//}

//std::string Element::type()
//{
//	return _type;
//}
		
void Element::isInteractive(bool value)
{
	_isInteractive = value;
}
bool Element::isInteractive()
{
	return _isInteractive;
}
 
bool Element::isHit(CCPoint point)
{
	return false;
}
		
void Element::setGlow(bool value)
{
	
}

void Element::step()
{
	nextPosition();
}
		
void Element::setSelect(bool value)
{
	IElement::setSelect(value);
}

bool Element::hitTest(CCPoint)
{
	return false;
}

Element::Element(const Element& RightSides)
{
	//if(!poseState)
	poseState = new PoseState();
	poseState->_suzhuType = this->getThingType();

	memcpy(poseState, RightSides.poseState, sizeof(*(RightSides.poseState)));
	if(!dirState)
		dirState = new DirState();
	memcpy(dirState, RightSides.dirState, sizeof(*(RightSides.dirState)));

	//if(m_baseSprite)
	//	memcpy(m_baseSprite, RightSides.m_baseSprite, sizeof(*(RightSides.m_baseSprite)));
	
	*this = RightSides;
}

Element& Element::operator = (const Element& RightSides)
{
	//if(!poseState)
	poseState = new PoseState();
	poseState->_suzhuType = this->getThingType();

	memcpy(poseState, RightSides.poseState, sizeof(*(RightSides.poseState)));
	if(!dirState)
		dirState = new DirState();
	memcpy(dirState, RightSides.dirState, sizeof(*(RightSides.dirState)));

	//if(m_baseSprite)
	//	memcpy(m_baseSprite, RightSides.m_baseSprite, sizeof(*(RightSides.m_baseSprite)));

	return *this;
}

void Element::poseChange()
{
}