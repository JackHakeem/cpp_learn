#include "Message.h"
#include "view/scene/components/MainScene.h"
#include "utils/ScaleUtil.h"
#include "manager/LayerManager.h"

#include "model/player/vo/PlayerInfoVo.h"
#include "model/player/RoleManage.h"
#include "model/scene/NPCManager.h"
#include "manager/SourceCacheManage.h"
#include "manager/GlobalManage.h"

Message::Message()
{
	//CCLayer::init();
	_msgContainer = 0;
	m_nNumberOfSprites = 0;
	m_nNumberOfLoadedSprites = 0;
}

Message::~Message()
{

}

void Message::show( string msg, ccColor3B color  /*= { 0, 255, 0 }*/, int delay /*= 3*/ )
{
	//onTime( 0.0f );

	//CCSize cs = CCDirector::sharedDirector()->getWinSize();
	//_msgContainer = CCLabelTTF::labelWithString( msg.c_str(), g_sSimHeiFont, 16 );
	//_msgContainer->setColor( color );
	//_msgContainer->setPosition( ccp( cs.width/2, cs.height/2 ) );

	//CCDirector::sharedDirector()->getRunningScene()->addChild( _msgContainer, 50 );

	//CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(Message::onTime), this, (float)delay, false);
	
	CCLog( " message show: %s ", msg.c_str() );
	if ( !LayerManager::tipsLayer )
	{
		return;
	}
	
	CCSize cs = CCDirector::sharedDirector()->getWinSize();
	if ( !_msgContainer )
	{
		_msgContainer = new CCLayer();
		_msgContainer->init();
		//CCDirector::sharedDirector()->getRunningScene()->addChild( _msgContainer, 600 );
		//LayerManager.noticeLayer.addChild(_msgContainer);
		LayerManager::tipsLayer->addChild( _msgContainer, TipsLayer::TipsLayerZ_messageUi+500, TipsLayer::TipsLayerTAG_messageUi );
		_msgContainer->release();

		//CCLayerColor* pLayer = new CCLayerColor();
		//pLayer->initWithColorWidthHeight(  ccc4( 120, 255, 120, 200 ), cs.width, cs.height  );
		//_msgContainer->addChild(pLayer);
	}

	MessageItem* messageItem = MessageItem::MessageItemWithString( msg.c_str() );
	messageItem->setColor( color );
	messageItem->setPosition( ccp( cs.width/2, cs.height/2 ) );
	_msgContainer->addChild( messageItem );
	messageItem->release();

	//CCSize csItem = messageItem->getContentSize();
	//CCLayerColor* pLayer = new CCLayerColor();
	//pLayer->initWithColorWidthHeight(  ccc4( 0, 0, 255, 200 ), csItem.width, csItem.height  );
	//messageItem->addChild(pLayer);

	_msgList.addObject( messageItem );
	layout();
	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(MessageItem::onTime), messageItem, (float)delay, false);

	if ( _msgList.count() > 3 )
	{
		messageItem = _msgList.getObjectAtIndex( 0 );
		CCScheduler::sharedScheduler()->unscheduleSelector( schedule_selector(MessageItem::onTime), messageItem );
		_msgList.removeObject( messageItem, true );
		if ( messageItem && messageItem->getParent() )
		{
			messageItem->removeFromParentAndCleanup( true );
		}
	}

}

/**
* Repain
*/
void Message::layout()
{
	CCSize cs = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* messageItem = 0;
	int len = _msgList.count();
	if ( len == 0 )		return;
	int i = 0;
	int j = len - 1;
	while (j >= 0)
	{
		i++;
		messageItem = _msgList.getObjectAtIndex(j);
		messageItem->setPosition( ccp( cs.width/2, cs.height/2-POSX(50) - POSX(i *( - 30)) ) );
		j = j - 1;
	}
}

void Message::loadingCallBack( CCObject* obj )
{
	++m_nNumberOfLoadedSprites;

	if ( m_nNumberOfLoadedSprites == m_nNumberOfSprites )
	{
		PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
		if(!info)
			return;
		std::vector<int> array = NPCManager::Instance()->getNpcsByMapId(info->playerBaseInfo._mapId);

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		CCLabelTTF* m_pLabelPercent = (CCLabelTTF*)LayerManager::tipsLayer->getChildByTag( TipsLayer::TipsLayerTAG_CurPercent );

		char _assetURL[128] = {0};
		char tmp[10] = {0};
		for(std::vector<int>::iterator iter = array.begin();
			iter != array.end(); ++iter)
		{
			NPCVo* npcVo = NPCManager::Instance()->getNPC(*iter);
			if(!npcVo)
				continue;

			sprintf( _assetURL, "assets/res/%d", npcVo->_resId );
			//BitmapMovieClip* m = NULL;
			//if(  npcVo->_isMonster ||
			//	(npcVo->action==SceneConst::FIGHT)  )
			//{
			//	m = SourceCacheManage::Instance()->loadModel(_assetURL, npcVo->_resId, 0.2f, false, true);
			//}
			//else
			//{
			//	m = SourceCacheManage::Instance()->loadPvrNormal(_assetURL,
			//		npcVo->_resId, BitmapMovieClip::ACTION_STAND, npcVo->state, 0.2f, false, true);
			//}

			++g_pGlobalManage->m_nNumberOfLoadedSprites;
			sprintf(tmp,"%%%d", (int)(((float)g_pGlobalManage->m_nNumberOfLoadedSprites / g_pGlobalManage->m_nNumberOfSprites) * 100));
			m_pLabelPercent->setString(tmp);
		}

	}
	
}