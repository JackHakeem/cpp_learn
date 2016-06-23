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
	int _curItemIndex;	//当前点击的科技Item索引
	bool hasInit;
	TechVo* _curVo;
	CCLabelTTF* _techName;	//公会科技名称和等级
	CCLabelTTF* _techLev;	//公会科技名称和等级
	CCLabelTTF* _techRate;		//进度条上面的文字
	CCLabelTTF* _techPrompt;	//科技升级提示文字
	CCLabelTTF* _techTips;	//tips

	CCUIBackground* m_selectedSpriteImageUp;
};