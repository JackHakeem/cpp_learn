#pragma once

#include "BaseListPanel.h"
#include "model/guild/vo/GuildVoBase.h"

class CCUIBackground;
class GuildDispatcher;
class TechVo;


class TechPanel:public BaseListPanel
{
public:

public:
	TechPanel();
	~TechPanel();

	bool init();

	void updateList(std::list<GuildVoBase*>& listDatas);
	void onItemClick(CCObject* obj);
	void onDonateClick(CCObject* pSender);
	TechVo* getcurVo();
	void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );
	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void onDefaultClick(CCObject* pSender);
public:
	GuildDispatcher* _guildDispatch;
public:
	CCUIBackground* selectedSpriteImage[10];

	CCUIBackground* picBg;
	CCSprite* _rateBar;
	CCSprite* _items[10];
	std::vector<TechVo*> _arrVo;
	int _curItemIndex;	//��ǰ����ĿƼ�Item����
	bool hasInit;
	TechVo* _curVo;
	CCLabelTTF* _techName;	//����Ƽ����ƺ͵ȼ�
	CCLabelTTF* _techLev;	//����Ƽ����ƺ͵ȼ�
	CCLabelTTF* _techRate;		//���������������
	CCLabelTTF* _techPrompt;	//�Ƽ�������ʾ����
	CCLabelTTF* _techTips;	//tips

	CCUIBackground* m_selectedSpriteImageUp;
};