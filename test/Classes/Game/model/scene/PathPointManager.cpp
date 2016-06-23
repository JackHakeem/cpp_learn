#include "PathPointManager.h"

PathPointManager::PathPointManager()
{
}

void PathPointManager::setWorldMapPathInfos(PathPoint* pathPoint)
{
	if(!pathPoint)
		return;

	_pathDic.insert(make_pair(pathPoint->resId, pathPoint->path));
}

std::vector<CCPoint> PathPointManager::getPath(int resId)
{
	std::vector<CCPoint> path;
	std::map<int, std::string>::iterator iter = _pathDic.find(resId);
	if(iter == _pathDic.end())
		return path;

	char pathData[1024] = {0};
	sprintf(pathData,"%s", iter->second.c_str());
	char pathArr[16] = {0};
	//int j=0;
	char *token;
	std::vector<std::string> tmpVec;
	token = strtok( pathData, "|" );
	while( token != NULL )
	{
		memcpy(pathArr, token, sizeof(*token));
		token = strtok( NULL, "|" );
		tmpVec.push_back(std::string(pathArr));
	}

	std::vector<std::string>::iterator it = tmpVec.begin();
	for(; it != tmpVec.end(); ++it)
	{
		char p[10] = {0};
		sprintf(p, "%s", (*it).c_str());
		token = strtok(p, ",");
		CCPoint point;
		point.x = atof(token) -3;
		token = strtok(NULL, ",");
		point.y = atof(token) - 3;
		path.push_back(point);
	}

	return path;
}