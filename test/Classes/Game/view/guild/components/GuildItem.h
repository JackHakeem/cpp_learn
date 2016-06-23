#pragma once

#include "BaseType.h"
#include "model/guild/vo/MemberVo.h"
#include "model/guild/vo/GuildInfoVo.h"
#include "cocos2d.h"
using namespace cocos2d;

class GuildItem:public LayerNode
{
public:
	enum
	{
		GuildItemZ_bg1,
	};
	enum
	{
		GuildItemTAG_bg1,
	};
	GuildItem();
	~GuildItem();

	bool init(GuildInfoVo guildVo);
	void initView();
	void onApplyBtnClick(CCObject* obj);
	void onExamineBtnClick(CCObject* obj);
	void canApply( bool flag );
public:
	//_item:MovieClip = null;				//����ItemԪ��
	//_rank:TextField = null;				//���������ֶ�
	//_name:TextField = null;				//���������ֶ�
	//_leader:TextField = null;			//����᳤�ֶ�
	//_level:TextField = null;			//����ȼ��ֶ�
	//_count:TextField = null;			//�����Ա��
	CCMenu* _btnApply;		//���밴ť
	CCMenu* _btnExamine;	//�鿴��ť
	//_introduce:String = "";				//�������
	CCLabelTTF* _applyText;
	GuildInfoVo _guildVo;		//������Ϣ����
};