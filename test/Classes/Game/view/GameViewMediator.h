#ifndef _GAME_VIEW_MEDIATOR_H_
#define _GAME_VIEW_MEDIATOR_H_

#include "GameView.h"
#include "BaseType.h"
#include "BaseMediator.h"

class GameViewMediator : public BaseMediator
{
public:
	enum
	{
		GOTO_GAME_VIEW = 0,
	};
public:
	GameViewMediator();
	~GameViewMediator();

	GameView *_gameView;
	virtual void handleNotification(int M2Vcmd, char* data);
	void gameViewAddChilds();
};

#endif