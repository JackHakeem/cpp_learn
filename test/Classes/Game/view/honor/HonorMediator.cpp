#include "HonorMediator.h"
#include "control/AppFacade.h"
#include "../report/ReportMediator.h"
#include "socket/command/c14/CCMD143.h"
#include "socket/network/GameServerSocket.h"
#include "bear/manager/DisplayObjectManager.h"
#include "model/honor/vo/HonorManage.h"
#include "../fight/callback/HonorAchieveAction.h"
#include "model/backpack/BagProxy.h"
#include "mvc/Facade.h"
#include "manager/LangManager.h"
#include "manager/GlobalManage.h"
#include "model/honor/HonorProxy.h"
#include "model/scene/vo/SceneType.h"
#include "manager/ViewManager.h"

HonorMediator* g_pHonorMediator = 0;

void HonorMediator::handleNotification(int M2Vcmd, char* data)
{   
	_fightProxy = (FightProxy*)g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
	switch(M2Vcmd)
	{
	//case HONONR_POP:
	//	honorPop();
	//	break;
	//case HONONR_CREAT_LIST:
	//	creatHonorList();
	//	break;
	//case HONONR_COMPLETED:
	//	updateHonorReach(note.getBody() as int);
	//	break;
	//case HONONR_TITLEUPDATE:
	//	updateHonorName();
	//	break;
	//case HONONR_POINTAWARDUPDATE:
	//	updateHonorPointAwardComplete(note.getBody() as int);
	//	break;
	case HONONR_HONORAWARDUPDATE:
		updateHonorAwardComplete( (int)data );
		break;
		//				case FIGHT_FIRST:
		//					fighthandler();
		//					break;
		//				case FIGHT_ENDS:
		//					fightEndHandler();
		//					break;
	}
}

/**
* one honor achieve
* */
void HonorMediator::updateHonorReach( int honorId )
{
	HonorGoodVo* _honorGoodsVo = HonorManage::Instance()->getHonorGoodsVo(honorId);
	if(!_honorGoodsVo)
		return;
//	if(_honorView!=null){
//		_honorView.setTopBaseData(_honorProxy.HonorNameID,_honorProxy.TotalPiont);
//
//		if(_honorGoodsVo!=null&&_honorGoodsVo.map==0){
//			_honorView.updatehonorList(honorId,_honorGoodsVo.bigtype,_honorGoodsVo.type);
//		}
//
//	}
	//set map pass through state
	if ( _honorGoodsVo->m_map > 0 )
	{
		_sceneProxy->setSceneThrough( _honorGoodsVo->m_map );
	}
	//if( _fightProxy->battleId != 0 )
	{ 
		//  when battleId != 0 then save honor to fightProxy 
		HonorAchieveAction* pHonorAchieveAction = new HonorAchieveAction( honorId, 0, 0 );
		_fightProxy->_bData._callbacks.push_back( pHonorAchieveAction );
		//_fightProxy->_bData._callbacks.push(new HonorAchieveAction(honorId, _honorProxy.LastTotalPoint, _honorProxy.TotalPiont));

	}
	//else
	//{			
	//	//DisplayObjectManager.playHonorEfc(honorId, _honorProxy.LastTotalPoint, _honorProxy.TotalPiont);
	//	DisplayObjectManager::getInstance()->loadPassGiftSkin( honorId );
	//}
}

/**
* 成就达成
* */
void HonorMediator::socketHonorHasReach( SCMD140* param )
{
	//sendNotification(AppFacade.HONOR_PROXY_CHANGE, param, HonorProxyCommand.UPDATE_S_LIST);
	updateHonorReach( param->a_honorid );
}

/**
* 成就奖励
* */
void HonorMediator::updateHonorAwardComplete( int honorId )
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
	g_pReportMediator->takeAward( honorId );
}

/**
* 领取成就奖励
* */
void HonorMediator::socketHonorhasGetItem( SCMD144* param )
{
	//sendNotification(AppFacade.HONOR_PROXY_CHANGE, param, HonorProxyCommand.UPDATE_S_HONORAWARD);
	updateHonorAwardComplete( param->a_honorid );
}

void HonorMediator::honorChangeClickHandler( int awardId )
{
	HonorGoodVo* _honorGoodsVo = HonorManage::Instance()->getHonorGoodsVo(awardId);
	if(_honorGoodsVo)
	{
		BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy( AppFacade_BAG_PROXY_CHANGE );
		for ( int i = 0; i < _honorGoodsVo->goods.size(); i++ )
		{
			if ( _honorGoodsVo->goods[i].type > 99 )//weapon
			{
				if ( _bagProxy->getSpaceGridNum()<=0 )
				{
					//LangManager::msgShow("HOR002");//bag full

					//g_pGlobalManage->setIsShowAllUILock(false);
					//g_pGlobalManage->showAllUI(true);

					HonorObject* obj = new HonorObject;
					obj->id = awardId;
					obj->award = 0;
					HonorProxy* _honorProxy = (HonorProxy*)g_pFacade->retrieveProxy(AppFacade_HONOR_PROXY_CHANGE);
					if (_honorProxy->_honorList.find(awardId)==_honorProxy->_honorList.end())
					{
						_honorProxy->_honorList.insert( make_pair( awardId, obj ) );
						HonorScheduleManage::Instance()->updateScheduleData(obj);
					}
					else
					{
						CC_SAFE_DELETE(obj);
					}
					if (g_pReportMediator->_arward)
					{
						g_pReportMediator->_arward->EnableButtonX(true);
						g_pReportMediator->_arward->showBagSeclet();
					}
					return;
				}
			}
		}
	}
	if (g_pReportMediator->_arward)
		g_pReportMediator->_arward->EnableButtonX(false);

	//switch (e.param.UseType)
	//{
	//case 1:
	//	var ahonorId:int = int(e.param.id);
	//	var honorsGooodVo:HonorGoodVo = HonorManage.getInstance().getHonorGoodsVo(ahonorId);
	//	if(honorsGooodVo.goods.length >= 1 && (honorsGooodVo.goods)[0] > 99){
	//		if(_bagProxy.getFirstSpaceGrid() == -1){
	//			LangManager.msgShow("HOR002");
	//			return;
	//		}  //提示包裹没有空余位置
	//	}
	CCMD143 honorAwardSender;
	honorAwardSender.a_honorid = awardId;
	GameServerSocket::getInstance()->sendMessage( &honorAwardSender );	//CMSG_GET_ACHIVEMENT_AWARD
	//	break;
	//case 2:
	//	//更换使用成就名称
	//	var honorId:int = int(e.param.id);
	//	var aNameSender:CCMD149 = new CCMD149();
	//	aNameSender.a_id = new Int16(honorId);
	//	_socket.sendMessage(SocketCMDConst.CMSG_CHANGE_ACHIEVEMENT_TITLE,aNameSender); 
	//	break;
	//case 3:
	//	var honorawardVo:HonorAwardVo = HonorManage.getInstance().getPointInfo(e.param.id);
	//	if(honorawardVo == null) return;
	//	if(honorawardVo.goods != 0){
	//		if(_bagProxy.getFirstSpaceGrid() == -1){
	//			LangManager.msgShow("HOR002");
	//			return;
	//		}  //提示包裹没有空余位置
	//	}
	//	if(honorawardVo.awardY > 0){
	//		var accountInfo:AccountInfoVo = RoleManage.getInstance().accountInfo;
	//		if((honorawardVo.awardY + accountInfo.silver) > accountInfo.silverLim){
	//			LangManager.msgShow("HOR003");
	//			return;
	//		}
	//	}
	//	var pointID:int = int(e.param.id);
	//	var aWardSender:CCMD145 = new CCMD145();
	//	aWardSender.a_pointid = new Int16(pointID);
	//	_socket.sendMessage(SocketCMDConst.CMSG_GET_POINT_AWARD,aWardSender); 
	//	break;
	//}
}

void HonorMediator::socketHasReachHonorList( SCMD142* pPacket )
{
	HonorProxy* _honorProxy = (HonorProxy*)g_pFacade->retrieveProxy(AppFacade_HONOR_PROXY_CHANGE);
	if (_honorProxy)
	{
		_honorProxy->createList(pPacket);
	}
	//sendNotification(AppFacade.HONOR_PROXY_CHANGE, param, HonorProxyCommand.CREATE_S_LIST);
	if(_sceneProxy->sceneInfoVo()->type == SceneType::STORY) 
	{
		HonorGoodVo* vo = HonorScheduleManage::Instance()->getAwardByMap(_sceneProxy->sceneInfoVo()->id);
		if (ViewManager::getInstance()->_secNavigate && vo)
		{
			HonorProxy* _honorProxy = (HonorProxy*)g_pFacade->retrieveProxy(AppFacade_HONOR_PROXY_CHANGE);
			map<int, HonorObject*>::iterator it = _honorProxy->_honorList.find(vo->honorsid);
			if ( it != _honorProxy->_honorList.end() )
			{
				HonorObject* obj = it->second;
				if (obj->award == 0)
				{
					ViewManager::getInstance()->_secNavigate->addButtonAward();
				}
			}
		}
	}
}
