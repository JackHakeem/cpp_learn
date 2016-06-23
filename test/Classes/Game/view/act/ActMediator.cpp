#include "CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "utils/http/ghttp.h"
#include "netdb.h"
#include "arpa/inet.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "utils/http/ghttp.h"
#include "netdb.h"
#include "arpa/inet.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "Poco/Net/NetException.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
using namespace Poco;
using namespace Poco::Net;
#endif


#include "ActMediator.h"
#include "manager/PopEventName.h"
#include "events/GameDispatcher.h"
#include "model/player/RoleManage.h"
#include "socket/network/GateServerSocket.h"
#include "model/guild/vo/MemberVo.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "components/ActView.h"
#include "manager/ViewManager.h"
#include "components/HotList.h"
#include "components/ActItem.h"
#include "utils/xml/TinyElementHandler.h"

ActMediator::ActMediator()
{
	_actView = 0;
}

ActMediator::~ActMediator()
{}

void ActMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd)
	{
	//case GUILD_POP:
	//	pop((GuildView*)data);
	//	break;
	default:
		break;
	}
}

// �򿪾�����
void ActMediator::pop()
{
	if (_actView)
	{
		_actView->release();
		_actView = 0;
	}
	if(!_actView)
	{
		_actView = new ActView();
		_actView->init();
		ViewManager::getInstance()->actView = _actView;

	}
	
	_actView->setisPop(!_actView->getisPop());
	if (_actView->getisPop())
	{
		_actView->release();
	}	

	sendApplyData();
}

void ActMediator::sendApplyData()
{
	CCMD38E cmd;
	GameServerSocket::getInstance()->sendMessage(&cmd);

	/*
	//ģ��һ��ʵ����PHP��ȡ
	SCMD38F cmdF;
	getData(cmdF);
	

	updateData(&cmdF);
	*/
}

void ActMediator::updateData(SCMD38F* pdata)
{
	////test
	//pdata = new SCMD38F();
	//{
	//	

	//	SCMD38FNode node;
	//	node.type = 0;
	//	node.title = ValuesUtil::Instance()->getString("FUCK002");
	//	node.content = ValuesUtil::Instance()->getString("FUCK001");
	//	pdata->_arr.push_back(node);	
	//	node.title = "keminghua1";
	//	pdata->_arr.push_back(node);

	//	node.title = "keminghua2";
	//	node.content = "this is a test field,fasdsssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	//	pdata->_arr.push_back(node);
	//	
	//}
	//{
	//	

	//	SCMD38FNode node;
	//	node.type = 1;
	//	node.title = "kemdfa";
	//	node.content = "this is a test field,fasdfsssssffoidhjshmdxffsdfsssssssssssjax927y43��A&DIAJA����*��*&��@&��@*&��*��&@��";
	//	pdata->_arr.push_back(node);	
	//	node.title = "keminsdfghua1";
	//	pdata->_arr.push_back(node);

	//	node.title = ValuesUtil::Instance()->getString("FUCK002");
	//	node.content = ValuesUtil::Instance()->getString("FUCK001");
	//	pdata->_arr.push_back(node);
	//	node.title = "s";
	//	node.content = ValuesUtil::Instance()->getString("FUCK001");
	//	pdata->_arr.push_back(node);
	//}
	//
	if (!_actView ||  !_actView->_pHot || !_actView->_pAct)
		return;
	//��֮ǰ�Ŀ���
	_actView->_pHot->m_arr.clear();
	_actView->_pHot->m_arrItem.clear();
	_actView->_pHot->_index = 0;
	_actView->_pHot->_curClickIndex = 0;

	_actView->_pAct->m_arr.clear();
	_actView->_pAct->m_arrItem.clear();
	_actView->_pAct->_index = 0;
	_actView->_pAct->_curClickIndex = 0;

	for (std::list<SCMD38FNode>::iterator it = pdata->_arr.begin(); it != pdata->_arr.end(); it++)
	{
		SCMD38FNode& node = *it;
		if (node.b_type == 0)
		{
			_actView->_pHot->m_arr.push_back(node);
			ActItem* newitem = new ActItem();
			newitem->init(node);
			_actView->_pHot->m_arrItem.push_back(newitem);
		}
		else if(node.b_type == 1)
		{
			_actView->_pAct->m_arr.push_back(node);
			ActItem* newitem = new ActItem();
			newitem->init(node);
			_actView->_pAct->m_arrItem.push_back(newitem);			
		}
	}
	//
	_actView->_pHot->_index = 0;
	_actView->_pAct->_index = 0;
	_actView->_pHot->setAdapter(_actView->_pHot);	
	_actView->_pAct->setAdapter(_actView->_pAct);	
	//
	//for (int i = 0; i < _actView->_pHot->m_arrItem.size(); i++)
	//{
	//	//_actView->_pHot->onItemClickListener(_actView->_pHot->m_arrItem[i] , i); // LH added
	//	_actView->_pHot->m_arrItem[i]->release();
	//}
	//for (int i = 0; i < _actView->_pAct->m_arrItem.size(); i++)
	//{
	//	//_actView->_pAct->onItemClickListener(_actView->_pAct->m_arrItem[i] , i);// LH added
	//	_actView->_pAct->m_arrItem[i]->release();
	//}
	//
	//delete pdata;
}

void ActMediator::sockActInfo(SCMD38F * cmdF)
{
	std::list<SCMD38FNode> node = cmdF->_arr;
	// store data
	//
	updateData(cmdF);
}

void ActMediator::getData(SCMD38F& cmdF)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    char pUrl[100] = "http://api.slcq.4399sy.com/get_activity.php";
#endif


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    char pUrl[100] = "http://api.slcq.4399sy.com/get_activity_android.php";
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
    char pUrl[100] = "http://api.slcq.4399sy.com/get_activity.php";
#endif



#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )

	ghttp_request *request = NULL;
	ghttp_status status;
	char *buf;
	int bytes_read;

	request = ghttp_request_new();
	if(ghttp_set_uri(request, pUrl) == -1)
		exit(-1);
	if(ghttp_set_type(request, ghttp_type_get) == -1)
		exit(-1);
	ghttp_set_sync(request, ghttp_async);
	ghttp_prepare(request);

	while(1) 
	{
		status = ghttp_process(request);
		if(status == ghttp_error)
		{
			CCMessageBox("http error", "Login");
			break;
		}
		buf = ghttp_get_body(request);
		bytes_read = ghttp_get_body_len(request);
		if(status == ghttp_done) 
		{
//			printf("%s", buf);
//			printf("\n");
//			printf("number:%d", bytes_read);
			break;
		}
		else
		{
//			printf("false\n");
		}
	}
    //Doyang 20120907
    if(bytes_read <= 0)
    {
        CCMessageBox("http error", "Login");
        return;
    }
    
    
	char* usefulBuff = new char[bytes_read+1];
	strncpy(usefulBuff, buf, bytes_read);
	usefulBuff[bytes_read] = '\0';

	loadDataXMLBuffer(usefulBuff, bytes_read +1 , TIXML_ENCODING_UTF8,cmdF);

	delete []usefulBuff;
	usefulBuff = 0;
	ghttp_request_destroy(request);

#endif	

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	Poco::Net::HTTPClientSession session("api.slcq.4399sy.com", Poco::Net::HTTPSession::HTTP_PORT);	
	Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET,"/get_activity.php",Poco::Net::HTTPMessage::HTTP_1_1);

	try
	{
		session.sendRequest(request);
	}
	catch (Poco::Net::NetException * e)
	{
		CCMessageBox(e->name() , ValuesUtil::Instance()->getString("LG033").c_str());
		return;
	}

	char buffer[8192] = {0};
	Poco::Net::HTTPResponse response;
	try
	{
		session.receiveResponse(response).read(buffer,8096);
	}
	catch (Poco::Net::NetException* e)
	{
		CCMessageBox(e->name() , ValuesUtil::Instance()->getString("LG033").c_str());
		return;
	}

	int len = sizeof(buffer);

	if (len)
	{
		loadDataXMLBuffer(buffer,sizeof(buffer),TiXmlEncoding::TIXML_ENCODING_UTF8,cmdF);
	}
	
#endif
}


int ActMediator::loadDataXMLBuffer( char *arr, int length, TiXmlEncoding encoding, SCMD38F& cmdF )
{
	if (!arr)
		return 1;

	TiXmlDocument xmlDoc(arr); 
    CCLog("-----------\n%s", arr);
	bool sus = xmlDoc.loadFileWithCharArr(arr, length, encoding);  
	if (!sus)
		return 1;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				// add code here
				SCMD38FNode node;
				elehandler.get(node.a_id);
				int type;
				elehandler.get(type);
				node.b_type = (uint8)type;
				elehandler.get(node.c_title);
				elehandler.get(node.d_content);
				elehandler.get(node.e_startTime);
				elehandler.get(node.f_endTime);
				cmdF._arr.push_back(node);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}
