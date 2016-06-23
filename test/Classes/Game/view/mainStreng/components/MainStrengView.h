#ifndef _MAINSTRENGVIEW_H_
#define _MAINSTRENGVIEW_H_

#include "BaseType.h"
#include "PopContainer.h"
#include "HeritagePanel.h"

class StrengPanel;
class MeltingPanel;
class MagicPanel;

class MainStrengView : public PopContainer
{
public:
	MainStrengView();
	~MainStrengView();

public:

	enum
	{
		//---Melting
		PAGE_CHANGE,
		MELTING_CLICK,
		FIGURE_CLICK,
		INHERIT_REQUEST,
	};

	bool init();
	LAYER_NODE_FUNC(MainStrengView);
	void setDefaultStrengPanel();
	void onTabHandler( CCObject* pSender );
	void setPanel( int type, CCLayer* panel = 0 );
	void CloseBtCallback( CCObject* pSender );
	virtual void clickCloseHandler(CCObject* pSender);
	int32 getSelfTag();
	CCNode *getNewHandItem(int id);
	void refreshTabMenu();
	virtual void removeDataObjectChild();
private:
	CCMenu* pTabMenu;
	CCMenuItemSprite* _tabMc1;	 // strengthen TAB
	CCMenuItemSprite* _tabMc2;	 // melting TAB
	CCMenuItemSprite* _tabMc3;	 // magic TAB
	CCMenuItemSprite* _tabMc4;	 // inheritance TAB

	int m_iInitUIRoleLev;

public:
	StrengPanel* strengPanel; 	// streng panel 
	MeltingPanel* meltingPanel; // melting panel
	MagicPanel* magicPanel;		// magic panel
	HeritagePanel* inheritPanel; // inheritance panel

	CCLayer *_pContainer;

};

#endif