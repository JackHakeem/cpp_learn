#ifndef _MemberVo_H_
#define _MemberVo_H_

#include "BaseType.h"
#include "GuildVoBase.h"
#include "manager/LangManager.h"

class MemberVo : public GuildVoBase
{
public:
	MemberVo()
	{
		name = "";
		id = 0;
		duty  = "";
		level = 0;
		fame = 0;
		state = "";
		contribution = 0;
	}
	virtual ~MemberVo(){}
	virtual int getType() {return GuildVoBase_MemberVo;}
public:
	string name;  	// ��Ա����
	int id;             //��ԱID
	string duty;  	// ��Աְ�񣨻᳤�����᳤����Ա����Ա��
	int level ;  		// �ȼ�
	int fame ;  		// �ƺ�
	string state; 	// ״̬��-1 ����   0 ����  else ����X��
	int contribution;		//���׶�

	int dutyValue()
	{
		if(duty == LangManager::getText("GLD038") ) return 4;
		if(duty == LangManager::getText("GLD039") ) return 3;
		if(duty == LangManager::getText("GLD058") ) return 2;
		if(duty == LangManager::getText("GLD059") ) return 1;
		return 0;
	}
};

#endif