#ifndef _FIND_VO_H_
#define _FIND_VO_H_

class FindVo
{
public:
	FindVo(){reset();}
	~FindVo(){}
	void reset()
	{
		_type = 0;
		_sceneId = 0;
		_npcId = 0;
		_isShowWorldMap = true;
	}
public:
	//0 scene, 1, NPC, 2, and the monster
	int _type;
	int _sceneId;
	int _npcId;
	//Pathfinding process is showed a map of the world (the default are displayed)
	bool _isShowWorldMap;
};
#endif