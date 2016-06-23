#include "view/figure/FigureMediator.h"
#include "model/skill/vo/SkillType.h"
#include "manager/ViewManager.h"
#include "manager/LayerManager.h"
#include "control/figure/FigureCommand.h"
#include "socket/command/s30/SCMD30E.h"
#include "socket/command/s31/SCMD31D.h"
#include "socket/command/s31/SCMD31F.h"
#include "socket/command/s30/SCMD30C.h"
#include "socket/command/s35/SCMD350.h"
#include "socket/command/s35/SCMD35E.h"
#include "model/player/RoleManage.h"
#include "components/SkillView.h"
#include "Message.h"
#include "manager/GlobalManage.h"
#include "socket/command/c17/CCMD170.h"
#include "socket/command/c17/CCMD171.h"
#include "utils/ValuesUtil.h"
#include "socket/command/c31/CCMD31C.h"
#include "socket/command/c31/CCMD31E.h"
#include "socket/command/c30/CCMD30B.h"
#include "socket/command/s29/SCMD295.h"
#include "manager/sound/SoundManager.h"
#include "socket/command/c31/CCMD317.h"
#include "../fight/callback/FightFollowLevelUpAction.h"
#include "model/player/vo/PlayerAniType.h"
#include "socket/command/c29/CCMD294.h"
#include "manager/PopEventName.h"
#include "socket/command/s2a/SCMD2A1.h"
#include "socket/command/s2a/SCMD2A7.h"
#include "socket/command/c2a/CCMD2A0.h"
#include "socket/command/c2a/CCMD2A6.h"
#include "socket/command/c2a/CCMD2A4.h"
#include "socket/command/c2a/CCMD2A2.h"
#include "model/newhand/NewhandManager.h"
#include "components/FigureMainView.h"
#include "socket/command/s18/SCMD185.h"
#include "../notify/NotifyManager.h"
#include "../notify/NotifyType.h"
#include "../newhand/components/LeaderAlert.h"
#include "../scene/components/story/callback/StoryFollowTipsAction.h"
#include "socket/command/s16/SCMD16D.h"
#include "../backpack/BagMediator.h"
#include "../fight/callback/SpecialItemAddAction.h"
#include "../fight/callback/ShowNewHandHelpAction.h"
#include "../newhand/components/NewHandHelpView.h"
#include "../fight/callback/ShowAttrChangeAction.h"

FigureMediator::FigureMediator()
{
	_figureMainView = NULL;

	GameDispatcher::getInstance()->addEventListener( PopEventName::SHOW_UI_FIGURE,
		this, callfuncND_selector(FigureMediator::openFigure) );
}

void FigureMediator::handleNotification(int M2Vcmd, char* data)
{
	switch(M2Vcmd)
	{
	case UPDATE_EQUIP_INFO:
		showEquipInfo();
		break;
	case EQUIP_UPDATE:	//Updated a equipment
		updateEquip(data);
		break;
	case PUT_ON_EQUIP://The news sent by the backpack: put on equipment
		{
			int typeId = ((int*)data)[0];
			int sitGrid = ((int*)data)[1];
			putOnEquipment(typeId, sitGrid);
			break;
		}
	case EQUIPMENT_ITEM_TIP_UPDATE:
		updateTip(data);
		break;
	case FIGURE_SKILL_CHANGE:
		//_mainView.figureView.changeSkill(note.getBody().figure, note.getBody().rank, note.getBody().info);
		break;
	case SKILL_ITEM_TIP_UPDATE:
		updateSkillTip(data);
		break;
	case EXCHANGE_SKILL:
		{
			int rank = ((int*)data)[0];
			if(rank == SkillType::PASSVIE)
			{
				if (!g_pFigureScrollView)
				{
					return;
				}
				g_pFigureScrollView->showSkillInfo();
				//_passiveView.exchangeSkill(note.getBody().eqId, note.getBody().offId);
			}
			else if (rank == SkillType::SKILL)
			{
				//_offensiveView.exchange(note.getBody().eqId, note.getBody().offId);
				if (g_pFigureScrollView)
				{
					g_pFigureScrollView->showSkillInfo();
				}
			}
			break;
		}
	case REFRESH_WASH_VALUE:
		updateWashView(data);
		break;
	case SAVE_WASH_VALUE://Save the attribute values: character panel, wash properties are updated
		{
			if(_figureMainView && _figureMainView->_figureV)
			{
				struct cmd
				{
					int figure;
					WashVo* washVo;
					cmd()
					{
						figure = 0;
						washVo = NULL;
					}
				};

				cmd* cmd1 = (cmd*)(data);
				//_figureMainView->_washView->saveNewValue(note.getBody().id, note.getBody().vo);
				_figureMainView->_figureV->updateFigureInfo(cmd1->figure, cmd1->washVo);
				updateAttributeView(data);
				//_figureMainView->_figureV->_attrLayer->loadItems();
			}
			PeiyangView * pv = ViewManager::getInstance()->_peiyangView;
			if (!pv)
			{
				return;
			}
			pv->loadItems(false);
			break;
		}
	}
}

void FigureMediator::showEquipInfo()
{
	/*
	if (!_figureMainView)
	{
		_figureMainView = new FigureMainView();
		ViewManager::getInstance()->figureView = _figureMainView;
	} // ADD BY LH
	*/
	
// 	if(_figureMainView/* && _figureMainView->getType() == 1*/
// 		&& _figureMainView->_figureV)
// 	{
// 		_figureMainView->_figureV->showEquipInfo();
// 	}
}

void FigureMediator::updateEquip(char* data)
{
	SCMD172* scmd172 = (SCMD172*)data;

	//if(_figureMainView && _figureMainView->getType()== 1 && RoleManage::Instance()->currentId() == scmd172->a_figureId)
	//{
	_figureMainView = ViewManager::getInstance()->figureView;
	if (!_figureMainView)
	{
		return;
	}
	_figureMainView->_figureV->updateEquipInfo(scmd172->a_figureId, scmd172->b_sitGrid);

	//}


}

void FigureMediator::putOnEquipment(int typeId, int sitGrid)
{

}

void FigureMediator::updateTip(char* data)
{

}

void FigureMediator::updateSkillTip(char* data)
{

}

void FigureMediator::updateWashView(char* data)
{
	struct cmd
	{
		int figure;
		WashVo* washVo;
		cmd()
		{
			figure = 0;
			washVo = NULL;
		}
	};
	cmd* cmd1 = (cmd*)(data);
	PlayerInfoVo * pi = RoleManage::Instance()->getMercenary(cmd1->figure);
	if (!pi)
	{
		return;
	}
	if ((!ViewManager::getInstance()->figureView)||(!ViewManager::getInstance()->figureView->_figureV))
	{
		return;
	}
	int i = 0;
	for (i = 0;i<MAX_ROLE_NUM;i++)
	{
		if (ViewManager::getInstance()->figureView->_figureV->RoleID[i] == pi->figureBaseInfo.mercId)
		{
			break;
		}
	}
	if (ViewManager::getInstance()->_peiyangView)
	{
		memcpy((void *)&ViewManager::getInstance()->_peiyangView->_cache[i],(void *)cmd1,sizeof(struct cmd));
		ViewManager::getInstance()->_peiyangView->showWashResult();
	}
}

void FigureMediator::updateAttributeView(char * data)
{
	if ((!ViewManager::getInstance()->figureView)||(!ViewManager::getInstance()->figureView->_figureV)||(!ViewManager::getInstance()->figureView->_figureV->_attrLayer))
	{
		return;
	}
	ViewManager::getInstance()->figureView->_figureV->_attrLayer->loadItems();
}

void FigureMediator::openFigureView()
{
	if(!_figureMainView)
	{
		_figureMainView = new FigureMainView();
		ViewManager::getInstance()->figureView = _figureMainView;
		//_figureMainView->init(); // closed by lh 0411

	}

	g_pGlobalManage->setCurFocusGID(LayerManager::windowLayer->getMyFocusGID());
	openView();
}

void FigureMediator::openFigure( CCNode *pNode, void *data )
{
	//openView();
	openFigureView();
}

void FigureMediator::openView()
{	
	if (!_figureMainView)
	{
		return;
	}
	
	_figureMainView->setisPop(!_figureMainView->getisPop());
	
	if (!_figureMainView)
	{
		return;
	}
	

	//LH 20120105
	if (_figureMainView->retainCount() > 2)
	{
		_figureMainView->release();
	}
	
	//sendMercIdentifyInfoRequest();
	//sendIdentifyRequest(700000806 , 0);
	if (_figureMainView->_figureV)
	{
		_figureMainView->_figureV->_statPanel = FigureView::STAT_ROLE;

		_figureMainView->_figureV->showSkillSelectPanel(false);

		_figureMainView->_figureV->resetBtn();
	}
	SkillView * sv = ViewManager::getInstance()->_skillView;
	if (sv)
	{
		if (sv->getisPop())
		{
			sv->setisPop(false);
		}
	}
	PeiyangView * pv = ViewManager::getInstance()->_peiyangView;
	if (pv)
	{
		if (pv->getisPop())
		{
			pv->setisPop(false);
		}
	}
	if(_figureMainView->getisPop())
	{
		g_pGlobalManage->setCurFocusGID(LayerManager::windowLayer->getMyFocusGID()); // add by LH 0412
		// to create manager cash data
		// add code here
		if (g_pFigureScrollView)
		{
			//g_pFigureScrollView->reNewScrollView();
			//g_pFigureScrollView->showEquipInfo();
			//g_pFigureScrollView->showSkillInfo();
		}
		if (_figureMainView->_figureV)
		{			
			if (_figureMainView->_figureV->_attrLayer)
			{
				_figureMainView->_figureV->_attrLayer->loadItems();
			}
		}
	}
	else
	{
		g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID()); // add by LH 0425
	}

	if (g_pFigureScrollView)
	{
		int page = g_pFigureScrollView->currentScreen;
		while (page > 1)
		{
			//g_pFigureScrollView->moveToPreviousPage();
			--page;
		}

		FigureMainView * fmv = ViewManager::getInstance()->figureView;
		if (fmv)
		{
			if (fmv->_figureV)
			{
				if (	fmv->_figureV->_attrLayer)
				{
					fmv->_figureV->_attrLayer->loadItems();
				}
			}
		}
	}	

	// required skill list
	CCMD317 cmd;
	cmd.a_type = 3;
	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmd);
	}
}

void FigureMediator::closeFigureView()
{
	if(_figureMainView)
	{
		_figureMainView->closeView();
		//_figureMainView = NULL;
	}
}

void FigureMediator::sockEquipInfo(char* cmd)
{
	//sendNotification(Facade_Command, AppFacade_FIGURE_COMMAND, (char*)cmd, FigureCommand::INIT_FIGURE_EQUIP_INFO);
	sendNotification(Facade_Command, AppFacade_FIGURE_COMMAND, (char*)cmd, FigureCommand::INIT_FIGURE_EQUIP_INFO);
}

void FigureMediator::sockEquipItemUpdate(char* cmd)
{
	//sendNotification(Facade_Command, AppFacade_FIGURE_COMMAND, (char*)cmd, FigureCommand::UPDATE_EQUIP_INFO);
	sendNotification(Facade_Command, AppFacade_FIGURE_COMMAND, (char*)cmd, FigureCommand::UPDATE_EQUIP_INFO);
}

void FigureMediator::sockEqipSkillUpdate(char* cmd)
{
	SCMD30E* scmd30e = (SCMD30E*)cmd;
	if(scmd30e->a_isSucceed == 1)
	{
		//sendNotification(Facade_Command, AppFacade_FIGURE_COMMAND, (char*)cmd, FigureCommand::UPDATE_SKILL_INFO);
		sendNotification(Facade_Command, AppFacade_FIGURE_COMMAND, (char*)cmd, FigureCommand::UPDATE_SKILL_INFO);
	}
	else
	{
		//
	}
}

void FigureMediator::sockSaveWashValue(char* cmd)
{
	SCMD31D* scmd31d = (SCMD31D*)cmd;
	if(scmd31d->a_isSuccess == 1)
	{
		//sendNotification(Facade_Command, AppFacade_FIGURE_COMMAND, (char*)cmd, FigureCommand::SAVE_WASH_VALUE);
		sendNotification(Facade_Command, AppFacade_FIGURE_COMMAND, (char*)cmd, FigureCommand::SAVE_WASH_VALUE);
	}
	else
	{
// 		Message * msg = new Message();
// 		msg->show(ValuesUtil::Instance()->getString("PY22"),ccc3(240,33,33),1);
	}
}

void FigureMediator::sockRefreshWashValue(char* cmd)
{
	SCMD31F* scmd31f = (SCMD31F*)cmd;
	if(scmd31f->a_isSuccess == 1)
	{
		//sendNotification(Facade_Command, AppFacade_FIGURE_COMMAND, (char*)cmd, FigureCommand::REFRESH_WASH_VALUE);
		sendNotification(Facade_Command, AppFacade_FIGURE_COMMAND, (char*)cmd, FigureCommand::REFRESH_WASH_VALUE);

	}
	else
	{
		Message * msg = new Message();
		msg->show(ValuesUtil::Instance()->getString("PY21"),ccc3(240,33,33),1);
		
		//_mainView.washView.showNewValue(param.b_figureId, null);//Wash attribute failure
	}
}

void FigureMediator::sockRebornResult(char* cmd)
{
	SCMD30C* scmd30c = (SCMD30C*)cmd;
	if(scmd30c->a_result == 1)
	{//Reincarnate success
		Message::Instance()->show(ValuesUtil::Instance()->getString("PY31"),ccc3(12,233,25),3.0f);
		PlayerInfoVo* info = RoleManage::Instance()->getMercenary(scmd30c->b_figureId);
		if (info)
		{
			info->figureBaseInfo.rebornNum = scmd30c->c_rebornNum;
			//info->playerBaseInfo._lev = 1;//Level is not changed
			info->playerBaseInfo._exp = 0;// should changed depend

			RoleManage::Instance()->updateMercenaryEx(scmd30c->b_figureId , info);
		}
	}
	else
	{
		//Message::Instance()->show("Reborn failed");
	}
}

void FigureMediator::sockPriceResult(char* cmd)
{
	SCMD295* scmd295 = (SCMD295*)cmd;
	if(scmd295->a_type == 0)
	{
		PeiyangView * pv = ViewManager::getInstance()->_peiyangView;
		if (pv)
		{
			pv->setPrice(scmd295->b_price);
			if (pv->getisPop())
			{
				pv->updatePrice(scmd295->b_price);
			}
		}
	}
}

void FigureMediator::sockUpdateExp(char* cmd)
{
 	SCMD350* scmd = (SCMD350*)cmd;

	PlayerInfoVo* info = RoleManage::Instance()->getMercenary(scmd->a_figureId);
	if (!info)
	{
		return;
	}

	int nTmpLev = info->playerBaseInfo.lev();
	info->playerBaseInfo._exp = scmd->c_exp;
	if (!scmd->b_isReborn)
	{
		if (info->playerBaseInfo.isRole)
		{
			RoleManage::Instance()->roleInfo()->playerBaseInfo._exp = scmd->c_exp;
			//RoleManage::Instance()->roleInfo()->playerBaseInfo._lev = scmd->d_lev;
			//Doyang 20120829
			RoleManage::Instance()->roleInfo()->playerBaseInfo.lev(scmd->d_lev);

			// LH20120910
			// new hand help
			if (scmd->e_isUpgrade)
			{
				if (g_pGlobalManage->getisInFight())
				{
					if (_fightProxy)
					{
						_fightProxy->_bData._callbacks.push_back(new ShowNewHandHelpAction(scmd->d_lev));
					}	
				}
				else
				{
					if (!ViewManager::getInstance()->_helpView)
					{
						ViewManager::getInstance()->_helpView = new NewHandHelpView();
						GameDispatcher::getInstance()->addEventListener(GameDispatcher::RESET_NEWHELP_VIEW ,
							ViewManager::getInstance()->_helpView ,callfuncND_selector(NewHandHelpView::resetView));
					}
					GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::RESET_NEWHELP_VIEW , (void *)&scmd->d_lev);
				}
				

				int lev = scmd->d_lev;
				for (int i = 32 ; i < 46 ; i++)
				{
					SCMD185 scmd;
					scmd.a_result = 1;
					scmd.b_id = i;
					scmd.c_level = lev;
					sendNotification(Facade_Command , AppFacade_CRYSTAL_PROXY_CHANGE , (char *)&lev , CrystalCommand::UPGRADE_CRYSTALS);
				}
			}
		}

		info->playerBaseInfo._exp = scmd->c_exp;
		info->playerBaseInfo._lev = scmd->d_lev;
		
		// auto reborn  by LH 20120804
		int starLev = info->figureBaseInfo.rebornNum;
		int reBornNeedLev = 51 + starLev * 5;
		if ((scmd->d_lev >= reBornNeedLev))
		{
			sendRebornRequest(scmd->a_figureId);
		}
	}
	else
	{
		info->playerBaseInfo.adExp = scmd->c_exp;
		info->playerBaseInfo.adLv = scmd->d_lev;
		if (info->playerBaseInfo.isRole)
		{
			RoleManage::Instance()->roleInfo()->playerBaseInfo.adExp = scmd->c_exp;
			RoleManage::Instance()->roleInfo()->playerBaseInfo.adLv = scmd->d_lev;
		}
	}
	// update
	RoleManage::Instance()->updateMercenaryEx(scmd->a_figureId , info);

	if (ViewManager::getInstance()->figureView && ViewManager::getInstance()->figureView->getisPop())
	{
		if (g_pFigureScrollView)
		{
			g_pFigureScrollView->setIsReborn(scmd->a_figureId,scmd->b_isReborn);
			g_pFigureScrollView->updateRoleLevel(scmd->a_figureId);
			g_pFigureScrollView->updateEXPInfo(scmd->a_figureId);
		}
	}
	
	// RoleUI update by LH0801
	RoleUI * pRoleUI = ViewManager::getInstance()->_roleUI;
	if (pRoleUI)
	{
		if (info->playerBaseInfo.isRole)
		{
			pRoleUI->setRoleLev(info->playerBaseInfo._lev);

			bool isUpgreade = scmd->e_isUpgrade;
			if (isUpgreade)
			{
				if (g_pGlobalManage->_isInFight)
				{
					if (_fightProxy)
					{
						_fightProxy->_bData._callbacks.push_back(new FightFollowLevelUpAction());
					}					
				}
				else
				{
					Scene * pScene = ViewManager::getInstance()->_scene;
					if (pScene && pScene->_role)
					{
						pScene->_role->playEffect(PlayerAniType::TYPE_LevelUp);
					}
				}
			}
		}
	}

	// reset vscroll
	if (scmd->e_isUpgrade && scmd->d_lev>2)
	{
		if (ViewManager::getInstance()->_pVScrollUI)
		{
			//ViewManager::getInstance()->_pVScrollUI->resetListView();
			ViewManager::getInstance()->_pVScrollUI->addButtonByLev(scmd->d_lev);
		}		
	}

	// open Navigate buttons
	if (scmd->e_isUpgrade)
	{
			// mainNavigate
		if (ViewManager::getInstance()->mainNavigate)
		{
			ViewManager::getInstance()->mainNavigate->addButtonByLev(scmd->d_lev);
		}
			// secNavigate
		if (ViewManager::getInstance()->_secNavigate)
		{
			ViewManager::getInstance()->_secNavigate->addButtonByLev(scmd->d_lev);
		}
	}

	// notify
	if (scmd->e_isUpgrade
		&& (scmd->d_lev == 10 || scmd->d_lev == 20 || scmd->d_lev == 30)
		&& nTmpLev < scmd->d_lev)
	{
		int goodId = 1042;
		if (scmd->d_lev == 10)
		{
			goodId = 1042;
		}
		else if (scmd->d_lev == 20)
		{
			goodId = 1043;
		}
		else if (scmd->d_lev == 30)
		{
			goodId = 1044;
		}
		
		//NotifyManager::Instance()->addNotification(NotifyType::NType_Gift);
		SCMD16D  *pParam = new SCMD16D();
		pParam->a_from = 0;
		pParam->b_goodsId = goodId;
		pParam->c_num = 0;
		pParam->d_sitGrid = 0;

		if (g_pGlobalManage->getisInFight())
		{
			SpecialItemAddAction * pCallBack = new SpecialItemAddAction();
			pCallBack->init(pParam);
			if (_fightProxy)
			{
				_fightProxy->_bData._callbacks.push_back(pCallBack);
			}
		}
		else
		{
			BagMediator * pBagMed = (BagMediator *)g_pFacade->retrieveMediator(AppFacade_BAG_PROXY_CHANGE);
			if (pBagMed)
			{
				pBagMed->onSpecialItemAdd(pParam);
			}		
		}
	}

	// challenge copy tips // special handler
	if (scmd->e_isUpgrade
		&& scmd->d_lev == 20)
	{
		/*
		if (g_pGlobalManage->getisInFight())
		{
			StepVo * pStep = new StepVo();
			pStep->btnId = -1;
			pStep->param.push_back("0" );
			pStep->param.push_back("0" );
			pStep->param.push_back("15" );
			FightProxy * pFightProxy = (FightProxy *)g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
			if (pFightProxy)
			{
				pFightProxy->_bData._callbacks.push_back((BaseAction *)new StoryFollowTipsAction(pStep));
			}
		}
		else
		{
			LeaderAlert::show("15", 5, true, NULL, NULL, NULL);
		}
		*/
	}
	// update train merch level
	if (scmd->e_isUpgrade && ViewManager::getInstance()->trainView)
	{
		ViewManager::getInstance()->trainView->updateLevelLabel(scmd->a_figureId , scmd->d_lev);
	}
	
	// new hand
	if (scmd->e_isUpgrade)
	{
		NewhandManager::Instance()->setNewHandStateByType(scmd->d_lev , NewhandManager::Flag_New);
	}
	
}

void FigureMediator::sockMercSkillExchange(char* cmd)
{
	//SCMD2FF
// 	_figureMainView = ViewManager::getInstance()->figureView;
// 	if (!_figureMainView)
// 	{
// 		return;
// 	}
	//sendNotification(Facade_Command, AppFacade_FIGURE_COMMAND, (char*)cmd, FigureCommand::MERC_SKILL_EXCHANGE);
	sendNotification(Facade_Command, AppFacade_FIGURE_COMMAND, (char*)cmd, FigureCommand::MERC_SKILL_EXCHANGE);
}

void FigureMediator::sockBuyIdentifyGrid(char* cmd)
{
	SCMD2A1 * scmd = (SCMD2A1 *)cmd;
	if (!scmd->a_isSuc)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("Failed").c_str() , ccc3(12, 233 ,25) , 1);
		return;
	}
	
	if (ViewManager::getInstance()->_pIdentifyView)
	{
		ViewManager::getInstance()->_pIdentifyView->updateCurrentIdentifyLayer(cmd);
		ViewManager::getInstance()->_pIdentifyView->updateNewIdentifyLayer(cmd);
	}
}

void FigureMediator::sockSaveIdentifyValue(char* cmd)
{
	//SCMD2A7 * scmd = (SCMD2A7 *)cmd;
	
}

void FigureMediator::sockMercIdentifyInfo(char* cmd)
{

}

void FigureMediator::attPointChange(char* cmd)
{
	SCMD35E* scmd = (SCMD35E*)cmd;

	PlayerInfoVo * pInfoVo = RoleManage::Instance()->getMercenary(scmd->a_mercId);
	if(!pInfoVo){		return;}

	std::string strTips("");
	char path[128] = {0};
	int differ = scmd->b_att - pInfoVo->figureBaseInfo.attPoint;
	NewhandManager::Instance()->_deltaAttacPoint = differ;
	NewhandManager::Instance()->_pInfoVo = pInfoVo;
	if (!NewhandManager::Instance()->_isGetEquipment)
	{
		if (differ > 0)
		{
			sprintf(path , ValuesUtil::Instance()->getString("ADD0010").c_str() , pInfoVo->playerBaseInfo.name.c_str() , differ);
			if (g_pGlobalManage->_isInFight)
			{
				if (_fightProxy)
				{
					ShowAttrChangeAction * pAction = new ShowAttrChangeAction(path , ccc3(255,215,0) , 2);
					_fightProxy->_bData._callbacks.push_back(pAction);
				}	
			}
			else
			{
				Message::Instance()->show(path , ccc3(255,215,0) , 2);
			}
		} 
		else if (differ < 0)
		{
			sprintf(path , ValuesUtil::Instance()->getString("ADD0011").c_str() , pInfoVo->playerBaseInfo.name.c_str() , (-1) * differ);
			if (g_pGlobalManage->_isInFight)
			{
				if (_fightProxy)
				{
					ShowAttrChangeAction * pAction = new ShowAttrChangeAction(path , ccc3(255,215,0) , 2);
					_fightProxy->_bData._callbacks.push_back(pAction);
				}
			}
			else
			{
				Message::Instance()->show(path , ccc3(233,12,233), 2);
			}
		}
	}
	


	pInfoVo->figureBaseInfo.attPoint = scmd->b_att;

	RoleManage::Instance()->updateMercenaryEx(scmd->a_mercId , pInfoVo);

// 	if(_figureMainView /*&&  _figureMainView->getType()== "_tab1" */
// 	/*&& _figureMainView->_currentId==scmd->a_mercId*/
// 	&& _figureMainView->_figureV)
// 	{
// 		_figureMainView->_figureV->showEquipInfo();
// 	}
	//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	//std::map<int, PlayerInfoVo>::iterator iter = list->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = list->begin();
	int page = 0;
	for (;iter != list->end();iter++)
	{
		if (scmd->a_mercId == iter->first.id)
		{
			iter->second.figureBaseInfo.attPoint = scmd->b_att;
			break;
		}
		++page;
	}

	if (iter->second.playerBaseInfo.isRole)
	{
		RoleManage::Instance()->roleInfo()->figureBaseInfo.attPoint = scmd->b_att;
	}

	if (!g_pFigureScrollView)
	{
		return;
	}
	if (ViewManager::getInstance()->figureView && ViewManager::getInstance()->figureView->getisPop())
	{
		g_pFigureScrollView->showEquipInfo(scmd->a_mercId,page);
		if (ViewManager::getInstance()->figureView->_figureV && ViewManager::getInstance()->figureView->_figureV->_attrLayer)
		{
			ViewManager::getInstance()->figureView->_figureV->_attrLayer->loadItems();
		}
	}
}

void FigureMediator::sendOnClotheRequest(uint32 figureID,uint8 sitGrid)
{
	CCMD170 * c = new CCMD170();
	if (c)
	{
		c->a_figureId = figureID;
		c->b_sitGrid = (uint8)sitGrid;
		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if (pSocket)
		{
			pSocket->sendMessage(c);
			cocos2d::CCLog("Role:send put on clothe Request:CCMD170 success");			
		}
		CC_SAFE_DELETE(c); // LH0712LEAK
	}
}

void FigureMediator::sendDownClotheRequest(uint32 figureID,uint8 sitGrid,uint8 bagGrid)
{
	CCMD171 * c = new CCMD171();
	if (c)
	{
		c->a_figureId = figureID;
		c->b_sitGrid = (uint8)sitGrid;
		c->c_bagGrid = (uint8)bagGrid;
		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if (pSocket)
		{
			pSocket->sendMessage(c);
			cocos2d::CCLog("Role:send put down clothe Request:CCMD171 success");			
		}
		CC_SAFE_DELETE(c); // LH0712LEAK
	}
}

void FigureMediator::sendRebornRequest(uint32 figureID)
{
	CCMD30B * c = new CCMD30B();
	if (c)
	{
		c->a_figureId = figureID;
		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if (pSocket)
		{
			pSocket->sendMessage(c);
		}
		CCLog("Peiyang:send reborn request success CCMD30B");
		CC_SAFE_DELETE(c); // LH0712LEAK
	}
}

void FigureMediator::sendWashRequest(uint32 figureID,uint8 type,uint8 useItem)
{
	CCMD31E * c = new CCMD31E();
	if (c)
	{
		c->a_figureId = figureID;
		c->b_type = type;
		c->c_useItem = useItem;
		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if (pSocket)
		{
			pSocket->sendMessage(c);
		}
		CCLog("Peiyang:send wash request success CCMD31E");
		CC_SAFE_DELETE(c); // LH0712LEAK
	}
}

void FigureMediator::sendSaveRequest(uint32 figureID)
{
	CCMD31C * c = new CCMD31C();
	if (c)
	{
		c->a_figureId = figureID;
		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if (pSocket)
		{
			pSocket->sendMessage(c);
		}
		CC_SAFE_DELETE(c); // LH0713
		CCLog("Peiyang:send save request success CCMD31C");
	}
}

void FigureMediator::sendPriceRequest(uint32 type)
{
	CCMD294 ccmd;
	ccmd.a_type = 0;
	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&ccmd);
	}
}

void FigureMediator::figurePopHandle( CCNode *pNode, void *data )
{
	//this->openView();
	//LH20120106
	openFigureView();
}

void FigureMediator::sendMercIdentifyInfoRequest()
{
	CCMD2A2 cmd;
	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmd);
	}
}

void FigureMediator::sendIdentifyRequest(int mechID , int type)
{
	CCMD2A4 cmd;
	cmd.a_mercId = mechID;
	cmd.b_useItem = (uint8)type;
	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmd);
	}
}

void FigureMediator::sendSaveIdentifyRequest()
{
	CCMD2A6 cmd;
	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmd);
	}
}

void FigureMediator::sendBuyGridRequest()
{
	CCMD2A0 cmd;
	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmd);
	}
}