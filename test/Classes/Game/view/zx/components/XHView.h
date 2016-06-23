#pragma once


#include "PopContainer.h"
#include "LayerNode.h"
#include "socket/command/s46/SCMD464_466Node.h"
#include "socket/command/s46/SCMD46ANode.h"

class XH;
class XHView:public PopContainer
{
public:
	enum
	{
		
		XHViewTAG_FIGURE = 500,

		XHViewTAG_SLOT = 1000,

		XHViewTAG_BAG = 2000,

		XHViewTAG_COPY = 3000,

		XHViewTAG_XH_VALUE = 4000,
	};

	enum
	{
		XHViewBagTAG_name = 10,
		XHViewBagTAG_pic = 11,
	};

	enum
	{
		XHViewCtl_NONE,
		XHViewCtl_PRESSED,
		XHViewCtl_INTERVAL_PASS,
	};

	enum
	{
		XHViewEquipTAG_LOCKBG = 500,
	};

	XHView();
	~XHView();
	bool init();
	void clickClose(CCObject* pSender);
	void clickOneKeyHeCheng(CCObject* pSender);
	void clickGoZX(CCObject* pSender);
	void buildBagXH(std::list<SCMD464_465Node>& a_XHList);
	void buildEquipXH(std::list<SCMD46ANode>& a_XHEquipList);
	void registerWithTouchDispatcher();

	void handleXHMove(CCObject* pSender);
	void handleXHMoveCancel(CCObject* pSender);
	void showFigureXH(int32 roleId);
	void updateXHViewValue();
	void handleOneKeyHeCheng(CCObject* pSender);
	void handleOneKeyHeChengCancel(CCObject* pSender);
public:
	void onEnter();
	void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	bool getXHByTouch(CCPoint touch, int& posType, int& pos);
	void step(float dt);
	void startSchedule();
	void stopSchedule();
	void setCtlState(int val) {m_iCtlState = val;}
	int getCtlState() {return m_iCtlState;}
	bool createCopy(XH* pOrg);
	void cancelCopy();

public:
	LayerNode* _pContainer;
	LayerNode* m_pEquipSlot[8];
	LayerNode* m_pBag[16];
	std::map<int, SCMD46ANode** > m_vXHRoleEquipList;
	//
	float m_fCtlInterval;
	int m_iCtlState;
	int m_iCopyPosType;
	int m_iCopyPos;
	CCPoint m_vPreTouchPoint;
	int m_iReadySendPosType;
	int m_iReadySendPos;
	int m_iXHValue;
	
};