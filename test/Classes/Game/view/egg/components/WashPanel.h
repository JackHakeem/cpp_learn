#pragma once

#include "BaseType.h"
#include "utils/TipBase.h"

class GameDispatcher;
class TipHelps;
class WashPanel:public LayerNode, public TipBase
{
public:
	WashPanel();
	~WashPanel();

	bool init();

	void close(CCObject* pSender);
	void updateGoods(int goodsId, int goodsNum);
	void updateTips(int goodsId);
	void washHandler(CCObject* pSender);
	void getHandler(CCObject* pSender);
	void onTips(CCObject* pSender);
	CCSize getSrcContentSize();
	void PlayEffectComplete( CCNode* pnode );
	void sureWash(CCObject* pSender);
	void sureWashCancel(CCObject* pSender);

	CCMenu* _pic;
	int _goodsId;
	LayerNode* _icon;
	CCLabelTTF* _txtName;
	int _eggId;		// µ°µ°id
	int _sEgg[5];
	GameDispatcher* _dispatcher;
	TipHelps* _tips;
	CCMenuItemSprite* _picbtn;
};