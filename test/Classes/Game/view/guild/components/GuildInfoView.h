#pragma once

#include "BaseType.h"
#include "model/guild/vo/GuildInfoVo.h"
class GuildInfoView:public LayerNode
{
public:
	GuildInfoView(GuildInfoVo guildVo);
	~GuildInfoView();

	bool init();
	void dispear(CCObject* pSender);
	void registerWithTouchDispatcher( void );
	bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
public:
	LayerNode* _container;


	//__skin:MovieClip = null;	//������Ϣ���
	//_icon:MovieClip = null;	//����ͼ��
	//_level:TextField = null;		//����ȼ�
	//_name:TextField = null;			//��������
	//_leader:TextField = null;		//����᳤
	//_count:TextField = null;		//��������
	//_introduce:TextField = null;	//�������
	//_closeBtn:SimpleButton = null;	//���رա���ť
	GuildInfoVo _guildVo;
};