#ifndef HLQS_PlayerBaseVo_h
#define HLQS_PlayerBaseVo_h
#include "model/scene/vo/LiveThingVo.h"
#include "socket/command/s11/SCMD111.h"

class PlayerBaseVo: public LiveThingVo
{
public:
	//std::string CHANGE_LEADER;
	//std::string CHANGEEXP;
	//std::string CHANGE_GUILD;

	enum
	{
		//Doyang 20120829
		CHANGE_LEADER = 1000,
		CHANGEEXP,
		CHANGE_GUILD,
		CHANGE_TITLE,
	};

	int accountId; // account ID only allow scene calls
	int team; // team only allow scene calls
	int guild; // union only allow scene calls
	std::string _guildName; // the name
	int _titleId;
	int career; // professional
	int sex; // gender
	int color; // color
	int weapon;
	int cloth;
	int horse;
	int energy; // energy
	int mercId; // prototype id
	bool isRole;
	int icon; // character stats (0: restore normal 1: death 2: resurrection 3: letters 4: is a strange)
	int ranger; // vision
	int speed;
	SCMD111 path; // player path
	int _isLeader;
	int _exp; // experience value
	int adExp;
	int adLv;
	int arraySeat;//Õ½¶·Õ¾Î»
	PlayerBaseVo()
	{

		//CHANGE_LEADER = "CHANGE_LEADER";
		//CHANGEEXP = "CHANGEEXP";
		//CHANGE_GUILD = "changeGuild";
		accountId = 0; // account ID only allow scene calls
		team = 0; // team only allow scene calls
		guild = 0; // union only allow scene calls
		career = 0; // professional
		_titleId = 0;
		sex = 0; // gender
		color = 0; // color
		weapon = 0;
		cloth = 0;
		horse = 0;
		energy = 0; // energy
		mercId = 0; // prototype id
		isRole = false;
		icon = 0; // character stats (0: restore normal 1: death 2: resurrection 3: letters 4: is a strange)
		ranger = 2; // vision
		speed = 0;
		_isLeader = 0;
		_exp = 0; // experience value
		adExp = 0;
		adLv = 0;
		arraySeat=0;
	}

	std::string guildName()
	{
		return _guildName;
	}

	void guildName(std::string value)
	{
		if(_guildName != value)
		{
			_guildName = value;
			dispatchEvent(CHANGE_GUILD, (char*)_guildName.c_str());
		}
	}
	int attackType()
	{
		if(career==2)
		{
			return 1;
		}
		return 0;
	}
	int isLeader()
	{
		return _isLeader;
	}
	void isLeader(int value)
	{
		if(_isLeader!=value)
		{
			_isLeader=value;
			dispatchEvent(CHANGE_LEADER, NULL);
		}
	}

	/**
	* @param value
	* 
	*/		
	void exp(int value)
	{
		if(_exp!=value)
		{
			_exp=value;
			dispatchEvent(CHANGEEXP, NULL);
		}

	}

	int exp()
	{
		return _exp;
	}		
};
#endif