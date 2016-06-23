#ifndef HLQS_PoseState_H_
#define HLQS_PoseState_H_
#include "SceneConst.h"
#include "utils/flash/CCIEventDispatcher.h"

USING_NS_CC;

class PoseState: public CCIEventDispatcher
{
public:
	int _state;
	bool _isChanged;
	int _suzhuType;
public:
	PoseState()
	{
		_state = 0;
		_isChanged = false;
	}

	void state(int value)
	{
		if (_suzhuType == 2)
		{
			int iiii = 0;
			iiii = 1;
		}
		if (value == 0 && _suzhuType == 2)//_state == 3 && 
		{
			int iiii = 0;
			iiii = 1;
		}
		if (_state == 3 && value == 0 && _suzhuType == 2)//_state == 3 && 
		{
			int iiii = 0;
			iiii = 1;
		}
		_isChanged = false;
		if(!canTransite(value))
			return;
		if(_state!=value)
		{
			_state = value;
			_isChanged = true;
			//dispatchEvent(SceneConst::CHANGE, NULL);
			dispatchEvent(SceneConst::CHANGE, this);
		}
	}

	bool canTransite(int value)
	{
		if(_state==SceneConst::DEAD)
		{
			return false;
		}
		else if(_state == SceneConst::MOVE)
		{
			if(value==SceneConst::HITED)
			{
				return false;
			}
		}
		return true;
	}

	int state()
	{
		return _state;
	}

	bool isChanged()
	{
		return _isChanged;
	}

	bool lockMove()
	{
		if(_state== SceneConst::DEAD || _state==SceneConst::STAND) 
		{
			return true;
		}
		return false;
	}
};


#endif