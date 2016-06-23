#ifndef _GuildInfoVo_H_
#define _GuildInfoVo_H_

#include "BaseType.h"
#include "GuildVoBase.h"

class GuildInfoVo:public GuildVoBase
{
public:
	GuildInfoVo()
	{
		id = 0;
		name = "";
		leaderName = "";
		guildGrade = 0;
		emblemGrade = 0;
		rank = 0;
		members = 0;
		memberLimit = 0;
		ctime = "";
		qq = "";
		notice = "";
		intr = "";
		flag = 0;
		state = 0;
		abortTime = 0;
	}
	virtual ~GuildInfoVo(){}
	virtual int getType() {return GuildVoBase_GuildInfoVo;}
public:
	int id ; 			// ����ID 
	string name;  // ��������
	string leaderName; //�᳤����
	/**����ȼ�*/
	int guildGrade ;  	// ����ȼ�
	/**���յȼ�*/
	int emblemGrade ;  	// ���յȼ�
	int rank ;  		// ��������
	int members;  		// ��Ա��
	int memberLimit;  	// ��Ա������
	string ctime;  // ����ʱ�� 
	string qq;   	// QQȺ 
	string notice;// ���� 
	string intr;   //�������
	uint flag;          //�Ƿ�������
	uint state;          //�Ƿ��ɢ��, 1Ϊ��ɢ ��
	int abortTime;      //��ɢ��ʱ���
};

#endif