#include "BankMediator.h"
#include "control/AppFacade.h"
#include "control/bank/BankProxyCommand.h"
#include "manager/ViewManager.h"
#include "mvc/Facade.h"

#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "model/com/GoodsDynamicManager.h"
#include "model/com/vo/GoodsDynamic.h"

#include "components/BankGoods.h"
#include "./components/BankView.h"
#include "model/bank/BankProxy.h"
#include "model/backpack/BagProxy.h"
#include "socket/network/GameServerSocket.h"
#include "events/GameDispatcher.h"
#include "manager/PopManage.h"
#include "manager/GlobalManage.h"
#include "socket/command/c16/CCMD166.h"
#include "socket/command/c16/CCMD162.h"
#include "socket/command/c16/CCMD16A.h"
#include "socket/command/c17/CCMD176.h"

const int canDelTypeArr[] = {2,3,4,5};//Can delete type: 2 equipment 3 4 5 gem stones equipment debris pieces

BankMediator::BankMediator():_bankProxy(0),_bankView(0)
{
	_bankProxy = (BankProxy*)g_pFacade->retrieveProxy(AppFacade_BANK_PROXY_CHANGE);

	_dispatcher = GameDispatcher::getInstance();
	_dispatcher->addEventListener(GameDispatcher::BANK_CHANGE, this, callfuncND_selector(BankMediator::packChange));
	_dispatcher->addEventListener(PopEventName::SHOW_UI_BANK, this, callfuncND_selector(BankMediator::bankPopHandle));
}

/*
void BankMediator::initWorldBag(char* data)
{
	sendNotification(Facade_Command, AppFacade_BAG_PROXY_CHANGE, data, BagProxyCommand::CREATE_GOODS_LIST);//这里要通知控制层处理
}
*/
void BankMediator::handleNotification(int M2Vcmd, char* data)
{
	switch(M2Vcmd)
	{
	case CREATE_LIST:
		createList();
		//bagPop();//kktest
		break;
	case BANK_ITEM_UPDATE:
		bankUpdate(data);
		break;
	case BANK_ITEM_TIP_UPDATE:
		updateTip( data );
		break;
	case BANK_CLOSE:
		break;
	default:
		break;
	}
}

void BankMediator::initWorldBank(char* data)
{
	sendNotification(Facade_Command, AppFacade_BANK_PROXY_CHANGE, data, BankProxyCommand::CREATE_GOODS_LIST);//这里要通知控制层处理
}

void BankMediator::bankPop()
{
	if (!_bankView)
	{
		_bankView = new BankView();
		ViewManager::getInstance()->bankView = _bankView;
		_bankView->init();
		startListener();
	}
	openBank();
	g_pGlobalManage->setCurFocusGID(LayerManager::windowLayer->getMyFocusGID());

	if(!_bankProxy->_isCreate)
	{
		CCMD166* s = new CCMD166();
		if (s)
		{
			GameServerSocket* pSocket = GameServerSocket::getInstance();
			if (pSocket)
				pSocket->sendMessage(s);

			
			LayerManager::loadingPic->socketWait_old( WMSG_WORLD_BANK_INIT );
		}
		SAFE_DELETE(s);
	}
	else
	{
		createList();	
	}
}

void BankMediator::startListener()
{
	if (!_bankView)
		return;
	/*背包打开后侦听背包的初始化*/
	//_bagView.addEventListener(BagView.BAG_SORT_CLICK, onSortHandler );	
	_bankView->addEventListener(BankView::BANK_ADD_GRID_CLICK, this, callfuncND_selector(BankMediator::onAddGridHandler));
}

void BankMediator::createList()
{
	if (_bankView && _bankView->getisPop())
	{
		_bankView->OpenBank(_bankProxy->_goodsList, _bankProxy->_noEmpty, _bankProxy->_goodsNumber);
	}	
}

bool BankMediator::isBankViewPop()
{
	if(!_bankView){
		return false;
	}else{
		return _bankView->getisPop();
	}
}

void BankMediator::openBank()
{
	//LH20120108
	if (_bankView)
	{
		_bankView->setisPop(!_bankView->getisPop());
		_bankView->release();
	}
}

/**
	* update  
	* @param arr
	* 
	*/		
void BankMediator::bankUpdate(char* arr)
{
	if (!_bankView || !isBankViewPop()) return;
	_bankView->updateGoods(arr, _bankProxy->_noEmpty);
}




void BankMediator::packChange(CCNode* n, void* data)//int32 UseType, int32 oldGrid, int32 newGrid
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

			CCMD162* s = new CCMD162();
			if (s)
			{
				s->c_oldSit = static_cast<int8>(d.oldGrid);
				s->d_newSit = static_cast<int8>(d.newGrid);
				GameServerSocket* pSocket = GameServerSocket::getInstance();
				if (pSocket)
					pSocket->sendMessage(s);

				
				LayerManager::loadingPic->socketWait_old( WMSG_WORLD_BANK_ITEM_UPDATE );
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

			if(g_pPopManage->isViewPop(PopEventName::BAG))
			{
				bankToBag(e.sitNum);
			}			
		}
//.......and so on
		break;
	default:
		break;
	}
}



/*



		private function packChange(e:ParamEvent):void{
			switch(e.param.UseType){
				case 1://移动格子,发送新、旧位置到服务端
					var cmd:CCMD162=new CCMD162();
					cmd.c_oldSit=new Int8(e.param.oldGrid);
					cmd.d_newSit=new Int8(e.param.newGrid);
					_socket.sendMessage(SocketCMDConst.CMSG_WORLD_BANK_ITEM_UPDATE, cmd);
					break;
				case 2://物品使用或者移动至其他面板
//					var bagMediator:BagMediator = facade.retrieveMediator(BagMediator.NAME) as BagMediator;
//					if(bagMediator.isBagViewPop()){//如果背包已经打开
					if(PopManage.getInstance().isViewPop(PopEventName.BAG)){
						bankToBag(e.param.sitNum);
					}
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
					if(isSelect ||goodsDynamic==null){
						cmdDym = new CCMD16E();
						cmdDym.a_locationType = new Int8(DynamicLocation.BANK);	
						cmdDym.b_sitNum = new Int8(sitGrid);
						cmdDym.c_roleId = RoleManage.getInstance().accountInfo.roleId;
						_socket.sendMessage(SocketCMDConst.CMSG_WORLD_ITEM_INFO, cmdDym);
					}
					break;
			}
		}

*/
void BankMediator::sockBankItemUpdate(std::list<SCMD161_163_165_167Node>*	param)
{
	sendNotification(Facade_Command, AppFacade_BANK_PROXY_CHANGE, (char*)param, BankProxyCommand::UPDATE_GOODS_LIST);//这里要通知控制层处理
}

/**
	*从仓库移到背包
	* @param sitGrid
	* 
	*/		
void BankMediator::bankToBag(int32 sitGrid)
{
	BagProxy* bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
	if (bagProxy && bagProxy->getSpaceGridNum() > 0)
	{
		CCMD16A* cmd2 = new CCMD16A();
		if (cmd2)
		{
			cmd2->a_type = static_cast<int8>(1);
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
		BankGoods* _bankGoods = _bankView->m_pCurSelectedBankGoods;
		if (_bankGoods)
		{
			_bankGoods->reShowItemAndFrame(true);
		}
		//MsgManage.getInstance().showMsg(MsgManage.SYSTEM_MSG, "S251");
	}
}

void BankMediator::bankPopHandle(CCNode* n, void* data)
{
	bankPop();
}

/**
	* 添加格子 
	* @param e
	* 
	*/		
void BankMediator::onAddGridHandler(CCNode* n, void* data)
{
	if (!data) return;
	int32 num = *((int*)data);
	CCMD176* s = new CCMD176();
	if (s)
	{
		s->a_gridType = 2;
		s->b_number = num;
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
        {
            CCLog("Send 0x176 fighting result notice");
			pSocket->sendMessage(s);

			LayerManager::loadingPic->socketWait_old( WMSG_WORLD_BANK_INIT );
        }
	}
	SAFE_DELETE(s);
}

void BankMediator::updateTip( char* data )
{
	struct Node
	{
		int id;
		int grid;
		int type;
	} obj;

	obj = *(Node*)data;

	if( !_bankView ) return;

	//_bankView->bankCreate.updateTip(grid/*,explain*/);
}
