#ifndef _SCENE_UI_LAYER_H_
#define _SCENE_UI_LAYER_H_

#include "BaseType.h"
#include "model/notice/NoticeManager.h"

#define NOTICE_START (500)

class SceneUILayer : public LayerNode
{
public:
	enum 
	{
		SceneUILayerZ_MainUIMediator = 0,
		SceneUILayerZ_WorldBoss,
		SceneUILayerZ_SmallMapMediator = SceneUILayerZ_MainUIMediator,
		SceneUILayerZ_btnFriend,
	};

	enum 
	{
		SceneUILayerTAG_MainUIMediator = 0,
		SceneUILayerTAG_SmallMapMediator,

		SceneUILayerTAG_btnFriend =NoticeManager::ADD_FRI+NOTICE_START,

		SceneUILayerTAG_RoleUI,

		SceneUILayerTAG_WorldBoss,

	};
	SceneUILayer(){}
	~SceneUILayer(){}

	virtual bool init();

	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch* touch, CCEvent* event);
};
#endif