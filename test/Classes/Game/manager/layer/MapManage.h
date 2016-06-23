#ifndef HLQS_MapManage_H_
#define HLQS_MapManage_H_
#include "utils/Singleton.h"
#include "model/scene/vo/FindVo.h"

class MapManage: public Singleton<MapManage>
{
public:
	MapManage();
	void findPath(FindVo _findVo);
	FindVo findVo();
	void cancelAutoPath();
	FindVo changeFindVoHandler(FindVo findVo);
	FindVo nextFindVo();
public:
	bool isAutoFindPath;
	FindVo _findVo;
	FindVo _nextFindVo;
};

#endif