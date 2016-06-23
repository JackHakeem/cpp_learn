#ifndef _TIPSEQUIPCANVAS_H_
#define _TIPSEQUIPCANVAS_H_

#include "BaseType.h"
#include "Alert.h"

//class BagGoods;
//class BagView;

class GameDispatcher;
class TipBase;
class TipHelps;
class TipsEquipCanvas: public LayerNode
{
public:
	TipsEquipCanvas();
	bool displayTip(CCPoint coordinate, TipBase* tips, int32 type, char* param, TipBase* otherTips=0);
	void tick(ccTime dt);

	void clickhandle(CCObject* pSender);


public:
	float dieCount;
	Alert* m_alert;
	GameDispatcher* _dispatcher;
};

extern TipsEquipCanvas* g_pTipsEquipCanvas;

#endif
