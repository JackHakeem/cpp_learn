#ifndef _SETTINGVIEW_H_
#define _SETTINGVIEW_H_

#include "PopContainer.h"
#include "LayerNode.h"

class FPContainer;
class SettingView:public PopContainer
{
public:
	enum
	{
		SettingViewZ_main,
		SettingViewZ_account,
		SettingViewZ_music,
	};

	enum
	{
		SettingViewTAG_main,
		SettingViewTAG_account,
		SettingViewTAG_music,
	};


	SettingView();
	~SettingView();
	bool init();
	
	
	void clickAccount(CCObject* pSender);
	void clickMusic(CCObject* pSender);

	virtual void clickCloseHandler(CCObject* pSender);
public:

};

#endif