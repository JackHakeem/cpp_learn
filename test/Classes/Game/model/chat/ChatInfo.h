#pragma once

#include "BaseType.h"

class ChatInfo
{
public:
	ChatInfo()
	{
		channel = 0;
		fromId = 0;
		fromName = "";
		content = "";
		data = "";
		line = 1;
		isPerson = false;
		isSelf = false;
		toId = 0;
		toName = "";
		isGM = false;
		color = "";
	}
		
	int channel;					//Ƶ������
	int fromId;					//���ID
	std::string fromName;				//�������
	std::string content;			//��������
	std::string data;			//�������ݣ�ս����չʾ��Ʒ�ȣ�
	int line;				//��·
	bool isPerson;	//�Ƿ���˽�� ��ѡ
	bool isSelf;		//�Ƿ����Լ� ��ѡ
	int toId;				//˽�Ķ���ID ��ѡ
	std::string toName;			//˽�Ķ������� ��ѡ
	bool isGM;	//�Ƿ�GM
	std::string color;		//��ɫ ��ѡ
		
};
