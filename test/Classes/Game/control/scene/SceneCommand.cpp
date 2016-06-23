#include "control/scene/SceneCommand.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "model/scene/vo/SceneInfoVo.h"
#include "utils/xml/TinyElementHandler.h"
#include "util/TileUtil.h"
#include "utils/findPath/FindPath8.h"
#include "model/player/RoleManage.h"
#include "model/scene/SceneManager.h"
#include <math.h>
#include "CCFileUtils.h"
#include "utils/Timer.h"
#include "utils/ScaleUtil.h"
#include "manager/LayerManager.h"
#include "view/mainUI/components/MainNavigate.h"

SceneCommand::SceneCommand():_loadTimes(3)
{
	//_sceneProxy = new SceneProxy();
	_sceneProxy = NULL;
}

SceneCommand::~SceneCommand()
{
	//delete _sceneProxy;
}

void SceneCommand::excute(int32 command, char* data)
{
	if(!g_pFacade)
		return;

	_sceneProxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
	if(_sceneProxy)
		_sceneProxy->isLoadMap = true;
	//int id = (int)data[0];
	char fileName[50] = {0};
	char path[50] = {0};
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;
	int id = info->playerBaseInfo._mapId;
	SceneVo* scene = SceneManager::Instance()->getSceneDic(id);
	if (!scene) return;
	std::string scenePath = "assets/mapassets/scene/%d/";
	std::string sceneRoot = "assets/mapassets/scene/%d/map.xx";
	sprintf(fileName, sceneRoot.c_str(), scene->mapResId);
	sprintf(path, scenePath.c_str(), scene->mapResId);
	loadMapData(path, fileName);
}

void SceneCommand::loadMapData(char* path, char* fileName)
{
	SceneInfoVo sceneInfo = SceneInfoVo();

    const char* filePath = CCFileUtils::fullPathFromRelativePath(fileName);
	if (!filePath)
		return ;

	TiXmlDocument xmlDoc(filePath); 
	bool sus = xmlDoc.LoadFile();
	if (!sus)
		return;

	TiXmlElement* pRootElement = xmlDoc.RootElement();
	if(!pRootElement)  
		return;  

	TiXmlNode* pNode = NULL;
	TiXmlElement* pEle = NULL;
	pNode = pRootElement->FirstChildElement();
	if(!pNode)
		return;
	int t = pNode->Type();
	if(t == TiXmlText::TINYXML_ELEMENT)
	{
		pEle = pNode->ToElement();
		TinyElementHandler elehandler(pEle);
		elehandler.get(sceneInfo.name);
		elehandler.get(sceneInfo.width);
		elehandler.get(sceneInfo.height);
		elehandler.get(sceneInfo.blockW);
		elehandler.get(sceneInfo.blockH);
		elehandler.get(sceneInfo.offsetX);
		elehandler.get(sceneInfo.offsetY);
	}

	sceneInfo.sceneRoot = std::string(path);
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(info)
	{

		sceneInfo.id =  info->playerBaseInfo._mapId;
		SceneVo* sceneVo = SceneManager::Instance()->getSceneDic(sceneInfo.id);
		if(sceneVo)
		{
			sceneInfo.type = sceneVo->type;
			sceneInfo.name = sceneVo->name;
			sceneInfo.pid = sceneVo->pid;
		}
	}

	if(pNode)
		pNode = pNode->NextSiblingElement();
	if(pNode)
		pNode = pNode->NextSiblingElement();

	const char *pt = NULL;
	if(pNode && pNode->FirstChild())
		pt = pNode->FirstChild()->Value();

	//int cols = (sceneInfo.width - sceneInfo.offsetX) / TileUtil::Instance()->getTileWidth();
	//int rows = (sceneInfo.height - sceneInfo.offsetY) / TileUtil::Instance()->getTileHeight();
	//POSX edwardliu
	//sceneInfo.width = sceneInfo.width / ScaleUtil::Instance()->pixNum();
	sceneInfo.mapCols = ceil(((float)(sceneInfo.width)) / (float)sceneInfo.blockW);
	sceneInfo.mapRoWs = ceil(((float)(sceneInfo.height)) / (float)sceneInfo.blockH);

	sceneInfo.width = POSX(sceneInfo.width);
	sceneInfo.height = POSX(sceneInfo.height);
	sceneInfo.blockH = POSX(sceneInfo.blockH);
	sceneInfo.blockW = POSX(sceneInfo.blockW);
	sceneInfo.offsetX = POSX(sceneInfo.offsetX);
	sceneInfo.offsetY = POSX(sceneInfo.offsetY);

	int cols = ceil(((float)(sceneInfo.width)) / (float)(TileUtil::Instance()->getTileWidth()));
	int rows = ceil(((float)(sceneInfo.height)) / (float)(TileUtil::Instance()->getTileHeight()));
	sceneInfo.cellCols = cols;
	sceneInfo.cellRows = rows;

	for(int y = 0; y < rows; ++y)
		for(int x = 0; x < cols; ++x)
		{
			//Characters for the digital transition, NND
			if(pt)
				sceneInfo.mapData[y][x] = *((char*)pt + y * cols + x) - 48;
			//CCLog("sceneInfo.mapData[%d][%d]:%d", y, x, sceneInfo.mapData[y][x]);
		}

	//for(int i = 0; i < cols * rows; ++i)
	//{
	//	for(int x = 0; x < cols; ++x)
	//	{
	//		sceneInfo.mapData[y][x] = *((char*)pt + y * cols + x) - 48;
	//		CCLog("sceneInfo.mapData[%d][%d]:%d", y, x, sceneInfo.mapData[y][x]);
	//	}
	//}
	/*for(int i = 0; i < cols * rows; ++i)
	{
		sceneInfo.mapData[i] = *((char*)pt + i) - 48;
	}*/

	//FindPath8 findPath8 = FindPath8((char**)sceneInfo.mapData, rows, cols);
	_findPath8 = FindPath8((char**)sceneInfo.mapData, MAX_CELLS_Y, MAX_CELLS_X);
	_sceneInfo = sceneInfo;

	TileUtil::Instance()->setPicWidth( _sceneInfo.blockW );
	TileUtil::Instance()->setPicHeight( _sceneInfo.blockH );
	/*if(_sceneProxy)
		_sceneProxy->setSceneInfoVo(sceneInfo, findPath8);*/

	CCLog("-------------------after _sceneProxy->setSceneInfoVo: %d",  Timer::millisecondNow());
}

void SceneCommand::setSceneInfo()
{
	if(_sceneProxy)
		_sceneProxy->setSceneInfoVo(_sceneInfo, _findPath8);

	MainNavigate* navigage = (MainNavigate*)LayerManager::sceneUILayer->getChildByTag(SceneUILayer::SceneUILayerTAG_MainUIMediator);
	if (!navigage)
	{
		return;
	}
	
	if(_sceneInfo.id < 1050)
	{
		// Is main town.
		navigage->hideOutMap();
	}
	else
	{
		navigage->showOutMap();
	}
}
