#pragma once

#include "BaseType.h"
#include "Alert.h"

class GameDispatcher;
class TipBase;
class TipHelps;
class TipsXHCanvas: public LayerNode
{
public:
	TipsXHCanvas();
	bool displayTip(CCPoint coordinate, TipBase* tips, char* param, TipBase* otherTips);


	Alert* m_alert;
	GameDispatcher* _dispatcher;
};

extern TipsXHCanvas* g_pTipsXHCanvas;
