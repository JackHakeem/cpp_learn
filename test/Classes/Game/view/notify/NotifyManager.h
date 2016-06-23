#pragma once

#include "BaseType.h"
#include "utils/Singleton.h"
#include "LayerNode.h"

class NotifyGrid;
class NotifyLayer;

class NotifyManager : public Singleton<NotifyManager> , public LayerNode
{
public:
	
public:
	NotifyManager();
	~NotifyManager();	
	virtual bool init();

public:
	void addNoticeLayer();
	void addNotification(int type); 
	int getListCount();
	std::map<int , NotifyGrid *> * getList();
	void refresh(CCNode * pNode , void * data);
	void playFlyAction(CCSprite * pItem);
	CCPoint & getStartPos(CCSize &size);
	void removeLayerByType(int type);

public:
	std::map<int , NotifyGrid *> _noticeList;
	enum
	{
		MAX_COUNT = 32,
	};

public:
	NotifyLayer * _notifyLayer;

};