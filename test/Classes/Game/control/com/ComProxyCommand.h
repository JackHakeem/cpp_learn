#ifndef _ComProxyCommand_H_
#define _ComProxyCommand_H_

#include "mvc/SimpleCommand.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "socket/command/s16/SCMD16F.h"

class ComProxyCommand:public SimpleCommand
{
public:
	enum 
	{
		UPDATE_GOODS_DYNAMIC,
		CHAT_SHOW_DYNAMIC,
	};

public:
	ComProxyCommand();
	~ComProxyCommand();
	virtual void execute(int32 command, char* data);
	void updateGoodsDynamic( SCMD16F* obj );
	GoodsInfo* getGoodsInfo( uint location, uint grid, uint roleId );
	void setDynamicInfo( uint location , uint grid, uint roleId );
private:
};

#endif