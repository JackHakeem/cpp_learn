#ifndef _ITEMVO_H 
#define _ITEMVO_H 
#include "BaseType.h"


class ItemVo
{


public:
	ItemVo()
	{
		x = 0;
		y = 0;
      _id = 0;
	  _name = "";
	  _resId = 0;

	}

	ItemVo(ItemVo &itemVo)
	{
		ItemVo();
		_itemVo = &itemVo;
	}

	~ItemVo(){}
    uint32 x;
    uint32 y;

	//public var otherInfos:Array;  // Obligate array



	private:
		int _id; 
		std::string _name;
		int _resId;
		ItemVo * _itemVo;

public:

	int getID(){return _id;}
	void setId(int id){_id=id;}
	std::string getName(){return _name;}
	void setName(std::string name){_name=name;}
	int getResId(){	return _resId; }
	void setResId( int value ) { _resId = value; }
};


#endif