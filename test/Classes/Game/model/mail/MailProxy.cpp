#include "MailProxy.h"
#include "socket/command/s1a/SCMD1AB.h"
#include "socket/command/s1a/SCMD1A1.h"
#include "socket/command/s1a/SCMD1A3.h"
#include "mvc/Facade.h"
#include "view/mail/MailMediator.h"
#include "control/AppFacade.h"
#include "MailConst.h"

MailProxy::MailProxy()
{

}

/**
		 *获得邮件数量 
		 * @param param
		 * 
		 */	
void MailProxy::initMailCount(SCMD1AB * data)
{
	_unreadNum = data->a_unreadNum;
	_totalNum = data->b_totalNum;
	_playerMailNum = data->c_playerMailNum;
	_sysMailNum = data->d_systemMailNum;
	sendNotification(Facade_Mediator,AppFacade_Mail_Mediator,(char *)data,MailMediator::SHOW_MAIL_COUNT);
}

/**
		 *获得邮件列表 ，在服务器取得数据之后触发
		 * 然后通知Mediator更新界面
		 * @param  SCMD1A1
		 * 
		 */
void MailProxy::updateMailList(SCMD1A1 * data)
{
	_mailHeadList.clear();
	_mailPlayerHeadList.clear();
	_mailSysHeadList.clear();

	uint32 type = data->a_mailType;
	uint32 count  = data->b_mailCount;
	int32 num  = data->c_startNum;
	std::list<SCMD1A1Node> arr = data->d_mailList;

	std::list<SCMD1A1Node>::iterator iter; 
	for(iter = arr.begin(); iter != arr.end(); iter++)
	{
		MailHeadVo headVo;
		headVo.mailId = iter->a_mailId;
		headVo.senderName = iter->b_senderName;
		headVo.mailTitle = iter->c_mailTitle;
		headVo.mailType = iter->d_mailType;
		headVo.mailStatus = iter->e_mailStatus;
		headVo.sendTime = iter->f_sendTime;
		headVo.attachStatus = iter->g_attachStatus;

		_mailHeadList.push_back(headVo);

		if (headVo.mailType == MailConst::MAIL_TYPE_SYSTEM)
		{
			_mailSysHeadList.push_back(headVo);
		}
		else if (headVo.mailType == MailConst::MAIL_TYPE_PLAYER)
		{
			_mailPlayerHeadList.push_back(headVo);
		}
	}
	/*
	_mailHeadList.reverse();
	_mailPlayerHeadList.reverse();
	_mailSysHeadList.reverse();
	*/
	_listCreated = true;
	sendNotification(Facade_Mediator,AppFacade_Mail_Mediator,(char *)data,MailMediator::UPDATE_MAIL_LIST);
}

/**
		 *获得邮件正文 
		 * @param mail
		 * 
		 */
void MailProxy::updateMailContent(SCMD1A3 * data)
{
	int id = data->a_mailId;
	MailContentVo contentVo;
	contentVo.mailId = data->a_mailId;
	contentVo.senderName = data->b_senderName;
	contentVo.mailTitle = data->c_mailTitle;
	contentVo.mailType = data->d_mailType;
	contentVo.mailStatus = data->e_mailStatus;
	contentVo.sendTime = data->f_sendTime;
	contentVo.attachStatus = data->g_attachStatus;
	contentVo.mailContent = data->h_mailContent;
	contentVo.attachId = data->i_attachId;
	contentVo.goodsNum = data->j_goodsNum;
	if (_mailContentDic.find(id) == _mailContentDic.end())
	{
		_mailContentDic.insert(make_pair(id,contentVo));
	}
	else
	{
		_mailContentDic.erase(id);
		_mailContentDic.insert(make_pair(id,contentVo));
	}

	sendNotification(Facade_Mediator,AppFacade_Mail_Mediator,(char *)data, MailMediator::SHOW_MAIL_CONTENT);
}

std::list<MailHeadVo> * MailProxy::getHeadListByType(int type)
{
	switch(type)
	{
	case MailConst::MAIL_TYPE_ALL:
		return &_mailHeadList;
		break;
	case MailConst::MAIL_TYPE_SYSTEM:
		return &_mailSysHeadList;
		break;
	case MailConst::MAIL_TYPE_PLAYER:
		return &_mailPlayerHeadList;
		break;
	}
	return 0;
}

bool MailProxy::getIsListCreated()
{
	return _listCreated;
}

int MailProxy::getTotalNum()
{
	return _totalNum;
}

int MailProxy::getSystemMailNum()
{
	return _sysMailNum;
}

int MailProxy::getPlayerMailNum()
{
	return _playerMailNum;
}

MailContentVo * MailProxy::getMailContent(uint32 mailId)
{
	if(_mailContentDic.find(mailId) != _mailContentDic.end())
	{
		return &_mailContentDic.find(mailId)->second;
	}
	return 0;
}