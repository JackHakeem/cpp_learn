#pragma once

class MailVo
{
public:
	MailVo() : id(0),type(0),date_time(""),sender(""),receiver(""),title(""),body(""),status(0),isSend(false)
	{

	}
	unsigned int id;			
	unsigned int type;			//���ͣ����� MailConst����
	std::string date_time;		//����ʱ��
	std::string sender;		//������
	std::string receiver;		//�ռ���
	std::string title;			//����
	std::string body;			//����
	unsigned int status;		//0:δ���ʼ�      1:�Ѷ��ʼ� ������ MailConst����
	bool isSend;				//true:�ѷ��ʼ�      false:�յ��ʼ�
};