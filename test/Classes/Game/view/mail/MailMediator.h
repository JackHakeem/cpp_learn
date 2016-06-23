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
	void sockAttachResult(SCMD1AE * data);	//��ȡ�ʼ��������
	void sockSendMailResult(SCMD1A7 * data);	//�����ʼ��ķ���ֵ
	void sockMailDelete(SCMD1A5 * data);	//socket:ɾ���ʼ��ظ�
	void sockMailReceive(SCMD1A9 * data);	//socket:���յ����ʼ�
	void sockMailList(SCMD1A1 * data);	//socket:�ʼ��б���
	void sockMailContent(SCMD1A3 * data);	//socket:�ʼ���ϸ���ݵ���
	void defaultMailList();		//�����䣬Ĭ�������һҳ�б��ʼ�����ѡ��ȫ��
	void sockMailCount(SCMD1AB * data);
	
	void onChangePage(CCObject * pSender);	//�����һҳ����һҳ
	void onMailTypeClick(uint32 tabType)	;	//��������ǩ�����������б�
	void requestMailList();					//��ʼ������ҳ���ı��ʼ����͵�����£���Ҫ�����ʼ��б�
	void requestMailCount();
	void onGetAttachRequest(uint32 mailId);
	void onMailDeleteClick(std::list<uint> mailList);	//���ɾ���ʼ�
	void onMailItemClick(uint32 id);	//���ĳ���ʼ�ͷ��������ϸ����
	void onSendMailClick(std::string recvName,std::string mailTitle,std::string mailContent);	//������Ͱ�ť
	void onMailAttachClick(unsigned int attachId);	//������������ȡ������Ʒ, ���жϱ���������Int:�ʼ�ID
	//void popHandler(CCObject * pSender);	/*ȫ����Ϣ�������̰���ʱ��ʾ���߹ر��ʼ�����*/
	//void loadMailSkin(CCObject * pSender);
	void showMailView();
	void startListener();
	//void onCloseView(CCObject * pSender);
	void updateMailList(uint32 mailType, uint32 mailCount, int startNum);	//�����ʼ��б�ͬʱȡ����ҳ������ǰҳ�����ʼ�����
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