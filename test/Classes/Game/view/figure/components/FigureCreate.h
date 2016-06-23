#ifndef HLQS_FigureCreate_H_
#define HLQS_FigureCreate_H_
#include "CCUIPartialScrollView.h"
#include "EquiptmentItem.h"
#include "platform.h"

class FigureCreate:public CCUIPartialScrollView
{
public:
	enum
	{
		Z_ITEM = 0
	};
	enum SKILLENUM
	{
		TAG_ITEM = 0,
		TAG_ROLE_LEV = 26,
		TAG_MODEL = 99,
		TAG_EQUIP = 100,
		TAG_SKILL = 200,
		TAG_Skill_HightLight = 241
	};
	std::map<int, EquiptmentItem*> _equipDic; //  selected figure equipment
	int _currentId; // selected figure ID
	int _currentPage;
	std::map<int,bool> _isRebornDic;

public:
	FigureCreate();
    ~FigureCreate();
	FigureCreate(const CCRect& mRect);
	static FigureCreate* figureScrollViewWithCCRect(const CCRect& mRect);
	void currentId(int value);
	int currentId();

	void showEquipInfo();
	void showEquipInfo(int role_id, int page);
	void setEquipInfo(int sitGrid, GoodsInfo* info, int page);
	void setMercInfo(int role_id,int page);
	void updateEXPInfo(int32 figureID);
	void setIsReborn(int figureID,bool isReborn);
	void showModel(int figureID,int page);
	void showSkillInfo();
	void reNewScrollView();
	void updateRoleLevel(int figureID);
	void setSkillHightLight(int index);

public:
	
 	virtual void registerWithTouchDispatcher();
  	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
  	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	CCPoint preTouchPoint;
};
extern FigureCreate * g_pFigureScrollView; // add by lh

#endif