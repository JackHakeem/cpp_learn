#include "TraderProxyCommand.h"
#include "socket/command/s1b/SCMD1B2.h"
#include "view/guild/GuildMediator.h"
#include "model/guild/vo/MemberVo.h"
#include "socket/command/s1c/SCMD1C3.h"
#include "manager/LangManager.h"
#include "model/guild/vo/GuildInfoVo.h"
#include "socket/command/s1c/SCMD1C1.h"
#include "socket/command/s1b/SCMD1BF.h"
#include "model/player/RoleManage.h"
#include "socket/command/s1c/SCMD1C6.h"
#include "model/guild/vo/TechVo.h"
#include "model/skill/SkillManager.h"
#include "model/guild/vo/ApplyVo.h"
#include "socket/command/s1b/SCMD1BC.h"
#include "socket/command/s1b/SCMD1B8.h"
#include "view/chat/ChatMediator.h"
#include "socket/command/s3b/SCMD3B3.h"
#include "socket/command/s3b/SCMD3B5.h"
#include "socket/command/s3b/SCMD3B7.h"
#include "socket/command/s3c/SCMD3CB.h"
#include "model/tower/vo/TowerPanel1Vo.h"
#include "model/scene/vo/NPCVo.h"
#include "model/scene/MonsterManager.h"
#include "model/backpack/GoodsManager.h"
#include "model/tower/vo/TowerRankItemVo.h"
#include "model/trader/vo/TraderEventVo.h"
#include "view/trader/CityTraderMediator.h"
#include "model/trader/vo/BankGridVo.h"
#include "model/scene/SceneProxy.h"
#include "mvc/Facade.h"
#include "model/trader/vo/CityPriceVo.h"
#include "model/scene/SceneManager.h"
#include "model/scene/vo/SceneVo.h"
#include "model/scene/vo/FindVo.h"
#include "manager/GlobalManage.h"
#include "events/GameDispatcher.h"
#include "manager/ViewManager.h"
#include "utils/xml/tinyxml.h"
#include "utils/xml/TinyElementHandler.h"
#include "util/TileUtil.h"
#include "model/scene/ExitManager.h"
#include "view/scene/SceneMediator.h"
#include "model/scene/NPCManager.h"
#include "Confirm.h"

TraderProxyCommand::TraderProxyCommand()
{
	_traderProxy = 0;
}

void TraderProxyCommand::execute( int32 command, char* data )
{
	if (!_traderProxy)
	{
		_traderProxy = (TraderProxy*)g_pFacade->retrieveProxy( AppFacade_CITY_TRADER_CHANGE );
	}

	switch( command )
	{
	case CREATE_HISTORY_LIST:
		updateHistoryList( (SCMD2B4*)data );
		break;
	case CREATE_EVENT_LIST:
		updateEventList( (SCMD2B1*)data );
		break;
	case CREATE_BANK_LIST:
		updateBankList( (SCMD2B3*)data );
		break;
	case CREATE_GOODS_LIST:
		updateItemList( (SCMD2B2*)data  );					
		break;
	case CREATE_CITY_PRICE_LIST:
		updateCityPrice( (SCMD2B6*)data );
		break;
	case START_BUSINESS:
		startBusiness( (SCMD2B9*)data );
		break;
	case END_BUSINESS:
		endBusiness( (SCMD2BB*)data );
		break;
		//				case UPDATE_HISTORY_LIST:
		//					break;
		//				case UPDATE_GOODS_LIST:
		//					break;
		//				case UPDATE_EVENT_LIST:
		//					break;
		//				case UPDATE_BANK_LIST:
		//					break;
	}
}

TraderProxyCommand::~TraderProxyCommand()
{

}

void TraderProxyCommand::updateEventList(SCMD2B1* param){

	std::list<TraderEventVo*>::iterator it = _traderProxy->_eventList.begin();
	for ( ; it != _traderProxy->_eventList.end(); it++ )
	{
		TraderEventVo* vo = *it;
		CC_SAFE_DELETE( vo );
	}
	_traderProxy->_eventList.clear();


	TraderEventVo* event1 = new TraderEventVo(); 
	event1->isActive = param->a_event1isFound;
	event1->eventArr.push_back(param->b_event1Item1);
	event1->eventArr.push_back(param->c_event1Item2);
	event1->eventName = param->d_event1Name;
	TraderEventVo* event2 = new TraderEventVo;
	event2->isActive = param->e_event2isFound;
	event2->eventArr.push_back(param->f_event2Item1);
	event2->eventArr.push_back(param->g_event2Item2);
	event2->eventArr.push_back(param->h_event2Item3);
	event2->eventName = param->i_event2Name;			
	TraderEventVo* event3 = new TraderEventVo;
	event3->isActive = param->j_event3isFound;
	event3->eventArr.push_back(param->k_event3Item1);
	event3->eventArr.push_back(param->l_event3Item2);
	event3->eventArr.push_back(param->m_event3Item3);
	event3->eventArr.push_back(param->n_event3Item4);
	event3->eventName = param->o_event3Name;
	_traderProxy->_eventList.push_back(event1);
	_traderProxy->_eventList.push_back(event2);
	_traderProxy->_eventList.push_back(event3);

	sendNotification(Facade_Mediator,
		AppFacade_CITY_TRADER_CHANGE, (char*)param, CityTraderMediator::UPDATE_EVENT_LIST);
	//this.sendNotification(CityTraderMediator.UPDATE_EVENT_LIST);
}

void TraderProxyCommand::updateHistoryList(SCMD2B4* param){
	_traderProxy->_historyList.clear();

	_traderProxy->_historyList.push_back(param->a_historyItem1);
	_traderProxy->_historyList.push_back(param->b_historyItem2);
	_traderProxy->_historyList.push_back(param->c_historyItem3);
	_traderProxy->_historyList.push_back(param->d_historyItem4);
	_traderProxy->_historyList.push_back(param->e_historyItem5);

	sendNotification(Facade_Mediator,
		AppFacade_CITY_TRADER_CHANGE, (char*)param, CityTraderMediator::UPDATE_HISTORY_LIST);
}

void TraderProxyCommand::updateBankList(SCMD2B3* param){

	std::list<BankGridVo*>::iterator itEvent = _traderProxy->_bankList.begin();
	for ( ; itEvent != _traderProxy->_bankList.end(); itEvent++ )
	{
		BankGridVo* vo = *itEvent;
		CC_SAFE_DELETE( vo );
	}
	_traderProxy->_bankList.clear();

	std::list<SCMD2B3::SCMD2B3Node>::iterator it = param->c_bankArr.begin();
	for( ; it != param->c_bankArr.end(); it++ ){
		SCMD2B3::SCMD2B3Node node = *it;
		BankGridVo* vo = new BankGridVo;
		vo->isActive  = node.a_isActive;
		vo->goodsId   = node.b_ItemId;
		_traderProxy->_bankList.push_back(vo);
	}
	_traderProxy->_buyNum = param->a_buyNum;

	sendNotification(Facade_Mediator,
		AppFacade_CITY_TRADER_CHANGE, (char*)param, CityTraderMediator::UPDATE_BANK_LIST);
}

void TraderProxyCommand::updateItemList(SCMD2B2* param){
	_traderProxy->_itemList.clear();

	_traderProxy->_itemList.push_back(param->a_item1);
	_traderProxy->_refreshCnt = param->b_refreshTimes;

	_traderProxy->_beatedCnt = param->c_beated;

	_traderProxy->_buyTokenCnt = param->d_buyTokenCnt;
	_traderProxy->_robedSilver = param->e_robSilver;
	_traderProxy->_robedPop = param->e_robPop;
	_traderProxy->_currentMapId = param->f_mapId;
	
	sendNotification(Facade_Mediator,
		AppFacade_CITY_TRADER_CHANGE, (char*)param, CityTraderMediator::UPDATE_GOODS_LIST);

}


void TraderProxyCommand::updateCityPrice(SCMD2B6* param){
	if (g_pGlobalManage->_isOnBusiness)
	{
		return;
	}
	std::list<CityPriceVo*>::iterator itEvent = _traderProxy->_cityPriceList.begin();
	for ( ; itEvent != _traderProxy->_cityPriceList.end(); itEvent++ )
	{
		CityPriceVo* vo = *itEvent;
		CC_SAFE_DELETE( vo );
	}
	_traderProxy->selectedVo = 0;
	_traderProxy->_cityPriceList.clear();

	SceneProxy* _sceneProxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
	std::list<SCMD2B6::SCMD2B6Node>::iterator it = param->a_cityPriceArr.begin(); 
	for( ; it != param->a_cityPriceArr.end(); it++ )
	{
		SCMD2B6::SCMD2B6Node node = *it;
		if(_sceneProxy->isSceneOpened(node.a_mapId))
		{
			CityPriceVo* vo = new CityPriceVo;
			vo->cityName = SceneManager::Instance()->getSceneDic(node.a_mapId)->name;
			vo->mapId = node.a_mapId;
			vo->cityPrice = node.b_price;
			vo->npcId = node.c_npcId;
			_traderProxy->_cityPriceList.push_back(vo);
		}
	}

	sendNotification(Facade_Mediator,
		AppFacade_CITY_TRADER_CHANGE, (char*)param, CityTraderMediator::UPDATE_CITY_PRICE_LIST);
}

/**开始跑商*/
void TraderProxyCommand::startBusiness(SCMD2B9* cmd){
	if(cmd->a_err > 0) {
		errorCodeTip(cmd->a_err);
		return;
	}
	if (!_traderProxy->selectedVo)
	{
		LangManager::msgShow("System error!");
		return;
	}
	FindVo findVo;
	findVo._type=1;
	findVo._sceneId = _traderProxy->selectedVo->mapId;
	findVo._npcId = _traderProxy->selectedVo->npcId;
	g_pGlobalManage->_isOnBusiness = true;

	sendNotification(Facade_Mediator,
		AppFacade_CITY_TRADER_CHANGE, (char*)&findVo, CityTraderMediator::START_RUNNING_BUSINESS);
	//GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::FIND_ELEMENT, (void*)&findVo );
	//GameDispatcher.getInstance().dispatchEvent(new ParamEvent(GameDispatcher.FIND_ELEMENT, findVo));
}

/**结束跑商*/
void TraderProxyCommand::endBusiness(SCMD2BB* cmd){
	if(cmd->a_err > 0){
		errorCodeTip(cmd->a_err);
		return;
	}
	string bj = "";
	switch(cmd->c_bj){
	case 1:
		//LangManager::msgStr( LangManager::getText("TRD031") );
		bj = LangManager::getText("TRD031");
		break;
	case 2:
		//LangManager::msgStr( LangManager::getText("TRD032") );
		bj = LangManager::getText("TRD032");
		break;
	}
	//Alert.show(LangManager::getText("TRD033")+"，" + bj + LangManager::getText("TRD034",cmd->b_silver));
	bj += LangManager::getText("TRD034",cmd->b_silver, cmd->d_pop);
	LangManager::msgStr(bj.c_str(), ccc3(0,255,0), 6);
	g_pGlobalManage->_isOnBusiness = false;

	if (cmd->e_doubleTime==1)
	{
		//LangManager::msgShow("TRD062", ccc3(0,255,0), 6);
		bj += LangManager::getText("TRD062");
	}

	if (LayerManager::windowLayer)
	{
		Confirm * _confirmBuy = new Confirm();
		_confirmBuy->initWithParam(
			bj.c_str(),
			LayerManager::windowLayer,
			menu_selector(WindowLayer::clickCancel),
			menu_selector(WindowLayer::clickCancel));
		if (LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame))
		{
			LayerManager::windowLayer->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
		}
		LayerManager::windowLayer->addChild(_confirmBuy,
			WindowLayer::WindowLayerZ_confirmFrame,WindowLayer::WindowLayerTAG_confirmFrame);
		_confirmBuy->release();
	}

	if( ViewManager::getInstance()->scene() ){ 
		ViewManager::getInstance()->scene()->roleReDress();
	}
}

/**跑商错误码处理*/
void TraderProxyCommand::errorCodeTip(int err){
	switch(err){
	case 301:
		LangManager::msgShow("TRD035");
		break;
	case 302:
		LangManager::msgShow("TRD036");
		break;
	case 303:
		LangManager::msgShow("TRD037");
		break;
	case 304:
		LangManager::msgShow("TRD038");
		break;
	case 305:
		LangManager::msgShow("TRD039");
		break;
	}
}

std::vector<CCPoint> TraderProxyCommand::loadMapData(char* fileName, CCPoint startPoint, CCPoint endPoint)
{
	std::vector<CCPoint> retPath;

    const char* filePath = CCFileUtils::fullPathFromRelativePath(fileName);
	if (!filePath)
		return retPath;

	TiXmlDocument xmlDoc(filePath); 
	bool sus = xmlDoc.LoadFile();
	if (!sus)
		return retPath;

	TiXmlElement* pRootElement = xmlDoc.RootElement();
	if(!pRootElement)  
		return retPath;  

	TiXmlNode* pNode = NULL;
	TiXmlElement* pEle = NULL;
	pNode = pRootElement->FirstChildElement();
	if(!pNode)
		return retPath;

	string sceneName = "";
	int width=0, height=0,blockW=0,blockH=0,offX=0,offY=0;
	int t = pNode->Type();
	if(t == TiXmlText::TINYXML_ELEMENT)
	{
		pEle = pNode->ToElement();
		TinyElementHandler elehandler(pEle);
		elehandler.get(sceneName);
		elehandler.get(width);
		elehandler.get(height);
		elehandler.get(blockW);
		elehandler.get(blockH);
		elehandler.get(offX);
		elehandler.get(offY);
	}

	if(pNode)
		pNode = pNode->NextSiblingElement();
	if(pNode)
		pNode = pNode->NextSiblingElement();

	const char *pt = NULL;
	if(pNode && pNode->FirstChild())
		pt = pNode->FirstChild()->Value();


	int cols = ceil(((float)(POSX(width))) / (float)(TileUtil::Instance()->getTileWidth()));
	int rows = ceil(((float)(POSX(height))) / (float)(TileUtil::Instance()->getTileHeight()));

	char mapData[MAX_CELLS_X][MAX_CELLS_Y];
	for(int i = 0; i< MAX_CELLS_Y; ++i)
	{
		for(int j = 0; j< MAX_CELLS_X; ++j)
		{
			mapData[i][j] = 1;
		}
	}
	for(int y = 0; y < rows; ++y)
		for(int x = 0; x < cols; ++x)
		{
			if(pt)
				mapData[y][x] = *((char*)pt + y * cols + x) - 48;
		}

	FindPath8 _findPath8 = FindPath8((char**)mapData, MAX_CELLS_Y, MAX_CELLS_X);


	point ps;
	point pe;
	ps.x = startPoint.x;
	ps.y = startPoint.y;
	pe.x = endPoint.x;
	pe.y = endPoint.y;
	if(startPoint.x < 0 || startPoint.y < 0 || endPoint.x < 0 || endPoint.y < 0)
		return retPath;

	std::vector<point> path;
	std::vector<point> opt_path;
	_findPath8.find(ps, pe, path);
	_findPath8.optimizePath(opt_path);


	std::vector<point>::iterator iter = opt_path.begin();
	for(; iter != opt_path.end(); ++iter)
	{
		retPath.push_back(ccp(float(iter->x), float(iter->y)));
		//CCLog("path :(%d, %d)", iter->x, iter->y);
	}
	return retPath;
}