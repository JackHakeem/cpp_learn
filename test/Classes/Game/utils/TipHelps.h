#ifndef _TIPHELPS_H_
#define _TIPHELPS_H_

#include "BaseType.h"
#include "LayerNode.h"

class TipBase;
class TipConst
{
public:
	enum
	{
		REPLACE 	= -1,		//�滻������ԭ���ġ�StringToChange����
		NORMAL 		= 0,		//��ͨ
		BACKPACK 	= 1,		//����
		BANK 		= 2,		//�ֿ�
		EQUIPMENT 	= 3,		//װ��
		STRENG 		= 4,		//ǿ��
		MAIL		= 5,		//�ʼ�
		SHOP		= 6,		//�ߵ�
		DIALOG		= 7,		//����Ի���
	};
};

class TipHelps
{
public:
	TipHelps();
	~TipHelps();

	void init(bool isEquip=false, int32 type =0, bool isSkill = false, bool isXH=false);
	void setToolTips(LayerNode* sprite, TipBase* tips);//, std::string tips
	void setTips(TipBase* tips = 0, TipBase* otherTips = 0);
	void timerComplete();
	void rollOverHander();
public:
	int32 _type;
	bool _isEquip;
	bool _isSkill;
	bool _isXH;
	LayerNode* _sprite;
	TipBase* _toolTips;
	bool _isTip;
};

#endif