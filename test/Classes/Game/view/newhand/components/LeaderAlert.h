#ifndef _LEADER_ALERT_H_
#define _LEADER_ALERT_H_
#include "LayerNode.h"
#include "ObjectGlow.h"
#include "utils/flash/CCIEventDispatcher.h"

class LeaderAlert : public LayerNode
{
public:
	LeaderAlert(string info, int type, bool isModel, CCNode *pTarget, SEL_CallFuncND selector, void *data );
	virtual ~LeaderAlert();

	static LeaderAlert* show(string info, int type, bool isModel, CCNode *pTarget, SEL_CallFuncND selector, void *data);
	virtual bool init();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	void close();
	void dispose();
	void closeModel();


	void onPopContainerOpen(CCNode *pNode, void *pData);
private:
	SEL_CallFuncND _selector;
	int _type;
	int m_pri;
	bool playInfo3(string info);
	bool playInfo5(int picId);

	void menuCallback(CCObject *pSender);

	ObjectGlow *_pGlow;
	KKCallfunc _callBack;
};
extern LeaderAlert *_preInstance;
#endif