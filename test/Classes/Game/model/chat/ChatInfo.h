#pragma once

#include "BaseType.h"

class ChatInfo
{
public:
	ChatInfo()
	{
		channel = 0;
		fromId = 0;
		fromName = "";
		content = "";
		data = "";
		line = 1;
		isPerson = false;
		isSelf = false;
		toId = 0;
		toName = "";
		isGM = false;
		color = "";
	}
		
	int channel;					//频道索引
	int fromId;					//玩家ID
	std::string fromName;				//玩家名称
	std::string content;			//聊天内容
	std::string data;			//附加数据（战报，展示物品等）
	int line;				//线路
	bool isPerson;	//是否是私聊 可选
	bool isSelf;		//是否是自己 可选
	int toId;				//私聊对象ID 可选
	std::string toName;			//私聊对象名字 可选
	bool isGM;	//是否GM
	std::string color;		//颜色 可选
		
};
