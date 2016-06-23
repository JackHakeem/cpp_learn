#ifndef HLQS_ExitManager_H_
#define HLQS_ExitManager_H_
#include "utils/Singleton.h"
#include "vo/ExitVo.h"

class ExitManager: public Singleton<ExitManager>
{
public:
	ExitManager();
	void setExit(ExitVo& exitVo);
	ExitVo* getExit(int exitId);
	std::vector<int>* getExitsByMapId(int mapId);

	void addNotOpenExit(ExitVo* exitVo);
	void removeNotOpenExit(int exitId);
	std::vector<ExitVo*> getNotOpenExitByMapId(int mapId);
	void dispose();

public:

	std::map<int, ExitVo> _exitDic;
	std::map<int, std::vector<int> >_exitMapDic;
	std::map<int, ExitVo*> _notOpenDic; //Export map not open
};

#endif