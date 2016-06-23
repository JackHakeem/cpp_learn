#pragma once

class MailVo
{
public:
	MailVo() : id(0),type(0),date_time(""),sender(""),receiver(""),title(""),body(""),status(0),isSend(false)
	{

	}
	unsigned int id;			
	unsigned int type;			//类型，参照 MailConst定义
	std::string date_time;		//日期时间
	std::string sender;		//发件人
	std::string receiver;		//收件人
	std::string title;			//标题
	std::string body;			//正文
	unsigned int status;		//0:未读邮件      1:已读邮件 ，参照 MailConst定义
	bool isSend;				//true:已发邮件      false:收到邮件
};