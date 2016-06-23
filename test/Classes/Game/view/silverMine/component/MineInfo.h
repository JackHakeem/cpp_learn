#pragma once

#include "BaseType.h"

class CCUIBackground;
class MineView;
class CustomCD;
class MineInfo:public LayerNode
{
public:
	MineInfo();
	~MineInfo();

	bool init(MineView* pContainer);
	void updateMoveCD(uint moveCD, bool inCD);
	void updateDigCD(uint digCD, bool inCD);
	void step(float dt = 0);
	static std::string formatData(int value);
	void setDigCD(std::string str);
	void setMoveCD(std::string str);
	void btnClick_showRank(CCObject* pSender);
	void showUI(CCObject* pSender);
	void goldInspire(CCObject* pSender);
	void pracInspire(CCObject* pSender);
	void updateAttPlus(int plus);
	void updateDefPlus(int plus);
	void isAllFull();
	void hide(CCObject* pSender);
	void lockBtn(ccTime dt);
public:
	int m_digOffset;	// jae note for time error
	int m_moveOffset;

	MineView* pContainer;
	uint _moveCD;
	uint _digCD;
	bool _inDigCD;
	bool _inMoveCD;
	bool _hasStep;
	CustomCD* _txtMoveCD;
	CustomCD* _txtDigCD;

	CCMenuItemSprite *_btnGoldImg;
	CCMenuItemSprite *_btnPracImg;
public:
	CCUIBackground* m_bg1;
	CCUIBackground* m_frame_1[2];
	CCUIBackground* m_frame_0[2];
	CCLabelTTF* m_txt[2];
	CCMenuItemSprite* _btn_showRank;
	CCMenuItemSprite* _btn_change;
	CCLabelTTF* m_Label_change;
	CCMenuItemSprite* m_btnGoldInspire;
	CCMenuItemSprite* m_btnPracInspire;
	CCLabelTTF* m_txtGW1;// ¹¥»÷¼Ó³É
	CCLabelTTF* m_txtGW2;
	bool _gIsFull;
	bool _dIsFull;
	bool m_hide;
};