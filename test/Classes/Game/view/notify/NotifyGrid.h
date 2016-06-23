#pragma once
#include "../../../UIComponent/LayerNode.h"


class NotifyGrid : public LayerNode
{
public:
	
public:
	NotifyGrid();
	NotifyGrid(int type);
	virtual ~NotifyGrid();
	virtual bool init();

	void loadItem();

public:
	int _type;
	CCSize _size;

public:
	
};