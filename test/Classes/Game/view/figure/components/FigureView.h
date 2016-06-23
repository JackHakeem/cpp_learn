#ifndef HLQS_FigureView_H_
#define HLQS_FigureView_H_
#include "LayerNode.h"
#include "model/skill/vo/UpGradeInfo.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "FigureCreate.h"
#include "model/figure/vo/WashVo.h"
#include "AttributeLayer.h"
#include "SkillLayer.h"

using namespace cocos2d;

#define MAX_ROLE_NUM (32)
#define MAX_SKILL_NUM (128)

class SkillView;
class PeiyangView;

class FigureView: public LayerNode
{
public:
	int _currentId; //FIGUER SELECTED id

	enum
	{
		RENDERZ_button = 0,
		RENDERZ_buttonSkill,
		RENDERZ_lable1,
		RENDERZ_lableSkill,
		RENDERZ_figureCreate,
	};

	enum
	{
		TAG_BTN_IMG = 0,
		TAG_BTN_PEIYANG = 51,
		TAG_BTN_SHUXING,
		TAG_BTN_XUNLIAN,
		TAG_BTN_IDENTIFY,
		TAG_BTN_EQ,
		TAG_SKILL_POPLAYER = 101,
		TAG_STUNT_POPLAYER,
		TAG_Skill_HightLight = 221,
		TAG_Container = 1211,
	};

	enum TouchStateEnum
	{
		TouchState_0 = 0,// no state, is not inspire the touch module
		TouchState_1, // points down, also didn't move, BAGVIEW_TOUCH_STATE1_INTERVAL seconds before
		TouchState_2, // BAGVIEW_TOUCH_STATE1_INTERVAL seconds after the
		TouchState_3, // backpack to scroll mode
		TouchState_4, // what nothing mode
		TouchState_5, // click on the selected mode
	};

	enum PanelState
	{
		STAT_ROLE = 0,
		STAT_SKILL,
		STAT_PEIYANG,
		STAT_TRAIN,
		STAT_IDETIFY
	};
	int _stateSkill;
	bool _IsStuntsPop;
	int RoleID[MAX_ROLE_NUM];
	int SkillID[MAX_SKILL_NUM];
	int _statPanel;

	CCPoint preTouchPoint;
	CCPoint currentTouchPoint;

	CCSize m_viewSize;
	LayerNode * __container;
	//FigureCreate* _figureCreate; //closed by LH
	SkillView * _skillV;
	PeiyangView *_peiyangV;

	AttributeLayer * _attrLayer;
	SkillLayer *_skillPopLayer;
	CCSprite * spriteLight;
	int _highLightIndex;

	unsigned int _nTouchCount;
	CCNode * _pCurSelectEquip;
	int _nClickIndex;
	int _nClickIndexCount;
	bool _isSelected;
	CCSize _csBt;

	CCMenuItemSprite *_buttonAtr;
	CCMenuItemSprite *_buttonTrain;
	CCMenuItemSprite *_buttonPeiyang;
	CCMenuItemSprite *_buttonJianding;

	CCMenu *buttonMenuAtr;
	CCMenu *buttonMenuTrain;
	CCMenu *buttonMenuPeiyang;
	CCMenu *buttonMenuJianding;
	CCMenu *buttonMenuChucu;
public:
	FigureView();
	FigureView(CCSize& viewSize);
	bool init();
	void showEquipInfo();
	void showSkillInfo();
	void changeSkill(int figure, int rank, UpGradeInfo info);
	void updateEquipInfo(int fid, int grid);
	void updateEquipTip(int fid, int grid);
	int currentId();
	void currentId(int value);
	void closeView();
	void addButton();
	void clickButtonPeiyang(CCObject* pSender);
	void clickButtonSkill(CCObject* pSender);
	void clickButtonEQ(CCObject* pSender);
	void showSkillSelectPanel(int _state);
	void show2Stunts(bool isStuntsPop);
	int getCurFigureID(int index);
	void showEquipTips(CCNode* pNode, void* data);
	void setSkillHightLight(int index);
	void showButtonByTag(int tag , bool var);

	void clickButtonIdentify(CCObject * pSender);
//	void sendOnClotheRequest(int figureID,int sitGrid);
//	int _curTouchState;
// 	int getTouchState();
// 	void setTouchState(int var);
	void step(CCTime dt);
	void count(ccTime dt);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void updateFigureInfo(int fid, WashVo* washValue);
	CC_PROPERTY(int32, _TouchState, TouchState)	

	void clickButtonTrain(CCObject* pSender);
	void changePopContainerSize();

	void  enableButton(int tag ,bool var);
	CCNode * getNewHandItem( int id );
	void clickButtonAtt(CCObject* obj);
	void resetBtn();
};

#endif