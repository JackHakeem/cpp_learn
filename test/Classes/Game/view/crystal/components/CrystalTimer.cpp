#include "CrystalTimer.h"
#include "manager/TimerManage.h"
#include "manager/CDManage.h"
#include "manager/ViewManager.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"

CrystalTimer::CrystalTimer( CrystalInfo* info )
{
	//this->setAnchorPoint(CCPointZero);
	//this->setIsRelativeAnchorPoint(true);
	_info = info;
    
	TimerManage::Instance()->add( 1.0f, schedule_selector(CrystalTimer::layout), this );//schedule_selectorDoyang


// 	CrystalView * _crystalView =  ViewManager::getInstance()->crystalView;
// 	if (!_crystalView)
// 	{
// 		return;
// 	}
	std::string szCD = info->time ? ValuesUtil::Instance()->getString("CSL17") : ValuesUtil::Instance()->getString("CSL18");
	_pDesText = CCLabelTTF::labelWithString(szCD.c_str(), 
		CCSizeMake(POSX(220), POSX(40)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(g_CrystalFontSize));
	_pDesText->setColor(info->time ?ccc3(240,133,25):ccc3(12,233,25));
	_pDesText->setPosition(ccp(POSX(20),POSX(0)));
	_pDesText->setAnchorPoint(ccp(0,0.5));
	_pDesText->setIsRelativeAnchorPoint(true);
	this->addChild( _pDesText ,0,TAG_DES);

	string str = TimerManage::Instance()->formatData((uint)_info->time, CDManage::Instance()->getServerTime());
	_tfText = CCLabelTTF::labelWithString( str.c_str(),CCSizeMake(POSX(100), POSX(40)),
		CCTextAlignmentLeft, g_sSimHeiFont, POSX(20) );
	_tfText->setColor(info->time ?ccc3(240,133,25):ccc3(12,233,25));
	_tfText->setAnchorPoint(ccp(0,0.5));
	_tfText->setIsRelativeAnchorPoint(true);
	_tfText->setColor(ccc3(240,133,25));
	_tfText->setPosition(ccp(POSX(150),POSX(0)));
	this->addChild( _tfText ,0,TAG_TIMER);
}

CrystalTimer::~CrystalTimer()
{

}

CrystalTimer* CrystalTimer::CrystalTimerWithCrystalInfo( CrystalInfo* info )
{
	if ( !info )
	{
		return 0;
	}

	CrystalTimer* pCrystalTime = new CrystalTimer(info);
	return pCrystalTime;
}

void CrystalTimer::update( CrystalInfo* info )
{
	_info = info;
	TimerManage::Instance()->add( 1.0f, schedule_selector(CrystalTimer::layout),this);//schedule_selectorDoyang
	layout();
}

void CrystalTimer::layout( ccTime dt )
{
	if( !_info ) return ;

	std::string strDes = _info->time ? ValuesUtil::Instance()->getString("CSL17") : ValuesUtil::Instance()->getString("CSL18");
	std::string strTime = TimerManage::Instance()->formatData((uint)_info->time, CDManage::Instance()->getServerTime());

	if(_pDesText && (_pDesText->getString() != strDes))
	{
		_pDesText->setString( strDes.c_str() );
	}

    if(_tfText && (_tfText->getString() != strTime))
    {
		_tfText->setString( strTime.c_str() );
    }

	_pDesText->setColor(_info->time ?ccc3(240,133,25):ccc3(12,233,25));
	_tfText->setColor(_info->time ?ccc3(240,133,25):ccc3(12,233,25));
}

void CrystalTimer::reinit()
{
	//scheduleUpdate();
	TimerManage::Instance()->remove( schedule_selector( CrystalTimer::layout ), this );
	TimerManage::Instance()->add( 1.0f,schedule_selector( CrystalTimer::layout ), this );
}

void CrystalTimer::dispose()
{
	TimerManage::Instance()->remove( schedule_selector(CrystalTimer::layout), this );//schedule_selectorDoyang
}
