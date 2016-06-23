#ifndef _LIVETHINGVO_H 
#define _LIVETHINGVO_H 

#include "BaseType.h"
#include "utils/flash/CCIEventDispatcher.h"

class LiveThingVo: public CCIEventDispatcher
{
public:
	LiveThingVo() : state(2)
	{
		id = 0;
		name = "";
		_lev = 0;
		x = 0;
		y = 0;
		_mapId = 0;
		formId = 0;
		_hp = 0;
		_maxHp = 0;
		_mp = 0;
		_maxMp = 100.f;
		skill1 = 0;
		skill2 = 0;
		skill3 = 0;
		threat = 0;
		_isCell = true;
	}

public:
	enum
	{
		CHANGEHP = 0,
		CHANGEMP,
		CHANGELEV,
		CHANGEMAXHP,
		CHANGEMAXMP,
		CHANGE_MAP,
	};

	int id;
	std::string name;
	int formId;	//formation id
	uint _lev;//level
public:
	int x;
	int y;
	int state;//:int=2; Action state

public:
	int _mapId;
	int _hp;
	int _maxHp;
	int _mp;
	int _maxMp;
	int skill1;
	int skill2;
	int skill3;
	int threat;
	bool _isCell;

public:

	// Map id
	void setMapId ( int value )	
	{ 
		_mapId = value;
		dispatchEvent(CHANGE_MAP, NULL);
	}

	int GetmapId() 
	{
		return _mapId;
	}

    // Lev   
	void setLevelId ( int value )
	{
		_lev = value;
	}

	int GetLevelId()
	{
		return _lev;
	}

	void hp(int value)
	{
		if(_hp!=value)
        {
        	_hp=value;
        	dispatchEvent(CHANGEHP, NULL);
        }
	}

	int hp()
    {
        return _hp;
    }

	void maxHp(int value)
    {
        if(_maxHp != value)
        {
        	if(_hp > value)
				hp(value);
        	_maxHp = value;
			dispatchEvent(CHANGEMAXHP, NULL);
        }
    }

	int maxHp()
    {
        return _maxHp;
    }

	void mp(int value)
	{
		if(_mp != value)
		{
			_mp = value;
			dispatchEvent(CHANGEMP, NULL);
		}
	}

	int mp()
	{
		return _mp;
	}

	void maxMp(int value)
    {
        if(_maxMp != value)
        {
        	if(_mp > value)
				mp(value);

			_maxMp=value;
			dispatchEvent(CHANGEMAXMP, NULL);
        }
        	
    }

    int maxMp()
    {
        return _maxMp;
    }

	void lev(int value)
    {
        if(_lev != value)
        {
        	_lev=value;
			dispatchEvent(CHANGELEV, &id);
        }
        	
    }
	int lev()
    {
        return _lev;
    }
};

#endif