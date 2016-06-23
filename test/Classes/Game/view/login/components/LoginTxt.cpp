#include "LoginTxt.h"
#include "utils/ScaleUtil.h"
#include "manager/NameManager.h"
#include "utils/ValuesUtil.h"
#include "utils/Timer.h"

#define ENTER_DELTA_TIME (3.0f)
#define REMOVE_DELTA_TIME (9.0f)

LoginTxt::LoginTxt()
{
}

LoginTxt::~LoginTxt()
{

}

bool LoginTxt::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    return true;

}

void LoginTxt::start()
{
	srand(Timer::millisecondNow());
	float dt = (float)(rand()%60)/100.0f;
	CCScheduler::sharedScheduler()->scheduleSelector( schedule_selector(LoginTxt::onTime), this ,ENTER_DELTA_TIME-dt,false);
}

void LoginTxt::createMsg()
{

}

void LoginTxt::dispose()
{

}

void LoginTxt::layout()
{
	LoginTxtItem* pLoginTxtItem = 0;
	int len = _msgList.count();
	if ( len == 0 ) { return;}
	int i = 0;
	int j = len - 1;
	while (j >= 0)
	{
		i++;
		pLoginTxtItem = _msgList.getObjectAtIndex(j);
		pLoginTxtItem->setPosition( ccp( POSX(20), POSX(i * 22) ) );
		--j;
	}
}

void LoginTxt::show( std::string msg, ccColor3B color, float delay)
{
	LoginTxtItem* pLoginTxtItem = LoginTxtItem::ItemWithString(msg,color,POSX(20));
	this->addChild(pLoginTxtItem);

	_msgList.addObject( pLoginTxtItem );

	LoginTxtItem* pTmpLoginTxtItem = 0;
	if ( _msgList.count() > 3 )
	{
		pTmpLoginTxtItem = _msgList.getObjectAtIndex( 0 );
		_msgList.removeObjectAtIndex( 0, false );
		if ( pTmpLoginTxtItem && pTmpLoginTxtItem->getParent() )
		{
			pTmpLoginTxtItem->getParent()-> removeChild(pTmpLoginTxtItem, true );
		}
	}
	layout();
	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(LoginTxtItem::onTime), pLoginTxtItem, (float)delay, false);
}

void LoginTxt::onTime(float dt )
{
	srand(Timer::millisecondNow());
	int sex = (rand()%10 > 5) ? 1 : 2;
	std::string name = Namemanager::Instance()->randomName(sex);
	std::string msg = name;
	msg.append(ValuesUtil::Instance()->getString("LG032"));
	int colorR = rand()%255;
	int colorG = rand()%255;
	int colorB = rand()%255;
	show(msg,ccc3(colorR,colorG,colorB),REMOVE_DELTA_TIME);
	//CCScheduler::sharedScheduler()->unscheduleSelector( schedule_selector(LoginTxt::onTime), this);
}