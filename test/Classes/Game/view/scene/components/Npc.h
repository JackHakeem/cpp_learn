#include "LiveThing.h"
//
//  Npc.h
//  HLQS
//
//  Created by edward liu on 12-3-5.
//  Copyright (c) 2012 4399. All rights reserved.
//

#ifndef HLQS_Npc_h
#define HLQS_Npc_h

class NPCVo;

class Npc : public LiveThing
{
public:

	Npc();
	~Npc();

	CCSprite * loadNpc();
	CCSprite * getNpcSprite();
	void playAnimation();
	void stopAnimation();

	void npcMove(char** map_desc, int &h, int &w);

private:
	CCAnimation** walkAnimationNpc;
	CCAnimation** standAnimationNpc;
	CCAction *m_action;

	CCAnimation* roleAnimation;

	int m_direction;

	vector<CCPoint> m_path;


};


#endif
