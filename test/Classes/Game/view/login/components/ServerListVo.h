#ifndef _SERVER_LISTVO_H_
#define _SERVER_LISTVO_H_

class ServerListVo
{
public:
	ServerListVo() : areaID(0) , areaName("") , serverID(0) , servName("") , ip("") , port(0) , state(0) , exchargeServerId("")
	{
// 		areaID = 0;
// 		areaName = "";
// 		serverID = 0;
// 		servName = "";
// 		ip = "";
// 		port = 0;	
// 		state= 0;
// 		exchargeServerId = "";
	}
	~ServerListVo(){}

public:
	int areaID;
	std::string areaName;
	int serverID;
	std::string servName;
	std::string ip;
	std::string exchargeServerId;
	unsigned short port;
	int state;
};

#endif
