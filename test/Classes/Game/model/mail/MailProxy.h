#pragma once
#include "mvc/Proxy.h"
#include "vo/MailHeadVo.h"
#include "vo/MailContentVo.h"

class SCMD1AB;
class SCMD1A1;
class SCMD1A3;

class MailProxy : public Proxy
{
public:
	MailProxy();
	
	void initMailCount(SCMD1AB * data);
	void updateMailList(SCMD1A1 * data);
	void updateMailContent(SCMD1A3 * data);
public:
	std::list<MailHeadVo> _mailHeadList;	//邮件头列表	
	std::list<MailHeadVo> _mailSysHeadList;
	std::list<MailHeadVo> _mailPlayerHeadList;
	std::map<int,MailContentVo> _mailContentDic; //邮件详情
	bool _listCreated;
	int _totalNum;
	int _unreadNum;
	int _sysMailNum;
	int _playerMailNum;

public:
	std::list<MailHeadVo> * getHeadListByType(int type);
	bool getIsListCreated();
	int getTotalNum();
	int getSystemMailNum();
	int getPlayerMailNum();
	MailContentVo * getMailContent(uint32 mailID);

protected:
private:
};