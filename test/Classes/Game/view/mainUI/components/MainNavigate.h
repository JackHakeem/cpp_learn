#ifndef _MAINNAVIGATE_H_
#define _MAINNAVIGATE_H_

#include "BaseType.h"
#include "MainNavigateX.h"

USING_NS_CC;

class MainNavigateX;
class MainNavigateY;

class MainNavigate:public LayerNode
{
public:
	enum
	{
		MainNavigateZ_mainNavigateX,
		MainNavigateZ_mainNavigateY,
		MainNavigateZ_menubtn,
		MainNavigateZ_menubtnX,
		//MainNavigateTAG_
	};

	enum
	{
		MainNavigateTAG_mainNavigateX,
		MainNavigateTAG_mainNavigateY,
		MainNavigateTAG_menubtn,
		MainNavigateTAG_menubtnX,
		//MainNavigateTAG_
	};
public:
	MainNavigate();
	~MainNavigate();

	bool init();
	//void visit();
	void resize();
	void configUI();
	void addButton(int32 type, int32 sitNum, bool isTween);
	void handleMainBtn(CCObject* pSender);
	SpriteNode* getBtnX();
	void popUIHandler1(CCObject* pSender);//½ÇÉ«
	void popUIHandler2(CCObject* pSender);//±³°ü
	void popUIHandler4(CCObject* pSender);// yanxi
	void popUIHandler3(CCObject* pSender);//streng
	void popUIHandler6(CCObject* pSender);
	void popUIHandler7(CCObject* pSender);
	void popUIHandler8(CCObject* pSender);//Ë®¾§
	void popUIHandler9(CCObject* pSender);//formation
	void popUIHandler10(CCObject* pSender);//train
	void popUIHandler11(CCObject* pSender); // task
	void popUIHandler13(CCObject * pSender); // zhanxing
	void popUIHandlerY1(CCObject* pSender); // ziyuantian
	void popUIHandlerY2(CCObject* pSender); // world map
	void popUIHandlerY3(CCObject* pSender); // setting
	void popUIHandlerY4(CCObject* pSender); // activity
	void popUIHandlerY5(CCObject* pSender); // mail
	void popUIHandlerY6(CCObject* pSender); // help
	CC_PROPERTY(bool, _isMainBtnOpen, isMainBtnOpen);

	void popUIHandlerCD(CCObject* pSender);

	void popUIHandlerMap(CCObject* pSender);

	void popUIHandlerArena(CCObject* pSender);//arena

	void popUIHandlerMail(CCObject* pSender);//mail
	void popUIHandlerHelp(CCObject* pSender);//help

	virtual void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	void ccTouchEnded(CCTouch* touch, CCEvent* event);
	void onCompleteButtonFly(CCNode *pNode, void *pData);
	void onCompleteButtonFlyForVscroll(CCNode *pNode, void *pData);
	void onCompleteAddButton(CCNode *pNode, void *pData);
	CCNode *getNewHandItem(int btnId);

	void onHideOtherPlayers(CCObject * pSender);

	//Doyang 20120723
	void outOfMap(CCObject* pSender); // setting
	void hideOutMap();
	void showOutMap();

	// LH 20121025
	void showChatComponents(bool bhide);
	void enableMainavigate(bool bVar);

	//
	void setMapName(std::string name);

	void showVScrollAndTaskUIView(bool var);
	void addButtonByLev(int lev);
	
public:
	MainNavigateX* _mainNavigateX;
	MainNavigateY* _mainNavigateY;
	bool _isCrystalOpen;
};

#endif