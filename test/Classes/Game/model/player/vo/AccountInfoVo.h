#ifndef HLQS_AccountInfoVo_h
#define HLQS_AccountInfoVo_h
#include "cocos2d.h"
#include "utils/flash/CCIEventDispatcher.h"

using namespace cocos2d;
class AccountInfoVo: public CCIEventDispatcher
{
public:
	std::string NAME;
	std::string CHANGE;

	enum
	{
		CHANGE_POPULARITY = 1300,
	};
	std::string CHANGE_HONOR_TITLE; // title
	std::string CHANGE_GOLD; // DianJuan
	std::string CHANGE_GOLDCOUNT; // DianJuan
	std::string CHANGE_SILVER; // game currency
	std::string CHANGE_SILVER_LIM; // silver ceiling
	std::string CHANGE_PRACTICE; // experience
	//std::string CHANGE_POPULARITY; // the name
	std::string CHANGE_STONE; // magic stone
	std::string CHANGE_ENERGY; // energy
	std::string CHANGE_CRYSTAL_LEV; // crystal level
	std::string CHANGE_CRYSTAL_CD_NUM; // crystal CD queue number
	std::string CHANGE_TRIAN_SIT_NUM; //
	std::string CHANGE_VIPLEV; // VIP level
	std::string CHANGE_THREATEN; // threat degrees
	int _gold; // int: 32 gold
	int _silver; // int: 32 silver
	int _silverLim; // silver dollar limit (with water level of the crystal relevant)
	int _practice; // int experience
	int _popularity; // int reputation
	int _energy; // energy
	int _stone; // magic stone
	int _honorTitleId; // title id
	int _vipLev; // VIP level (0 ordinary players, no VIP);
	bool _trialVip; // temporary VIP
	int _goldcount; // total cost to VIP level have influence
	int _onlineTime;
	std::string name; // nickname
	int accountId; // account
	int roleId; // protagonist Numbers
	int roleNum; // mercenaries data
	int roleLim; // mercenaries cap
	int currFormation; // current formations
	int currTeamFormation; // the current group formation
	int _crystalLev; // life level of the crystal
	int _numCrystalCd; // crystal CD queue CD slot number, the server storage (old: according to the VIP level changes)
	int _trainSitNumLim; // training position
	int _levArea; // the current level area (0-0-level 20; 1:21-level 40; 2:41-level 60; when 1-80, 1-100 "grade level; 5:10 1-120 class)
	int _threaten; // threat degrees
	/* * group state. 0-no group; 1-captain; 2-players */
	int team; // team
	int guild; // trade union
	int _red;
	int _blue;
	int _purple;
	int _vigourBuffCount;
	int _gongExpBuffCount;
public:
	AccountInfoVo()
	{
		NAME = "_AccountInfoVo";
		CHANGE = "CHANGE";
		CHANGE_HONOR_TITLE = "CHANGE_HONOR_TITLE" + NAME; // title
		CHANGE_GOLD = "CHANGEGOLD" + NAME; // DianJuan
		CHANGE_GOLDCOUNT = "CHANGE_GOLDCOUNT" + NAME; // DianJuan
		CHANGE_SILVER = "CHANGESILVER" + NAME; // game currency
		CHANGE_SILVER_LIM = "CHANGESILVER_LIM" + NAME; // silver ceiling
		CHANGE_PRACTICE = "CHANGEPRACTICE" + NAME; // experience
		//CHANGE_POPULARITY = "CHANGEPOPULARITY" + NAME; // the name
		CHANGE_STONE = "CHANGESTONE" + NAME; // magic stone
		CHANGE_ENERGY = "CHANGEENERGY" + NAME; // energy
		CHANGE_CRYSTAL_LEV = "CHANGE_CRYSTAL_LEV" + NAME; // crystal level
		CHANGE_CRYSTAL_CD_NUM = "CHANGE_CRYSTAL_CD_NUM" + NAME; // crystal CD queue number
		CHANGE_TRIAN_SIT_NUM = "CHANGE_TRIAN_SIT_NUM" + NAME; //
		CHANGE_VIPLEV = "CHANGE_VIPLEV" + NAME; // VIP level
		CHANGE_THREATEN = "CHANGE_THREATEN" + NAME; // threat degrees
		_gold = 0; // int: 32 gold
		_silver = 0; // int: 32 silver
		_silverLim = 0; // silver dollar limit (with water level of the crystal relevant)
		_practice = 0; // int experience
		_popularity = 0; // int reputation
		_energy = 0; // energy
		_stone = 0; // magic stone
		_honorTitleId = 0; // title id
		_vipLev = 0; // VIP level (0 ordinary players, no VIP);
		_trialVip = 0; // temporary VIP
		_goldcount = 0; // total cost to VIP level have influence
		_onlineTime = 0;
		accountId = 0; // account
		roleId = 0; // protagonist Numbers
		roleNum = 0; // mercenaries data
		roleLim = 0; // mercenaries cap
		currFormation = 0; // current formations
		currTeamFormation = 0; // the current group formation
		_crystalLev = 1; // life level of the crystal
		_numCrystalCd = 2; // crystal CD queue CD slot number, the server storage (old: according to the VIP level changes)
		_trainSitNumLim = 2; // training position
		_levArea = 0; // the current level area (0-0-level 20; 1:21-level 40; 2:41-level 60; when 1-80, 1-100 "grade level; 5:10 1-120 class)
		_threaten = 0; // threat degrees
		/* * group state. 0-no group; 1-captain; 2-players */
		team = 0; // team
		guild = 0; // trade union
		_red = 0;
		_blue = 0;
		_purple = 0;
		_vigourBuffCount = 0;
		_gongExpBuffCount = 0;
	}


	/**
	* @param value
	* 
	*/		
	void threaten(int value)
	{
		_threaten = value;
		dispatchEvent(Event::CHANGE_THREATEN, NULL);
	}

	/**
	* 
	*/        
	void change()
	{
		dispatchEvent(Event::CHANGE, NULL);
	}
	/**
	* @param value
	* 
	*/        
	void gold(int value);

	int gold()
	{
		return _gold;
	}

	/**
	* @param value
	* 
	*/        
	void goldcount(int value)
	{
		_goldcount = value;
		dispatchEvent(Event::CHANGE_GOLDCOUNT, NULL);
	}

	int goldcount()
	{
		return _goldcount;
	}

	/**
	* @param value
	* 
	*/		
	void silver(int value)
	{
		_silver = value;
		dispatchEvent(Event::CHANGE_SILVER, NULL);
	}

	int silver()
	{
		return _silver;
	}
	/**
	* @param value
	* 
	*/		
	void silverLim(int value)
	{
		_silverLim = value;
		dispatchEvent(Event::CHANGE_SILVER_LIM, NULL);
	}

	int silverLim()
	{
		return _silverLim;
	}

	/**
	* @param value
	* 
	*/        
	void practice(int value)
	{
		_practice = value;
		dispatchEvent(Event::CHANGE_PRACTICE, NULL);
	}
	int practice()
	{
		return _practice;
	}

	/**
	* @param value
	* 
	*/		
	void popularity(int value)
	{
		_popularity = value;
		dispatchEvent(Event::CHANGE_POPULARITY, NULL);
	}

	int popularity()
	{
		return _popularity;
	}

	/**
	* @param value
	* 
	*/		
	void stone(int value)
	{
		_stone = value;
		dispatchEvent(Event::CHANGE_STONE, NULL);
	}

	int stone()
	{
		return _stone;
	}


	/**
	* @param value
	* 
	*/		
	void energy(int value)
	{
		_energy = value;
		dispatchEvent(Event::CHANGE_ENERGY, NULL);
	}
	int energy()
	{
		return _energy;
	}

	void trialVip(bool value)
	{
		_trialVip = value;
		dispatchEvent(Event::CHANGE_VIPLEV, NULL);
	}

	bool trialVip()
	{
		return _trialVip;
	}
	/**
	*  vip
	* @param value
	* 
	*/		
	void vipLev(int value)
	{
		_vipLev = value;
		dispatchEvent(Event::CHANGE_VIPLEV, NULL);
	}

	int vipLev()
	{
		return _vipLev;
	}

	void onlineTime(int value)
	{
		_onlineTime = value;
	}

	int onlineTime()
	{
		return _onlineTime;
	}


	/**
	* @return 
	* 
	*/		
	int crystalLev()
	{
		return _crystalLev;
	}

	void crystalLev(int value)
	{
		_crystalLev = value;
		dispatchEvent(Event::CHANGE_CRYSTAL_LEV, NULL);
	}

	int honorTitleId()
	{
		return _honorTitleId;
	}

	void honorTitleId(int value)
	{
		_honorTitleId = value;
		dispatchEvent(Event::CHANGE_HONOR_TITLE, NULL);
	}

	int numCrystalCd()
	{
		return _numCrystalCd;
	}

	void numCrystalCd(int value)
	{
		_numCrystalCd = value;
		dispatchEvent(Event::CHANGE_CRYSTAL_CD_NUM, NULL);
	}

	void trainSitNumLim(int value)
	{
		_trainSitNumLim = value;
		dispatchEvent(Event::CHANGE_TRIAN_SIT_NUM, NULL);
	}

	int trainSitNumLim()
	{
		return _trainSitNumLim;
	}

	void vigourBuffCount(int value)
	{
		_vigourBuffCount = value;
		dispatchEvent(Event::CHANGE_VIGOUR_BUFF, NULL);
	}

	int vigourBuffCount()
	{
		return _vigourBuffCount;
	}

	//int levArea()
	//{
	//	if(_crystalLev <= 20) _levArea = 0;
	//	else if(_crystalLev <= 40) _levArea = 1;
	//	else if(_crystalLev <= 60) _levArea = 2;
	//	else if(_crystalLev <= 80) _levArea = 3;
	//	else if(_crystalLev <=100) _levArea = 4;
	//	else if(_crystalLev <=120) _levArea = 5;
	//	else _levArea = 0;
	//	return _levArea;
	//}
};
#endif