#pragma once

#include "LayerNode.h"
#include "KKUIListView/KKCCUIListView.h"
class SCMD13D;
class SCMD419;
class SCMD414;
class DungeonGUAMsgItem;


class ChallengeGuaView:public LayerNode, KKCCUIListViewAdapter, KKCCUIListViewItemActionListener
{
public:
	enum
	{
		ChallengeGuaViewTAG_radioSelect = 10,
	};
public:
	ChallengeGuaView();
	~ChallengeGuaView();

	bool init();
	void clickCloseHandler(CCObject* pSender);
	void onTAOFABegin(CCObject* pSender);
	void onTAOFACancel(CCObject* pSender);
	void clickRadio(CCObject* pSender);
	void stepGUA(float dt);
	virtual std::vector<LayerNode*>* getViewList();
	void addRecords(SCMD13D* pPacket);
	void addRecords(SCMD419* pPacket);
	void addStrRecords(char* label, ccColor3B color);
	void clearCacheNodes();
	void changeRound(int value);
	void addRoundRecords();
	void updateNeedVigour(SCMD414* pPacket);
public:
	CCMenuItemSprite* m_pStartGUA;
	CCMenuItemSprite* m_pStopGUA;
	int m_iSelectMode;
	std::vector<int> m_vMG;
	std::vector<std::string> m_vMGName;
	float m_timerGUA;
	int m_iMGIndex;
	int m_iRoundCount;
	int m_iMaxRound;
	KKCCUIListView* _pKKListView;
	std::vector<LayerNode*> _cacheNodes;
	LayerNode* _pShowChange[2];
	CCPoint aryRadioPNG[3];
	LayerNode* m_pContainer;
	int m_vNeedVigour[3];
	
	uint8 m_canChaTimes;
};