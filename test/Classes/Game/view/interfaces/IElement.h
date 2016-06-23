#ifndef HLQS_IElement_H_
#define HLQS_IElement_H_
#include "utils/flash/CCIEventDispatcher.h"

class IElement: public CCLayer, public CCIEventDispatcher
{
public:
	IElement()
	{
		_x = 0.0f;
		_y = 0.0f;
		_id = 0;
	}

	virtual int getThingType() 
	{
		return 0;
	}

	virtual bool isHit(CCPoint point)
	{
		return false;
	}

	virtual bool setGlow()
	{
		return false;
	}

	virtual bool hitTest(CCPoint)
	{
		return false;
	}

	virtual void setSelect(bool value)
	{
		_select = value;
	}

	virtual void dispose(){}

	virtual void eleName(std::string)
	{
	}

	virtual std::string eleName()
	{
		return "";
	}
	virtual std::vector<int>* otherInfos()
	{
		return &(_otherInfos);
	}

	virtual void otherInfos(std::vector<int>& value)
	{
		_otherInfos = value;
	}

	std::string type()
	{
		return _type;
	}

	void type(std::string value)
	{
		_type = value;
	}

	virtual void step(){}

	void x(float value)
	{
		_x = value;
	}

	float x()
	{
		return _x;
	}

	void y(float value)
	{
		_y = value;
	}

	float y()
	{
		return _y;
	}

	int id()
	{
		return _id;
	}

	void id(int value)
	{
		_id = value;
	}

	virtual void shutup(){};

	virtual void isInteractive(bool){}
	virtual bool isInteractive(){return false;}

public:
	float _x;
	float _y;
	std::string _type;
	std::vector<int> _otherInfos;
	int _id;
	bool _select;
};

#endif