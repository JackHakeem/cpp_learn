
#include "ConfigManager.h"
#include "utils/xml/TinyElementHandler.h"
#include "ConfigManager.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "model/backpack/GoodsManager.h"
#include "../scene/vo/NPCVo.h"
#include "../scene/NPCManager.h"
#include "utils/Singleton.h"
#include "../shop/vo/shopVo.h"
#include "model/shop/ShopManage.h"
#include "../dialog/vo/DialogueVo.h"
#include "../dialog/DialogManager.h"
#include "../com/ResourceManage.h"
#include "../scene/SentenceVo.h"
#include "../scene/SentenceManager.h"
#include "../scene/vo/SceneConst.h"
#include "model/skill/vo/SkillVo.h"
#include "model/skill/SkillManager.h"
#include "../task/TaskManager.h"
#include "../scene/MonsterManager.h"
#include "../scene/vo/ExitVo.h"
#include "../scene/ExitManager.h"
#include "../player/vo/FigureCfgBaseVo.h"
#include "../player/FigureBaseManage.h"
#include "../streng/StrengManage.h"
#include "../shop/ShopManager.h"
#include "../scene/vo/SceneVo.h"
#include "../scene/SceneManager.h"
#include "CCFileUtils.h"
#include "../figure/LevelExpManage.h"
#include "../magic/vo/MagicLimitVo.h"
#include "../magic/MagicManage.h"
#include "../dungeonEntrys/DungeonEntrysManage.h"
#include "../scene/StoryManager.h"
#include "../newhand/vo/StepVo.h"
#include "../newhand/vo/FightLeaderVo.h"
#include "../newhand/NewhandManager.h"
#include "../newhand/vo/ScriptVo.h"
#include "../honor/vo/HonorManage.h"
#include "view/login/components/ServerListVo.h"
#include "LoginManage.h"
#include "model/arena/ArenaManage.h"
#include "../skill/vo/SpeedupVo.h"
#include "../train/vo/TrainManager.h"
#include "../scene/vo/MusicVo.h"
#include "manager/sound/SoundManager.h"
#include "manager/NameManager.h"
#include "../player/PlayerEffectManage.h"
#include "../appoint/vo/AppointBlessVo.h"
#include "../appoint/AppointManager.h"
#include "../newhand/vo/HelpScriptVo.h"
#include "../guild/GuildManager.h"
#include "model/silverMine/vo/BasicMineVo.h"
#include "model/silverMine/SilverMineManage.h"
#include "../vip/VipManager.h"
#include "model/egg/EggManager.h"
#include "model/shop/ItemRiseInfo.h"
#include "../trader/TraderManager.h"
#include "../onlineReward/OnlineRewardManager.h"
#include "model/zx/XHConfManager.h"

ConfigManager* g_pConfigManager = 0;

ConfigManager::ConfigManager()
{

}

ConfigManager::~ConfigManager()
{
	//NPCManager::DestroyInstance();
	//ShopManager::DestroyInstance();
	//DialogManager::DestroyInstance();
	//ResourceManage::DestroyInstance();
	//SentenceManager::DestroyInstance();
	//MonsterManager::DestroyInstance();

}

void ConfigManager::loadConfig()
{
	loadGoodsXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/goods.xml"));//Here the string can't write dead, want to focus in a configuration file, later to join
	loadShopGoodsXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/shopGoods.xml"));
	loadNPCXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/npc.xml"));
	loadShopsXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/shops.xml"));
	loadDialogXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/dialog.xml"));
	loadResXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/resconfig.xml"));
	//loadSkillResXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/skillresconfig.xml"));
	loadSentenceXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/sentence.xml"));
	loadSkillXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/skill.xml"));
	loadMonsterXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/monster.xml"));
	loadMonsterGroupXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/monstergroup.xml"));
	loadGameProgressXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/gameprogress.xml"));
	loadMapExitXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/exit.xml"));
	loadLeveExpXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/leveexp.xml")); // must be loaded before loading Mercenary XML
	loadMercenaryXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/mercenary.xml"));
	loadStrengriseXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/strengrise.xml"));
	loadMapXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/map.xml"));
	loadTaskXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/task.xml"));
	loadEnchantlimitXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/enchantlimit.xml"));
	loadleveSkillXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/leveskill.xml"));
	loadMapEnterXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/mapEnter.xml"));
	loadstorymodelXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/storymodel.xml"));
	loadstoryprogressXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/storyprogress.xml"));
	loadNewhandXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/newhand.xml"));
	loadNewhandHelpXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/newhandhelp.xml"));
	loadNewhandStepXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/newhandStep.xml"));
	loadHonorsXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/honor.xml"));
    //	loadserverlistXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/serverlist.xml"));
	loadArenaXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/arena.xml"));
	loadSpeedupXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/speedup.xml"));
	loadMusicXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/music.xml"));
	loadNameXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/name.xml"));
	loadPlayerAniXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/playerAni.xml"));
	loadAppointBlessXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/appointBless.xml"));
	loadAppointXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/appoint.xml"));
    
	loadGuildLevXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/guildlev.xml"));
	//loadSilverMineXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/silvermine.xml"));
	loadSilverMineXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/silvermine_new.xml"));
	loadVipGiftXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/vipGift.xml"));
    loadEggXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/egg.xml"));
	loadItemRiseInfoXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/itemriseinfo.xml"));

	loadTraderGoodsXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/tradergoods.xml"));
	loadActivityAwardXML( CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/activityAward.xml") );
	loadXHXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/XH.xml"));
	loadXHExpXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/xhexp.xml"));
}  

int32 ConfigManager::loadGoodsXML(const char* filename)
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		//case TiXmlText::TINYXML_TEXT:
		//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);
			

				GoodsBasic* newgood = new GoodsBasic();
				if (!newgood) 
					return 1;

				elehandler.get(newgood->goodId);
				elehandler.get(newgood->goodName);
				elehandler.get(newgood->intro);
				elehandler.get(newgood->throws);
				elehandler.get(newgood->type);

				elehandler.get(newgood->item_type);
				elehandler.get(newgood->equip_type);
				elehandler.get(newgood->icon);
				elehandler.get(newgood->price);
				elehandler.get(newgood->sell_price);
				elehandler.get(newgood->gold_price);

				elehandler.get(newgood->career_id);
				elehandler.get(newgood->level);
				elehandler.get(newgood->hp);
				elehandler.get(newgood->att);
				elehandler.get(newgood->def);

				elehandler.get(newgood->magicAtt);
				elehandler.get(newgood->magicDef);
				elehandler.get(newgood->hit);
				elehandler.get(newgood->dodge);
				elehandler.get(newgood->crit);

				elehandler.get(newgood->back);
				elehandler.get(newgood->suit_id);
				elehandler.get(newgood->max_hole);
				elehandler.get(newgood->max_overlap);
				elehandler.get(newgood->to_goodID);

				elehandler.get(newgood->quality);
				elehandler.get(newgood->growUp);
				elehandler.get(newgood->expire_time);
				elehandler.get(newgood->drop_from);
				elehandler.get(newgood->enchant_Rate);


				//Insert operation


				g_pGoodsManager->addGood(newgood);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadShopGoodsXML(const char* filename)
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		//case TiXmlText::TINYXML_TEXT:
		//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);
			

				ShopGoodsVo shopGoodsVo;

				elehandler.get(shopGoodsVo.shopid);
				elehandler.get(shopGoodsVo.goodsid);

				GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood(shopGoodsVo.goodsid);
				if (goodBasic)
				{
					shopGoodsVo.name = goodBasic->goodName;
					shopGoodsVo.price = goodBasic->price;
					shopGoodsVo.sitGrid=0;
				}
				else
				{
					shopGoodsVo.name = "";
					shopGoodsVo.price = 0;
					shopGoodsVo.sitGrid = 0;
				}

				//Insert operation
				g_pShopManage->createGoods(shopGoodsVo.shopid, shopGoodsVo);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadNPCXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	NPCManager* pNPCManager = NPCManager::Instance();
	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);


				NPCVo* pNPCVo = pNPCManager->allocVo();
				if (!pNPCVo) 
					return 1;
				//  <item id="1" resid="117" mapid="1001" name="????" leve="1" x="44" y="40" state="1" otherInfos="1" rank="0" /> 

				int iResid( 0 ), iMapid ( 0 );
				uint uLevel( 0 );

				elehandler.get(pNPCVo->id);
				elehandler.get(iResid);
				pNPCVo->setResId(iResid);
				elehandler.get(iMapid);
				pNPCVo->setMapId(iMapid);
				elehandler.get(pNPCVo->name);
				elehandler.get(uLevel);
				pNPCVo->setLevelId(uLevel);
				elehandler.get(pNPCVo->x);
				elehandler.get(pNPCVo->y);
				elehandler.get(pNPCVo->state);
				elehandler.get(pNPCVo->otherInfos);

				elehandler.get(pNPCVo->action);
				if ( pNPCVo->action == 0 )
				{
					pNPCVo->action = SceneConst::TALK;
				}
				else if(pNPCVo->action == 1)
				{
					pNPCVo->action = SceneConst::FIGHT;
				}
				else
				{
					pNPCVo->action = SceneConst::WANDER;
				}

				//cocos2d::CCLog( pNPCVo->name.c_str() );
				//Insert operation
				pNPCManager->setNPC(pNPCVo);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}


//Read GPH 2012.3.26 monster. XML data is MonsterManager member variables of
int32 ConfigManager::loadMonsterXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	MonsterManager* pMonsterManager =  MonsterManager::Instance();
	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);


				NPCVo* pNPCVo = pMonsterManager->allocVo();
				if (!pNPCVo) 
					return 1;
				//  <item id="1" resid="202.0" type="2" name="??????" leve="1" hp="12" mp="100" skill1="463" skill2="0" /> 

				int iResid( 0 );//, iMapid ( 0 );
				uint uLevel( 0 );
			 

				elehandler.get(pNPCVo->id);
				elehandler.get(iResid);
				pNPCVo->setResId(iResid);
				elehandler.get(pNPCVo->typeId);
				elehandler.get(pNPCVo->name);
				elehandler.get(uLevel);
				pNPCVo->setLevelId(uLevel);
				elehandler.get(pNPCVo->_hp);
				elehandler.get(pNPCVo->_mp);
				elehandler.get(pNPCVo->skill1);
				elehandler.get(pNPCVo->skill2);
				elehandler.get(pNPCVo->skill3);
				////Test read
				//cocos2d::CCLog( pNPCVo->name.c_str() );
				//Insert operation

				// add by L.H. 0703
				pNPCVo->_maxHp = pNPCVo->_hp;
				pNPCVo->_maxMp = pNPCVo->_mp;

				pMonsterManager->setMonsters(pNPCVo);
			}
			break;
		default:
			break;
		}

	}
	 
	return 0;
}



//GPH 2012.3.26 read monstergroup. XML data is MonsterManager member variables of
int32 ConfigManager::loadMonsterGroupXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	MonsterManager* pMonsterManager =  MonsterManager::Instance();
	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				NPCVo* pNPCVo = pMonsterManager->allocVo();
				if (!pNPCVo) 
					return 1;
				//  <item id="1" resid="202" name="??????" formId="24" leve="1" groupinfo="0|0|0|0|1|0|0|0|0" groupLev="1" exp="6" dropItem="0" /> 
				int tmpResid(0);
				
				elehandler.get(pNPCVo->id);  //Here is actually groupid id......
				elehandler.get(tmpResid);
				pNPCVo->setResId(tmpResid);
				elehandler.get(pNPCVo->name);
				elehandler.get(pNPCVo->formId);
				elehandler.get(pNPCVo->_lev);
		         elehandler.get(pNPCVo->forInfo);
				elehandler.get(pNPCVo->groupLev);
				elehandler.get(pNPCVo->GroupExp);
				elehandler.get(pNPCVo->DropGoods);
				////Test read
				//cocos2d::CCLog( pNPCVo->name.c_str() );
				//Insert operation
			  pMonsterManager->setMonsterGroup(pNPCVo);
			}
			break;
		default:
			break;
		}

	}
	 
	return 0;
}


int32 ConfigManager::loadGameProgressXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	MonsterManager* pMonsterManager =  MonsterManager::Instance();
	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);


				 GMProgressVo* gmproVo=new GMProgressVo();
				if (!gmproVo) 
					return 1;
				//  <item id="1002" mapId="1051" mgId="594" x="20" y="35" /> 

                 elehandler.get(gmproVo->id);
				 elehandler.get(gmproVo->mapId);
				 elehandler.get(gmproVo->mgId);
				 elehandler.get(gmproVo->x);
				 elehandler.get(gmproVo->y);

				 
				////Test read
				//cocos2d::CCLog( "gmprogress id is %d",gmproVo->id);
				//Insert operation
				pMonsterManager->setGMProgess(gmproVo);
			}
			break;
		default:
			break;
		}

	}

	//Test read
//	pMonsterManager->_mapGMonstersDic;
 
	return 0;
}



int32 ConfigManager::loadShopsXML(const char* filename)
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		//case TiXmlText::TINYXML_TEXT:
		//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);
			

				ShopVo* shopVo = new ShopVo();
				if (!shopVo) 
					return 1;

				elehandler.get(shopVo->npcid);
				elehandler.get(shopVo->name);
				elehandler.get(shopVo->otherinfos);
				elehandler.get(shopVo->type);

				//Insert operation
				g_pShopManage->createShops(shopVo->npcid, *shopVo);
				ShopManager::Instance()->createShops(shopVo);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}






int32 ConfigManager::loadDialogXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	DialogManager* pDialogManager = DialogManager::Instance();
	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);


				DialogueVo* pDialogueVo = pDialogManager->allocVo();
				if (!pDialogueVo) 
					return 1;
				//<item id="1" content="????????<?§Õ??????????????????????????????????¡ã???"/>

				elehandler.get(pDialogueVo->id);
				elehandler.get(pDialogueVo->content);

				//Insert operation
				pDialogManager->setDialogs(pDialogueVo);
			}
			break;
		default:
			break;
		}
	}

	return 0;
}

int32 ConfigManager::loadResXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	ResourceManage* pResourceManage = ResourceManage::Instance();
	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				ResourceVo* pResourceVo = pResourceManage->allocVo();
				if (!pResourceVo) 
					return 1;
				//	<item type="1" id="1" timer="84" namey="-120"/>

				elehandler.get(pResourceVo->type);
				elehandler.get(pResourceVo->id);
				elehandler.get(pResourceVo->timer);
				elehandler.get(pResourceVo->nameY);
				elehandler.get(pResourceVo->actzhen);
				int intActime = 0;
				elehandler.get(intActime);
				pResourceVo->acttime = (float)intActime/10.0f;

				//
				

				string offsetBuffer;
				elehandler.get(offsetBuffer);
				vector<std::string> splitStr;
				splitStringByCharacterEx(offsetBuffer, "|", splitStr);

				for (int i = 0 ; i < splitStr.size(); i++)
				{
					if (splitStr[i].size() != 8)//action dir +-value  +-value
					{
						CCLog("read model:%d offset error!!!!!!", pResourceVo->id);
						continue;
					}
					char valueStr[9] = {0};
					strcpy(valueStr, splitStr[i].c_str());
					valueStr[8] = '\0';


					int action = (int)(valueStr[0])-48;
					int dir = (int)(valueStr[1])-48;
					int zhengfu = (int)(valueStr[2])-48;
					ResVoPoint value;
					value.x = (int)(valueStr[3])-48;
					value.x = value.x*10 + ((int)(valueStr[4])-48);
					if (zhengfu == 1) value.x *= -1;

					zhengfu = (int)(valueStr[5])-48;
					value.y = (int)(valueStr[6])-48;
					value.y = value.y*10 + ((int)(valueStr[7])-48);
					if (zhengfu == 1) value.y *= -1;

					pResourceVo->offset[action*8+dir] = value;
				}

				//Insert operation
				pResourceManage->setRes(pResourceVo);
			}
			break;
		default:
			break;
		}
	}

	return 0;
}

int32 ConfigManager::loadSkillResXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	ResourceManage* pResourceManage = ResourceManage::Instance();
	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				ResourceVo* pResourceVo = pResourceManage->allocVo();
				if (!pResourceVo) 
					return 1;
				//<item type="2" id="1" timer="84" blendMode="normal"/>

				elehandler.get(pResourceVo->type);
				elehandler.get(pResourceVo->id);
				elehandler.get(pResourceVo->timer);
				elehandler.get(pResourceVo->blendMode);

				//Insert operation
				pResourceManage->setRes(pResourceVo);
			}
			break;
		default:
			break;
		}
	}

	return 0;
}

int32 ConfigManager::loadSentenceXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	SentenceManager* pSentenceManager = SentenceManager::Instance();

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				SentenceVo* pSentenceVo = pSentenceManager->allocVo();
				if (!pSentenceVo) 
					return 1;
				//<item id="1" type="1" content="?????????????????§Ñ????????????????/06" mapId="1052" otherinfos="1007"/>

				elehandler.get(pSentenceVo->id);
				elehandler.get(pSentenceVo->type);
				elehandler.get(pSentenceVo->content);
				elehandler.get(pSentenceVo->mapId);
				elehandler.get(pSentenceVo->otherInfo);

				//Insert operation
				pSentenceManager->setSentence(pSentenceVo);
			}
			break;
		default:
			break;
		}
	}

	return 0;
}


int32 ConfigManager::loadSkillXML(const char* filename)
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	
	std::vector<SkillVo> skillVoList;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		//case TiXmlText::TINYXML_TEXT:
		//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);
			
				SkillVo skillVo;
				//int nameid(0);//iLevel(0),  musid(0), 

				elehandler.get(skillVo.id);
				elehandler.get(skillVo.resId);
				elehandler.get(skillVo.pListId);
				elehandler.get(skillVo.name);
				
				elehandler.get(skillVo.longAttack);
				elehandler.get(skillVo.rank);

				elehandler.get(skillVo.icon);

				//elehandler.get(skillVo.level);
				//elehandler.get(iLevel);

				elehandler.get(skillVo.des);

				elehandler.get(skillVo.musid);
				//elehandler.get(musid);

				elehandler.get(skillVo.nameid);

				elehandler.get(skillVo.shift);
				elehandler.get(skillVo.combo);
                
                elehandler.get(skillVo.actzhen);
                
                int acttimeTMP = 0;
                elehandler.get(acttimeTMP);
                skillVo.acttime = acttimeTMP/100.0f;

				int iOffsetX = 0;
				elehandler.get(iOffsetX);
				skillVo.offsetX = iOffsetX/*/100.0f*/;

				int iOffsetY = 0;
				elehandler.get(iOffsetY);
				skillVo.offsetY = iOffsetY/*/100.0f*/;

				int iOffsetX2 = 0;
				elehandler.get(iOffsetX2);
				skillVo.offsetX2 = iOffsetX2/*/100.0f*/;

				int iOffsetY2 = 0;
				elehandler.get(iOffsetY2);
				skillVo.offsetY2 = iOffsetY2/*/100.0f*/;

				elehandler.get(skillVo.flipX);

				elehandler.get(skillVo.flipY);

				
				int scale = 0;
				elehandler.get(scale);
				skillVo.scale = scale/100.0f;
				
				skillVoList.push_back(skillVo);
				//Insert operation
				

			}
			break;
		default:
			break;
		}
	}

	SkillManager::Instance()->createSkill(&skillVoList);

	return 0;
}

int32 ConfigManager::loadTaskXML( const char* filename )
{

	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;

	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);


				TaskVo *taskVo = new TaskVo();

				elehandler.get(taskVo->_id);
				elehandler.get(taskVo->_level);
				elehandler.get(taskVo->_frontTaskId);
				elehandler.get(taskVo->_type);
				elehandler.get(taskVo->_askType);
				elehandler.get(taskVo->_taskName);
				elehandler.get(taskVo->_description);
				elehandler.get(taskVo->_copper);
				elehandler.get(taskVo->_gold);
				elehandler.get(taskVo->_dificulty);
				elehandler.get(taskVo->_experience);
				elehandler.get(taskVo->_lifeExperiences);
				elehandler.get(taskVo->_energy);

				std::string fixGoodsStr;
				elehandler.get(fixGoodsStr);
				taskVo->setFixGoods(fixGoodsStr);
				
				std::string dialogsStr;
				elehandler.get(dialogsStr);
				taskVo->setDialogs(dialogsStr);

				std::string taskTipsStr;
				elehandler.get(taskTipsStr);
				taskVo->setTaskTips(taskTipsStr);

				std::string npcsStr;
				elehandler.get(npcsStr);
				taskVo->setNPCs(npcsStr);

				// Do not use this string.
				std::string ignoreStr;
				elehandler.get(ignoreStr);

				std::string storysStr;
				elehandler.get(storysStr);
				taskVo->setStorys(storysStr);
				/*cocos2d::CCLog("fixGoodsStr=%s", fixGoodsStr.c_str());
				cocos2d::CCLog("dialogsStr=%s", dialogsStr.c_str());
				cocos2d::CCLog("taskTipsStr=%s", taskTipsStr.c_str());
				cocos2d::CCLog("npcsStr=%s", npcsStr.c_str());
				cocos2d::CCLog("storysStr=%s", storysStr.c_str());*/
				TaskManager::Instance()->setTask(taskVo);
			}
			break;
		default:
			break;
		}
	}
    return -1;
}


int32 ConfigManager::loadMapExitXML(const char* filename)
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);


				ExitVo exitVo;
				std::string otherinfo;
				elehandler.get(exitVo._id);
				elehandler.get(exitVo._resId);
				elehandler.get(exitVo._name);
				elehandler.get(exitVo._mapId);
				elehandler.get(exitVo.x);
				elehandler.get(exitVo.y);
				elehandler.get(otherinfo);
				
				char tmp_char[32];
				int i = 0;
				sprintf(tmp_char, "%s", otherinfo.c_str());
				//int j=0;
				char *token;
				token = strtok( tmp_char, "|" );
				while( token != NULL )
				{
					i = atoi(token);
					exitVo.otherInfo(i);
					token = strtok( NULL, "|" ); 
				}

				ExitManager::Instance()->setExit(exitVo);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadMercenaryXML(const char* filename)
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				std::string recommend("");
				std::string selected("");

				FigureCfgBaseVo figureCfgBaseVo;
				elehandler.get(figureCfgBaseVo.mercId);
				int rank = 0;
				elehandler.get(rank);
				figureCfgBaseVo.isRole = (rank == 1 ? true : false);
				elehandler.get(figureCfgBaseVo.name);
				elehandler.get(figureCfgBaseVo.sex);
				elehandler.get(figureCfgBaseVo.color);
				elehandler.get(figureCfgBaseVo.careerId);
				elehandler.get(figureCfgBaseVo.strength);
				elehandler.get(figureCfgBaseVo.intellect);
				elehandler.get(figureCfgBaseVo.hitRate);
				elehandler.get(figureCfgBaseVo.agility);
				elehandler.get(figureCfgBaseVo.crit);
				elehandler.get(figureCfgBaseVo.stamina);
				elehandler.get(figureCfgBaseVo.needPop);
				elehandler.get(figureCfgBaseVo.cloth);
				//figureCfgBaseVo.cloth = figureCfgBaseVo.mercId;// Jae change
				//int avartar;
				//elehandler.get(figureCfgBaseVo.avartar);
				elehandler.get(figureCfgBaseVo.exp);

				//elehandler.get(figureCfgBaseVo.requirement);//jae note 20120723
				std::string req("");
				elehandler.get( req );
				std::vector<std::string> reqVec = splitStringByCharacter(req,"|");
				if ( reqVec.size() > 1 )
				{
					figureCfgBaseVo.requirement = std::string(reqVec[1].c_str());
				} 
				else
				{
					figureCfgBaseVo.requirement = "";
				}
				

				elehandler.get(figureCfgBaseVo.silver);

				elehandler.get(recommend);
				std::vector<std::string> recommedVector = splitStringByCharacter(recommend,"|");
				std::vector<std::string>::iterator iter1 = recommedVector.begin();
				for (;iter1 != recommedVector.end();iter1++)
				{
					figureCfgBaseVo.recommend.push_back(atoi((*iter1).c_str()));
				}

				elehandler.get(selected);
				std::vector<std::string> selectedVector = splitStringByCharacter(selected,"|");
				std::vector<std::string>::iterator iter2 = selectedVector.begin();
				for (;iter2 != selectedVector.end();iter2++)
				{
					figureCfgBaseVo.selected.push_back(atoi((*iter2).c_str()));
				}

				elehandler.get(figureCfgBaseVo.explanation);
				elehandler.get(figureCfgBaseVo.score);

				std::string skill1;
				elehandler.get(skill1);
				string t1 = skill1.substr( 0, skill1.find_first_of("|") );
				int iSkill = atoi( t1.c_str() );
				figureCfgBaseVo.skill1.push_back(iSkill);
				t1 = skill1.substr( skill1.find_first_of("|")+1, skill1.find('\0'));
				iSkill = atoi( t1.c_str() );
				figureCfgBaseVo.skill1.push_back(iSkill);

				elehandler.get(figureCfgBaseVo.skill2);

				//std::map<int, LevelExpVo> * expdic = &LevelExpManage::Instance()->_expDic;
				figureCfgBaseVo.lev = LevelExpManage::Instance()->getLevByExp(figureCfgBaseVo.exp);
				//Insert operation
				FigureBaseManage::Instance()->setMercenaryDic(&figureCfgBaseVo);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadStrengriseXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	StrengManage* pStrengManage = StrengManage::Instance();

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				StrengRise* pStrengRise = pStrengManage->allocVo();
				if (!pStrengRise) 
					return 1;
				//<item gradeleve="1" equippos="1" growup="2" phygrowup="0" maggrowup="1" smalltype="1"/>

				elehandler.get(pStrengRise->gradeLevel);
				elehandler.get(pStrengRise->equipPos);
				elehandler.get(pStrengRise->growUp);
				elehandler.get(pStrengRise->phygrowUp);
				elehandler.get(pStrengRise->maggrowUp);
				elehandler.get(pStrengRise->smallType);

				//Insert operation
				pStrengManage->createStrengRise(pStrengRise);
			}
			break;
		default:
			break;
		}
	}

	return 0;
}


int32 ConfigManager::loadMapXML(const char* filename)
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);


				SceneVo sceneVo;

				elehandler.get(sceneVo.id);
				elehandler.get(sceneVo.mapResId);
				elehandler.get(sceneVo.name);
				elehandler.get(sceneVo.x);
				elehandler.get(sceneVo.y);
				elehandler.get(sceneVo.resid);
				elehandler.get(sceneVo.type);
				elehandler.get(sceneVo.pid);
				elehandler.get(sceneVo.preId);
				elehandler.get(sceneVo.nextId);
				elehandler.get(sceneVo.remark);
				elehandler.get(sceneVo.timeLim);

				//Insert operation
				SceneManager::Instance()->setMapDic(&sceneVo);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadLeveExpXML(const char* filename)
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);


				std::map<int, LevelExpVo> * expdic = &LevelExpManage::Instance()->_expDic;
				LevelExpVo levExp;
				int id = 0;
				elehandler.get(id);
				elehandler.get(levExp.needExp);
				elehandler.get(levExp.countExp);

				//Insert operation
				expdic->insert(make_pair(id,levExp));
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadEnchantlimitXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				MagicLimitVo* magicLimitVo = MagicManage::Instance()->allocVo();
				elehandler.get(magicLimitVo->equipType);
				elehandler.get(magicLimitVo->quality);
				elehandler.get(magicLimitVo->equipLevel);
				elehandler.get(magicLimitVo->stamina);
				elehandler.get(magicLimitVo->wrist);
				elehandler.get(magicLimitVo->intellect);
				elehandler.get(magicLimitVo->crystalLev);

				//Insert operation
				MagicManage::Instance()->createMagicInfo( magicLimitVo );
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadleveSkillXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				LevSkillVo levSkillVo;
				elehandler.get(levSkillVo.id);
				elehandler.get(levSkillVo.lev);
				elehandler.get(levSkillVo.roleLevel);
				elehandler.get(levSkillVo.skillEXP);
				elehandler.get(levSkillVo.cdTime);
				std::string sParam("");
				elehandler.get(sParam);
				if (sParam != "")
				{
					int ret = sParam.find("|");
					if (ret >= 0)
					{
						vector<std::string> splitStr;//= splitStringByCharacter(sParam,"|");
						splitStringByCharacterEx(sParam, "|", splitStr);

						while (!splitStr.empty())
						{
							levSkillVo.arrParam.push_back(atoi(splitStr.front().c_str()));
							splitStr.erase(splitStr.begin());
						}

						elehandler.get(levSkillVo.silver);
					}
					else
					{
						levSkillVo.silver = atoi(sParam.c_str());
						//levSkillVo.arrParam.push_back(atoi(sParam.c_str()));
					}
				}
				//elehandler.get(levSkillVo.silver);
				elehandler.get(levSkillVo.prevSkillID);
				elehandler.get(levSkillVo.prevSkillLevel);
				elehandler.get(levSkillVo.des);

				std::map<int, LevSkillVo> _levSkill;
				std::map<int, std::map<int, LevSkillVo> > * _LevSkillDic = &SkillManager::Instance()->_levSkillDic;
				std::map<int, std::map<int, LevSkillVo> >::iterator iter = _LevSkillDic->find(levSkillVo.id);
				std::map<int, LevSkillVo> *list;
				bool bNeedInsert = false;
				if (iter != _LevSkillDic->end())
				{
					list = &iter->second;
				}
				else
				{
					list = &_levSkill;
					bNeedInsert = true;
				}
				list->insert(make_pair(levSkillVo.lev,levSkillVo));
				
				if (bNeedInsert)
				{
					_LevSkillDic->insert(make_pair(levSkillVo.id,*list));
				}				
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadMapEnterXML(const char* filename)
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				int city = 0;
				std::string str;
				elehandler.get(city);
				elehandler.get(str);

				char tmp_char[128];
				int i = 0;
				sprintf(tmp_char, "%s", str.c_str());
				std::vector<int> maps;
				//int j = 0;
				char *token;
				token = strtok( tmp_char, ",");
				while(token != NULL)
				{
					i = atoi(token);
					maps.push_back(i);
					token = strtok( NULL, ",");
				}
				DungeonEntrysManage::Instance()->setDungeonEntrysCfg(city, maps);
			}
			break;

		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadNewhandXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	NewhandManager *pNewhandManager = NewhandManager::Instance();

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);
				
				string id, task, clear, trigger, loc, locId, draw, next_id, info;
				elehandler.get(id);
				elehandler.get(task);
				elehandler.get(clear);
				elehandler.get(trigger);
				elehandler.get(loc);
				elehandler.get(locId);
				elehandler.get(draw);
				elehandler.get(next_id);
				elehandler.get(info);

				ScriptVo *pScript = new ScriptVo();
				pScript->id = atoi(id.c_str());
				pScript->taskId = atoi(task.c_str());
				pScript->clear = atoi(clear.c_str());
				//pScript->trigger = this->splitStringByCharacter(trigger, "|");
				splitStringByCharacterEx(trigger, "|", pScript->trigger);
				pScript->loc = loc;
				pScript->locId = atoi(locId.c_str());
				pScript->next_id = atoi(next_id.c_str());
				pScript->info = info;
				//std::vector<string> drawVector = this->splitStringByCharacter(draw, "|");
				std::vector<string> drawVector;
				splitStringByCharacterEx(draw, "|", drawVector);
				pScript->arrow = atoi(drawVector[0].c_str());
				pScript->locType = atoi(drawVector[1].c_str());
				pScript->typeId = atoi(drawVector[2].c_str());
				if(drawVector.size() <= 3)
				{
					pScript->isFlyEffect = false;
				}
				else
				{
					pScript->isFlyEffect = (atoi(drawVector[3].c_str()) == 1) ? true : false;
				}
				pNewhandManager->addScript(pScript);
				
			}
			break;

		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadNewhandHelpXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	NewhandManager *pNewhandManager = NewhandManager::Instance();

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);
				
				HelpScriptVo * pScript = new HelpScriptVo();
				elehandler.get(pScript->id);
				elehandler.get(pScript->type);
				elehandler.get(pScript->processid);
				elehandler.get(pScript->bodyid);
				elehandler.get(pScript->title);
				elehandler.get(pScript->content);
				elehandler.get(pScript->btntxt);
				elehandler.get(pScript->isBtnShow);
				elehandler.get(pScript->newhandid);

				std::string strAction("");
				elehandler.get(strAction);
				std::vector<std::string> vec = splitStringByCharacter(strAction , "|");
				std::vector<std::string>::iterator iter = vec.begin();
				for (; iter != vec.end() ; iter++)
				{
					pScript->action.push_back(string2Int(*iter));
				}
				
				elehandler.get(pScript->isIgnore);
				elehandler.get(pScript->AutoPop);

				pNewhandManager->addNewHandHelpScript(pScript);

			}
			break;

		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadstorymodelXML( const char* filename )
{
	if (!filename)
		return 1;
	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				// add code here
				StoryModelVo storyModelVo;
				elehandler.get(storyModelVo.id);
				elehandler.get(storyModelVo.resid);
				elehandler.get(storyModelVo.name);
				StoryManager::Instance()->setStoryModel(&storyModelVo);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadstoryprogressXML( const char* filename )

{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				// add code here
				StoryVo storyVo;
				elehandler.get(storyVo.id);

				std::string szElement("");
				elehandler.get(szElement);
				storyVo.elemenet = StoryManager::Instance()->createElemenet(szElement);

				std::string szScript("");
				elehandler.get(szScript);
				storyVo.script = StoryManager::Instance()->createScript(szScript);

				elehandler.get(storyVo.x);
				elehandler.get(storyVo.y);

				StoryManager::Instance()->setStorys(&storyVo);		
			}
			break;
		default:
			break;
		}
	}

	StoryManager::Instance()->setStoryScriptType();

	return 0;
}

int32 ConfigManager::loadNewhandStepXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  
	
	NewhandManager *pNewhandManager = NewhandManager::Instance();

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				string trigger, param, info;
				//std::vector<std::string> triggerArr;
				elehandler.get(trigger);
				elehandler.get(param);
				elehandler.get(info);

				StepVo *pStep = new StepVo();

				pStep->setTrigger(trigger);

				pStep->setParam(param);

				pStep->btnId = atoi(pStep->param[0].c_str());
				pStep->btnSit = atoi(pStep->param[1].c_str());
				pStep->info = info;
				//triggerArr.clear();
				pNewhandManager->addStep(pStep);

			}
			break;

		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadserverlistXML( const char* filename )

{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				// add code here
				ServerListVo servListVo;
				elehandler.get(servListVo.areaID);
				elehandler.get(servListVo.areaName);
				elehandler.get(servListVo.serverID);
				elehandler.get(servListVo.servName);
				elehandler.get(servListVo.ip);

				int port;
				elehandler.get(port);
				servListVo.port = port & 0x0000ffff;

				std::map<int/*servID*/,ServerListVo> servListVoMap;
				servListVoMap.insert(make_pair(servListVo.serverID,servListVo));

				std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> > *_serverListVoDic = &g_pLoginManage->_serverListVoDic;
				std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> >::iterator iter = _serverListVoDic->find(servListVo.areaID);
				if (iter != _serverListVoDic->end())
				{
					iter->second.insert(make_pair(servListVo.serverID,servListVo));
				}
				else
				{
					_serverListVoDic->insert(make_pair(servListVo.areaID,servListVoMap));
				}
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

void ConfigManager::splitStringByCharacterEx(string o_str, char* sCharacter, std::vector<std::string>& dst)
{
	int size = o_str.size();

	char* sentence;//[1000];
	sentence = new char[size+1];
	strncpy(sentence, o_str.c_str(), o_str.size());
	sentence[o_str.size()] = '\0';

	string value;
	char *tokenPtr=strtok(sentence, sCharacter);

	
	while(tokenPtr != 0)
	{
		value = tokenPtr;
		dst.push_back(value);

		tokenPtr=strtok(0, sCharacter);
		
	}

	SAFE_DELETE_ARRAY(sentence);
}


std::vector<std::string> ConfigManager::splitStringByCharacter( string o_str, string sCharacter )
{
	std::vector<std::string> str_list; // ??????????
	//int comma_n = 0;
	do
	{
		std::string tmp_s = "";
		int comma_n = o_str.find( sCharacter );
		if( -1 == comma_n )
		{
			tmp_s = o_str.substr( 0, o_str.length() );
			str_list.push_back( tmp_s );
			break;
		}
		tmp_s = o_str.substr( 0, comma_n );
		o_str.erase( 0, comma_n+1 );
		str_list.push_back( tmp_s );
	}
	while(true);
	return str_list;
}

int32 ConfigManager::loadHonorsXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	HonorManage *pHonorManage = HonorManage::Instance();

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);
				//<item type="16" bigid="2" honorsid="115" honorsname="¨¨?????" 
				//reward="10" title="" reamark="???????1????¨¢?????¨¨" goods="1:10|2:2000" map="1052|3" enabled="1" /> 

				int iTemp(0);
				string strTemp;
				HonorGoodVo* pHonorGoodVo = new HonorGoodVo();
				elehandler.get(iTemp);//type
				elehandler.get(iTemp);//bigID
				elehandler.get(pHonorGoodVo->honorsid);
				elehandler.get(strTemp);//honorsname
				elehandler.get(iTemp);//reward
				elehandler.get(strTemp);//title
				elehandler.get(strTemp);//reamark

				elehandler.get(strTemp);	// goods="1:10|2:2000"
				vector<std::string> goodsVector;// = splitStringByCharacter( strTemp, "|" );
				splitStringByCharacterEx( strTemp, "|" ,goodsVector);
				for ( int i = 0; i < goodsVector.size(); i++ )
				{
					AwardThing awardGood;
					string temp = goodsVector[i];
					char txt[54];
					vector<std::string> goodsItem;// = splitStringByCharacter( temp, ":" );
					splitStringByCharacterEx( temp, ":" ,goodsItem);
					sprintf( txt, "%s", goodsItem[0].c_str() );
					awardGood.type = atoi( txt );
					sprintf( txt, "%s", goodsItem[1].c_str() );
					awardGood.numbers = atoi( txt );
					pHonorGoodVo->goods.push_back( awardGood );
				}

				elehandler.get(strTemp);	// map="1052|3"
				vector<std::string> mapStr;// = splitStringByCharacter( strTemp, "|" );
				splitStringByCharacterEx( strTemp, "|" , mapStr);
				if ( mapStr.size() == 2 )
				{
					pHonorGoodVo->m_map = atoi(mapStr[0].c_str());
					pHonorGoodVo->taskId = atoi(mapStr[1].c_str());
				}
				elehandler.get(iTemp);

				pHonorManage->createHonors( pHonorGoodVo );
			}
			break;

		default:
			break;
		}
	}
	return 0;
}


int32 ConfigManager::loadArenaXML(const char* filename)
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		//case TiXmlText::TINYXML_TEXT:
		//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);
			

				CfgRankVo newgood;
				std::string interests;

				elehandler.get(newgood.rank);
				elehandler.get(newgood.silver);
				elehandler.get(newgood.pop);
				elehandler.get(interests);
				//Insert operation
				
				std::vector<std::string> tmpv;//= this->splitStringByCharacter(interests,"|");
				splitStringByCharacterEx(interests,"|", tmpv);
				for (int i = 0; i < tmpv.size(); i++)
				{
					int v = atoi(tmpv[i].c_str());
					newgood.interests.push_back(v) ;
				}

				ArenaManage::Instance()->_cfgArenaDic.insert(std::make_pair(newgood.rank, newgood));
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadSpeedupXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	std::map< int, SpeedupVo* > _speedupDic;
	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				SpeedupVo* pSpeedupVo = new SpeedupVo();

				elehandler.get( pSpeedupVo->crystalLev );
				elehandler.get( pSpeedupVo->speedup );

				_speedupDic.insert( make_pair( pSpeedupVo->crystalLev, pSpeedupVo ) );
			}
			break;

		default:
			break;
		}
	}

	TrainManager::Instance()->setSpeedupDic( _speedupDic );

	return 0;
}

int32 ConfigManager::loadMusicXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;

	std::map<int/*type*/,std::map<int/*mapId*/,MusicVo*> > typeDic;
	std::map<int/*type*/,std::map<int/*mapId*/,MusicVo*> >::iterator iter;

	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				MusicVo * pMusicVo = new MusicVo;
				elehandler.get( pMusicVo->type );
				elehandler.get( pMusicVo->mapId );
				elehandler.get( pMusicVo->musicId );
				std::map<int/*mapid*/,MusicVo*> mapMusic;
				mapMusic.insert(make_pair(pMusicVo->mapId, pMusicVo));
				iter = typeDic.find(pMusicVo->type);
				if (iter != typeDic.end())
				{
					iter->second.insert(make_pair(pMusicVo->mapId,pMusicVo));
				}
				else
				{
					typeDic.insert(make_pair(pMusicVo->type,mapMusic));
				}
			}
			break;

		default:
			break;
		}
	}

	SoundManager::Instance()->setMusic( typeDic );

	return 0;
}

int32 ConfigManager::loadNameXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	std::map< int, SpeedupVo* > _speedupDic;
	TiXmlNode* pNode = NULL;

	std::map<int/*type*/,std::map<int/*mapId*/,MusicVo*> > typeDic;
	std::map<int/*type*/,std::map<int/*mapId*/,MusicVo*> >::iterator iter;

	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);
				int type = 0;
				std::string name;
				elehandler.get( type );
				elehandler.get( name );
				std::vector<string> namelist;// = this->splitStringByCharacter(name,",");
				splitStringByCharacterEx(name,",", namelist);
				switch (type)
				{
				case 110:
					Namemanager::Instance()->_firstMale.insert(make_pair(type,namelist));
					break;
				case 120:
					Namemanager::Instance()->_firstFemale.insert(make_pair(type,namelist));
					break;
				case 21:
					Namemanager::Instance()->_secondNoThirdMale.insert(make_pair(type,namelist));
					break;
				case 22:
					Namemanager::Instance()->_secondNoThirdFemale.insert(make_pair(type,namelist));
					break;
				case 210:
					Namemanager::Instance()->_secondMale.insert(make_pair(type,namelist));
					break;
				case 220:
					Namemanager::Instance()->_secondFemale.insert(make_pair(type,namelist));
					break;
				case 310:
					Namemanager::Instance()->_thirdMale.insert(make_pair(type,namelist));
					break;
				case 320:
					Namemanager::Instance()->_thirdFemale.insert(make_pair(type,namelist));
					break;
				default:
					break;
				}
			}
			break;

		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadPlayerAniXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	std::map< int, SpeedupVo* > _speedupDic;
	TiXmlNode* pNode = NULL;

	std::map<int/*type*/,std::map<int/*mapId*/,MusicVo*> > typeDic;
	std::map<int/*type*/,std::map<int/*mapId*/,MusicVo*> >::iterator iter;

	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);
				
				PlayerEffectInfoVo *aniInfo = new PlayerEffectInfoVo();
				elehandler.get(aniInfo->_type);
				elehandler.get(aniInfo->_path);
				elehandler.get(aniInfo->_name);
				elehandler.get(aniInfo->_nFrameCount);
				int time;
				elehandler.get(time);
				aniInfo->_time = (float)time/1000.0f;
				elehandler.get(aniInfo->_x);
				elehandler.get(aniInfo->_y);
				PlayerEffectManage::Instance()->setAniInfo(aniInfo);
			}
			break;

		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadAppointXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				AppointVo *pAppoint = new AppointVo();
				
				std::string id, type, lev, silver, gold, icon, info;
				elehandler.get(id);
				elehandler.get(type);
				elehandler.get(lev);
				elehandler.get(pAppoint->name);
				elehandler.get(silver);
				elehandler.get(gold);
				elehandler.get(icon);
				elehandler.get(pAppoint->info);
				pAppoint->id = atoi(id.c_str());
				pAppoint->type = atoi(type.c_str());
				pAppoint->level = atoi(lev.c_str());
				pAppoint->silver = atoi(silver.c_str());
				pAppoint->gold = atoi(gold.c_str());
				char pIcon[20];
				sprintf(pIcon, "%s.png", icon.c_str());
				pAppoint->icon = pIcon;

				AppointManager::Instance()->setAppointTraders(pAppoint);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadAppointBlessXML( const char* filename )
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				AppointBlessVo *pAppointBless = new AppointBlessVo();

				std::string id, type, price, lev;
				elehandler.get(id);
				elehandler.get(type);
				elehandler.get(price);
				elehandler.get(lev);
				pAppointBless->goodsId = atoi(id.c_str());
				pAppointBless->goodsType = atoi(type.c_str());
				pAppointBless->blessValue = atoi(price.c_str());
				pAppointBless->crystalLev = atoi(lev.c_str());

				AppointManager::Instance()->setBlessVo(pAppointBless);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int ConfigManager::string2Int(std::string str)
{
	std::string strTmp = str;
	int len = strTmp.length();
	if (!len)	{	return (-1);}

	bool isNegative = false;

	if (strTmp[0] == '-')
	{
		isNegative = true;
		strTmp.substr(1,strTmp.length()-1);
	}

	len = strTmp.length();
	int result = 0;
	for (int i = 0;i < len;i++)
	{
		result = result * 10 + ( strTmp[i] - '0');
	}

	if (isNegative)
	{
		result = (-1) * result;
	}
	return result;
}

int32 ConfigManager::loadSilverMineXML( const char* filename )
{
	if (!filename)
		return 1;
	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				BasicMineVo basicMineVo;

				elehandler.get(basicMineVo.mineId);
				elehandler.get(basicMineVo.mineLev);
				elehandler.get(basicMineVo.xPos);
				elehandler.get(basicMineVo.yPos);
				elehandler.get(basicMineVo.x);
				elehandler.get(basicMineVo.y);
				SilverMineManage::Instance()->addBasicCfgByID(basicMineVo);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadGuildLevXML( const char* filename )
{
	if (!filename)
		return 1;
	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				GuildLevInfo *pGuildLevInfo = new GuildLevInfo;

				elehandler.get(pGuildLevInfo->lev);
				elehandler.get(pGuildLevInfo->needGold);
				elehandler.get(pGuildLevInfo->incMember);

				GuildManager::Instance()->setGuildLevInfos(pGuildLevInfo);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

//set vipGiftList from vipGift.xml
int32 ConfigManager::loadVipGiftXML( const char* filename )
{
	if (!filename)
		return 1;
	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				std::string id;
				std::string gift;

				elehandler.get(id);
				elehandler.get(gift);

				std::list<VipGiftVo *> giftList;
				std::vector<std::string> giftStrList = splitStringByCharacter(gift, "|");
				std::vector<std::string>::iterator it;
				for(it = giftStrList.begin(); it != giftStrList.end(); ++it)
				{
					std::string giftStr = *it;
					int index, end;
					index = 0;
					VipGiftVo *giftVo = new VipGiftVo();

					std::string tmp_s = "";
					end = giftStr.find( "," );
					tmp_s = giftStr.substr( index, end );
					giftVo->_career = atoi( tmp_s.c_str() );

					index = end + 1;
					end = giftStr.find( ",", index );
					tmp_s = giftStr.substr( index, end );
					giftVo->_goodsId = atoi( tmp_s.c_str() );

					index = end + 1;
					tmp_s = giftStr.substr( index );
					giftVo->_count = atoi( tmp_s.c_str() );

					giftList.push_back(giftVo);
				}


				int vipLev = atoi(id.c_str());

				VipManager::Instance()->setVipGiftList(giftList, vipLev);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadEggXML( const char* filename )
{
	if (!filename)
		return 1;
	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				int type;
				int smalltype;
				int quality;
				std::string k;
				std::string v;
				char key[50];
				elehandler.get(type);
				elehandler.get(smalltype);
				elehandler.get(quality);
				sprintf(key, "%d_%d_%d", type, smalltype, quality);
				k = key;
				elehandler.get(v);

				EggManager::Instance()->addEgg(k, v);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadItemRiseInfoXML( const char* filename )
{
	if (!filename)
		return 1;
	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	int ItemGradeLevel;
	int EquipPos;
	int Growup;	
	int cfg_PhyGrowup;
	int cfg_MagGrowup;
	int ItemSmallType;
	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);



				elehandler.get(ItemGradeLevel);
				elehandler.get(EquipPos);
				elehandler.get(Growup);
				elehandler.get(cfg_PhyGrowup);
				elehandler.get(cfg_MagGrowup);
				elehandler.get(ItemSmallType);
				

				ItemRiseInfo::Instance()->addInfo(ItemGradeLevel, EquipPos, ItemSmallType, Growup);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadTraderGoodsXML( const char* filename )
{
	if (!filename)
		return 1;
	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}

				 /*<item goodId="1" goodName="Áé»êË®¾§" icon="1" price="20"/>*/
				TinyElementHandler elehandler(pEle);

				TraderGoodsVo* vo = new TraderGoodsVo;

				elehandler.get(vo->goodsId);
				elehandler.get(vo->goodsName);
				elehandler.get(vo->icon);
				elehandler.get(vo->price);

				TraderManager::Instance()->createGoods(vo);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadActivityAwardXML(const char* filename)
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				OnlineRewardVo vo;
				elehandler.get(vo._id);
				elehandler.get(vo._dayNums);
				std::string strReward("");
				elehandler.get(strReward);

				vo.goodsList = splitStringByCharacter(strReward , "|");
				
				OnlineRewardManager::Instance()->addRewardList(vo);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadXHXML(const char* filename)
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				XHConfVo vo;
				int val = 0;
				elehandler.get(val);
				vo.type = val;

				elehandler.get(val);
				vo.color = val;

				elehandler.get(vo.name);

				elehandler.get(val);
				vo.effecttype = val;

				for (int i = 0; i < 10; i++)
				{
					elehandler.get(val);
					if (vo.effecttype >=6 && vo.effecttype <=13)
					{
						vo.lv[i] = val*0.001f;
					}
					else
						vo.lv[i] = val;
				}

				elehandler.get(vo.score);
						
				XHConfManager::Instance()->addXHConf(vo);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int32 ConfigManager::loadXHExpXML(const char* filename)
{
	if (!filename)
		return 1;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
			//case TiXmlText::TINYXML_TEXT:
			//	break;
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				XHExpConfVo vo;
				int val = 0;
				elehandler.get(val);
				vo.color = val;
				
				for (int i = 0; i < 10; i++)
				{
					elehandler.get(vo.lv[i]);
				}

				XHConfManager::Instance()->addXHExpConf(vo);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}