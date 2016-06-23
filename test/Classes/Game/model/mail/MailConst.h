#pragma once

class MailConst
{
public:
	MailConst()
	{
	}
	/*�����ʼ�����*/
	static const unsigned int MAIL_TYPE_ALL		=	0;	//ȫ��
	static const unsigned int MAIL_TYPE_PLAYER	=	1;	//���
	static const unsigned int MAIL_TYPE_SYSTEM	=	2;	//ϵͳ

	/*�����ʼ�״̬*/	
	static const unsigned int MAIL_STATUS_UNREAD	=	1;	//δ��
	static const unsigned int MAIL_STATUS_READED	=	2;	//�Ѷ�

	//����id����
	static const unsigned int GOLD_ITEM_ID		=	1;	// ��������ƷId
	static const unsigned int SILVER_ITEM_ID		=	2;	// ���������ƷId
	static const unsigned int PRACTICE_ITEM_ID	=	3;	// ����
	static const unsigned int POPULARITY_ITEM_ID	=	4;	// ����
	static const unsigned int EXP_ITEM_ID		=	5;	// ����
	static const unsigned int VIGOUR_ITEM_ID		=	6;	// ����
	static const unsigned int ENCHANT_ITEM_ID		=	7;	// ħ��ʯ
	static const unsigned int OTHER_ITEM_ID		=	99;	// �������ڰ�������ʾ����ƷID�����ڸ�ֵ

	//����״̬	
	static const unsigned int ATTACH_STATUS_NULL		=	0;	// 0�޸���
	static const unsigned int ATTACH_STATUS_UNLOAD	=	1;	// 1δ��ȡ
	static const unsigned int ATTACH_STATUS_LOADED	=	2;	// 2����ȡ
	static const unsigned int ATTACH_STATUS_LOADING	=	3;	// 3������ȡ��

	//�ʼ�����
	static const unsigned int ERR_MAIL_SEND_FAILED	= 101;		// �ʼ�����ʧ��
	static const unsigned int ERR_MAIL_DEL_FAILED		= 102;		// �ʼ�ɾ��ʧ��
	static const unsigned int ERR_MAIL_GET_DETAIL_FAILED	= 103;	// ��ȡ�ʼ�����ʧ��
	static const unsigned int ERR_MAIL_RECVER_NOEXIST	= 104;		// �ռ��˲�����

protected:
private:
};