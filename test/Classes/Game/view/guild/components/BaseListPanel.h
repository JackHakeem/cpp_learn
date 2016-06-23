#pragma once

#include "BaseType.h"
class MemberVo;
class GuildVoBase;

class BaseListPanel:public LayerNode
{
public:
	BaseListPanel()
	{
		_hasInit = false;
	}
		
	bool _hasInit;
			
	virtual void setPage(int max = 1, int index = 1)
	{
			
	}
		
	virtual void updateList(std::list<GuildVoBase*>& listDatas)
	{
	}
		
	virtual void sethasInit(bool b)
	{
		_hasInit = b;
	}
		
	virtual bool gethasInit()
	{
		return _hasInit;
	}
		
	virtual int getcurPage()
	{
		return 1;
	}
};