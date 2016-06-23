#include "MineItem.h"
#include "model/silverMine/SilverMineManage.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/LangManager.h"
#include "model/silverMine/SilverConst.h"
#include "MineView.h"

const int NONADJACENT = -1;
const int ADJACENT_MOVE = 0;
const int ADJACENT_PK = 1;

const int ILLEGAL_TYPE = -1;
const int MOVE_TYPE = 0;
const int PK_TYPE = 1;
const int SPEED_TYPE = 2;
const int RAID_TYPE = 3;
const int HARASS_TYPE = 4;
const int SEARCH_TYPE = 5;


MineItem::MineItem()
{
	pContainer = 0;
	_mineID = 0;
	_doubleMc = 0;
	_pkMc = 0;
	_moveMc = 0;
	_operateType = 0;
	_frame = 0;

	//NONADJACENT = -1;
	//ADJACENT_MOVE = 0;
	//ADJACENT_PK = 1;

	//ILLEGAL_TYPE = -1;
	//MOVE_TYPE = 0;
	//PK_TYPE = 1;
	//SPEED_TYPE = 2;
	//RAID_TYPE = 3;
	//HARASS_TYPE = 4;
	//SEARCH_TYPE = 5;
}

MineItem::~MineItem()
{}

bool MineItem::init(MineView* pContainer, int mineID)
{
	if (!LayerNode::init())
		return false;

	this->pContainer = pContainer;
	_mineID = mineID;
	_basicMineVo = SilverMineManage::Instance()->getBasicCfgByID(mineID);
	//
	this->setPosition(ccp(POSX(_basicMineVo.x), POSX(_basicMineVo.y)));
	//btn
	{
		char str[50];
		if (_basicMineVo.mineLev == 1)			
			sprintf(str, "silvermine_icon5.png");
		else
			sprintf(str, "icon_%d.png", _basicMineVo.mineLev);

		CCSprite* p1 = CCSprite::spriteWithSpriteFrameName(str);
		CCSprite* p2 = CCSprite::spriteWithSpriteFrameName(str);
		CCSprite* p3 = CCSprite::spriteWithSpriteFrameName(str);
		_handleBtn = CCMenuItemImage::itemFromNormalSprite(
			p1, 
			p2, 
			p3, 
			this, 
			menu_selector(MineItem::itemClick) );
		_handleBtn->setPosition(ccp(POSX(0), POSX(0)));
		_handleBtn->setTag(0);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_handleBtn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_guild-1);
		this->addChild(buttonMenu, 0, 10);	
	}
	//

	_pkMc = new SpriteNode();
	_pkMc->initWithSpriteFrameName("mf_fight.png");
	this->addChild(_pkMc);
	_pkMc->release();
	_pkMc->setScale(0.5f);

	_moveMc = new SpriteNode();
	_moveMc->initWithSpriteFrameName("mf_shoes.png");
	this->addChild(_moveMc);
	_moveMc->release();
	_moveMc->setScale(0.5f);
	_moveMc->setAnchorPoint(ccp(0.4, 0.7));

	_doubleMc = new SpriteNode();
	_doubleMc->initWithSpriteFrameName("x2.png");
	this->addChild(_doubleMc);
	_doubleMc->release();
	_doubleMc->setScale(0.5f);
	//		
	//_skin.addEventListener(MouseEvent.CLICK, itemClick);
	//_skin.addEventListener(MouseEvent.MOUSE_OVER, itemOver);
	return true;
}

void MineItem::itemClick(CCObject* pSender)
{
	struct sdata
	{
		int type;
		int mineID;
	};

	switch(_operateType)
	{
		case MOVE_TYPE:
			pContainer->dispatchEvent(SilverConst::MOVE_MINE, &_mineID);
			break;
		case PK_TYPE: // 与Move_Type同样的流程 
			pContainer->dispatchEvent(SilverConst::MOVE_MINE, &_mineID);
			break;
		case RAID_TYPE:
			{
				sdata d;
				d.type = SilverConst::TOKEN_RAID;
				d.mineID = _mineID;

				pContainer->dispatchEvent(SilverConst::USE_TOKEN, &d);
			}
			break;
		case SEARCH_TYPE:
			{
				sdata d;
				d.type = SilverConst::TOKEN_SEARCH;
				d.mineID = _mineID;

				pContainer->dispatchEvent(SilverConst::USE_TOKEN, &d);
			}
			break;
		case HARASS_TYPE:
			{
				sdata d;
				d.type = SilverConst::TOKEN_HARASS;
				d.mineID = _mineID;

				pContainer->dispatchEvent(SilverConst::USE_TOKEN, &d);
			}
			break;
		case SPEED_TYPE:
			{
				sdata d;
				d.type = SilverConst::TOKEN_SPEED;
				d.mineID = _mineID;

				pContainer->dispatchEvent(SilverConst::USE_TOKEN, &d);
			}
			break;
		case ILLEGAL_TYPE:
			LangManager::msgShow("SLM007");
			break;
	}	
}

void MineItem::updateMineVo(SilverMineVo mineVo)
{
	if(_mineID != mineVo.id)return;
			
	_mineVo = mineVo;
			
	int frame = getFrameByCampId(mineVo.campId);
	//_skin.gotoAndStop(frame);
			
	if(mineVo.isDouble){
		_doubleMc->setIsVisible(true);
	}
	else{
		_doubleMc->setIsVisible(false);
	}
}

int MineItem::getFrameByCampId(int campId)
{
	int frame = -1;
	if (_mineVo.id == 0 || _mineVo.id == 27 || _mineVo.id == 30)
		return frame;
	
	switch(campId)
	{
	case 0:
		{
			if (_frame)
				_frame->removeFromParentAndCleanup(true);
			frame=2;
			char str[50];
			sprintf(str, "frame%d.png", frame);
			_frame = new SpriteNode();
			_frame->initWithSpriteFrameName(str);
			this->addChild(_frame);
			_frame->setPosition(ccp(POSX(-10), POSX(-10)));
			_frame->release();
			_frame->setScale(0.5f);
		}
		break;
	case 1:
		{
			if (_frame)
				_frame->removeFromParentAndCleanup(true);
			frame=3;
			char str[50];
			sprintf(str, "frame%d.png", frame);
			_frame = new SpriteNode();
			_frame->initWithSpriteFrameName(str);
			this->addChild(_frame);
			_frame->setPosition(ccp(POSX(-10), POSX(-10)));
			_frame->release();
			_frame->setScale(0.5f);
		}
		break;
	case 2:
		{
			if (_frame)
				_frame->removeFromParentAndCleanup(true);
			frame=4;
			char str[50];
			sprintf(str, "frame%d.png", frame);
			_frame = new SpriteNode();
			_frame->initWithSpriteFrameName(str);
			this->addChild(_frame);
			_frame->setPosition(ccp(POSX(-10), POSX(-10)));
			_frame->release();
			_frame->setScale(0.5f);
		}
		break;
	default:
		{
			frame=1;
			if (_frame)
			{
				_frame->removeFromParentAndCleanup(true);
				_frame = 0;
			}
		}
		break;
	}
	return frame;
}

// 设置点击该Item的操作类型  
void MineItem::setOperateType(int operateType)
{
	_operateType = operateType;
	switch(_operateType)
	{
		case MOVE_TYPE:
			setMoveEnable(true);
			setPkEnable(false);
			setMouseEnable(true);
			break;
		case PK_TYPE:
			setPkEnable(true);
			setMoveEnable(false);
			setMouseEnable(true);
			break;
		case RAID_TYPE:
			setPkEnable(true);
			setMoveEnable(false);
			setMouseEnable(true);
			break;
		case SPEED_TYPE:
			setMoveEnable(true);
			setPkEnable(false);
			setMouseEnable(true);
			break;
		case HARASS_TYPE:
			setMoveEnable(true);
			setPkEnable(false);
			setMouseEnable(true);
			break;
		case SEARCH_TYPE:
			setMoveEnable(true);
			setPkEnable(false);
			setMouseEnable(true);
			break;
		case ILLEGAL_TYPE: 
			setPkEnable(false);
			setMoveEnable(false);
			setMouseEnable(false);
			break;
	}
}
		
void MineItem::setMoveEnable(bool value)
{
	_moveMc->setIsVisible(value);
	if (value)
	{
		CCFiniteTimeAction* fir = cocos2d::CCRotateTo::actionWithDuration(0.5f, -30);

		CCFiniteTimeAction* sec = cocos2d::CCRotateTo::actionWithDuration(0.5f, 45.0f);

		_moveMc->runAction( CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(fir, sec)));
	}
	else
	{
		_moveMc->stopAllActions();
	}
}
		
void MineItem::setPkEnable(bool value)
{
	_pkMc->setIsVisible(value);
}

void MineItem::setMouseEnable(bool value)
{
	_handleBtn->setIsEnabled(value);
}

// type为令牌ID即种类 
void MineItem::useToken(int type)
{
	int myCamp = pContainer->getcurCampID();
	setPkEnable(false);
	setMoveEnable(false);
			
	switch(type)
	{
		case SilverConst::TOKEN_RAID:
			tokenRaid();
			break;
		case SilverConst::TOKEN_HARASS:
			tokenHarass();
			break;
		case SilverConst::TOKEN_SPEED:
			tokenSpeed();
			break;
		case SilverConst::TOKEN_SEARCH:
			tokenSearch();
			break;
		default:
			break;
	}
}

// 袭击
void MineItem::tokenRaid()
{
	// 当前矿有人占领且属不同阵营 则可操作
	if(_mineVo.campId!=SilverConst::NON_CAMP && pContainer->getcurCampID()!=_mineVo.campId 
		&& (_mineVo.id!=0||_mineVo.id!=27||_mineVo.id!=30) ){
		setOperateType(RAID_TYPE);		
	}
	else{
		// 	
	}
}
		
// 干扰
void MineItem::tokenHarass()
{
	if(_mineVo.campId!=SilverConst::NON_CAMP && _mineVo.campId!=pContainer->getcurCampID()
		&& (_mineVo.id!=0||_mineVo.id!=27||_mineVo.id!=30)){
		setOperateType(HARASS_TYPE);
	}
	else{
		// 
	}
}
		
// 奔驰
void MineItem::tokenSpeed()
{
	if(_mineVo.campId == pContainer->getcurCampID()
		&& (_mineVo.id!=0||_mineVo.id!=27||_mineVo.id!=30)){
		setOperateType(SPEED_TYPE);
	}
	else{
		//
	}
}
		
// 查
void MineItem::tokenSearch()
{
	if(_mineVo.id==0 || _mineVo.id==27 || _mineVo.id==30){
		// 大本营不能查 
	}
	else if(_mineVo.id==pContainer->getcurMineID()){
		// 自己所在阵营
	}
	else{
		// 可查 
		setOperateType(SEARCH_TYPE);
	}
}

// 检查this于testMineVo是否相邻 
int MineItem::testNeighour(SilverMineVo testMineVo)
{/*
	if(!_mineVo || !testMineVo)
		return NONADJACENT;*/
			
	int nearType = NONADJACENT;
	int testCampId = pContainer->whichCampHome(testMineVo.id);
	BasicMineVo testBasicVo = SilverMineManage::Instance()->getBasicCfgByID(testMineVo.id);
	bool isNear = isNeighbour(_basicMineVo, testBasicVo);
			
	if(_mineVo.campId == testCampId){  // 自己的大本营 
		nearType = isNear?ADJACENT_MOVE:NONADJACENT;
				
	}else if(testCampId != SilverConst::NON_CAMP){	// 别人的大本营 
		nearType = NONADJACENT;
				
	}else{  // 非大本营
				
		if(false==isNear){  //不相邻 
			nearType = NONADJACENT;
		}
		else{
			if(_mineVo.campId==testMineVo.campId || -1==testMineVo.campId){ // 阵营相同或testMine无人占领
				nearType = ADJACENT_MOVE;
			}
			else{
				nearType = ADJACENT_PK;
			}
		}
	}
	return nearType;
}
		
bool MineItem::isNeighbour(BasicMineVo mineVo1, BasicMineVo mineVo2)
{
	if(mineVo1.mineId==mineVo2.mineId)
		return false; 
			
	bool result = false;
	int distanceX = (mineVo1.xPos-mineVo2.xPos)>0?(mineVo1.xPos-mineVo2.xPos):(mineVo2.xPos-mineVo1.xPos);
	int distanceY = (mineVo1.yPos-mineVo2.yPos)>0?(mineVo1.yPos-mineVo2.yPos):(mineVo2.yPos-mineVo1.yPos);
	if(distanceX!=2 && (distanceX+distanceY)==2)
	{
		result = true;
	}
			
	return result;
}

SilverMineVo MineItem::getmineVo() 
{
	return _mineVo;
}