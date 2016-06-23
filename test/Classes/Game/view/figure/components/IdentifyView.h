#ifndef HLQS_IdentifyView_H_
#define HLQS_IdentifyView_H_

#include "PopContainer.h"

USING_NS_CC;

class IdentifyView : public PopContainer
{
public:
	IdentifyView();
	~IdentifyView();
	virtual bool init();
	void initHeadMap();
	void loadItems();

	void updateRoleInfoLayer();
	void updateDiffLayer(char * data);
	void updateCurrentIdentifyLayer(char * data);
	void updateNewIdentifyLayer(char * data);
	void updateSelectedOptionsLayer(int type);
	void updateIdentifyButtons(bool bVar);

	void onIdentifyHandler(CCObject * pSender);
	void onSaveHandler(CCObject * pSender);
	void onCancelHandler(CCObject * pSender);
	void onBuyGridHandler(CCObject * pSender);

	int getCurMerchId();

public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

public:
	CCSize _winSize;
	int _CurScreen;
	int _type;
	std::map<int,int> headMap;

	enum
	{
		ItemType_Gold = 0,
		ItemType_Reel = 1,
	};

	enum
	{
		Tag_RoleInfoLayer = 10,
		Tag_DiffLayer,
		Tag_CurrentIdentifyLayer,
		Tag_NewIdentifyLayer,
		Tag_SelectedOptionsLayer,
		Tag_IdentifyButtons,
	};
};

#endif