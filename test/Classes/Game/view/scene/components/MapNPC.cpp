#include "utils/loader/KKAnimationFactory.h"
#include "MapNPC.h"
#include "model/com/vo/ResourceVo.h"
#include "model/com/ResourceManage.h"
#include "model/shop/ShopManager.h"
#include "model/scene/SentenceManager.h"
#include "model/scene/vo/SceneConst.h"
#include "MapNPCSprite.h"
#include "manager/SourceCacheManage.h"
#include "view/task/components/TaskState.h"
#include "util/TileUtil.h"
#include "manager/GlobalManage.h"
#include "utils/Utils.h"
#include "model/player/RoleManage.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "CCStrokeLabel/CCStrokeLabel.h"

static const int TAG_ICONMC = 101;
static const int TAG_Talk_BG = 102;

MapNPC::MapNPC()
{
	timer = 0;
	_npcVo = NULL;
	m_pTexureCanRecvTask = NULL;
	m_pTexureCanFinishTask = NULL;
	m_pTexureNoFinishTask = NULL;
	_label = NULL;

}

MapNPC::MapNPC( NPCVo* pNPCVo )
{
	if(!pNPCVo)
		return;
	timer = 0;

	m_baseSprite = NULL;
	_npcVo = NULL;
	if(!_npcVo)
	{
		_npcVo = new NPCVo();
		*_npcVo = *pNPCVo;
	}
	m_TalkVisibleTimer = NULL;

	m_bCanTalk = false;

	m_pTexureCanRecvTask = 0;
	m_pTexureCanFinishTask = 0;

	m_pTexureNoFinishTask = 0;
	ResourceVo* res = NULL;

	if(pNPCVo)
	{
		ResourceVo* vo = ResourceManage::Instance()->getRes(1, pNPCVo->_resId);
		if(vo)
			_res = *vo;
		this->_id = pNPCVo->id;
	}
	else
	{
		this->_id = 0;
	}

	if(res)
		_res = *res;


	_label = NULL;
	if(dirState)
	{
		dirState->isNPC = true;
		dirState->_state = _npcVo->state;
	}
	_speed = _npcVo->speed;
	_id = _npcVo->id;
	_hp = _npcVo->_hp;
	_maxHp = _npcVo->_maxHp;
	_mp = _npcVo->_mp;
	_maxMp = _npcVo->_maxMp;
	_eleName = _npcVo->name;
	_level = _npcVo->_lev;
	_type = NPC_TYPE;
	ResourceVo* vo = ResourceManage::Instance()->getRes(1, _npcVo->_resId);
	if(vo)
	{
		_res = *vo;
	}
	skill1 = _npcVo->skill1;
	skill2 = _npcVo->skill2;
	skill3 = _npcVo->skill3;

	init();
}

MapNPC::~MapNPC()
{
	CC_SAFE_DELETE( m_TalkVisibleTimer );
	CC_SAFE_DELETE( _npcVo );
}

void MapNPC::init()
{
	showRes();
}

void MapNPC::showRes()
{
	redraw();
}

CCSprite * MapNPC::getNpcSprite()
{
	return m_baseSprite;
}

CCSprite * MapNPC::loadNpc()
{
	//Doyang 20120712
	if(!_npcVo)
		return 0;
	
	_assetURL = _res.modelUrl();
	int id = _res.id;

	BitmapMovieClip* movieClip = NULL;
	/*if (id == 1000)
	{
	movieClip = SourceCacheManage::Instance()->loadBossModel(_assetURL, id, 0.2f, true, true);
	}*/

	if(  _npcVo->_isMonster ||
		(_npcVo->action==SceneConst::FIGHT) || (_npcVo->action==SceneConst::STORY) )
	{
		movieClip = SourceCacheManage::Instance()->loadModel(_assetURL, id, 0.2f, true, true);
		if ( movieClip)
		{
			SourceCacheManage::Instance()->reLoadModel( movieClip, _assetURL, id, 0.2f );
		}
	}
	else
	{
		movieClip = SourceCacheManage::Instance()->loadPvrNormal(_assetURL, id, BitmapMovieClip::ACTION_STAND, _npcVo->state, 0.2f, true, true);
	}

	if ( !movieClip )
	{
		_assetURL = "assets/res/1000";
		id = 1000;
		if( _npcVo->_isMonster||
			(_npcVo->action==SceneConst::FIGHT) || (_npcVo->action==SceneConst::STORY) )
		{
			movieClip = SourceCacheManage::Instance()->loadModel(_assetURL, id, 0.2f, true, true);
		}
		else
		{
			movieClip = SourceCacheManage::Instance()->loadPvrNormal(_assetURL,
				id, BitmapMovieClip::ACTION_STAND, _npcVo->state,  0.2f, true, true);
		}
	}

	if(movieClip)
	{
		if(livingMovieClip && livingMovieClip->getParent() == this)
		{
			removeChild(livingMovieClip, false);
			livingMovieClip->release();
		}

		livingMovieClip = movieClip;
		movieClip->m_resId = id;//kevin0828
		if(livingMovieClip && livingMovieClip->getParent() == NULL)
		{
			addChild(livingMovieClip);
			livingMovieClip->setAnchorPoint(ccp(0.5,0.5));
			livingMovieClip->setPosition(0, POSX(125 / 2.0f));//POSX(125 / 2)kevinpos
			livingMovieClip->release();
		}
	}

	//Doyang 20120712
	/*if(!_npcVo)
		return NULL;*/
		
	MapNPCSprite* npcSprite = new MapNPCSprite( _npcVo );
	
	if(npcSprite == NULL)
	{
		CCLog("Create NPC sprite failed");
		return 0;
	}
	m_baseSprite = npcSprite;
	m_baseSprite->setAnchorPoint(ccp(0.5,0.5));
	CCSize csSprite = m_baseSprite->getContentSize();
	std::string _NameTxt = _npcVo->name;
	//CCLabelTTF* _label = CCLabelTTF::labelWithString( _NameTxt.c_str(), g_sSimHeiFont, POSX(20) );
	CCStrokeLabel *_label = CCStrokeLabel::labelWithString(_NameTxt.c_str(), g_sSimHeiFont, POSX(22));
	if(_label)
	{
		_label->setStroke(0.5f, ccc3(0, 0, 0));
		if (!_npcVo->_isMonster)
		{
			_label->setColor( ccc3(248,248,0) );
		}
		else
		{
			_label->setColor( ccc3(250,250,0) );
		}
		
		if ( livingMovieClip )
		{
			_label->setPosition( ccp( livingMovieClip->getPosition().x, POSX(55 + 125 / 2) ) );
		}
		m_baseSprite->addChild(_label, 0, COLOR_NAMETEXT);
		_label->release();
	}
	
	if ( _npcVo->action == SceneConst::TALK )
	{
		char sIconUrl[54];
		int icon = ShopManager::Instance()->getIconByNPCID( _npcVo->id );
		if ( icon > 4 )
		{
			sprintf( sIconUrl, "npcthing_icon/0%d.png", icon - 4 );
			//sprintf( sIconUrl, "assets/ui/npc_thing/npcthing_icon/0%d.png", icon - 4 );

			if (!g_pGlobalManage->isInStory && !_npcVo->_isMonster)
			{
				//Doyang 20120712
				m_baseSprite->removeChildByTag(TAG_ICONMC, true);

				CCSprite *pIconMc = CCSprite::spriteWithSpriteFrameName( sIconUrl );
				if(pIconMc)
				{
					pIconMc->setPosition( ccp( csSprite.width/2, csSprite.height/2 + POSX(50 + 55 + 125 / 2) ) );
					m_baseSprite->addChild(pIconMc, 0, TAG_ICONMC);
				}
			}
		}
	}
	else  // NPC
	{
		addNPCTalk();
	}

	//if(  _npcVo->_isMonster ||
	//	(_npcVo->action==SceneConst::FIGHT)  )
	{
		if(livingMovieClip)
			livingMovieClip->runActionNormal(BitmapMovieClip::ACTION_STAND, _npcVo->state);
	}
	//else
	//{
	//	if(livingMovieClip)
	//		livingMovieClip->runActionPvrNormal( _npcVo->state, m_baseSprite );
	//}

	addChild(m_baseSprite);
	m_baseSprite->release();
	
	return m_baseSprite;
}

void MapNPC::playAnimation()
{
	return;

}

void MapNPC::stopAnimation()
{
	return;
}

void MapNPC::npcMove(char** map_desc, int &h, int &w)
{
	return;
}

bool MapNPC::addNPCTalk()
{
	if ( !m_baseSprite )
	{
		return false;
	}
	CCNode* pNodeTalkBG = m_baseSprite->getChildByTag(TAG_Talk_BG);
	if ( !pNodeTalkBG )
	{
		std::string str = SentenceManager::Instance()->getSentence( _npcVo->GetmapId(), _npcVo->id );

		if ( str != "" )
		{
			CCSize csBack = CCSizeMake(POSX(200), POSX(78));
			int length = str.length()/3;
			float factor = 1.0f;
			if ( length > 14 )
			{
				factor = length/14.0f/* + 0.1f*/;
				if ( factor > 2.3f )
				{
					factor = 2.3f;
				}
				csBack = CCSizeMake(POSX(200), POSX(78*factor));
			}

			CCUIBackground *pBackground1 = new CCUIBackground();
			pBackground1->initWithFile( "assets/ui/npcdialog/sentence.png", 
				ccp(0, POSX(nameY-20)),
				ccp(0,0), 
				CCSizeMake( csBack.width+POSX(20), csBack.height+POSX(10) ) );
			pBackground1->setTag(TAG_Talk_BG);
			m_baseSprite->addChild(pBackground1);
			pBackground1->setAnchorPoint(CCPointZero);
			pBackground1->release();
			pBackground1->setIsVisible( false );

			csBack = CCSizeMake( csBack.width, csBack.height-POSX(20) );
			CCLabelTTF* m_pTalkSenTenceCCLabel = CCLabelTTF::labelWithString(  str.c_str(),
				csBack, CCTextAlignmentLeft, g_sSimHeiFont, (float)POSX(21)  );
			if(m_pTalkSenTenceCCLabel && m_baseSprite)
			{
				m_pTalkSenTenceCCLabel->setColor( ccYELLOW );
				m_pTalkSenTenceCCLabel->setPosition( ccp( POSX(10), POSX(25)) );
				m_pTalkSenTenceCCLabel->setAnchorPoint(CCPointZero);
				pBackground1->addChild( m_pTalkSenTenceCCLabel );

				//CCLayerColor* pCol = CCLayerColor::layerWithColorWidthHeight(ccc4(0,0,255,100),csBack.width, csBack.height);
				//m_pTalkSenTenceCCLabel->addChild(pCol);
			}
			m_bCanTalk = true;

			if ( !m_TalkVisibleTimer )
			{
				m_TalkVisibleTimer = new Timer();
				m_TalkVisibleTimer->setTimer( 3000 );
			}			
		}
		else
			m_bCanTalk = false;
	}
	

	return false;
}

bool MapNPC::getTalkVisible()
{
	if ( !m_baseSprite )
	{
		return false;
	}
	CCNode* pNodeTalkBG = m_baseSprite->getChildByTag(TAG_Talk_BG);
	if ( pNodeTalkBG && pNodeTalkBG->getIsVisible() )
	{
		return true;
	}
	return false;
}

bool MapNPC::canTalk()
{
	return m_bCanTalk;
}

void MapNPC::setTalkVisible( bool bVar )
{
	if ( !m_baseSprite )
	{
		return;
	}
	CCNode* pNodeTalkBG = m_baseSprite->getChildByTag(TAG_Talk_BG);
	if ( pNodeTalkBG )
	{
		pNodeTalkBG->setIsVisible(bVar);
	}
}

int MapNPC::action()
{
	if(_npcVo)
		return _npcVo->action;

	return -1;
}

void MapNPC::icon( int ico )
{
	if (_npcVo && ico != _npcVo->icon )
	{
		_npcVo->icon = ico;

		layout();
	}	
}

void MapNPC::layout()
{
	if(!_npcVo)
		return;

	// LH0711
	if(m_baseSprite && m_baseSprite->getChildByTag(TAG_ICONMC))
	{
		m_baseSprite->removeChildByTag(TAG_ICONMC, true);
	}

	if ( _npcVo->icon == 0 )
	{
		return;
	}

	
	char sIconUrl[54];
	//if (g_pGlobalManage->isInStory){return;}
	//Doyang 20120712
	CCSprite *pIconMc = NULL;
	if ( _npcVo->icon > 4 )
	{
		sprintf( sIconUrl, "npcthing_icon/0%d.png", _npcVo->icon - 4 );
		//sprintf( sIconUrl, "assets/ui/npc_thing/npcthing_icon/0%d.png", _npcVo->icon - 4 );
		pIconMc = CCSprite::spriteWithSpriteFrameName( sIconUrl );
		
		if(m_baseSprite)
		{
			CCSize csSprite = m_baseSprite->getContentSize();
			if(pIconMc)
			{
				pIconMc->setPosition( ccp(POSX(0), csSprite.height/2 + POSX(50 + 55 + 125 / 2) ) );
				m_baseSprite->addChild(pIconMc, 0, TAG_ICONMC);
			}
		}
	}
	else	// task icon
	{
		pIconMc = new CCSprite();
		pIconMc->init();
		CCAnimation* clickEffect = 0;

		if ( _npcVo->icon == CANREC_ICON )
		{
			clickEffect = g_pKKAnimationFactory->registAni(
				"assets/ui/npc_thing/recvTaskIcon/recvTaskIcon.plist",
				"recvTaskIcon/%d.png", 30, 0.1f);
		} 
		else if(_npcVo->icon == FINISH_ICON )
		{
			clickEffect = g_pKKAnimationFactory->registAni(
				"assets/ui/npc_thing/finishTaskIcon/finishTaskIcon.plist",
				"finishTaskIcon/%d.png", 30, 0.1f);
		}		
		else if(_npcVo->icon == NOFINISH_ICON )
		{
			clickEffect = g_pKKAnimationFactory->registAni(
				"assets/ui/npc_thing/noFinishTaskIcon/noFinishTaskIcon.plist",
				"noFinishTaskIcon/%d.png", 30, 0.1f);
		}
		if (m_baseSprite)
		{
			m_baseSprite->addChild(pIconMc,	0, TAG_ICONMC);
		}
		
		pIconMc->release();

		CCSize csSprite = m_baseSprite->getContentSize();
		pIconMc->setPosition( ccp(POSX(0), csSprite.height/2 + POSX(50 + 55 + 125 / 2) ) );
		
		CCAnimate* animate = CCAnimate::actionWithAnimation(clickEffect);
		CCActionInterval*  seq = (CCActionInterval*)(CCSequence::actions( animate, NULL));
		pIconMc->runAction(CCRepeatForever::actionWithAction(seq));
	}
}

bool MapNPC::isHit(CCPoint point)
{
	//Begin Kenfly modify 20121024
	/*
	CCPoint pos = getMapStartPoint();
	CCSize size;
	CCSize s;
	if(livingMovieClip)
		s = livingMovieClip->getSize();
	size.width = POSX(s.width);
	size.height = POSX(s.height);
	if(point.x > (pos.x - size.width / 2) && point.x < (pos.x + size.width / 2)
		&& point.y > (pos.y - size.height / 2) && point.y < (pos.y + size.height / 2))
		return true;

	return false;
	*/
	if (livingMovieClip)
	{
		CCSize sz = livingMovieClip->getSize();
		const CCPoint* pos = this->getMapCurrentPoint();
		if (pos)
		{
			CCRect rt = CCRectMake(pos->x - (sz.width/2.0f), pos->y - (sz.height), (sz.width), (sz.height));
			if (CCRect::CCRectContainsPoint(rt, point))
			{
				return true;
			}
		}
	}
	return false;
	//End Kenfly modify 20121024
}

ccColor3B MapNPC::color()
{
	return _ccNameTextColor;
}


void MapNPC::color(ccColor3B value)
{
	_ccNameTextColor = value;
	if(m_baseSprite)
	{
		//CCLabelTTF* lb = (CCLabelTTF*)(m_baseSprite->getChildByTag(COLOR_NAMETEXT));
		CCStrokeLabel* lb = (CCStrokeLabel*)(m_baseSprite->getChildByTag(COLOR_NAMETEXT));
		if(lb)
			lb->setColor(_ccNameTextColor);
	}
		//lb->setColor(ccc3(255, 0, 0));
}

void MapNPC::name(const char* name)
{
	if(m_baseSprite)
	{
		//CCLabelTTF* lb = (CCLabelTTF*)(m_baseSprite->getChildByTag(COLOR_NAMETEXT));
		CCStrokeLabel* lb = (CCStrokeLabel*)(m_baseSprite->getChildByTag(COLOR_NAMETEXT));
		if(lb)
			lb->setString(name);
	}
}

void MapNPC::poseChange()
{
	if(poseState && poseState->_state == SceneConst::DEAD)
		return;


	//bitmapMovieClip.delay = this.resource.timer;
	if(poseState)
		_res.pose = poseState->_state;
	//_assetURL =  resource.dgUrl;
	redraw();
	//this.bitmapMovieClip.translate(_assetURL, BitmapMovieClip.URL_TYPE, callback, LoadLevel.LOW);
}

void MapNPC::movePath(std::vector<CCPoint> path, int delay)
{
	_path.clear();
	_path = path;
	if(_path.size() == 0 && poseState)
	{
		poseState->state(SceneConst::STAND);
		dispatchEvent(SceneConst::WALK_COMPLETE, NULL);
		return;
	}
	else
	{
		CCPoint point;
		std::vector<CCPoint>::iterator iter = _path.begin();
		if(iter != _path.end())
		{
			point = *iter;
			_path.erase(iter);
		}
		moveTo(point, delay);
	}			
}

void MapNPC::moveTo(CCPoint point, int delay)
{
	move1(point, delay);
}

void MapNPC::moveComplete()
{
	Element::moveComplete();
	completeHandler();
}

void MapNPC::completeHandler()
{
	if(_path.size() == 0)
	{
		if(poseState)
		{
			poseState->state(SceneConst::STAND);
		}
		dispatchEvent(SceneConst::WALK_COMPLETE, NULL);
	}
	else
	{
		dispatchEvent(SceneConst::WALK_COMPLETE_NODE, NULL); 
		std::vector<CCPoint>::iterator iter = _path.begin();
		if(iter != _path.end())
		{
			moveTo(*iter);
			_path.erase(iter);
		}
	}
}

void MapNPC::updateAction(bool repeat)
{
	LiveThing::updateAction(repeat);
	if(hasDispose)
	{
		return;
	}
	//bitmapMovieClip.scaleX = dirState.scale;
}

bool MapNPC::toAttack()
{
	LiveThing::toAttack();

	if(poseState == NULL)
		return false;

	poseState->state(SceneConst::ATTACK);
	//bitmapMovieClip.scaleX = dirState.scale;
	if(poseState->_isChanged)
	{
		update(false);
	}
	else
	{
		return false;
	}

	return true;
}

bool MapNPC::toHited(bool iscrit)
{
	LiveThing::toHited(iscrit);
	//if(!poseState)
	//	return false;
	//
	//{
	//	poseState->state(SceneConst::HITED);
	//	update(false);
	//}

	return true;
}

void MapNPC::updateInfo()
{
	LiveThing::updateInfo();
	/*if(_hpBar)
	{
		_hpBar->progress = hp/maxHp;
	}*/
}

void MapNPC::dispose()
{
	LiveThing::dispose();
	SAFE_DELETE(_npcVo);
	SAFE_DELETE(m_TalkVisibleTimer);
}


//Begin Kenfly 20121106
void MapNPC::loadModel()
{
	do 
	{
		CC_BREAK_IF(NULL == _npcVo);
	
		_assetURL = _res.modelUrl();
		int id = _res.id;

		if(livingMovieClip && livingMovieClip->getParent() == this)
		{
			removeChild(livingMovieClip, false);
			livingMovieClip->release();
			livingMovieClip = NULL;
		}

		livingMovieClip = new BitmapMovieClip();
		CC_BREAK_IF(NULL == livingMovieClip);

		if(_npcVo->_isMonster || (_npcVo->action == SceneConst::FIGHT) || (_npcVo->action==SceneConst::STORY) )
		{
			livingMovieClip->loadModelAsync(_assetURL, id, 0.2/*, this, callfuncOD_selector(MapNPC::loadModelCallBack), NULL*/);
		}
		else
		{
			livingMovieClip->loadPvrNormalAsync(_assetURL, id, BitmapMovieClip::ACTION_STAND, _npcVo->state, 0.2f/*, this, callfuncOD_selector(MapNPC::loadModelCallBack), NULL*/);
		}

		this->addChild(livingMovieClip);
		livingMovieClip->setAnchorPoint(ccp(0.5, 0.5));
		livingMovieClip->setPosition(0, POSX(125 / 2.0f));
		livingMovieClip->release();

		MapNPCSprite* npcSprite = new MapNPCSprite( _npcVo );
		CC_BREAK_IF(NULL == npcSprite);

		m_baseSprite = npcSprite;
		m_baseSprite->setAnchorPoint(ccp(0.5,0.5));
		CCSize csSprite = m_baseSprite->getContentSize();
		std::string _NameTxt = _npcVo->name;
		//CCLabelTTF* _label = CCLabelTTF::labelWithString( _NameTxt.c_str(), g_sSimHeiFont, POSX(20) );
		CCStrokeLabel *_label = CCStrokeLabel::labelWithString(_NameTxt.c_str(), g_sSimHeiFont, POSX(22));
		if(_label)
		{
			_label->setStroke(0.5f, ccc3(0, 0, 0));
			if (!_npcVo->_isMonster)
			{
				_label->setColor( ccc3(248,248,0) );
			}
			else
			{
				_label->setColor( ccc3(250,250,0) );
			}
		
			if ( livingMovieClip )
			{
				_label->setPosition( ccp( livingMovieClip->getPosition().x, POSX(55 + 125 / 2) ) );
			}
			m_baseSprite->addChild(_label, 0, COLOR_NAMETEXT);
		}
		_label->release();
	
		if ( _npcVo->action == SceneConst::TALK )
		{
			char sIconUrl[54];
			int icon = ShopManager::Instance()->getIconByNPCID( _npcVo->id );
			if ( icon > 4 )
			{
				sprintf( sIconUrl, "npcthing_icon/0%d.png", icon - 4 );
				//sprintf( sIconUrl, "assets/ui/npc_thing/npcthing_icon/0%d.png", icon - 4 );

				if (!g_pGlobalManage->isInStory && !_npcVo->_isMonster)
				{
					//Doyang 20120712
					m_baseSprite->removeChildByTag(TAG_ICONMC, true);

					CCSprite *pIconMc = CCSprite::spriteWithSpriteFrameName( sIconUrl );
					if(pIconMc)
					{
						pIconMc->setPosition( ccp( csSprite.width/2, csSprite.height/2 + POSX(50 + 55 + 125 / 2) ) );
						m_baseSprite->addChild(pIconMc, 0, TAG_ICONMC);
					}
				}
			}
		}
		else  // NPC
		{
			addNPCTalk();
		}

		addChild(m_baseSprite);
		m_baseSprite->release();

		if(livingMovieClip)
			livingMovieClip->runActionNormal(BitmapMovieClip::ACTION_STAND, _npcVo->state);

	} while (0);
}

//End Kenfly 20121106