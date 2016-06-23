#ifndef _MAPMEDIATOR_H_
#define _MAPMEDIATOR_H_

#include "BaseType.h"
#include "mvc/Mediator.h"

class Map;
class GameDispatcher;
class SceneProxy;
class MapMediator:public Mediator
{
public:
	MapMediator();

	void startupSmallmapUI(CCNode* n, void* data);
	void openMapView();
	void startListener();
	void addNPCHandler(std::vector<int>& arr);
	void roleToNpc(CCNode* n, void* data);
	void rolePosChangeHandler( CCNode* n, void* data );
	void roleMoveHandler( CCNode* n, void* data );
public:
	Map* _map;
	GameDispatcher* _dispatcher;
	CCPoint _rolePos;
	bool _isStart;
	SceneProxy* _sceneProxy;
	std::vector<CCPoint> _pathArr;

	enum
	{
		CLOSE_MAP,
	};
};

#endif