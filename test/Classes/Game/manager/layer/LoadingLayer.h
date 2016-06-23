#ifndef _LoadingLayer_H_
#define _LoadingLayer_H_

#include "BaseType.h"
#include "socket/network/Packet.h"
#include "utils/flash/CCIEventDispatcher.h"

USING_NS_CC;

class LoadingLayer:public CCLayer//LayerNode
{
public:
	LoadingLayer();
	~LoadingLayer();
	bool init();

public:
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	void socketWait_old( PacketID_t idMessage );
	void socketWait( PacketID_t idMessage, CCNode* tar, SEL_CallFuncND selector  );
	void releaseLock( PacketID_t idMessage );
	void TimeOutreleaseLock( ccTime ct );
private:
	//map<PacketID_t, bool> m_releaseLockMessageContainer;
	PacketID_t m_releaseLockMessage;
	CCSprite* m_actionSprite;
	KKCallfunc m_vCallback;//when timeout run
};

#endif