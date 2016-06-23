#ifndef HLQS_PathPointManager_H_
#define HLQS_PathPointManager_H_
#include "utils/Singleton.h"
#include "cocos2d.h"
USING_NS_CC;

struct PathPoint
{
	int resId;
	std::string path;
};

class PathPointManager: public Singleton<PathPointManager>
{
public:
	PathPointManager();
	void setWorldMapPathInfos(PathPoint* pathPoint);
	std::vector<CCPoint> getPath(int resId);

public:
	std::map<int, std::string> _pathDic;
};

#endif