#include "Player.h"
#include "utils/loader/KKAnimationFactory.h"
#include "utils/findPath/FindPath8.h"
#include "model/scene/SceneProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "model/player/RoleManage.h"
#include "util/TileUtil.h"
#include "model/com/ResourceManage.h"
#include "model/com/vo/ResourceVo.h"
#include "model/player/ClothManage.h"
#include "manager/GlobalManage.h"
#include "manager/SourceCacheManage.h"
#include "utils/loader/LoadLevel.h"
#include "events/GameDispatcher.h"
#include "../SceneMediator.h"
#include "utils/ValuesUtil.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "utils/ColorUtil.h"
#include "utils/ScaleUtil.h"
#include "BaseType.h"
#include "NPCChat.h"
#include "model/newhand/NewhandManager.h"
#include <cmath>
#include "model/player/PlayerEffectManage.h"
#include "model/player/vo/PlayerAniType.h"
#include "manager/ViewManager.h"
#include "model/trader/TraderProxy.h"
#include "socket/command/c11/CCMD116.h"
#include "../SceneListenerMediator.h"
#include "socket/command/c0f/CCMD0F3.h"

// Doyang 20120710
const int TAG_POINT_MC = 1001;
const int TAG_POINT_GO = 1002;
Player::Player()
{
	_isOnbusiness =false;

	for(int i = 0; i < 5; ++i)
	{
		walkAnimation[i] = NULL;
		standAnimation[i] = NULL;
	}
    m_action = NULL;  
    roleAnimation = NULL;

	SceneProxy* proxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
	if(proxy != NULL && proxy->_sceneInfoVo != NULL)
		mapData = (char**)(proxy->_sceneInfoVo->mapData);

	//add from flash
	_bodyLayer = new CCLayer();
	_horseLayer = new CCLayer();
	_bodyLayer->init();
	_horseLayer->init();
	_nameTxt = NULL;
	_guildTxt = NULL;
	_isHide = false;
	_stations = 0;
	_scale = 0.0f;
	_preGoVisible = false;
	_hpBar = 0;
	_mPercentage = 100;

	_clothNum = 0;

	livingMovieClip = 0;

	if(g_pGlobalManage && g_pGlobalManage->isGuest)
	{
		GameDispatcher::getInstance()->addEventListener(GameDispatcher::CHANGE_NAME, this, callfuncND_selector(Player::setPlayerName));
		//setPlayerName();
	}

	addChild(_bodyLayer);
	_bodyLayer->release();
	addChild(_horseLayer);
	_horseLayer->release();

	if (poseState)
		poseState->_suzhuType = getThingType();

}
Player::Player(PlayerBaseVo* playerVo):LiveThing(playerVo->hp(),playerVo->maxHp(),playerVo->mp(),playerVo->maxMp())
{
	_isOnbusiness =false;

	for(int i = 0; i < 5; ++i)
	{
		walkAnimation[i] = NULL;
		standAnimation[i] = NULL;
	}
	m_action = NULL;  
	roleAnimation = NULL;

	SceneProxy* proxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
	if(proxy != NULL && proxy->_sceneInfoVo != NULL)
		mapData = (char**)(proxy->_sceneInfoVo->mapData);

	//add from flash
	_bodyLayer = new CCLayer();
	_horseLayer = new CCLayer();
	_bodyLayer->init();
	_horseLayer->init();
	_nameTxt = NULL;
	_guildTxt = NULL;
	_isHide = false;
	_stations = 0;
	_scale = 0.0f;
	_preGoVisible = false;
	_hpBar = 0;
	_mPercentage = 100;

	_clothNum = 0;

	if(g_pGlobalManage && g_pGlobalManage->isGuest)
	{
		GameDispatcher::getInstance()->addEventListener(GameDispatcher::CHANGE_NAME, this, callfuncND_selector(Player::setPlayerName));
		//setPlayerName();
	}

	addChild(_bodyLayer);
	_bodyLayer->release();
	addChild(_horseLayer);
	_horseLayer->release();

	if (poseState)
		poseState->_suzhuType = getThingType();
}
Player::~Player()
{

}

CCSprite * Player::getPlayerSprite()
{
    return m_baseSprite;
}

CCSprite * Player::loadPlayer()
{
	m_baseSprite = new CCSprite();
	m_baseSprite->init();
	m_baseSprite->setContentSize(CCSizeMake(50, 150));
    return m_baseSprite;
}

void Player::playAnimation()
{
	if(!m_baseSprite)
		return;

    m_baseSprite->stopAllActions();
    
    vector<CCPoint>::iterator iter = m_path.begin();
    if(iter == m_path.end())
    {
        m_baseSprite->runAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(standAnimation[m_direction])));
        return;
    }
    
    float x1 = iter->x;
    float y1 = iter->y;
    
    m_mapStartPoint = *iter;
    iter = m_path.erase(iter);
    if(iter == m_path.end())
    {
        m_baseSprite->runAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(standAnimation[m_direction])));
        return ;
    }
    
    
    float x2 = iter->x;
    float y2 = iter->y;
    
    float x = x2 - x1;
    float y = y1 - y2;
    
    float x_ = x * 2.414f;
    float y_ = y * 2.414f;
    
    if(y < 0.0f && x_ > y && x_ < (y * -1.0))
        m_direction = 1;
    else if(x < 0.0f && y > x_ && x > y_)
        m_direction = 0;
    else if(x < 0.0f && y_ > x && y_ < (x * -1.0f))
        m_direction = 2;
    else if(y > 0 && x > (y_ * -1.0f) && (y * -1.0f )> x_)
        m_direction = 3;
    else if(y > 0 && x_ > (y * -1.0f) && y > x_)
        m_direction = 4;
    else if(x > 0 && x < y_ && x_ >y)
        m_direction = 5;
    else if(x > 0 && y_ < x && y_ > (x * -1.0f))
        m_direction = 6;
    else
        m_direction = 7;
    
    float v = sqrt(x * x + y * y) / 240.f;
    
    CCPoint pt = ccp(x, y);
    
    
    m_action = CCSequence::actions(
                                   CCSpawn::actions(
                                                    CCMoveBy::actionWithDuration(v, pt),
                                                    NULL),
													CCCallFunc::actionWithTarget(this,
																  callfunc_selector(Player::playAnimation)
																  ),
                                                                  //(void*)m_direction),
                                   NULL);
								   
    bool needFlix = false;
    if(m_direction == 5)
    {
        m_direction = 0;
        needFlix = true;
    }
    else if(m_direction == 6)
    {
        m_direction = 2;
        needFlix = true;
    }
    else if(m_direction == 7)
    {
        m_direction = 3;
        needFlix = true;
    }

    CCAnimate* animate = CCAnimate::actionWithAnimation(walkAnimation[m_direction]);

    CCActionInterval* seq = (CCActionInterval*)(CCSequence::actions(CCFlipX::actionWithFlipX(needFlix), animate, NULL));
    m_baseSprite->runAction(CCRepeatForever::actionWithAction(seq));
    
	//edit by edwardliu 0406
    //m_baseSprite->runAction(m_action);
	runAction(m_action);
}

void Player::stopAnimation()
{
    if(m_action && m_baseSprite)
        m_baseSprite->stopAction(m_action);
    m_path.clear();
}

void Player::setFindPath8(char** map_desc, int &h, int &w)
{
	FindPath8 fp8((char**)map_desc, h, w);
	_fp8 = fp8;
}

void Player::playerMove()
{
    if(this->m_mapStartPoint.x != this->m_mapEndPoint.x || this->m_mapStartPoint.y != this->m_mapEndPoint.y)
    {
        m_path.clear();
        
        
        //FindPath8 fp8((char**)map_desc, h, w);
        vector<point> path;
        vector<point> path_opt;
        point point_start;
        point point_end;
        point_start.x = (int)m_mapStartPoint.x / TILE_WIDTH;
        point_start.y = (int)m_mapStartPoint.y / TILE_HEIGHT;
        
        point_end.x = (int)m_mapEndPoint.x / TILE_WIDTH;
        point_end.y = (int)m_mapEndPoint.y / TILE_HEIGHT;
        
        _fp8.find(point_start, point_end, path_opt);
        //_fp8.find(point_start, point_end, path);
        _fp8.optimizePath(path);
        
        vector<point>::iterator it1 = path.begin();
        vector<point>::iterator it2 = path_opt.begin();
        for(;it1 != path.end(); ++it1)
        {
            CCLog("***********path: x:%d, y:%d", it1->x, it1->y);
        }
        
        for(;it2 != path_opt.end(); ++it2)
        {
            CCLog("*******path_opt: x:%d, y:%d", it2->x, it2->y);
        }
        vector<point>::iterator iter = path.begin();
        if(iter != path.end())
        {
            iter++;
        }
        else
        {
            return;
        }
        
        m_path.push_back(m_mapStartPoint);
        for(; iter != path.end(); ++iter)
        {
            if((iter + 1) == path.end())
                break;
            
            CCPoint pt;
            pt.x = (float)(iter->x) * (float)TILE_WIDTH + (float)TILE_WIDTH / 2.0f;
            pt.y = (float)(iter->y) * (float)TILE_HEIGHT + (float)TILE_HEIGHT / 2.0f;
            m_path.push_back(pt);
        }
        
        m_path.push_back(m_mapEndPoint);

        for(vector<point>::iterator it1 = path.begin(); it1 != path.end(); ++it1)
        {
            CCLog("path x:[%d],y:[%d]",it1->x, it1->y);
        }
        
        for(vector<CCPoint>::iterator it2 = m_path.begin(); it2 != m_path.end(); ++it2)
        {
            CCLog("m_path x:[%f],y[%f]", it2->x, it2->y);
        }
        
        playAnimation();

    }
}



//add from flash
void Player::setPlayerName(CCNode* n, void* data)
{
	AccountInfoVo* acc = RoleManage::Instance()->accountInfo();
	if(acc && _playerVo.accountId == acc->accountId)
	{
		GameDispatcher::getInstance()->removeEventListener(GameDispatcher::CHANGE_NAME);
		if(_nameTxt)
		{
			_nameTxt->setString(acc->name.c_str());
//			_nameTxt->setColor(ColorUtil::getMerchColor(_playerVo.color));
		}
	}
}


void Player::setPlayerVo(PlayerBaseVo& playerVo, float scale)
{
	_playerVo = playerVo;
	_scale = scale;
	//CCPoint point = TileUtil::Instance()->changeTileToPixs( ccp(_playerVo.x, _playerVo.y));

	//this->setPosition(point.x, point.y);
	if(dirState)
		dirState->state(_playerVo.state);
	
	if(!_bodyLayer)
		return;

	_bodyLayer->setAnchorPoint(CCPointZero);
	_bodyLayer->setIsRelativeAnchorPoint(true);

	_hp = playerVo._hp;
	_id = playerVo.accountId;
	_maxHp = playerVo._maxHp;
	_mp = playerVo._mp;
	_maxMp = playerVo._maxMp;
	_eleName = playerVo.name;
	_level = playerVo._lev;

	if (_playerVo.cloth == ClothManage::RES_ID_ONBUSINESS)
	{
		_type = TRADEPLAYER_TYPE;
	} 
	else
	{
		_type = PLAYER_TYPE;
	}
	
	skill1 = playerVo.skill1;
	skill2 = playerVo.skill2;
	skill3 = playerVo.skill3;
	_energy = playerVo.energy;

	if (_nameTxt)
	{
		_nameTxt->removeFromParentAndCleanup(true);
		_nameTxt = 0;
	}
	if (_guildTxt)
	{
		_guildTxt->removeFromParentAndCleanup(true);
		_guildTxt = 0;
	}
	/*_nameTxt = new CCLabelTTF();
	_nameTxt->initWithString(_eleName.c_str(), g_sSimHeiFont, POSX(20));*/

	//Doyang
	//Stroke
	_nameTxt = CCStrokeLabel::labelWithString(_eleName.c_str(), g_sSimHeiFont, POSX(22));
	_nameTxt->setStroke(1.0f, ccc3(0, 0, 0));

	//_nameTxt = CCLabelTTF::labelWithString(_eleName.c_str(), g_sSimHeiFont, POSX(20));
	char guildTxt[128] = {0};
	/*_guildTxt = new CCLabelTTF();
	_guildTxt->initWithString(playerVo._guildName.c_str(), g_sSimHeiFont, POSX(20));*/

	_guildTxt = CCStrokeLabel::labelWithString(playerVo._guildName.c_str(), g_sSimHeiFont, POSX(20));
	_guildTxt->setStroke(1.0f, ccc3(0, 0, 0));
	//_guildTxt = CCLabelTTF::labelWithString(guildTxt, g_sSimHeiFont, POSX(20));
	AccountInfoVo* acc = RoleManage::Instance()->accountInfo();
	if(acc && _playerVo.accountId == acc->accountId)
	{
		//ccColor3B col= ccc3(0xff, 0xff, 0x00);
		//ccColor3B col= ccc3(0x83, 0xeb, 0xe1);
		ccColor3B col= ccc3(248,248,0);
		if(_nameTxt)
			_nameTxt->setColor(col);

		ccColor3B col1 = ccc3(0, 255, 18);
		if(_guildTxt)
			_guildTxt->setColor(col1);
		/*_nameTxt.textColor = 0xffff00;
		_guildTxt.textColor = 0x83eb4f;
		*/

		PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
		if(info)
			info->playerBaseInfo.addEventListener(PlayerBaseVo::CHANGE_GUILD, this, callfuncND_selector(Player::updateGuildName));
			//_roleManage.roleInfo.playerBaseInfo.addEventListener(PlayerBaseVo::CHANGE_GUILD, updateGuildName);
	}
	else
	{
		ccColor3B col= ccc3(0xee, 0xf9, 0xe1);
		if(_nameTxt)
			_nameTxt->setColor(col);

		if (strstr(_nameTxt->getString(),"GM"))
		{
			_nameTxt->setColor(ccc3(255,10,10));
		}

		ccColor3B col1 = ccc3(0, 255, 18);
		if(_guildTxt)
			_guildTxt->setColor(col1);

		/*_nameTxt.textColor = 0xfff9e1;
		_guildTxt.textColor = 0xece3a8;*/
	}

	//_nameTxt.filters = [new GlowFilter(0x0, 1, 2, 2, 10)];
	if(playerVo._guildName != "")
	{
		sprintf(guildTxt,/*ValuesUtil::Instance()->getString("GNAME").c_str()*/"[%s]",playerVo._guildName.c_str());
		if(_guildTxt)
			_guildTxt->setString(guildTxt);
	}

	if(_nameTxt)
	{
		_bodyLayer->addChild(_nameTxt, 5, 8000);
		_nameTxt->release();
		//POSX
		_nameTxt->setPosition(ccp(POSX(0),POSX(this->nameY))); 
	}
	
	if(_guildTxt)
	{
		_bodyLayer->addChild(_guildTxt, 5, 9000);
		_guildTxt->release();
		//POSX
		_guildTxt->setPosition( ccp(POSX(0.0f), POSX(this->nameY)) );//POSX(105.0f)));
	}

	if(livingMovieClip && _bodyLayer && livingMovieClip->getParent() == _bodyLayer)
		_bodyLayer->removeChild(livingMovieClip, false);

	ResourceVo* res = ResourceManage::Instance()->getRes(1, playerVo.cloth);
	if(res)
		_res = *res;
			
	_isInteractive = !(_playerVo.isRole);
			
 	showRes();
	
}

void Player::showHP(bool value)
{
	LiveThing::showHP(value);
	if(_hpBar)
		_hpBar->setIsVisible(value);
}

void Player::showRes()
{
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;

	int accountId = info->playerBaseInfo.accountId;

	bool isSelf = (_playerVo.accountId == accountId); 
	AccountInfoVo* acc = RoleManage::Instance()->accountInfo();
	if(!acc)
		return;

	int _lv = (isSelf ? acc->_crystalLev:_playerVo._lev);

	setRoleSpeed(g_pGlobalManage->getRoleSpeed());
	
	if((_playerVo.cloth == ClothManage::RES_ID_ONBUSINESS) || _isOnbusiness
		/*(g_pGlobalManage && g_pGlobalManage->isOnBusiness() && isSelf )*/)
	{
			_clothURL =  ClothManage::Instance()->RES_PATH_ONBUSINESS;
			_clothNum = 900;
			if(_playerVo.name != "")
			{
				char guildtxt[128];
				sprintf(guildtxt, LangManager::getText("TRD001").c_str(), _playerVo.name.c_str());
				_nameTxt->setString(guildtxt);
				//_nameTxt = CCLabelTTF::labelWithString(guildtxt, g_sSimHeiFont, 15);
			}
			//_nameTxt->setPosition(ccp(POSX(22.0f), POSX(125.0f)));
			//_nameTxt.x = -_nameTxt.width>>1;
			if (_nameTxt)
			{
				_nameTxt->setColor( TraderProxy::getTradeColor(_playerVo.color) );
			}
			if (_guildTxt)
			{
				_guildTxt->setColor( /*TraderProxy::getTradeColor(_playerVo.color)*/ccc3(0, 255, 18) );
			}			

			_speed = POSX(39);//42ms == 1frame
			_playerVo.speed = _speed;
			
	}
	else if((_playerVo.cloth == ClothManage::Instance()->RES_ID_ONMEDITATION) || 
		(g_pGlobalManage && g_pGlobalManage->isOnMeditation()  && isSelf))
	{
			if(isSelf)
			{
				PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
				if(info)
				{
					_clothURL =  ClothManage::Instance()->getCloth(info->figureBaseInfo.mercId);
					_clothNum = info->figureBaseInfo.mercId;
				}
			}
			else
			{
				_clothURL =  ClothManage::Instance()->getCloth(_playerVo.mercId);
				_clothNum = _playerVo.mercId;
			}
			_res.timer = 125;
	}else
	{
		_clothURL =  _res.modelUrl();
		_clothNum = _res.id;
	}

	updateGuildName(NULL, NULL);

	if(_clothURL != "")
	{
		//Begin Kenfly 20121107 : modify, load async
		do 
		{
			CC_BREAK_IF(NULL == _bodyLayer);
			if(livingMovieClip && _bodyLayer && livingMovieClip->getParent() == _bodyLayer)
			{
				_bodyLayer->removeChild(livingMovieClip, false);
				livingMovieClip->release();
				livingMovieClip = NULL;
			}

			livingMovieClip = new BitmapMovieClip();
			CC_BREAK_IF(NULL == livingMovieClip);

			livingMovieClip->loadModelAsync(_clothURL, _clothNum, 0.1f/*, this, callfuncOD_selector(Player::loadModelCallback), NULL*/);

			_bodyLayer->addChild(livingMovieClip);
			livingMovieClip->setTag(TAG_BitMapMovie);
			livingMovieClip->setPosition(0, POSX(125 / 2.0));
			livingMovieClip->release();
			redraw();
			update();
		} while (0);
		
		//BitmapMovieClip* m = SourceCacheManage::Instance()->loadModel(_clothURL, _clothNum, 0.1f, true);
		//if ( !m )
		//{
		//	m = loadDefautRes();
		//}

		//if(m)
		//{
		//	livingMovieClip = (BitmapMovieClip*)_bodyLayer->getChildByTag( TAG_BitMapMovie );
		//	if(livingMovieClip && _bodyLayer && livingMovieClip->getParent() == _bodyLayer)
		//	{
		//		_bodyLayer->removeChild(livingMovieClip, false);
		//		livingMovieClip->release();
		//		livingMovieClip = 0;
		//	}

		//	livingMovieClip = m;

		//	if(livingMovieClip && livingMovieClip->getParent() == NULL && _bodyLayer)
		//	{
		//		_bodyLayer->addChild(livingMovieClip);
		//		livingMovieClip->setTag(TAG_BitMapMovie);
		//		//POSX edwardliu
		//		livingMovieClip->setPosition(0, POSX(125 / 2.0f));//POSX(125 / 2)kevinpos
		//		livingMovieClip->release();
		//	}
		//	redraw();
		//	update();
		//}

		//End Kenfly 20121107
	}
}

// please do not call this function
void Player::clothLoadCompleteHandler(CCNode* n, void* data)
{
	if(_clothURL == "")
		return;

	livingMovieClip = (BitmapMovieClip*)_bodyLayer->getChildByTag( TAG_BitMapMovie );
	if(livingMovieClip && _bodyLayer && livingMovieClip->getParent() == _bodyLayer)
		_bodyLayer->removeChild(livingMovieClip, false);

	livingMovieClip = SourceCacheManage::Instance()->getObject(_clothURL);
	if(livingMovieClip && _bodyLayer && livingMovieClip->getParent() == NULL)
	{
		_bodyLayer->addChild(livingMovieClip);
		livingMovieClip->setTag(TAG_BitMapMovie);
		//POSX edwardliu
		livingMovieClip->setPosition(0, POSX(125 / 2));
	}

	update();
	//SourceCacheManage::Instance()->removeEventListener(Event::COMPLETE);
}

void Player::updateGuildName(CCNode* n, void* data)
{
	if(data != NULL)
	{
		PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
		if(info)
		{
			std::string name = info->playerBaseInfo._guildName;
			if( !name.empty() )
			{
				char guildtxt[128];
				//sprintf(guildtxt,ValuesUtil::Instance()->getString("GNAME").c_str(),name.c_str());
				sprintf(guildtxt,"[%s]",name.c_str());
				if ( _guildTxt )
				{
					_guildTxt->setString( guildtxt );
				}
				else			
				{
					//_guildTxt = CCLabelTTF::labelWithString(guildtxt, g_sSimHeiFont, POSX(20));
					_guildTxt = CCStrokeLabel::labelWithString(guildtxt, g_sSimHeiFont, POSX(20));
					_guildTxt->setStroke(1.0f, ccc3(0, 0, 0));
				//_guildTxt.filters = [new GlowFilter(0x0, 1, 2, 2, 10)];
				}
			}
			else
			{
				if ( _guildTxt )
				{
					_guildTxt->setString( name.c_str() );
				}
				else
				{
					//_guildTxt = CCLabelTTF::labelWithString(name.c_str(), g_sSimHeiFont, POSX(20));
					_guildTxt = CCStrokeLabel::labelWithString(name.c_str(), g_sSimHeiFont, POSX(20));
					_guildTxt->setStroke(1.0f, ccc3(0, 0, 0));
				}
			}
		}
	}

	if(_guildTxt && _nameTxt)
	{
		//CCPoint gPos = _guildTxt->getPosition();
		//_guildTxt->setPosition(gPos);

		//std::string str(_guildTxt->getString());

		//if(str != "")
		//{
		//	//nameY = gPos.y + POSX(20);
		//	nameY = 144.0f + POSX(20);
		//	CCPoint nPos = _nameTxt->getPosition();
		//	nPos.y = nameY;
		//	_nameTxt->setPosition(nPos);
		//}
		std::string str(_guildTxt->getString());
		if (str != "")
		{
			CCPoint gPos = _guildTxt->getPosition();
			nameY = 144.0f + POSX(20);
			_guildTxt->setPosition(ccp(0, POSX(144)));
			_nameTxt->setPosition(ccp(0, POSX(144)+POSX(20)));
		}
		else
		{
			//_guildTxt->setPosition(gPos);
		}
	}
}


void Player::layout()
{
	if(hasDispose)
		return;
	if(!poseState)
		return;

	if(poseState->_state == SceneConst::ATTACK 
		|| poseState->_state == SceneConst::DEAD)
	{
		if(_hpBar)
			_hpBar->setIsVisible(false);
	}
	else if(_showHP && _hpBar)
	{
		_hpBar->setIsVisible(false);
	}

	if(poseState->_state == SceneConst::DEAD)
	{
		if(_nameTxt)
			_nameTxt->setIsVisible(false);
		if(_guildTxt)
			_guildTxt->setIsVisible(false);
		/*if(_shadow)
			_shadow->setIsVisible(false);*/
	}

	//_iconMc.gotoAndStop(_playerVo.icon);
	//_iconMc.y = this.nameY - 10;

	if(_hpBar)
	{
		CCPoint hPos = _hpBar->getPosition();
		hPos.y = nameY + POSX(10);
		_hpBar->setPosition(hPos);
	}
			
	//if(_voice){
	//	_npcChat.showContent(_voice);
	//	_npcChat.x = _nameTxt.x;
	//	_npcChat.y = this.nameY - _npcChat.height;
	//	_voice = null;
	//}
	
	//the next it seemed do nothing
	dispatchEvent(SceneConst::PLAYER_LAYOUT, NULL);
}


void Player::dispose()
{
	LiveThing::dispose();

	if(_horseLayer)
	{
		_horseLayer->removeAllChildrenWithCleanup(true);
		_horseLayer->removeFromParentAndCleanup(true);
	}

	if(_bodyLayer)
	{
		_bodyLayer->removeAllChildrenWithCleanup(true);
		_bodyLayer->removeFromParentAndCleanup(true);
	}

	if(isLoading)
	{
		SourceCacheManage::Instance()->removeEventListener(Event::COMPLETE);
	}

	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(info)
		info->playerBaseInfo.removeEventListener(PlayerBaseVo::CHANGE_GUILD, this, callfuncND_selector(Player::updateGuildName));

}

void Player::moveComplete()
{
	Element::moveComplete();
	completeHandler();
}

void Player::completeHandler()
{
	if(_path.size() == 0)
	{
		if(poseState)
		{
			int preState = poseState->_state;
			if(poseState)
				poseState->state(SceneConst::STAND);

			if(preState != SceneConst::STAND)
			{
				if (_playerVo.cloth == ClothManage::RES_ID_ONBUSINESS)
				{
					do 
					{
						//CC_BREAK_IF(_playerVo.accountId != RoleManage::Instance()->accountInfo()->accountId);

						//TraderProxy* _traderProxy = (TraderProxy*)g_pFacade->retrieveProxy( AppFacade_CITY_TRADER_CHANGE );

						//CC_BREAK_IF(!_traderProxy);
						//CC_BREAK_IF(!_traderProxy->selectedVo);

						{
							//if (_traderProxy->_traderState==TraderProxy::Trader_State_City1)
							//{
							//}
							//else
							//{
							//	SceneListenerMediator* md = 
							//		(SceneListenerMediator*)g_pFacade->retrieveMediator(
							//		AppFacade_SCENELISTENER_MEDIATOR);
							//	CC_BREAK_IF(!md);
							//	md->businessEndCheck(_traderProxy->selectedVo->npcId);
							//	g_pGlobalManage->_tradeMapLimit = false;
							//	_traderProxy->_traderState = TraderProxy::Trader_State_none;
							//}

							SceneMediator* pMeditor = (SceneMediator*)g_pFacade->retrieveMediator(AppFacade_SCENE_MEDIATOR);
							if (pMeditor)
							{
								pMeditor->_scene->addRemoveEliment(_playerVo.accountId);
							}							
						}
					} while (0);					
				}
				else
				{
					CCPoint point = getMapStartPoint();
					dispatchEvent(SceneConst::WALK_COMPLETE, (void*)(&point));
				}
				
			}
		}
	}
	else
	{
		//it seemed do nothing, the dispatch event
		dispatchEvent(SceneConst::WALK_COMPLETE_NODE, NULL);
		std::vector<CCPoint>::iterator iter = _path.begin();
		if(iter != _path.end())
		{
			CCPoint pos = *iter;
			_path.erase(iter);
			moveTo(pos);
		}
	}
}

	
void Player::movePath(std::vector<CCPoint>& path, float delay)
{
	_path = path;
	if(_path.size() == 0)
	{
		if(poseState)
			poseState->state(SceneConst::STAND);
		dispatchEvent(SceneConst::WALK_COMPLETE, NULL);
		//this.dispatchEvent(new Event(SceneConst.WALK_COMPLETE));
		return;
	}
	else
	{
		CCPoint point;
		if(poseState && poseState->_state == SceneConst::MOVE)
		{
			CCPoint pos = getMapStartPoint();
			dispatchEvent(SceneConst::WALK_PATH_CHANGE, &pos);
			//this.dispatchEvent(new ParamEvent(SceneConst.WALK_PATH_CHANGE,new Point(this.x,this.y)));
			if(!_playerVo.isRole)
			{
				point = _path.front();
				//this.x = point.x;
				//this.y = point.y;
				startPoint = point;
			}
		}
		dispatchEvent(SceneConst::WALK_START, &_path);
		//this.dispatchEvent(new ParamEvent(SceneConst.WALK_START,_path));
		
		


		std::vector<CCPoint>::iterator iter = _path.begin();
		if(iter != _path.end())
		{
			point = *iter;
			_path.erase(iter);
			moveTo(point,delay);
		}

	}
}


void Player::addPath(std::vector<CCPoint>& path)
{
	std::vector<CCPoint>::iterator  iter = path.begin();
	for(; iter != path.end(); ++iter)
	{
		_path.push_back(*iter);
	}
}
		

void Player::changePath(std::vector<CCPoint>& path)
{
	if(poseState && poseState->_state==SceneConst::STAND)
	{
		movePath(path);
	}
	else
	{
		_path = path;
	}
}
		
	
void Player::moveTo(CCPoint point, float delay)
{
	if (_playerVo.isRole)
	{
		DialogView * pDlgView = ViewManager::getInstance()->dialogView;
		if (pDlgView && pDlgView->getisPop() )
		{
			pDlgView->setisPop(false);
		}
	}

	move1(point, delay);

	std::vector<CCPoint> path;
	CCPoint point1 = getMapStartPoint();
	path.push_back(point1);
	path.push_back(point);

	if (_type==TRADEPLAYER_TYPE)
	{
		//dispatchEvent(SceneConst::TRADE_WALK_START_NODE, (void*)(&path));

		DWORD d2 = Timer::millisecondNow();;

		static DWORD d1 = d2;
		CCLog("-------------------build scene use: %f s", (d2-d1)*0.001 );
		d1 = d2;
	}
	else
	{
		dispatchEvent(SceneConst::WALK_START_NODE, (void*)(&path));
	}
}




void Player::updateAction(bool repeat)
{
	LiveThing::updateAction(repeat);
			
	if(hasDispose)
	{
		//trace("player updateAction debug hasDispose ", hasDispose );	
		return;
	}
	//_bodyLayer->_scaleX = dirState->_scale * _scale;
	//_bodyLayer->_scaleY = _scale;
}

std::vector<CCPoint>* Player::getCurrentPath()
{
	return &_path;
}

bool Player::isHit()
{
	if(_isHide==true || isInteractive() == false)
		return false;

	return true;
	//float pixel = livingMovieClip.bitmapData.getPixel(livingMovieClip.bitmap.mouseX,livingMovieClip.bitmap.mouseY);

	//return pixel > 0; 
}


bool Player::isHit(CCPoint point)
{
	if (livingMovieClip)
	{
		CCSize sz = livingMovieClip->getSize();
		const CCPoint* pos = this->getMapCurrentPoint();
		if (pos)
		{
			CCRect rt = CCRectMake(pos->x - POSX(sz.width/2.0f), pos->y - POSX(sz.height), POSX(sz.width), POSX(sz.height));
			if (CCRect::CCRectContainsPoint(rt, point))
			{
				return true;
			}
		}
	}
	return false;
}
		
void Player::hide()
{
	_isHide = true;
	if(_bodyLayer)
		_bodyLayer->setIsVisible(false);

	if(_horseLayer)
		_horseLayer->setIsVisible(false);
}
		
void Player::show()
{
	_isHide = false;
	if(_bodyLayer)
		_bodyLayer->setIsVisible(true);
	if(_horseLayer)
		_horseLayer->setIsVisible(true);
}		
		
void Player::setGlow(bool value)
{
	//_glowFilter = null;
	//if(!livingMovieClip) return;
			
	/*if(value) {
	_glowFilter =  new GlowFilter(0xffffff,1,10,10,2); 
	livingMovieClip.buttonMode=true;
	livingMovieClip.filters = [_glowFilter];
	}
	else {
	livingMovieClip.buttonMode = false;
	livingMovieClip.filters = [];
	}*/
}
		
float Player::distance(Player* player)
{
	if(!player)
		return 0.0f;

	CCPoint p1 = getPosition();
	CCPoint p2 = player->getPosition();
	float dis = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	return dis;
}
		
void Player::setColor(ccColor3B col)
{
	if(_nameTxt)
		_nameTxt->setColor(col);
}

bool Player::toAttack()
{
	if(!poseState)
		return false;

	LiveThing::toAttack();
			
	poseState->state(SceneConst::ATTACK);
	
	if(poseState->isChanged())
	{
		update(false);
		poseState->state(SceneConst::STAND);
	}
	else
	{
		return false;
	}
	return true;
}

void Player::endAttackFun()
{
	if(hasDispose)
	{
		//trace("endAttackFun hasDispose");
		return;
	}

	if(poseState)
		poseState->state(SceneConst::STAND);

	dispatchEvent(SceneConst::ATTACK_COMPLETE, NULL);
			
}
		
bool Player::toHited(bool iscrit)
{
	LiveThing::toHited(iscrit);
			
	if(poseState == NULL)
		return false;


	//poseState->state(SceneConst::HITED);kevinf
	//update(false);

	return true;
}

void Player::endHitFun()
{
	if(hasDispose)
	{
		//trace("endHitFun hasDispose");
		return;
	}
	if(poseState && poseState->_state == SceneConst::HITED)
	{
		poseState->state(SceneConst::STAND);
	}
	if(has0hp())
	{
		updateAction();
		if(poseState)
		{
			//trace("PLAYER endHitFun check poseState=", poseState);
			poseState->state(SceneConst::DEAD);
		}
	}
}
		
	
void Player::updateInfo()
{
	LiveThing::updateInfo();
	//_hpBar.progress = hp / maxHp;
}
		
bool Player::hitTest(CCPoint point)
{
	/*var rx:Number = this.x+_playerContainer.x+_bodyLayer.x+livingMovieClip.x
	var pixel:Number = livingMovieClip.bitmapData.getPixel(livingMovieClip.bitmap.mouseX,livingMovieClip.bitmap.mouseY);
			
	return pixel>0 ;*/
	return false;
} 

void Player::toShade(bool value)
{
	/*if(value)
	this->m_baseSprite->setOpacity(128);
	else
	this->m_baseSprite->setOpacity(255);*/

	if(!livingMovieClip)
		return;

	if(value)
	{
		livingMovieClip->setAlpha(128);
	}
	else
	{
		livingMovieClip->setAlpha(255);
	}
}

void Player::setSelect(bool value)
{
	Element::setSelect(value);
	SceneMediator* md = (SceneMediator*)g_pFacade->retrieveMediator(AppFacade_SCENE_MEDIATOR);
	if(!md || !(md->_scene))
		return;

	if(value)
		md->_scene->dispatchEvent(SceneConst::SELECT_PLAYER, (void*)(&_playerVo));
	else
		md->_scene->dispatchEvent(SceneConst::CANCEL_PLAYER, NULL);
}


void Player::icon(int value)
{
	_playerVo.icon = value;
	if(value == 11)
	{
		this->showOnePNGEffect(PlayerAniType::TYPE_AutoFind);
	}
	else if (value == 0)
	{
		this->removeOnePNGEffect(PlayerAniType::TYPE_AutoFind);
	}
	layout();
}
		
int Player::icon()
{
	return _playerVo.icon;
}

void Player::poseChange()
{
	if(poseState && poseState->_state == SceneConst::DEAD)
		return;

	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(info && _playerVo.accountId == info->playerBaseInfo.accountId
		&& g_pGlobalManage && g_pGlobalManage->isOnBusiness())
	{
		return;
	}
	if(poseState)
		_res.pose = poseState->_state;
	//_clothURL =  _res.dgUrl;
	//bitmapMovieClip.delay = this.resource.timer;
	redraw();
	//this.bitmapMovieClip.translate(_clothURL, BitmapMovieClip.URL_TYPE, callback, level);
}

void Player::setRoleSpeed(int nSpeed)
{
	_speed = nSpeed;
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(info)
	{
		_playerVo.speed = _speed;
	}
}

void Player::initDirArrow()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/res_go.plist");
	//_pointMc = Reflection.createInstance("lead_road");
	CCSprite *pPointMc = CCSprite::spriteWithSpriteFrameName("icon_arrow.png");

	CCSprite *pPointGo = CCSprite::spriteWithSpriteFrameName("icon_go.png");


	if(!pPointMc || !pPointGo)
		return;

	//新手阶段显示Go字样
	ScriptVo *curScript = NewhandManager::Instance()->_pCurScript;
	if( curScript && 
		(curScript->taskId > 14 ||
		curScript->taskId == 0 ))
	{
		pPointGo->setIsVisible(false);
	}
	_preGoVisible = pPointGo->getIsVisible();
	pPointMc->setPosition(CCPointZero);
	pPointMc->setAnchorPoint(ccp(0.5, 0.5));
	pPointMc->setScaleY(0.8f);

	pPointGo->setPosition(CCPointZero);
	pPointGo->setAnchorPoint(ccp(0.5, 0.5));
	
	CCFiniteTimeAction *pScaleBigAction = CCScaleTo::actionWithDuration(0.2, 1.2, 1.2);
	CCFiniteTimeAction *pScaleSmallAction = CCScaleTo::actionWithDuration(0.2, 0.833, 0.833);
	CCActionInterval *pAction = CCSequence::actionOneTwo(pScaleBigAction, pScaleSmallAction);
	CCAction *pRepeatAction = CCRepeatForever::actionWithAction(pAction);
	pPointGo->runAction(pRepeatAction);

	this->addChild(pPointMc, -100, TAG_POINT_MC);
	this->addChild(pPointGo, -101, TAG_POINT_GO);

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/res_go.plist");
}

//移除箭头
void Player::removeDirArrow()
{
	this->removeChildByTag(TAG_POINT_MC, true);
	this->removeChildByTag(TAG_POINT_GO, true);
}

//旋转箭头方向
void Player::resetDirArrow( int dir )
{
	CCSprite *pPointMc = (CCSprite *) this->getChildByTag(TAG_POINT_MC);
	CCSprite *pPointGo = (CCSprite *) this->getChildByTag(TAG_POINT_GO);
	if(pPointMc)
	{
		//Doyang
		float newRotate = -(-dir - 180);
		pPointMc->setRotation( newRotate );

		if(pPointGo)
		{
			/*if(newRotate > -0.1 ||
			newRotate < -135)
			{
			newRotate -= 90;
			}*/
			float rotate = newRotate * 0.0175;
			pPointGo->setPosition(ccp(POSX(-160 * cos(rotate)), POSX(160 * sin(rotate))));
			while(newRotate > 45 || newRotate < -45)
			{
				if(newRotate > 45)
				{
					newRotate -= 45;
				}
				else if(newRotate < -45)
				{
					newRotate += 45;
				}
			}
			/*if(newRotate > 45)
			{
			newRotate -= 45;
			}
			else if(newRotate < -45)
			{
			newRotate += 45;
			}*/
			//pPointGo->setRotation(newRotate);
		}
	}
}

//设置箭头可见性
void Player::dirArrowVisible( bool visible )
{
	CCSprite *pPointMc = (CCSprite *) this->getChildByTag(TAG_POINT_MC);
	if(pPointMc)
	{
		pPointMc->setIsVisible(visible);
	}
}

void Player::goVisible( bool visible )
{
	CCSprite *pPointGo = (CCSprite *) this->getChildByTag(TAG_POINT_GO);
	if(pPointGo)
	{
		pPointGo->setIsVisible(visible);
	}
}

void Player::playEffect(int type)
{
	PlayerEffectInfoVo * pEffctInfo = PlayerEffectManage::Instance()->getAniInfoByType(type);
	if (!pEffctInfo){ return;	}

	CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_RGBA4444 );//jae 20120803
	CCAnimation * pLevelUpAnimation = g_pKKAnimationFactory->registAni(
		pEffctInfo->_path.c_str(),
		pEffctInfo->_name.c_str(),
		pEffctInfo->_nFrameCount,
		pEffctInfo->_time);

	CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_Default );

    int* tran_effectType = new int;
    if (tran_effectType)
        *tran_effectType = type;
	CCCallFuncND * pCallback = CCCallFuncND::actionWithTarget(this,callfuncND_selector(Player::removeEffect),(void *)tran_effectType);
	CCAction * pActions = CCSequence::actions(CCAnimate::actionWithAnimation(pLevelUpAnimation, false),pCallback,0);
	CCSprite * pSprite = new CCSprite();
	if (pSprite && pSprite->init())
	{
		pSprite->setTag(TAG_PLAYER_ANI_SPRITE + type);
		pSprite->setPosition(ccp(POSX(pEffctInfo->_x),POSX(pEffctInfo->_y)));
		this->addChild(pSprite);
		pSprite->release();
		pSprite->runAction(pActions);
	}
}

void Player::removeEffect(CCNode * pTarget,void * pType)
{
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/effect/levelUp/levelUp.plist");//kevinshit

	//if (CCTextureCache::sharedTextureCache()->textureForKey("assets/effect/levelUp/levelUp.pvr.ccz"))
	//{
	//	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/effect/levelUp/levelUp.pvr.ccz");
	//}

    if (!pType)
        return;
    
	int type = *(int *) pType;
    
    int* pinttype = (int*)pType;
    SAFE_DELETE(pinttype)
    
	PlayerEffectInfoVo * pEffctInfo = PlayerEffectManage::Instance()->getAniInfoByType(type);
	if (!pEffctInfo){ return;	}

	CCSprite * pSprite = (CCSprite *)this->getChildByTag(TAG_PLAYER_ANI_SPRITE + type);
	if (pSprite)
	{
		pSprite->cleanup();
		this->removeChildByTag(TAG_PLAYER_ANI_SPRITE + type,true);
	}
	/*
	for (int i = 1;i <= pEffctInfo->_nFrameCount;i++)
	{
		char path[16];
		sprintf(path,pEffctInfo->_name.c_str(),i);
		CCAnimationCache::sharedAnimationCache()->removeAnimationByName(path);
		CCTextureCache::sharedTextureCache()->removeTextureForKey(path);
	}
	*/
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile( pEffctInfo->_path.c_str() );
	CCTextureCache::sharedTextureCache()->removeTextureForKey( pEffctInfo->_name.c_str() );
}

void Player::showOnePNGEffect(int type)
{
	std::string szPath = "";
	switch (type)
	{
	case PlayerAniType::TYPE_AutoFind:
		szPath = "autofind.png";
		break;
	case PlayerAniType::TYPE_RunBusiness:
			break;
	default:
			break;
	}

	CCSprite * pPNGSprite = new CCSprite();
	if (pPNGSprite)
	{
		if (pPNGSprite->initWithSpriteFrameName(szPath.c_str()))
		{
			pPNGSprite->setScale(0.7);
			pPNGSprite->setPosition(ccp(POSX(0) , POSX(150 + 30)));
			pPNGSprite->setTag(TAG_PLAYER_onePNG + type);
			if (_bodyLayer)
			{
				_bodyLayer->addChild(pPNGSprite);
			}
		}
		pPNGSprite->release();
	}
}

void Player::removeOnePNGEffect(int type)
{
	if (_bodyLayer && _bodyLayer->getChildByTag(TAG_PLAYER_onePNG + type))
	{
		_bodyLayer->removeChildByTag(TAG_PLAYER_onePNG + type , true);
	}
}

void Player::setRoleVipIcon(int vipLev)
{
	if (vipLev < 1 || vipLev >10)
	{
		return;
	}
	
	if (this->getChildByTag(TAG_VIP_ICON))
	{
		this->removeChildByTag(TAG_VIP_ICON , true);
	}
	char path[16] = {0};
	sprintf(path , "vip%d.png" , vipLev);
	CCSprite * pVipSprite = new CCSprite();
	bool var = pVipSprite->initWithSpriteFrameName(path);
	if (var && _bodyLayer && _nameTxt )
	{
			CCPoint pos = _nameTxt->getPosition();
			std::string str = _nameTxt->getString();
			int len = str.length();
			int bytes = 0;
			while (bytes < len)
			{
				if (str[bytes] & 0x80)
				{
					bytes += 3;
				}
				else
				{
					++bytes;
				}
			}		
			float fontsize = 20.0;
			float wideth = bytes * fontsize/2;
			CCSize sizev = pVipSprite->getContentSize();
			pVipSprite->setScale(0.9);
			pVipSprite->setPosition(ccp(pos.x + wideth/2 + sizev.width/2 , pos.y));
			_bodyLayer->addChild(pVipSprite, 5);
			pVipSprite->release();
	}
}
