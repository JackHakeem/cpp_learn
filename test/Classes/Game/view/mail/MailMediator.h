#pragma once
#include "mvc/Mediator.h"

class MailView;
class SCMD1AE;
class SCMD1A7;
class SCMD1A5;
class SCMD1A9;
class SCMD1A1;
class SCMD1A3;
class SCMD1AB;

class MailMediator : public Mediator
{
public:
	MailMediator();
	~MailMediator();
	virtual void handleNotification( int M2Vcmd, char* data );
	void sockAttachResult(SCMD1AE * data);	//获取邮件附件结果
	void sockSendMailResult(SCMD1A7 * data);	//发送邮件的返回值
	void sockMailDelete(SCMD1A5 * data);	//socket:删除邮件回复
	void sockMailReceive(SCMD1A9 * data);	//socket:接收到新邮件
	void sockMailList(SCMD1A1 * data);	//socket:邮件列表到达
	void sockMailContent(SCMD1A3 * data);	//socket:邮件详细内容到达
	void defaultMailList();		//打开邮箱，默认请求第一页列表，邮件类型选择全部
	void sockMailCount(SCMD1AB * data);
	
	void onChangePage(CCObject * pSender);	//点击上一页、下一页
	void onMailTypeClick(uint32 tabType)	;	//点击分类标签，重新请求列表
	void requestMailList();					//初始化、翻页、改变邮件类型的情况下，都要请求邮件列表
	void requestMailCount();
	void onGetAttachRequest(uint32 mailId);
	void onMailDeleteClick(std::list<uint> mailList);	//点击删除邮件
	void onMailItemClick(uint32 id);	//点击某个邮件头，请求详细内容
	void onSendMailClick(std::string recvName,std::string mailTitle,std::string mailContent);	//点击发送按钮
	void onMailAttachClick(unsigned int attachId);	//向服务端请求领取附件物品, 先判断背包容量；Int:邮件ID
	//void popHandler(CCObject * pSender);	/*全局消息，当键盘按下时显示或者关闭邮件窗口*/
	//void loadMailSkin(CCObject * pSender);
	void showMailView();
	void startListener();
	//void onCloseView(CCObject * pSender);
	void updateMailList(uint32 mailType, uint32 mailCount, int startNum);	//更新邮件列表，同时取得总页数、当前页数、邮件类型
	void updateMailText(int num);
public:
	enum
	{
		UPDATE_MAIL_LIST,
		SHOW_MAIL_CONTENT,
		SHOW_MAIL_COUNT,
	};

	MailView * _mailView;
	uint32 _curMailType;
	uint32 _totalPage;
	uint32 _curPage;
	uint32 _reqNum;
	uint32 _unreadNum;
protected:
private:
};