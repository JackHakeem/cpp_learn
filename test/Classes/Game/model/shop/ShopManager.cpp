#include "ShopManager.h"
#include "../dialog/vo/DialogueType.h"


void ShopManager::createShops( ShopVo* pShopVo )
{
	if (!pShopVo) return;

	_shops.insert(  make_pair( pShopVo->npcid, pShopVo )  );
}

ShopVo* ShopManager::getShopsByNPCId( int npcid )
{
	SHOPVOITER it = _shops.find( npcid );

	if ( it != _shops.end() )
	{
		ShopVo* pShopVo =  it->second;
		return pShopVo;
	}

	return NULL;
}

/**
* According to the NPC function get the head of the corresponding specific reference npc_thing ICON, fla
* @ param type
* 1 2 3 4 warehouse stores appointed recruiting 5 mysterious businessman
* 
*/
int ShopManager::getIconByType( int type )
{
	//SHOPVOITER it = _shops.find( type );

	int icon = 0;
	switch(type){
	case SHOP:	// 
		icon = 1;
		break;
	case BANK:	// 
		icon = 3;
		break;
	case APPOINT:		// 
		//if(NewhandManager.getInstance().isOpenButton(NewhandConst.ENABLE_Appoint))
			icon = 5; 
		break;
	case RECRUIT:		// 
		//if(NewhandManager.getInstance().isOpenButton(NewhandConst.ENABLE_RECRUIT))
			icon = 2;
		break;
	case MYSTIC:     // 
		icon = 5;
		break;
	case ARMY:     // 
		icon = 4;
		break;
	case TRADER:      // 
		icon = 6;
		break;
	case COPY:     // 
		icon = 5;
		break;
	}
	return icon + 4; 
}

int ShopManager::getIconByNPCID( int iNPCID )
{

	SHOPVOITER it = _shops.find( iNPCID );

	if ( it != _shops.end() )
	{
		ShopVo* pShopVo =  it->second;
		return getIconByType( pShopVo->type );
	}
	return 0;
}

ShopManager::~ShopManager()
{
	for ( SHOPVOITER it = _shops.begin(); it != _shops.begin(); it++ )
	{
		CC_SAFE_DELETE( it->second );
		it++;
	}
}


//		
//	/**
//		* ���ݲ�ͬ�ĵ�ͼ��ȡ��ͬ����Ʒ  
//		* @param id
//		* @return 
//		* 
//		*/		
//	public function getGoodsByShopId(id:int):Array
//	{
//		if (_shopGoods[id] == undefined)
//		{
//			return null;
//		}
//		return _shopGoods[id] as Array;
//	} 
// 
//	/**
//		* ����npcid��������Ͼ�����Щ������� ����� ��ļ  
//		* @param id
//		* @return 
//		* 
//		*/		
//	public function getShopsByNPCId(npcid:int):Array{
//		if (_shops[npcid] == undefined)
//		{
//			return null;
//		}
//		return _shops[npcid] as Array;
//	} 
//		
//	/**
//		* ��ȡ��ѨNpc 
//		* @return 
//		* 
//		*/		
//	public function getArmyNpc():Array{
//		var arr:Array =[];
//		for each(var obj:Object in _shops){
//			if(obj[0].type==6){
//				arr.push(obj);
//			}
//		}
//		return arr;
//	}
//	/**
//		* ��ȡ����npc 
//		* @return 
//		* 
//		*/		
//	public function getDuplicateNpc():Array{
//		var arr:Array =[];
//		for each(var obj:Object in _shops){
//			if(obj[0].type==8){
//				arr.push(obj);
//			}
//		}
//		return arr;
//	}
//		
//
//	/**
//		* ����NPC���ܻ�ȡ��ͷ����Ӧ��ICON ����ο�npc_thing.fla 
//		* @param type
//		* 1 �̵�    2 �ֿ�   3 ί��     4 ��ļ    5��������
//		* 
//		*/		
//	public function getIconByType(type:int):int{
//		var icon:int = 0;
//		switch(type){
//			case 1:
//				icon = 7;
//				break;
//			case 2:
//				icon = 5;
//				break;
//			case 3:
//				if(NewhandManager.getInstance().isOpenButton(NewhandConst.ENABLE_Appoint))
//					icon = 9;
//				break;
//			case 4:
//				if(NewhandManager.getInstance().isOpenButton(NewhandConst.ENABLE_RECRUIT))
//					icon = 6;
//				break;
//			case 5:
//				icon = 0;
//				break;
//			case 7:
//				icon = 10;
//				break;
//		}
//		return icon; 
//	}
//		
//}