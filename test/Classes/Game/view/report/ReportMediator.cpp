#include "ReportMediator.h"
#include "control/AppFacade.h"
#include "manager/LayerManager.h"
#include "utils/ScaleUtil.h"
#include "components/PassGiftSkin.h"
#include "components/ReportView.h"
#include "model/honor/vo/HonorManage.h"
#include "model/honor/vo/HonorScheduleManage.h"
#include "model/honor/HonorProxy.h"
#include "model/scene/SceneProxy.h"
#include "model/scene/vo/SceneType.h"
#include "model/scene/SceneManager.h"
#include "manager/LangManager.h"
#include "manager/ViewManager.h"
#include "manager/PopManage.h"
#include "socket/command/c12/CCMD128.h"
#include "socket/command/c13/CCMD136.h"
#include "socket/command/c13/CCMD134.h"
#include "model/scene/MonsterManager.h"
#include "manager/LayerManager.h"
#include "manager/GlobalManage.h"

ReportMediator* g_pReportMediator = 0;

ReportMediator::ReportMediator()
{
	_arward = 0;
	_passGift = 0;
    

	//Begin chenjian 20121012
	_reportView = 0;
	GameDispatcher* _dispatcher = GameDispatcher::getInstance();
	_dispatcher->addEventListener(PopEventName::SHOW_UI_REPORT, this, callfuncND_selector(ReportMediator::loadReportSource));
	_dispatcher->addEventListener(GameDispatcher::SELECT_REPORT, this, callfuncND_selector(ReportMediator::onSelectReport));
	_dispatcher->addEventListener(GameDispatcher::APPLY_REPORT_LIST, this, callfuncND_selector(ReportMediator::onApplyReportList));
	//End chenjian 20121012
}


void ReportMediator::handleNotification(int M2Vcmd, char* data)
{   
	_fightProxy = (FightProxy*)g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
	switch(M2Vcmd)
	{
	case PLAY_REPORT:
		//_socket.sendMessage(SocketCMDConst.CMSG_WORLD_BATTLE_REPORT_REQUEST,int(note.getBody()));
		break;
	case TAKE_AWRAD:	
		takeAward( (int)data );
		break;
	case INIT_PROGRESS:
		//resetLayerStar(note.getBody() as int);
		break;
	}
}

void ReportMediator::openAward( int awardId )
{
	if( !_arward )
	{
		_arward = new MapAwardPanel();
		if ( !_arward->init() )	return;
	}
	//if ( _arward->getisPop() )
	//{
	//	_arward->setisPop( false );
	//}
	//else
	//{
	//	_arward->setisPop( true );
	//	//_arward.addEventListener(PopContainer.CLOSE_CONTAINER,closeAwardPanel);
	//	//var honorGoodsVo:HonorGoodVo = HonorManage.getInstance().getHonorGoodsVo(awardId);
	//	//if(honorGoodsVo)
	//	//{
	//	//	_arward.init(honorGoodsVo);
	//	//}
	//}

	CCSize cs = CCDirector::sharedDirector()->getWinSize();
	//if ( _passGift )
	//{
	//	_passGift->setIsVisible(true);
	//} 
	//else
	{
		_passGift = PassGiftSkin::passGiftSkinWithRect( 
			CCRectMake( cs.width/2-POSX(220/2), cs.height/2-POSX(260/2), POSX(220), POSX(260) )
			);
		if ( LayerManager::sceneUILayer && _passGift )
		{
			_passGift->initPassGiftSkin( awardId );
			LayerManager::sceneUILayer->addChild( _passGift );
			_passGift->release();
		}

	}
}


void ReportMediator::openAwardWithoutGift()
{
	if( !_arward )
	{
		_arward = new MapAwardPanel();
		if ( !_arward->init() )	return;
	}

	//通关奖励按钮
	int awardId = -1;
	SceneProxy* _sceneProxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
	//int pid = _sceneProxy->pid();
	//std::vector<int>* pArr = SceneManager::Instance()->getChildByPid(pid);
	HonorGoodVo* vo = HonorScheduleManage::Instance()->getAwardByMap(_sceneProxy->sceneInfoVo()->id);
	if( vo && ( vo->goods.size()>0 )
		)
	{
		HonorProxy* _honorProxy = (HonorProxy*)g_pFacade->retrieveProxy(AppFacade_HONOR_PROXY_CHANGE);
		map<int, HonorObject*>::iterator it = _honorProxy->_honorList.find(vo->honorsid);
		if ( it != _honorProxy->_honorList.end() )
		{
			HonorObject* obj = it->second;
			if (obj->award == 0)
			{
				awardId = vo->honorsid;
			}
		}
	}
		
	HonorGoodVo* honorGoodsVo = HonorManage::Instance()->getHonorGoodsVo(awardId);
	if ( honorGoodsVo )
	{
		g_pReportMediator->_arward->init( honorGoodsVo );
	}
}

/**
* 成就奖励
* */
void ReportMediator::updateHonorAwardComplete( int honorId )
{
	//var vo:HonorGoodVo = HonorManage.getInstance().getHonorGoodsVo(honorId);
	//if(_honorView!=null && _honorView.isPop && vo.map==0){
	//	_honorView.updateHonorComplete(honorId);
	//	if(vo.goods.length >= 1 && (vo.goods)[0] > 99)
	//		LangManager.msgShow("HOR001");
	//}
	//else if(vo.map!=0){
	//	this.sendNotification(ReportMediator.TAKE_AWRAD, honorId);
	//}

}

void ReportMediator::takeAward( int awardId )
{
	////Message.show("成功领取通关奖励");
	//if(_reportView && _reportView.isPop){
	//	_reportView.clearAwardButton(awardId);
	//}
	//if(_arward && _arward.isPop){
		_arward->tookItem( awardId );
	//}
}



//Begin chenjian 20121012
void ReportMediator::loadReportSource(CCNode *pNode, void *pData)
{
	showReportView();
}

void ReportMediator::showReportView()
{
	if (_sceneProxy->sceneInfoVo()->type != SceneType::STORY)
	{
		return;
	}

	CC_SAFE_RELEASE_NULL(_reportView);

    if (! _reportView)
    {
        _reportView = new ReportView();
		if (! _reportView->init())
			return;
        ViewManager::getInstance()->reportView = _reportView;
    }
	_reportView->setisPop(! _reportView->getisPop());

	this->updateReportData();

	//SceneProxy* sceneProxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
	//int mapId = sceneProxy->sceneInfoVo()->id;

	//this->sendApplyReportData(mapId);

	this->initLayerTitleStar();
}



void ReportMediator::updateReportData()
{
	if (! _reportView || ! _reportView->getisPop())
    {
		return;
	}

	int watchMapId = _sceneProxy->sceneInfoVo()->id;

	SceneVo* pSceneVo = SceneManager::Instance()->getSceneDic(watchMapId);
	if (pSceneVo->type != SceneType::STORY)
	{
		return;
	}
	//add map data
	ReportVo& vo = _reportView->datas;
	vo.monsters.clear();
	vo.mapId = watchMapId;
	vo.mapName = pSceneVo->name;

	

	//add monster datas by map id.
	std::list<GMProgressVo*> arr = MonsterManager::Instance()->getGroupMonsterByMapId(watchMapId);
	std::list<GMProgressVo*>::iterator it = arr.begin();
	while (it != arr.end())
	{
		ReportMonsterVo mvo;
		mvo.mgId = (*it)->mgId;
		mvo.id = (*it)->id;
		NPCVo* monsterGroup = MonsterManager::Instance()->getMonsterGroup(mvo.mgId);

		if (monsterGroup)
		{
			mvo.name = monsterGroup->name;

			vo.monsters.push_back(mvo);
		}
		++it;
	}

	//update report view
	if (! arr.empty())
	{
		_reportView->setCurrentPage(0);
		_reportView->updateView();
	}

}

//update report list
void ReportMediator::sockReportList(SCMD137* pPacket)
{
	if (! _reportView || ! _reportView->getisPop())
	{
		return;
	}

	std::vector<ReportHeadVo> lst;

	int32 flag = 0;
	std::vector<SCMD137::SCMD137Node>::iterator it = (pPacket->b_SCMD137Node).begin();
	while (it != (pPacket->b_SCMD137Node).end())
	{
		ReportHeadVo vo;
		vo.battleId1 = it->a_battleId1;
		vo.battleId2 = it->b_battleId2;
		vo.acount = it->c_acountId;
		vo.lev = it->d_lev;
		vo.name = it->e_playerName;
		vo.groupId = pPacket->a_groupId;
		if(flag < 3)
		{
			vo.type = flag;
		}
		lst.push_back(vo);

		if(flag > 6)
			break;
		++it;
		++flag;
	}

	_reportView->updateReportList(lst);
}

void ReportMediator::onSelectReport(CCNode *pNode, void *pData)
{
	if (! pData)
		return;
	if(g_pGlobalManage && (g_pGlobalManage->isReport) || (g_pGlobalManage->getisInFight()))
	{
		LangManager::msgShow("RPO040");
		//延迟5秒再响应
		CCDelayTime* pWaitAction = CCDelayTime::actionWithDuration(5.0);
		CCCallFunc *pWaitActionDo = CCCallFunc::actionWithTarget(this, callfunc_selector(ReportMediator::reportWaitTime));
		CCAction *pAction = cocos2d::CCSequence::actions(pWaitAction, pWaitActionDo, 0);
		this->runAction(pAction);
		return;
	}

	g_pGlobalManage->isReport = true;

	ReportHeadVo vo = *((ReportHeadVo*)pData);
	CCMD134 cmd;
	cmd.a_battleId1 = vo.battleId1;
	cmd.b_battleId2 = vo.battleId2;
	GameServerSocket::getInstance()->sendMessage(&cmd);
}

void ReportMediator::onApplyReportList(CCNode *pNode, void *pData)
{
	int monsterId = *((int*)pData);
	CCMD136 cmd;
	cmd.a_monsterId = monsterId;
	GameServerSocket::getInstance()->sendMessage(&cmd);
}


void ReportMediator::sendApplyReportData(const int16& mapId)
{
    CCMD128 cmd;
	cmd.a_mapID = mapId;
	GameServerSocket::getInstance()->sendMessage(&cmd);
}


void ReportMediator::initLayerTitleStar()
{
}

void ReportMediator::reportWaitTime()
{
    if (g_pGlobalManage)
		g_pGlobalManage->isReport = false;
}
//End chenjian 20121012
