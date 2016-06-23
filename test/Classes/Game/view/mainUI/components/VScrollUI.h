#ifndef _VSCROLL_H_
#define _VSCROLL_H_
#include "LayerNode.h"
#include "UIListView/CCUIListView.h"
#include "utils/ScaleUtil.h"
#include <vector>
#include "VSCustomCD.h"

using namespace cocos2d;

#define CC_NEW_VSCROLLUI_OPEN (1)
#define CCSZIE_LISTVIEW CCRectMake(POSX(0) , POSX(0) ,POSX(94) , POSX(425))

class LHLabelTTF;
class VScrollUI : public LayerNode, CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:
	VScrollUI();
	virtual ~VScrollUI();

	virtual bool init();
	void loadItem();
	void loadItemNew();
	void resetListView();
	void onClick2Up(CCObject * pSender);
	void onClick2Down(CCObject * pSender);
	CCNode * getNewHandItem( int btnId );
	void onClickHideVscroll(CCObject * pSender);
	void clickHideVscroll();
	void movieCallback(CCNode * pNode , void * data);
	void setItemLight(LayerNode *itemCell ,bool var);
	void showUI(bool var);
	void setDirState(int state);
	void runMyAction(CCNode * pNode , CCAction * pAction);
	CCAction * getMyAction(int type);
	void reSortButtons();
	int getMaxListItemCounts();
	CCSize getListLayerSize();
	void resetContentLayerPosition();
	void scrollToItemByIndex(int index , ccTime duration);
	CCPoint getNewHandItemPos(int index);
	void initPos();
	int getLevByPos(int pos);

public: // new UI
	void initItem();
	bool isNeedAdded(int id);
	std::vector<string> getPathById(int id);
	void onItemClickHandle(CCObject * pSender );
	void addButtonByLev(int lev);
	void addButton(int id);
	void reSortPosition();
	void resetSize();
	void showCDICon(bool var);
	//void updateCDICon();
	void updateShowLabel();
	VSCustomCD * getCDItemById(int id);
	LHLabelTTF * getShowLabelById(int id);
	int getCDCnt();
	int getOtherCnt();
	void updateTimer(ccTime dt);
	void startTimer();
	void stopTimer();

public:
	virtual int getCount();
	virtual LayerNode * getView( int position );
	virtual void onItemClickListener( LayerNode *itemCell, int position );
	virtual void onItemTouchListener( LayerNode *itemCell, int position );
	virtual void onItemTouchCancelListener( LayerNode *itemCell, int position );

public:
	enum
	{
		Tag_ItemLight = 3,
		Tag_Item = 10,
		Tag_HideBack,
		Tag_HideBtn,
		Tag_ListView = 20,
		Tag_UpDir = 30,
		Tag_DownDir,
	};

	enum
	{
		Tag_back = 0,
		Tag_NewHandSprite = 11,
		Tag_ItemMenu = 1000,
		Tag_ItemCDIcon = 1100,
		Tag_ItemCDText = 1200,
		Tag_ItemShowText = 1500,
	};

	enum
	{
		Item_strength = 0, 
		Item_Levy,
		Item_Ore,
		Item_Arena,
		Item_Train,

		Max_Count,
	};

	enum
	{
		Stat_Normal = 0, 
		Stat_Up = 1, 
		Stat_Down = 2, 
		Stat_Hide = 3,

	};

	enum
	{
		ActionType_0 = 0, 
	};

	
	CC_SYNTHESIZE(bool , _isHide , IsHide);
	CC_SYNTHESIZE(int , _listCount , ListCount);

protected:
public:
	CCMenuItemSprite * _pHideMenuItem;
	CCPoint _pos;
	CCPoint _originPos;
	CCSize _moveSize;
	CCPoint _btnPos;
	int levPos[121];
	int _deltaPos;
	int _btnArr[32];
	int _btnCnt;
	int _cdCnt;
	int _otherCnt;
	int _cd[121];
	int _other[121];
};

#endif