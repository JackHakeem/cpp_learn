#ifndef HLQS_SceneVo_H_
#define HLQS_SceneVo_H_

USING_NS_CC;

class SceneVo
{
public:
	int id;
	std::string name;
	int x;
	int y;
	int mapResId;
	std::string resid;
	int type;			//SceneType

	int pid; // father map if no is 0
	int preId; // a map layer, if not is 0
	int nextId; // a layer of the map, if not is 0
	std::string remark; // introduced, note
	int timeLim; // into the number limit
public:
	SceneVo()
	{
		id = 0;
		x = 0;
		y = 0;
		mapResId = 0;
		type = 0;			//SceneType

		pid = 0; // father map if no is 0
		preId = 0; // a map layer, if not is 0
		nextId = 0; // a layer of the map, if not is 0
		timeLim = 0; // into the number limit
	}
};

#endif