#include "MinePanel.h"
#include "MineView.h"
#include "model/silverMine/SilverMineManage.h"
#include "MineBg.h"
#include "MineItem.h"
#include "model/silverMine/SilverConst.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "utils/GlobalScale.h"

MinePanel::MinePanel()
{
	_campMc = 0;
	_curCampID = -1;
	_curMineID = -1;
	m_stateMC = STATE_IDLE;
	_timeCounter = 0.0f;
	m_actionImm = false;
	_curItem = 0;
	pContainer = 0;
	m_parlayer = 0;
}

MinePanel::~MinePanel()
{}

bool MinePanel::init(LayerNode* layer, MineView* pContainer)
{
	if (!LayerNode::init())
		return false;

	m_parlayer = layer;
	this->pContainer = pContainer;
	//_itemDic = new Dictionary;
	//_keyDic = new Dictionary;
	_itemDic.clear();
 	for(int i=0; i<=36; i++)
	{
		MineItem* item = new MineItem();
		item->init(pContainer, i);
		_itemDic.insert(std::map<int, MineItem*>::value_type(i, item));
		layer->addChild(item, MineView::Z_mineItem);
		item->release();
	}


	//

	//
	schedule (schedule_selector(MinePanel::step));//keving
	return true;
}

int MinePanel::getcurCampID()
{
	return _curCampID;
}

int MinePanel::getcurMineID()
{
	return _curMineID;
}

void MinePanel::move2mine(int mineId, bool imm)
{
	_campMc->stopAllActions();

	BasicMineVo vo = SilverMineManage::Instance()->getBasicCfgByID(mineId);
	if(480 == GlobalScale::Instance()->getStandardWidth())
	{
		vo.x += 480;
		vo.y += 320;
	}
	if (imm)
	{
		m_stateMC = STATE_IDLE;
	//	_campMc->setPosition(ccp(POSX(vo.x), POSX(vo.y)));
		_campMc->setPosition(ccp(POSX(vo.x), POSX(vo.y)));
		//
		CCPoint campMcScreenPos = getScreenPos(_campMc, true);
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCPoint centerScreenPos = ccp(screenSize.width/2, screenSize.height/2);

		CCSize dis = CCSizeMake(centerScreenPos.x - (campMcScreenPos.x),
			centerScreenPos.y - (campMcScreenPos.y));

		LayerNode* pContainer = (LayerNode*)_campMc->getParent();
		if (pContainer)
		{
			pContainer->setPosition(ccp(
				pContainer->getPosition().x+dis.width, 
				pContainer->getPosition().y+dis.height
				));
		}
	}
	else
	{
		m_stateMC = STATE_MOVING;
		CCAction* moveAct = cocos2d::CCMoveTo::actionWithDuration(1.0f, ccp(POSX(vo.x), POSX(vo.y)));
		_campMc->runAction(moveAct);
		_timeCounter = 0.0f;
	}
	
}



// 阵营 0-2 
void MinePanel::setMyCamp(int campId)
{
	if (!_campMc)
	{
		if (campId==0)
		{
			_campMc = new LayerNode();
			_campMc->init();
			m_parlayer->addChild(_campMc, MineView::Z_campMc, MineView::TAG_campMc);
			_campMc->release();

			SpriteNode* _campMc2 = new SpriteNode();
			_campMc2->initWithSpriteFrameName("_head.png");
			if(480 == GlobalScale::Instance()->getStandardWidth())
			{
				_campMc2->setPosition(ccp(-240, -160));
			}
			else
			{
				_campMc2->setPosition(ccp(0, 0));
			}
			_campMc->addChild(_campMc2);
			_campMc2->release();
		}
		else
		{
			_campMc = new LayerNode();
			_campMc->init();
			m_parlayer->addChild(_campMc, MineView::Z_campMc, MineView::TAG_campMc);
			_campMc->release();

			SpriteNode* _campMc2 = new SpriteNode();
			_campMc2->initWithFile("assets/ui/silvermine/_head2.png");
			if(480 == GlobalScale::Instance()->getStandardWidth())
			{
				_campMc2->setPosition(ccp(-240, -160));
			}
			else
			{
				_campMc2->setPosition(ccp(0, 0));
			}
			_campMc->addChild(_campMc2);
			_campMc2->release();
		}
	}

	_curCampID = campId;
//	_campMc.gotoAndStop(campId+1);
	_campMc->setIsVisible(true);

	switch(_curCampID)
	{
		case 0:  /*阵营0 大本营id=0*/
			move2mine(0, true);
			break;
		case 1:  /*阵营1 大本营id=27*/
			move2mine(27, true);
			break;
		case 2:  /*阵营2 大本营id=30*/
			move2mine(30, true);
			break;
		default:
			break;
	}
}

void MinePanel::setMyMine(int mineID)
{
	//解决安卓编译问题-》良杰提出的问题
	/*
	int NONADJACENT = -1;
	int ADJACENT_MOVE = 0;
	int ADJACENT_PK = 1;

	int ILLEGAL_TYPE = -1;
	int MOVE_TYPE = 0;
	int PK_TYPE = 1;
	int SPEED_TYPE = 2;
	int RAID_TYPE = 3;
	int HARASS_TYPE = 4;
	int SEARCH_TYPE = 5;
	*/

	_curMineID = mineID;
	if (_curMineID != -1)
	{
		_curItem = _itemDic[mineID];
		move2mine(mineID);

		if (pContainer->getTokenType() == -1)
		{
			for(int i=0; i<=14; i++)
			{
				MineItem* item = _itemDic[i];
				if (!item)
					continue;
				int nearType = _curItem->testNeighour(item->getmineVo());
				switch(nearType)
				{
				case 0://MineItem::ADJACENT_MOVE:解决安卓编译问题-》良杰提出的问题
						item->setOperateType(0);//MineItem::MOVE_TYPE解决安卓编译问题-》良杰提出的问题
						break;
				case 1://MineItem::ADJACENT_PK:解决安卓编译问题-》良杰提出的问题
						item->setOperateType(1);//MineItem::PK_TYPE解决安卓编译问题-》良杰提出的问题
						break;
				case -1://MineItem::NONADJACENT:解决安卓编译问题-》良杰提出的问题
						item->setOperateType(-1);//MineItem::ILLEGAL_TYPE解决安卓编译问题-》良杰提出的问题
						break;
				default:
					break;
				}


			}
		}
		int campID = pContainer->whichCampHome(_curMineID);
		if(campID == SilverConst::NON_CAMP){
			pContainer->setDigEnable(false);
		}
	}
}

void MinePanel::useToken(int type)
{
	for(int i=0; i<=36; i++)
	{
		MineItem* item = _itemDic[i];
 		item->useToken(type);
	}
}
		 

void MinePanel::step(ccTime dt)
{
	if (m_stateMC == STATE_IDLE)
	{
		//const CCPoint& offsetPix = _campMc->getOffsetPositionInPixels();
		CCPoint offsetPix = getScreenPos(_campMc, true);
		_timeCounter = 0.0f;
	//	CCLog(">_<    STATE_IDLE:   %f  %f", offsetPix.x, offsetPix.y);
	}
	if (m_stateMC == STATE_MOVING)
	{
		_timeCounter += dt;
		CCPoint campMcScreenPos = getScreenPos(_campMc, true);
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCPoint centerScreenPos = ccp(screenSize.width/2, screenSize.height/2);

		CCSize dis = CCSizeMake(centerScreenPos.x - POSX(campMcScreenPos.x),
			centerScreenPos.y - POSX(campMcScreenPos.y));
		//计算要走的长度
		double stepLen = 100.0 / 2;
		double disLen = dis.width*dis.width+dis.height*dis.height;
		disLen = sqrt(disLen);
		if (stepLen < disLen)
		{
			dis.width *= stepLen/disLen;
			dis.height *= stepLen/disLen;
		}

		if (_timeCounter > 1.f && dis.width >=0.0f && dis.width <= 0.0f  && dis.height >=0.0f && dis.height <= 0.0f)
		{
			m_stateMC = STATE_IDLE;
			_timeCounter = 0.0f;
			return;
		}
		LayerNode* pContainer = (LayerNode*)_campMc->getParent();
		//MineBg* pbg = (MineBg*)pContainer->getChildByTag(MineView::TAG_mineBg);
		if (pContainer)
		{
			pContainer->setPosition(ccp(
				pContainer->getPosition().x+dis.width, 
				pContainer->getPosition().y+dis.height
				));
		}


		//CCLog(">_<    STATE_MOVING:   %f  %f", offsetPix.x, offsetPix.y);
	}
		
}

void MinePanel::updateMinePanel(std::list<SilverMineVo>& mines)
{
	for (std::list<SilverMineVo>::iterator it = mines.begin(); it != mines.end(); it++)
	{
		SilverMineVo silverMineVo = *it;
		MineItem* item = _itemDic[silverMineVo.id];
		if (item)
		{
			item->updateMineVo(silverMineVo);
		}
	}	
}
