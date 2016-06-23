#include "CDManage.h"
#include "Alert.h"
#include "model/player/RoleManage.h"
#include "events/GameDispatcher.h"
#include "events/CDEvent.h"
#include "TimerManage.h"
#include "utils/ValuesUtil.h"
#include "CustomCD.h"
#include "LangManager.h"
#include "ViewManager.h"
#include "view/ore/OreMediator.h"

int CDManage::BUY_LIST_VIPLEV[6] = {0, 0, 0, 1, 4, 8};
int CDManage::BUY_LIST_GOLD[6] = {0, 0, 100, 200, 300, 400};
//string CDManage::CDlockTimeName[CDManage::TIMER_MAX];

CDManage::CDManage()
{
	string cdArray[TIMER_MAX] = { 
		LangManager::getText("CD001"), 
		LangManager::getText("CD002"),
		LangManager::getText("CD003"),
		LangManager::getText("CD004"),
		"",
		LangManager::getText("CD020"),
		LangManager::getText("CD005"),
		LangManager::getText("CD006"),
		LangManager::getText("CD007",1),
		LangManager::getText("CD007",2),
		LangManager::getText("CD007",3),
		LangManager::getText("CD007",4),
		LangManager::getText("CD007",5),
		LangManager::getText("CD007",6), 
		LangManager::getText("CD008"), 
		LangManager::getText("CD009"),
		LangManager::getText("CD010"),
		"",
		"",
		""//LangManager::getText( "CD015" )
	};

	for ( int i = 0; i < TIMER_MAX; i++ )
	{
		CDlockTimeName[i] = cdArray[i];
	}

	_clientTimer = 0;
	_serverTimer = 0;
	_timeoffset = 0;
	m_nLastTick = 0;

	TimerManage::Instance()->add( 1.0f, schedule_selector(CDManage::step), this );//schedule_selectorDoyang
}

CDManage::~CDManage()
{
	std::map<int, CustomCD*>::iterator it;
	for ( it = customCDDic.begin(); it != customCDDic.end(); it++ )
	{
		//CC_SAFE_DELETE( it->second );
		it->second = 0;
	}
	customCDDic.clear();

	map<int, CDNode*>::iterator itCDic;
	for ( itCDic = _cdDic.begin(); itCDic != _cdDic.end(); itCDic++ )
	{
		CC_SAFE_DELETE( itCDic->second );
	}
	_cdDic.clear();
}

/**
* rewrite in a time 
* @param value second
* 
*/		
void CDManage::serverTimer( Number value )
{
	_serverTimer = value * 1000;
	setTimeoffset( _serverTimer );

	//Message::Instance()->show( TimerManage::formatServerTimeToDate(value) );
}

void CDManage::setTimeoffset( Number sTimer )
{
	_clientTimer = Timer::millisecondNow();
	_timeoffset = sTimer - _clientTimer;
	m_nLastTick = Timer::millisecondNow();

	TimerManage::Instance()->remove( schedule_selector(CDManage::timeStep), this );//schedule_selectorDoyang
	timeStep( 1.0f );
	TimerManage::Instance()->add( 1.0f, schedule_selector(CDManage::timeStep), this );//schedule_selectorDoyang
}
		
/**
* _timeoffset bettween server and client 
* @return millisecond
* 
*/		
Number CDManage::getTimeoffset()
{
	return _timeoffset ;
}

// 独立出来计时 同步 
void CDManage::timeStep( ccTime dt )
{
	Number bOffset = Timer::millisecondNow() - m_nLastTick;
	//CCLog("bOffset:%d", bOffset);
	_clientTimer = _clientTimer + bOffset;  // 
	m_nLastTick = Timer::millisecondNow();
}
		
/**
* get server time 
* @return millisecond
* 
*/		
Number CDManage::getServerTime() 
{
	if(_clientTimer == 0)
	{
		_clientTimer = (Number)Timer::millisecondNow();  // if 0 then haven't get server time,return client time
	}
	return _clientTimer + _timeoffset; 
}
		
/**
* initial CD
* @param array
* 
*/		
void CDManage::initAllCD( vector<SCMD17F::SCMD17FNode>& array )
{
	vector<SCMD17F::SCMD17FNode>::iterator it = array.begin();
	for ( ;it != array.end(); it++ )
	{
		SCMD17F::SCMD17FNode obj = *it;
		CDNode* pCDNode = new CDNode;
		pCDNode->lock = obj.b_incd;
		pCDNode->time = (Number)obj.c_time * 1000;

		_cdDic.insert( make_pair( obj.a_type, pCDNode ) );
	}
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          

void CDManage::addNewCD(int type , int time)
{
	CDNode* pCDNode = new CDNode;
	pCDNode->lock = 1;
	pCDNode->time = (Number)time * 1000;

	if (_cdDic.find(type) != _cdDic.end())
	{
		CC_SAFE_DELETE(_cdDic.find(type)->second);
		_cdDic.erase(_cdDic.find(type));
	}	
	_cdDic.insert( make_pair( type, pCDNode ) );
}

/**
* update a CD
* @param type
* @param time second
*/
void CDManage::updateCD( int type, int lock, Number time )
{
	map<int, CDNode*>::iterator it = _cdDic.find( type );
	if ( it != _cdDic.end() )
	{
		CDNode* pCDNode = it->second;
		pCDNode->lock = lock;
		pCDNode->time = time * 1000;
	}
	else
	{
		CDNode* pCDNode = new CDNode;
		pCDNode->lock = lock;
		pCDNode->time = time * 1000;
		_cdDic.insert( make_pair( type, pCDNode ) );
	}

	CDEvent e( "CDCHANGED", type, lock, time * 1000 );

	this->dispatchEvent(  CDManage::CDCHANGED, (char*)&e ) ;
}

/**
*  Clear a CD
* @param type CD type
* @param state clear result，0:success,6:not enough gold
*/
void CDManage::clearCD( uint type, uint state )
{
	switch(state)
	{
	case 0:
		updateCD( type, 0, getServerTime() * 0.001 );
		break;
	case 6:
		//m_alert->addStr( LangManager::getText("CD011"), ccc3(255,225,135) );
		LangManager::msgShow( "CD011", ccc3(255,225,135) );
		break;
	}
}

/**
* Get a CD end time
* @param type
* @return millisecond
*/		
Number CDManage::getCDTimeBytype( uint type )
{
	map<int, CDNode*>::iterator it = _cdDic.find( type );
	if ( it != _cdDic.end() )
	{
		CDNode* pCDNode = it->second;
		return pCDNode->time;
	}

	return 0;
}
		
/**
*  get a CD's lock(red) 
* @param type
* @return 
* 
*/		
int CDManage::getLockBytype( uint type )
{
	map<int, CDNode*>::iterator it = _cdDic.find( type );
	if ( it != _cdDic.end() )
	{
		CDNode* pCDNode = it->second;
		return pCDNode->lock;
	}

	return 0;
}

/*
* system autorelease lock
*/
void CDManage::step( ccTime ct )
{
	//_clientTimer = _clientTimer + 1000;
	Number sTime = getServerTime();
	vector<int> array;
	int i(0);
	for ( map<int, CDNode*>::iterator it = _cdDic.begin(); it != _cdDic.end(); it++ )
	{
		CDNode* obj = it->second;
		if ( !obj )
		{
			CCLog( "Empty CD!\n" );
			continue;
		}
		i = it->first;
		
		if ( sTime >= obj->time && obj->lock )
		{
			// autorelease lock
			array.push_back( i );
			obj->lock = 0;
			if( i != ONLINE_AWARD )
			{
				//CDEvent *pCDEvent = new CDEvent( "CDCHANGED", i, 0, obj->time );
				//this->dispatchEvent(  CDManage::CDCHANGED, &pCDEvent  ) ;
				CDEvent e( "CDCHANGED", i, 0, obj->time );
				this->dispatchEvent(  CDManage::CDCHANGED, (char*)&e ) ;
			}
		}
		else if( i == FIGHT || i == STRENGTHEN )
		{
			// Fight CD and Streng CD changed
			if( i == STRENGTHEN && RoleManage::Instance()->roleLev() < 36 )
			{
				if( sTime >= ( obj->time - 2*60*1000 ) && obj->lock == 1 )
				{
					obj->lock = 0;
                    //CDEvent *pCDEvent = new CDEvent( "CDCHANGED", i, 0, obj->time ) ;
					//this->dispatchEvent(  CDManage::CDCHANGED, &pCDEvent ) ;
					CDEvent e( "CDCHANGED", i, 0, obj->time );
					this->dispatchEvent(  CDManage::CDCHANGED, (char*)&e ) ;
				}
			} 
			else if( sTime >= ( obj->time-30*60*1000 ) && obj->lock==1 )
			{
				obj->lock = 0;
				//CDEvent *pCDEvent = new CDEvent( "CDCHANGED", i, 0, obj->time ) ;
				//this->dispatchEvent(  CDManage::CDCHANGED, &pCDEvent) ;
				CDEvent e( "CDCHANGED", i, 0, obj->time );
				this->dispatchEvent(  CDManage::CDCHANGED, (char*)&e ) ;
			}
		}
	}//for

	if( array.size() > 0 )
	{
		for (int j = 0; j < array.size(); j++ )
		{
			int iTemp = array[j];
			map<int, CDNode*>::iterator it = _cdDic.find( iTemp );
			if ( it != _cdDic.end() )
			{
				CC_SAFE_DELETE( it->second );
				_cdDic.erase( it );
			}
		}
	}
}

/**
* Register CD computing，jump once per second
* @param fun
*/
void CDManage::addTimerHandle( SEL_SCHEDULE pfnSelector, CCObject *pTarget  )
{
	CCScheduler::sharedScheduler()->scheduleSelector( pfnSelector, pTarget, 1.0f, false);
}

void CDManage::removeTimerHandle( SEL_SCHEDULE pfnSelector, CCObject *pTarget )
{
	CCScheduler::sharedScheduler()->unscheduleSelector( pfnSelector, pTarget );
}

void CDManage::addCustomCD( int type, CustomCD* pCustomCD )
{
	if ( pCustomCD )
	{
		std::map<int, CustomCD*>::iterator it = customCDDic.find(type);
		if ( it == customCDDic.end() )
		{
			customCDDic.insert( make_pair( type, pCustomCD ) );
		}
		else
		{
			CCLog("Custom cd add error.");
		}
// 		if (type >= 8 && type <= 13)
// 		{
// 			_CrystalCDDic.insert( make_pair( type, pCustomCD ) );
// 		}
	}
	
}

void CDManage::deleteCustomCD( int type )
{
	std::map<int, CustomCD*>::iterator it = customCDDic.find(type);
	if ( it != customCDDic.end() )
	{
		customCDDic.erase( it );
	}
	
}

CustomCD* CDManage::getCustomCD( int type )
{
	std::map<int, CustomCD*>::iterator it = customCDDic.find(type);
	if ( it != customCDDic.end() )
	{
		return it->second;
	}

	return 0;
}

bool CDManage::getCDReady( int cdType )
{
	Number sTime = getServerTime();
	Number _timer = getCDTimeBytype( cdType );

	if( _timer <= sTime)
	{
		return true;
	}
	return false;
}

int CDManage::getTagByMinOreCD()
{
	int tag = -1;
	OreMediator * pMetr = (OreMediator *)g_pFacade->retrieveMediator(AppFacade_ORE);
	if (!pMetr)
	{
		return -1;
	}	
	int num = pMetr->getOreNumber();
	std::map<int , Number> tmmap;
	tmmap.insert(make_pair(ORE_0 , getCDTimeBytype(ORE_0)));
	tmmap.insert(make_pair(ORE_1 , getCDTimeBytype(ORE_1)));
	tmmap.insert(make_pair(ORE_2 , getCDTimeBytype(ORE_2)));
	tmmap.insert(make_pair(ORE_3 , getCDTimeBytype(ORE_3)));
	tmmap.insert(make_pair(ORE_4 , getCDTimeBytype(ORE_4)));

	if (tmmap.empty())
	{
		return -1;
	}
	
	std::map<int , Number>::iterator iter = tmmap.begin();
	Number time = iter->second;
	int count = 1;
	for (iter ; iter != tmmap.end() ; iter++)
	{
		if (count > num)
		{
			break;
		}
		time = MIN(time , iter->second);
		++count;
	}

	 iter = tmmap.begin();
	 count = 1;
	for (iter ; iter != tmmap.end() ; iter++)
	{
		if (count > num)
		{
			break;
		}
		if (iter->second == time)
		{
			tag = iter->first;
		}
		++count;
	}

	return tag;	
}

int CDManage::getNoCDOreNum()
{
	OreMediator * pMetr = (OreMediator *)g_pFacade->retrieveMediator(AppFacade_ORE);
	if (!pMetr)
	{
		return 0;
	}

	int nmber = pMetr->getOreNumber();

	std::map<int , bool> tmmap;
	tmmap.insert(make_pair(ORE_0 , getCDReady(ORE_0)));
	tmmap.insert(make_pair(ORE_1 , getCDReady(ORE_1)));
	tmmap.insert(make_pair(ORE_2 , getCDReady(ORE_2)));
	tmmap.insert(make_pair(ORE_3 , getCDReady(ORE_3)));
	tmmap.insert(make_pair(ORE_4 , getCDReady(ORE_4)));

	if (tmmap.empty())
	{
		return 0;
	}

	int count = 0;
	int count1 = 0;
	std::map<int , bool>::iterator iter = tmmap.begin();
	for (iter ; iter != tmmap.end() ; iter++)
	{
		if (!iter->second)
		{
			++count;
			if (count >= nmber)
			{
				break;
			}
			continue;
		}
		++count1;		
		++count;
		if (count >= nmber)
		{
			break;
		}
	}
	return count1;
}


