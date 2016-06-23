#pragma once

#include "mvc/Mediator.h"
#include "socket/command/c38/CCMD38E.h"
#include "socket/command/s38/SCMD38F.h"
#include "utils/xml/tinyxml.h"
//#include "socket/command/s1b/SCMD1B2.h"
//#include "model/guild/vo/GuildInfoVo.h"
//#include "components/GuildPreView.h"
class ActView;

class ActMediator:public Mediator
{
public:
	enum
	{

	};
public:
	ActMediator();
	~ActMediator();

	void handleNotification( int M2Vcmd, char* data );
	//void setGuildList( char* data );
	//void setDefaultVO( MemberVo* info );
	void pop();
	void sendApplyData();
	void updateData(SCMD38F* pdata);
	void getData(SCMD38F& cmdF);
	void sockActInfo(SCMD38F * cmdF);
	int loadDataXMLBuffer( char *arr, int length, TiXmlEncoding encoding,  SCMD38F& cmdF);
public:
	ActView* _actView;


};
 