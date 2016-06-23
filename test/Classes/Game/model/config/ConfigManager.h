#ifndef _CONFIGMANAGER_H_
#define _CONFIGMANAGER_H_

#include "BaseType.h"

class TiXmlAttribute;
class ConfigManager
{
public:
	
public:
	ConfigManager();
	~ConfigManager();

	void loadConfig();
	static vector<std::string> splitStringByCharacter( string o_str, string sCharacter );
	static void splitStringByCharacterEx(string o_str, char* sCharacter, std::vector<std::string>& dst);
	static int string2Int(std::string str);
public:
	int32 loadGoodsXML(const char* filename);
	int32 loadShopGoodsXML(const char* filename);
	int32 loadNPCXML(const char* filename);
	int32 loadShopsXML(const char* filename);
	int32 loadDialogXML(const char* filename);
	int32 loadResXML(const char* filename);	//More than 400 meditation, to run the business with another such as writing
	int32 loadSkillResXML(const char* filename);	
	int32 loadSentenceXML(const char* filename);
	int32 loadSkillXML(const char* filename);
	int32 loadTaskXML(const char* filename);
	int32 loadMonsterXML(const char* filename);
	int32 loadMonsterGroupXML(const char* filename);
	int32 loadGameProgressXML(const char* filename);
	int32 loadMapExitXML(const char* filename);
	int32 loadMercenaryXML(const char* filename);
	int32 loadStrengriseXML(const char* filename);
	int32 loadMapXML(const char* filename);
	int32 loadLeveExpXML(const char* filename);
	int32 loadMapEnterXML(const char* filename);
	int32 loadEnchantlimitXML(const char* filename);
	int32 loadleveSkillXML(const char* filename);
	int32 loadstorymodelXML(const char* filename);
	int32 loadstoryprogressXML(const char* filename);
	int32 loadNewhandXML(const char* filename);
	int32 loadNewhandStepXML(const char* filename);
	int32 loadNewhandHelpXML( const char* filename);
	int32 loadHonorsXML(const char* filename);
	int32 loadserverlistXML(const char* filename);
	int32 loadArenaXML(const char* filename);
	int32 loadSpeedupXML( const char* param1 );
	int32 loadMusicXML( const char* filename );
	int32 loadNameXML( const char* filename );
	int32 loadPlayerAniXML( const char* filename );
	int32 loadAppointXML( const char* filename);
	int32 loadAppointBlessXML( const char* filename);
	int32 loadGuildLevXML( const char* param1 );
	int32 loadVipGiftXML( const char* filename );
	int32 loadSilverMineXML( const char* param1 );
	int32 loadEggXML( const char* filename ); 
	int32 loadItemRiseInfoXML( const char* filename ); 
	int32 loadTraderGoodsXML( const char* param1 );
	int32 loadActivityAwardXML( const char* filename );
	int32 loadXHXML(const char* filename);
	int32 loadXHExpXML(const char* filename);
private:

};

extern ConfigManager* g_pConfigManager;

#endif