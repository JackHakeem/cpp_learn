#ifndef _TIPSSKILLCANVAS_H_
#define _TIPSSKILLCANVAS_H_

#include "BaseType.h"
#include "Alert.h"

class GameDispatcher;
class TipBase;
class TipHelps;
class TipsSkillCanvas: public LayerNode
{
public:
	TipsSkillCanvas();
	bool displayTip(CCPoint coordinate, TipBase* tips, char* param, TipBase* otherTips);


	Alert* m_alert;
	GameDispatcher* _dispatcher;
};

extern TipsSkillCanvas* g_pTipsSkillCanvas;

#endif