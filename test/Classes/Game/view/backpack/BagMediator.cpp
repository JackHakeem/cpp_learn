#include "BagMediator.h"
#include "control/AppFacade.h"
#include "control/backpack/BagProxyCommand.h"
#include "manager/ViewManager.h"
#include "mvc/Facade.h"
#include "model/backpack/BagProxy.h"
#include "model/bank/BankProxy.h"
#include "components/BagGoods.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "model/com/GoodsDynamicManager.h"
#include "model/com/vo/GoodsDynamic.h"
#include "socket/network/GameServerSocket.h"
#include "events/GameDispatcher.h"
#include "manager/PopManage.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "model/backpack/GoodsManager.h"
#include "socket/command/c16/CCMD160.h"
#include "socket/command/c16/CCMD16A.h"
#include "socket/command/c17/CCMD176.h"
#include "socket/command/c16/CCMD16B.h"
#include "socket/command/c1d/CCMD1D9.h"
#include "socket/command/s16/SCMD16D.h"
#include "socket/command/c16/CCMD168.h"
#include "socket/command/c16/CCMD169.h"
#include "view/fight/callback/SpecialItemAddAction.h"
#include "model/scene/fight/vo/BattleData.h"
#include "manager/sound/SoundManager.h"

const int canDelTypeArr[] = {2,3,4,5};//Can delete type: 2 equipment 3 4 5 gem stones equipment debris pieces

BagMediator::BagMediator():_bagProxy(0),_bagView(0),_dispatcher(0)
{
	_bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
	
	_dispatcher = GameDispatcher::getInstance();
	_dispatcher->addEventListener(GameDispatcher::PACK_CHANGE, this, callfuncND_selector(BagMediator::packChange));
	_dispatcher->addEventListener(PopEventName::SHOW_UI_BAG, this, callfuncND_selector(BagMediator::bagPopHandle));
	//_socket.addCmdListener(SocketCMDConst.WMSG_WORLD_ITEM_ADD_INFO,onSpecialItemAdd); 
}

void BagMediator::initWorldBag(char* data)
{
	sendNotification(Facade_Command, AppFacade_BAG_PROXY_CHANGE, data, BagProxyCommand::CREATE_GOODS_LIST);//Here to inform the control layer handles
}

void BagMediator::handleNotification(int M2Vcmd, char* data)
{
	switch(M2Vcmd)
	{
	case CREATE_LIST:
		createList();
		//bagPop();//kktest
		break;
	case BAG_ITEM_UPDATE:
		bagUpdate(data);
		break;
	case BAG_ITEM_TIP_UPDATE:
		updateTip( data );
		break;
	case OPEN_ID_GOOD:
		openGoodsById(data);
		break;
	default:
		break;
	}
}

//根据原型id打开物品（新手阶段自动打开礼包）
void BagMediator::openGoodsById(char* datagoodId)
{
	if (!datagoodId)
		return;
	int goodId = *(int*)datagoodId;

	std::map<int32, GoodsInfo*>& tmpGoodList = _bagProxy->_goodsList;
	for (std::map<int32, GoodsInfo*>::iterator it = tmpGoodList.begin(); it != tmpGoodList.end(); it++)
	{
		GoodsInfo* info = it->second;
		if (info->goodId == goodId)
		{
			struct sdata
			{
				int32 UseType;
				int32 type;
				int32 sitNum;
			//	int32 id;
			//	int32 goodsId;
			};
			sdata d;
			d.UseType = 2;
		//	d.id = info->id;
		//	d.goodsId = info->goodId;
			d.type = info->type;
			d.sitNum = info->sitGrid;
			packChange(0, &d);	
		}
	}

	//new ParamEvent(GameDispatcher.PACK_CHANGE, 
		//		{UseType:2, id:info.id, goodsId:info.goodId,type:info.type, sitNum:info.sitGrid})
}

/**
	* Open the package will be put to the front of the place
	* 
	*/	
void BagMediator::openBag()
{
	if (_bagView)
	{
		_bagView->setisPop(!_bagView->getisPop());
		_bagView->release(); //LH20120108
	}
}

bool BagMediator::isBagViewPop()
{
	if(!_bagView){
		return false;
	}else{
		return _bagView->getisPop();
	}
}

/**
	*  Create
	* 
	*/	
void BagMediator::createList()
{
	if (_bagView && _bagView->getisPop())
	{
		_bagView->OpenBag(_bagProxy->_goodsList, _bagProxy->_noEmpty, _bagProxy->_goodsNumber);
	}
}

/**
	* Update 
	* @param arr
	* 
	*/		
void BagMediator::bagUpdate(char* arr)
{
	if (!_bagView || !isBagViewPop()) return;
	_bagView->updateGoods(arr, _bagProxy->_noEmpty);

	SoundManager::Instance()->playBagItemEffectSound();
}
/*
private function bagUpdate(arr:Array):void{
	if(!_bagView || !isBagViewPop()) return;
	_bagView.updateGoods(arr,_bagProxy.noEmpty);
}*/

void BagMediator::startListener()
{
	if (!_bagView)
		return;
	/*背包打开后侦听背包的初始化*/
	//_bagView.addEventListener(BagView.BAG_SORT_CLICK, onSortHandler );	
	_bagView->addEventListener(BagView::BAG_ADD_GRID_CLICK, this, callfuncND_selector(BagMediator::onAddGridHandler));
	_bagView->addEventListener(BagView::BAG_SORT_CLICK, this, callfuncND_selector(BagMediator::onSortHandler));

}


void BagMediator::bagPopHandle(CCNode* n, void* data)
{
	bagPop();
}
	
void BagMediator::bagPop()
{
	
	if (!_bagView)
	{
		_bagView = new BagView();
		ViewManager::getInstance()->bagView = _bagView;
		_bagView->init();
		startListener();
	}
	openBag();

	g_pGlobalManage->setCurFocusGID(LayerManager::windowLayer->getMyFocusGID());
	createList();

}


void BagMediator::packChange(CCNode* n, void* data)
{
	if (!data)
		return;

	int32 UseType = *(int32*)data;
	switch (UseType)
	{
	case 1://Mobile grid, send the new and old position to the server
		{
			struct sdata
			{
				int32 UseType;
				int32 oldGrid;
				int32 newGrid;
			};
			sdata d = *(sdata*)data;
			

			CCMD160* s = new CCMD160();
			if (s)
			{
				s->a_oldSit = static_cast<int8>(d.oldGrid);
				s->b_newSit = static_cast<int8>(d.newGrid);
				GameServerSocket* pSocket = GameServerSocket::getInstance();
				if (pSocket)
					pSocket->sendMessage(s);

				LayerManager::loadingPic->socketWait_old( WMSG_WORLD_BAG_ITEM_UPDATE );
			}
			SAFE_DELETE(s);
		}
		break;
	case 2://Use or mobile to other items panel
		{
			struct sdata
			{
				int32  UseType;
				uint32 type;
				uint32 sitNum;
			};
			sdata e = *(sdata*)data;
			//
			if (e.type == 1 || (e.type >= 6 && e.type <= 15))//Gift bag 1, the VIP gift bag 6 to 15
			{
				/*
				if(!testCanVipGiftOpen(e.param.type)){
							Message.show("VIP等级未达到, 请充值达到等级后再使用");
						}
						else if(_bagProxy.getSpaceGridNum()<=0){
							MsgManage.getInstance().showMsg(MsgManage.SYSTEM_MSG, "S251");
						}
						else{
						*/
							CCMD1D9* s = new CCMD1D9();
							if (s)
							{
								s->a_sitNum = static_cast<int16>(e.sitNum);
								GameServerSocket* pSocket = GameServerSocket::getInstance();
								if (pSocket)
									pSocket->sendMessage(s);
							}
							SAFE_DELETE(s);
						/*
						}
				*/

				
			}
			else if (e.type == 16)//Random gift bag
			{
			//_socket.sendMessage(SocketCMDConst.CMSG_WORLD_GET_RANDGIFT_INFO, new Int8( e.param.sitNum));
			}
			else if (e.type == 21)
			{
				/*
					if(RoleManage.getInstance().accountInfo.roleLim < RoleManage.getInstance().accountInfo.roleNum+1){
						LangManager.msgShow("R0001");
						break;
					}
					var name:String = _bagProxy.goodsInfo(e.param.sitNum).name;
					name = name.slice(0,name.length-3);		
				*/
				std::string name = _bagProxy->goodsInfo(e.sitNum)->name;//->goodsInfo(e.param.sitNum).name;
				name = name.substr(0,name.size()-7);
				//name = name.slice(0,name.length-3);		
				if (checkMerc(name))
				{
					//Message.show("已经招募了该佣兵");
					break;				
				}

				CCMD1D9* s = new CCMD1D9();
				if (s)
				{
					s->a_sitNum = static_cast<int16>(e.sitNum);
					GameServerSocket* pSocket = GameServerSocket::getInstance();
					if (pSocket)
						pSocket->sendMessage(s);
				}
				SAFE_DELETE(s);				
			}
			/*
				else if(e.param.type == 21)
				{						
					if(RoleManage.getInstance().accountInfo.roleLim < RoleManage.getInstance().accountInfo.roleNum+1){
						LangManager.msgShow("R0001");
						break;
					}
					var name:String = _bagProxy.goodsInfo(e.param.sitNum).name;
					name = name.slice(0,name.length-3);						
					if(checkMerc(name))
					{
						Message.show("已经招募了该佣兵");
						break;
					}
						_socket.sendMessage(SocketCMDConst.CMSG_WORLD_USE_ITEM, new Int8( e.param.sitNum));
				}
				*/
			else//operation
			{
				if(g_pPopManage->isViewPop(PopEventName::BANK))//If the warehouse is already open
				{
					bagToBank(e.sitNum);
				}
				else if (g_pPopManage->isViewPop(PopEventName::SHOP))
				{
					struct sdata
					{
						int32 UseType;
						int32 sit;
					//	int32 goodid;
					};
					sdata d;
					d.UseType = 2;
					d.sit = e.sitNum;
					//d.goodid = e.
					_dispatcher->dispatchEvent(GameDispatcher::SHOP_VIEW_CLICK, &d);
					//_dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.SHOP_VIEW_CLICK, {UseType:2,
					//			sit:e.param.sitNum,goodid:e.param.goodsId}));
				}
				else
				{
					//The default open character interface, and items
					if (g_pPopManage->isViewPop(PopEventName::FIGURE))
					{
						//_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_FIGURE));
					}
					//uint32 typeId = _bagProxy->goodsInfo(e.sitNum)->goodId;
					//sendNotification(FigureMediator.PUT_ON_EQUIP, {typeId:typeId, sitGrid:e.param.sitNum});
				}
			}
		}
		break;
	case 3://丢弃物品
		{
			struct sdata
			{
				int32 UseType;
				int32 sitGrid;
			};
			sdata e = *(sdata*)data;

			deleteGoodsHandle(e.sitGrid);
		}
		break;
//.......还有
		break;
	default:
		break;
	}
	
}

bool BagMediator::checkMerc(std::string name)
{
	std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	std::map<int ,PlayerInfoVo>::iterator it;
	for (it = list->begin(); it != list->end(); it++)
	{
		PlayerInfoVo pvo = it->second;
		CCLog("kevin test %s   %s ", pvo.playerBaseInfo.name.c_str(), name.c_str());
		if (strcmp(pvo.playerBaseInfo.name.c_str(), name.c_str()) == 0)
		{
			return true;
		}
	}
	return false;
}


/*
private function packChange(e:ParamEvent):void{
			switch(e.param.UseType){

				case 3://丢弃物品
					deleteGoodsHandle(e.param.sitGrid);
					break;
				case 7://获取物品动态信息(必定是装备)
					var id:uint = e.param.id;
					var sitGrid:int = e.param.sitGrid;
					var type:int = e.param.type;	//位置 
					//获取对比信息
					var contrast:GoodsInfo = RoleManage.getInstance().getSitGridEquip(type);
					var cmdDym:CCMD16E = new CCMD16E();
					var isSelect:Boolean = false;
					if(contrast!=null && contrast.id>0){
						var contrastDynamic:GoodsDynamic = GoodsDynamicManager.getInstance().getGoodsDynamic(contrast.id);
						if(!contrastDynamic){
							cmdDym = new CCMD16E();
							cmdDym.a_locationType = new Int8(DynamicLocation.FIGURE);	
							cmdDym.b_sitNum = new Int8(contrast.sitGrid);
							cmdDym.c_roleId = RoleManage.getInstance().currentId;
							_socket.sendMessage(SocketCMDConst.CMSG_WORLD_ITEM_INFO, cmdDym);
							isSelect = true;
						}
						else{
							updateTip({grid:sitGrid,type:type});
						}
					}
					else{//清除对比信息
						updateTip({grid:sitGrid,type:type});
					}
					var goodsDynamic:GoodsDynamic = GoodsDynamicManager.getInstance().getGoodsDynamic(id);
					if(isSelect || goodsDynamic==null){
						cmdDym = new CCMD16E();
						cmdDym.a_locationType = new Int8(DynamicLocation.BAG);	
						cmdDym.b_sitNum = new Int8(sitGrid);
						cmdDym.c_roleId = RoleManage.getInstance().accountInfo.roleId;
						_socket.sendMessage(SocketCMDConst.CMSG_WORLD_ITEM_INFO, cmdDym);
					}
					break;
				case 10:
					_socket.sendMessage(SocketCMDConst.CMSG_WORLD_SUBGOLD_REQUEST, new Int8(e.param.type));
					break;
			}
		}
*/

/**
	*从背包移到仓库 
	* @param sitGrid
	* 
	*/		
void BagMediator::bagToBank(int32 sitGrid)
{
	BankProxy* bankProxy = (BankProxy*)g_pFacade->retrieveProxy(AppFacade_BANK_PROXY_CHANGE);
	if (bankProxy && bankProxy->getSpaceGridNum() > 0)
	{
		CCMD16A* cmd2 = new CCMD16A();
		if (cmd2)
		{
			cmd2->a_type = static_cast<int8>(0);
			cmd2->b_sitGrid = static_cast<int8>(sitGrid);
			GameServerSocket* pSocket = GameServerSocket::getInstance();
			if (pSocket)
				pSocket->sendMessage(cmd2);

			LayerManager::loadingPic->socketWait_old( WMSG_WORLD_BANK_ITEM_UPDATE );
		}
		SAFE_DELETE(cmd2);
	}
	else
	{
		BagGoods* _bagGoods = _bagView->m_pCurSelectedBagGoods;
		if (_bagGoods)
		{
			_bagGoods->reShowItemAndFrame(true);
		}
		//MsgManage.getInstance().showMsg(MsgManage.SYSTEM_MSG, "S252");
	}
}

/**
	* 物品更新 
	* @param param
	* 
				
private function sockBagItemUpdate(param:SCMD161_163_165_167):void{
	var arr:Array = param.a_goodsList;
	this.sendNotification(AppFacade.BAG_PROXY_CHANGE,arr, BagProxyCommand.UPDATE_GOODS_LIST);
} 
*/
void BagMediator::sockBagItemUpdate(std::list<SCMD161_163_165_167Node>*	param)
{
	sendNotification(Facade_Command, AppFacade_BAG_PROXY_CHANGE, (char*)param, BagProxyCommand::UPDATE_GOODS_LIST);//这里要通知控制层处理
}

/**
	*从背包删除物品 
	* @param sit
	* 
	*/	

void BagMediator::deleteGoodsHandle(int32 sit)
{
	GoodsInfo* info = _bagProxy->goodsInfo(sit);
	int32 type = info->type;
	if (canDelTypeArr[type] == -1)
	{
		//Message.show("该类型物品不能删除", 0xff0000);
	}
	else
	{
		GoodsDynamic* dynInfo = g_pGoodsDynamicManager->getGoodsDynamic(info->id);
		if (dynInfo && dynInfo->u_stamina + dynInfo->v_wrist + dynInfo->w_intellect > 0)
		{
			//Message.show("不能删除有魔化属性的物品", 0xff0000);
		}
		else
		{
			confirmToDel(sit);
		}
	}
	/*
			var info:GoodsInfo =  _bagProxy.goodsInfo(sit);
			var type:int = info.type;
			if(canDelTypeArr.indexOf(type)==-1){
				Message.show("该类型物品不能删除", 0xff0000);
			}
			else {
				var dynInfo:GoodsDynamic = GoodsDynamicManager.getInstance().getGoodsDynamic(info.id);
				if(dynInfo && dynInfo.u_stamina + dynInfo.v_wrist + dynInfo.w_intellect > 0){
					Message.show("不能删除有魔化属性的物品", 0xff0000);
				}
				else{
					Alert.show(new GameCodeMsg("C0020").message, "提示", 1, 
						confirmToDel, null, "确认", "取消", sit);
				}
			}
	*/


}

void BagMediator::confirmToDel(int32 sit)
{
	CCMD16B* cmdDel = new CCMD16B();
	if (cmdDel)
	{
		cmdDel->a_bagType = static_cast<int8>(1);
		cmdDel->b_sitGrid = static_cast<int8>(sit);
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(cmdDel);
		
		LayerManager::loadingPic->socketWait_old( WMSG_WORLD_BAG_ITEM_UPDATE );
	}
	SAFE_DELETE(cmdDel);
}

/**
	*部分物品获得时播放特性 
	*
	* @param param
	* 
	*/	
void BagMediator::onSpecialItemAdd(SCMD16D* param)
{
	FightProxy* fightProxy = (FightProxy*)g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);

	if (fightProxy->battleId != 0)
	{
		SpecialItemAddAction* callback = new SpecialItemAddAction();
		callback->init(param);
		
		fightProxy->_bData._callbacks.push_back(callback);
		return;
	}

	// 直接
	SpecialItemAddAction callback = SpecialItemAddAction();
	callback.init(param);
	callback.doAction();
	
}


void BagMediator::onSortHandler(CCNode* n, void* data)
{
	CCMD168* s = new CCMD168();
	if (s)
	{
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
        {
			pSocket->sendMessage(s);

			LayerManager::loadingPic->socketWait_old( WMSG_WORLD_BAG_INIT );
        }
	}
	SAFE_DELETE(s);
	//
	CCMD169* s169 = new CCMD169();
	if (s169)
	{
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
        {
			pSocket->sendMessage(s169);
        }
	}
	SAFE_DELETE(s169);
}

/**
	* 添加格子 
	* @param e
	* 
	*/		
void BagMediator::onAddGridHandler(CCNode* n, void* data)
{
	if (!data) return;
	int32 num = *((int*)data);
	CCMD176* s = new CCMD176();
	if (s)
	{
		s->a_gridType = 1;
		s->b_number = num;
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
        {
            CCLog("Send 0x176 fighting result notice");
			pSocket->sendMessage(s);

			LayerManager::loadingPic->socketWait_old( WMSG_WORLD_BAG_INIT );
        }
	}
	SAFE_DELETE(s);
}

void BagMediator::updateTip( char* data )
{
	struct Node
	{
		int id;
		int grid;
		int type;
	} obj;

	obj = *(Node*)data;

	if( !_bagView ) return;
	//int grid = obj.grid;
	//int type = obj.type;
	string explain;
	//if( PopManage.getInstance().isViewPop(PopEventName.FIGURE) )
	//{
	//	var contrast:GoodsInfo = RoleManage.getInstance().getSitGridEquip(type);		
	//	explain = contrast==null?null:contrast.explain;
	//}
	//_bagView->_bagCreate.updateTip( grid, explain );
}
