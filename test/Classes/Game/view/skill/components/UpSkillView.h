#ifndef _UPSKILLVIEW_H_
#define _UPSKILLVIEW_H_
#include "PopContainer.h"
#include "view/figure/components/SkillView.h" 
#include "model/skill/vo/UpGradeInfo.h"
#include "UPSkillItem.h"

USING_NS_CC;

#define ROW_UPSKILL (4)
#define COL_UPSKILL (5)
#define UPSKILL_NUM_PER_PAGE (ROW_UPSKILL*COL_UPSKILL)

#define MAX_TAB (8)

class CrystalProxy;
class UPSkillCreate;
class UpSkillView : public PopContainer
{
public:
	UpSkillView();
	~UpSkillView();

	bool init();
	void addBackGround();
	void addScrollViews();
	void addButtons();
	void loadDirections(int tabID);
	void updateDirections(int tabID);
	void loadSkillItems();
	void loadFormationItems();
	void loadTalentItems();
	void clickCloseHandler(CCObject * pSender);
	void clickSkillHandler(CCObject * pSender);
	void clickFormationHandler(CCObject * pSender);
	void clickTalentHandler(CCObject * pSender);
	void clickUpgradeHandler(CCObject * pSender);
	void addNewPassiveSkill(UpGradeInfo *info);
	void addNewFormation(UpGradeInfo *info);
	void loadUPSkillTips(UpGradeInfo *info);
	void showDefaultTips(int tabID);
	UPSkillCreate * getCurrentCreate();
	void enableButton(int tag, bool var);
	void setBtnState(bool a[]);
	bool isCanUpgradeOK(UpGradeInfo * info);

	void onPrePage(CCObject * pSender);
	void onNextPage(CCObject * pSender);
	void lockBtn(ccTime dt);

	void setDefaultPanel();

	void updatePractice();

	CCNode * getNewHandItem(int id);

	virtual void removeDataObjectChild();

public:
	enum
	{
		Z_BG = 0,
		Z_SCROLL,
		Z_BTN
	};
	enum
	{
		TAG_BG = 0,
		TAG_PASSIVE = 10,
		TAG_FORMATION,
		TAG_TALENT,
		TAG_TIPS = 20,
		TAG_BUTTON = 50,

		TAG_BTN_IMG = 101,
		TAG_BTN_UPGRADE = 201,

		TAG_BTN_PASSIVE = 211,
		TAG_BTN_FORMATION,
		TAG_BTN_TALENT,

		TAG_DIR_LEFT = 301,
		TAG_DIR_RIGHT = 302,
		TAG_DIR_TXT = 303,
	};
	enum
	{
		TAB_PASSIVE = 0,
		TAB_FORMATION,
		TAB_TALENT
	};

	enum
	{
		MAX_FORMATION_LEVEL = 20,
	};

	enum
	{
		MAX_SKILL_LEVEL = 30,
	};

	CCSize _viewSize;
	int _nLen[MAX_TAB];
	int PassiveSkillID[MAX_SKILL_NUM];
	int FormationSkillID[MAX_SKILL_NUM];
	//UPSkillItem * _curSelectedItem;
	int _curSelectedItemTag;
	LayerNode * _tipsLayer;
	int _curSelectTab;
	CCMenu * _skillMenu;
	CCMenu * _formationMenu;
	CCMenu * _talentMenu;

	CCLayer *_pContainer;

	CrystalProxy * _pCryProxy;

	CCMenuItemSprite *_btnUpgrade;
};

#endif
