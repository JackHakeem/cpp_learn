#ifndef _GAMEVIEW_H_
#define _GAMEVIEW_H_

#include "BaseType.h"

class GameView:public LayerNode
{
public:
	GameView();
	~GameView();
	void init();
};

extern GameView* g_pGameView;

#endif