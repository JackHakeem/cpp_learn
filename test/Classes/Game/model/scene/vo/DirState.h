#ifndef HLQS_DirState_H_H
#define HLQS_DirState_H_H
#include "utils/flash/CCIEventDispatcher.h"
#include "SceneConst.h"

class DirState: public CCIEventDispatcher
{
public:
	DirState()
	{
		_state = 0;
		_isChanged = false;
		_scale = 1;
		_frame = 2;
		isNPC = false;
	}
	
public:
	int _state;
	bool _isChanged;
	int _scale;
	int _frame;
	bool isNPC;

	void state(int value)
	{
		if(_state != value)
		{
			_state = value;
			_isChanged = true;

			switch(_state)
			{
			case 9:
				_frame = 7;
				_scale = -1;
				break;
			case 6:
				_frame = 4;
				_scale = -1;
				break;
			case 3:
				_frame = 1;
				_scale = -1;
				break;
			default:
				_frame = _state;
				_scale = 1;
				break;
			}
			dispatchEvent(SceneConst::CHANGE, NULL);
		}
		else 
		{
			_isChanged=false;
		}
	}

	int state()
	{
		return _state;
	}

	bool isChanged()
	{
		return _isChanged;
	}

	int scale()
	{
		return _scale;
	}

	int frame()
	{
		return _frame;
	}
};

#endif